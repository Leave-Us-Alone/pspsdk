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

#ifndef CUBICVR_PARTICLESYSTEM
#define CUBICVR_PARTICLESYSTEM


#include <CubicVR/cvr_defines.h>

#include <list>
#include <vector>

#include <CubicVR/GLExt.h>

#include <CubicVR/XYZ.h>
#include <CubicVR/Vector.h>
#include <CubicVR/RGB.h>
#include <CubicVR/Texture.h>
#include <CubicVR/Particle.h>
#include <CubicVR/ParticleEmitter.h>


class IMPEXP ParticleSystem
{
private:
	std::list<Particle *> particles;

	Vector right, up;
	
public:

	ParticleSystem();
	unsigned long numParticles();
	void addParticle(Particle &p_in);
	void viewSetup(float defaultSize=1.0f);
	void drawBegin();
	void drawEnd();
	void draw(ParticleEmitter &pe, float timeIndex);
	void drawParticle(Particle &p);

};


#endif