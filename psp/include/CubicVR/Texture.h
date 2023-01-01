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

#ifndef CUBICVR_TEXTURE_H
#define CUBICVR_TEXTURE_H

#include <CubicVR/cvr_defines.h>

#include <CubicVR/GLExt.h>
#include <CubicVR/map_string.h>
#include <CubicVR/Resource.h>

//#ifndef ARCH_PSP
//#include <CubicVR/textureTGA.h>
//#endif

#if !defined(OPENGL_ES) && !defined(ARCH_DC) && !defined(ARCH_PSP)
#include <CubicVR/ph/ph.h>
#endif


#ifndef ARCH_PSP
#include <CubicVR/IMAGE.h>
#endif

#define FORMAT_TGA 0
#define FORMAT_PNG 1

#define TEXTURE_DIFF 1	// color
#define TEXTURE_SPEC 2	// specular strength
#define TEXTURE_NORM 3	// normal
#define TEXTURE_LUMI 4	// luminosity
#define TEXTURE_ALPHA 5	// alpha transparency
#define TEXTURE_REFL 6	// reflection strength
#define TEXTURE_ENVSPHERE 7	// environment (spherical)
#define TEXTURE_LIGHTMAP 8
#define TEXTURE_BUMP 9	// parallax bump (height map)

#include <vector>
#include <map>
#include <string>
#include <iostream>

#ifdef ARCH_PSP
#include <CubicVR/psp/TGALoader.h>
#include <pspdebug.h>
#define printf pspDebugScreenPrintf 
#endif


class IMPEXP TextureInit	/* Texture pointer garbage cleanup */
{
	public:
		TextureInit();
		~TextureInit();  /* gets called before program exit due to static instance in Texture class */
};


class IMPEXP Texture : public Resource
{
friend class TextureInit;

private:
	static TextureInit initializer;
#ifdef ARCH_PSP
	CTGATexture psp_texture;
#endif
	
	
public:
#ifndef ARCH_PSP
	IMAGE img;
#endif
#if !defined(ARCH_PSP) && !defined(ARCH_DC) && !defined(OPENGL_ES)
	PHsurfaceRec renderSurface;
	bool render_srf;
#endif
	unsigned int format;
	bool alpha;
	
	/* static members */
	static std::vector<Texture *> textures;
	static std::map<std::string, cvrIndex, string_less> nameref;

	static cvrIndex create();
	static cvrIndex create(std::string file_name);
	static cvrIndex create(std::string file_name, std::string tex_name);

	static cvrIndex getTextureId(std::string tex_name);
	static cvrIndex bindTexture(Texture *tex_in, std::string tex_name="");
	
	static void destroy(cvrIndex texNum);
	static void use(cvrIndex texNum);
	
	static void clear();

	static void lock();
	static void clearLocks();

	static int tex_use;
	static int tex_lock;
	
	static void setTexture(int textureid);
	static int nextTexture();
	
	static void clearAllTextures();
	

	/* non-static members */
#ifndef ARCH_PSP
	GLuint glTexId;
#endif	

	unsigned int width;
	unsigned int height;

	std::vector<unsigned char> image;
	
	Texture();
	Texture(bool global_init_in);
	~Texture();

	
	void generate();
	bool load(std::string strFn);
#ifndef ARCH_PSP
	bool loadMipmap(std::string strFn);
	void loadLightMap(GLubyte *data, int width, int height);
#endif
	void load(std::string strFn, int imgType);
	void use();
	
	
#if !defined(ARCH_PSP) && !defined(ARCH_DC) && !defined(OPENGL_ES)	
	bool createRenderTarget(unsigned int width, unsigned int height, GLboolean depth = false, int fp = 0, GLboolean linear = true, GLboolean stencil = false, int attachments=1);
	void destroyRenderTarget();
	void bindRenderTarget();
	void resetRenderTarget();
#endif
	
};



#endif