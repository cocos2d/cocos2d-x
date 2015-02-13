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

#include "CCPUParticle3DGravityAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DGravityAffector::DEFAULT_GRAVITY = 1.0f;

//-----------------------------------------------------------------------
PUParticle3DGravityAffector::PUParticle3DGravityAffector(void) : 
    PUParticle3DAffector(),
    _gravity(DEFAULT_GRAVITY)
{
}
//-----------------------------------------------------------------------
PUParticle3DGravityAffector::~PUParticle3DGravityAffector( void )
{

}
//-----------------------------------------------------------------------
float PUParticle3DGravityAffector::getGravity(void) const
{
    return _gravity;
}
//-----------------------------------------------------------------------
void PUParticle3DGravityAffector::setGravity(float gravity)
{
    _gravity = gravity;
}

void PUParticle3DGravityAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
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
            scaleVelocity = (static_cast<PUParticleSystem3D *>(_particleSystem))->getParticleSystemScaleVelocity();
        }
        if (length > 0/* && mParentTechnique*/)
        {
            //Real force = (mGravity * particle->mass * mass) / length;
            float force = (scaleVelocity * _gravity * particle->mass * _mass) / length;
            particle->direction += force * distance * deltaTime * calculateAffectSpecialisationFactor(particle);
        }
    }
}

void PUParticle3DGravityAffector::preUpdateAffector( float deltaTime )
{
    getDerivedPosition();
}

PUParticle3DGravityAffector* PUParticle3DGravityAffector::create()
{
    auto pga = new (std::nothrow) PUParticle3DGravityAffector();
    pga->autorelease();
    return pga;
}

NS_CC_END