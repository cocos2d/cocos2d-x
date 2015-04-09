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

#include "CCPUInterParticleCollider.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DInterParticleCollider::DEFAULT_ADJUSTMENT = 1.0f;
const PUParticle3DInterParticleCollider::InterParticleCollisionResponse PUParticle3DInterParticleCollider::DEFAULT_COLLISION_RESPONSE = 
         PUParticle3DInterParticleCollider::IPCR_AVERAGE_VELOCITY;

//-----------------------------------------------------------------------
PUParticle3DInterParticleCollider::PUParticle3DInterParticleCollider(void) : 
    PUBaseCollider(),
    _adjustment(DEFAULT_ADJUSTMENT),
    _interParticleCollisionResponse(DEFAULT_COLLISION_RESPONSE)
{
}

PUParticle3DInterParticleCollider::~PUParticle3DInterParticleCollider( void )
{

}
//-----------------------------------------------------------------------
float PUParticle3DInterParticleCollider::getAdjustment(void) const
{
    return _adjustment;
}
//-----------------------------------------------------------------------
void PUParticle3DInterParticleCollider::setAdjustment(float adjustment)
{
    _adjustment = adjustment;
}
//-----------------------------------------------------------------------
PUParticle3DInterParticleCollider::InterParticleCollisionResponse PUParticle3DInterParticleCollider::getInterParticleCollisionResponse(void) const
{
    return _interParticleCollisionResponse;
}
//-----------------------------------------------------------------------
void PUParticle3DInterParticleCollider::setInterParticleCollisionResponse(PUParticle3DInterParticleCollider::InterParticleCollisionResponse interParticleCollisionResponse)
{
    _interParticleCollisionResponse = interParticleCollisionResponse;
}
//-----------------------------------------------------------------------
void PUParticle3DInterParticleCollider::prepare()
{
    // Activate spatial hashing
    //particleTechnique->setSpatialHashingUsed(true);
}
//-----------------------------------------------------------------------
void PUParticle3DInterParticleCollider::unPrepare()
{
    // Deactivate spatial hashing
    //particleTechnique->setSpatialHashingUsed(false);
}
//-----------------------------------------------------------------------
bool PUParticle3DInterParticleCollider::validateAndExecuteSphereCollision (PUParticle3D* particle1, PUParticle3D* particle2, float timeElapsed)
{
    PUParticle3D* vp1 = static_cast<PUParticle3D*>(particle1);
    PUParticle3D* vp2 = static_cast<PUParticle3D*>(particle2);
    if ((vp1->position - vp2->position).length() < _adjustment * (vp1->radius + vp2->radius))
    {
        /** Collision detected.
        @remarks
            The collision response calculation isn't accurate, but gives an acceptable result.
        */
        Vec3 n = vp1->position - vp2->position;
        n.normalize();
        switch(_interParticleCollisionResponse)
        {
            case IPCR_AVERAGE_VELOCITY:
            {
                // Use average velocity; this keeps the particles in movement.
                float velocity1 = vp1->direction.length();
                float velocity2 = vp2->direction.length();
                float averageVelocity = 0.5f * (velocity1 + velocity2);
                vp1->direction = averageVelocity * vp2->mass * n;
                vp2->direction = averageVelocity * vp1->mass * -n;
            }
            break;

            case IPCR_ANGLE_BASED_VELOCITY:
            {
                // The new velocity is based on the angle between original direction and new direction.
                // Note, that this usually means that the velocity decreases.

                float velocity1 = Vec3(std::abs(vp1->direction.x), std::abs(vp1->direction.y), std::abs(vp1->direction.z)).dot(n);
                float velocity2 = Vec3(std::abs(vp2->direction.x), std::abs(vp2->direction.y), std::abs(vp2->direction.z)).dot(n);
                vp1->direction = velocity1 * vp2->mass * n;
                vp2->direction = velocity2 * vp1->mass * -n;
            }
            break;
        }
        vp1->direction *= _bouncyness;
        vp2->direction *= _bouncyness;
        vp1->addEventFlags(PUParticle3D::PEF_COLLIDED);
        vp2->addEventFlags(PUParticle3D::PEF_COLLIDED);
        return true;
    }

    return false;
}
//-----------------------------------------------------------------------

void PUParticle3DInterParticleCollider::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //CCASSERT(0, "nonsupport yet");
    //for (auto iter : _particleSystem->getParticles())
    //{
    //    PUParticle3D *particle = iter;
    //     Fast rejection: only visible, moving particles are able to collide, unless they are colliding already
    //     Changed && into || in V1.3.1
    //    if (//particle->particleType != Particle::PT_VISUAL || 
    //        particle->hasEventFlags(PUParticle3D::PEF_COLLIDED) || 
    //        particle->direction == Vec3::ZERO)
    //    {
    //        return;
    //    }

    //    // Determine whether neighbour particles are colliding.
    //    SpatialHashTable<Particle*>* hashtable = particleTechnique->getSpatialHashTable();
    //    if (hashtable)
    //    {
    //    	SpatialHashTable<Particle*>::HashTableCell cell = hashtable->getCell(particle->position);
    //    	if (cell.empty())
    //    		return;

    //    	unsigned int size = static_cast<unsigned int>(cell.size());
    //    	for (unsigned int i = 0; i < size; ++i)
    //    	{
    //    		Particle* p = cell[i];

    //    		// Don't check if it is the same particle or the particle is already colliding.
    //    		if (particle != p  && !p->hasEventFlags(PUParticle3D::PEF_COLLIDED))
    //    		{
    //    			// Check for collision
    //    			if (validateAndExecuteSphereCollision(particle, p, deltaTime))
    //    			{
    //    				return;
    //    			}
    //    		}
    //    	}
    //    }
    //}
}

PUParticle3DInterParticleCollider* PUParticle3DInterParticleCollider::create()
{
    auto pipc = new (std::nothrow) PUParticle3DInterParticleCollider();
    pipc->autorelease();
    return pipc;
}

void PUParticle3DInterParticleCollider::copyAttributesTo( PUAffector* affector )
{
    PUBaseCollider::copyAttributesTo(affector);
    PUParticle3DInterParticleCollider* interParticleCollider = static_cast<PUParticle3DInterParticleCollider*>(affector);
    interParticleCollider->_adjustment = _adjustment;
    interParticleCollider->_interParticleCollisionResponse = _interParticleCollisionResponse;
}

NS_CC_END
