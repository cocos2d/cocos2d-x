//
//  C3DUtilty.cpp
//  test3D
//
//  Created by ck04-040 on 13-8-5.
//
//

#include "Base.h"
#include "C3DUtilty.h"

namespace cocos3d
{

C3DUtility::~C3DUtility()
{
    SAFE_DELETE_ARRAY(_costab);
    SAFE_DELETE_ARRAY(_sintab);
        
}

C3DUtility& C3DUtility::getInstance()
{
    static C3DUtility instance;
    return instance;
}


C3DUtility::C3DUtility()
{
    _costab = NULL;
    _sintab = NULL;
    
    initUtility();
}

// approximate value of sin(rad), precision 1 degree
float C3DUtility::sin(float rad)
{
    int degree = rad2degree(rad);
    
    return _sintab[degree];
}

// approximate value of sin(rad), precision 1 degree
float C3DUtility::cos(float rad)
{
    int degree = rad2degree(rad);
    
    return _costab[degree];
}
    
int C3DUtility::rad2degree(float rad)
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
    
void C3DUtility::sincos(float rad, float *sinvalue, float* cosvalue)
{
    int degree = rad2degree(rad);
    
    
    if (sinvalue)
        *sinvalue = _sintab[degree];
    if (cosvalue)
        *cosvalue = _costab[degree];
}

void C3DUtility::initUtility()
{
    
    SAFE_DELETE_ARRAY(_costab);
    SAFE_DELETE_ARRAY(_sintab);
    
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