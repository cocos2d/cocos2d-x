#include "C3DAnimationCurve.h"
#include "CocosMath.h"
#include "Base.h"


#ifndef NULL
#define NULL 0
#endif

#ifndef MATH_PI
#define MATH_PI 3.14159265358979323846f
#endif

#ifndef MATH_PIOVER2 
#define MATH_PIOVER2 1.57079632679489661923f
#endif

#ifndef MATH_PIX2
#define MATH_PIX2 6.28318530717958647693f
#endif

// Object deletion macro
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) \
    if (x) \
    { \
        delete x; \
        x = nullptr; \
    }
#endif

// Array deletion macro
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) \
    if (x) \
    { \
        delete[] x; \
        x = nullptr; \
    }
#endif


namespace cocos2d
{

C3DAnimationCurve* C3DAnimationCurve::create(unsigned int pointCount, unsigned int componentCount)
{
    return new C3DAnimationCurve(pointCount, componentCount);
}

C3DAnimationCurve::C3DAnimationCurve(unsigned int pointCount, unsigned int componentCount)
    : _pointCount(pointCount), _componentCount(componentCount), _componentSize(sizeof(float)*componentCount),  _points(nullptr), _dur(0)
{
    _points = new Point[_pointCount];
    for (unsigned int i = 0; i < _pointCount; i++)
    {
        _points[i].time = 0.0f;
        _points[i].value = new float[_componentCount];

    }
    _points[_pointCount - 1].time = 1.0f;
}

C3DAnimationCurve::~C3DAnimationCurve()
{
    for (unsigned int i = 0; i < _pointCount; i++) {
        SAFE_DELETE_ARRAY(_points[i].value);
    }
    SAFE_DELETE_ARRAY(_points);

}

C3DAnimationCurve::Point::Point()
    : time(0.0f), value(nullptr)
{
}

C3DAnimationCurve::Point::~Point()
{
    SAFE_DELETE_ARRAY(value);

}

unsigned int C3DAnimationCurve::getPointCount() const
{
    return _pointCount;
}

unsigned int C3DAnimationCurve::getComponentCount() const
{
    return _componentCount;
}

float C3DAnimationCurve::getStartTime() const
{
    return _points[0].time;
}

float C3DAnimationCurve::getEndTime() const
{
    return _points[_pointCount-1].time;
}


void C3DAnimationCurve::setPoint(unsigned int index, float time, float* value)
{
    //assert(index < _pointCount && time >= 0.0f && time <= 1.0f && !(index == 0 && time != 0.0f) && !(_pointCount != 1 && index == _pointCount - 1 && time != 1.0f));

    _points[index].time = time;


    if (value)
        memcpy(_points[index].value, value, _componentSize);


}


void C3DAnimationCurve::evaluate(float time, float* dst) const
{
    assert(dst && time >= 0 && time <= 1.0f);

    if (_pointCount == 1 || time <= _points[0].time)
    {
        memcpy(dst, _points[0].value, _componentSize);
        return;
    }
    else if (time >= _points[_pointCount - 1].time)
    {
        memcpy(dst, _points[_pointCount - 1].value, _componentSize);
        return;
    }

    unsigned int index = determineIndex(time);
    
    Point* from = _points + index;
    Point* to = _points + (index + 1);

    float scale = (to->time - from->time);
    float t = (time - from->time) / scale;


    interpolateLinear(t, from, to, dst);
}

float C3DAnimationCurve::lerp(float t, float from, float to)
{
    return from + (to-from) * t;
}


void C3DAnimationCurve::interpolateLinear(float t, Point* from, Point* to, float* dst) const
{
    float* fromValue = from->value;
    float* toValue = to->value;

    unsigned int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (fromValue[i] == toValue[i])
            dst[i] = fromValue[i];
        else
            dst[i] = fromValue[i] + (toValue[i] - fromValue[i]) * t;
    }


    interpolateQuaternion(t, (fromValue + i), (toValue + i), (dst + i));
        
    for (i += 4; i < _componentCount; i++)
    {
        if (fromValue[i] == toValue[i])
            dst[i] = fromValue[i];
        else
            dst[i] = fromValue[i] + (toValue[i] - fromValue[i]) * t;
    }
    
}

void C3DAnimationCurve::interpolateQuaternion(float t, float* from, float* to, float* dst) const
{
    // Evaluate.
    if (t >= 0)
    {
        Quaternion::slerp(from[0], from[1], from[2], from[3], to[0], to[1], to[2], to[3], t, dst, dst + 1, dst + 2, dst + 3);
    }
    else
        Quaternion::slerp(to[0], to[1], to[2], to[3], from[0], from[1], from[2], from[3], t, dst, dst + 1, dst + 2, dst + 3);

    //((Quaternion*) dst)->normalize();
}

