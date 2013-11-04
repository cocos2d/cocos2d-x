#include "C3DQuaternion.h"

namespace cocos3d
{

inline const C3DQuaternion C3DQuaternion::operator*(const C3DQuaternion& q) const
{
    C3DQuaternion result(*this);
    result.multiply(q);
    return result;
}

inline C3DQuaternion& C3DQuaternion::operator*=(const C3DQuaternion& q)
{
    multiply(q);
    return *this;
}

}
