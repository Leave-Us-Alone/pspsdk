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

#ifndef CUBICVR_COLLISIONMAP
#define CUBICVR_COLLISIONMAP

#include <CubicVR/Object.h>
#include <CubicVR/Transform.h>
#include <CubicVR/Shader.h>
//#include <CubicVR/SceneObject.h>
#include <vector>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btOptimizedBvh.h>

#define CMAP_SPHERE_NOMINAL 0.3f


struct collision_sphere
{
	XYZ center;
	cvrFloat radius;
	unsigned long face;
	std::vector<collision_sphere *> parents;
	std::vector<collision_sphere *> children;	
};


struct collision_box
{
	cvrFloat xmin, xmax, ymin, ymax, zmin, zmax;
};

typedef struct std::map< Face *, std::vector< Face * >, ltulong > CollisionList;

class CollisionMap
{
public:
	btCollisionShape *mTriMeshShape;
	
	std::vector<Object *> meshes;
	std::vector<std::vector<collision_sphere *>* > spheres;
	std::vector<collision_box *> bboxes;
	std::map< cvrIndex, std::map< cvrIndex, cvrIndex, ltindex >, ltindex > sphere_map;
	Transform *trans;
#ifndef ARCH_PSP
#ifndef OPENGL_ES
	LineShader cmapShader;
#endif
#endif
	unsigned int activeSphereSet;
	float margin;
	
	CollisionMap();
	
	void compileSphereMap(float nominal_rad = CMAP_SPHERE_NOMINAL);
	void bindTransformation(Transform *trans_in);
#ifndef ARCH_PSP
	void render();
#endif

	void addMesh(Object &mesh_obj);
	void addBoundingBox(cvrFloat xmin, cvrFloat xmax, cvrFloat ymin, cvrFloat ymax, cvrFloat zmin, cvrFloat zmax);
	void addSphere(XYZ &center, cvrFloat radius, cvrIndex faceNum = -1);
	void processSpheres(float nominal_rad = CMAP_SPHERE_NOMINAL);
	void setMargin(float margin_in);
	float getMargin();
	
	static void sphereTest(CollisionMap &a, CollisionMap &b, CollisionList &alist, CollisionList &blist);
	
	void getBoundingBox(XYZ &aabbMin, XYZ &aabbMax);
//	btCollisionShape *makeCollisionShape(const XYZ &scale=XYZ(1,1,1), vector<int> *arrayParam=NULL, XYZ *spacing=NULL);
	btCollisionShape *makeCollisionShape(float mass, const XYZ &scale=XYZ(1,1,1), vector<int> *arrayParam=NULL, XYZ *spacing=NULL);
};


#endif
