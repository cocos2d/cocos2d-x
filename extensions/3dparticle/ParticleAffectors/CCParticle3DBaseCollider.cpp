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

#include "CCParticle3DBaseCollider.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float Particle3DBaseCollider::DEFAULT_BOUNCYNESS = 1.0f;
const float Particle3DBaseCollider::DEFAULT_FRICTION = 0.0f;
const Particle3DBaseCollider::IntersectionType Particle3DBaseCollider::DEFAULT_INTERSECTION_TYPE = Particle3DBaseCollider::IT_POINT;
const Particle3DBaseCollider::CollisionType Particle3DBaseCollider::DEFAULT_COLLISION_TYPE = Particle3DBaseCollider::CT_BOUNCE;
//-----------------------------------------------------------------------
Particle3DBaseCollider::Particle3DBaseCollider() 
    : Particle3DAffector()
{
}

Particle3DBaseCollider::~Particle3DBaseCollider()
{
}

const Particle3DBaseCollider::IntersectionType Particle3DBaseCollider::getIntersectionType() const
{
	return _intersectionType;
}

void Particle3DBaseCollider::setIntersectionType( const IntersectionType& intersectionType )
{
	_intersectionType = intersectionType;
}

const Particle3DBaseCollider::CollisionType Particle3DBaseCollider::getCollisionType() const
{
	return _collisionType;
}

void Particle3DBaseCollider::setCollisionType( const CollisionType& collisionType )
{
	_collisionType = collisionType;
}

const float Particle3DBaseCollider::getFriction() const
{
	return _friction;
}

void Particle3DBaseCollider::setFriction( const float friction )
{
	_friction = friction;
}

const float Particle3DBaseCollider::getBouncyness() const
{
	return _bouncyness;
}

void Particle3DBaseCollider::setBouncyness( const float bouncyness )
{
	_bouncyness = bouncyness;
}

void Particle3DBaseCollider::populateAlignedBox( AABB& box, const Vec3& position, const float width, const float height, const float depth )
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

void Particle3DBaseCollider::calculateRotationSpeedAfterCollision( Particle3D* particle )
{
	float signedFriction = CCRANDOM_0_1() > 0.5 ? -(_friction - 1) : (_friction - 1);

	particle->rotationSpeed *= signedFriction;
	particle->zRotationSpeed *= signedFriction;
}

NS_CC_END