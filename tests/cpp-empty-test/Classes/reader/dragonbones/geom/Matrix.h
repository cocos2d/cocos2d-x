#ifndef DRAGONBONES_MATRIX_H
#define DRAGONBONES_MATRIX_H

#include "../core/DragonBones.h"
#include "Point.h"

DRAGONBONES_NAMESPACE_BEGIN

class Matrix final
{
public:
    float a;
    float b;
    float c;
    float d;
    float tx;
    float ty;

    Matrix():
        a(1.f),
        b(0.f),
        c(0.f),
        d(1.f),
        tx(0.f),
        ty(0.f)
    {
    }
    Matrix(const Matrix& value)
    {
        operator=(value);
    }
    ~Matrix() {}

    inline void operator=(const Matrix& value)
    {
        a = value.a;
        b = value.b;
        c = value.c;
        d = value.d;
        tx = value.tx;
        ty = value.ty;
    }

    inline void identity()
    {
        a = d = 1.f;
        b = c = 0.f;
        tx = ty = 0.f;
    }

    inline void concat(const Matrix& value)
    {
        const auto aA = a;
        const auto bA = b;
        const auto cA = c;
        const auto dA = d;
        const auto txA = tx;
        const auto tyA = ty;
        const auto aB = value.a;
        const auto bB = value.b;
        const auto cB = value.c;
        const auto dB = value.d;
        const auto txB = value.tx;
        const auto tyB = value.ty;

        a = aA * aB + bA * cB;
        b = aA * bB + bA * dB;
        c = cA * aB + dA * cB;
        d = cA * bB + dA * dB;
        tx = aB * txA + cB * tyA + txB;
        ty = dB * tyA + bB * txA + tyB;
    }

    inline void invert() 
    {
        const auto aA = a;
        const auto bA = b;
        const auto cA = c;
        const auto dA = d;
        const auto txA = tx;
        const auto tyA = ty;
        const auto n = aA * dA - bA * cA;

        a = dA / n;
        b = -bA / n;
        c = -cA / n;
        d = aA / n;
        tx = (cA * tyA - dA * txA) / n;
        ty = -(aA * tyA - bA * txA) / n;
    }

    inline void transformPoint(float x, float y, Point& result, bool delta = false) const
    {
        result.x = a * x + c * y;
        result.y = b * x + d * y;

        if (!delta)
        {
            result.x += tx;
            result.y += ty;
        }
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_MATRIX_H