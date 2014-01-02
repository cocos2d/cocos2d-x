#ifndef C3DAABB_H_
#define C3DAABB_H_

#include "math/Vector3.h"
#include "math/Matrix.h"

namespace cocos2d
{
class C3DPlane;
/**
* Defines a class describe 3-dimensional axis-aligned bounding box.
*/
class C3DAABB
{
public:

	Vector3 _min;

	Vector3 _max;

	/**
	* Constructor.
	*/
	C3DAABB();

	/**
	* Constructor.
	*/
	C3DAABB(const Vector3& min, const Vector3& max);

	/**
	* Constructor.
	*/
	C3DAABB(const C3DAABB& box);

	/**
	* Destructor.
	*/
	~C3DAABB();

	/**
	* Gets the center point of the bounding box.
	*/
	Vector3 getCenter();

	Vector3 getSize();

	float getLength();

	/**
	* Gets the corners of the bounding box in the specified array.
	*/
	void getCorners(Vector3* dst) const;

	/**
	* Tests whether this bounding box intersects the specified bounding object.
	*/
	bool intersects(const C3DAABB& box) const;

	bool containPoint( const Vector3& point) const;
	bool containSphere( const Vector3 &center,float radius ) const;

	float distance( const Vector3& vPoint);

	/**
	* Sets this bounding box to the smallest bounding box
	* that contains both this bounding object and the specified bounding box.
	*/
	void merge(const C3DAABB& box);

	/**
	* Sets this bounding box to the specified values.
	*/
	void set(const Vector3& min, const Vector3& max);

	void reset();

	/**
	* Transforms the bounding box by the given transformation matrix.
	*/
	void transform(const Matrix& matrix);
};
}

#endif
