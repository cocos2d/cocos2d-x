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

#include "CCPUGeometryRotator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
// Constants
const bool PUGeometryRotator::DEFAULT_USE_OWN = false;
const float PUGeometryRotator::DEFAULT_ROTATION_SPEED = 10.0f;
const Vec3 PUGeometryRotator::DEFAULT_ROTATION_AXIS(0, 0, 0);

//-----------------------------------------------------------------------
PUGeometryRotator::PUGeometryRotator() : 
    PUAffector(),
    _scaledRotationSpeed(0.0f),
    _useOwnRotationSpeed(DEFAULT_USE_OWN),
    //mQ(Quaternion::IDENTITY),
    _rotationAxis(DEFAULT_ROTATION_AXIS),
    _rotationAxisSet(false)
{
    _dynRotationSpeed = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
};
//-----------------------------------------------------------------------
PUGeometryRotator::~PUGeometryRotator()
{
    if (_dynRotationSpeed)
        CC_SAFE_DELETE(_dynRotationSpeed);
}
//-----------------------------------------------------------------------
const Vec3& PUGeometryRotator::getRotationAxis() const
{
    return _rotationAxis;
}
//-----------------------------------------------------------------------
void PUGeometryRotator::setRotationAxis(const Vec3& rotationAxis)
{
    _rotationAxis = rotationAxis;
    _rotationAxisSet = true;
}
//-----------------------------------------------------------------------
void PUGeometryRotator::resetRotationAxis(void)
{
    _dynRotationSpeed = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
    _rotationAxisSet = false;
}
//-----------------------------------------------------------------------
PUDynamicAttribute* PUGeometryRotator::getRotationSpeed(void) const
{
    return _dynRotationSpeed;
}
//-----------------------------------------------------------------------
void PUGeometryRotator::setRotationSpeed(PUDynamicAttribute* dynRotationSpeed)
{
    if (_dynRotationSpeed)
        CC_SAFE_DELETE(_dynRotationSpeed);
    _dynRotationSpeed = dynRotationSpeed;
}
//-----------------------------------------------------------------------
bool PUGeometryRotator::useOwnRotationSpeed (void) const
{
    return _useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
void PUGeometryRotator::setUseOwnRotationSpeed (bool useOwnRotationSpeed)
{
    _useOwnRotationSpeed = useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
float PUGeometryRotator::calculateRotationSpeed(PUParticle3D* particle)
{
    return _dynamicAttributeHelper.calculate(_dynRotationSpeed, particle->timeFraction);
}
//-----------------------------------------------------------------------
void PUGeometryRotator::initParticleForEmission(PUParticle3D* particle)
{
    //// Only continue if the particle is a visual particle
    //if (particle->particleType != Particle::PT_VISUAL)
    //	return;
    //for (auto iter : _particleSystem->getParticlePool().getActiveParticleList())
    {
        //PUParticle3D *particle = static_cast<PUParticle3D*>(iter);
        if (!_rotationAxisSet)
        {
            // Set initial random rotation axis and orientation(PU 1.4)
            particle->orientation.x = CCRANDOM_MINUS1_1();
            particle->orientation.y = CCRANDOM_MINUS1_1();
            particle->orientation.z = CCRANDOM_MINUS1_1();
            particle->orientation.w = CCRANDOM_MINUS1_1();
            particle->orientation.normalize();
            particle->rotationAxis.x = CCRANDOM_0_1();
            particle->rotationAxis.y = CCRANDOM_0_1();
            particle->rotationAxis.z = CCRANDOM_0_1();
            particle->rotationAxis.normalize();
        }

        if (_useOwnRotationSpeed)
        {
            // Use the rotation speed of the particle itself
            particle->rotationSpeed = calculateRotationSpeed(particle);
        }
    }
}
//-----------------------------------------------------------------------

void PUGeometryRotator::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        // Rotate the geometry

        if (_useOwnRotationSpeed)
        {
            // Use scaled rotationspeed and adjust the speed according to the velocity
            _scaledRotationSpeed = particle->rotationSpeed * deltaTime;
        }
        else
        {
            // Scale speed (beware that dynamic values don't result in a rotation; use a fixed value instead)
            _scaledRotationSpeed = calculateRotationSpeed(particle) * deltaTime;
        }

        _q.set(0.0f, 0.0f, 0.0f, 1.0f);
        //_q = Quaternion::IDENTITY;
        if (_rotationAxisSet)
        {
            _q.set(_rotationAxis, _scaledRotationSpeed);
            //_q.FromAngleAxis(Radian(_scaledRotationSpeed), _rotationAxis);
        }
        else
        {
            _q.set(particle->rotationAxis, _scaledRotationSpeed);
            //_q.FromAngleAxis(Radian(_scaledRotationSpeed), visualParticle->rotationAxis);
        }

        particle->orientation = _q * particle->orientation;
    }
}

PUGeometryRotator* PUGeometryRotator::create()
{
    auto pgr = new (std::nothrow) PUGeometryRotator();
    pgr->autorelease();
    return pgr;
}

void PUGeometryRotator::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUGeometryRotator* geometryRotator = static_cast<PUGeometryRotator*>(affector);
    geometryRotator->setRotationSpeed(getRotationSpeed()->clone());
    geometryRotator->_useOwnRotationSpeed = _useOwnRotationSpeed;
    geometryRotator->_rotationAxis = _rotationAxis;
    geometryRotator->_rotationAxisSet = _rotationAxisSet;
}

//-----------------------------------------------------------------------

NS_CC_END
