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

#ifndef MATRIX_H
#define MATRIX_H

#include <CubicVR/cvr_defines.h>

#include <string>
#include <stdio.h>
#include <string.h>

/* nothing is checked, so they better be the right dimensions! */
class IMPEXP Matrix
{
private:
	int width, height;
	float *mData;

public:

	Matrix(int h, int w);
	~Matrix();

	void multiply(Matrix &mIn, Matrix &mOut);

	void multiply1_4by4_4(Matrix &mIn, Matrix &mOut);	// optimized
	void multiply4_4by4_4(Matrix &mIn, Matrix &mOut);
	
	void multiply(float val);
	void add(Matrix &mIn);
	void add(Matrix &mIn, int k);	/* add with multiple k of mIn */

	void set(Matrix &mIn);
	void set(float *mat);
	float *get() { return mData; };

	void loadIdentity(void);
	

	void set(int i, int j, float val)	{	*(mData+i*width+j) = val;	}
	float get(int i, int j)				{	return *(mData+i*width+j);	}

	int WIDTH()	{	return width;	}
	int HEIGHT() {	return height;	}
};






#endif

