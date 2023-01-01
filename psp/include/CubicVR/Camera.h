/*
    This file is part of CubicVR.

    CubicVR is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    CubicVR is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with CubicVR; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
    
    
    Source (c) 2003 by Charles J. Cliffe unless otherwise specified
    To contact me, e-mail or MSN to cj@cubicproductions.com or by ICQ#7188044
    http://www.cubicproductions.com
*/

#ifndef CUBICVR_CAMERA_H
#define CUBICVR_CAMERA_H


#include <CubicVR/cvr_defines.h>
#include <CubicVR/GLExt.h>
#include <CubicVR/XYZ.h>
#include <CubicVR/Motion.h>
#include <CubicVR/SceneObject.h>


#define CAMERA_FREE 0
#define CAMERA_TARGET 1

#define CAMERA_CONTROLLER_FOV 100
#define CAMERA_MOTION_FOV 100


class IMPEXP Camera : public Resource, public Controllable
{
private:
public:
	
	unsigned short type;
	float fov, aspect, nearclip, farclip;
	int width, height;	
	
	static Camera *lastActive;
	
	float projectionMatrix[16];
	float viewMatrix[16];
	
#ifdef ARCH_PSP
	float camAngle;	// stored and used for env mapping on psp
#endif

#if !defined(ARCH_PSP) && !defined(OPENGL_ES) && !defined(ARCH_DC)
	float dof_near, dof_far;
	float dof_near_linear, dof_far_linear;
	inline void setNearDOF(float dof_near_in) { dof_near=dof_near_in; dof_near_linear = dof_near/(farclip-nearclip); };
	inline void setFarDOF(float dof_far_in) { dof_far=dof_far_in; dof_far_linear = dof_far/(farclip-nearclip); };
	inline float getNearDOF() { return dof_near; };
	inline float getFarDOF() { return dof_far; };
#endif
	
	XYZ position, rotation, target;
	Vector up,right;
	SceneObject *sceneObjTarget;
	
	Camera(int width_in, int height_in, float fov_in = 60, float nearclip_in=0.1, float farclip_in=2000.0, int type_in = CAMERA_FREE);
	Camera();
	~Camera();

	void control(int controllerId, int motionId, float value);
	
	void setSize(int width_in, int height_in);
	void setFOV(float fov_in);
	void setAspect(float aspect_in);
	void setAspect(int screen_w, int screen_h);
	void setPosition(const XYZ &pos);
	void setRotation(const XYZ &pos);
	void setTarget(const XYZ &pos);
	void bindTarget(SceneObject *sceneObj);
	void trackTarget(float trackingSpeed, float safeDistance);
	void moveViewRelative(XYZ &pt, float xdelta, float zdelta);

	btVector3 getRayTo(int x,int y);
	Vector getRay(int x,int y);
	void setClip(float near_in, float far_in);
	void setType(int type_in);
	
	void setup();
	
	float distSlopeX(float z);
	float distSlopeY(float z);
	static void orthoNearBounds(XYZ position, float ortho_width, float ortho_height, MATRIX4X4 projMatrix, MATRIX4X4 modelMatrix, float nearClip, XYZ &aabb1, XYZ &aabb2);
	static void orthoFarBounds(XYZ position, float ortho_width, float ortho_height, MATRIX4X4 projMatrix, MATRIX4X4 modelMatrix, float farClip, XYZ &aabb1, XYZ &aabb2);

};


#endif
