#ifndef RAY_H_
#define RAY_H_

#include "Vector3.h"

namespace cocos2d
{
class C3DAABB;
class C3DPlane;
class C3DOBB;

/**
* Defines a 3-dimensional ray.
*
* This class guarantees that its direction vector is always normalized.
*/
class C3DRay
{
public:

	/**
	* Represents when a 3D entity does not intersect a ray.
	*/
	static const int INTERSECTS_NONE = -1;

	/**
	* Constructor.
	*/
	C3DRay();

	/**
	* Constructs a new ray initialized to the specified values.
	*
	* @param origin The ray's origin.
	* @param direction The ray's direction.
	*/
	C3DRay(const Vector3& origin, const Vector3& direction);

	/**
	* Destructor.
	*/
	~C3DRay();

	/**
	* Gets the ray's origin.
	*/
	const Vector3& getOrigin() const;

	/**
	* Sets the ray's origin.
	*/
	void setOrigin(const Vector3& origin);

	/**
	* Gets the ray's direction.
	*/
	const Vector3& getDirection() const;

	/**
	* sets the ray's direction.
	*/
	void setDirection(const Vector3& direction);

	/**
	* Check whether this ray intersects the specified bounding box.
	*/
	bool intersects(const C3DAABB* box) const;

	/**
	* Check whether this ray intersects the specified obb.
	*/
	bool intersects(const C3DOBB* obb) const;

	float dist(const C3DPlane* plane) const;
	Vector3 intersects(const C3DPlane* plane) const;

	/**
	* Sets this ray to the specified values.
	*
	* @param origin The ray's origin.
	* @param direction The ray's direction.
	*/
	void set(const Vector3& origin, const Vector3& direction);

	/**
	* Sets this ray to the given ray.
	*
	* @param ray The ray to copy.
	*/
	void set(const C3DRay& ray);

	/**
	* Transforms this ray by the given transformation matrix.
	*
	* @param matrix The transformation matrix to transform by.
	*/
	void transform(const Matrix& matrix);

	/**
	* Transforms this ray by the given matrix.
	*
	* @param matrix The matrix to transform by.
	* @return This ray, after the transformation occurs.
	*/
	inline C3DRay& operator*=(const Matrix& matrix);

private:

	/**
	* Normalizes the ray.
	*/
	void normalize();

	Vector3 _origin;        // The ray origin position.
	Vector3 _direction;     // The ray direction vector.
};

inline C3DRay& C3DRay::operator*=(const Matrix& matrix)
{
	transform(matrix);
	return *this;
}

/**
* Transforms the given ray by the given matrix.
*
* @param matrix The matrix to transform by.
* @param ray The ray to transform.
* @return The resulting transformed ray.
*/
inline const C3DRay operator*(const Matrix& matrix, const C3DRay& ray);

inline const C3DRay operator*(const Matrix& matrix, const C3DRay& ray)
{
	C3DRay r(ray);
	r.transform(matrix);
	return r;
}
}

#endif
