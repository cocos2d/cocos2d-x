//
//  C3DMathUtilty.h
//  
//
//  utitlity function, such as approximate sin, cos, more fast less accuate, can be used by particle system
//
//

#ifndef __C3DUtilty__
#define __C3DUtilty__



namespace cocos2d
{

class MathUtility
{
public:
    ~MathUtility();
    
    static MathUtility& getInstance();
    
    /**
     * approximate value of sin(rad), precision 1 degree
     *
     * @param rad to retreive.
     * @param isUseTable use look up table retrive sin value.
     */
    float sin(float rad, bool isUseTable = false);
    
    /**
     * approximate value of cos(rad), precision 1 degree
     *
     * @param rad to retreive.
     * @param isUseTable use look up table retrive sin value.
     */
    float cos(float rad, bool isUseTable = false);
    
    /**
     * approximate value of cos(rad), precision 1 degree
     *
     * @param rad to retreive.
     * @param sinvalue to receive sin value
     * @param cosvalue to receive cos value
     * @param isUseTable use look up table retrive sin value.
     */
    void sincos(float rad, float *sinvalue, float* cosvalue, bool isUseTable = false);

    
private:
    MathUtility();
    
    void initMathUtility();
    
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
