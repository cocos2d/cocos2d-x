/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "extensions/Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DOnRandomObserver.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DOnRandomObserver::DEFAULT_THRESHOLD = 0.5f;

//-----------------------------------------------------------------------
PUParticle3DOnRandomObserver::PUParticle3DOnRandomObserver(void) : 
    PUParticle3DObserver(),
    _threshold(DEFAULT_THRESHOLD)
{
}
//-----------------------------------------------------------------------
void PUParticle3DOnRandomObserver::preUpdateObserver(float deltaTime)
{
    // Call parent
    PUParticle3DObserver::preUpdateObserver(deltaTime);

    // Handle the _observe here
    handleObserve(0, deltaTime);
}
//-----------------------------------------------------------------------
void PUParticle3DOnRandomObserver::updateObserver(PUParticle3D *particle, float deltaTime, bool firstParticle)
{
    // No need to determine per particle
}
//-----------------------------------------------------------------------
bool PUParticle3DOnRandomObserver::observe (PUParticle3D* particle, float timeElapsed)
{
    return (CCRANDOM_0_1() > _threshold);
}

PUParticle3DOnRandomObserver* PUParticle3DOnRandomObserver::create()
{
    auto pro = new (std::nothrow) PUParticle3DOnRandomObserver();
    pro->autorelease();
    return pro;
}

void PUParticle3DOnRandomObserver::copyAttributesTo( PUParticle3DObserver* observer )
{
    PUParticle3DObserver::copyAttributesTo(observer);
    PUParticle3DOnRandomObserver* onRandomObserver = static_cast<PUParticle3DOnRandomObserver*>(observer);
    onRandomObserver->_threshold = _threshold;
}

NS_CC_END
