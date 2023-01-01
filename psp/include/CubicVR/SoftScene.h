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

#ifndef CUBICVR_SOFTSCENE_H
#define CUBICVR_SOFTSCENE_H

#include <CubicVR/RigidScene.h>
#include <CubicVR/SceneObjects/SoftSceneObject.h>
#include <BulletSoftBody/btSoftBody.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>

#ifndef ARCH_PSP
#include <CubicVR/RigidSceneDebug.h>
#endif

class SoftScene : public RigidScene
{
protected:
	std::set<SoftSceneObject *> soft_sceneobjs_bound;
	
	std::map<std::string, SoftSceneObject *, string_less> soft_sceneobjs_bound_ref;

#ifdef ARCH_PSP
	btSoftBody::btSoftBodyWorldInfo	softBodyWorldInfo;
#else
	btSoftBodyWorldInfo	softBodyWorldInfo;
#endif
	btSoftRigidDynamicsWorld *softDynamicsWorld;
public:

	SoftScene(int scr_width_in = 512, int scr_height_in = 512);
	
	void bind(SoftSceneObject &rigid_sceneObj_in);
	using Scene::bind;

	SoftSceneObject &softSceneObject(const std::string name_in);
		
	void stepSimulation(btScalar timeStep, int maxSubSteps=1, btScalar fixedTimeStep=btScalar(1.0)/btScalar(60.0));
	virtual void firstInit();
	virtual void process();

	virtual void render();
	btSoftRigidDynamicsWorld *getSoftDynamicsWorld();

	inline std::set<SoftSceneObject *> &softobjs() { return soft_sceneobjs_bound; };
	void setGravity(const XYZ &grav_in);
	
};

#endif