#ifndef DRAGONBONES_TRANSFORM_H
#define DRAGONBONES_TRANSFORM_H

#include "../core/DragonBones.h"
#include "Matrix.h"

DRAGONBONES_NAMESPACE_BEGIN

class Transform final
{
public:
    static float normalizeRadian(float value)
    {
        value = std::fmod(value + PI, PI * 2.f);
        value += value > 0.f ? -PI : PI;

        return value;
    }

public:
    float x;
    float y;
    float skewX;
    float skewY;
    float scaleX;
    float scaleY;

    Transform():
        x(0.f),
        y(0.f),
        skewX(0.f),
        skewY(0.f),
        scaleX(1.f),
        scaleY(1.f)
    {
    }
    Transform(const Transform& value)
    {
        operator=(value);
    }
    ~Transform() {}

    inline void operator=(const Transform& value)
    {
        x = value.x;
        y = value.y;
        skewX = value.skewX;
        skewY = value.skewY;
        scaleX = value.scaleX;
        scaleY = value.scaleY;
    }

    inline Transform& identity()
    {
        x = y = skewX = skewY = 0.f;
        scaleX = scaleY = 1.f;

        return *this;
    }

    inline Transform& add(const Transform& value)
    {
        x += value.x;
        y += value.y;
        skewX += value.skewX;
        skewY += value.skewY;
        scaleX *= value.scaleX;
        scaleY *= value.scaleY;

        return *this;
    }

    inline Transform& minus(const Transform& value)
    {
        x -= value.x;
        y -= value.y;
        skewX = normalizeRadian(skewX - value.skewX);
        skewY = normalizeRadian(skewY - value.skewY);
        scaleX /= value.scaleX;
        scaleY /= value.scaleY;

        return *this;
    }

    inline Transform& fromMatrix(const Matrix& matrix)
    {
        const auto  backupScaleX = scaleX, backupScaleY = scaleY;

        x = matrix.tx;
        y = matrix.ty;

        skewX = std::atan(-matrix.c / matrix.d);
        skewY = std::atan(matrix.b / matrix.a);
        if (skewX != skewX) skewX = 0.f;
        if (skewY != skewY) skewY = 0.f;
        
        scaleY = (skewX > -PI_Q && skewX < PI_Q) ? (matrix.d / std::cos(skewX)) : (-matrix.c / std::sin(skewX));
        scaleX = (skewY > -PI_Q && skewY < PI_Q) ? (matrix.a / std::cos(skewY)) : (matrix.b / std::sin(skewY));

        if (backupScaleX >= 0.f && scaleX < 0.f)
        {
            scaleX = -scaleX;
            skewY = skewY - PI;
        }

        if (backupScaleY >= 0.f && scaleY < 0.f)
        {
            scaleY = -scaleY;
            skewX = skewX - PI;
        }

        return *this;
    }

    inline Transform& toMatrix(Matrix& matrix)
    {
        matrix.a = scaleX * cos(skewY);
        matrix.b = scaleX * sin(skewY);
        matrix.c = -scaleY * sin(skewX);
        matrix.d = scaleY * cos(skewX);
        matrix.tx = x;
        matrix.ty = y;

        return *this;
    }

    inline float getRotation() const
    {
        return skewY;
    }

    inline void setRotation(float value)
    {
        const auto dValue = value - skewY;
        skewX += dValue;
        skewY += dValue;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_TRANSFORM_H