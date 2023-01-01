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


#pragma once

#include <iostream>
#include <map>
#include <set>
#include <vector>
#ifndef _WIN32
#include <dirent.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


//#include <errno.h>



#include <CubicVR/map_string.h>

#ifdef WIN32
	#define RESOURCEPOOL_PATH_CHAR "\\"
#else
	#define RESOURCEPOOL_PATH_CHAR "/"
#endif

#define RESOURCEPOOL_MAX_PATH 4096

using namespace std;

class MapStringPool;

class ResourcePool
{
public:	
	map<string, vector<string>, string_less> fileMap;
	map<string, vector<string>, string_less> extMap;
	set<string> pathList;
	map<string,bool> recList;
	string tmp_str;
	MapStringPool *strMap;

	ResourcePool();	
	~ResourcePool();	
	
	const char *findByFilename(const char *fn);		
	void findByFilename(const char *fn, std::vector<std::string> &fileList);
	void findByExtension(const char *ext, std::vector<std::string> &fileList);
	int getSize(const char *dirname);	
	int scanDir(const char *dirname,char *entries);
	void refresh();
	void addPath(const char *dirname, bool recursive=false);
	void clearPaths();
	int scanString(char *string,char *buffer);
	std::string StringToLower(std::string str);
	MapString &getMap();
};

class MapStringPool : public MapString
{
private:
	const char *tmp;
	std::string tmpStr;
	
public:
	ResourcePool *pool;
	
	MapStringPool(ResourcePool &pool_in) { pool = &pool_in; };
	const char *getString(const char *str_ref) 
	{ 
		//	printf("requested: %s\n",str_ref);		
		
		tmp = pool->findByFilename(str_ref); 
		tmpStr.clear();
		tmpStr.append(tmp);
		
		//	printf("returned: %s\n",tmpStr.c_str());
		return tmpStr.c_str();
	};
};


