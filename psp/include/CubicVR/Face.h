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

#ifndef CUBICVR_FACE_H
#define CUBICVR_FACE_H

/* need to allow for floating point inacuracies */
#define FLOAT_TOLERANCE 0.1f


#include <CubicVR/cvr_defines.h>

#include <vector>

#include <CubicVR/XYZRGB.h>
#include <CubicVR/Vector.h>
#include <CubicVR/Material.h>
#include <CubicVR/UV.h>

using namespace std;


class IMPEXP Face
{
public:
	std::vector<XYZ *> points;
	std::vector<cvrIndex> pointref;
	std::vector< std::vector<UV> > uv;
	std::vector<Vector> point_normals;
	std::vector<RGB> point_colors;

	Material *mat_ref;
	Vector face_normal;
	
	unsigned int segment_id;

//#ifndef OPENGL_ES|ARCH_PSP
//	Vector invNormal;
//	Vector binormal;
//	Vector tangent;
//#endif
	
	Face();
	~Face();
	
	void calcNormal(Vector &norm_out);
	void calcFaceNormal();
	void flip();

	float planeDistanceTo(XYZ &v_test);
	bool triangleDistanceTest(XYZ &v_test,float dist_test);

	bool segmentIntersects(XYZ &returned_intersect_point, XYZ &segment_start, XYZ &segment_end, float tolerance=FLOAT_TOLERANCE);
	bool intersects(Face &test_face);
	bool onTriangle(XYZ &p_test, float tolerance=FLOAT_TOLERANCE);

	void copyUV(Face &dst, unsigned int dstPointNum, unsigned int srcPointNum);
	
	void setUV(unsigned int facePoint, UV pointUV, unsigned int uvLayer=0);
	void setUV(unsigned int facePoint, vector< UV > pointUVs);

	void setColor(unsigned int facePoint, RGB &clr);
	
	void setSegment(unsigned int segment);
	unsigned int getSegment();
	
//#ifndef OPENGL_ES|ARCH_PSP
//	void FindInvTBN(XYZ Vertices[3], UV TexCoords[3], Vector & InvNormal, Vector & InvBinormal, Vector & InvTangent);
//	void calcTangentBinormal();
//#endif
};


#endif

