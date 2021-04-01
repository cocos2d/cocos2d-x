/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "extensions/Particle3D/PU/CCPUOnVelocityObserver.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

static bool almostEquals(float a, float b, float epsilon = std::numeric_limits<float>::epsilon())
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon); 
};

// Constants
const float PUOnVelocityObserver::DEFAULT_VELOCITY_THRESHOLD = 0.0f;

//-----------------------------------------------------------------------
PUOnVelocityObserver::PUOnVelocityObserver() : 
    PUObserver(),
    _threshold(DEFAULT_VELOCITY_THRESHOLD),
    _compare(CO_LESS_THAN)
{
};
//-----------------------------------------------------------------------
bool PUOnVelocityObserver::observe (PUParticle3D* particle, float /*timeElapsed*/)
{
    if (!particle)
        return false;

    // Compensate for the scaled velocity
    float scaleVelocity = _particleSystem->getParticleSystemScaleVelocity();
    if (_compare == CO_GREATER_THAN)
    {
        // Changed in V 1.3.1
        return (particle->calculateVelocity()) > (scaleVelocity * _threshold);
    }
    else if (_compare == CO_LESS_THAN)
    {
        return (particle->calculateVelocity()) < (scaleVelocity * _threshold);
    }
    else
    {
        // Equals
        return almostEquals(particle->calculateVelocity(), (scaleVelocity * _threshold), 0.01f);
    }

    return false;
}

PUOnVelocityObserver* PUOnVelocityObserver::create()
{
    auto pvo = new (std::nothrow) PUOnVelocityObserver();
    pvo->autorelease();
    return pvo;
}

void PUOnVelocityObserver::copyAttributesTo( PUObserver* observer )
{
    PUObserver::copyAttributesTo(observer);

    PUOnVelocityObserver* onVelocityObserver = static_cast<PUOnVelocityObserver*>(observer);
    onVelocityObserver->_threshold = _threshold;
    onVelocityObserver->_compare = _compare;
}

NS_CC_END
