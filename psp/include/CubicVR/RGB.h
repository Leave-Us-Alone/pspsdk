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

#ifndef CUBICVR_RGB_H
#define CUBICVR_RGB_H

#include <CubicVR/cvr_defines.h>
#include <CubicVR/GLExt.h>

#ifdef RGB
#undef RGB
#endif


class IMPEXP RGB
{
public:
	float r,g,b;
	
	RGB();
	RGB(float r_in, float g_in, float b_in);
	~RGB();
	
	friend inline bool operator==(const RGB &c1, const RGB &c2)
	{
		return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
	};	
	
	friend inline bool operator!=(const RGB &c1, const RGB &c2)
	{
		return c1.r != c2.r || c1.g != c2.g || c1.b != c2.b;
	};	
	
	inline RGB &operator=(const RGB &pt)
	{
		r = pt.r;
		g = pt.g;
		b = pt.b;
		
		return *this;
	};
	
	inline RGB &operator+=(const RGB &pt)
	{
		r += pt.r;
		g += pt.g;
		b += pt.b;
		
		return *this;
	};
	
	
	inline RGB &operator-=(const RGB &pt)
	{
		r -= pt.r;
		g -= pt.g;
		b -= pt.b;
		
		return *this;
	};
	
	
	inline RGB operator-(const RGB &pt)
	{
		RGB diff(*this);
		
		diff -= pt;
		
		return diff;
	};
	
	
	inline RGB operator+(const RGB &pt)
	{
		RGB sum(*this);
		
		sum += pt;
		
		return sum;
	};
	
	
	inline RGB operator-(const double val)
	{
		RGB sum(*this);
		
		sum -= val;
		
		return sum;
	};
	
	inline RGB operator+(const double val)
	{
		RGB sum(*this);
		
		sum += val;
		
		return sum;
	};
	
	
	inline RGB operator*(const float val)
	{
		RGB mul(*this);
		
		mul *= val;
		
		return mul;
	};
	
	
	inline RGB &operator+=(const double val)
	{
		r += (cvrFloat)val;
		g += (cvrFloat)val;
		b += (cvrFloat)val;
		
		return *this;
	};
	
	inline RGB &operator+=(const float val)
	{
		r += val;
		g += val;
		b += val;
		
		return *this;
	};
	
	inline RGB &operator+=(const long val)
	{
		r += val;
		g += val;
		b += val;
		
		return *this;
	};
	
	inline RGB &operator+=(const int val)
	{
		r += val;
		g += val;
		b += val;
		
		return *this;
	};
	
	
	
	inline RGB &operator-=(const double val)
	{
		r -= (cvrFloat)val;
		g -= (cvrFloat)val;
		b -= (cvrFloat)val;
		
		return *this;
	};
	
	
	inline RGB &operator*=(const float val)
	{
		r *= val;
		g *= val;
		b *= val;
		
		return *this;
	};
	
	inline RGB &operator-=(const float val)
	{
		r -= val;
		g -= val;
		b -= val;
		
		return *this;
	};
	
	inline RGB &operator-=(const long val)
	{
		r -= val;
		g -= val;
		b -= val;
		
		return *this;
	};
	
	inline RGB &operator-=(const int val)
	{
		r -= val;
		g -= val;
		b -= val;
		
		return *this;
	};
};


#endif

