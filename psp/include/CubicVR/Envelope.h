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

#ifndef CUBICVR_ENVELOPE_H
#define CUBICVR_ENVELOPE_H

/*
	Portions adapted from the work of Ernie Wright from the lightwave SDK
*/

#include <CubicVR/cvr_defines.h>

#include <map>

#ifdef ARCH_PSP
#include <fastmath.h>
#else
#include <math.h>
#endif

/* map comparison function */
struct float_less
{
  bool operator()(float s1, float s2) const
  {
    return s1 < s2;
  }
};


#define MOTION_POSITION_X 0
#define MOTION_POSITION_Y 1
#define MOTION_POSITION_Z 2

#define MOTION_ROTATION_X 3
#define MOTION_ROTATION_Y 4
#define MOTION_ROTATION_Z 5

#define MOTION_SCALE_X 6
#define MOTION_SCALE_Y 7
#define MOTION_SCALE_Z 8


#define ENV_SHAPE_TCB   0
#define ENV_SHAPE_HERM  1
#define ENV_SHAPE_BEZI  2
#define ENV_SHAPE_LINE  3
#define ENV_SHAPE_STEP  4
#define ENV_SHAPE_BEZ2  5


#define ENV_BEH_RESET      0
#define ENV_BEH_CONSTANT   1
#define ENV_BEH_REPEAT     2
#define ENV_BEH_OSCILLATE  3
#define ENV_BEH_OFFSET     4
#define ENV_BEH_LINEAR     5


class IMPEXP EnvelopeKey
{
public:
	
	float value;
	float time;
	int shape;
	float tension;
	float continuity;
	float bias;
	float param[4];	
	
	EnvelopeKey *prev;
	EnvelopeKey *next;
	
	EnvelopeKey();
};


class IMPEXP Envelope
{
public:

	std::map<float, EnvelopeKey *, float_less> key_map;
	
	int nKeys;
	int in_behavior;
	int out_behavior;

	EnvelopeKey *keys;

	float evaluate(float time);
	
	Envelope();
	~Envelope();
	
	void behavior(int in_b, int out_b);	
	bool empty();
	
	EnvelopeKey *addKey(float time, float value);
	EnvelopeKey *addKey(float time);
	EnvelopeKey *firstKey()
	{
		EnvelopeKey *k = keys;
		if (k) while (k->prev) k = k->prev;
		return k;
	}
};


#endif

