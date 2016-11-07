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

struct cpShape;

NS_CC_BEGIN

class PhysicsBody;

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

const PhysicsMaterial PHYSICSSHAPE_MATERIAL_DEFAULT;

/**
 *  @addtogroup physics
 *  @{
 *  @addtogroup physics_2d
 *  @{

 */

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
        POLYGON,
        EDGESEGMENT,
        EDGEBOX,
        EDGEPOLYGON,
        EDGECHAIN,

        /** @deprecated Use Type::POLYGON instead. */
        POLYGEN = POLYGON,

        /** @deprecated Use Type::EDGEPOLYGON instead. */
        EDGEPOLYGEN = EDGEPOLYGON,
    };
    
public:
    /** 
     * Get the body that this shape attaches.
     *
     * @return A PhysicsBody object pointer.
     */
    PhysicsBody* getBody() const { return _body; }
    
    /** 
     * Return this shape's type.
     *
     * @return A Type object.
     */
    Type getType() const { return _type; }

    /**
     * Return this shape's area.
     *
     * @return A float number.
     */
    float getArea() const { return _area; }
    
    /**
     * Get this shape's moment.
     *
     * @return A float number.
     */
    float getMoment() const { return _moment; }
    
    /**
     * Set this shape's moment.
     *
     * It will change the body's moment this shape attaches.
     *
     * @param moment A float number.
     */
    void setMoment(float moment);
    
    /**
     * Set this shape's tag.
     *
     * @param tag An integer number that identifies a shape object.
     */
    void setTag(int tag) { _tag = tag; }
    
    /**
     * Get this shape's tag.
     *
     * @return An integer number.
     */
    int getTag() const { return _tag; }
    
    /**
     * Get the mass of this shape.
     *
     * @return A float number.
     */
    float getMass() const { return _mass; }
    
    /**
     * Set this shape's mass.
     *
     * It will change the body's mass this shape attaches.
     *
     * @param mass A float number.
     */
    void setMass(float mass);
    
    /**
     * Get this shape's density.
     *
     * @return A float number.
     */
    float getDensity() const { return _material.density; }
    
    /**
     * Set this shape's density.
     *
     * It will change the body's mass this shape attaches.
     *
     * @param density A float number.
     */
    void setDensity(float density);
    
    /**
     * Get this shape's restitution.
     *
     * @return A float number.
     */
    float getRestitution() const { return _material.restitution; }
    
    /**
     * Set this shape's restitution.
     *
     * It will change the shape's elasticity.
     *
     * @param restitution A float number.
     */
    void setRestitution(float restitution);
    
    /**
     * Get this shape's friction.
     *
     * @return A float number.
     */
    float getFriction() const { return _material.friction; }
    
    /**
     * Set this shape's friction.
     *
     * It will change the shape's friction.
     *
     * @param friction A float number.
     */
    void setFriction(float friction);
    
    /**
     * Get this shape's PhysicsMaterial object.
     *
     * @return A PhysicsMaterial object reference.
     */
    const PhysicsMaterial& getMaterial() const { return _material; }
    
    /**
     * Set this shape's material.
     *
     * It will change the shape's mass, elasticity and friction.
     *
     * @param material A PhysicsMaterial object.
     */
    void setMaterial(const PhysicsMaterial& material);
    bool isSensor() const { return _sensor; }
    void setSensor(bool sensor);
    
    /** 
     * Calculate the default moment value.
     * 
     * This function should be overridden in inherit classes.
     * @return A float number, equals 0.0.
     */
    virtual float calculateDefaultMoment() { return 0.0f; }
    
    /**
     * Get this shape's position offset.
     *
     * This function should be overridden in inherit classes.
     * @return A Vec2 object.
     */
    virtual Vec2 getOffset() { return Vec2::ZERO; }
    
    /**
     * Get this shape's center position.
     *
     * This function should be overridden in inherit classes.
     * @return A Vec2 object.
     */
    virtual Vec2 getCenter() { return getOffset(); }
    
    /** 
     * Test point is inside this shape or not.
     *
     * @param point A Vec2 object.
     * @return A bool object.
     */
    bool containsPoint(const Vec2& point) const;
    
    /** 
     * Move the points to the center.
     * 
     * @param points A Vec2 object pointer.
     * @param count An integer number.
     * @param center A Vec2 object, default value is Vec2(0,0).
     */
    static void recenterPoints(Vec2* points, int count, const Vec2& center = Vec2::ZERO);

    /**
     * Get center of the polygon points.
     *
     * @param points A Vec2 object pointer.
     * @param count An integer number.
     * @return A Vec2 object.
     */
    static Vec2 getPolygonCenter(const Vec2* points, int count);

    /** @deprecated use getPolygonCenter() instead */
    CC_DEPRECATED_ATTRIBUTE static Vec2 getPolyonCenter(const Vec2* points, int count);
    
    /**
     * Set a mask that defines which categories this physics body belongs to.
     *
     * Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.
     * @param bitmask An integer number, the default value is 0xFFFFFFFF (all bits set).
     */
    void setCategoryBitmask(int bitmask) { _categoryBitmask = bitmask; }
    
    /**
     * Get a mask that defines which categories this physics body belongs to.
     *
     * @return An integer number.
     */
    int getCategoryBitmask() const { return _categoryBitmask; }
    
    
    /**
     * A mask that defines which categories of bodies cause intersection notifications with this physics body.
     *
     * When two bodies share the same space, each body's category mask is tested against the other body's contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.
     * @param bitmask An integer number, the default value is 0x00000000 (all bits cleared).
     */
    void setContactTestBitmask(int bitmask) { _contactTestBitmask = bitmask; }
    
    /**
     * Get a mask that defines which categories of bodies cause intersection notifications with this physics body.
     *
     * @return An integer number.
     */
    int getContactTestBitmask() const { return _contactTestBitmask; }

    /**
     * A mask that defines which categories of physics bodies can collide with this physics body.
     *
     * When two physics bodies contact each other, a collision may occur. This body's collision mask is compared to the other body's category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body's velocity.
     * @param bitmask An integer number, the default value is 0xFFFFFFFF (all bits set).
     */
    void setCollisionBitmask(int bitmask) { _collisionBitmask = bitmask; }
    
    /**
     * Get a mask that defines which categories of physics bodies can collide with this physics body.
     *
     * @return An integer number.
     */
    int getCollisionBitmask() const { return _collisionBitmask; }
    
    /**
     * Set the group of body.
     *
     * Collision groups let you specify an integral group index. You can have all fixtures with the same group index always collide (positive index) or never collide (negative index).
     * @param group An integer number, it have high priority than bit masks.
     */
    void setGroup(int group);
    
    /**
     * Get the group of body.
     *
     * @return An integer number.
     */
    int getGroup() { return _group; }
    
