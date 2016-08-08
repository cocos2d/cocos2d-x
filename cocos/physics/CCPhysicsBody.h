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

#include "2d/CCComponent.h"
#include "math/CCGeometry.h"
#include "physics/CCPhysicsShape.h"
#include "base/CCVector.h"

struct cpBody;

NS_CC_BEGIN

class Node;
class PhysicsWorld;
class PhysicsJoint;

typedef Vec2 Vect;

const PhysicsMaterial PHYSICSBODY_MATERIAL_DEFAULT(0.1f, 0.5f, 0.5f);

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

/**
 * A body affect by physics.
 *
 * It can attach one or more shapes.
 * If you create body with createXXX, it will automatically compute mass and moment with density your specified(which is PHYSICSBODY_MATERIAL_DEFAULT by default, and the density value is 0.1f), and it based on the formula: mass = density * area.
 * If you create body with createEdgeXXX, the mass and moment will be PHYSICS_INFINITY by default. And it's a static body.
 * You can change mass and moment with setMass() and setMoment(). And you can change the body to be dynamic or static by use function setDynamic().
 */
class CC_DLL PhysicsBody : public Component
{
public:
    const static std::string COMPONENT_NAME;

    /** 
     * Create a body with default mass and moment.
     *
     * This default mass value is 1.0.
     * This default moment value is 200.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* create();
   
    /** 
     * Create a body with mass and default moment.
     *
     * @param mass This body's mass.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* create(float mass);
    
    /** 
     * Create a body with mass and moment.
     *
     * @param mass This body's mass.
     * @param moment This body's moment.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* create(float mass, float moment);
    
    /**
     * Create a body contains a circle.
     *
     * @param   radius A float number, it is the circle's radius.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* createCircle(float radius, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    /**
     * Create a body contains a box shape.
     *
     * @param   size Size contains this box's width and height.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* createBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);

    /**
     * @brief Create a body contains a polygon shape.
     *
     * @param   points Points is an array of Vec2 structs defining a convex hull with a clockwise winding.
     * @param   count An integer number, contains the count of the points array.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* createPolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);

    /**
     * Create a body contains a EdgeSegment shape.
     *
     * @param   a It's the edge's begin position.
     * @param   b It's the edge's end position.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* createEdgeSegment(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);

    /**
     * Create a body contains a EdgeBox shape.
     * @param   size Size contains this box's width and height.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* createEdgeBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);

    /**
     * Create a body contains a EdgePolygon shape.
     *
     * @param   points Points is an array of Vec2 structs defining a convex hull with a clockwise winding.
     * @param   count An integer number, contains the count of the points array.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* createEdgePolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);

    /**
     * Create a body contains a EdgeChain shape.
     *
     * @param   points A Vec2 object pointer, it contains an array of points.
     * @param   count An integer number, contains the count of the points array.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @return  An autoreleased PhysicsBody object pointer.
     */
    static PhysicsBody* createEdgeChain(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);

    /**
     * @brief Add a shape to body.
     * @param shape The shape to be added.
     * @param addMassAndMoment If this is true, the shape's mass and moment will be added to body. The default is true.
     * @return This shape's pointer if added success or nullptr if failed.
     */
    virtual PhysicsShape* addShape(PhysicsShape* shape, bool addMassAndMoment = true);

    /**
     * @brief Remove a shape from body.
     * @param shape Shape the shape to be removed.
     * @param reduceMassAndMoment If this is true, the body mass and moment will be reduced by shape. The default is true.
     */
    void removeShape(PhysicsShape* shape, bool reduceMassAndMoment = true);

    /**
     * @brief Remove a shape from body.
     * @param tag The tag of the shape to be removed.
     * @param reduceMassAndMoment If this is true, the body mass and moment will be reduced by shape. The default is true.
     */
    void removeShape(int tag, bool reduceMassAndMoment = true);
    
    /** 
     * Remove all shapes.
     *
     * @param reduceMassAndMoment If this is true, the body mass and moment will be reduced by shape. The default is true.
     */
    void removeAllShapes(bool reduceMassAndMoment = true);

    /**
     * Get the body shapes.
     * 
     * @return A Vector<PhysicsShape*> object contains PhysicsShape pointer.
     */
    inline const Vector<PhysicsShape*>& getShapes() const { return _shapes; }

    /** 
     * get the shape of the body.
     *
     * @param   tag   An integer number that identifies a PhysicsShape object.
     * @return A PhysicsShape object pointer or nullptr if no shapes were found.
     */
    PhysicsShape* getShape(int tag) const;
    
