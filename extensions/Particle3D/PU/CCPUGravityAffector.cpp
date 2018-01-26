/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPUGravityAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUGravityAffector::DEFAULT_GRAVITY = 1.0f;

//-----------------------------------------------------------------------
PUGravityAffector::PUGravityAffector(void) : 
    PUAffector(),
    _gravity(DEFAULT_GRAVITY)
{
}
//-----------------------------------------------------------------------
PUGravityAffector::~PUGravityAffector( void )
{

}
//-----------------------------------------------------------------------
float PUGravityAffector::getGravity(void) const
{
    return _gravity;
}
//-----------------------------------------------------------------------
void PUGravityAffector::setGravity(float gravity)
{
    _gravity = gravity;
}

void PUGravityAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
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

void PUGravityAffector::preUpdateAffector( float /*deltaTime*/ )
{
    getDerivedPosition();
}

PUGravityAffector* PUGravityAffector::create()
{
    auto pga = new (std::nothrow) PUGravityAffector();
    pga->autorelease();
    return pga;
}

void PUGravityAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUGravityAffector* gravityAffector = static_cast<PUGravityAffector*>(affector);
    gravityAffector->_gravity = _gravity;
}

NS_CC_END
