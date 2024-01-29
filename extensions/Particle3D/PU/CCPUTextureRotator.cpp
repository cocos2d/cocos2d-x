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

#include "CCPUTextureRotator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const bool PUTextureRotator::DEFAULT_USE_OWN_SPEED = false;
const float PUTextureRotator::DEFAULT_ROTATION_SPEED = 10.0f;
const float PUTextureRotator::DEFAULT_ROTATION = 0.0f;

//-----------------------------------------------------------------------
PUTextureRotator::PUTextureRotator()
: PUAffector()
, _useOwnRotationSpeed(DEFAULT_USE_OWN_SPEED)
, _scaledRotationSpeed(0.0f)
, _twoPiRad(float(2.0 * M_PI))
{
    _dynRotation = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRotation))->setValue(DEFAULT_ROTATION);
    _dynRotationSpeed = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
}
//-----------------------------------------------------------------------
PUTextureRotator::~PUTextureRotator()
{
    if (_dynRotation)
    {
        CC_SAFE_DELETE(_dynRotation);
    }

    if (_dynRotationSpeed)
    {
        CC_SAFE_DELETE(_dynRotationSpeed);
    }
}
//-----------------------------------------------------------------------
bool PUTextureRotator::useOwnRotationSpeed () const
{
    return _useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
void PUTextureRotator::setUseOwnRotationSpeed (bool useOwnRotationSpeed)
{
    _useOwnRotationSpeed = useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
PUDynamicAttribute* PUTextureRotator::getRotation() const
{
    return _dynRotation;
}
//-----------------------------------------------------------------------
void PUTextureRotator::setRotation(PUDynamicAttribute* dynRotation)
{
    if (_dynRotation)
        CC_SAFE_DELETE(_dynRotation);

    _dynRotation = dynRotation;
}
//-----------------------------------------------------------------------
PUDynamicAttribute* PUTextureRotator::getRotationSpeed() const
{
    return _dynRotationSpeed;
}
//-----------------------------------------------------------------------
void PUTextureRotator::setRotationSpeed(PUDynamicAttribute* dynRotationSpeed)
{
    if (_dynRotationSpeed)
        CC_SAFE_DELETE(_dynRotationSpeed);

    _dynRotationSpeed = dynRotationSpeed;
}
//-----------------------------------------------------------------------
float PUTextureRotator::calculateRotation()
{
    return _dynamicAttributeHelper.calculate(_dynRotation, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
}
//-----------------------------------------------------------------------
float PUTextureRotator::calculateRotationSpeed(PUParticle3D* particle)
{
    return _dynamicAttributeHelper.calculate(_dynRotationSpeed, particle->timeFraction);
}
//-----------------------------------------------------------------------
void PUTextureRotator::initParticleForEmission(PUParticle3D* particle)
{
    //// Only continue if the particle is a visual particle
    //if (particle->particleType != PUParticle3D::PT_VISUAL)
    //	return;

    // Set initial random zRotation
    particle->zRotation = calculateRotation();
    //FIXME
    //if (particle->parentEmitter->getParentTechnique()->getRenderer())
    //{
    //	// Assume that all parents exist. That must be the case otherwise particles are not emitted.
    //	particle->parentEmitter->getParentTechnique()->getRenderer()->_notifyParticleZRotated();
    //}

    // Set the zRotationSpeed
    particle->zRotationSpeed = calculateRotationSpeed(particle);
}
//-----------------------------------------------------------------------

void PUTextureRotator::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        //// Only continue if the particle is a visual particle
        //if (particle->particleType != PUParticle3D::PT_VISUAL)
        //	return;

        if (_useOwnRotationSpeed)
        {
            // Use scaled rotationspeed and adjust the speed according to the velocity
            _scaledRotationSpeed = particle->zRotationSpeed * deltaTime;
        }
        else
        {
            // Scale speed
            _scaledRotationSpeed = calculateRotationSpeed(particle) * deltaTime;
        }

        particle->zRotation += _scaledRotationSpeed;
        particle->zRotation = particle->zRotation > _twoPiRad ? particle->zRotation - _twoPiRad : particle->zRotation;

        //FIXME
        //if (particleTechnique->getRenderer())
        //{
        //	particleTechnique->getRenderer()->_notifyParticleZRotated();
        //}
    }
}

PUTextureRotator* PUTextureRotator::create()
{
    auto ptr = new (std::nothrow) PUTextureRotator();
    ptr->autorelease();
    return ptr;
}

void PUTextureRotator::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUTextureRotator* textureRotator = static_cast<PUTextureRotator*>(affector);
    textureRotator->setRotation(getRotation()->clone());
    textureRotator->setRotationSpeed(getRotationSpeed()->clone());
    textureRotator->_useOwnRotationSpeed = _useOwnRotationSpeed;
}

NS_CC_END