    /** 
     * Applies a continuous force to body.
     * 
     * @param force The force is applies to this body.
     * @param offset A Vec2 object, it is the offset from the body's center of gravity in world coordinates.
     */
    virtual void applyForce(const Vec2& force, const Vec2& offset = Vec2::ZERO);

    /** 
     * reset all the force applied to body. 
     */
    virtual void resetForces();

    /**
     * Applies a immediate force to body.
     *
     * @param impulse The impulse is applies to this body.
     * @param offset A Vec2 object, it is the offset from the body's center of gravity in world coordinates.
     */
    virtual void applyImpulse(const Vec2& impulse, const Vec2& offset = Vec2::ZERO);
    
    /** 
     * Applies a torque force to body.
     *
     * @param torque The torque is applies to this body.
     */
    virtual void applyTorque(float torque);
    
    /** 
     * Set the velocity of a body.
     * 
     * @param velocity The velocity is set to this body.
     */
    virtual void setVelocity(const Vec2& velocity);
    
    /** Get the velocity of a body. */
    virtual Vec2 getVelocity();
    
    /** 
     * Set the angular velocity of a body.
     *
     * @param velocity The angular velocity is set to this body.
     */
    virtual void setAngularVelocity(float velocity);
    
    /** Get the angular velocity of a body at a local point.*/
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
    
    /** get the node the body set to. */
    Node* getNode() const { return _owner; }
    
    /**
     * A mask that defines which categories this physics body belongs to.
     * 
     * Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.
     * @param bitmask An integer number, the default value is 0xFFFFFFFF (all bits set).
     */
    void setCategoryBitmask(int bitmask);
    
    /** 
     * A mask that defines which categories of bodies cause intersection notifications with this physics body.
     *
     * When two bodies share the same space, each body's category mask is tested against the other body's contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.
     * @param bitmask An integer number, the default value is 0x00000000 (all bits cleared).
     */
    void setContactTestBitmask(int bitmask);
    
    /**
     * A mask that defines which categories of physics bodies can collide with this physics body.
     *
     * When two physics bodies contact each other, a collision may occur. This body's collision mask is compared to the other body's category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body's velocity.
     * @param bitmask An integer number, the default value is 0xFFFFFFFF (all bits set).
     */
    void setCollisionBitmask(int bitmask);
    
    /** 
     * Return bitmask of first shape.
     * 
     * @return If there is no shape in body, return default value.(0xFFFFFFFF)
     */
    int getCategoryBitmask() const;
    
    /** 
     * Return bitmask of first shape.
     *
     * @return If there is no shape in body, return default value.(0x00000000)
     */
    int getContactTestBitmask() const;
    
    /** 
     * Return bitmask of first shape.
     * 
     * @return If there is no shape in body, return default value.(0xFFFFFFFF)
     */
    int getCollisionBitmask() const;
    
    /** 
     * Set the group of body.
     *
     * Collision groups let you specify an integral group index. You can have all fixtures with the same group index always collide (positive index) or never collide (negative index).
     * It have high priority than bit masks.
     */
    void setGroup(int group);
    
    /** 
     * Return group of first shape.
     * 
     * @return If there is no shape in body, return default value.(0) 
     */
    int getGroup() const;
    
    /** get the body position. */
    Vec2 getPosition() const;

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
     * @brief Test the body is dynamic or not.
     *
     * A dynamic body will effect with gravity.
     */
    inline bool isDynamic() const { return _dynamic; }
    /**
     * @brief Set dynamic to body.
     * 
     * A dynamic body will effect with gravity.
     */
    void setDynamic(bool dynamic);
    
    /**
     * @brief Set the body mass.
     *
     * @attention If you need add/subtract mass to body, don't use setMass(getMass() +/- mass), because the mass of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMass() instead.
     */
    void setMass(float mass);
    
    /** Get the body mass. */
    inline float getMass() const { return _mass; }

    /**
     * @brief Add mass to body.
     *
     * @param mass If _mass(mass of the body) == PHYSICS_INFINITY, it remains.
     * if mass == PHYSICS_INFINITY, _mass will be PHYSICS_INFINITY.
     * if mass == -PHYSICS_INFINITY, _mass will not change.
     * if mass + _mass <= 0, _mass will equal to MASS_DEFAULT(1.0)
     * other wise, mass = mass + _mass;
     */
    void addMass(float mass);
    
    /**
     * @brief Set the body moment of inertia.
     *
     * @note If you need add/subtract moment to body, don't use setMoment(getMoment() +/- moment), because the moment of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMoment() instead.
     */
    void setMoment(float moment);
    
    /** Get the body moment of inertia. */
    inline float getMoment() const { return _moment; }
    
