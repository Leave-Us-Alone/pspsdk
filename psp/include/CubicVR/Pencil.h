#pragma once
/*
 *  Pencil.h
 *  Builder
 *
 *  Created by Charles J. Cliffe on 23/09/08.
 *  Copyright 2008 Cubic Productions. All rights reserved.
 *
 */


#include <vector>
#include <CubicVR/XYZ.h>
#include <CubicVR/Vector.h>
#include <CubicVR/Envelope.h>
#if !defined(ARCH_DC) && !defined(ARCH_PSP) && !defined(OPENGL_ES)
#include <CubicVR/GLShader.h>
#endif
#include <CubicVR/Envelope.h>

using namespace std;

class Pencil
{
private:
	static std::vector<XYZ>::iterator point_i;
	
public:
	static void drawCircles(std::vector<XYZ> &pointList, float radius);	
	static void drawLine(std::vector<XYZ> &pointList);	
	static void drawLine(std::vector<XYZ> &pointList, Vector up, Vector right);	
	static void drawCurve(std::vector<XYZ> &pointList, int subdivisions);
	static void drawExtruded(std::vector<XYZ> &pointList);
	static void drawExtrudedCurve(std::vector<XYZ> &pointList, int subdivisions);
	static void drawLine(std::vector<XYZ> &pointList,int subdivions);
	static void drawCircle(const XYZ &pt, float radius, int divisions=10);	
	static void drawAxis(const XYZ &pt, float size);	
	static void drawGrid(const XYZ &center, const XYZ &dimensions, float gridsize);
	static void drawGrid(const XYZ &center, const XYZ &dimensions, float gridsize, Vector &up, Vector &right, int divs=3);
	static void drawFrustum(XYZ &position, float modelview[16], float fov, float nearf, float farf, float aspect);
	static void drawBB(const XYZ &bb1, const XYZ &bb2);
};

