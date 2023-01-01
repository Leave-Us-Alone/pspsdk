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

#ifndef CUBICVR_SHADER
#define CUBICVR_SHADER

#include <CubicVR/cvr_defines.h>

#include <CubicVR/GLExt.h>

#include <CubicVR/Light.h>
#include <CubicVR/AreaLight.h>

#include <CubicVR/Object.h>

#define SHADER_STAGE_NULL	0
#define SHADER_STAGE_OPAQUE	1
#define SHADER_STAGE_TRANSPARENT 2
#define SHADER_STAGE_NOMATERIAL 3
#define SHADER_STAGE_NOTEXTURE 4
#define SHADER_STAGE_SHADOW 5

class IMPEXP Shader
{
	public:
		std::set<Light *> *lights;
		float *shadowModelMatrix;
		float shadow_alpha;
		XYZ lod_src;
		bool lod;
		
		Shader();
		virtual ~Shader() {};
		virtual void render(Object &obj, int stage = SHADER_STAGE_NULL) = 0;

//		void bind(Light &lightObj);
		inline void bind(std::set<Light *> *lights_in) { lights = lights_in; };
		inline void setLODSource(const XYZ &lod_src_in) { lod_src = lod_src_in; };
		inline void clearLOD() { lod = false; };
		void shadowAlpha(float shadow_alpha_in);
		float shadowAlpha();
};


#ifdef ARCH_PSP

#include <pspdebug.h>
#define printf pspDebugScreenPrintf 

//class IMPEXP PSPShader : public Shader	/* todo: commenting */
//{
//	public:
//		void render(Object &obj, int stage = SHADER_STAGE_NULL);
//};
//
#endif
//#else

#if !defined(OPENGL_ES) && !defined(ARCH_PSP)

class IMPEXP LineShader : public Shader
{
	public:
		void render(Object &obj, int stage = SHADER_STAGE_NULL);
};

class IMPEXP VertexColorShader : public Shader
{
	public:
		void render(Object &obj, int stage = SHADER_STAGE_NULL);
};

class IMPEXP ShadowShader : public Shader
{
public:
	void render(Object &obj, int stage = SHADER_STAGE_NULL);
};

class IMPEXP RegularShader : public Shader
{
public:
	void render(Object &obj, int stage = SHADER_STAGE_NULL);
};

#endif

class IMPEXP CacheShader : public Shader	/* todo: commenting */
{
	public:
	
#ifndef ARCH_PSP
		static Object *lockObj;	// if we draw the same object more than once consecutively this will avoid some context switching
		static void setup(Object &obj, bool init_texcoord);
#endif

		void render(Object &obj, int stage = SHADER_STAGE_NULL);
};

//#endif



class IMPEXP ObjectShader : public Shader	// determines whehter the object is cached or not
{
	private:
//#ifdef ARCH_PSP
//		PSPShader pspShader;
//#else
		CacheShader cShader;
#if !defined(OPENGL_ES) && !defined(ARCH_PSP)
		RegularShader rShader;
#endif
//#endif
	
	
	public:
		void bind(std::set<Light *> *lights_in);
		void render(Object &obj, int stage = SHADER_STAGE_NULL);
};



#endif
