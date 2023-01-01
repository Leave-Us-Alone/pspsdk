#ifndef GLSHADER_H
#define GLSHADER_H

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

#include <CubicVR/cvr_defines.h>
#include <CubicVR/Light.h>

#include <map>
#include <string>

#include <CubicVR/map_string.h>


#ifdef OPENGL_ES
#include <OpenGLES/ES1/glext.h>
#endif

#ifdef WIN32
//#include <GL/glew.h>
//#include <GL/wglew.h>
//#include <GL/glut.h>
#include <gl/GL.h>
//#include <gl/GLAux.h>
#include <gl/GLU.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#endif

#ifdef ARCH_DC
//#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <CubicVR/Logger.h>

#define FailGLError(X) {int err = (int)glGetError(); \
	if (err != GL_NO_ERROR) \
		{Logger::log(LOG_ERROR,X); Logger::log(LOG_ERROR," error 0x%x\n",err); \
		return err;} }
#define FailWithMessage(X) { Logger::log(LOG_ERROR,X); Logger::log(LOG_ERROR,"\n"); return 1;}
#define FailOnErrWithMessage(X,message) { if (X!=0) {Logger::log(LOG_ERROR,message); Logger::log(LOG_ERROR,"\n"); return 1;}}

#define SHADER_VAL_INT 0
#define SHADER_VAL_XYZ 1
#define SHADER_VAL_4X4 2
#define SHADER_VAL_FLOAT 3
#define SHADER_VAL_ATTRIB 4

#define SHADER_VARIANT_COLOR		1
#define SHADER_VARIANT_ALPHA		2
#define SHADER_VARIANT_SPECULAR		4
#define SHADER_VARIANT_LUMINOSITY	8
#define SHADER_VARIANT_BUMP			16
#define SHADER_VARIANT_SHADOW0		32
#define SHADER_VARIANT_SHADOW1		64
#define SHADER_VARIANT_SHADOW2		128
#define SHADER_VARIANT_SHADOW3		256
#define SHADER_VARIANT_SHADOW4		512
#define SHADER_VARIANT_SHADOW5		1024
#define SHADER_VARIANT_SHADOW6		2048
#define SHADER_VARIANT_SHADOW7		4096
#define SHADER_VARIANT_ENVSPHEREMAP		8192
#define SHADER_VARIANT_REFLECTION		16384
#define SHADER_VARIANT_LIGHTMAP		32768
#define SHADER_VARIANT_PARALLAX		65536
//#define SHADER_VARIANT_		131070
//#define SHADER_VARIANT_		262140
//#define SHADER_VARIANT_		524280
//#define SHADER_VARIANT_		1048560
//#define SHADER_VARIANT_		2097120
//#define SHADER_VARIANT_		4194240
//#define SHADER_VARIANT_		8388480
//#define SHADER_VARIANT_		16776960
//#define SHADER_VARIANT_		33553920
//#define SHADER_VARIANT_		67107840
//#define SHADER_VARIANT_		134215680
//#define SHADER_VARIANT_		268431360
//#define SHADER_VARIANT_		536862720


//00100000000000000000000000000001

struct shaderValPair
{
	unsigned short valType;
	
	unsigned int curVal;
	unsigned int lastVal;
	float *mat;
	
	XYZ xyzVal;
	XYZ xyzLastVal;
	
	GLint binding;
};


struct shaderQueueEntry
{
	unsigned int lightType;
	unsigned int shaderMask;
	bool multiLight;
};


class IMPEXP GLShader
{
protected:
	std::map<const char *, shaderValPair> shaderVals;
	static GLhandleARB     activeProgram;
	static GLint	binding_inc;
	
private:
	GLhandleARB     fragShader;
	GLhandleARB     fragShader2;
	GLhandleARB     vertShader;
	GLhandleARB     program;

	std::string frag_str;
	std::string frag_str2;
	std::string vert_str;

	static std::map<unsigned long, std::string, ltulong> light_frag_str;
	static std::map<unsigned long, std::string, ltulong> light_frag_str2;
	static std::map<unsigned long, std::string, ltulong> light_vert_str;
	static std::map<unsigned long, bool, ltulong> light_multi;
	static std::vector<shaderQueueEntry> shader_queue;
	static unsigned long shaderQueuePtr;

public:
	static bool defaultShaderLoaded;
	static GLShader defaultShader;
	static std::map<unsigned long, std::map<unsigned long, std::vector<GLShader *>, ltulong>, ltulong> lightShader;

	GLint light_binding;
	GLint light_type_binding;

	bool loaded;

	GLShader();

	static bool loadDefaultShader(const char *vf, const char *ff, const char *ff2 = 0);
	static bool loadLightShader(int lightType, const char *vf, const char *ff, const char *ff2 = 0, bool multiLight=false);
	static bool loadShaderStrings(std::string &vs, std::string &fs, std::string &fs2, const char *vf, const char *ff, const char *ff2 = 0);

	static bool activateLight(int lightType, int lightNum, unsigned long lightVariant, bool compile);
	static bool isMultiLight(int lightType);

//	static void setLightShaderValue(int lightType, const char *varId, unsigned int value);
//	static void setLightShaderValue(int lightType, const char *varId, XYZ &value);
//	static void setLightShaderValue(int lightType, const char *varId, float *value);
	
	static bool buildLightShaderVariant(int lightType, int variantFlag);
	static bool queueLightShaderVariant(int lightType, int variantFlag);
	static bool processShaderQueue();
	
	static void searchAndReplace(std::string &haystack, const char *needle, const char *replacement);
	static void findLoops(std::string &shaderStr, const char *loopStart, const char *loopEnd, std::vector<unsigned int> &loopStarts, std::vector<unsigned int> &loopEnds);
	static void printLog(GLuint obj);
	
	static GLboolean HasGLSL(void);
	static void clear();

	void activateLighting();

//	static inline void setLightActivation(int lightNum, int value) { active_lights[lightNum]=value; };
//	static inline void setLightType(int lightNum, int lightType) { active_light_types[lightNum]=lightType; };

	void setShaderValue(const char *varId, unsigned int value);
	void setShaderValue(const char *varId, XYZ &value);
	void setShaderValue(const char *varId, float *value);
	void setShaderValue(const char *varId, float value);
	void setShaderAttrib(const char *varId, void *value);

	void setupShader();
	void setupShader(GLShader &extShader);
	void clearShader();

	GLenum LinkProgram(GLhandleARB program);
	GLenum CompileProgram(GLenum target, GLcharARB* sourcecode, GLhandleARB *shader);
	bool setup(const char *vp, const char *fp, const char *fp2 = 0);
	bool load(const char *vf, const char *ff, const char *ff2 = 0);
	void use();
	bool isLoaded();
	GLhandleARB getProgramId();

};

#endif