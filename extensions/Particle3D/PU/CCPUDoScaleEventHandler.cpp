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

#include "extensions/Particle3D/PU/CCPUDoScaleEventHandler.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const PUDoScaleEventHandler::ScaleType PUDoScaleEventHandler::DEFAULT_SCALE_TYPE = PUDoScaleEventHandler::ST_TIME_TO_LIVE;
const float PUDoScaleEventHandler::DEFAULT_SCALE_FRACTION = 0.2f;

//-----------------------------------------------------------------------
PUDoScaleEventHandler::PUDoScaleEventHandler(void) : 
    PUEventHandler(),
    _scaleFraction(DEFAULT_SCALE_FRACTION),
    _scaleType(DEFAULT_SCALE_TYPE)
{
}
//-----------------------------------------------------------------------
const PUDoScaleEventHandler::ScaleType& PUDoScaleEventHandler::getScaleType(void) const
{
    return _scaleType;
}
//-----------------------------------------------------------------------
void PUDoScaleEventHandler::setScaleType(const PUDoScaleEventHandler::ScaleType& scaleType)
{
    _scaleType = scaleType;
}
//-----------------------------------------------------------------------
const float PUDoScaleEventHandler::getScaleFraction(void) const
{
    return _scaleFraction;
}
//-----------------------------------------------------------------------
void PUDoScaleEventHandler::setScaleFraction(const float scaleFraction)
{
    _scaleFraction = scaleFraction;
}
//-----------------------------------------------------------------------
void PUDoScaleEventHandler::handle (PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed)
{
    if (!particle)
        return;

    switch (_scaleType)
    {
    case ST_TIME_TO_LIVE:
        particle->timeToLive -= timeElapsed * _scaleFraction * particle->timeToLive;
        break;

    case ST_VELOCITY:
        particle->direction += timeElapsed * _scaleFraction * particle->direction;
        break;
    }
}

PUDoScaleEventHandler* PUDoScaleEventHandler::create()
{
    auto peh = new (std::nothrow) PUDoScaleEventHandler();
    peh->autorelease();
    return peh;
}

void PUDoScaleEventHandler::copyAttributesTo( PUEventHandler* eventHandler )
{
    PUEventHandler::copyAttributesTo(eventHandler);
    PUDoScaleEventHandler* doScaleEventHandler = static_cast<PUDoScaleEventHandler*>(eventHandler);
    doScaleEventHandler->setScaleFraction(_scaleFraction);
    doScaleEventHandler->setScaleType(_scaleType);
}

NS_CC_END
