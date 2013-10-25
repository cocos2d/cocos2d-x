/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "CCPhysicsSetting.h"
#ifdef CC_USE_PHYSICS

#ifndef __CCPHYSICS_BODY_H__
#define __CCPHYSICS_BODY_H__

#include "CCObject.h"
#include "CCGeometry.h"

#include "CCPhysicsShape.h"

#include <vector>

NS_CC_BEGIN
class Sprite;
class PhysicsWorld;
class PhysicsJoint;

class PhysicsBodyInfo;


const PhysicsMaterial PHYSICSBODY_MATERIAL_DEFAULT(1.0f, 1.0f, 1.0f);

/**
 * A body affect by physics.
 * it can attach one or more shapes.
 */
class PhysicsBody : public Object//, public Clonable
{
public:
    static PhysicsBody* create();
    /**
     * @brief Create a body contains a circle shape.
     */
    static PhysicsBody* createCircle(float radius, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    /**
     * @brief Create a body contains a box shape.
     */
    static PhysicsBody* createBox(Size size, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    /**
     * @brief Create a body contains a polygon shape.
     * points is an array of Point structs defining a convex hull with a clockwise winding.
     */
    static PhysicsBody* createPolygon(Point* points, int count, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    
    /**
     * @brief Create a body contains a EdgeSegment shape.
     */
    static PhysicsBody* createEdgeSegment(Point a, Point b, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    /**
     * @brief Create a body contains a EdgeBox shape.
     */
    static PhysicsBody* createEdgeBox(Size size, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    /**
     * @brief Create a body contains a EdgePolygon shape.
     */
    static PhysicsBody* createEdgePolygon(Point* points, int count, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    /**
     * @brief Create a body contains a EdgeChain shape.
     */
    static PhysicsBody* createEdgeChain(Point* points, int count, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    
    virtual void addShape(PhysicsShape* shape);
    
    /**
     * @brief Applies a immediate force to body.
     */
    virtual void applyForce(Point force);
    /**
     * @brief Applies a immediate force to body.
     */
    virtual void applyForce(Point force, Point offset);
    /**
     * @brief Applies a continuous force to body.
     */
    virtual void applyImpulse(Point impulse);
    /**
     * @brief Applies a continuous force to body.
     */
    virtual void applyImpulse(Point impulse, Point offset);
    /**
     * @brief Applies a torque force to body.
     */
    virtual void applyTorque(float torque);
    
    virtual void setVelocity(Point velocity);
    virtual Point getVelocity();
    virtual void setAngularVelocity(float velocity);
    virtual float getAngularVelocity();
    virtual void setVelocityLimit(float limit);
    virtual float getVelocityLimit();
    virtual void setAngularVelocityLimit(float limit);
    virtual float getAngularVelocityLimit();
    
    /*
     * @brief get the body shapes.
     */
    inline std::vector<PhysicsShape*>& getShapes() { return _shapes; }
    /*
     * @brief get the first body shapes.
     */
    inline PhysicsShape* getShape() { return _shapes.size() >= 1 ? _shapes.front() : nullptr; }
    PhysicsShape* getShapeByTag(int tag);
    /*
     * @brief remove a shape from body
     */
    void removeShape(PhysicsShape* shape);
    void removeShapeByTag(int tag);
    /*
     * @brief remove all shapes
     */
    void removeAllShapes();
    
    /*
     * @brief get the world body added to.
     */
    inline PhysicsWorld* getWorld() const { return _world; }
    /*
     * @brief get all joints the body have
     */
    inline const std::vector<PhysicsJoint*>* getJoints() const { return &_joints; }
    
    /*
     * @brief get the sprite the body set to.
     */
    inline Sprite* getOwner() const { return _owner; }
    
    inline void setCategoryBitmask(int bitmask) { _categoryBitmask = bitmask; }
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    inline void setContactTestBitmask(int bitmask) { _contactTestBitmask = bitmask; }
    inline int getContactTestBitmask() const { return _contactTestBitmask; }
    inline void setCollisionBitmask(int bitmask) { _collisionBitmask = bitmask; }
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    /*
     * @brief get the body position.
     */
    Point getPosition() const;
    /*
     * @brief get the body rotation.
     */
    float getRotation() const;
    
    /*
     * @brief test the body is dynamic or not.
     * a dynamic body will effect with gravity.
     */
    inline bool isDynamic() { return _dynamic; }
    /*
     * @brief set dynamic to body.
     * a dynamic body will effect with gravity.
     */
    void setDynamic(bool dynamic);
    
    /*
     * @brief set the body mass.
     * @note if you need add/subtract mass to body, don't use setMass(getMass() +/- mass), because the mass of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMass() instead.
     */
    void setMass(float mass);
    /*
     * @brief get the body mass.
     */
    inline float getMass() { return _mass; }
    /*
     * @brief add mass to body.
     * if _mass(mass of the body) == PHYSICS_INFINITY, it remains.
     * if mass == PHYSICS_INFINITY, _mass will be PHYSICS_INFINITY.
     * if mass == -PHYSICS_INFINITY, _mass will not change.
     * if mass + _mass <= 0, _mass will equal to MASS_DEFAULT(1.0)
     * other wise, mass = mass + _mass;
     */
    void addMass(float mass);
    
    /*
     * @brief set the body moment of inertia.
     * @note if you need add/subtract moment to body, don't use setMoment(getMoment() +/- moment), because the moment of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMoment() instead.
     */
    void setMoment(float moment);
    /*
     * @brief get the body moment of inertia.
     */
    inline float getMoment(float moment) { return _moment; }
    /*
     * @brief add moment of inertia to body.
     * if _moment(moment of the body) == PHYSICS_INFINITY, it remains.
     * if moment == PHYSICS_INFINITY, _moment will be PHYSICS_INFINITY.
     * if moment == -PHYSICS_INFINITY, _moment will not change.
     * if moment + _moment <= 0, _moment will equal to MASS_DEFAULT(1.0)
     * other wise, moment = moment + _moment;
     */
    void addMoment(float moment);
    /*
     * @brief set angular damping.
     */
    //void setAngularDamping(float angularDamping);
    /*
     * @brief get angular damping.
     */
    inline float getLinearDamping() { return _linearDamping; }
    inline void setLinearDamping(float damping) { _linearDamping = damping; }
    inline float getAngularDamping() { return _angularDamping; }
    inline void setAngularDamping(float damping) { _angularDamping = damping; }
    
    //virtual Clonable* clone() const override;
    
    bool isResting();
    inline bool isEnable() { return _enable; }
    void setEnable(bool enable);
    
    inline bool isRotationEnable() { return _rotationEnable; }
    void setRotationEnable(bool enable);
    
    inline bool isGravityEnable() { return _gravityEnable; }
    void setGravityEnable(bool enable);
    
    
    inline int getTag() { return _tag; }
    inline void setTag(int tag) { _tag = tag; }
    
    
protected:
    
    bool init();
    
    virtual void setPosition(Point position);
    virtual void setRotation(float rotation);
    
    virtual void update(float delta) override;
    
protected:
    PhysicsBody();
    virtual ~PhysicsBody();
    
protected:
    Sprite*  _owner;
    std::vector<PhysicsJoint*>  _joints;
    std::vector<PhysicsShape*>  _shapes;
    PhysicsWorld*               _world;
    PhysicsBodyInfo*            _info;
    bool                        _dynamic;
    bool                        _enable;
    bool                        _rotationEnable;
    bool                        _gravityEnable;
    bool                        _massDefault;
    bool                        _momentDefault;
    float                       _mass;
    float                       _area;
    float                       _density;
    float                       _moment;
    float                       _linearDamping;
    float                       _angularDamping;
    int                         _tag;
    
    int    _categoryBitmask;
    int    _collisionBitmask;
    int    _contactTestBitmask;
    
    friend class PhysicsWorld;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class Node;
};

NS_CC_END

#endif // __CCPHYSICS_BODY_H__

#endif // CC_USE_PHYSICS
