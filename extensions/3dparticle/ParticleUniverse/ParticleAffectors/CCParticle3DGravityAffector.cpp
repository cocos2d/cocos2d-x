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

#include "CCParticle3DGravityAffector.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float Particle3DGravityAffector::DEFAULT_GRAVITY = 1.0f;

//-----------------------------------------------------------------------
Particle3DGravityAffector::Particle3DGravityAffector(void) : 
    PUParticle3DAffector(),
    _gravity(DEFAULT_GRAVITY)
{
}
//-----------------------------------------------------------------------
Particle3DGravityAffector::~Particle3DGravityAffector( void )
{

}
//-----------------------------------------------------------------------
float Particle3DGravityAffector::getGravity(void) const
{
    return _gravity;
}
//-----------------------------------------------------------------------
void Particle3DGravityAffector::setGravity(float gravity)
{
    _gravity = gravity;
}

void Particle3DGravityAffector::updateAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        // Applied scaling in V1.3.1
        /** Applying Newton's law of universal gravitation.	*/
        Vec3 distance = _derivedPosition - particle->position;
        float length = distance.lengthSquared();
        float scaleVelocity = 1.0f;
        //if (mParentTechnique)
        {
            scaleVelocity = _particleSystem->getParticleSystemScaleVelocity();
        }
        if (length > 0/* && mParentTechnique*/)
        {
            //Real force = (mGravity * particle->mass * mass) / length;
            float force = (scaleVelocity * _gravity * particle->mass/* * mass*/) / length;
            particle->direction += force * distance * deltaTime * calculateAffectSpecialisationFactor(particle);
        }
    }
}

void Particle3DGravityAffector::preUpdateAffector( float deltaTime )
{
    getDerivedPosition();
}

NS_CC_END