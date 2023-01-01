/*
 *  HDR.h
 *  CubicVR
 *  
 *  Based directly on http://www.prideout.net/bloom/ nice work!
 *
 */

#pragma once

#include "CubicVR/ph/ph.h"

#define HDR_FILTER_COUNT  filter_levels
#define HDR_FILTER_MAX	6
#define HDR_KERNEL_SIZE   3 
#define HDR_BLUR_MAX	24

typedef enum {HORIZONTAL, VERTICAL} Direction;

class HDR
{
protected:
	PHsurface window;
	PHsurface pass0[HDR_FILTER_MAX];
	PHsurface pass1[HDR_FILTER_MAX];
	PHsurface mblur[HDR_BLUR_MAX];
	GLuint sphereVerts;
	GLuint sphereFaces;
	GLuint blitProg;
	GLuint combineProg;
	GLuint filterProg;
	GLuint hiPassProg;
	
	int blur_step;
	
	float *kernel;
	bool initialized, buffer_open;
	int filter_levels;
	int blur_levels;

public:
	PHsurface scene;

	int buffer_width, buffer_height, view_width, view_height;
	
	HDR(int width_in, int height_in, int filter_levels=5);
	
	~HDR();
	void blur(PHsurface *sources, PHsurface *dests, int count, Direction dir);
	void init();
	void drawBegin();
	void drawEnd();
	void setFilterLevel(int filter_level_in);
	void setBlurLevel(int blur_level_in);
	
	void drawOpen();
	void drawClear();
	void drawClose();
	
	void setViewSize(int width_in, int height_in);
	void clear();
	
	
};
