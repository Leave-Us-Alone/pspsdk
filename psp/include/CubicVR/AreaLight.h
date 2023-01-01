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


#pragma once
#include <CubicVR/Light.h>

class Camera;

class AreaLight: public Light
{
public:
	Light oLight[3];
	Camera *cam;
	XYZ shadow_vec;
	
	unsigned int near_res, far_res, near_range, far_range;
	float ceiling, floor;
	
	
	
	AreaLight(Camera *cam_in, unsigned int near_map_res, unsigned int far_map_res, float near_map_range, float far_map_range, float ceiling_height, float floor_height);	
	void update();
	void setShadowVector(XYZ vec);
	
};
