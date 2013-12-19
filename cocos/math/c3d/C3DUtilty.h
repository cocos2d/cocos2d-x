//
//  C3DUtilty.h
//  
//
//  utitlity function, such as approximate sin, cos
//
//

#ifndef __C3DUtilty__
#define __C3DUtilty__

#include <iostream>

namespace cocos3d
{

class C3DUtility
{
public:
    ~C3DUtility();
    
    static C3DUtility& getInstance();
    
    /**
     * approximate value of sin(rad), precision 1 degree
     *
     * @param rad to retreive.
     */
    float sin(float rad);
    
    /**
     * approximate value of cos(rad), precision 1 degree
     *
     * @param rad to retreive.
     */
    float cos(float rad);
    
    /**
     * approximate value of cos(rad), precision 1 degree
     *
     * @param rad to retreive.
     * @param sinvalue to receive sin value
     * @param cosvalue to receive cos value
     */
    void sincos(float rad, float *sinvalue, float* cosvalue);
    
private:
    C3DUtility();
    
    void initUtility();
    
    /**
     * convert rad to degree
     *
     * @param rad to retreive.
     * @return degree [0, 360)
     */
    int rad2degree(float rad);
    
    float *_costab;
    float *_sintab;
    
};

}
#endif /* defined(__C3DUtilty__) */
