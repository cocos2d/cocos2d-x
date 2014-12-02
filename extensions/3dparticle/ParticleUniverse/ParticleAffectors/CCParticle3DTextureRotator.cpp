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

#include "CCParticle3DTextureRotator.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const bool Particle3DTextureRotator::DEFAULT_USE_OWN_SPEED = false;
const float Particle3DTextureRotator::DEFAULT_ROTATION_SPEED = 10.0f;
const float Particle3DTextureRotator::DEFAULT_ROTATION = 0.0f;

//-----------------------------------------------------------------------
Particle3DTextureRotator::Particle3DTextureRotator(void) : 
    PUParticle3DAffector(),
    _useOwnRotationSpeed(DEFAULT_USE_OWN_SPEED),
    _scaledRotationSpeed(0.0f),
    _twoPiRad(float(2.0 * M_PI))
{
    _dynRotation = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynRotation))->setValue(DEFAULT_ROTATION);
    _dynRotationSpeed = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
}
//-----------------------------------------------------------------------
Particle3DTextureRotator::~Particle3DTextureRotator(void)
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
bool Particle3DTextureRotator::useOwnRotationSpeed (void) const
{
    return _useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
void Particle3DTextureRotator::setUseOwnRotationSpeed (bool useOwnRotationSpeed)
{
    _useOwnRotationSpeed = useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
DynamicAttribute* Particle3DTextureRotator::getRotation(void) const
{
    return _dynRotation;
}
//-----------------------------------------------------------------------
void Particle3DTextureRotator::setRotation(DynamicAttribute* dynRotation)
{
    if (_dynRotation)
        CC_SAFE_DELETE(_dynRotation);

    _dynRotation = dynRotation;
}
//-----------------------------------------------------------------------
DynamicAttribute* Particle3DTextureRotator::getRotationSpeed(void) const
{
    return _dynRotationSpeed;
}
//-----------------------------------------------------------------------
void Particle3DTextureRotator::setRotationSpeed(DynamicAttribute* dynRotationSpeed)
{
    if (_dynRotationSpeed)
        CC_SAFE_DELETE(_dynRotationSpeed);

    _dynRotationSpeed = dynRotationSpeed;
}
//-----------------------------------------------------------------------
float Particle3DTextureRotator::calculateRotation(void)
{
    return float(_dynamicAttributeHelper.calculate(_dynRotation, _particleSystem->getTimeElapsedSinceStart()));
}
//-----------------------------------------------------------------------
float Particle3DTextureRotator::calculateRotationSpeed(PUParticle3D* particle)
{
    return float(_dynamicAttributeHelper.calculate(_dynRotationSpeed, particle->timeFraction));
}
//-----------------------------------------------------------------------
void Particle3DTextureRotator::initParticleForEmission(PUParticle3D* particle)
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

void Particle3DTextureRotator::updateAffector( PUParticle3D *particle, float deltaTime )
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

NS_CC_END