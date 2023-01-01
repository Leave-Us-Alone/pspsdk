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

#ifndef CUBICVR_RIGIDPARTICLEEMITTER
#define CUBICVR_RIGIDPARTICLEEMITTER


#include <CubicVR/cvr_defines.h>


#include <CubicVR/XYZ.h>
#include <CubicVR/RGB.h>
#include <CubicVR/Particle.h>
#include <CubicVR/ParticleEmitter.h>
#include <CubicVR/ObjectController.h>
#include <btBulletDynamicsCommon.h>


#include <stdlib.h>


class IMPEXP RigidParticleEmitter : public IMPEXP ParticleEmitter
{
protected:
	btDiscreteDynamicsWorld* dynamicsWorld;
	map<float,btCollisionShape*,ltufloat> particleShapes;
	
public:
	float particle_velocity;

	RigidParticleEmitter(btDiscreteDynamicsWorld &dynamicsWorld_in):ParticleEmitter()
	{
		dynamicsWorld = &dynamicsWorld_in;
	}

	virtual void emit(Particle &newParticle, float timeIndex, float lifeSpan=8.0)
	{
		float mass = 0.01;
		
		btCollisionShape *particleShape;
		
		newParticle.birth = timeIndex;
		newParticle.lifespan = lifeSpan;
//		newParticle.size = 1.0;
		
		if (particleShapes.find(newParticle.size) == particleShapes.end())
		{
			particleShapes[newParticle.size] = particleShape = new btSphereShape(newParticle.size/2.0);
		}
		else
		{
			particleShape = particleShapes[newParticle.size];
		}

		btTransform startTransform;

		btVector3 localInertia(0,0,0);

		particleShape->calculateLocalInertia(mass,localInertia);

		startTransform.setIdentity();

		newParticle.position = position+newParticle.position;
		
		startTransform.setOrigin(btVector3(newParticle.position.x, newParticle.position.y, newParticle.position.z));			
		
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo cInfo(mass,myMotionState,particleShapes[newParticle.size],localInertia);

		newParticle.mRigidBody = new btRigidBody(cInfo);
		
		newParticle.mRigidBody->setAngularFactor(0);

		newParticle.mRigidBody->setFriction(0);

		dynamicsWorld->addRigidBody(newParticle.mRigidBody);

		newParticle.mRigidBody->activate(true);
	
		if (rotation.x||rotation.y||rotation.z)
		{
			btVector3 force(rotation.x,rotation.y,rotation.z);

//			printf("%.3f -- %.3f,%.3f,%.3f\n", particle_velocity, force.getX(), force.getY(), force.getZ());			
			
			force *= particle_velocity;
	
			newParticle.mRigidBody->applyImpulse(force, btVector3(0,0,0));
			
		}

		
	};
	
	
	virtual void govern(Particle &p_in, Particle &p_out, float timeIndex)
	{	
		btTransform objTrans;

		btDefaultMotionState* myMotionState = (btDefaultMotionState*)p_in.mRigidBody->getMotionState();

		myMotionState->getWorldTransform(objTrans);

		p_out.position = XYZ(objTrans.getOrigin().getX(),objTrans.getOrigin().getY(),objTrans.getOrigin().getZ());
	};
	
	virtual void bury(Particle &dead_particle)
	{
		dynamicsWorld->removeRigidBody(dead_particle.mRigidBody);
	}

};

/*


	

class RigidSphere : public RigidSceneObject
{
	static std::map<float, btCollisionShape*, ltufloat> sphereShapes;

	
public:
	RigidSphere() : RigidSceneObject()
	{
	
	}

	virtual void initialize(btDiscreteDynamicsWorld &dynamicsWorld_in)
	{
		XYZ scale = controller().scale;
		
		if (sphereShapes[scale.x])
		{
			colShape = sphereShapes[scale.x];
		}
		else
		{
			colShape = new btSphereShape(scale.x/2.0);
			sphereShapes[scale.x] = colShape;
		}
		
		RigidSceneObject::initialize(dynamicsWorld_in);		
	}
};

*/


#endif