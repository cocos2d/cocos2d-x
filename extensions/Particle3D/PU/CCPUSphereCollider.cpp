/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CCPUSphereCollider.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const float PUSphereCollider::DEFAULT_RADIUS = 100.0f;

//-----------------------------------------------------------------------
PUSphereCollider::PUSphereCollider() : 
    PUBaseCollider(),
    _radius(DEFAULT_RADIUS),
    _innerCollision(false)
{
}

PUSphereCollider::~PUSphereCollider( void )
{

}

//-----------------------------------------------------------------------
float PUSphereCollider::getRadius() const
{
    return _radius;
}
//-----------------------------------------------------------------------
void PUSphereCollider::setRadius(const float radius)
{
    _radius = radius;
    _sphere.setRadius(_radius);
}
//-----------------------------------------------------------------------
bool PUSphereCollider::isInnerCollision() const
{
    return _innerCollision;
}
//-----------------------------------------------------------------------
void PUSphereCollider::setInnerCollision(bool innerCollision)
{
    _innerCollision = innerCollision;
}
//-----------------------------------------------------------------------
void PUSphereCollider::calculateDirectionAfterCollision(PUParticle3D* particle, Vec3 distance, float distanceLength)
{
    switch (_collisionType)
    {
        case PUBaseCollider::CT_BOUNCE:
        {
            /** If the particle is on the surface (or just inside the sphere); bounce it
                Make use of formula R = 2 * (-I dot N) * N + I, where
                R = the new direction vector
                I = the old (unit) direction vector before the collision
                N = the Normal at the collision point
            */
            float directionLength = particle->direction.length();
            particle->direction.normalize();
            distance.normalize();
            particle->direction = 2 * (-particle->direction.dot(distance)) * distance + particle->direction;

            // Adjust to original speed
            particle->direction *= directionLength;

            // Accelerate/slow down, using the bounce value
            particle->direction *= _bouncyness;
        }
        break;
        case PUBaseCollider::CT_FLOW:
        {
            /** Reset the position (on the sphere), but keep the direction.
                This doesn't really work good for box-type collisions, because it doesn't take the particle
                dimensions into account.
            */
            float scaledRadius = 0.3333f * (_affectorScale.x + _affectorScale.y + _affectorScale.z) * _radius;
            particle->position = _derivedPosition + distance * (scaledRadius / distanceLength);
        }
        break;
        default:
        break;
    }
}

void PUSphereCollider::updatePUAffector( PUParticle3D *particle, float /*deltaTime*/ )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        _predictedPosition = particle->position + _velocityScale * particle->direction;
        bool collision = false;
        Vec3 distance = particle->position - _derivedPosition;
        float distanceLength = distance.length();
        float scaledRadius = 0.3333f * (_affectorScale.x + _affectorScale.y + _affectorScale.z) * _radius; // Scaling changed in V 1.3.1

        switch(_intersectionType)
        {
        case PUBaseCollider::IT_POINT:
            {
                // Validate for a point-sphere intersection
                if (_innerCollision == (distanceLength > scaledRadius))
                {
                    // Collision detected (re-position the particle)
                    particle->position -= _velocityScale * particle->direction;
                    collision = true;
                }
                else
                {
                    distance = _predictedPosition - _derivedPosition;
                    distanceLength = distance.length();
                    if (_innerCollision == (distanceLength > scaledRadius))
                    {
                        // Collision detected
                        collision = true;
                    }
                }
            }
            break;

        case PUBaseCollider::IT_BOX:
            {
                //// Validate for a box-sphere intersection
                //if (particle->particleType != Particle::PT_VISUAL)
                //	break;
                AABB box;
                populateAlignedBox(box,
                    particle->position, 
                    particle->width, 
                    particle->height,
                    particle->depth);

                //FIXME
                //if (_innerCollision != box.intersects(_sphere))
                //{
                //	// Collision detected (re-position the particle)
                //	particle->position -= _velocityScale * particle->direction;
                //	collision = true;
                //}
                //else
                //{
                //	AABB box;
                //	populateAlignedBox(box,
                //		_predictedPosition, 
                //		particle->width, 
                //		particle->height,
                //		particle->depth);
                //	if (_innerCollision != box.intersects(_sphere))
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
            calculateDirectionAfterCollision(particle, distance, distanceLength);
            calculateRotationSpeedAfterCollision(particle);
            particle->addEventFlags(PUParticle3D::PEF_COLLIDED);
        }
    }
}

void PUSphereCollider::preUpdateAffector( float /*deltaTime*/ )
{
    // Calculate the affectors' center position.
    _sphere.setCenter(getDerivedPosition());
}

PUSphereCollider* PUSphereCollider::create()
{
    auto psc = new (std::nothrow) PUSphereCollider();
    psc->autorelease();
    return psc;
}

void PUSphereCollider::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUSphereCollider* sphereCollider = static_cast<PUSphereCollider*>(affector);
    sphereCollider->_radius = _radius;
    sphereCollider->_sphere = _sphere;
    sphereCollider->_innerCollision = _innerCollision;
}

NS_CC_END
