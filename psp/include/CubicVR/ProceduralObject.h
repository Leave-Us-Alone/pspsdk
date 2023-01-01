#pragma once
/*
 *  ProceduralObject.h
 *  Builder
 *
 *  Created by Charles J. Cliffe on 27/09/08.
 *  Copyright 2008 Cubic Productions. All rights reserved.
 *
 */


#include <CubicVR/Object.h>
#include <CubicVR/Vector.h>
#include <CubicVR/UVMapper.h>
#include <CubicVR/Shader.h>
#include <CubicVR/Curve.h>

#define PROCEDURAL_LATHE 10
#define PROCEDURAL_EXTRUDE 10

class ProceduralObject : public Object
{
private:
	bool generated;
	bool needs_regen;
	Material *mat;
	
	std::vector<XYZ> lastPoints;
	unsigned int lastDivisions;
	
public:
	ProceduralObject();	

	void regenerate();

	Material &material();
	
	void generateSphere(float radius, unsigned int hor_div, unsigned int vert_div, Material *materialId, bool dynamicUpdate=false);
	void generateLathe(std::vector<XYZ> &pointList, unsigned int lathe_divisions, Material *materialId, bool dynamicUpdate=false);
	void generateExtruded(Curve &curve_in);
	
	void staticRotate(const XYZ &rot);
};


