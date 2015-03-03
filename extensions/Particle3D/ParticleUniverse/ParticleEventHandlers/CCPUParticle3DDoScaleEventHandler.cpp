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

#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoScaleEventHandler.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const PUParticle3DDoScaleEventHandler::ScaleType PUParticle3DDoScaleEventHandler::DEFAULT_SCALE_TYPE = PUParticle3DDoScaleEventHandler::ST_TIME_TO_LIVE;
const float PUParticle3DDoScaleEventHandler::DEFAULT_SCALE_FRACTION = 0.2f;

//-----------------------------------------------------------------------
PUParticle3DDoScaleEventHandler::PUParticle3DDoScaleEventHandler(void) : 
    PUParticle3DEventHandler(),
    _scaleFraction(DEFAULT_SCALE_FRACTION),
    _scaleType(DEFAULT_SCALE_TYPE)
{
}
//-----------------------------------------------------------------------
const PUParticle3DDoScaleEventHandler::ScaleType& PUParticle3DDoScaleEventHandler::getScaleType(void) const
{
    return _scaleType;
}
//-----------------------------------------------------------------------
void PUParticle3DDoScaleEventHandler::setScaleType(const PUParticle3DDoScaleEventHandler::ScaleType& scaleType)
{
    _scaleType = scaleType;
}
//-----------------------------------------------------------------------
const float PUParticle3DDoScaleEventHandler::getScaleFraction(void) const
{
    return _scaleFraction;
}
//-----------------------------------------------------------------------
void PUParticle3DDoScaleEventHandler::setScaleFraction(const float scaleFraction)
{
    _scaleFraction = scaleFraction;
}
//-----------------------------------------------------------------------
void PUParticle3DDoScaleEventHandler::handle (PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed)
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

PUParticle3DDoScaleEventHandler* PUParticle3DDoScaleEventHandler::create()
{
    auto peh = new (std::nothrow) PUParticle3DDoScaleEventHandler();
    peh->autorelease();
    return peh;
}

void PUParticle3DDoScaleEventHandler::copyAttributesTo( PUParticle3DEventHandler* eventHandler )
{
    PUParticle3DEventHandler::copyAttributesTo(eventHandler);
    PUParticle3DDoScaleEventHandler* doScaleEventHandler = static_cast<PUParticle3DDoScaleEventHandler*>(eventHandler);
    doScaleEventHandler->setScaleFraction(_scaleFraction);
    doScaleEventHandler->setScaleType(_scaleType);
}

NS_CC_END
