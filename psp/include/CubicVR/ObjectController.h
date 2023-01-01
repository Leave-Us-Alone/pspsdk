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

#ifndef CUBICVR_OBJECTCONTROLLER_H
#define CUBICVR_OBJECTCONTROLLER_H

#include <CubicVR/cvr_defines.h>

#include <CubicVR/GLExt.h>

#include <CubicVR/XYZ.h>
#include <CubicVR/Object.h>
//#include <CubicVR/Shader.h>
//#include <CubicVR/Envelope.h>

#ifdef ARCH_PSP
#include <fastmath.h>
#else
#include <math.h>
#endif

/// ObjectController -- 
class IMPEXP ObjectController
{
protected:
	XYZ scale, rotation, position, pivot, target;
//	XYZ center;	

	
	// Transform states
	bool l_init, w_init, matrix_lock, t_moved, t_bounds;
	bool is_targeted;
	
	// Parent Controller
	ObjectController *p_trans;
	
	inline void clearBounds() {	t_bounds = true; if (p_trans) p_trans->clearBounds(); }	
	
public:	
	// World and Local transform matrix
	float w_trans[16], l_trans[16];
	
	
	ObjectController();
	~ObjectController();

	void targeted(bool targeted_in);
	
	void transformBegin(bool no_pivot=false, bool no_scale=false, bool update_only=false);
	void transformEnd();		
	void transformReverseBegin();
	void transformReverseEnd();		
	
	void setMatrix(float t_trans_in[16]);
	void setMatrixLock(bool matrix_lock_state=true);

	inline XYZ &getPosition() { return position; };
	inline XYZ &getRotation() { return rotation; };
	inline XYZ &getScale() { return scale; };
	inline XYZ &getPivot() { return pivot; };
	inline XYZ &getTarget() { return target; };
	
	inline void setPosition(const XYZ &pos_in) { t_bounds = true; l_init = false; position = pos_in; };
	inline void setRotation(const XYZ &rot_in) { t_bounds = true; l_init = false; rotation = rot_in; };
	inline void setScale(const XYZ &scale_in) { t_bounds = true; l_init = false; scale = scale_in; };
	inline void setPivot(const XYZ &pivot_in) { t_bounds = true; l_init = false; pivot = pivot_in; };
	inline void setTarget(const XYZ target_in) { t_bounds = true; l_init = false; target = target_in; };	
	inline void clearTarget();
	
	inline void clearTransform() { l_init = w_init = false; clearBounds(); };
	inline void clearWorldTransform() { w_init = false; clearBounds(); };

	inline bool moved() { return t_moved; }
	inline void movedForce() { t_moved = true; }
	inline void movedReset() { t_moved = false; }
	
	void getAxis(XYZ &right, XYZ &up, XYZ &forward);
	void getWorldAxis(XYZ &right, XYZ &up, XYZ &forward);
	XYZ getWorldRotation();
	XYZ getWorldPosition();	
//	XYZ getWorldScale();
};



#endif
