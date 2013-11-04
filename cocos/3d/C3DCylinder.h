#ifndef C3DCYLINDER_H_
#define C3DCYLINDER_H_

#include "C3DMatrix.h"
#include "C3DVector3.h"

namespace cocos3d
{

class C3DRay;
class C3DVector3;

/**
 * axis aligned cylinder
 */ 


/**
 * Defines a class describe 3-dimensional axis-aligned Cone.
 */
class C3DCylinder
{
public:
	enum align
	{
		xAxis,
		yAxis,
		zAxis
	};
public:
	C3DCylinder(const C3DVector3& point, align _dim, float radius, float height);
	virtual ~C3DCylinder(){}

	virtual bool Intersect(const C3DRay *ray)const;

	void translate(float cx, float cy, float cz);

	void setPosition(const C3DVector3& point);

	float getHeight() const { return height; }

	float getRadius() const { return radius; }

	const C3DVector3& getCenter() const { return _center; }

	const C3DVector3& getAxisY() const { return _vAxisY; }

	const C3DVector3& getAxisX() const { return _vAxisX; }

	const C3DVector3& getAxisZ() const { return _vAxisZ; }

private:
	void setVector(C3DVector3& src, unsigned int nIndex, float fVal)const;
	float getVector(const C3DVector3& src, unsigned int nIndex)const;

	void setDirAndUp(const C3DVector3& dir, const C3DVector3& up);

private:
	C3DVector3 _down;
	C3DVector3 _up;
	C3DVector3 _center;

	C3DVector3 _vAxisX;
	C3DVector3 _vAxisY;
	C3DVector3 _vAxisZ;

	enum  align _dim;
	float radius;
	float height;
};

}

#endif//C3DCYLINDER_H_
