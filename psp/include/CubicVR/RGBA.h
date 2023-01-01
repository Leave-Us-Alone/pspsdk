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

#ifndef CUBICVR_RGBA_H
#define CUBICVR_RGBA_H

#include <CubicVR/cvr_defines.h>

#include <CubicVR/RGB.h>

class IMPEXP RGBA : public RGB
{
public:
	float a;
	
	RGBA();
	RGBA(float r_in, float g_in, float b_in, float a_in);
	~RGBA();
	
	friend inline bool operator==(const RGBA &c1, const RGBA &c2)
	{
		return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
	};	
	
	friend inline bool operator!=(const RGBA &c1, const RGBA &c2)
	{
		return c1.r != c2.r || c1.g != c2.g || c1.b != c2.b || c1.a != c2.a;
	};	
	
	inline RGBA &operator=(const RGB &pt)
	{
		r = pt.r;
		g = pt.g;
		b = pt.b;
		
		return *this;
	};
	
	inline RGBA &operator+=(const RGB &pt)
	{
		r += pt.r;
		g += pt.g;
		b += pt.b;
		
		return *this;
	};
	
	
	inline RGBA &operator-=(const RGB &pt)
	{
		r -= pt.r;
		g -= pt.g;
		b -= pt.b;
		
		return *this;
	};
	
	
	inline RGBA &operator+=(const double val)
	{
		r += (cvrFloat)val;
		g += (cvrFloat)val;
		b += (cvrFloat)val;
		a += (cvrFloat)val;
		
		return *this;
	};
	
	inline RGBA &operator+=(const float val)
	{
		r += val;
		g += val;
		b += val;
		a += val;
		
		return *this;
	};
	
	inline RGBA &operator+=(const long val)
	{
		r += val;
		g += val;
		b += val;
		a += val;
		
		return *this;
	};
	
	inline RGBA &operator+=(const int val)
	{
		r += val;
		g += val;
		b += val;
		a += val;
		
		return *this;
	};
	
	
	
	inline RGBA &operator-=(const double val)
	{
		r -= (cvrFloat)val;
		g -= (cvrFloat)val;
		b -= (cvrFloat)val;
		a -= (cvrFloat)val;
		
		return *this;
	};
	
	
	inline RGBA &operator*=(const float val)
	{
		r *= val;
		g *= val;
		b *= val;
		a *= val;
		
		return *this;
	};
	
	inline RGBA &operator-=(const float val)
	{
		r -= val;
		g -= val;
		b -= val;
		a -= val;
		
		return *this;
	};
	
	inline RGBA &operator-=(const long val)
	{
		r -= val;
		g -= val;
		b -= val;
		a -= val;
		
		return *this;
	};
	
	inline RGBA &operator-=(const int val)
	{
		r -= val;
		g -= val;
		b -= val;
		a -= val;
		
		return *this;
	};
	
	
	////
	
	inline RGBA &operator=(const RGBA &pt)
	{
		r = pt.r;
		g = pt.g;
		b = pt.b;
		a = pt.a;
		
		return *this;
	};
	
	inline RGBA &operator+=(const RGBA &pt)
	{
		r += pt.r;
		g += pt.g;
		b += pt.b;
		a += pt.a;
		
		return *this;
	};
	
	
	inline RGBA &operator-=(const RGBA &pt)
	{
		r -= pt.r;
		g -= pt.g;
		b -= pt.b;
		a += pt.a;
		
		return *this;
	};
	
	
	inline RGBA operator-(const RGBA &pt)
	{
		RGBA diff(*this);
		
		diff -= pt;
		
		return diff;
	};
	
	
	inline RGBA operator+(const RGBA &pt)
	{
		RGBA sum(*this);
		
		sum += pt;
		
		return sum;
	};
	
	
	inline RGBA operator-(const double val)
	{
		RGBA sum(*this);
		
		sum -= val;
		
		return sum;
	};
	
	inline RGBA operator+(const double val)
	{
		RGBA sum(*this);
		
		sum += val;
		
		return sum;
	};
	
	
	inline RGBA operator*(const float val)
	{
		RGBA mul(*this);
		
		mul *= val;
		
		return mul;
	};
	
	
};


#endif

