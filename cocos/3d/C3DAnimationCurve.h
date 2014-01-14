#ifndef CURVE_H_
#define CURVE_H_

#include <vector>
#include <map>
#include <string>
#include "cocos2d.h"
namespace cocos2d
{

/**
 * Represents an n-dimensional curve.
 */
class C3DAnimationCurve : public cocos2d::CCObject
{
    friend class C3DAnimation;
    friend class C3DAnimationClip;   
    friend class C3DMeshSkin;
    friend class C3DAnimationCurveMgr;
    friend class C3DAnimationChannel;

public:
    /**
    * creates C3DAnimationCurve.
    */
    static C3DAnimationCurve* create(unsigned int pointCount, unsigned int componentCount);

    /**
    * get point count.
    */
    unsigned int getPointCount() const;

    /**
    * get component count.
    */
    unsigned int getComponentCount() const;

    /**
    * get start time.
    */
    float getStartTime() const;

    /**
    * get end time.
    */
    float getEndTime() const;

    /**
    * get druation time.
    */
    unsigned long getDruationTime() const { return _dur; }

    /**
    * set point to point list.
    */
    void setPoint(unsigned int index, float time, float* value);

    /**
    * interpolate evaluate by time.
    */
    void evaluate(float time, float* dst) const;

    /**
    * lerp.
    */
    static float lerp(float t, float from, float to);

private:

    /**
     * Defines a single point within a curve.
     */
    class Point
    {
    public:

        float time;

        float* value;

        Point();

        ~Point();
    };

    /**
     * Constructor.
     */
    C3DAnimationCurve();

    /**
     * Constructor.
     */
    C3DAnimationCurve(unsigned int pointCount, unsigned int componentCount);

    /**
     * Destructor.
     */
    ~C3DAnimationCurve();

    /**
     * Interpolate by Linear.
     */
    void interpolateLinear(float t, Point* from, Point* to, float* dst) const;

    /**
     * Interpolate by Quaternion.
     */
    void interpolateQuaternion(float s, float* from, float* to, float* dst) const;
    
    /**
     * Determine index by time.
     */
    int determineIndex(float time) const;

    unsigned int _pointCount;           // Number of points on the curve.
    unsigned int _componentCount;       // Number of components on the curve.
    unsigned int _componentSize;        // The component size (in bytes).

    Point* _points;                     // The points on the curve.
    
    unsigned long _dur;                          //  duration of the animation curve, ms
};

    /**
    * animation curve manager
    */
    class C3DAnimationCurveMgr
    {
    public:
        typedef std::map<std::string, C3DAnimationCurve*> CurveMap;//boneId, animation curve for this bone
        typedef std::map<std::string, CurveMap* > CurvesMap;//animation path, animation curve collection
        
        
        /**
         * get the share AnimationCurveMgr.
         */
        static C3DAnimationCurveMgr* sharedAnimationCurveMgr();
        
        /**
         * get the AnimationCurve.
         */
        const C3DAnimationCurve* getAnimationCurve(const char* path, const char* boneId);
        CurveMap* getAnimationCurves(const char* path);
        
        /**
         * C3DAnimationCurve auto add, should release outside if not used.
         */
        void addAnimationCurve(const char* path, const char* boneId, C3DAnimationCurve* curve);
        void addAnimationCurves(const char* path, CurveMap* curves);
        
        /**
         * create the CurveMap.
         */
        CurveMap* createAnimationCurves(const char* path);
        
        /**
         * remove target animation curve.
         */
        void removeAnimationCurve(const char* path, const char* boneId);
        void removeAnimationCurves(const char* path);
        
        /**
         * create aniamation curve.
         */
        static C3DAnimationCurve* createAniamationCurve(unsigned int keyCount, unsigned long* keyTimes, float* keyValues);
        
    protected:
        static C3DAnimationCurveMgr* _instance;
        
        /**
         * Constructor.
         */
        C3DAnimationCurveMgr();

        /**
         * Destructor.
         */
        virtual ~C3DAnimationCurveMgr();
        
        
        //attribute
        //map key animation file path, value curves
        CurvesMap _curves;
    };

}


#endif
