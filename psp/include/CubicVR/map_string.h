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

#ifndef CUBICVR_MAPSTRING
#define CUBICVR_MAPSTRING

#include <string>
#include <functional> 

/* map comparison function */
struct string_less : public std::binary_function<std::string,std::string,bool> 
{
 bool operator()(const std::string& a,const std::string& b) const
 {
  return a.compare(b) < 0;
 }
};

/* int comparison function */
struct int_less : public std::binary_function<int,int,bool> 
{
 bool operator()(int a,int b) const
 {
 	return a < b;
 }
};


class MapString
{
public:
	virtual const char *getString(const char *str_ref) = 0;
};

#endif

