#ifndef C3DPLANE_H_
#define C3DPLANE_H_

#include "Vector3.h"

namespace cocos2d
{
/**
* Defines a 3D plane.
* a*x + b*y + c*z = d;
*/
class C3DPlane
{
public:
    enum POINT_CLASSIFICATION
    {
		ON_PLANE,
		FRONT_PLANE,
		BEHIND_PLANE,
    };

public:
	/**
     * create plane from tree point.
     */
    C3DPlane(const Vector3& p1, const Vector3& p2, const Vector3& p3);

	/**
     * create plane from normal and dist.
     */
    C3DPlane(const Vector3& normal, float dist);

	/**
     * create plane from normal and a point on plane.
     */
    C3DPlane(const Vector3& normal, const Vector3& point);
    C3DPlane();
    ~C3DPlane();

	/**
     * init plane from tree point.
     */
    void initPlane(const Vector3& p1, const Vector3& p2, const Vector3& p3);

	/**
     * init plane from normal and dist.
     */
    void initPlane(const Vector3& normal, float dist);

	/**
     * init plane from normal and a point on plane.
     */
    void initPlane(const Vector3& normal, const Vector3& point);

	/**
	* Sets the plane's normal to the given vector.
	*/
    void setNormal(const Vector3& normal);

    // dist to plane, > 0 normal direction
    float dist2Plane(const Vector3& p) const;

    // allowed error when point on plane
    static void setOnPlaneErr(float fError);

	/**
	* Gets the plane's normal.
	*/
    const Vector3& getNormal() const { return m_vNormal; }

	/**
	* Gets the plane's distance to the origin along its normal.
	*/
    float getDist() const  { return m_fDist; }

	/**
     * Return positon relatively to the plane.
     */
    POINT_CLASSIFICATION pointClassify(const Vector3& point) const;

protected:
    Vector3 m_vNormal;
    float m_fDist;

    static float s_fOnPlaneErr;
};
}

#endif
