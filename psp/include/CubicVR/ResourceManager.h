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

#include <CubicVR/Resource.h>
#include <CubicVR/ResourceManager.h>
#include <CubicVR/ResourcePool.h>
#include <CubicVR/map_string.h>

typedef std::map<std::string, Resource*, string_less> ResourceTypeSet;
typedef std::map< std::string, std::map<std::string, Resource*, string_less>, string_less> ResourceSet;

class ResourceManager;

typedef ResourceManager * ResourceManagerPtr;
typedef Resource * ResourcePtr;
typedef ResourcePtr (*ResourceCast)(ResourceManagerPtr,ResourcePtr);

class ResourceManagerInit
{
public:
	ResourceManagerInit();	
	~ResourceManagerInit();
};


class ResourceManager
{
private:
	ResourceSet *mResources;
	ResourceSet *mSubResources;

	std::map<Resource *,Resource *> outcastBin;
	std::set<Resource *> resourceBin;
	std::set<Resource *> upcastBin;
	std::map<std::string, ResourcePool *> mFilePool;	
	
	// static class init causes initilization at runtime
	static ResourceManagerInit function_initializer;
	static std::map<std::string, ResourceCast, string_less> upcastFunc;
	
	
public:
	ResourceManager();
	~ResourceManager();

	static void addCastFunc(std::string cast_type, ResourceCast cast_func);
	
	void loadResourcePool(string poolName);
	
	bool hasPool(string poolName);	
	bool hasResource(string typeId, string idName);
	bool hasSubResource(string typeId, string idName);
	bool hasCast(string typeId, string idName);	
	
	ResourcePool &pool(string poolName);
	
	void addResource(Resource &res_in, bool final=false);
	Resource *removeResource(Resource &res_in);
	
	Resource &getResource(string typeId, string idName);
	ResourceSet &getResources();
	ResourceTypeSet &getResources(string typeId);

	Resource &getSubResource(string typeId, string idName);
	ResourceSet &getSubResources();
	ResourceTypeSet &getSubResources(string typeId);
	
	Resource *upcast(Resource *res_in);			
};