protected:
    void setBody(PhysicsBody* body);
    
    /** calculate the area of this shape */
    virtual float calculateArea() { return 0.0f; }
    
    virtual void setScale(float scaleX, float scaleY);
    virtual void updateScale();
    void addShape(cpShape* shape);
    
protected:
    PhysicsShape();
    virtual ~PhysicsShape() = 0;
    
protected:
    PhysicsBody* _body;
    std::vector<cpShape*> _cpShapes;

    Type _type;
    float _area;
    float _mass;
    float _moment;
    bool _sensor;
    float _scaleX;
    float _scaleY;
    float _newScaleX;
    float _newScaleY;
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

/** A circle shape. */
class CC_DLL PhysicsShapeCircle : public PhysicsShape
{
public:
    /**
     * Creates a PhysicsShapeCircle with specified value.
     *
     * @param   radius A float number, it is the circle's radius.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsShapeCircle object pointer.
     */
    static PhysicsShapeCircle* create(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2(0, 0));
    
    /**
     * Calculate the area of a circle with specified radius.
     *
     * @param radius A float number
     * @return A float number
     */
    static float calculateArea(float radius);
    
    /**
     * Calculate the moment of a circle with specified value.
     *
     * @param mass A float number
     * @param radius A float number
     * @param offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return A float number
     */
    static float calculateMoment(float mass, float radius, const Vec2& offset = Vec2::ZERO);
    
    /**
     * Calculate the moment for a circle.
     *
     * @return A float number.
     */
    virtual float calculateDefaultMoment() override;
    
    /**
     * Get the circle's radius.
     *
     * @return A float number.
     */
    float getRadius() const;
    
    /**
     * Get this circle's position offset.
     *
     * @return A Vec2 object.
     */
    virtual Vec2 getOffset() override;
    
protected:
    bool init(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    virtual float calculateArea() override;
    virtual void updateScale() override;
    
protected:
    PhysicsShapeCircle();
    virtual ~PhysicsShapeCircle();
};

/** A polygon shape. */
class CC_DLL PhysicsShapePolygon : public PhysicsShape
{
public:
    /**
     * Creates a PhysicsShapePolygon with specified value.
     *
     * @param   points A Vec2 object pointer, it is an array of Vec2.
     * @param   count An integer number, contains the count of the points array.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsShapePolygon object pointer.
     */
    static PhysicsShapePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO, float radius = 0.0f);
    
    /**
     * Calculate the area of a polygon with specified value.
     *
     * @param   points A Vec2 object pointer, it is an array of Vec2.
     * @param   count An integer number, contains the count of the points array.
     * @return A float number.
     */
    static float calculateArea(const Vec2* points, int count);
    
    /**
     * Calculate the moment of a polygon with specified value.
     *
     * @param mass A float number
     * @param   points A Vec2 object pointer, it is an array of Vec2.
     * @param   count An integer number, contains the count of the points array.
     * @param offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return A float number
     */
    static float calculateMoment(float mass, const Vec2* points, int count, const Vec2& offset = Vec2::ZERO, float radius = 0.0f);
    
