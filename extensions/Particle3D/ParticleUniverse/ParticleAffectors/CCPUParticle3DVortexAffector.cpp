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

#include "CCPUParticle3DVortexAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 PUParticle3DVortexAffector::DEFAULT_ROTATION_VECTOR(0, 0, 0);
const float PUParticle3DVortexAffector::DEFAULT_ROTATION_SPEED = 1.0f;

//-----------------------------------------------------------------------
PUParticle3DVortexAffector::PUParticle3DVortexAffector(void) : 
    PUParticle3DAffector(),
    _rotationVector(DEFAULT_ROTATION_VECTOR)
{
    _dynRotationSpeed = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
}
//-----------------------------------------------------------------------
PUParticle3DVortexAffector::~PUParticle3DVortexAffector(void)
{
    if (_dynRotationSpeed)
    {
        CC_SAFE_DELETE(_dynRotationSpeed);
    }
}
//-----------------------------------------------------------------------
const Vec3& PUParticle3DVortexAffector::getRotationVector(void) const
{
    return _rotationVector;
}
//-----------------------------------------------------------------------
void PUParticle3DVortexAffector::setRotationVector(const Vec3& rotationVector)
{
    _rotationVector = rotationVector;
}
//-----------------------------------------------------------------------
PUDynamicAttribute* PUParticle3DVortexAffector::getRotationSpeed(void) const
{
    return _dynRotationSpeed;
}
//-----------------------------------------------------------------------
void PUParticle3DVortexAffector::setRotationSpeed(PUDynamicAttribute* dynRotationSpeed)
{
    if (_dynRotationSpeed)
        CC_SAFE_DELETE(_dynRotationSpeed);

    _dynRotationSpeed = dynRotationSpeed;
}
//-----------------------------------------------------------------------
float PUParticle3DVortexAffector::calculateRotationSpeed(void)
{
    return float(_dynamicAttributeHelper.calculate(_dynRotationSpeed, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart()));
}
//-----------------------------------------------------------------------

void PUParticle3DVortexAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        // Explicitly check on 'freezed', because it passes the techniques' validation.
        if (particle->isFreezed())
            return;

        // Rotate position, direction and orientation (visible particle only) and compensate for the affector position
        // Also take the affect specialisation into account
        Mat4 rotMat;
        Mat4::createRotation(_rotation, &rotMat);
        Vec3 local = particle->position - _derivedPosition;
        particle->position = _derivedPosition + rotMat * local;
        particle->direction = rotMat * particle->direction;
        particle->orientation = _rotation * particle->orientation;
    }
}

void PUParticle3DVortexAffector::preUpdateAffector( float deltaTime )
{
    PUParticleSystem3D* sys = static_cast<PUParticleSystem3D *>(_particleSystem);

    if (sys)
    {
        Mat4 rotMat;
        Mat4::createRotation(sys->getDerivedOrientation(), &rotMat);
        _rotation.set(rotMat * _rotationVector, float(calculateRotationSpeed() * deltaTime));
    }
    else
    {
        _rotation.set(_rotationVector, float(calculateRotationSpeed() * deltaTime));
    }

    getDerivedPosition();
}

PUParticle3DVortexAffector* PUParticle3DVortexAffector::create()
{
    auto pvf = new (std::nothrow) PUParticle3DVortexAffector();
    pvf->autorelease();
    return pvf;
}

NS_CC_END