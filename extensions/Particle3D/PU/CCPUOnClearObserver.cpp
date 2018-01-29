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

#include "extensions/Particle3D/PU/CCPUOnClearObserver.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

//-----------------------------------------------------------------------
void PUOnClearObserver::notifyStart (void)
{
    PUObserver::notifyStart();
    _continue = false;
}
//-----------------------------------------------------------------------
bool PUOnClearObserver::observe (PUParticle3D* /*particle*/, float /*timeElapsed*/)
{
    // This function always returns false, but is never called (but it must be implemented).
    return false;
}
//-----------------------------------------------------------------------
void PUOnClearObserver::updateObserver(PUParticle3D* /*particle*/, float /*timeElapsed*/, bool firstParticle)
{
    // Override the _processParticle() function, because we don't observe individual particles.
    if (firstParticle)
    {
        // Only continue to validate if there was at least 1 particle emitted, otherwise the event-
        // handlers are already called at the very start (when there are no particle yet).
        _continue = true;
    }
}
//-----------------------------------------------------------------------
void PUOnClearObserver::postUpdateObserver(float timeElapsed)
{
    if (_continue)
    {
        if (static_cast<PUParticleSystem3D *>(_particleSystem)->getAliveParticleCount() <= 0)
        {
            /** Handle the event. Use 0 as the particle pointer. This means that not all eventhandlers
                are suitable. If they expect a particle (and most eventhandlers do), it could
                result in an exception. Handlers such as the DoEnableComponentEventHandler and the
                DoStopSystemEventHandler however can be used without any problem.
            */
            handleEvent (0, timeElapsed);
            _continue = false;
        }
    }
}

PUOnClearObserver* PUOnClearObserver::create()
{
    auto pco = new (std::nothrow) PUOnClearObserver();
    pco->autorelease();
    return pco;
}

NS_CC_END
