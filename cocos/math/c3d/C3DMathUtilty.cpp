//
//  C3DMathUtilty.cpp
//  
//
//  
//
//

#include "C3DMath.h"

namespace cocos3d
{

C3DMathUtility::~C3DMathUtility()
{
    delete[] _costab;
    delete[] _sintab;
        
}

C3DMathUtility& C3DMathUtility::getInstance()
{
    static C3DMathUtility instance;
    return instance;
}


C3DMathUtility::C3DMathUtility(): _costab(NULL), _sintab(NULL)
{

}

// approximate value of sin(rad), precision 1 degree
float C3DMathUtility::sin(float rad, bool bUseTable)
{
    if (bUseTable)
    {
        initMathUtility();
        
        int degree = rad2degree(rad);
        
        return _sintab[degree];
    }

    return sinf(rad);
}

// approximate value of sin(rad), precision 1 degree
float C3DMathUtility::cos(float rad, bool bUseTable)
{
    if (bUseTable)
    {
        initMathUtility();
        
        int degree = rad2degree(rad);
        
        return _costab[degree];
    }
    return cosf(rad);
}
    
int C3DMathUtility::rad2degree(float rad)
{
    int degree = (int)((rad) + 0.5f);
    if (degree >= 360 || degree <= -360)
    {
        degree = degree % 360;
    }
    if (degree < 0)
        degree += 360;
	
    return degree;
}
    
void C3DMathUtility::sincos(float rad, float *sinvalue, float* cosvalue, bool bUseTable)
{
    if (bUseTable)
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

void C3DMathUtility::initMathUtility()
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