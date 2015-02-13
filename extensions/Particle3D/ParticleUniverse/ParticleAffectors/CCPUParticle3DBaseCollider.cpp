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

#include "CCPUParticle3DBaseCollider.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DBaseCollider::DEFAULT_BOUNCYNESS = 1.0f;
const float PUParticle3DBaseCollider::DEFAULT_FRICTION = 0.0f;
const PUParticle3DBaseCollider::IntersectionType PUParticle3DBaseCollider::DEFAULT_INTERSECTION_TYPE = PUParticle3DBaseCollider::IT_POINT;
const PUParticle3DBaseCollider::CollisionType PUParticle3DBaseCollider::DEFAULT_COLLISION_TYPE = PUParticle3DBaseCollider::CT_BOUNCE;
//-----------------------------------------------------------------------
PUParticle3DBaseCollider::PUParticle3DBaseCollider() 
    : PUParticle3DAffector()
    , _bouncyness(DEFAULT_BOUNCYNESS)
    , _friction(DEFAULT_FRICTION)
    , _intersectionType(DEFAULT_INTERSECTION_TYPE)
    , _collisionType(DEFAULT_COLLISION_TYPE)
    , _velocityScale(1.0f)
{
}

PUParticle3DBaseCollider::~PUParticle3DBaseCollider()
{
}

const PUParticle3DBaseCollider::IntersectionType PUParticle3DBaseCollider::getIntersectionType() const
{
    return _intersectionType;
}

void PUParticle3DBaseCollider::setIntersectionType( const IntersectionType& intersectionType )
{
    _intersectionType = intersectionType;
}

const PUParticle3DBaseCollider::CollisionType PUParticle3DBaseCollider::getCollisionType() const
{
    return _collisionType;
}

void PUParticle3DBaseCollider::setCollisionType( const CollisionType& collisionType )
{
    _collisionType = collisionType;
}

const float PUParticle3DBaseCollider::getFriction() const
{
    return _friction;
}

void PUParticle3DBaseCollider::setFriction( const float friction )
{
    _friction = friction;
}

const float PUParticle3DBaseCollider::getBouncyness() const
{
    return _bouncyness;
}

void PUParticle3DBaseCollider::setBouncyness( const float bouncyness )
{
    _bouncyness = bouncyness;
}

void PUParticle3DBaseCollider::populateAlignedBox( AABB& box, const Vec3& position, const float width, const float height, const float depth )
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

void PUParticle3DBaseCollider::calculateRotationSpeedAfterCollision( PUParticle3D* particle )
{
    float signedFriction = CCRANDOM_0_1() > 0.5 ? -(_friction - 1) : (_friction - 1);

    particle->rotationSpeed *= signedFriction;
    particle->zRotationSpeed *= signedFriction;
}

void PUParticle3DBaseCollider::preUpdateAffector( float deltaTime )
{
    // Take scaled velocity into account
    _velocityScale = deltaTime * (static_cast<PUParticleSystem3D *>(_particleSystem))->getParticleSystemScaleVelocity();
}

NS_CC_END