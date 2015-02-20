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

#include "CCPUParticle3DBoxCollider.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DBoxCollider::DEFAULT_WIDTH = 100.0f;
const float PUParticle3DBoxCollider::DEFAULT_HEIGHT = 100.0f;
const float PUParticle3DBoxCollider::DEFAULT_DEPTH = 100.0f;

//-----------------------------------------------------------------------
PUParticle3DBoxCollider::PUParticle3DBoxCollider() : 
    PUParticle3DBaseCollider(),
    _width(DEFAULT_WIDTH),
    _height(DEFAULT_HEIGHT),
    _depth(DEFAULT_DEPTH),
    _xmin(0.0f),
    _xmax(0.0f),
    _ymin(0.0f),
    _ymax(0.0f),
    _zmin(0.0f),
    _zmax(0.0f),
    _predictedPosition(Vec3::ZERO),
    _innerCollision(false)
{
}


PUParticle3DBoxCollider::~PUParticle3DBoxCollider()
{
}
//-----------------------------------------------------------------------
const float PUParticle3DBoxCollider::getWidth() const
{
    return _width;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxCollider::setWidth(const float width)
{
    _width = width;
}
//-----------------------------------------------------------------------
const float PUParticle3DBoxCollider::getHeight() const
{
    return _height;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxCollider::setHeight(const float height)
{
    _height = height;
}
//-----------------------------------------------------------------------
const float PUParticle3DBoxCollider::getDepth() const
{
    return _depth;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxCollider::setDepth(const float depth)
{
    _depth = depth;
}
//-----------------------------------------------------------------------
bool PUParticle3DBoxCollider::isInnerCollision(void) const
{
    return _innerCollision;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxCollider::setInnerCollision(bool innerCollision)
{
    _innerCollision = innerCollision;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxCollider::calculateDirectionAfterCollision(PUParticle3D* particle)
{
    switch (_collisionType)
    {
        case PUParticle3DBaseCollider::CT_BOUNCE:
        {
            // Determine the nearest side and reverse the direction
            if (isSmallestValue (particle->position.x - _xmin, particle->position))
            {		
                particle->direction.x *= -1;
            }
            else if (isSmallestValue (_xmax - particle->position.x, particle->position))
            {
                particle->direction.x *= -1;
            }
            else if (isSmallestValue (particle->position.y - _ymin, particle->position))
            {
                particle->direction.y *= -1;
            }
            else if (isSmallestValue (_ymax - particle->position.y, particle->position))
            {
                particle->direction.y *= -1;
            }
            else if (isSmallestValue (particle->position.z - _zmin, particle->position))
            {
                particle->direction.z *= -1;
            }
            else if (isSmallestValue (_zmax - particle->position.z, particle->position))
            {
                particle->direction.z *= -1;
            }
            particle->direction *= _bouncyness;
        }
        break;
        case PUParticle3DBaseCollider::CT_FLOW:
        {
            if (isSmallestValue (particle->position.x - _xmin, particle->position))
            {		
                particle->direction.x = 0;
            }
            else if (isSmallestValue (_xmax - particle->position.x, particle->position))
            {
                particle->direction.x = 0;
            }
            else if (isSmallestValue (particle->position.y - _ymin, particle->position))
            {
                particle->direction.y = 0;
            }
            else if (isSmallestValue (_ymax - particle->position.y, particle->position))
            {
                particle->direction.y = 0;
            }
            else if (isSmallestValue (particle->position.z - _zmin, particle->position))
            {
                particle->direction.z = 0;
            }
            else if (isSmallestValue (_zmax - particle->position.z, particle->position))
            {
                particle->direction.z = 0;
            }
            particle->direction *= -_friction;
        }
        break;
        default:
        break;
    }
}
//-----------------------------------------------------------------------
void PUParticle3DBoxCollider::calculateBounds ()
{
    float scaledWidth = _affectorScale.x * _width;
    float scaledHeight = _affectorScale.y * _height;
    float scaledDepth = _affectorScale.z * _depth;

    _xmin = _derivedPosition.x - 0.5f * scaledWidth;
    _xmax = _derivedPosition.x + 0.5f * scaledWidth;
    _ymin = _derivedPosition.y - 0.5f * scaledHeight;
    _ymax = _derivedPosition.y + 0.5f * scaledHeight;
    _zmin = _derivedPosition.z - 0.5f * scaledDepth;
    _zmax = _derivedPosition.z + 0.5f * scaledDepth;
}
//-----------------------------------------------------------------------
bool PUParticle3DBoxCollider::isSmallestValue(float value, const Vec3& particlePosition)
{
    float value1 = particlePosition.x - _xmin;
    float value2 = _xmax - particlePosition.x;
    float value3 = particlePosition.y - _ymin;
    float value4 = _ymax - particlePosition.y;
    float value5 = particlePosition.z - _zmin;
    float value6 = _zmax - particlePosition.z;

    return (
        value <= value1 && 
        value <= value2 &&
        value <= value3 && 
        value <= value4 &&
        value <= value5 &&
        value <= value6);
}

void PUParticle3DBoxCollider::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        _predictedPosition = particle->position + _velocityScale * particle->direction;
        bool collision = false;

        /** Collision detection is a two-step. First, we determine whether the particle is now colliding.
            If it is, the particle is re-positioned. However, a timeElapsed value is used, which is not the same
            as the one that was used at the moment before the particle was colliding. Therefore, we rather 
            want to predict particle collision in front. This probably isn't the fastest solution.
            The same approach was used for the other colliders.
        */
        switch(_intersectionType)
        {
            case PUParticle3DBaseCollider::IT_POINT:
            {
                // Validate for a point-box intersection
                if (_innerCollision != _box.containPoint(particle->position))
                {
                    // Collision detected (re-position the particle)
                    particle->position -= _velocityScale * particle->direction;
                    collision = true;
                }
                else if (_innerCollision != _box.containPoint(_predictedPosition))
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

                if (_innerCollision != box.intersects(_box))
                {
                    // Collision detected (re-position the particle)
                    particle->position -= _velocityScale * particle->direction;
                    collision = true;
                }
                else
                {
                    populateAlignedBox(box,
                        _predictedPosition, 
                        particle->width, 
                        particle->height,
                        particle->depth);
                    if (_innerCollision != box.intersects(_box))
                    {
                        // Collision detected
                        collision = true;
                    }
                }
            }
            break;
        }

        if (collision)
        {
            calculateDirectionAfterCollision(particle);
            calculateRotationSpeedAfterCollision(particle);
            particle->addEventFlags(PUParticle3D::PEF_COLLIDED);
        }
    }

}

void PUParticle3DBoxCollider::preUpdateAffector( float deltaTime )
{
    // Calculate the affectors' center position in worldspace, set the box and calculate the bounds
    // Applied scaling in V 1.3.1.
    populateAlignedBox(_box, getDerivedPosition(), _affectorScale.x * _width, _affectorScale.y * _height, _affectorScale.z * _depth);
    calculateBounds();
}

PUParticle3DBoxCollider* PUParticle3DBoxCollider::create()
{
    auto pbc = new (std::nothrow) PUParticle3DBoxCollider();
    pbc->autorelease();
    return pbc;
}

NS_CC_END