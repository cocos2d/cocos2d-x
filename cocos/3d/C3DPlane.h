#ifndef C3DPLANE_H_
#define C3DPLANE_H_

#include "C3DVector3.h"

namespace cocos3d
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
    C3DPlane(const C3DVector3& p1, const C3DVector3& p2, const C3DVector3& p3);

	/**
     * create plane from normal and dist.
     */
    C3DPlane(const C3DVector3& normal, float dist);

	/**
     * create plane from normal and a point on plane.
     */
    C3DPlane(const C3DVector3& normal, const C3DVector3& point);
    C3DPlane();
    ~C3DPlane();
    
	/**
     * init plane from tree point.
     */
    void initPlane(const C3DVector3& p1, const C3DVector3& p2, const C3DVector3& p3);

	/**
     * init plane from normal and dist.
     */
    void initPlane(const C3DVector3& normal, float dist);

	/**
     * init plane from normal and a point on plane.
     */
    void initPlane(const C3DVector3& normal, const C3DVector3& point);
    
	 /**
     * Sets the plane's normal to the given vector.
     */
    void setNormal(const C3DVector3& normal);
    
    // dist to plane, > 0 normal direction
    float dist2Plane(const C3DVector3& p) const;
    
    // allowed error when point on plane
    static void setOnPlaneErr(float fError);
    
	 /**
     * Gets the plane's normal.
     */
    const C3DVector3& getNormal() const { return m_vNormal; }

	 /**
     * Gets the plane's distance to the origin along its normal.
     */
    float getDist() const  { return m_fDist; }
    
	/**
     * Return positon relatively to the plane.
     */
    POINT_CLASSIFICATION pointClassify(const C3DVector3& point) const;
	
protected:
    C3DVector3 m_vNormal;
    float m_fDist;
	
    static float s_fOnPlaneErr;
};

}

#endif
