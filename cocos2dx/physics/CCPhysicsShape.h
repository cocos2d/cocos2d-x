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
    
protected:
    bool init(PhysicsBody* body, Type type);
    
    /**
     * @brief PhysicsShape is PhysicsBody's friend class, but all the subclasses isn't. so this method is use for subclasses to catch the bodyInfo from PhysicsBody.
     */
    PhysicsBodyInfo* bodyInfo() const;
    
    void addToBody();
    
protected:
    PhysicsShape();
    virtual ~PhysicsShape() = 0;
    
protected:
    PhysicsBody* _body;
    PhysicsShapeInfo* _info;
    Type _type;
    
    friend class PhysicsWorld;
    friend class PhysicsBody;
};

/** A circle shape */
class PhysicsShapeCircle : public PhysicsShape
{
protected:
    static PhysicsShapeCircle* create(PhysicsBody* body, float radius, Point offset = Point(0, 0));
    bool init(PhysicsBody* body, float radius, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeCircle();
    virtual ~PhysicsShapeCircle();
    
    friend class PhysicsBody;
};

/** A box shape */
class PhysicsShapeBox : public PhysicsShape
{
protected:
    static PhysicsShapeBox* create(PhysicsBody* body, Size size, Point offset = Point(0, 0));
    bool init(PhysicsBody* body, Size size, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
    
    friend class PhysicsBody;
};

/** A polygon shape */
class PhysicsShapePolygon : public PhysicsShape
{
protected:
    static PhysicsShapePolygon* create(PhysicsBody* body, Point* points, int count, Point offset = Point(0, 0));
    bool init(PhysicsBody* body, Point* points, int count, Point offset = Point(0, 0));
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
    
    friend class PhysicsBody;
};

/** A segment shape */
class PhysicsShapeEdgeSegment : public PhysicsShape
{
protected:
    static PhysicsShapeEdgeSegment* create(PhysicsBody* body, Point a, Point b, float border = 1);
    bool init(PhysicsBody* body, Point a, Point b, float border = 1);
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
    friend class PhysicsBody;
};

/** An edge box shape */
class PhysicsShapeEdgeBox : public PhysicsShape
{
public:
    static PhysicsShapeEdgeBox* create(PhysicsBody* body, Size size, float border = 0, Point offset = Point(0, 0));
    
protected:
    bool init(PhysicsBody* body, Size size, float border = 1, Point offset = Point(0, 0));
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
    friend class PhysicsBody;
};

/** An edge polygon shape */
class PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    static PhysicsShapeEdgePolygon* create(PhysicsBody* body, Point* points, int count, float border = 1);
    
protected:
    bool init(PhysicsBody* body, Point* points, int count, float border = 1);
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
};

/** a chain shape */
class PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    static PhysicsShapeEdgeChain* create(PhysicsBody* body, Point* points, int count, float border = 1);
    
protected:
    bool init(PhysicsBody* body, Point* points, int count, float border = 1);
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();
    
    friend class PhysicsBody;
};

NS_CC_END
#endif // __CCPHYSICS_FIXTURE_H__

#endif // CC_USE_PHYSICS
