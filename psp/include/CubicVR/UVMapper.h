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

#ifndef CUBICVR_UVMAPPER
#define CUBICVR_UVMAPPER

#include <CubicVR/cvr_defines.h>

#include <CubicVR/XYZ.h>
#include <CubicVR/Vector.h>
#include <CubicVR/Object.h>


/* Projection enums */
#define UV_PROJECTION_UV 0
#define UV_PROJECTION_PLANAR	1
#define UV_PROJECTION_CYLINDRICAL	2
#define UV_PROJECTION_SPHERICAL	3
#define UV_PROJECTION_CUBIC	4

/* Axis enums */
#define UV_AXIS_X 0
#define UV_AXIS_Y 1
#define UV_AXIS_Z 2


class IMPEXP UVMapper
{
private:
	/* UVMapper tools */
	void rotatexyz(XYZ &rot_in, XYZ &point_in, XYZ &point_out);
	void xyz_to_h(float x,float y,float z,float *h);
	void xyz_to_hp(float x,float y,float z,float *h,float *p);
	float fract (float x);

public:
	/* UV rotation, scale and center */
	XYZ rotation;
	XYZ scale;
	XYZ center;
	
	/* Projection mode and Projection axis */
	unsigned short projection_mode;
	unsigned short projection_axis;
	
	/* wrap count, number of times WxH to wrap the texture */
	float wrap_w_count, wrap_h_count;
		
	UVMapper();
	~UVMapper();
	
	/// Apply this UVMapper to object obj on material materialRef to texture layer layerRef
	void apply(Object &obj, Material *materialRef, unsigned short layerRef);
	/// Apply this UVMapper to object obj on material materialRef to texture layer 0
	void apply(Object &obj, Material *materialRef);
	
	/// Get a U & V value for a point (all except cubic which requires surface normals 
	void getUV(XYZ &point_in, UV &uv_out);
	
	/* these all work identically to lightwave's surface dialog */
	void setProjection(unsigned short proj_in);
	void setAxis(unsigned short axis_in);
	void setWrap(float w_in, float h_in);
	void setScale(const XYZ &scale_in);
	void setRotation(const XYZ &rotation_in);
	void setCenter(const XYZ &center_in);
};


#endif

