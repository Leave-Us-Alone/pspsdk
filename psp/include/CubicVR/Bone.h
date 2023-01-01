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

#pragma once

#include <CubicVR/cvr_defines.h>

#include <CubicVR/Motion.h>
#include <CubicVR/Shader.h>
#include <CubicVR/ObjectController.h>
#include <CubicVR/map_string.h>
#include <vector>

class IMPEXP Bone : public Controllable, public ObjectController
{
public:
//	ObjectController objController;
	std::vector<Bone *> children;

	Bone *parent;
	float matrix[16];
	XYZ start_pt, end_pt;
	
	XYZ center;
	
	XYZ restPosition;
	XYZ restDirection;
	float restLength;
	float strength;
	
	bool trans_init;

	Bone();
	~Bone();
	
	void calcMatrix(bool childBones=true,bool firstBone=true);
	void calcNodes(bool firstBone=true);

	void control(int controllerId, int motionId, float value);
	float read_control(int controllerId, int motionId);

	inline void setRestPosition(const XYZ &pt) { restPosition = pt; }
	inline void setRestDirection(const XYZ &pt) { restDirection = pt; }
	inline void setRestLength(float restLen) { restLength = restLen; }
	inline void setStrength(float strengthVal) { strength = strengthVal; }
	
	void bindChild(Bone &boneObj_in);
	void bindParent(Bone &boneObj_in);

	bool hasParent();
	
//	void transformBegin();
//	void transformEnd();
//	void transformReverseBegin();
//	void transformReverseEnd();	

//	ObjectController &controller();
#if !defined(ARCH_PSP) && !defined(OPENGL_ES)	
	void debugDraw(bool firstBone=true);
	void debugDrawNode();
#endif
};

class IMPEXP BoneSet
{
public:
	std::vector<Bone *> bones;
	std::map<const char *, cvrIndex> bone_map;
	
	cvrIndex bind(Bone *newBone, char *boneName=NULL)
	{
		bones.push_back(newBone);
		if (boneName != NULL) bone_map[boneName] = bones.size()-1;

		return bones.size()-1;
	}
	
	Bone *bone(cvrIndex boneNum) { return bones[boneNum]; }
	Bone *bone(const string &boneName) { if (bone_map.find(boneName.c_str()) == bone_map.end()) return NULL; return bones[bone_map[boneName.c_str()]]; }
};

