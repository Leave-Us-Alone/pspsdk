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
    
    
    Source (c) 2008 by Charles J. Cliffe unless otherwise specified
    To contact me, e-mail or MSN to cj@cubicproductions.com or by ICQ#7188044
    http://www.cubicproductions.com
*/



#ifndef CUBICVR_PRIMITIVES
#define CUBICVR_PRIMITIVES

#include <CubicVR/cvr_defines.h>
#include <CubicVR/Scene.h>
#include <CubicVR/SceneObject.h>
#include <CubicVR/UVMapper.h>


class IMPEXP Primitive: public SceneObject
{
	public:

		Primitive();

		void createSolidCube(Scene &scene, int size);

	/*
	unsigned int uiMaterial, fontMaterial;
	int consoleWidth, consoleHeight;
	
	vector<string> consoleData;
	vector<SceneObject *> uiFontLetters;
	vector<Object *> uiFontLetterObjs;
	
	Console(int consoleWidth_in, int consoleHeight_in, unsigned int fontMaterial_in, unsigned int uiMaterial_in = 0);

	void makeLetter(Object &obj, unsigned short charnum, unsigned int fontMaterial);

	void writeLn(string console_str = "");
	void write(string console_str = "");
	void refreshConsole();

	void fxWave(float timeVal);

	*/	
	private:
		int size;

};

#endif