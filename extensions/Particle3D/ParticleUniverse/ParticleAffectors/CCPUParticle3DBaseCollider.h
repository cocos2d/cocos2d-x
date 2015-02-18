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


#ifndef __CC_PU_PARTICLE_3D_BASE_COLLIDER_H__
#define __CC_PU_PARTICLE_3D_BASE_COLLIDER_H__

#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "3d/CCAABB.h"

NS_CC_BEGIN

struct PUParticle3D;
class  CC_DLL PUParticle3DBaseCollider : public PUParticle3DAffector
{
public:
    /** Determines how a particle collision should be determined. IT_POINT means that the position of 
        the particle will be validated against the Colliders' shape. IT_BOX means that the dimensions
        (width, height and depth) are used to determine whether the particle collides.
    */
    enum IntersectionType
    {
        IT_POINT,
        IT_BOX
    };

    /** Determines how a particle behaves after collision with this collider. The behaviour of the
        particle is solved in the collider and only behaviour that needs the colliders?data is taken
        into account. The fact that a particle expires for example, can be achieved by using an 
        Observer in combination with an EventHandler (DoExpireEventHandler).
        CT_NONE means that the particle doesn do anything. This value should be set if the behaviour 
        of the particle is determined outside the collider (for example, expiring the particle).
        CT_BOUNCE means that the particle bounces off the collider.
        CT_FLOW means that the particle flows around the contours of the collider.
    */
    enum CollisionType
    {
        CT_NONE,
        CT_BOUNCE,
        CT_FLOW,
    };

    // Constants
    static const float DEFAULT_BOUNCYNESS;
    static const float DEFAULT_FRICTION;
    static const IntersectionType DEFAULT_INTERSECTION_TYPE;
    static const CollisionType DEFAULT_COLLISION_TYPE;

    virtual void preUpdateAffector(float deltaTime) override;

        /** Returns the type of intersection.
    */
    const IntersectionType getIntersectionType() const;

    /** Sets the type of intersection.
    */
    void setIntersectionType(const IntersectionType& intersectionType);

    /** Returns the type of collision.
    */
    const CollisionType getCollisionType() const;

    /** Sets the type of collision.
    */
    void setCollisionType(const CollisionType& collisionType);

    /** Returns the friction value.
    */
    const float getFriction() const;

    /** Sets the friction value.
    */
    void setFriction(const float friction);

    /** Returns the bouncyness value.
    */
    const float getBouncyness() const;

    /** Sets the bouncyness value.
    */
    void setBouncyness(const float bouncyness);

    /** Fill the AxisAlignedBox with data derived from the other arguments.
    */
    void populateAlignedBox(AABB& box,
        const Vec3& position, 
        const float width,
        const float height,
        const float depth);

    /** Recalculates the rotation speed after collision.
        This function must be explicitly called in the updatePUAffector(float deltaTime) function of the class that inherits from 
        BaseCollider.
    */
    void calculateRotationSpeedAfterCollision(PUParticle3D* particle);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DBaseCollider();
    virtual ~PUParticle3DBaseCollider();

protected:

    float _friction; // Physics characteristic that influences particle rotation speed.
    float _bouncyness; // Physics characteristic that influences particle velocity.
    IntersectionType _intersectionType;
    CollisionType _collisionType;
    float _velocityScale; // Value set in the particle system, but stored in the collider for convenience.

};
NS_CC_END

#endif