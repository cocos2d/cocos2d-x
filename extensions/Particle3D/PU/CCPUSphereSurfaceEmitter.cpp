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

#include "CCPUSphereSurfaceEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUUtil.h"

NS_CC_BEGIN
// Constants
const float PUSphereSurfaceEmitter::DEFAULT_RADIUS = 10.0f;

//-----------------------------------------------------------------------
PUSphereSurfaceEmitter::PUSphereSurfaceEmitter(void) : 
    PUEmitter(),
    _radius(DEFAULT_RADIUS)
{
}
//-----------------------------------------------------------------------
const float PUSphereSurfaceEmitter::getRadius(void) const
{
    return _radius;
}
//-----------------------------------------------------------------------
void PUSphereSurfaceEmitter::setRadius(const float radius)
{
    _radius = radius;
}
//-----------------------------------------------------------------------
void PUSphereSurfaceEmitter::initParticlePosition(PUParticle3D* particle)
{
    // Generate a random unit vector to calculate a point on the sphere. This unit vector is
    // also used as direction vector if mAutoDirection has been set.
    _randomVector.set(CCRANDOM_MINUS1_1(), CCRANDOM_MINUS1_1(), CCRANDOM_MINUS1_1());
    _randomVector.normalize();
    //ParticleSystem* sys = mParentTechnique->getParentSystem();
    //if (sys)
    {
        Mat4 rotMat;
        Mat4::createRotation(static_cast<PUParticleSystem3D *>(_particleSystem)->getDerivedOrientation(), &rotMat);
        particle->position = getDerivedPosition() + rotMat * (Vec3(_emitterScale.x * _randomVector.x, _emitterScale.y * _randomVector.y, _emitterScale.z * _randomVector.z) * _radius);
    }
    //else
    //{
    //	particle->position = getDerivedPosition() + (_mEmitterScale * _randomVector * _radius);
    //}
    particle->originalPosition = particle->position;
}
//-----------------------------------------------------------------------
void PUSphereSurfaceEmitter::initParticleDirection(PUParticle3D* particle)
{
    if (_autoDirection)
    {
        // The value of the direction vector that has been set does not have a meaning for
        // the sphere surface emitter.
        float angle = 0.0f;
        generateAngle(angle);
        if (angle != 0.0f)
        {
            //particle->direction = _randomVector.randomDeviant(angle, mUpVector);
            particle->direction = PUUtil::randomDeviant(_randomVector, angle, _upVector);
            particle->originalDirection = particle->direction;
        }
        else
        {
            particle->direction = _randomVector;
            particle->originalDirection = particle->direction;
        }
    }
    else
    {
        // Use the standard way
        PUEmitter::initParticleDirection(particle);
    }
}

PUSphereSurfaceEmitter* PUSphereSurfaceEmitter::create()
{
    auto pe = new (std::nothrow) PUSphereSurfaceEmitter();
    pe->autorelease();
    return pe;
}

void PUSphereSurfaceEmitter::copyAttributesTo( PUEmitter* emitter )
{
    PUEmitter::copyAttributesTo(emitter);

    PUSphereSurfaceEmitter* sphereSurfaceEmitter = static_cast<PUSphereSurfaceEmitter*>(emitter);
    sphereSurfaceEmitter->_radius = _radius;
}

PUSphereSurfaceEmitter* PUSphereSurfaceEmitter::clone()
{
    auto be = PUSphereSurfaceEmitter::create();
    copyAttributesTo(be);
    return be;
}

NS_CC_END
