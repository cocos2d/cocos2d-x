/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#ifndef __CCPHYSICS_BODY_H__
#define __CCPHYSICS_BODY_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "physics/CCPhysicsShape.h"
#include "base/CCVector.h"

struct cpBody;

NS_CC_BEGIN

class Node;
class Sprite;
class PhysicsWorld;
class PhysicsJoint;

typedef Vec2 Vect;


const PhysicsMaterial PHYSICSBODY_MATERIAL_DEFAULT(0.1f, 0.5f, 0.5f);

/**
 * A body affect by physics.
 * it can attach one or more shapes.
 * if you create body with createXXX, it will automatically compute mass and moment with density your specified(which is PHYSICSBODY_MATERIAL_DEFAULT by default, and the density value is 0.1f), and it based on the formular: mass = density * area.
 * if you create body with createEdgeXXX, the mass and moment will be PHYSICS_INFINITY by default. and it's a static body.
 * you can change mass and moment with setMass() and setMoment(). and you can change the body to be dynamic or static by use function setDynamic().
 */
class CC_DLL PhysicsBody : public Ref
{
public:
    /** create a body with defult mass and moment. */
    static PhysicsBody* create();
    /** create a body with mass and defult moment. */
    static PhysicsBody* create(float mass);
    /** create a body with mass and moment. */
    static PhysicsBody* create(float mass, float moment);
    /** Create a body contains a circle shape. */
    static PhysicsBody* createCircle(float radius, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    /** Create a body contains a box shape. */
    static PhysicsBody* createBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    /**
     * @brief Create a body contains a polygon shape.
     * points is an array of Vec2 structs defining a convex hull with a clockwise winding.
     */
    static PhysicsBody* createPolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
    /** Create a body contains a EdgeSegment shape. */
    static PhysicsBody* createEdgeSegment(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    /** Create a body contains a EdgeBox shape. */
    static PhysicsBody* createEdgeBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);
    /** Create a body contains a EdgePolygon shape. */
    static PhysicsBody* createEdgePolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    /** Create a body contains a EdgeChain shape. */
    static PhysicsBody* createEdgeChain(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    
    /*
     * @brief add a shape to body
     * @param shape the shape to be added
     * @param addMassAndMoment if this is true, the shape's mass and moment will be added to body. the default is true
     */
    virtual PhysicsShape* addShape(PhysicsShape* shape, bool addMassAndMoment = true);
    /*
     * @brief remove a shape from body
     * @param shape the shape to be removed
     * @param reduceMassAndMoment if this is true, the body mass and moment will be reduced by shape. the default is true
     */
    void removeShape(PhysicsShape* shape, bool reduceMassAndMoment = true);
    /*
     * @brief remove a shape from body
     * @param tag the tag of the shape to be removed
     * @param reduceMassAndMoment if this is true, the body mass and moment will be reduced by shape. the default is true
     */
    void removeShape(int tag, bool reduceMassAndMoment = true);
    /* remove all shapes */
    void removeAllShapes(bool reduceMassAndMoment = true);
    /* get the body shapes. */
    inline const Vector<PhysicsShape*>& getShapes() const { return _shapes; }
    /* get the first shape of the body shapes. */
    inline PhysicsShape* getFirstShape() const { return _shapes.size() >= 1 ? _shapes.at(0) : nullptr; }
    /* get the shape of the body. */
    PhysicsShape* getShape(int tag) const;
    
    /** Applies a immediate force to body. */
    virtual void applyForce(const Vect& force);
    /** Applies a immediate force to body. */
    virtual void applyForce(const Vect& force, const Vec2& offset);
    /** reset all the force applied to body. */
    virtual void resetForces();
    /** Applies a continuous force to body. */
    virtual void applyImpulse(const Vect& impulse);
    /** Applies a continuous force to body. */
    virtual void applyImpulse(const Vect& impulse, const Vec2& offset);
    /** Applies a torque force to body. */
    virtual void applyTorque(float torque);
    
    /** set the velocity of a body */
    virtual void setVelocity(const Vect& velocity);
    /** get the velocity of a body */
    virtual Vec2 getVelocity();
    /** set the angular velocity of a body */
    virtual void setAngularVelocity(float velocity);
    /** get the angular velocity of a body at a local point */
    virtual Vec2 getVelocityAtLocalPoint(const Vec2& point);
    /** get the angular velocity of a body at a world point */
    virtual Vec2 getVelocityAtWorldPoint(const Vec2& point);
    /** get the angular velocity of a body */
    virtual float getAngularVelocity();
    /** set the max of velocity */
    virtual void setVelocityLimit(float limit);
    /** get the max of velocity */
    virtual float getVelocityLimit();
    /** set the max of angular velocity */
    virtual void setAngularVelocityLimit(float limit);
    /** get the max of angular velocity */
    virtual float getAngularVelocityLimit();
    
    /** remove the body from the world it added to */
    void removeFromWorld();
    
    /** get the world body added to. */
    inline PhysicsWorld* getWorld() const { return _world; }
    /** get all joints the body have */
    inline const std::vector<PhysicsJoint*>& getJoints() const { return _joints; }
    
    /** get the sprite the body set to. */
    inline Node* getNode() const { return _node; }
    
    /**
     * A mask that defines which categories this physics body belongs to.
     * Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.
     * The default value is 0xFFFFFFFF (all bits set).
     */
    void setCategoryBitmask(int bitmask);
    /** 
     * A mask that defines which categories of bodies cause intersection notifications with this physics body.
     * When two bodies share the same space, each body’s category mask is tested against the other body’s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.
     * The default value is 0x00000000 (all bits cleared).
     */
    void setContactTestBitmask(int bitmask);
    /**
     * A mask that defines which categories of physics bodies can collide with this physics body.
     * When two physics bodies contact each other, a collision may occur. This body’s collision mask is compared to the other body’s category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body’s velocity.
     * The default value is 0xFFFFFFFF (all bits set).
     */
    void setCollisionBitmask(int bitmask);
    /** Return bitmask of first shape, if there is no shape in body, return default value.(0xFFFFFFFF) */
    int getCategoryBitmask() const;
    /** Return bitmask of first shape, if there is no shape in body, return default value.(0x00000000) */
    int getContactTestBitmask() const;
    /** Return bitmask of first shape, if there is no shape in body, return default value.(0xFFFFFFFF) */
    int getCollisionBitmask() const;
    
    /** 
     * set the group of body
     * Collision groups let you specify an integral group index. You can have all fixtures with the same group index always collide (positive index) or never collide (negative index)
     * it have high priority than bit masks
     */
    void setGroup(int group);
    /** Return group of first shape, if there is no shape in body, return default value.(0) */
    int getGroup() const;
    
    /** get the body position. */
    const Vec2& getPosition();
    /** get the body rotation. */
    float getRotation();
    
    /** set body position offset, it's the position witch relative to node */
    void setPositionOffset(const Vec2& position);
    /** get body position offset. */
    const Vec2& getPositionOffset() const { return _positionOffset; }
    /** set body rotation offset, it's the rotation witch relative to node */
    void setRotationOffset(float rotation);
    /** set the body rotation offset */
    float getRotationOffset() const { return _rotationOffset; }
    
    /**
     * @brief test the body is dynamic or not.
     * a dynamic body will effect with gravity.
     */
    inline bool isDynamic() const { return _dynamic; }
    /**
     * @brief set dynamic to body.
     * a dynamic body will effect with gravity.
     */
    void setDynamic(bool dynamic);
    
    /**
     * @brief set the body mass.
     * @note if you need add/subtract mass to body, don't use setMass(getMass() +/- mass), because the mass of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMass() instead.
     */
    void setMass(float mass);
    /** get the body mass. */
    inline float getMass() const { return _mass; }
    /**
     * @brief add mass to body.
     * if _mass(mass of the body) == PHYSICS_INFINITY, it remains.
     * if mass == PHYSICS_INFINITY, _mass will be PHYSICS_INFINITY.
     * if mass == -PHYSICS_INFINITY, _mass will not change.
     * if mass + _mass <= 0, _mass will equal to MASS_DEFAULT(1.0)
     * other wise, mass = mass + _mass;
     */
    void addMass(float mass);
    
    /**
     * @brief set the body moment of inertia.
     * @note if you need add/subtract moment to body, don't use setMoment(getMoment() +/- moment), because the moment of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMoment() instead.
     */
    void setMoment(float moment);
    /** get the body moment of inertia. */
    inline float getMoment() const { return _moment; }
    /**
     * @brief add moment of inertia to body.
     * if _moment(moment of the body) == PHYSICS_INFINITY, it remains.
     * if moment == PHYSICS_INFINITY, _moment will be PHYSICS_INFINITY.
     * if moment == -PHYSICS_INFINITY, _moment will not change.
     * if moment + _moment <= 0, _moment will equal to MASS_DEFAULT(1.0)
     * other wise, moment = moment + _moment;
     */
    void addMoment(float moment);
    /** get linear damping. */
    inline float getLinearDamping() const { return _linearDamping; }
    /** 
     * set linear damping.
     * it is used to simulate fluid or air friction forces on the body. 
     * the value is 0.0f to 1.0f. 
     */
    inline void setLinearDamping(float damping) { _linearDamping = damping; updateDamping(); }
    /** get angular damping. */
    inline float getAngularDamping() const { return _angularDamping; }
    /**
     * set angular damping.
     * it is used to simulate fluid or air friction forces on the body.
     * the value is 0.0f to 1.0f.
     */
    inline void setAngularDamping(float damping) { _angularDamping = damping; updateDamping(); }
    
    /** whether the body is at rest */
    bool isResting() const;
    /** set body to rest */
    void setResting(bool rest) const;
    /** 
     * whether the body is enabled
     * if the body it isn't enabled, it will not has simulation by world
     */
    inline bool isEnabled() const { return _enabled; }
    /**
     * set the enable value.
     * if the body it isn't enabled, it will not has simulation by world
     */
    void setEnable(bool enable);
    
    /** whether the body can rotation */
    inline bool isRotationEnabled() const { return _rotationEnabled; }
    /** set the body is allow rotation or not */
    void setRotationEnable(bool enable);
    
    /** whether this physics body is affected by the physics world’s gravitational force. */
    inline bool isGravityEnabled() const { return _gravityEnabled; }
    /** set the body is affected by the physics world's gravitational force or not. */
    void setGravityEnable(bool enable);
    
    /** get the body's tag */
    inline int getTag() const { return _tag; }
    /** set the body's tag */
    inline void setTag(int tag) { _tag = tag; }
    
    /** convert the world point to local */
    Vec2 world2Local(const Vec2& point);
    /** convert the local point to world */
    Vec2 local2World(const Vec2& point);

    cpBody* getCPBody() { return _cpBody; }
    
protected:
    
    bool init();
    
    virtual void setPosition(const Vec2& position);
    virtual void setRotation(float rotation);
    virtual void setScale(float scaleX, float scaleY);
    
    void update(float delta);
    
    void removeJoint(PhysicsJoint* joint);
    inline void updateDamping() { _isDamping = _linearDamping != 0.0f ||  _angularDamping != 0.0f; }
    
protected:
    PhysicsBody();
    virtual ~PhysicsBody();
    
protected:
    Node* _node;
    std::vector<PhysicsJoint*> _joints;
    Vector<PhysicsShape*> _shapes;
    PhysicsWorld* _world;
    cpBody* _cpBody;
    bool _dynamic;
    bool _enabled;
    bool _rotationEnabled;
    bool _gravityEnabled;
    bool _massDefault;
    bool _momentDefault;
    float _mass;
    float _area;
    float _density;
    float _moment;
    bool _isDamping;
    float _linearDamping;
    float _angularDamping;
    int _tag;
    
    bool _positionInitDirty;
    Vec2 _recordedPosition;
    Vec2 _latestPosition;
    Vec2 _positionOffset;
    float _rotationOffset;
    float _recordedRotation;
    double _recordedAngle;
    
    friend class PhysicsWorld;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class Node;
    friend class Layer;
    friend class ProtectedNode;
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_BODY_H__
