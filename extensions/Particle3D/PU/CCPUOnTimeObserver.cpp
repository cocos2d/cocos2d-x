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

#include "extensions/Particle3D/PU/CCPUOnTimeObserver.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUOnTimeObserver::DEFAULT_THRESHOLD = 0.0f;
const bool PUOnTimeObserver::DEFAULT_SINCE_START_SYSTEM = false;

static bool almostEquals(float a, float b, float epsilon = std::numeric_limits<float>::epsilon())
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon); 
};

//-----------------------------------------------------------------------
PUOnTimeObserver::PUOnTimeObserver(void) : PUObserver(),
    _threshold(DEFAULT_THRESHOLD),
    _compare(CO_GREATER_THAN),
    _sinceStartSystem(DEFAULT_SINCE_START_SYSTEM)
{
};
//-----------------------------------------------------------------------
void PUOnTimeObserver::preUpdateObserver(float deltaTime)
{
    // Call parent
    PUObserver::preUpdateObserver(deltaTime);

    // Also observe if there are no particles emitted, because some of the event handlers do not only
    // perform an action on a particle.
    if (static_cast<PUParticleSystem3D *>(_particleSystem)->getAliveParticleCount() <= 0)
    {
        handleObserve(0, deltaTime);
    }
}
//-----------------------------------------------------------------------
bool PUOnTimeObserver::observe (PUParticle3D* particle, float /*timeElapsed*/)
{
    if (_compare == CO_GREATER_THAN)
    {
        if (_sinceStartSystem)
        {
            // Validate whether time since start of the particle system > threshold
            return (_particleSystem->getTimeElapsedSinceStart() > _threshold);
        }
        else
        {
            // Validate whether time since start of the particle emission > threshold
            return (particle && (particle->totalTimeToLive - particle->timeToLive) > _threshold);
        }
    }
    else if (_compare == CO_LESS_THAN)
    {
        if (_sinceStartSystem)
        {
            // Validate whether time since start of the particle system < threshold
            return (_particleSystem->getTimeElapsedSinceStart() < _threshold);
        }
        else
        {
            // Validate whether time since start of the particle emission < threshold
            return (particle && (particle->totalTimeToLive - particle->timeToLive) < _threshold);
        }
    }
    else
    {
        // Equals
        if (_sinceStartSystem)
        {
            // Validate whether time since start of the particle system == threshold
            return almostEquals(_particleSystem->getTimeElapsedSinceStart(), _threshold, 0.01f);
        }
        else
        {
            // Validate whether time since start of the particle emission == threshold
            return particle && almostEquals((particle->totalTimeToLive - particle->timeToLive), _threshold, 0.01f);
        }
    }

    return false;
}

PUOnTimeObserver* PUOnTimeObserver::create()
{
    auto pto = new (std::nothrow) PUOnTimeObserver();
    pto->autorelease();
    return pto;
}

void PUOnTimeObserver::copyAttributesTo( PUObserver* observer )
{
    PUObserver::copyAttributesTo(observer);

    PUOnTimeObserver* onTimeObserver = static_cast<PUOnTimeObserver*>(observer);
    onTimeObserver->_threshold = _threshold;
    onTimeObserver->_compare = _compare;
    onTimeObserver->_sinceStartSystem = _sinceStartSystem;
}

NS_CC_END
