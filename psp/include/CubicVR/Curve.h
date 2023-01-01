#pragma once

#include <vector>
#include <CubicVR/XYZ.h>
#include <CubicVR/Envelope.h>
#include <CubicVR/Vector.h>
#if !defined(OPENGL_ES) && !defined(ARCH_PSP)
#include <CubicVR/Pencil.h>
#endif

/*
 *  Curve.h
 *  Builder
 *
 *  Created by Charles J. Cliffe on 23/09/08.
 *  Copyright 2008 Cubic Productions. All rights reserved.
 *
 */

// Curve types

#define CURVE_TCB   0
#define CURVE_HERM  1
#define CURVE_BEZI  2
#define CURVE_LINE  3
#define CURVE_STEP  4
#define CURVE_BEZ2  5


class CurveNode
{
public:	
	int shape;
	float tension;
	float continuity;
	float bias;
	float param[4];
	
	CurveNode();
	CurveNode &operator=(const CurveNode &node_in);
};


class Curve
{
private:
	std::vector<XYZ> pointList;
	std::vector<CurveNode> tcbList;
	std::vector<XYZ>::iterator point_i;
	
	std::vector<XYZ> pointListGen;
	std::vector<XYZ>::iterator pointGen_i;

	bool needs_regen;
	int divisions;
	float threshold;
	
	void regenerate();
	
public:
	Curve();
	
	int numPoints();
	int addPoint(const XYZ &pt);	
	bool empty();
	void clear();
	
	XYZ &getPoint(unsigned int ptNum);
	void setPoint(unsigned int ptNum, const XYZ &pt);
	void deletePoint(unsigned int ptNum);
	
	CurveNode &getNode(unsigned int ptNum);
	void setNode(unsigned int ptNum, CurveNode &node_in);
	
	void setDivisions(unsigned int numDivisions);
	void getCurve(std::vector<XYZ>&curve_out);
	
	void draw();
	void drawExtruded();
	void drawLathe(unsigned int lathe_divisions);
	void setAdaptive(float angle_threshold);
	
	
	XYZ &getCurvePoint(unsigned int ptNum);
	int addCurvePoint(unsigned int ptNum);
	
	int closestPointTo(XYZ &pt);	
	int closestCurvePointTo(XYZ &pt);	
	
//	Curve &operator=(const Curve &vect);
};

