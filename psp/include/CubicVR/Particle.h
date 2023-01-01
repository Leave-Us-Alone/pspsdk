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

#ifndef CUBICVR_PARTICLE
#define CUBICVR_PARTICLE

#include <CubicVR/cvr_defines.h>

#include <CubicVR/XYZ.h>
#include <CubicVR/RGBA.h>
#include <btBulletDynamicsCommon.h>

class IMPEXP Particle
{
	public:
		XYZ position, velocity, accel;
		RGBA color,src_color,colorDelta;
		float sizeDelta;
		
		float size,birth,lifespan;
		
		int sequence_id;
		btRigidBody *mRigidBody;

		
		Particle() : birth(0), lifespan(0), mRigidBody(NULL)
		{
			position = XYZ(0,0,0);
			velocity = XYZ(0,0,0);
			accel = XYZ(0,0,0);
			color = RGBA(1,1,1,1);
			colorDelta = RGBA(0,0,0,0);
			size = 1;
		};
		
		Particle &operator=(const Particle &eq_point)
		{
			position = eq_point.position;
			velocity = eq_point.velocity;
			accel = eq_point.accel;
			color = eq_point.color;
			size = eq_point.size;
			birth = eq_point.birth;
			lifespan = eq_point.lifespan;
			sequence_id = eq_point.sequence_id;
			mRigidBody = eq_point.mRigidBody;
			
			return *this;
		};

		
};


#endif