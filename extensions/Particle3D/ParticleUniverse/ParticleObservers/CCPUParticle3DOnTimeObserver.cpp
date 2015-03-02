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

#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnTimeObserver.h"
#include "Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DOnTimeObserver::DEFAULT_THRESHOLD = 0.0f;
const bool PUParticle3DOnTimeObserver::DEFAULT_SINCE_START_SYSTEM = false;

static bool almostEquals(float a, float b, float epsilon = std::numeric_limits<float>::epsilon())
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon); 
};

//-----------------------------------------------------------------------
PUParticle3DOnTimeObserver::PUParticle3DOnTimeObserver(void) : PUParticle3DObserver(),
    _threshold(DEFAULT_THRESHOLD),
    _compare(CO_GREATER_THAN),
    _sinceStartSystem(DEFAULT_SINCE_START_SYSTEM)
{
};
//-----------------------------------------------------------------------
void PUParticle3DOnTimeObserver::preUpdateObserver(float deltaTime)
{
    // Call parent
    PUParticle3DObserver::preUpdateObserver(deltaTime);

    // Also observe if there are no particles emitted, because some of the event handlers do not only
    // perform an action on a particle.
    if (static_cast<PUParticleSystem3D *>(_particleSystem)->getAliveParticleCnt() <= 0)
    {
        handleObserve(0, deltaTime);
    }
}
//-----------------------------------------------------------------------
bool PUParticle3DOnTimeObserver::observe (PUParticle3D* particle, float timeElapsed)
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

PUParticle3DOnTimeObserver* PUParticle3DOnTimeObserver::create()
{
    auto pto = new PUParticle3DOnTimeObserver();
    pto->autorelease();
    return pto;
}

void PUParticle3DOnTimeObserver::copyAttributesTo( PUParticle3DObserver* observer )
{
    PUParticle3DObserver::copyAttributesTo(observer);

    PUParticle3DOnTimeObserver* onTimeObserver = static_cast<PUParticle3DOnTimeObserver*>(observer);
    onTimeObserver->_threshold = _threshold;
    onTimeObserver->_compare = _compare;
    onTimeObserver->_sinceStartSystem = _sinceStartSystem;
}

NS_CC_END
