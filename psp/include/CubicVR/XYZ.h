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

#ifndef CUBICVR_XYZ_H
#define CUBICVR_XYZ_H


#include <CubicVR/GLExt.h>
#include <CubicVR/cvr_defines.h>
#include <btBulletDynamicsCommon.h>
//#include <CubicVR/math/VECTOR3D.h>

#ifdef ARCH_PSP
#include <fastmath.h>
#else
#include <math.h>
#endif




class IMPEXP XYZ
{
public:

	cvrFloat x,y,z;
	
	
	XYZ() : x(0), y(0), z(0)
	{	
	};
	
	
	XYZ(cvrFloat in_x, cvrFloat in_y, cvrFloat in_z)
	{
		x =	in_x;
		y = in_y;
		z = in_z;
	};
	
	XYZ(const btVector3 &xyz_in)
	{
		x =	xyz_in.getX();
		y = xyz_in.getY();
		z = xyz_in.getZ();
	}
	
//	XYZ(const VECTOR3D &v_in)
//	{
//		x = v_in.x;
//		y = v_in.y;
//		z = v_in.z;
//	}
	
	~XYZ()
	{
		// nil
	};
	
	
	inline cvrFloat distanceTo(XYZ &pt)
	{
		cvrFloat dx, dy, dz;
		
		dx = pt.x - x;
		dy = pt.y - y;
		dz = pt.z - z;
		
		return sqrt( dx*dx + dy*dy + dz*dz );
	};
	
	
	inline bool onSegment(XYZ &pt1, XYZ &pt2)
	{
		return (
				((x >= pt1.x && x <= pt2.x) || (x >= pt2.x && x <= pt1.x)) &&
				((y >= pt1.y && y <= pt2.y) || (y >= pt2.y && y <= pt1.y)) &&
				((z >= pt1.z && z <= pt2.z) || (z >= pt2.z && z <= pt1.z))
				);
	};
	
	
	
	inline const btVector3 cast()
	{
		return btVector3(x,y,z);
	};
	
	inline XYZ &operator=(const XYZ &pt)
	{
		x = pt.x;
		y = pt.y;
		z = pt.z;
		
		return *this;
	};
	
	inline XYZ &operator=(const btVector3 &pt)
	{
		x = pt.getX();
		y = pt.getY();
		z = pt.getZ();
		
		return *this;
	};
	
	
	inline XYZ &operator+=(const XYZ &pt)
	{
		x += pt.x;
		y += pt.y;
		z += pt.z;
		
		return *this;
	};
	
	
	inline XYZ &operator-=(const XYZ &pt)
	{
		x -= pt.x;
		y -= pt.y;
		z -= pt.z;
		
		return *this;
	};
	
	
	inline XYZ operator-(const XYZ &pt)
	{
		XYZ diff(*this);
		
		diff -= pt;
		
		return diff;
	};
	
	
	inline XYZ operator+(const XYZ &pt)
	{
		XYZ sum(*this);
		
		sum += pt;
		
		return sum;
	};
	
	
	inline XYZ operator-(const double val)
	{
		XYZ sum(*this);
		
		sum -= val;
		
		return sum;
	};
	
	inline XYZ operator+(const double val)
	{
		XYZ sum(*this);
		
		sum += val;
		
		return sum;
	};
	
	
	inline XYZ operator*(const float val)
	{
		XYZ mul(*this);
		
		mul *= val;
		
		return mul;
	};
	
	
	inline XYZ &operator+=(const double val)
	{
		x += (cvrFloat)val;
		y += (cvrFloat)val;
		z += (cvrFloat)val;
		
		return *this;
	};
	
	inline XYZ &operator+=(const float val)
	{
		x += val;
		y += val;
		z += val;
		
		return *this;
	};
	
	inline XYZ &operator+=(const long val)
	{
		x += val;
		y += val;
		z += val;
		
		return *this;
	};
	
	inline XYZ &operator+=(const int val)
	{
		x += val;
		y += val;
		z += val;
		
		return *this;
	};
	
	
	
	inline XYZ &operator-=(const double val)
	{
		x -= (cvrFloat)val;
		y -= (cvrFloat)val;
		z -= (cvrFloat)val;
		
		return *this;
	};
	
	
	inline XYZ &operator*=(const float val)
	{
		x *= val;
		y *= val;
		z *= val;
		
		return *this;
	};
	
	inline XYZ &operator-=(const float val)
	{
		x -= val;
		y -= val;
		z -= val;
		
		return *this;
	};
	
	inline XYZ &operator-=(const long val)
	{
		x -= val;
		y -= val;
		z -= val;
		
		return *this;
	};
	
	inline XYZ &operator-=(const int val)
	{
		x -= val;
		y -= val;
		z -= val;
		
		return *this;
	};
};

#ifndef _WIN32
IMPEXP inline bool operator==(const XYZ &pt1, const XYZ &pt2);
IMPEXP inline bool operator!=(const XYZ &pt1, const XYZ &pt2);
#endif

//void IMPEXP matTransform(float *mat, XYZ &v_in, XYZ &v_out);

inline bool operator==(const XYZ &pt1, const XYZ &pt2)
{
	return pt1.x == pt2.x && pt1.y == pt2.y && pt1.z == pt2.z;
};

inline bool operator!=(const XYZ &pt1, const XYZ &pt2)
{
	return !(pt1.x == pt2.x && pt1.y == pt2.y && pt1.z == pt2.z);
};

inline void matTransform(float *mat, XYZ &v_in, XYZ &v_out)
{
	v_out.x = 
	mat[0]*v_in.x+ 
	mat[4]*v_in.y+ 
	mat[8]*v_in.z+
	mat[12]*1.0f;
	
	v_out.y = 
	mat[1]*v_in.x+
	mat[5]*v_in.y+
	mat[9]*v_in.z+
	mat[13]*1.0f;
	
	v_out.z = 
	mat[2]*v_in.x+
	mat[6]*v_in.y+
	mat[10]*v_in.z+
	mat[14]*1.0f;
}

#endif