    /**
     * @brief Add moment of inertia to body.
     * 
     * @param moment If _moment(moment of the body) == PHYSICS_INFINITY, it remains.
     * if moment == PHYSICS_INFINITY, _moment will be PHYSICS_INFINITY.
     * if moment == -PHYSICS_INFINITY, _moment will not change.
     * if moment + _moment <= 0, _moment will equal to MASS_DEFAULT(1.0)
     * other wise, moment = moment + _moment;
     */
    void addMoment(float moment);
    
    /** get linear damping. */
    inline float getLinearDamping() const { return _linearDamping; }
    
    /** 
     * Set linear damping.
     *
     * it is used to simulate fluid or air friction forces on the body.
     * @param damping The value is 0.0f to 1.0f.
     */
    inline void setLinearDamping(float damping) { _linearDamping = damping; updateDamping(); }
    
    /** Get angular damping. */
    inline float getAngularDamping() const { return _angularDamping; }

    /**
     * Set angular damping.
     *
     * It is used to simulate fluid or air friction forces on the body.
     * @param damping The value is 0.0f to 1.0f.
     */
    inline void setAngularDamping(float damping) { _angularDamping = damping; updateDamping(); }
    
    /** Whether the body is at rest. */
    bool isResting() const;
    
    /** set body to rest */
    void setResting(bool rest) const;
    
    /**
     * Set the enable value.
     *
     * If the body it isn't enabled, it will not has simulation by world.
     */
    virtual void setEnabled(bool enable) override;
    
    /** Whether the body can rotation. */
    inline bool isRotationEnabled() const { return _rotationEnabled; }
    
    /** Set the body is allow rotation or not */
    void setRotationEnable(bool enable);
    
    /** Whether this physics body is affected by the physics world's gravitational force. */
    inline bool isGravityEnabled() const { return _gravityEnabled; }
    
    /** Set the body is affected by the physics world's gravitational force or not. */
    void setGravityEnable(bool enable);
    
    /** Get the body's tag. */
    inline int getTag() const { return _tag; }
    
    /** set the body's tag. */
    inline void setTag(int tag) { _tag = tag; }
    
    /** Convert the world point to local. */
    Vec2 world2Local(const Vec2& point);
    
    /** Convert the local point to world. */
    Vec2 local2World(const Vec2& point);

    /** Get the rigid body of chipmunk. */
    cpBody* getCPBody() const { return _cpBody; }

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onAdd() override;
    virtual void onRemove() override;
    
protected:
    PhysicsBody();
    virtual ~PhysicsBody();

    virtual bool init()override;
    
    virtual void setPosition(float positionX, float positionY);

    virtual void setRotation(float rotation);

    virtual void setScale(float scaleX, float scaleY);
    
    void update(float delta)override;
    
    void removeJoint(PhysicsJoint* joint);

    inline void updateDamping() { _isDamping = _linearDamping != 0.0f ||  _angularDamping != 0.0f; }

    void addToPhysicsWorld();
    void removeFromPhysicsWorld();

    void beforeSimulation(const Mat4& parentToWorldTransform, const Mat4& nodeToWorldTransform, float scaleX, float scaleY, float rotation);
    void afterSimulation(const Mat4& parentToWorldTransform, float parentRotation);
protected:
    std::vector<PhysicsJoint*> _joints;
    Vector<PhysicsShape*> _shapes;
    PhysicsWorld* _world;
    
    cpBody* _cpBody;
    bool _dynamic;
    bool _rotationEnabled;
    bool _gravityEnabled;
    bool _massDefault;
    bool _momentDefault;
    float _mass;
    float _area;
    float _density;
    float _moment;
    float _velocityLimit;
    float _angularVelocityLimit;
    bool _isDamping;
    float _linearDamping;
    float _angularDamping;

    int _tag;
    
    // when setMass() is invoked, it means body's mass is not calculated by shapes
    bool _massSetByUser;
    // when setMoment() is invoked, it means body's moment is not calculated by shapes
    bool _momentSetByUser;
    
    Vec2 _positionOffset;
    float _rotationOffset;
    float _recordedRotation;
    double _recordedAngle;
    
    // offset between owner's center point and down left point
    Vec3 _ownerCenterOffset;
    // offset of owner's center point and anchor point in parent coordinate
    Vec2 _offset;
    float _recordScaleX;
    float _recordScaleY;

    float _recordPosX;
    float _recordPosY;

    friend class PhysicsWorld;
    friend class PhysicsShape;
    friend class PhysicsJoint;
};

/** @} */
/** @} */


NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_BODY_H__
