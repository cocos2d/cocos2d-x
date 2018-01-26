/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPUDynamicAttribute.h"
#include "base/ccRandom.h"
#include "platform/CCStdC.h"

NS_CC_BEGIN
    //-----------------------------------------------------------------------
    PUDynamicAttribute::PUDynamicAttribute (void)
{
}
//-----------------------------------------------------------------------
PUDynamicAttribute::~PUDynamicAttribute (void)
{
}
//-----------------------------------------------------------------------
PUDynamicAttribute::DynamicAttributeType PUDynamicAttribute::getType (void) const
{
    return _type;
}
//-----------------------------------------------------------------------
void PUDynamicAttribute::setType (PUDynamicAttribute::DynamicAttributeType type)
{
    _type = type;
}

//-----------------------------------------------------------------------
PUDynamicAttributeFixed::PUDynamicAttributeFixed (void) : _value(0)
{
    _type = PUDynamicAttribute::DAT_FIXED;
}
//-----------------------------------------------------------------------
PUDynamicAttributeFixed::PUDynamicAttributeFixed (const PUDynamicAttributeFixed& dynamicAttributeFixed)
{
    _type = PUDynamicAttribute::DAT_FIXED;
    _value = dynamicAttributeFixed._value;
}
//-----------------------------------------------------------------------
PUDynamicAttributeFixed::~PUDynamicAttributeFixed (void)
{
}
//-----------------------------------------------------------------------
void PUDynamicAttributeFixed::setValue (float value)
{
    _value = value;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeFixed::getValue (float /*x*/)
{
    return _value;
}

void PUDynamicAttributeFixed::copyAttributesTo( PUDynamicAttribute* dynamicAttribute )
{
    if (!dynamicAttribute || dynamicAttribute->getType() != PUDynamicAttribute::DAT_FIXED)
        return;

    PUDynamicAttributeFixed* dynAttr = static_cast<PUDynamicAttributeFixed*>(dynamicAttribute);
    dynAttr->_value = _value;
}

PUDynamicAttributeFixed* PUDynamicAttributeFixed::clone()
{
    auto af = new (std::nothrow) PUDynamicAttributeFixed();
    this->copyAttributesTo(af);
    return af;
}

//-----------------------------------------------------------------------
PUDynamicAttributeRandom::PUDynamicAttributeRandom (void) : _min(0), _max(0)
{
    _type = PUDynamicAttribute::DAT_RANDOM;
}
//-----------------------------------------------------------------------
PUDynamicAttributeRandom::PUDynamicAttributeRandom (const PUDynamicAttributeRandom& dynamicAttributeRandom)
{
    _type = PUDynamicAttribute::DAT_RANDOM;
    _min = dynamicAttributeRandom._min;
    _max = dynamicAttributeRandom._max;
}
//-----------------------------------------------------------------------
PUDynamicAttributeRandom::~PUDynamicAttributeRandom (void)
{
}
//-----------------------------------------------------------------------
float PUDynamicAttributeRandom::getMin (void) const
{
    return _min;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeRandom::setMin (float min)
{
    _min = min;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeRandom::getMax (void) const
{
    return _max;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeRandom::setMax (float max)
{
    _max = max;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeRandom::setMinMax (float min, float max)
{
    _min = min;
    _max = max;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeRandom::getValue (float /*x*/)
{
    return cocos2d::random(_min, _max);
}

void PUDynamicAttributeRandom::copyAttributesTo( PUDynamicAttribute* dynamicAttribute )
{
    if (!dynamicAttribute || dynamicAttribute->getType() != PUDynamicAttribute::DAT_RANDOM)
        return;

    PUDynamicAttributeRandom* dynAttr = static_cast<PUDynamicAttributeRandom*>(dynamicAttribute);
    dynAttr->_min = _min;
    dynAttr->_max = _max;
}

PUDynamicAttributeRandom* PUDynamicAttributeRandom::clone()
{
    auto ar = new (std::nothrow) PUDynamicAttributeRandom();
    this->copyAttributesTo(ar);
    return ar;
}

//-----------------------------------------------------------------------
PUDynamicAttributeCurved::PUDynamicAttributeCurved (void) : 
	_range(0),
	_interpolationType(IT_LINEAR)
{
    _type = PUDynamicAttribute::DAT_CURVED;
}
//-----------------------------------------------------------------------
PUDynamicAttributeCurved::PUDynamicAttributeCurved (PUInterpolationType interpolationType) : 
    _range(0),
    _interpolationType(interpolationType) 
{
    _type = PUDynamicAttribute::DAT_CURVED;
}
//-----------------------------------------------------------------------
PUDynamicAttributeCurved::PUDynamicAttributeCurved (const PUDynamicAttributeCurved& dynamicAttributeCurved) :
    _range(dynamicAttributeCurved._range),
    _spline(dynamicAttributeCurved._spline),
    _interpolationType(dynamicAttributeCurved._interpolationType)
{
    _type = PUDynamicAttribute::DAT_CURVED;

    // Copy controlpoints
    for (const auto& controlPoint : dynamicAttributeCurved._controlPoints)
    {
        _controlPoints.push_back (controlPoint);
    }
    processControlPoints();
}
//-----------------------------------------------------------------------
PUDynamicAttributeCurved::~PUDynamicAttributeCurved (void)
{
}
//-----------------------------------------------------------------------
void PUDynamicAttributeCurved::setInterpolationType (PUInterpolationType interpolationType)
{
    if (interpolationType != _interpolationType)
    {
        // If switched to another InterpolationType, the already existing ControlPoints will be removed.
        removeAllControlPoints();
        _interpolationType = interpolationType;
    }
}
//-----------------------------------------------------------------------
PUInterpolationType PUDynamicAttributeCurved::getInterpolationType (void) const
{
    return _interpolationType;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeCurved::getValue (float x)
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
void PUDynamicAttributeCurved::addControlPoint (float x, float y)
{
    _controlPoints.push_back(Vec2(x, y));
}
//-----------------------------------------------------------------------
const PUDynamicAttributeCurved::ControlPointList& PUDynamicAttributeCurved::getControlPoints (void) const
{
    return _controlPoints;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeCurved::processControlPoints(void)
{
    if (_controlPoints.empty())
        return;

    std::sort(_controlPoints.begin(), _controlPoints.end(), PUControlPointSorter());
    _range = (*getLastValidIterator()).x - (*getFirstValidIterator()).x;

    if (_interpolationType == IT_SPLINE)
    {
        // Add all sorted control points to the spline
        PUDynamicAttributeCurved::ControlPointList::iterator it;
        _spline.clear();
        for (it = _controlPoints.begin(); it != _controlPoints.end(); ++it)
            _spline.addPoint(Vec3((*it).x, (*it).y, 0));
    }
}
//-----------------------------------------------------------------------
size_t PUDynamicAttributeCurved::getNumControlPoints(void) const
{
    return _controlPoints.size();
}
//-----------------------------------------------------------------------
void PUDynamicAttributeCurved::removeAllControlPoints(void)
{
    _controlPoints.clear();
}
//-----------------------------------------------------------------------
PUDynamicAttributeCurved::ControlPointList::iterator PUDynamicAttributeCurved::findNearestControlPointIterator(float x)
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
PUDynamicAttributeCurved::ControlPointList::iterator PUDynamicAttributeCurved::getFirstValidIterator(void)
{
    return _controlPoints.begin();
}
//-----------------------------------------------------------------------
PUDynamicAttributeCurved::ControlPointList::iterator PUDynamicAttributeCurved::getLastValidIterator(void)
{
    return _controlPoints.end() - 1;
}

void PUDynamicAttributeCurved::copyAttributesTo( PUDynamicAttribute* dynamicAttribute )
{
    if (!dynamicAttribute || dynamicAttribute->getType() != PUDynamicAttribute::DAT_CURVED)
        return;

    PUDynamicAttributeCurved* dynAttr = static_cast<PUDynamicAttributeCurved*>(dynamicAttribute);
    dynAttr->_interpolationType = _interpolationType;
    dynAttr->_spline = _spline;
    dynAttr->_range = _range;

    // Copy controlpoints
    PUDynamicAttributeCurved::ControlPointList::const_iterator it; // Need const_iterator here!
    PUDynamicAttributeCurved::ControlPointList::const_iterator itEnd = _controlPoints.end();
    for (it = _controlPoints.begin(); it != itEnd; ++it)
    {
        Vec2 controlPoint = *it;
        dynAttr->_controlPoints.push_back(controlPoint);
    }
    dynAttr->processControlPoints();
}

PUDynamicAttributeCurved* PUDynamicAttributeCurved::clone()
{
    auto ac = new (std::nothrow) PUDynamicAttributeCurved();
    this->copyAttributesTo(ac);
    return ac;
}

//-----------------------------------------------------------------------
PUDynamicAttributeOscillate::PUDynamicAttributeOscillate (void) :
    _oscillationType(PUDynamicAttributeOscillate::OSCT_SINE),
    _frequency(1.0f),
    _phase(0.0f),
    _base(0.0f),
    _amplitude(1.0f)
{
    _type = PUDynamicAttribute::DAT_OSCILLATE;
}
//-----------------------------------------------------------------------
PUDynamicAttributeOscillate::PUDynamicAttributeOscillate (const PUDynamicAttributeOscillate& /*dynamicAttributeOscillate*/)
{
    _type = PUDynamicAttribute::DAT_OSCILLATE;
}
//-----------------------------------------------------------------------
PUDynamicAttributeOscillate::~PUDynamicAttributeOscillate (void)
{
}
//-----------------------------------------------------------------------
PUDynamicAttributeOscillate::OscillationType PUDynamicAttributeOscillate::getOscillationType (void) const
{
    return _oscillationType;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeOscillate::setOscillationType (PUDynamicAttributeOscillate::OscillationType oscillationType)
{
    _oscillationType = oscillationType;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeOscillate::getFrequency (void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeOscillate::setFrequency (float frequency)
{
    _frequency = frequency;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeOscillate::getPhase (void) const
{
    return _phase;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeOscillate::setPhase (float phase)
{
    _phase = phase;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeOscillate::getBase (void) const
{
    return _base;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeOscillate::setBase (float base)
{
    _base = base;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeOscillate::getAmplitude (void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void PUDynamicAttributeOscillate::setAmplitude (float amplitude)
{
    _amplitude = amplitude;
}
//-----------------------------------------------------------------------
float PUDynamicAttributeOscillate::getValue (float x)
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
            if (std::abs(val) < 0.00001f)
                val = val >0? 1: -1;
            return _base + _amplitude * val;
        }
        break;
    }

    return 0;
}

void PUDynamicAttributeOscillate::copyAttributesTo( PUDynamicAttribute* dynamicAttribute )
{
    if (!dynamicAttribute || dynamicAttribute->getType() != PUDynamicAttribute::DAT_OSCILLATE)
        return;

    PUDynamicAttributeOscillate* dynAttr = static_cast<PUDynamicAttributeOscillate*>(dynamicAttribute);
    dynAttr->_oscillationType = _oscillationType;
    dynAttr->_frequency = _frequency;
    dynAttr->_phase = _phase;
    dynAttr->_base = _base;
    dynAttr->_amplitude = _amplitude;
}

PUDynamicAttributeOscillate* PUDynamicAttributeOscillate::clone()
{
    auto ao = new (std::nothrow) PUDynamicAttributeOscillate();
    this->copyAttributesTo(ao);
    return ao;
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
float PUDynamicAttributeHelper::calculate(PUDynamicAttribute* dyn, float x, float defaultValue)
{
    if (dyn)
    {
        return dyn->getValue(x);
    }

    return defaultValue;
}
NS_CC_END
