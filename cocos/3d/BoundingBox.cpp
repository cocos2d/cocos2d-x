#include "Base.h"
#include "BoundingBox.h"


namespace cocos3d
{

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(const C3DVector3& min, const C3DVector3& max)
{
    set(min, max);
}

BoundingBox::BoundingBox(const BoundingBox& box)
{
	set(box._min,box._max);
}


BoundingBox::~BoundingBox()
{
}


C3DVector3 BoundingBox::getCenter()
{
    C3DVector3 center;
	center.x = 0.5f*(_min.x+_max.x);
	center.y = 0.5f*(_min.y+_max.y);
	center.z = 0.5f*(_min.z+_max.z);
  
    return center;
}

void BoundingBox::getCorners(C3DVector3* dst) const
{
    assert(dst);

    // Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
    // Left-top-front.
    dst[0].set(_min.x, _max.y, _max.z);
    // Left-bottom-front.
    dst[1].set(_min.x, _min.y, _max.z);
    // Right-bottom-front.
    dst[2].set(_max.x, _min.y, _max.z);
    // Right-top-front.
    dst[3].set(_max.x, _max.y, _max.z);

    // Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
    // Right-top-back.
    dst[4].set(_max.x, _max.y, _min.z);
    // Right-bottom-back.
    dst[5].set(_max.x, _min.y, _min.z);
    // Left-bottom-back.
    dst[6].set(_min.x, _min.y, _min.z);
    // Left-top-back.
    dst[7].set(_min.x, _max.y, _min.z);
}


bool BoundingBox::intersects(const BoundingBox& box) const
{
    return ((_min.x >= box._min.x && _min.x <= box._max.x) || (box._min.x >= _min.x && box._min.x <= _max.x)) &&
           ((_min.y >= box._min.y && _min.y <= box._max.y) || (box._min.y >= _min.y && box._min.y <= _max.y)) &&
           ((_min.z >= box._min.z && _min.z <= box._max.z) || (box._min.z >= _min.z && box._min.z <= _max.z));
}

void BoundingBox::merge(const BoundingBox& box)
{
    // Calculate the new minimum point.
    _min.x = std::min(_min.x, box._min.x);
    _min.y = std::min(_min.y, box._min.y);
    _min.z = std::min(_min.z, box._min.z);

    // Calculate the new maximum point.
    _max.x = std::max(_max.x, box._max.x);
    _max.y = std::max(_max.y, box._max.y);
    _max.z = std::max(_max.z, box._max.z);
}

void BoundingBox::set(const C3DVector3& min, const C3DVector3& max)
{
    this->_min = min;
    this->_max = max;
}

void updateMinMax(C3DVector3* point, C3DVector3* min, C3DVector3* max)
{
    // Leftmost point.
    if (point->x < min->x)
    {
        min->x = point->x;
    }

    // Lowest point.
    if (point->y < min->y)
    {
        min->y = point->y;
    }

    // Farthest point.
    if (point->z < min->z)
    {
        min->z = point->z;
    }

    // Rightmost point.
    if (point->x > max->x)
    {
        max->x = point->x;
    }

    // Highest point.
    if (point->y > max->y)
    {
        max->y = point->y;
    }

    // Nearest point.
    if (point->z > max->z)
    {
        max->z = point->z;
    }
}



void BoundingBox::transform(const C3DMatrix& matrix)
{
   
    C3DVector3 corners[8];  
	 // Near face, specified counter-clockwise
    // Left-top-front.
    corners[0].set(_min.x, _max.y, _max.z);
    // Left-bottom-front.
    corners[1].set(_min.x, _min.y, _max.z);
    // Right-bottom-front.
    corners[2].set(_max.x, _min.y, _max.z);
    // Right-top-front.
    corners[3].set(_max.x, _max.y, _max.z);

    // Far face, specified clockwise
    // Right-top-back.
    corners[4].set(_max.x, _max.y, _min.z);
    // Right-bottom-back.
    corners[5].set(_max.x, _min.y, _min.z);
    // Left-bottom-back.
    corners[6].set(_min.x, _min.y, _min.z);
    // Left-top-back.
    corners[7].set(_min.x, _max.y, _min.z);

    // C3DTransform the corners, recalculating the min and max points along the way.
    matrix.transformPoint(&corners[0]);
    C3DVector3 newMin = corners[0];
    C3DVector3 newMax = corners[0];
    for (int i = 1; i < 8; i++)
    {
        matrix.transformPoint(&corners[i]);
        updateMinMax(&corners[i], &newMin, &newMax);
    }
    _min = newMin;
    _max = newMax;
}

}
