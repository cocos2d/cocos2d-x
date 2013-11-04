#include "Base.h"
#include "C3DCylinder.h"
#include "C3DRay.h"
#include "C3DVector3.h"
#include "C3DPlane.h"

namespace cocos3d
{

C3DCylinder::C3DCylinder(const C3DVector3& point, align _dim, float radius, float height)
	: _center(point), _dim(_dim), radius(radius), height(height)
{
	// unit vector in _dim direction
	C3DVector3 add = C3DVector3::zero();
	//add.set(_dim, 1);
	setVector(add, _dim, 1);
	//// compute center of the cylinder
	//_center = point;
	// center of the sphere downwards
	_down = _center - height * add;
	// center of the sphere upwards
	_up = _center + height * add;

	switch (_dim)
	{
	case C3DCylinder::xAxis:
		{
			setDirAndUp(C3DVector3(0.0f, 0.0f, 1.0f), C3DVector3(1.0f, 0.0f, 0.0f));
		}	
		break;
	case C3DCylinder::yAxis:
		{
			setDirAndUp(C3DVector3(0.0f, 0.0f, 1.0f), C3DVector3(0.0f, 1.0f, 0.0f));
		}
		break;
	case C3DCylinder::zAxis:
		{
			setDirAndUp(C3DVector3(0.0f, 1.0f, 0.0f), C3DVector3(0.0f, 0.0f, 1.0f));
		}
		break;
	}
}

void C3DCylinder::setDirAndUp(const C3DVector3& dir, const C3DVector3& up)
{
	_vAxisZ = dir;
	_vAxisZ.normalize();
	_vAxisY = up;
	_vAxisY.normalize();

	C3DVector3::cross(_vAxisY, _vAxisZ, &_vAxisX);
    C3DVector3::cross(_vAxisZ, _vAxisX, &_vAxisY);
}

bool C3DCylinder::Intersect(const C3DRay *ray)const
{
	if (!ray) return false;

    /** 
    * first: infinite long cylinder
    * computation as for sphere, just one dimension missing
    */
                 
    /** 
    * x^2 + y^2 = radius^2 
    */
    C3DVector3 diff = ray->getOrigin() - _down;
    C3DVector3 dir  = ray->getDirection();

    //diff[_dim] = 0.0;
    //dir[_dim] = 0.0;
	setVector(diff, _dim, 0.f);
	setVector(dir, _dim, 0.f);
        
    float a = C3DVector3::dot(dir, dir);
    float b = 2 * C3DVector3::dot(dir, diff);
    float c = C3DVector3::dot(diff, diff) - radius * radius;
        
    float inRoot = b*b - 4*a*c;
    if (inRoot < 0) 
        return false;
    float root = sqrt(inRoot);
          
	float ray_t = 100000.f;
    float dist = (-b - root)/(2*a);
    if (dist > ray_t/*ray._t*/)
        return false;
        
    if (dist < FLT_EPSILON) 
    {
        dist = (-b + root)/(2*a);
        if (dist < FLT_EPSILON || dist > ray_t/*ray._t*/)
            return false;
    }   

    /**
    * side
    * cut off, so that a 2*height cylinder stays
    * which is open to both sides
    */
    C3DVector3 hit = ray->getOrigin() + dist * ray->getDirection();
    //float t1 = (hit - _center).get(_dim);
     float t1 = getVector((hit - _center), _dim);          
    if ( - height < t1 && t1 < height ) 
    {
        //ray._t = dist;
        //ray.hit = this;
        return true;
    }

    /** 
    * compute top and bottom surfaces => close the cylinder
    * check if ray hits planes located at _down and _up within the radius of the cylinder
    */
    const C3DRay* ray1 = ray;
    const C3DRay* ray2 = ray;
                                
    C3DVector3 normal = C3DVector3(0);
    //normal[_dim] = 1.0;
	setVector(normal, _dim, 1.0);

    //Primitive* plane1 = new InfinitePlane( _down, normal );
	//plane1->intersect(ray1);
	//delete plane1;
	C3DPlane plane1(normal, _down);// = new C3DPlane(normal, _down);
	float hit_plane1 = ray1->dist(&plane1);
    
        
    //Primitive* plane2 = new InfinitePlane( _up,   normal );
	//bool hit_plane2 = plane2->Intersect(ray2);
	//delete plane2;
	C3DPlane plane2(normal, _up);
	float hit_plane2 = ray2->dist(&plane2);
        
    // bottom surface
    if (hit_plane1 >= FLT_EPSILON)
    {
        C3DVector3 hit1 = (ray1->getOrigin() + ray_t * ray1->getDirection()) - _down;
        //hit1[_dim] = 0.0;
		setVector(hit1, _dim, 0.0);
        if ( /*Length(hit1)*/hit1.length() < radius * radius )
        {                                       
            //ray._t = ray1._t;
            //ray.hit = this;
            return true;
        }
    }
        
    // top surface
    if (hit_plane2 >= FLT_EPSILON)
    {
        C3DVector3 hit2 = (ray2->getOrigin() + /*ray2._t*/ray_t * ray2->getDirection()) - _up;
        //hit2[_dim] = 0.0;
		setVector(hit2, _dim, 0.0);
        
        if ( /*Length(hit2)*/hit2.length() < radius * radius )
        {                                       
            //ray._t = ray2._t;
            //ray.hit = this;
            return true;
        }
    }
                                
    return false;       
};

void C3DCylinder::translate(float cx, float cy, float cz)
{
	C3DVector3 add = C3DVector3::zero();
	setVector(add, _dim, 1);

	C3DVector3 move(cx, cy, cz);
	_center += move;

	_down = _center - height * add;
	// center of the sphere upwards
	_up = _center + height * add;
}

void C3DCylinder::setPosition(const C3DVector3& point)
{
	C3DVector3 add = C3DVector3::zero();
	//add.set(_dim, 1);
	setVector(add, _dim, 1);
	// compute center of the cylinder
	_center = point;
	// center of the sphere downwards
	_down = _center - height * add;
	// center of the sphere upwards
	_up = _center + height * add;
}

void C3DCylinder::setVector(C3DVector3& src, unsigned int nIndex, float fVal)const
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

float C3DCylinder::getVector(const C3DVector3& src, unsigned int nIndex)const
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
