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

#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnEventFlagObserver.h"
#include "Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const unsigned int PUParticle3DOnEventFlagObserver::DEFAULT_EVENT_FLAG = 0;

//-----------------------------------------------------------------------
PUParticle3DOnEventFlagObserver::PUParticle3DOnEventFlagObserver(void) : 
    PUParticle3DObserver(),
    _eventFlag(DEFAULT_EVENT_FLAG)
{
}
//-----------------------------------------------------------------------
bool PUParticle3DOnEventFlagObserver::observe (PUParticle3D* particle, float timeElapsed)
{
    if (!particle)
        return false;

    return (particle->hasEventFlags(_eventFlag));
}

PUParticle3DOnEventFlagObserver* PUParticle3DOnEventFlagObserver::create()
{
    auto peo = new PUParticle3DOnEventFlagObserver();
    peo->autorelease();
    return peo;
}

void PUParticle3DOnEventFlagObserver::copyAttributesTo( PUParticle3DObserver* observer )
{
    PUParticle3DObserver::copyAttributesTo(observer);

    PUParticle3DOnEventFlagObserver* onEventFlagObserver = static_cast<PUParticle3DOnEventFlagObserver*>(observer);
    onEventFlagObserver->_eventFlag = _eventFlag;
}

NS_CC_END
