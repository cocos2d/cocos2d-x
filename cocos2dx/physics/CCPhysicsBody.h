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
class PhysicsFixture;
class PhysicsBodyInfo;

class PhysicsBody : public Object, public Clonable
{
public:
    static PhysicsBody* createCircle(Point centre, float radius);
    static PhysicsBody* createRectangle(Rect rect);
    static PhysicsBody* createPolygon(Array* points);
    
    static PhysicsBody* createEdgeSegment(Point x, Point y);
    static PhysicsBody* createEdgeCircle(Point centre, float radius);
    static PhysicsBody* createEdgeRectangle(Rect rect);
    static PhysicsBody* createEdgePolygon(Array* points);
    static PhysicsBody* createEdgeChain(Array* points);
    
    virtual void applyForce(Point force);
    virtual void applyForce(Point force, Point point);
    virtual void applyImpulse(Point impulse);
    virtual void applyImpulse(Point impulse, Point point);
    virtual void applyTorque(float torque);
    virtual void applyAngularImpulse(float impulse);
    
    void addFixture(PhysicsFixture* fixture);
    inline Array* getFixtures() const { return _fixtures; }
    void removeFixture(PhysicsFixture* fixture);
    void removeAllFixtures();
    
    inline PhysicsWorld* getWorld() const { return _world; }
    inline const std::vector<PhysicsJoint*>* getJoints() const { return &_joints; }
    
    inline Sprite* getOwner() const { return _owner; }
    
    void setCategoryBitmask(int bitmask);
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    void setContactTestBitmask(int bitmask);
    inline int getContactTestBitmask() const { return _contactTestBitmask; }
    void setCollisionBitmask(int bitmask);
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    virtual Clonable* clone() const override;
    
protected:
    static PhysicsBody* create();
    bool init();
    
protected:
    PhysicsBody();
    virtual ~PhysicsBody();
    
protected:
    float  _mass;
    float  _density;
    float  _area;
    float  _friction;
    Sprite*  _owner;
    Point  _velocity;
    float  _angularVelocity;
    bool   _resting;
    
    int    _categoryBitmask;
    int    _contactTestBitmask;
    int    _collisionBitmask;
    
    std::vector<PhysicsJoint*> _joints;
    Array* _fixtures;
    PhysicsWorld* _world;
    PhysicsBodyInfo* _info;
};

NS_CC_END

#endif // __CCPHYSICS_BODY_H__

#endif // CC_USE_PHYSICS
