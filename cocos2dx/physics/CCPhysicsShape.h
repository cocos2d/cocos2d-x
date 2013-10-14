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

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN

class PhysicsShapeInfo;
class PhysicsBody;
class PhysicsBodyInfo;


typedef struct PhysicsMaterial
{
    float density;
    float elasticity;
    float friction;
    
    PhysicsMaterial()
    : density(0.0f)
    , elasticity(0.0f)
    , friction(0.0f){}
    
    PhysicsMaterial(float density, float elasticity, float friction)
    : density(density)
    , elasticity(elasticity)
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
    inline PhysicsBody* getBody(){ return _body; }
    inline Type getType() { return _type; }
    inline float getArea() { return _area; }
    inline float getMoment() { return _moment; }
    void setMoment(float moment);
    inline void setTag(int tag) { _tag = tag; }
    inline int getTag() { return _tag; }
    void setEnable(bool enable);
    inline bool isEnable() { return _enable; }
    
    inline float getMass() { return _mass; }
    void setMass(float mass);
    inline float getDensity() { return _material.density; }
    void setDensity(float density);
    void setElasticity(float elasticity);
    void setFriction(float friction);
    
protected:
    bool init(Type type, PhysicsMaterial material);
    void initEnd();
    
    /**
     * @brief PhysicsShape is PhysicsBody's friend class, but all the subclasses isn't. so this method is use for subclasses to catch the bodyInfo from PhysicsBody.
     */
    PhysicsBodyInfo* bodyInfo() const;
    
    inline void setBody(PhysicsBody* body) { _body = body; }
    
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
    bool _enable;
    
    friend class PhysicsWorld;
    friend class PhysicsBody;
};

/** A circle shape */
class PhysicsShapeCircle : public PhysicsShape
{
public:
    static PhysicsShapeCircle* create(float radius, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    bool init(float radius, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeCircle();
    virtual ~PhysicsShapeCircle();
    
    friend class PhysicsBody;
};

/** A box shape */
class PhysicsShapeBox : public PhysicsShape
{
public:
    static PhysicsShapeBox* create(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    bool init(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
    
    friend class PhysicsBody;
};

/** A polygon shape */
class PhysicsShapePolygon : public PhysicsShape
{
public:
    static PhysicsShapePolygon* create(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    bool init(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, Point offset = Point(0, 0));
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
    
    friend class PhysicsBody;
};

/** A segment shape */
class PhysicsShapeEdgeSegment : public PhysicsShape
{
public:
    static PhysicsShapeEdgeSegment* create(Point a, Point b, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    bool init(Point a, Point b, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
    friend class PhysicsBody;
};

/** An edge box shape */
class PhysicsShapeEdgeBox : public PhysicsShape
{
public:
    static PhysicsShapeEdgeBox* create(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 0, Point offset = Point(0, 0));
    
protected:
    bool init(Size size, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
    friend class PhysicsBody;
};

/** An edge polygon shape */
class PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    static PhysicsShapeEdgePolygon* create(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    bool init(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
};

/** a chain shape */
class PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    static PhysicsShapeEdgeChain* create(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    bool init(Point* points, int count, PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();
    
    friend class PhysicsBody;
};

NS_CC_END
#endif // __CCPHYSICS_FIXTURE_H__

#endif // CC_USE_PHYSICS
