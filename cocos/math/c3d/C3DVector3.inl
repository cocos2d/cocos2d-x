#include "C3DVector3.h"

namespace cocos3d
{

inline const C3DVector3 C3DVector3::operator+(const C3DVector3& v) const
{
    C3DVector3 result(*this);
    result.add(v);
    return result;
}

inline C3DVector3& C3DVector3::operator+=(const C3DVector3& v)
{
    add(v);
    return *this;
}

inline const C3DVector3 C3DVector3::operator-(const C3DVector3& v) const
{
    C3DVector3 result(*this);
    result.subtract(v);
    return result;
}

inline C3DVector3& C3DVector3::operator-=(const C3DVector3& v)
{
    subtract(v);
    return *this;
}

inline const C3DVector3 C3DVector3::operator-() const
{
    C3DVector3 result(*this);
    result.negate();
    return result;
}

inline const C3DVector3 C3DVector3::operator*(float x) const
{
    C3DVector3 result(*this);
    result.scale(x);
    return result;
}

inline C3DVector3& C3DVector3::operator*=(float x)
{
    scale(x);
    return *this;
}

inline bool C3DVector3::operator<(const C3DVector3& v) const
{
    if (x == v.x)
    {
        if (y == v.y)
        {
            return z < v.z;
        }
        return y < v.y;
    }
    return x < v.x;
}

inline bool C3DVector3::operator==(const C3DVector3& v) const
{
    return x==v.x && y==v.y && z==v.z;
}

inline bool C3DVector3::operator!=(const C3DVector3& v) const
{
    return x!=v.x || y!=v.y || z!=v.z;
}

inline const C3DVector3 operator*(float x, const C3DVector3& v)
{
    C3DVector3 result(v);
    result.scale(x);
    return result;
}

inline float C3DVector3::operator[](int index) const 
{ 	
	return ((float*)this)[index]; 
}

}
