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

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"
#include <vector>

NS_CC_BEGIN
class Sprite;
class PhysicsWorld;
class PhysicsJoint;
class PhysicsShape;
class PhysicsShapeCircle;
class PhysicsShapeBox;
class PhysicsShapePolygon;
class PhysicsShapeEdgeSegment;
class PhysicsShapeEdgeBox;
class PhysicsShapeEdgePolygon;
class PhysicsShapeEdgeChain;

class PhysicsBodyInfo;

class PhysicsBody : public Object//, public Clonable
{
public:
    static PhysicsBody* createCircle(float radius);
    static PhysicsBody* createBox(Size size);
    static PhysicsBody* createPolygon(Point* points, int count);
    
    static PhysicsBody* createEdgeSegment(Point a, Point b, float border = 1);
    static PhysicsBody* createEdgeBox(Size size, float border = 1);
    static PhysicsBody* createEdgePolygon(Point* points, int count, float border = 1);
    static PhysicsBody* createEdgeChain(Point* points, int count, float border = 1);
    
    virtual PhysicsShapeCircle* addCircle(float radius, Point offset = Point(0, 0));
    virtual PhysicsShapeBox* addBox(Size size, Point offset = Point(0, 0));
    virtual PhysicsShapePolygon* addPolygon(Point* points, int count, Point offset = Point(0, 0));
    
    virtual PhysicsShapeEdgeSegment* addEdgeSegment(Point a, Point b, float border = 1);
    virtual PhysicsShapeEdgeBox* addEdgeBox(Size size, float border = 1, Point offset = Point(0, 0));
    virtual PhysicsShapeEdgePolygon* addEdgePolygon(Point* points, int count, float border = 1);
    virtual PhysicsShapeEdgeChain* addEdgeChain(Point* points, int count, float border = 1);
    
    virtual void applyForce(Point force);
    virtual void applyForce(Point force, Point offset);
    virtual void applyImpulse(Point impulse);
    virtual void applyImpulse(Point impulse, Point offset);
    virtual void applyTorque(float torque);
    
    inline std::vector<PhysicsShape*>& getShapes() { return _shapes; }
    inline PhysicsShape* getShape() { return _shapes.size() >= 1 ? _shapes.front() : nullptr; }
    void removeShape(PhysicsShape* shape);
    void removeAllShapes();
    
    inline PhysicsWorld* getWorld() const { return _world; }
    inline const std::vector<PhysicsJoint*>* getJoints() const { return &_joints; }
    
    inline Sprite* getOwner() const { return _owner; }
    
    void setCategoryBitmask(int bitmask);
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    void setContactTestBitmask(int bitmask);
    inline int getContactTestBitmask() const { return _contactTestBitmask; }
    void setCollisionBitmask(int bitmask);
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    Point getPosition() const;
    float getRotation() const;
    
    inline bool isDynamic() { return _dynamic; }
    void setDynamic(bool dynamic);
    
    void setMass(float mass);
    inline float getMass() { return _mass; }
    
    void setAngularDamping(float angularDamping);
    inline float getAngularDamping() { return _angularDamping; }
    
    //virtual Clonable* clone() const override;
    
protected:
    
    bool init();
    bool initStatic();
    
    virtual void setPosition(Point position);
    virtual void setRotation(float rotation);
    virtual void addShape(PhysicsShape* shape);
    
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
    bool                        _massDefault;
    bool                        _angularDampingDefault;
    float                       _mass;
    float                       _area;
    float                       _density;
    float                       _angularDamping;
    
    int    _categoryBitmask;
    int    _contactTestBitmask;
    int    _collisionBitmask;
    
    friend class PhysicsWorld;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class Sprite;
};

NS_CC_END

#endif // __CCPHYSICS_BODY_H__

#endif // CC_USE_PHYSICS
