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

#ifndef CUBICVR_PARTICLEEMITTER
#define CUBICVR_PARTICLEEMITTER


#include <CubicVR/cvr_defines.h>


#include <CubicVR/XYZ.h>
#include <CubicVR/RGB.h>
#include <CubicVR/Particle.h>
#include <CubicVR/ObjectController.h>


#include <stdlib.h>


class ParticleEmitter : public ObjectController
{
protected:
	
public:
	float particle_velocity;

	ParticleEmitter():ObjectController(),particle_velocity(10)
	{
	
	}

	virtual void emit(Particle &newParticle, float timeIndex, float lifeSpan=8.0) = 0;
	virtual void govern(Particle &p_in, Particle &p_out, float timeIndex) = 0;
	virtual void bury(Particle &dead_particle) = 0;
};


class PointParticleEmitter : public ParticleEmitter
{
protected:
	
public:
	float particle_velocity;
	float grav;

	PointParticleEmitter();
	void emit(Particle &newParticle, float timeIndex, float lifeSpan=8.0);	
	
	void govern(Particle &p_in, Particle &p_out, float timeIndex);
	void bury(Particle &dead_particle);
};



/*
		// spray emitter

		double randx = (double)rand()/(double)RAND_MAX;
		double randz = (double)rand()/(double)RAND_MAX;
		double randspeed = (double)rand()/(double)RAND_MAX;

		double clr = ((double)rand()/(double)RAND_MAX);
		
		newParticle.color.r = 0; //((double)rand()/(double)RAND_MAX);
		newParticle.color.g = clr*0.58; //((double)rand()/(double)RAND_MAX);
		newParticle.color.b = clr*1.0;
		
		newParticle.velocity.x = 40.0 * (randx - 0.5);
		newParticle.velocity.z = 40.0 * (randz - 0.5);

		newParticle.velocity.y = 10 + 60.0 * randspeed;

		newParticle.accel.y = -9.8;
		newParticle.lifespan=10;
//		newParticle.size = 0.2+6.0*((double)rand()/(double)RAND_MAX);



*/


#endif