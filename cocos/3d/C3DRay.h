#ifndef RAY_H_
#define RAY_H_

#include "C3DVector3.h"

namespace cocos3d
{

class C3DAABB;
class C3DPlane;
class C3DOBB;
class C3DCone;
class C3DCone2;
class C3DCylinder;
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
    C3DRay(const C3DVector3& origin, const C3DVector3& direction);

	/**
     * Destructor.
     */
    ~C3DRay();

	/**
     * Gets the ray's origin.
     */
    const C3DVector3& getOrigin() const;
	
	/**
     * Sets the ray's origin.
     */
    void setOrigin(const C3DVector3& origin);
	
	/**
     * Gets the ray's direction.
     */
    const C3DVector3& getDirection() const;
	
	/**
     * sets the ray's direction.
     */
    void setDirection(const C3DVector3& direction);

	/**
     * Check whether this ray intersects the specified bounding box.
     */
    bool intersects(const C3DAABB* box) const;
    
	/**
     * Check whether this ray intersects the specified obb.
     */
    bool intersects(const C3DOBB* obb) const;

	float dist(const C3DPlane* plane) const;
	C3DVector3 intersects(const C3DPlane* plane) const;

	///**
 //    * Tests whether this ray intersects the specified plane and returns the distance
 //    * from the origin of the ray to the plane.
 //    *
 //    * @param plane The plane to test intersection with.
 //    * 
 //    * @return The distance from the origin of this ray to the plane or
 //    *     INTERSECTS_NONE if this ray does not intersect the plane.
 //    */
	//float intersects(const C3DPlane* plane) const;

	/**
     * Check whether this ray intersects the specified Cone.
     */
    bool intersects(const C3DCone* cone) const;

	/**
     * Check whether this ray intersects the specified Cylinder.
     */
    bool intersects(const C3DCylinder* pCylinder) const;

	/**
     * Sets this ray to the specified values.
     *
     * @param origin The ray's origin.
     * @param direction The ray's direction.
     */
    void set(const C3DVector3& origin, const C3DVector3& direction);
	
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
    void transform(const C3DMatrix& matrix);

    /**
     * Transforms this ray by the given matrix.
     * 
     * @param matrix The matrix to transform by.
     * @return This ray, after the transformation occurs.
     */
    inline C3DRay& operator*=(const C3DMatrix& matrix);

private:

    /**
     * Normalizes the ray.
     */
    void normalize();

    C3DVector3 _origin;        // The ray origin position.
    C3DVector3 _direction;     // The ray direction vector.
};
    
inline C3DRay& C3DRay::operator*=(const C3DMatrix& matrix)
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
inline const C3DRay operator*(const C3DMatrix& matrix, const C3DRay& ray);
    
    inline const C3DRay operator*(const C3DMatrix& matrix, const C3DRay& ray)
    {
        C3DRay r(ray);
        r.transform(matrix);
        return r;
    }

}


#endif