int C3DAnimationCurve::determineIndex(float time) const
{
    unsigned int min = 0;
    unsigned int max = _pointCount - 1;
    unsigned int mid = 0;

    do 
    {
        mid = (min + max) >> 1;

        if (time >= _points[mid].time && time <= _points[mid + 1].time)
            return mid;
        else if (time < _points[mid].time)
            max = mid - 1;
        else
            min = mid + 1;
    } while (min <= max);
    
    // We should never hit this!
    return -1;
}


    ///////////////////implementation of animation manager////////////
    
    C3DAnimationCurveMgr* C3DAnimationCurveMgr::_instance = nullptr;
    C3DAnimationCurveMgr::C3DAnimationCurveMgr()
    {
    }
    C3DAnimationCurveMgr::~C3DAnimationCurveMgr()
    {
        for (CurvesMap::iterator it = _curves.begin(); it != _curves.end(); it++)
        {
           // removeAnimationCurves(it->first.c_str() );
            CurveMap* curvemap = it->second;
            for (CurveMap::iterator itor = curvemap->begin(); itor != curvemap->end(); itor++) {
                itor->second->release();
            }
            
            curvemap->clear();
            delete curvemap;
        }
        _curves.clear();
    }
    
    C3DAnimationCurveMgr* C3DAnimationCurveMgr::sharedAnimationCurveMgr()
    {
        if (_instance == nullptr)
        {
            static C3DAnimationCurveMgr mgr;
            _instance = &mgr;
        }
        
        return _instance;
    }
    
    const C3DAnimationCurve* C3DAnimationCurveMgr::getAnimationCurve(const char* path, const char* boneId)
    {
        CurvesMap::iterator it = _curves.find(path);
        if (it != _curves.end())
        {
            CurveMap* curvemap = it->second;
            CurveMap::iterator itor = curvemap->find(boneId);
            if (itor != curvemap->end())
                return itor->second;
        }
        
        return nullptr;
    }
    C3DAnimationCurveMgr::CurveMap* C3DAnimationCurveMgr::getAnimationCurves(const char* path)
    {
        CurvesMap::iterator it = _curves.find(path);
        if (it != _curves.end())
        {
            return it->second;
        }
        return nullptr;
    }
    void C3DAnimationCurveMgr::addAnimationCurve(const char* path, const char* boneId, C3DAnimationCurve* curve)
    {
        CurveMap* &curvemap = _curves[path];
        if (curvemap == nullptr)
            curvemap = new CurveMap();
        
        curve->retain();
        curvemap->insert(std::pair<std::string, C3DAnimationCurve*>(boneId, curve) );
        
    }
    void C3DAnimationCurveMgr::addAnimationCurves(const char* path, CurveMap* curvemap)
    {
        removeAnimationCurves(path);
        _curves.insert(std::pair<std::string, CurveMap*>(path, curvemap) );
        for (CurveMap::iterator itor = curvemap->begin(); itor != curvemap->end(); itor++) {
            itor->second->retain();
        }
        
    }
    C3DAnimationCurveMgr::CurveMap* C3DAnimationCurveMgr::createAnimationCurves(const char* path)
    {
        removeAnimationCurves(path);
        CurveMap* curvemap = new CurveMap();
        _curves.insert(std::pair<std::string, CurveMap*>(path, curvemap) );
        return curvemap;
    }
    void C3DAnimationCurveMgr::removeAnimationCurve(const char* path, const char* boneId)
    {
        CurvesMap::iterator it = _curves.find(path);
        if (it != _curves.end())
        {
            CurveMap* curvemap = it->second;
            CurveMap::iterator itor = curvemap->find(boneId);
            if (itor != curvemap->end())
            {
                itor->second->release();
                curvemap->erase(itor);
            }
        }
    }
    void C3DAnimationCurveMgr::removeAnimationCurves(const char* path)
    {
        CurvesMap::iterator it1 = _curves.find(path);
        if (it1 != _curves.end())
        {
            CurveMap* curvemap = it1->second;
            for (CurveMap::iterator itor = curvemap->begin(); itor != curvemap->end(); itor++) {
                itor->second->release();
            }
            _curves.erase(it1);
        }
    }
    
    C3DAnimationCurve* C3DAnimationCurveMgr::createAniamationCurve(unsigned int keyCount, unsigned long* keyTimes, float* keyValues)
    {
        C3DAnimationCurve* curve = C3DAnimationCurve::create(keyCount, 10);
        
        
        unsigned long lowest = keyTimes[0];
        unsigned long duration = keyTimes[keyCount-1] - lowest;
        
        float keytime;
        
        keytime = 0.0f;
        curve->setPoint(0, keytime, keyValues);
        
        unsigned int pointOffset = 10;
        unsigned int i = 1;
        for (; i < keyCount - 1; i++)
        {
            keytime = (float) (keyTimes[i] - lowest) / (float) duration;
            curve->setPoint(i, keytime, (keyValues + pointOffset));
            pointOffset += 10;
        }
        i = keyCount - 1;
        keytime = 1.0f;
        curve->setPoint(i, keytime, keyValues + pointOffset);
        
        curve->_dur = duration;
        
        return curve;
    }

}