    /**
     * Calculate the moment for a polygon.
     *
     * @return A float number.
     */
    float calculateDefaultMoment() override;
    
    /**
     * Get a point of this polygon's points array.
     *
     * @param i A index of this polygon's points array.
     * @return A point value.
     */
    Vec2 getPoint(int i) const;
    
    /**
     * Get this polygon's points array.
     *
     * @param outPoints A Vec2 array pointer.
     */
    void getPoints(Vec2* outPoints) const;
    
    /**
     * Get this polygon's points array count.
     *
     * @return An integer number.
     */
    int getPointsCount() const;
    
    /**
     * Get this polygon's center position.
     *
     * @return A Vec2 object.
     */
    virtual Vec2 getCenter() override;
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO, float radius = 0.0f);
    float calculateArea() override;
    virtual void updateScale() override;
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
};

/** A box shape. */
class CC_DLL PhysicsShapeBox : public PhysicsShapePolygon
{
public:
    /**
     * Creates a PhysicsShapeBox with specified value.
     *
     * @param   size Size contains this box's width and height.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsShapeBox object pointer.
     */
    static PhysicsShapeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO, float radius = 0.0f);
    
    /**
     * Get this box's width and height.
     *
     * @return An Size object.
     */
    Size getSize() const;
    
    /**
     * Get this box's position offset.
     *
     * @return A Vec2 object.
     */
    virtual Vec2 getOffset() override { return getCenter(); }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO, float radius = 0.0f);
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
};

/** A segment shape. */
class CC_DLL PhysicsShapeEdgeSegment : public PhysicsShape
{
public:
    /**
     * Creates a PhysicsShapeEdgeSegment with specified value.
     *
     * @param   a It's the edge's begin position.
     * @param   b It's the edge's end position.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @return  An autoreleased PhysicsShapeEdgeSegment object pointer.
     */
    static PhysicsShapeEdgeSegment* create(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    /**
     * Get this edge's begin position.
     *
     * @return A Vec2 object.
     */
    Vec2 getPointA() const;
    
    /**
     * Get this edge's end position.
     *
     * @return A Vec2 object.
     */
    Vec2 getPointB() const;
    
    /**
     * Get this edge's center position.
     *
     * @return A Vec2 object.
     */
    virtual Vec2 getCenter() override;
    
protected:
    bool init(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void updateScale() override;
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
    friend class PhysicsBody;
};

/** An edge polygon shape. */
class CC_DLL PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    /**
     * Creates a PhysicsShapeEdgePolygon with specified value.
     *
     * @param   points A Vec2 object pointer, it contains an array of points.
     * @param   count An integer number, contains the count of the points array.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @return  An autoreleased PhysicsShapeEdgePolygon object pointer.
     */
    static PhysicsShapeEdgePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    /**
     * Get this polygon's center position.
     *
     * @return A Vec2 object.
     */
    virtual Vec2 getCenter() override;
    
    /**
     * Get this polygon's points array.
     *
     * @param outPoints A Vec2 array pointer.
     */
    void getPoints(Vec2* outPoints) const;
    
    /**
     * Get this polygon's points array count.
     *
     * @return An integer number.
     */
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void updateScale() override;
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
};

/** An edge box shape. */
class CC_DLL PhysicsShapeEdgeBox : public PhysicsShapeEdgePolygon
{
public:
    /**
     * Creates a PhysicsShapeEdgeBox with specified value.
     *
     * @param   size Size contains this box's width and height.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.
     * @return  An autoreleased PhysicsShapeEdgeBox object pointer.
     */
    static PhysicsShapeEdgeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 0, const Vec2& offset = Vec2::ZERO);
    
    /**
     * Get this box's position offset.
     *
     * @return A Vec2 object.
     */
    virtual Vec2 getOffset() override { return getCenter(); }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
    friend class PhysicsBody;
};

/** A chain shape. */
class CC_DLL PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    /**
     * Creates a PhysicsShapeEdgeChain with specified value.
     *
     * @param   points A Vec2 object pointer, it contains an array of points.
     * @param   count An integer number, contains the count of the points array.
     * @param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @param   border It's a edge's border width.
     * @return  An autoreleased PhysicsShapeEdgeChain object pointer.
     */
    static PhysicsShapeEdgeChain* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    /**
     * Get this chain's center position.
     *
     * @return A Vec2 object.
     */
    virtual Vec2 getCenter() override;
    
    /**
     * Get this chain's points array.
     *
     * @param outPoints A Vec2 array pointer.
     */
    void getPoints(Vec2* outPoints) const;
    
    /**
     * Get this chain's points array count.
     *
     * @return An integer number.
     */
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void updateScale() override;
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();

    friend class PhysicsBody;
};

/** @} */
/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_FIXTURE_H__
