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

#ifndef IFF_H
#define IFF_H

#include <CubicVR/cvr_defines.h>

#include "CubicVR/XYZ.h"
#include "CubicVR/Vector.h"

#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

class IMPEXP IFFBlock
{

public:

	char header[5];
	unsigned long size;
	unsigned long block_ptr;
	char *data;

	IFFBlock() { size = 0; block_ptr = 0; data = NULL; }
	IFFBlock(char *header_in, unsigned long size_in, char *data_in);
	~IFFBlock() { if (data) delete data; }
	
	
	long getLong() 
	{ 
		long long_out = longbuf2long(data+block_ptr); 
		block_ptr+=4; 
		return long_out;
	}
	
	float getFloat() 
	{  
		float float_out = floatbuf2float(data+block_ptr);
		block_ptr+=4; 
		return float_out;
	}

	short getShort() 
	{  
		short short_out = shortbuf2short(data+block_ptr);
		block_ptr+=2;
		return short_out;
	}
	
	void getVector(XYZ &xyz_out) 
	{  
		vectbuf2vect(xyz_out,data+block_ptr); block_ptr+=12;	
	}
	
	unsigned long getVx(int &vxsize) 
	{  
		unsigned long vx_out;
		vx_out = vxbuf2vx(data+block_ptr,vxsize); 
		block_ptr+=vxsize;	
		return vx_out;
	}
	
	unsigned long getVx() 
	{  
		unsigned long vx_out;
		int vxsize;
		vx_out = vxbuf2vx(data+block_ptr,vxsize); 
		block_ptr+=vxsize; 
		return vx_out;
	}
	
	void getHeader(char *header) 
	{ 
		memcpy(header,data+block_ptr,4); 
		header[4] = 0; 
		block_ptr+=4; 
	}

	void getString(string &str_out) 
	{ 
		int len; 
		char *temp = data+block_ptr; 
		
		len = strlen(temp)+1; if (len % 2) len++; 
		block_ptr+=len;
		
		str_out = string(temp);
	}
	
	bool finished() { return block_ptr >= size; }

	char *data_ptr() { return data+block_ptr; }
	long remainder() { return size-block_ptr; }

	static long longbuf2long(char *in_buf);	
	static float floatbuf2float(char *in_buf);
	static short shortbuf2short(char *in_buf);
	static void vectbuf2vect(XYZ &xyz_out, char *in_buf);
	static unsigned long vxbuf2vx(char *in_buf, int &vxsize);
};


class IMPEXP IFFReader
{

private:

	vector<IFFBlock *> iffData;
	

public:

	char header[5];

	IFFReader() { }
	IFFReader(char *in_data, long data_size, int ptr_size = 4);

	static bool isIFF(const string &filename);

	bool load(const string &filename);
	
	void processIFFBlock(char *in_data, long data_size, int ptr_size);
	void processIFFBlockWithHeader(char *in_data, long data_size, int ptr_size);
	void processIFFBlockWithHeader(char *in_data, long data_size);

	IFFBlock *getBlock(char *header_name);
	IFFBlock *getBlock(char *header_name, int blockCount);
	void getBlockNames(std::vector<string> &blockList);
};


#endif
