/****************************************************************************
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

#include "CCPUParticle3DTextureRotator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const bool PUParticle3DTextureRotator::DEFAULT_USE_OWN_SPEED = false;
const float PUParticle3DTextureRotator::DEFAULT_ROTATION_SPEED = 10.0f;
const float PUParticle3DTextureRotator::DEFAULT_ROTATION = 0.0f;

//-----------------------------------------------------------------------
PUParticle3DTextureRotator::PUParticle3DTextureRotator(void) : 
    PUParticle3DAffector(),
    _useOwnRotationSpeed(DEFAULT_USE_OWN_SPEED),
    _scaledRotationSpeed(0.0f),
    _twoPiRad(float(2.0 * M_PI))
{
    _dynRotation = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRotation))->setValue(DEFAULT_ROTATION);
    _dynRotationSpeed = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
}
//-----------------------------------------------------------------------
PUParticle3DTextureRotator::~PUParticle3DTextureRotator(void)
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
bool PUParticle3DTextureRotator::useOwnRotationSpeed (void) const
{
    return _useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureRotator::setUseOwnRotationSpeed (bool useOwnRotationSpeed)
{
    _useOwnRotationSpeed = useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
PUDynamicAttribute* PUParticle3DTextureRotator::getRotation(void) const
{
    return _dynRotation;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureRotator::setRotation(PUDynamicAttribute* dynRotation)
{
    if (_dynRotation)
        CC_SAFE_DELETE(_dynRotation);

    _dynRotation = dynRotation;
}
//-----------------------------------------------------------------------
PUDynamicAttribute* PUParticle3DTextureRotator::getRotationSpeed(void) const
{
    return _dynRotationSpeed;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureRotator::setRotationSpeed(PUDynamicAttribute* dynRotationSpeed)
{
    if (_dynRotationSpeed)
        CC_SAFE_DELETE(_dynRotationSpeed);

    _dynRotationSpeed = dynRotationSpeed;
}
//-----------------------------------------------------------------------
float PUParticle3DTextureRotator::calculateRotation(void)
{
    return _dynamicAttributeHelper.calculate(_dynRotation, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
}
//-----------------------------------------------------------------------
float PUParticle3DTextureRotator::calculateRotationSpeed(PUParticle3D* particle)
{
    return _dynamicAttributeHelper.calculate(_dynRotationSpeed, particle->timeFraction);
}
//-----------------------------------------------------------------------
void PUParticle3DTextureRotator::initParticleForEmission(PUParticle3D* particle)
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

void PUParticle3DTextureRotator::updatePUAffector( PUParticle3D *particle, float deltaTime )
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

PUParticle3DTextureRotator* PUParticle3DTextureRotator::create()
{
    auto ptr = new (std::nothrow) PUParticle3DTextureRotator();
    ptr->autorelease();
    return ptr;
}

NS_CC_END