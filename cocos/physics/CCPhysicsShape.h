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

#ifndef __CCPHYSICS_SHAPE_H__
#define __CCPHYSICS_SHAPE_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

class PhysicsShapeInfo;
class PhysicsBody;
class PhysicsBodyInfo;


typedef struct CC_DLL PhysicsMaterial
{
    float density;          ///< The density of the object.
    float restitution;      ///< The bounciness of the physics body.
    float friction;         ///< The roughness of the surface of a shape.
    
    PhysicsMaterial()
    : density(0.0f)
    , restitution(0.0f)
    , friction(0.0f)
    {}
    
    PhysicsMaterial(float aDensity, float aRestitution, float aFriction)
    : density(aDensity)
    , restitution(aRestitution)
    , friction(aFriction)
    {}
}PhysicsMaterial;

const PhysicsMaterial PHYSICSSHAPE_MATERIAL_DEFAULT(0.0f, 0.5f, 0.5f);

/**
 * @brief A shape for body. You do not create PhysicsWorld objects directly, instead, you can view PhysicsBody to see how to create it.
 */
class CC_DLL PhysicsShape : public Ref
{
public:
    enum class Type
    {
        UNKNOWN,
        CIRCLE,
        BOX,
        POLYGEN,
        EDGESEGMENT,
        EDGEBOX,
        EDGEPOLYGEN,
        EDGECHAIN,
    };
    
public:
    /** Get the body that this shape attaches */
    inline PhysicsBody* getBody() const { return _body; }
    /** Return the type of this shape */
    inline Type getType() const { return _type; }
    /** return the area of this shape */
    inline float getArea() const { return _area; }
    /** get moment */
    inline float getMoment() const { return _moment; }
    /** Set moment, it will change the body's moment this shape attaches */
    void setMoment(float moment);
    inline void setTag(int tag) { _tag = tag; }
    inline int getTag() const { return _tag; }
    
    /** get mass */
    inline float getMass() const { return _mass; }
    /** Set mass, it will change the body's mass this shape attaches */
    void setMass(float mass);
    inline float getDensity() const { return _material.density; }
    void setDensity(float density);
    inline float getRestitution() const { return _material.restitution; }
    void setRestitution(float restitution);
    inline float getFriction() const { return _material.friction; }
    void setFriction(float friction);
    const PhysicsMaterial& getMaterial() const { return _material; }
    void setMaterial(const PhysicsMaterial& material);
    
    /** Calculate the default moment value */
    virtual float calculateDefaultMoment() { return 0.0f; }
    /** Get offset */
    virtual Vec2 getOffset() { return Vec2::ZERO; }
    /** Get center of this shape */
    virtual Vec2 getCenter() { return getOffset(); }
    /** Test point is in shape or not */
    bool containsPoint(const Vec2& point) const;
    
    /** move the points to the center */
    static void recenterPoints(Vec2* points, int count, const Vec2& center = Vec2::ZERO);
    /** get center of the polyon points */
    static Vec2 getPolyonCenter(const Vec2* points, int count);
    
    /**
     * A mask that defines which categories this physics body belongs to.
     * Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.
     * The default value is 0xFFFFFFFF (all bits set).
     */
    inline void setCategoryBitmask(int bitmask) { _categoryBitmask = bitmask; }
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    /**
     * A mask that defines which categories of bodies cause intersection notifications with this physics body.
     * When two bodies share the same space, each body’s category mask is tested against the other body’s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.
     * The default value is 0x00000000 (all bits cleared).
     */
    inline void setContactTestBitmask(int bitmask) { _contactTestBitmask = bitmask; }
    inline int getContactTestBitmask() const { return _contactTestBitmask; }
    /**
     * A mask that defines which categories of physics bodies can collide with this physics body.
     * When two physics bodies contact each other, a collision may occur. This body’s collision mask is compared to the other body’s category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body’s velocity.
     * The default value is 0xFFFFFFFF (all bits set).
     */
    inline void setCollisionBitmask(int bitmask) { _collisionBitmask = bitmask; }
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    /**
     * set the group of body
     * Collision groups let you specify an integral group index. You can have all fixtures with the same group index always collide (positive index) or never collide (negative index)
     * it have high priority than bit masks
     */
    void setGroup(int group);
    inline int getGroup() { return _group; }
    
protected:
    bool init(Type type);
    
