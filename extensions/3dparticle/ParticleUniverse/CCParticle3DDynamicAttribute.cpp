/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCParticle3DDynamicAttribute.h"
#include "base/ccRandom.h"
#include "platform/CCStdC.h"

NS_CC_BEGIN
    //-----------------------------------------------------------------------
    DynamicAttribute::DynamicAttribute (void)
{
}
//-----------------------------------------------------------------------
DynamicAttribute::~DynamicAttribute (void)
{
}
//-----------------------------------------------------------------------
DynamicAttribute::DynamicAttributeType DynamicAttribute::getType (void) const
{
    return _type;
}
//-----------------------------------------------------------------------
void DynamicAttribute::setType (DynamicAttribute::DynamicAttributeType type)
{
    _type = type;
}

//-----------------------------------------------------------------------
DynamicAttributeFixed::DynamicAttributeFixed (void) : _value(0)
{
    _type = DynamicAttribute::DAT_FIXED;
}
//-----------------------------------------------------------------------
DynamicAttributeFixed::DynamicAttributeFixed (const DynamicAttributeFixed& dynamicAttributeFixed)
{
    _type = DynamicAttribute::DAT_FIXED;
    _value = dynamicAttributeFixed._value;
}
//-----------------------------------------------------------------------
DynamicAttributeFixed::~DynamicAttributeFixed (void)
{
}
//-----------------------------------------------------------------------
void DynamicAttributeFixed::setValue (float value)
{
    _value = value;
}
//-----------------------------------------------------------------------
float DynamicAttributeFixed::getValue (float x)
{
    return _value;
}
//-----------------------------------------------------------------------
DynamicAttributeRandom::DynamicAttributeRandom (void) : _min(0), _max(0)
{
    _type = DynamicAttribute::DAT_RANDOM;
}
//-----------------------------------------------------------------------
DynamicAttributeRandom::DynamicAttributeRandom (const DynamicAttributeRandom& dynamicAttributeRandom)
{
    _type = DynamicAttribute::DAT_RANDOM;
    _min = dynamicAttributeRandom._min;
    _max = dynamicAttributeRandom._max;
}
//-----------------------------------------------------------------------
DynamicAttributeRandom::~DynamicAttributeRandom (void)
{
}
//-----------------------------------------------------------------------
float DynamicAttributeRandom::getMin (void) const
{
    return _min;
}
//-----------------------------------------------------------------------
void DynamicAttributeRandom::setMin (float min)
{
    _min = min;
}
//-----------------------------------------------------------------------
float DynamicAttributeRandom::getMax (void) const
{
    return _max;
}
//-----------------------------------------------------------------------
void DynamicAttributeRandom::setMax (float max)
{
    _max = max;
}
//-----------------------------------------------------------------------
void DynamicAttributeRandom::setMinMax (float min, float max)
{
    _min = min;
    _max = max;
}
//-----------------------------------------------------------------------
float DynamicAttributeRandom::getValue (float x)
{
    return cocos2d::random(_min, _max);
}

