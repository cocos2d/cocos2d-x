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

#include "CCParticle3DVortexAffector.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 Particle3DVortexAffector::DEFAULT_ROTATION_VECTOR(0, 0, 0);
const float Particle3DVortexAffector::DEFAULT_ROTATION_SPEED = 1.0f;

//-----------------------------------------------------------------------
Particle3DVortexAffector::Particle3DVortexAffector(void) : 
    Particle3DAffector(),
    _rotationVector(DEFAULT_ROTATION_VECTOR)
{
    _dynRotationSpeed = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
}
//-----------------------------------------------------------------------
Particle3DVortexAffector::~Particle3DVortexAffector(void)
{
    if (_dynRotationSpeed)
    {
        CC_SAFE_DELETE(_dynRotationSpeed);
    }
}
//-----------------------------------------------------------------------
const Vec3& Particle3DVortexAffector::getRotationVector(void) const
{
    return _rotationVector;
}
//-----------------------------------------------------------------------
void Particle3DVortexAffector::setRotationVector(const Vec3& rotationVector)
{
    _rotationVector = rotationVector;
}
//-----------------------------------------------------------------------
DynamicAttribute* Particle3DVortexAffector::getRotationSpeed(void) const
{
    return _dynRotationSpeed;
}
//-----------------------------------------------------------------------
void Particle3DVortexAffector::setRotationSpeed(DynamicAttribute* dynRotationSpeed)
{
    if (_dynRotationSpeed)
        CC_SAFE_DELETE(_dynRotationSpeed);

    _dynRotationSpeed = dynRotationSpeed;
}
//-----------------------------------------------------------------------
float Particle3DVortexAffector::calculateRotationSpeed(void)
{
    return float(_dynamicAttributeHelper.calculate(_dynRotationSpeed, _particleSystem->getTimeElapsedSinceStart()));
}
//-----------------------------------------------------------------------

void Particle3DVortexAffector::updateAffector( Particle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //Particle3D *particle = iter;
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

void Particle3DVortexAffector::preUpdateAffector( float deltaTime )
{
    //ParticleSystem* sys = mParentTechnique->getParentSystem();

    //if (sys)
    //{
    //	_rotation.FromAngleAxis(float(calculateRotationSpeed() * timeElapsed), sys->getDerivedOrientation() * _rotationVector);
    //}
    //else
    //{
    //	_rotation.FromAngleAxis(float(calculateRotationSpeed() * timeElapsed), _rotationVector);
    //}

    //FIXME
    _rotation.set(/*_particleSystem->getDerivedOrientation() * */_rotationVector, calculateRotationSpeed() * deltaTime);
    getDerivedPosition();
}

NS_CC_END