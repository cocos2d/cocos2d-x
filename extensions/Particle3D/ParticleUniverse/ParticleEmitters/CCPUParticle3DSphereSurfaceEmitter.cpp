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

#include "CCPUParticle3DSphereSurfaceEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DUtil.h"

NS_CC_BEGIN
// Constants
const float PUParticle3DSphereSurfaceEmitter::DEFAULT_RADIUS = 10.0f;

//-----------------------------------------------------------------------
PUParticle3DSphereSurfaceEmitter::PUParticle3DSphereSurfaceEmitter(void) : 
    PUParticle3DEmitter(),
    _radius(DEFAULT_RADIUS),
    _randomVector(Vec3::ZERO)
{
}
//-----------------------------------------------------------------------
const float PUParticle3DSphereSurfaceEmitter::getRadius(void) const
{
    return _radius;
}
//-----------------------------------------------------------------------
void PUParticle3DSphereSurfaceEmitter::setRadius(const float radius)
{
    _radius = radius;
}
//-----------------------------------------------------------------------
void PUParticle3DSphereSurfaceEmitter::initParticlePosition(PUParticle3D* particle)
{
    // Generate a random unit vector to calculate a point on the sphere. This unit vector is
    // also used as direction vector if mAutoDirection has been set.
    _randomVector = Vec3(CCRANDOM_MINUS1_1(), 
        CCRANDOM_MINUS1_1(),
        CCRANDOM_MINUS1_1());
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
void PUParticle3DSphereSurfaceEmitter::initParticleDirection(PUParticle3D* particle)
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
            particle->direction = PUParticle3DUtil::randomDeviant(_randomVector, angle, _upVector);
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
        PUParticle3DEmitter::initParticleDirection(particle);
    }
}

PUParticle3DSphereSurfaceEmitter* PUParticle3DSphereSurfaceEmitter::create()
{
    auto pe = new (std::nothrow) PUParticle3DSphereSurfaceEmitter();
    pe->autorelease();
    return pe;
}

NS_CC_END