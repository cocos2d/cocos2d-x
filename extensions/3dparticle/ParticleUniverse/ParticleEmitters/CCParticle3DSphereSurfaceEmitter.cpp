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

#include "CCParticle3DSphereSurfaceEmitter.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const float Particle3DSphereSurfaceEmitter::DEFAULT_RADIUS = 10.0f;

//-----------------------------------------------------------------------
Particle3DSphereSurfaceEmitter::Particle3DSphereSurfaceEmitter(void) : 
    PUParticle3DEmitter(),
    _radius(DEFAULT_RADIUS),
    _randomVector(Vec3::ZERO)
{
}
//-----------------------------------------------------------------------
const float Particle3DSphereSurfaceEmitter::getRadius(void) const
{
    return _radius;
}
//-----------------------------------------------------------------------
void Particle3DSphereSurfaceEmitter::setRadius(const float radius)
{
    _radius = radius;
}
//-----------------------------------------------------------------------
void Particle3DSphereSurfaceEmitter::initParticlePosition(PUParticle3D* particle)
{
    // Generate a random unit vector to calculate a point on the sphere. This unit vector is
    // also used as direction vector if mAutoDirection has been set.
    _randomVector = Vec3(CCRANDOM_0_1(), 
        CCRANDOM_0_1(),
        CCRANDOM_0_1());
    _randomVector.normalize();
    //ParticleSystem* sys = mParentTechnique->getParentSystem();
    //if (sys)
    {
        particle->position = getDerivedPosition() + /*_particleSystem->getDerivedOrientation() * */(Vec3(_emitterScale.x * _randomVector.x, _emitterScale.y * _randomVector.y, _emitterScale.z * _randomVector.z) * _radius);
    }
    //else
    //{
    //	particle->position = getDerivedPosition() + (_mEmitterScale * _randomVector * _radius);
    //}
    particle->originalPosition = particle->position;
}
//-----------------------------------------------------------------------
void Particle3DSphereSurfaceEmitter::initParticleDirection(PUParticle3D* particle)
{
    if (_autoDirection)
    {
        // The value of the direction vector that has been set does not have a meaning for
        // the sphere surface emitter.
        float angle = 0.0f;
        generateAngle(angle);
        if (angle != 0.0f)
        {
            //FIXME
            //particle->direction = _randomVector.randomDeviant(angle, mUpVector);
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
NS_CC_END