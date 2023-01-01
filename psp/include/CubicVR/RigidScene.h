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

#ifndef CUBICVR_RIGIDSCENE_H
#define CUBICVR_RIGIDSCENE_H

#include <CubicVR/Scene.h>
#include <CubicVR/SceneObjects/RigidSceneObject.h>

#ifndef ARCH_PSP
#include <CubicVR/RigidSceneDebug.h>
#endif

class RigidScene : public Scene
{
protected:
//	std::vector<RigidSceneObject *> rigid_objects;
	std::set<RigidSceneObject *> rigid_sceneobjs_bound;

	std::map<std::string, RigidSceneObject *, string_less> rigid_sceneobjs_bound_ref;
	
	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	
	btVector3 worldAabbMin;
	btVector3 worldAabbMax;
	
	btAxisSweep3* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	
	int	maxProxies;
	bool constraints_setup;
	
//	bool debugMode;
	bool collisionEvents;

#if !defined(ARCH_PSP) && !defined(OPENGL_ES)
	RigidSceneDebug *debugDrawer;
#endif

	bool rigidUpdate;

public:
	std::map<btRigidBody *, RigidSceneObject *> contactMap;

	RigidScene(int scr_width_in = 512, int scr_height_in = 512,  XYZ aabbMin = XYZ(-10000,-10000,-10000), XYZ aabbMax = XYZ(10000,10000,10000));
	
	void solidifyScene();
	
	void bind(RigidSceneObject &rigid_sceneObj_in);
	using Scene::bind;
	void unbind(RigidSceneObject &rigid_sceneObj_in);
	using Scene::unbind;
	
	RigidSceneObject &rigidSceneObject(const std::string name_in);
	
	void stepSimulation( btScalar timeStep,int maxSubSteps=1, btScalar fixedTimeStep=btScalar(1.0)/btScalar(60.0));
	void setupConstraints();
	
	btDiscreteDynamicsWorld *getDynamicsWorld();
	
	virtual void firstInit();
	virtual void process();
	virtual void render();
//	void debug(bool debug_mode);
//	bool debug();
	
	inline void setRigidUpdate(bool rigidUpdateFlag) { rigidUpdate = rigidUpdateFlag; };
	void setGravity(const XYZ &grav_in);

	inline std::set<RigidSceneObject *> &rigidobjs() { return rigid_sceneobjs_bound; };
};

#endif