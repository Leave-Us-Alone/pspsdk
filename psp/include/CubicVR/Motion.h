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

#ifndef CUBICVR_MOTION_H
#define CUBICVR_MOTION_H


#include <CubicVR/cvr_defines.h>
#include <CubicVR/Envelope.h>
#include <CubicVR/Resource.h>

#include <vector>
#include <map>



#define MOTION_X	0
#define MOTION_Y	1
#define MOTION_Z	2


#define CONTROLLER_POSITION 0
#define CONTROLLER_ROTATION	1
#define CONTROLLER_SCALE	2


class IMPEXP Controllable
{
private:
public:
	virtual ~Controllable() {};	
	virtual void control(int controllerId, int motionId, float value) = 0;
	virtual float read_control(int controllerId, int motionId) { return 0; };
};

struct ltu_int
{
  bool operator()(int i1, int i2) const
  {
    return i1 < i2;
  }
};


struct ltu_cptr
{
  bool operator()(Controllable *c1, Controllable *c2) const
  {
    return (unsigned long)c1 < (unsigned long)c2;
  }
};


class IMPEXP MotionController
{
private:
	std::map<int, std::map<int, Envelope, ltu_int>, ltu_int> controllers;	
	
public:
	MotionController();
	
	Envelope &envelope(int controllerId, int motionId);
	
	void apply(Controllable &objControllable, float index);
	void record(Controllable &objControllable, float index);
};


class IMPEXP Motion : public Resource
{
private:
	std::map<Controllable *, MotionController, ltu_cptr> controllers;
public:
	Motion();
	
	void bind(Controllable &objControllable);

	EnvelopeKey *setKey(Controllable &objControllable, int controllerId, int motionId, float index, float value);
	void setBehavior(Controllable &objControllable, int controllerId, int motionId, int behavior_in, int behavior_out);
	MotionController *getController(Controllable *c)
	{
		if (controllers.find(c) != controllers.end())
		{
			return &controllers[c];
		}
		
		return NULL;
	}
	
	
	void evaluate(float index);	
	void record(float index);
};


#endif

