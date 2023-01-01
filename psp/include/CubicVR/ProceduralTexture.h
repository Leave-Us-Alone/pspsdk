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

#include <CubicVR/GLExt.h>
#include <CubicVR/RGBA.h>
#include <CubicVR/Texture.h>
#include <vector>

typedef enum ProceduralTextureBlendMode
{
	BLEND_NORMAL,
	BLEND_ADD,
	BLEND_SUBTRACT,
	//	MULTIPLY,
	//	SCREEN,
	//	LIGHT
};

typedef enum ProceduralTextureFormat
{
	FORMAT_RGB,
	FORMAT_RGBA,
	FORMAT_SPAT
};

class ProceduralTexture: public Texture
{
private:
protected:
	std::vector<unsigned char> image;
	ProceduralTextureFormat format;
	
	// noise functions adapted from http://www.dreamincode.net/forums/showtopic66480.htm
	double findnoise2(double x,double y);
	double interpolate1(double a,double b,double x);
	double noise2(double x,double y);
	
public:	
	ProceduralTexture(ProceduralTextureFormat fmt=FORMAT_RGBA);
	~ProceduralTexture();
	
	void init(int w_in,int h_in);		
	void generateBuffer();		
	void clear(const RGB &color=RGB(0,0,0));		
	void blur(bool tile_mode=false);
	unsigned short getBPP();
	unsigned int multiSample(int x,int y, unsigned short bpp, unsigned short channel,bool tile_mode);

	
	void brush(unsigned int size, unsigned int inner, int xpos, int ypos, const RGBA &color, ProceduralTextureBlendMode blend_mode=BLEND_NORMAL, bool tile_mode=false);		
	void imageTest(float t=0.0);		
	void commit();		
	
	void clouds(double zoom, double p, int r, int g, int b);
	
	bool loadPNG(char *png_map);
	bool savePNG(char *png_map);
};
