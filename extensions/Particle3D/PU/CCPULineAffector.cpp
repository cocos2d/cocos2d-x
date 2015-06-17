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

#include "CCPULineAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PULineAffector::DEFAULT_MAX_DEVIATION = 1.0f;
const float PULineAffector::DEFAULT_TIME_STEP = 0.1f;
const Vec3 PULineAffector::DEFAULT_END(0, 0, 0);
const float PULineAffector::DEFAULT_DRIFT = 0.0f;

//-----------------------------------------------------------------------
PULineAffector::PULineAffector(void) : 
    PUAffector(),
    _maxDeviation(DEFAULT_MAX_DEVIATION),
    _scaledMaxDeviation(1.0f),
    _end(DEFAULT_END),
    _timeSinceLastUpdate(0.0f),
    _timeStep(DEFAULT_TIME_STEP),
    _drift(DEFAULT_DRIFT),
    _oneMinusDrift(1.0f),
    _update(true),
    _first(true)
{
}

PULineAffector::~PULineAffector( void )
{

}
//-----------------------------------------------------------------------
float PULineAffector::getMaxDeviation(void) const
{
    return _maxDeviation;
}
//-----------------------------------------------------------------------
void PULineAffector::setMaxDeviation(float maxDeviation)
{
    _maxDeviation = maxDeviation;
    _scaledMaxDeviation = _maxDeviation * _affectorScale.length();
}
//-----------------------------------------------------------------------
const Vec3& PULineAffector::getEnd(void) const
{
    return _end;
}
//-----------------------------------------------------------------------
void PULineAffector::setEnd(const Vec3& end)
{
    _end = end;
}
//-----------------------------------------------------------------------
float PULineAffector::getTimeStep(void) const
{
    return _timeStep;
}
//-----------------------------------------------------------------------
void PULineAffector::setTimeStep(float timeStep)
{
    _timeStep = timeStep;
}
//-----------------------------------------------------------------------
float PULineAffector::getDrift(void) const
{
    return _drift;
}
//-----------------------------------------------------------------------
void PULineAffector::setDrift(float drift)
{
    _drift = drift;
    _oneMinusDrift = 1.0f - drift;
}
//-----------------------------------------------------------------------
void PULineAffector::notifyRescaled(const Vec3& scale)
{
    _scaledMaxDeviation = _maxDeviation * scale.length();
}
//-----------------------------------------------------------------------
void PULineAffector::preUpdateAffector(float deltaTime)
{
    if (/*technique->getNumberOfEmittedParticles()*/static_cast<PUParticleSystem3D *>(_particleSystem)->getAliveParticleCount() > 0)
    {
        _timeSinceLastUpdate += deltaTime;
        while (_timeSinceLastUpdate > _timeStep)
        {
            _timeSinceLastUpdate -= _timeStep;
            _update = true;
        }
    }
    (static_cast<PUParticleSystem3D *>(_particleSystem))->rotationOffset(_end); // Always update
}
//-----------------------------------------------------------------------

void PULineAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //_first = true;
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        (static_cast<PUParticleSystem3D *>(_particleSystem))->rotationOffset(particle->originalPosition); // Always update
        if (_update && CCRANDOM_0_1() > 0.5 && !_first)
        {
            // Generate a random vector perpendicular on the line
            Vec3 perpendicular;
            Vec3::cross(_end, Vec3(CCRANDOM_MINUS1_1(), CCRANDOM_MINUS1_1(), CCRANDOM_MINUS1_1()), &perpendicular);
            perpendicular.normalize();

            // Determine a random point near the line.
            Vec3 targetPosition = particle->originalPosition + _scaledMaxDeviation * CCRANDOM_0_1() * perpendicular;

            /** Set the new position.
            @remarks
                This affector already takes rotational offset of the particle system into account. This means that there is no need
                to set the particle system to keep_local to 'true'. The reason is that this is a specialized affector that calculates
                a new particle position instead of a direction.
            */
            particle->position = _drift * targetPosition + _oneMinusDrift * particle->position;
            (static_cast<PUParticleSystem3D *>(_particleSystem))->rotationOffset(particle->position);
        }
        _first = false;
    }
}

//-----------------------------------------------------------------------
void PULineAffector::postUpdateAffector(float deltaTime)
{
    _update = false;
}

void PULineAffector::firstParticleUpdate( PUParticle3D *particle, float deltaTime )
{
    _first = true;
}

PULineAffector* PULineAffector::create()
{
    auto pla = new (std::nothrow) PULineAffector();
    pla->autorelease();
    return pla;
}

void PULineAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PULineAffector* lineAffector = static_cast<PULineAffector*>(affector);
    lineAffector->setMaxDeviation(_maxDeviation);
    lineAffector->_end = _end;
    lineAffector->_timeStep = _timeStep;
    lineAffector->_drift = _drift;
    lineAffector->_oneMinusDrift = _oneMinusDrift;
}

NS_CC_END
