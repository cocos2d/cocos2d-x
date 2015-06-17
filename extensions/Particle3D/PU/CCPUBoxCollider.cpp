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

#include "CCPUBoxCollider.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUBoxCollider::DEFAULT_WIDTH = 100.0f;
const float PUBoxCollider::DEFAULT_HEIGHT = 100.0f;
const float PUBoxCollider::DEFAULT_DEPTH = 100.0f;

//-----------------------------------------------------------------------
PUBoxCollider::PUBoxCollider() : 
    PUBaseCollider(),
    _width(DEFAULT_WIDTH),
    _height(DEFAULT_HEIGHT),
    _depth(DEFAULT_DEPTH),
    _xmin(0.0f),
    _xmax(0.0f),
    _ymin(0.0f),
    _ymax(0.0f),
    _zmin(0.0f),
    _zmax(0.0f),
    _innerCollision(false)
{
}


PUBoxCollider::~PUBoxCollider()
{
}
//-----------------------------------------------------------------------
const float PUBoxCollider::getWidth() const
{
    return _width;
}
//-----------------------------------------------------------------------
void PUBoxCollider::setWidth(const float width)
{
    _width = width;
}
//-----------------------------------------------------------------------
const float PUBoxCollider::getHeight() const
{
    return _height;
}
//-----------------------------------------------------------------------
void PUBoxCollider::setHeight(const float height)
{
    _height = height;
}
//-----------------------------------------------------------------------
const float PUBoxCollider::getDepth() const
{
    return _depth;
}
//-----------------------------------------------------------------------
void PUBoxCollider::setDepth(const float depth)
{
    _depth = depth;
}
//-----------------------------------------------------------------------
bool PUBoxCollider::isInnerCollision(void) const
{
    return _innerCollision;
}
//-----------------------------------------------------------------------
void PUBoxCollider::setInnerCollision(bool innerCollision)
{
    _innerCollision = innerCollision;
}
//-----------------------------------------------------------------------
void PUBoxCollider::calculateDirectionAfterCollision(PUParticle3D* particle)
{
    switch (_collisionType)
    {
        case PUBaseCollider::CT_BOUNCE:
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
        case PUBaseCollider::CT_FLOW:
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
void PUBoxCollider::calculateBounds ()
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
bool PUBoxCollider::isSmallestValue(float value, const Vec3& particlePosition)
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

void PUBoxCollider::updatePUAffector( PUParticle3D *particle, float deltaTime )
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
            case PUBaseCollider::IT_POINT:
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

            case PUBaseCollider::IT_BOX:
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

void PUBoxCollider::preUpdateAffector( float deltaTime )
{
    PUBaseCollider::preUpdateAffector(deltaTime);
    // Calculate the affectors' center position in worldspace, set the box and calculate the bounds
    // Applied scaling in V 1.3.1.
    populateAlignedBox(_box, getDerivedPosition(), _affectorScale.x * _width, _affectorScale.y * _height, _affectorScale.z * _depth);
    calculateBounds();
}

PUBoxCollider* PUBoxCollider::create()
{
    auto pbc = new (std::nothrow) PUBoxCollider();
    pbc->autorelease();
    return pbc;
}

void PUBoxCollider::copyAttributesTo( PUAffector* affector )
{
    PUBaseCollider::copyAttributesTo(affector);

    PUBoxCollider* boxCollider = static_cast<PUBoxCollider*>(affector);
    boxCollider->_width = _width;
    boxCollider->_height = _height;
    boxCollider->_depth = _depth;
    boxCollider->_innerCollision = _innerCollision;
}

NS_CC_END
