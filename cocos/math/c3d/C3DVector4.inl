#include "C3DVector4.h"

namespace cocos3d
{

inline void C3DVector4::add(const C3DVector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}
inline const C3DVector4 C3DVector4::operator+(const C3DVector4& v) const
{
    return C3DVector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

inline C3DVector4& C3DVector4::operator+=(const C3DVector4& v)
{
    add(v);
    return *this;
}

inline const C3DVector4 C3DVector4::operator-(const C3DVector4& v) const
{
    C3DVector4 result(*this);
    result.subtract(v);
    return result;
}

inline C3DVector4& C3DVector4::operator-=(const C3DVector4& v)
{
    subtract(v);
    return *this;
}

inline const C3DVector4 C3DVector4::operator-() const
{
    C3DVector4 result(*this);
    result.negate();
    return result;
}

inline const C3DVector4 C3DVector4::operator*(float x) const
{
    C3DVector4 result(*this);
    result.scale(x);
    return result;
}

inline C3DVector4& C3DVector4::operator*=(float x)
{
    scale(x);
    return *this;
}

inline bool C3DVector4::operator<(const C3DVector4& v) const
{
    if (x == v.x)
    {
        if (y == v.y)
        {
            if (z < v.z)
            {
                if (w < v.w)
                {
                    return w < v.w;
                }
            }
            return z < v.z;
        }
        return y < v.y;
    }
    return x < v.x;
}

inline bool C3DVector4::operator==(const C3DVector4& v) const
{
    return x==v.x && y==v.y && z==v.z && w==v.w;
}

inline bool C3DVector4::operator!=(const C3DVector4& v) const
{
    return x!=v.x || y!=v.y || z!=v.z || w!=v.w;
}

inline const C3DVector4 operator*(float x, const C3DVector4& v)
{
    C3DVector4 result(v);
    result.scale(x);
    return result;
}

inline const C3DVector4 C3DVector4::operator*(const C3DVector4& v) const
{
	return C3DVector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

}
