#ifndef C3DOBB_H_
#define C3DOBB_H_

#include "Vector3.h"
#include "C3DMatrix.h"
#include "C3DAABB.h"

namespace cocos2d
{
/**
* a class represent oriented bounding box
*/
class C3DOBB
{
public:
	C3DOBB();
	C3DOBB(const C3DOBB& obb);

	// is point in this obb
	bool isPointIn(const Vector3& point) const;

	// clear obb
	void clear();

	// build obb from oriented bounding box
	void build(const C3DAABB& aabb);

	// build obb from points
	void build(const Vector3* verts, int nVerts);

	// face to the obb's -z direction
	// verts[0] : front left bottom corner
	// verts[1] : front right bottom corner
	// verts[2] : front right top corner
	// verts[3] : front left top corner
	// verts[4] : back left bottom corner
	// verts[5] : back right bottom corner
	// verts[6] : back right top corner
	// verts[7] : back left top corner
	void getVertices(Vector3* verts) const;

	// compute extX, extY, extZ
	// if obb axis changed call this function before use ext axis
	void completeExtAxis()
	{
		extX = xAxis * extents.x;
		extY = yAxis * extents.y;
		extZ = zAxis * extents.z;
	}

	/**
	* Transforms the obb by the given transformation matrix.
	*/
	void transform(const Matrix& mat);

public:

	Vector3 center; // obb center

	Vector3 xAxis; // x axis of obb, unit vector
	Vector3 yAxis; // y axis of obb, unit vecotr
	Vector3 zAxis; // z axis of obb, unit vector

	Vector3 extX; // xAxis * extents.x
	Vector3 extY; // yAxis * extents.y
	Vector3 extZ; // zAxis * extents.z

	Vector3 extents; // obb length along each axis
};
}

#endif
