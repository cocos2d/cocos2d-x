#ifndef C3DCAPSULE_H_
#define C3DCAPSULE_H_
#include "C3DVector3.h"

namespace cocos3d
{



class C3DMesh;
class BBVertex;
class C3DVector4;

/**
 * define Capsule geometry.
 */
class C3DCapsule
{

public:
    C3DCapsule();
    ~C3DCapsule();
    
    /**
     * set capsule z, y axis
     */
    void setDirAndUp(const C3DVector3& dirz, const C3DVector3& upY);
    
    /**
     * get axis of capsule
     */
    const C3DVector3& getAxisX() const { return _vAxisX; }
    const C3DVector3& getAxisY() const { return _vAxisY; }
    const C3DVector3& getAxisZ() const { return _vAxisZ; }
    
    /**
     * get & set capsule radius
     */
    float getRadius() const{ return _radius; }
    
    void setRadius(float r) { _radius = r; }
    
    /**
     * get capsule height, cylinder height
     */
    float getCylinderHeight() const { return _height; }
    
    void setCylinderHeight(float hei) { _height = hei; }
    
    /**
     * get & set capsule center position
     */
    void setCenterPos(const C3DVector3& pos) { _vCenter = pos; }
    const C3DVector3& getCenterPos() const { return _vCenter; }
    
protected:
    C3DVector3 _vAxisX;
	C3DVector3 _vAxisY;
	C3DVector3 _vAxisZ;
    
	
	float _radius;
	float _height;
	
    C3DVector3 _vCenter;
};

}

#endif
