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

#include "CCPUParticle3DPlaneCollider.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 PUParticle3DPlaneCollider::DEFAULT_NORMAL(0, 0, 0);

//-----------------------------------------------------------------------
PUParticle3DPlaneCollider::PUParticle3DPlaneCollider(void) : 
    PUParticle3DBaseCollider(),
    _predictedPosition(Vec3::ZERO),
    _normal(DEFAULT_NORMAL)
{
}
PUParticle3DPlaneCollider::~PUParticle3DPlaneCollider( void )
{

}
//-----------------------------------------------------------------------
const Vec3 PUParticle3DPlaneCollider::getNormal(void) const
{
    return _normal;
}
//-----------------------------------------------------------------------
void PUParticle3DPlaneCollider::setNormal(const Vec3& normal)
{
    _normal = normal;
    _plane.redefine(_normal, getDerivedPosition()); // Changed in 1.3.1
}
//-----------------------------------------------------------------------
void PUParticle3DPlaneCollider::notifyRescaled(const Vec3& scale)
{
    // Function added in 1.3.1
    _plane.redefine(_normal, getDerivedPosition());
}
//-----------------------------------------------------------------------
void PUParticle3DPlaneCollider::calculateDirectionAfterCollision(PUParticle3D* particle, float timeElapsed)
{
    float directionLength = particle->direction.length();
    switch (_collisionType)
    {
        case PUParticle3DBaseCollider::CT_BOUNCE:
        {
            /** If the particle is on the plane or at the back of the plane, bounce it.
                Make use of the same formula as the sphere collider.
            */
            particle->direction.normalize();
            particle->direction = 2 * (-particle->direction.dot(-_normal)) * -_normal + particle->direction;

            // Adjust to original speed
            particle->direction *= directionLength;

            // Accelerate/slow down, using the bounce value
            particle->direction *= _bouncyness;
        }
        break;
        case PUParticle3DBaseCollider::CT_FLOW:
        {
            /** Reset the position (just in front of the plane), but keep the direction.
            @remarks
                This is not really the correct way, because the particle 'jumps'. Maybe it is better to change 
                the direction parallel to the plane.
            */
            particle->position += timeElapsed * directionLength * _normal;
        }
        break;
        default:
        break;
    }
}

void PUParticle3DPlaneCollider::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        _predictedPosition = particle->position + _velocityScale * particle->direction;
        bool collision = false;

        switch(_intersectionType)
        {
        case PUParticle3DBaseCollider::IT_POINT:
            {
                // Validate for a point-plane intersection (on the plane or the back side)
                // First determine whether it is now colliding (some affector made the particle move), else
                // determine whether it WILL be colliding
                if (_plane.getDistance(particle->position) <= 0.0f)
                {
                    // Collision detected (re-position the particle)
                    particle->position -= _velocityScale * particle->direction;
                    collision = true;
                }
                else if (_plane.getDistance(_predictedPosition) <= 0.0f)
                {
                    // Collision detected
                    collision = true;
                }
            }
            break;

        case PUParticle3DBaseCollider::IT_BOX:
            {

                AABB box;
                populateAlignedBox(box,
                    particle->position, 
                    particle->width, 
                    particle->height,
                    particle->depth);
                //FIXME
                //if (box.intersects(_plane))
                //{
                //	// Collision detected (re-position the particle)
                //	particle->position -= _velocityScale * particle->direction;
                //	collision = true;
                //}
                //else 
                //{
                //	populateAlignedBox(box,
                //		_predictedPosition, 
                //		particle->width, 
                //		particle->height,
                //		particle->depth);
                //	if (box.intersects(_plane))
                //	{
                //		// Collision detected
                //		collision = true;
                //	}
                //}
            }
            break;
        }

        if (collision)
        {
            calculateDirectionAfterCollision(particle, deltaTime);
            calculateRotationSpeedAfterCollision(particle);
            particle->addEventFlags(PUParticle3D::PEF_COLLIDED);
        }
    }

}

PUParticle3DPlaneCollider* PUParticle3DPlaneCollider::create()
{
    auto ppc = new (std::nothrow) PUParticle3DPlaneCollider();
    ppc->autorelease();
    return ppc;
}

NS_CC_END