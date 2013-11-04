#ifndef C3DCONE_H_
#define C3DCONE_H_

#include "C3DMatrix.h"

namespace cocos3d
{

class C3DRay;
class C3DVector3;
class C3DCone
{
public:
	enum align
	{
		xAxis,
		yAxis,
		zAxis
	};
public:
    /**
     * axis aligned cone
     * the alignment is not given as parameter, thus: only cone in y-direction!
     * since I have a translation class which supports rotation
     */
    C3DCone(const C3DVector3& center, align dim, float radius, float height);
    
    virtual ~C3DCone(){}
    
    virtual bool Intersect(const C3DRay *ray)const;

private:
	void setVector(C3DVector3& src, unsigned int nIndex, float fVal)const;
	float getVector(const C3DVector3& src, unsigned int nIndex)const;

private:
	C3DVector3 _center;
	float _radius;
	float _height;
	int _dim;
};


}

#endif//C3DCONE_H_
