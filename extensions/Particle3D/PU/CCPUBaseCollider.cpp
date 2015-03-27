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

#include "CCPUBaseCollider.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUBaseCollider::DEFAULT_BOUNCYNESS = 1.0f;
const float PUBaseCollider::DEFAULT_FRICTION = 0.0f;
const PUBaseCollider::IntersectionType PUBaseCollider::DEFAULT_INTERSECTION_TYPE = PUBaseCollider::IT_POINT;
const PUBaseCollider::CollisionType PUBaseCollider::DEFAULT_COLLISION_TYPE = PUBaseCollider::CT_BOUNCE;
//-----------------------------------------------------------------------
PUBaseCollider::PUBaseCollider() 
    : PUAffector()
    , _friction(DEFAULT_FRICTION)
    , _bouncyness(DEFAULT_BOUNCYNESS)
    , _intersectionType(DEFAULT_INTERSECTION_TYPE)
    , _collisionType(DEFAULT_COLLISION_TYPE)
    , _velocityScale(1.0f)
{
}

PUBaseCollider::~PUBaseCollider()
{
}

const PUBaseCollider::IntersectionType PUBaseCollider::getIntersectionType() const
{
    return _intersectionType;
}

void PUBaseCollider::setIntersectionType( const IntersectionType& intersectionType )
{
    _intersectionType = intersectionType;
}

const PUBaseCollider::CollisionType PUBaseCollider::getCollisionType() const
{
    return _collisionType;
}

void PUBaseCollider::setCollisionType( const CollisionType& collisionType )
{
    _collisionType = collisionType;
}

const float PUBaseCollider::getFriction() const
{
    return _friction;
}

void PUBaseCollider::setFriction( const float friction )
{
    _friction = friction;
}

const float PUBaseCollider::getBouncyness() const
{
    return _bouncyness;
}

void PUBaseCollider::setBouncyness( const float bouncyness )
{
    _bouncyness = bouncyness;
}

void PUBaseCollider::populateAlignedBox( AABB& box, const Vec3& position, const float width, const float height, const float depth )
{
    float halfWidth = 0.5f * width;
    float halfHeight = 0.5f * height;
    float halfDepth = 0.5f * depth;
    box.set(Vec3(position.x - halfWidth, 
        position.y - halfHeight, 
        position.z - halfDepth),
        Vec3(position.x + halfWidth, 
        position.y + halfHeight, 
        position.z + halfDepth));
}

void PUBaseCollider::calculateRotationSpeedAfterCollision( PUParticle3D* particle )
{
    if (particle->particleType != PUParticle3D::PT_VISUAL)
        return;

    float signedFriction = CCRANDOM_0_1() > 0.5 ? -(_friction - 1) : (_friction - 1);

    particle->rotationSpeed *= signedFriction;
    particle->zRotationSpeed *= signedFriction;
}

void PUBaseCollider::preUpdateAffector( float deltaTime )
{
    // Take scaled velocity into account
    _velocityScale = deltaTime * (static_cast<PUParticleSystem3D *>(_particleSystem))->getParticleSystemScaleVelocity();
}

void PUBaseCollider::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUBaseCollider* baseCollider = static_cast<PUBaseCollider*>(affector);
    baseCollider->_bouncyness = _bouncyness;
    baseCollider->_friction = _friction;
    baseCollider->_intersectionType = _intersectionType;
    baseCollider->_collisionType = _collisionType;
}

NS_CC_END
