//
//  MathUtilty.cpp
//  
//
//  
//
//
#include "Math.h"

namespace cocos2d
{
    
    
MathUtility::MathUtility(): _costab(NULL), _sintab(NULL)
{
}

MathUtility::~MathUtility()
{
    delete[] _costab;
    delete[] _sintab;
        
}

MathUtility& MathUtility::getInstance()
{
    static MathUtility instance;
    return instance;
}



// approximate value of sin(rad), precision 1 degree
float MathUtility::sin(float rad, bool isUseTable)
{
    if (isUseTable)
    {
        initMathUtility();
            
        int degree = rad2degree(rad);
            
        return _sintab[degree];
    }

    return sinf(rad);
}

// approximate value of sin(rad), precision 1 degree
float MathUtility::cos(float rad, bool isUseTable)
{
    if (isUseTable)
    {
        initMathUtility();
        
        int degree = rad2degree(rad);
        
        return _costab[degree];
    }
    return cosf(rad);
}
    
int MathUtility::rad2degree(float rad)
{
    int degree = (int)(MATH_RAD_TO_DEG(rad) + 0.5f);
    if (degree >= 360 || degree <= -360)
    {
        degree = degree % 360;
    }
    if (degree < 0)
        degree += 360;
	
    return degree;
}
    
void MathUtility::sincos(float rad, float *sinvalue, float* cosvalue, bool isUseTable)
{
    if (isUseTable)
    {
        initMathUtility();
        
        int degree = rad2degree(rad);
        
        
        if (sinvalue)
            *sinvalue = _sintab[degree];
        if (cosvalue)
            *cosvalue = _costab[degree];
    }
    else
    {
        if (sinvalue)
            *sinvalue = sinf(rad);
        if (cosvalue)
            *cosvalue = cosf(rad);
    }
}

void MathUtility::initMathUtility()
{
    
    if (_sintab && _costab)
        return;
    
    delete[] _sintab;
    delete[] _costab;
    
    const int count = 360;
    _costab = new float[count];
    _sintab = new float[count];
    
    for (int i = 0; i < count; i++) {
        float rad = MATH_DEG_TO_RAD(i);
        _sintab[i] = sinf(rad);
        _costab[i] = cosf(rad);
    }
}

}