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

#ifndef CUBICVR_VECTOR
#define CUBICVR_VECTOR


#define PLANE_FLOAT_TOLERANCE 0.001

#include <CubicVR/cvr_defines.h>

#include <CubicVR/XYZ.h>


class IMPEXP Vector : public XYZ
{
public:

	Vector();
	Vector(cvrFloat x, cvrFloat y, cvrFloat z);
	Vector(XYZ &ptA, XYZ &ptB);
	Vector(XYZ &pt);
	~Vector();
	
	/// return the magnitude (length) of this vector
	inline cvrFloat magnitude() 
	{ 
		return sqrt(x*x + y*y + z*z); 
	};
	
	
	/// make this vector a unit length of 1
	inline void makeUnit()	
	{
		cvrFloat m;
		
		m = magnitude();
		
		if (m && (m != 1))
		{
			*this/=m;
		}
	};
	
	/// return the dot product between this vector and another
	inline cvrFloat dotProduct(Vector &v_in)
	{
		return x * v_in.x + y * v_in.y + z * v_in.z;
	};
	
	
	inline cvrFloat dotProduct(XYZ &v_in)
	{
		return x * v_in.x + y * v_in.y + z * v_in.z;
	};
	
	
	///	find the angle between two vectors on their common plane
	inline cvrFloat angle(Vector &v_in)
	{
#ifdef ARCH_DC
		float ang;
		sh4_dot_single3(x,y,z, v_in.x, v_in.y, v_in.z, ang);
		return fabs(acos(ang));
#else
		cvrFloat dp,denom;
		
		dp = dotProduct(v_in);	// A . B
		denom = magnitude()*v_in.magnitude();	// divided by |A| * |B|
		
		//printf("dp: %f, denom: %f\n",dp, denom);
#ifdef ARCH_PSP
		if (fabs(dp-denom)<0.000001) return M_PI/2.0f;
#endif
				
		return acos(dp/denom); // theta = (A . B) / (|A| * |B|)
#endif
	};
	
	
	/// find point outPt on line A->B closest to point pointTest	
	static inline XYZ getClosestTo(XYZ &lineA, XYZ &lineB, XYZ &pointTest)
	{
		/*
		 Use line XYZ A and XYZ B and test point XYZ C to find new closest point XYZ D
		 
		 Vector S = B-A
		 Vector T = C-A
		 
		 D = A + (S.T / S.S) * S
		 */

		Vector S, T, U;
		
		S = lineB-lineA;
		
		T = pointTest - lineA;
		
		U = S;
		U *= S.dotProduct(T) / S.dotProduct(S);
		U += lineA;
		
		return U;
	};
	
	
	/// form a plane from normal and point_on_plane and test segment start->end to find returned_intersect_point
	static inline bool linePlaneIntersect(XYZ &returned_intersect_point, Vector &normal, XYZ &point_on_plane, XYZ &segment_start, XYZ &segment_end)
	{
		cvrFloat denom,mu,d;
		Vector pa,pb,pc;
		
		d = - normal.x * point_on_plane.x - normal.y * point_on_plane.y - normal.z * point_on_plane.z;
		
		/* calculate position where the plane intersects the segment */
		denom = normal.x * (segment_end.x - segment_start.x) + normal.y * (segment_end.y - segment_start.y) + normal.z * (segment_end.z - segment_start.z);
		
		if (fabs(denom) < PLANE_FLOAT_TOLERANCE) return false; /* point on plane is outside of line, no intersection */
		
		mu = - (d + normal.x * segment_start.x + normal.y * segment_start.y + normal.z * segment_start.z) / denom;
		returned_intersect_point = XYZ(
									   (float)(segment_start.x + mu * (segment_end.x - segment_start.x)),
									   (float)(segment_start.y + mu * (segment_end.y - segment_start.y)),
									   (float)(segment_start.z + mu * (segment_end.z - segment_start.z))
									   );
		
		return true;
	}
	
	
	/// return the cross product of vector A and B
	static inline Vector crossProduct(const Vector &vectA, const Vector &vectB)
	{
		Vector cp;
		
		cp.x = vectA.y * vectB.z - vectB.y * vectA.z;
		cp.y = vectA.z * vectB.x - vectB.z * vectA.x;
		cp.z = vectA.x * vectB.y - vectB.x * vectA.y;
		
		return cp;
	};
	
	
	inline Vector &operator=(const Vector &vect)
	{
		x = vect.x;
		y = vect.y;
		z = vect.z;
		
		return *this;
	};
	
	
	inline Vector &operator+=(const Vector &vect)
	{
		x += vect.x;
		y += vect.y;
		z += vect.z;
		
		return *this;
	};
	
	
	inline Vector &operator-=(const Vector &vect)
	{
		x -= vect.x;
		y -= vect.y;
		z -= vect.z;
		
		return *this;
	};
	
	
	inline Vector &operator=(const XYZ &pt)
	{
		x = pt.x;
		y = pt.y;
		z = pt.z;
		
		return *this;
	};
	
	
	inline Vector &operator+=(const XYZ &pt)
	{
		x += pt.x;
		y += pt.y;
		z += pt.z;
		
		return *this;
	};
	
	
	inline Vector &operator-=(const XYZ &pt)
	{
		x -= pt.x;
		y -= pt.y;
		z -= pt.z;
		
		return *this;
	};
	
	
	inline Vector &operator/=(const cvrFloat div_val)
	{
		x /= div_val;
		y /= div_val;
		z /= div_val;
		
		return *this;
	};
	
	
	inline Vector &operator*=(const cvrFloat mp_val)
	{
		x *= mp_val;
		y *= mp_val;
		z *= mp_val;
		
		return *this;
	};
	
	// cross product
	inline Vector &operator*=(const Vector &vect)
	{
		*this = crossProduct(*this,vect);
		
		return *this;
	};
	
	
	inline Vector operator+(const Vector &vect)
	{
		Vector sum(*this);
		
		sum += vect;
		
		return sum;
	};
	
	
	inline Vector operator-(const Vector &vect)
	{
		Vector diff(*this);
		
		diff -= vect;
		
		return diff;
	};
	
	
	inline Vector operator+(const XYZ &pt)
	{
		Vector sum(*this);
		
		sum += pt;
		
		return sum;
	};
	
	
	inline Vector operator-(const XYZ &pt)
	{
		Vector diff(*this);
		
		diff -= pt;
		
		return diff;
	};
	
	
	inline Vector operator/(const cvrFloat div_val)
	{
		Vector divd(*this);
		
		divd /= div_val;
		
		return divd;
	};
	
	
	inline Vector operator*(const cvrFloat mp_val)
	{
		Vector mpd(*this);
		
		mpd *= mp_val;
		
		return mpd;
	};
	
	inline Vector operator*(const Vector &vt)
	{
		Vector cp(*this);
		
		cp *= vt;
		
		return cp;
	};
	
	
	
	friend bool operator==(const Vector &vect1, const Vector &vect2);
	friend bool operator!=(const Vector &vect1, const Vector &vect2);
};	

inline bool operator==(const Vector &vect1, const Vector &vect2)
{
	return vect1.x == vect2.x && vect1.y == vect2.y && vect1.z == vect2.z;
};


inline bool operator!=(const Vector &vect1, const Vector &vect2)
{
	return !(vect1 == vect2);
};


#endif

