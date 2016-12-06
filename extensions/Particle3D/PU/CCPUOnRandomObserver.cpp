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

#include "extensions/Particle3D/PU/CCPUOnRandomObserver.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUOnRandomObserver::DEFAULT_THRESHOLD = 0.5f;

//-----------------------------------------------------------------------
PUOnRandomObserver::PUOnRandomObserver(void) : 
    PUObserver(),
    _threshold(DEFAULT_THRESHOLD)
{
}
//-----------------------------------------------------------------------
void PUOnRandomObserver::preUpdateObserver(float deltaTime)
{
    // Call parent
    PUObserver::preUpdateObserver(deltaTime);

    // Handle the _observe here
    handleObserve(0, deltaTime);
}
//-----------------------------------------------------------------------
void PUOnRandomObserver::updateObserver(PUParticle3D* /*particle*/, float /*deltaTime*/, bool /*firstParticle*/)
{
    // No need to determine per particle
}
//-----------------------------------------------------------------------
bool PUOnRandomObserver::observe (PUParticle3D* /*particle*/, float /*timeElapsed*/)
{
    return (CCRANDOM_0_1() > _threshold);
}

PUOnRandomObserver* PUOnRandomObserver::create()
{
    auto pro = new (std::nothrow) PUOnRandomObserver();
    pro->autorelease();
    return pro;
}

void PUOnRandomObserver::copyAttributesTo( PUObserver* observer )
{
    PUObserver::copyAttributesTo(observer);
    PUOnRandomObserver* onRandomObserver = static_cast<PUOnRandomObserver*>(observer);
    onRandomObserver->_threshold = _threshold;
}

NS_CC_END