    /**
     * @brief PhysicsShape is PhysicsBody's friend class, but all the subclasses isn't. so this method is use for subclasses to catch the bodyInfo from PhysicsBody.
     */
    PhysicsBodyInfo* bodyInfo() const;
    
    void setBody(PhysicsBody* body);
    
    /** calculate the area of this shape */
    virtual float calculateArea() { return 0.0f; }
    
    virtual void setScale(float scale);
    virtual void setScale(float scaleX, float scaleY);
    virtual void setScaleX(float scaleX);
    virtual void setScaleY(float scaleY);
    virtual void update(float delta);
    
protected:
    PhysicsShape();
    virtual ~PhysicsShape() = 0;
    
protected:
    PhysicsBody* _body;
    PhysicsShapeInfo* _info;
    Type _type;
    float _area;
    float _mass;
    float _moment;
    float _scaleX;
    float _scaleY;
    float _newScaleX;
    float _newScaleY;
    bool _dirty;
    PhysicsMaterial _material;
    int _tag;
    int    _categoryBitmask;
    int    _collisionBitmask;
    int    _contactTestBitmask;
    int    _group;
    
    friend class PhysicsWorld;
    friend class PhysicsBody;
    friend class PhysicsJoint;
    friend class PhysicsDebugDraw;
};

/** A circle shape */
class CC_DLL PhysicsShapeCircle : public PhysicsShape
{
public:
    static PhysicsShapeCircle* create(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2(0, 0));
    static float calculateArea(float radius);
    static float calculateMoment(float mass, float radius, const Vec2& offset = Vec2::ZERO);
    
    virtual float calculateDefaultMoment() override;
    
    float getRadius() const;
    virtual Vec2 getOffset() override;
    
protected:
    bool init(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    virtual float calculateArea() override;
    virtual void setScale(float scale) override;
    virtual void setScale(float scaleX, float scaleY) override;
    virtual void setScaleX(float scale) override;
    virtual void setScaleY(float scale) override;
    virtual void update(float delta) override;
    
protected:
    PhysicsShapeCircle();
    virtual ~PhysicsShapeCircle();
};

/** A polygon shape */
class CC_DLL PhysicsShapePolygon : public PhysicsShape
{
public:
    static PhysicsShapePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    static float calculateArea(const Vec2* points, int count);
    static float calculateMoment(float mass, const Vec2* points, int count, const Vec2& offset = Vec2::ZERO);
    
    float calculateDefaultMoment() override;
    
    Vec2 getPoint(int i) const;
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const;
    virtual Vec2 getCenter() override;
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    float calculateArea() override;
    virtual void update(float delta) override;
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
};

/** A box shape */
class CC_DLL PhysicsShapeBox : public PhysicsShapePolygon
{
public:
    static PhysicsShapeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
    Size getSize() const;
    virtual Vec2 getOffset() override { return getCenter(); }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
};

/** A segment shape */
class CC_DLL PhysicsShapeEdgeSegment : public PhysicsShape
{
public:
    static PhysicsShapeEdgeSegment* create(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    Vec2 getPointA() const;
    Vec2 getPointB() const;
    virtual Vec2 getCenter() override;
    
protected:
    bool init(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void update(float delta) override;
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
    friend class PhysicsBody;
};

/** An edge polygon shape */
class CC_DLL PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    static PhysicsShapeEdgePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual Vec2 getCenter() override;
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void update(float delta) override;
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
};

/** An edge box shape */
class CC_DLL PhysicsShapeEdgeBox : public PhysicsShapeEdgePolygon
{
public:
    static PhysicsShapeEdgeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 0, const Vec2& offset = Vec2::ZERO);
    virtual Vec2 getOffset() override { return getCenter(); }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
    friend class PhysicsBody;
};

/** a chain shape */
class CC_DLL PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    static PhysicsShapeEdgeChain* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual Vec2 getCenter() override;
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void update(float delta) override;
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();

    friend class PhysicsBody;
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_FIXTURE_H__
