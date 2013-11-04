#include "Base.h"
#include "C3DCone.h"
#include "C3DRay.h"
#include "C3DPlane.h"
#include "C3DCylinder.h"
namespace cocos3d
{
	
C3DCone::C3DCone(const C3DVector3& center, align dim, float radius, float height)
				: _center(center), _dim(dim), _radius(radius), _height(height)
{
	dim = yAxis;
};

bool C3DCone::Intersect(const C3DRay *ray)const
{   
	if (!ray) return false;

	float ray_t = 100000.f;

    /**
    * formula for the cone:
    * (x^2 + y^2) = (h/r)^2 * (z - h)^2
    * with ray = org + t * dir, we obtain a quadratic equation
    */
    
    // side
    C3DVector3 diff = ray->getOrigin() - _center;
    C3DVector3 dir  = ray->getDirection();
                
    float ratio = _radius / _height;
        
    C3DVector3 help = C3DVector3(1.0, 1.0, 1.0);/*C3DVector3(1.0);*/
    // help[dim] = -powf(ratio,2.0);
	setVector(help, _dim, -powf(ratio, 2.0));
        
	C3DVector3 tmp;
	C3DVector3::cross(dir, help, &tmp);
    float a = /*Dot*/C3DVector3::dot(dir, tmp/*dir * help*/);
    float b = /*Dot*/C3DVector3::dot(diff, tmp/*dir * help*/) + _height * powf(ratio, 2.0) * getVector(dir, _dim)/*dir[dim]*/;
    b *= 2.0;       
        
	//C3DVector3::cross(dir, help, &tmp);
    float c = /*Dot*/C3DVector3::dot( diff, tmp/*diff * help*/ );
    c += 2.0 * _height * powf(ratio, 2.0) * getVector(diff, _dim)/*diff[dim]*/;
    c -= powf(ratio, 2.0) * powf(_height, 2.0);
        
    /**
    * use 'abc'-formula for finding root t_1,2 = (-b +/- sqrt(b^2-4ac))/(2a)
    */
    float inRoot = b*b - 4*a*c;
    if (inRoot < 0) 
        return false;
    float root = sqrt(inRoot);
        
    float dist = (-b - root)/(2*a);
    if (dist > ray_t)
        return false;
        
    if (dist < FLT_EPSILON) 
    {
        dist = (-b + root)/(2*a);
        if (dist < FLT_EPSILON || dist > ray_t)
            return false;
    }

    /** 
    * compute where the hitpoint is lying
    * side of cone is hit between 0 and height in dim direction
    */
    C3DVector3 hitpoint = ray->getOrigin() + dist * ray->getDirection();
    float t1 = /*(hitpoint - center)[dim]*/getVector((hitpoint - _center), _dim);
        
    if ( 0 < t1 && t1 < _height )
    {
        //ray.t = dist;
        //ray.hit = this;
        return true;
    }

    /**
    * and the base is hit at y = 0
    * thus: compute the plane going through 'center' with dim.th
    * unit vector as normal vector, to close the cone
    */
    C3DVector3 normal = C3DVector3(0,0,0);
    //normal[dim] = 1.0;
	setVector(normal, _dim, 1.0);

    C3DRay clone = *ray;
        
    //Primitive* plane = new InfinitePlane( center, normal );
	C3DPlane *plane = new C3DPlane(normal, _center);
    float t = clone.dist(plane);
    if ( t > FLT_EPSILON)
    {
        /**
        * is the distance of the hitpoint on the plane to the center smaller than radius^2 ?
        * then part of the base found
        * otherwise the ray neither hits the cone's side nor its base 
        */             
        C3DVector3 hitpoint = clone.intersects(plane);;

        if ( /*Length*/(hitpoint - _center).length() < powf(_radius, 2) )
        {       
            //ray.t = clone.t;
            //ray.hit = this;

            return true;
        }
        else 
            return false;
    }

	delete plane;
        
    return false;
};

void C3DCone::setVector(C3DVector3& src, unsigned int nIndex, float fVal)const
{
	if (nIndex == 0)
		src.x = fVal;
	else if (nIndex == 1)
		src.y = fVal;
	else if (nIndex == 2)
		src.z = fVal;
	else
		assert(0);
}

float C3DCone::getVector(const C3DVector3& src, unsigned int nIndex)const
{
	if (nIndex == 0)
		return src.x;
	else if (nIndex == 1)
		return src.y;
	else if (nIndex == 2)
		return src.z;
	else
		assert(0);
	return 0.0f;
}

}
