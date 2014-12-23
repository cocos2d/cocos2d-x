#include "3d/CCAnimationCurve.h"
NS_CC_BEGIN

template <int componentSize>
void AnimationCurve<componentSize>::evaluate(float time, float* dst, EvaluateType type) const
{
    if (_count == 1 || time <= _keytime[0])
    {
        memcpy(dst, _value, _componentSizeByte);
        return;
    }
    else if (time >= _keytime[_count - 1])
    {
        memcpy(dst, &_value[(_count - 1) * componentSize], _componentSizeByte);
        return;
    }
    
    unsigned int index = determineIndex(time);
    
    float scale = (_keytime[index + 1] - _keytime[index]);
    float t = (time - _keytime[index]) / scale;
    
    float* fromValue = &_value[index * componentSize];
    float* toValue = fromValue + componentSize;
    
    switch (type) {
        case EvaluateType::INT_LINEAR:
        {
            for (auto i = 0; i < componentSize; i++) {
                dst[i] = fromValue[i] + (toValue[i] - fromValue[i]) * t;
            }
        }
        break;
        case EvaluateType::INT_NEAR:
        {
            float* src = t > 0.5f ? toValue : fromValue;
            memcpy(dst, src, _componentSizeByte);
        }
        break;
        case EvaluateType::INT_QUAT_SLERP:
        {
            // Evaluate.
            Quaternion quat;
            if (t >= 0)
                Quaternion::slerp(Quaternion(fromValue), Quaternion(toValue), t, &quat);
            else
                Quaternion::slerp(Quaternion(toValue), Quaternion(fromValue), t, &quat);
            
            dst[0] = quat.x, dst[1] = quat.y, dst[2] = quat.z, dst[3] = quat.w;
        }
        break;
        case EvaluateType::INT_USER_FUNCTION:
        {
            if (_evaluateFun)
                _evaluateFun(time, dst);
        }
        break;
            
        default:
            break;
    }
}

template <int componentSize>
void AnimationCurve<componentSize>::setEvaluateFun(std::function<void(float time, float* dst)> fun)
{
    _evaluateFun = fun;
}

//create animation curve
template <int componentSize>
AnimationCurve<componentSize>* AnimationCurve<componentSize>::create(float* keytime, float* value, int count)
{
    int floatSize = sizeof(float);
    AnimationCurve* curve = new (std::nothrow) AnimationCurve();
    curve->_keytime = new float[count];
    memcpy(curve->_keytime, keytime, count * floatSize);
    
    int compoentSizeByte = componentSize * floatSize;
    int totalByte = count * compoentSizeByte;
    curve->_value = new float[totalByte / floatSize];
    memcpy(curve->_value, value, totalByte);
    
    curve->_count = count;
    curve->_componentSizeByte = compoentSizeByte;
    
    curve->autorelease();
    return curve;
}

template <int componentSize>
float AnimationCurve<componentSize>::getStartTime() const
{
    return _keytime[0];
}

template <int componentSize>
float AnimationCurve<componentSize>::getEndTime() const
{
    return _keytime[_count - 1];
}


template <int componentSize>
AnimationCurve<componentSize>::AnimationCurve()
: _value(nullptr)
, _keytime(nullptr)
, _count(0)
, _componentSizeByte(0)
, _evaluateFun(nullptr)
{
    
}
template <int componentSize>
AnimationCurve<componentSize>::~AnimationCurve()
{
    CC_SAFE_DELETE(_keytime);
    CC_SAFE_DELETE(_value);
}

template <int componentSize>
int AnimationCurve<componentSize>::determineIndex(float time) const
{
    unsigned int min = 0;
    unsigned int max = _count - 1;
    unsigned int mid = 0;
    
    do
    {
        mid = (min + max) >> 1;
        
        if (time >= _keytime[mid] && time <= _keytime[mid + 1])
            return mid;
        else if (time < _keytime[mid])
            max = mid - 1;
        else
            min = mid + 1;
    } while (min <= max);
    
    // We should never hit this!
    return -1;
}

NS_CC_END