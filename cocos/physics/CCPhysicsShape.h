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

#ifndef __CCPHYSICS_SHAPE_H__
#define __CCPHYSICS_SHAPE_H__

#include "CCObject.h"
#include "CCGeometry.h"

NS_CC_BEGIN

class PhysicsShapeInfo;
class PhysicsBody;
class PhysicsBodyInfo;


typedef struct PhysicsMaterial
{
    float density;
    float restitution;
    float friction;
    
    PhysicsMaterial()
    : density(0.0f)
    , restitution(0.0f)
    , friction(0.0f){}
    
    PhysicsMaterial(float density, float restitution, float friction)
    : density(density)
    , restitution(restitution)
    , friction(friction){}
}PhysicsMaterial;

const PhysicsMaterial PHYSICSSHAPE_MATERIAL_DEFAULT = {0.0f, 1.0f, 1.0f};

/**
 * @brief A shape for body. You do not create PhysicsWorld objects directly, instead, you can view PhysicsBody to see how to create it.
 */
class PhysicsShape : public Object
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
    inline PhysicsBody* getBody() const { return _body; }
    inline Type getType() const { return _type; }
    inline float getArea() const { return _area; }
    inline float getMoment() const { return _moment; }
    void setMoment(float moment);
    inline void setTag(int tag) { _tag = tag; }
    inline int getTag() const { return _tag; }
    
    inline float getMass() const { return _mass; }
    void setMass(float mass);
    inline float getDensity() const { return _material.density; }
    void setDensity(float density);
    void setRestitution(float restitution);
    void setFriction(float friction);
    void setMaterial(PhysicsMaterial material);
    
    virtual float calculateDefaultMoment() { return 0; }
    virtual float calculateDefaultArea() { return 0; }
    virtual Point getOffset() { return Point::ZERO; }
    virtual Point getCenter() { return getOffset(); }
    
    static Point* recenterPoints(Point* points, int count, Point center);
    static Point getPolyonCenter(Point* points, int count);
    
protected:
    bool init(Type type);
    
    /**
     * @brief PhysicsShape is PhysicsBody's friend class, but all the subclasses isn't. so this method is use for subclasses to catch the bodyInfo from PhysicsBody.
     */
    PhysicsBodyInfo* bodyInfo() const;
    
    void setBody(PhysicsBody* body);
    
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
    PhysicsMaterial _material;
    int _tag;
    
    friend class PhysicsWorld;
    friend class PhysicsBody;
    friend class PhysicsJoint;
};

/** A circle shape */
class PhysicsShapeCircle : public PhysicsShape
{
public:
    static PhysicsShapeCircle* create(float radius, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    static float calculateArea(float radius);
    static float calculateMoment(float mass, float radius, Point offset = Point(0, 0));
    
    float calculateDefaultArea() override;
    float calculateDefaultMoment() override;
    
    float getRadius();
    Point getOffset();
protected:
    bool init(float radius, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeCircle();
    ~PhysicsShapeCircle();
};

/** A box shape */
class PhysicsShapeBox : public PhysicsShape
{
public:
    static PhysicsShapeBox* create(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    static float calculateArea(Size size);
    static float calculateMoment(float mass, Size size, Point offset = Point(0, 0));
    
    float calculateDefaultArea() override;
    float calculateDefaultMoment() override;
    
    Point* getPoints(Point* points);
    Size getSize();
    Point getOffset() override { return _offset; }
    
protected:
    bool init(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
    
protected:
    Point _offset;
};

/** A polygon shape */
class PhysicsShapePolygon : public PhysicsShape
{
public:
    static PhysicsShapePolygon* create(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    static float calculateArea(Point* points, int count);
    static float calculateMoment(float mass, Point* points, int count, Point offset = Point(0, 0));
    
    float calculateDefaultArea() override;
    float calculateDefaultMoment() override;
    
    Point* getPoints(Point* points);
    int getPointsCount();
    Point getCenter() override;
protected:
    bool init(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
    
protected:
    Point _center;
};

/** A segment shape */
class PhysicsShapeEdgeSegment : public PhysicsShape
{
public:
    static PhysicsShapeEdgeSegment* create(Point a, Point b, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    Point getPointA();
    Point getPointB();
    Point getCenter() override;
    
protected:
    bool init(Point a, Point b, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
protected:
    Point _center;
    
    friend class PhysicsBody;
};

/** An edge box shape */
class PhysicsShapeEdgeBox : public PhysicsShape
{
public:
    static PhysicsShapeEdgeBox* create(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 0, Point offset = Point(0, 0));
    Point getOffset() override { return _offset; }
    Point* getPoints(Point* points);
    int getPointsCount();
    
protected:
    bool init(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
protected:
    Point _offset;
    
    friend class PhysicsBody;
};

/** An edge polygon shape */
class PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    static PhysicsShapeEdgePolygon* create(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    Point getCenter() override;
    Point* getPoints(Point* points);
    int getPointsCount();
    
protected:
    bool init(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
    
protected:
    Point _center;
};

/** a chain shape */
class PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    static PhysicsShapeEdgeChain* create(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    Point getCenter() override;
    Point* getPoints(Point* points);
    int getPointsCount();
    
protected:
    bool init(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();
    
protected:
    Point _center;
    
    friend class PhysicsBody;
};

NS_CC_END
#endif // __CCPHYSICS_FIXTURE_H__

#endif // CC_USE_PHYSICS