//-----------------------------------------------------------------------
DynamicAttributeCurved::DynamicAttributeCurved (void) : 
    _interpolationType(IT_LINEAR), 
    _range(0)
{
    _type = DynamicAttribute::DAT_CURVED;
}
//-----------------------------------------------------------------------
DynamicAttributeCurved::DynamicAttributeCurved (InterpolationType interpolationType) : 
    _interpolationType(interpolationType), 
    _range(0)
{
    _type = DynamicAttribute::DAT_CURVED;
}
//-----------------------------------------------------------------------
DynamicAttributeCurved::DynamicAttributeCurved (const DynamicAttributeCurved& dynamicAttributeCurved)
{
    _type = DynamicAttribute::DAT_CURVED;
    _interpolationType = dynamicAttributeCurved._interpolationType;
    _spline = dynamicAttributeCurved._spline;
    _range = dynamicAttributeCurved._range;

    // Copy controlpoints
    DynamicAttributeCurved::ControlPointList::const_iterator it; // Need const_iterator here!
    DynamicAttributeCurved::ControlPointList::const_iterator itEnd = dynamicAttributeCurved._controlPoints.end();
    for (it = dynamicAttributeCurved._controlPoints.begin(); it != itEnd; ++it)
    {
        Vec2 controlPoint = *it;
        _controlPoints.push_back (controlPoint);
    }
    processControlPoints();
}
//-----------------------------------------------------------------------
DynamicAttributeCurved::~DynamicAttributeCurved (void)
{
}
//-----------------------------------------------------------------------
void DynamicAttributeCurved::setInterpolationType (InterpolationType interpolationType)
{
    if (interpolationType != _interpolationType)
    {
        // If switched to another InterpolationType, the already existing ControlPoints will be removed.
        removeAllControlPoints();
        _interpolationType = interpolationType;
    }
}
//-----------------------------------------------------------------------
InterpolationType DynamicAttributeCurved::getInterpolationType (void) const
{
    return _interpolationType;
}
//-----------------------------------------------------------------------
float DynamicAttributeCurved::getValue (float x)
{
    switch (_interpolationType)
    {
    case IT_LINEAR:
        {
            // Search the interval in which 'x' resides and apply linear interpolation
            if (_controlPoints.empty())
                return 0;

            ControlPointList::iterator it1 = findNearestControlPointIterator(x);
            ControlPointList::iterator it2 = it1 + 1;
            if (it2 != _controlPoints.end())
            {
                // Calculate fraction: y = y1 + ((y2 - y1) * (x - x1)/(x2 - x1))
                return (*it1).y + (((*it2).y - (*it1).y) * (x - (*it1).x)/((*it2).x - (*it1).x));
            }
            else
            {
                return (*it1).y;
            }
        }
        break;

    case IT_SPLINE:
        {
            // Fit using spline
            if (_spline.getNumPoints() < 1)
                return 0;

            float fraction = x / _range;
            return (_spline.interpolate(fraction < 1.0f ? fraction : 1.0f)).y;
        }
        break;
    }

    return 0;
}
//-----------------------------------------------------------------------
void DynamicAttributeCurved::addControlPoint (float x, float y)
{
    _controlPoints.push_back(Vec2(x, y));
}
//-----------------------------------------------------------------------
const DynamicAttributeCurved::ControlPointList& DynamicAttributeCurved::getControlPoints (void) const
{
    return _controlPoints;
}
//-----------------------------------------------------------------------
void DynamicAttributeCurved::processControlPoints(void)
{
    if (_controlPoints.empty())
        return;

    std::sort(_controlPoints.begin(), _controlPoints.end(), ControlPointSorter());
    _range = (*getLastValidIterator()).x - (*getFirstValidIterator()).x;

    if (_interpolationType == IT_SPLINE)
    {
        // Add all sorted control points to the spline
        DynamicAttributeCurved::ControlPointList::iterator it;
        _spline.clear();
        for (it = _controlPoints.begin(); it != _controlPoints.end(); ++it)
            _spline.addPoint(Vec3((*it).x, (*it).y, 0));
    }
}
//-----------------------------------------------------------------------
size_t DynamicAttributeCurved::getNumControlPoints(void) const
{
    return _controlPoints.size();
}
//-----------------------------------------------------------------------
void DynamicAttributeCurved::removeAllControlPoints(void)
{
    _controlPoints.clear();
}
//-----------------------------------------------------------------------
DynamicAttributeCurved::ControlPointList::iterator DynamicAttributeCurved::findNearestControlPointIterator(float x)
{
    // Assume that the ControlPointList is not empty
    ControlPointList::iterator it;
    ControlPointList::iterator itEnd = _controlPoints.end();
    for (it = _controlPoints.begin(); it != itEnd; ++it)
    {
        if (x < (*it).x)
        {
            if (it == _controlPoints.begin())
                return it;
            else
                return --it;
        }
    }

    // If not found return the last valid iterator
    return --it;
}
//-----------------------------------------------------------------------
DynamicAttributeCurved::ControlPointList::iterator DynamicAttributeCurved::getFirstValidIterator(void)
{
    return _controlPoints.begin();
}
//-----------------------------------------------------------------------
DynamicAttributeCurved::ControlPointList::iterator DynamicAttributeCurved::getLastValidIterator(void)
{
    return _controlPoints.end() - 1;
}

//-----------------------------------------------------------------------
DynamicAttributeOscillate::DynamicAttributeOscillate (void) :
    _oscillationType(DynamicAttributeOscillate::OSCT_SINE),
    _frequency(1.0f),
    _phase(0.0f),
    _base(0.0f),
    _amplitude(1.0f)
{
    _type = DynamicAttribute::DAT_OSCILLATE;
}
//-----------------------------------------------------------------------
DynamicAttributeOscillate::DynamicAttributeOscillate (const DynamicAttributeOscillate& dynamicAttributeOscillate)
{
    _type = DynamicAttribute::DAT_OSCILLATE;
}
//-----------------------------------------------------------------------
DynamicAttributeOscillate::~DynamicAttributeOscillate (void)
{
}
//-----------------------------------------------------------------------
DynamicAttributeOscillate::OscillationType DynamicAttributeOscillate::getOscillationType (void) const
{
    return _oscillationType;
}
//-----------------------------------------------------------------------
void DynamicAttributeOscillate::setOscillationType (DynamicAttributeOscillate::OscillationType oscillationType)
{
    _oscillationType = oscillationType;
}
//-----------------------------------------------------------------------
float DynamicAttributeOscillate::getFrequency (void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void DynamicAttributeOscillate::setFrequency (float frequency)
{
    _frequency = frequency;
}
//-----------------------------------------------------------------------
float DynamicAttributeOscillate::getPhase (void) const
{
    return _phase;
}
//-----------------------------------------------------------------------
void DynamicAttributeOscillate::setPhase (float phase)
{
    _phase = phase;
}
//-----------------------------------------------------------------------
float DynamicAttributeOscillate::getBase (void) const
{
    return _base;
}
//-----------------------------------------------------------------------
void DynamicAttributeOscillate::setBase (float base)
{
    _base = base;
}
//-----------------------------------------------------------------------
float DynamicAttributeOscillate::getAmplitude (void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void DynamicAttributeOscillate::setAmplitude (float amplitude)
{
    _amplitude = amplitude;
}
//-----------------------------------------------------------------------
float DynamicAttributeOscillate::getValue (float x)
{
    switch (_oscillationType)
    {
    case OSCT_SINE:
        {
            return _base + _amplitude * sin(_phase + _frequency * x * M_PI * 2.0f);
        }
        break;
    case OSCT_SQUARE:
        {
            float val = sin(_phase + _frequency * x * M_PI * 2.0f);
            if (abs(val) < 0.00001f)
                val = val >0? 1: -1;
            return _base + _amplitude * val;
        }
        break;
    }

    return 0;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
float DynamicAttributeHelper::calculate(DynamicAttribute* dyn, float x, float defaultValue)
{
    if (dyn)
    {
        return dyn->getValue(x);
    }

    return defaultValue;
}
NS_CC_END
