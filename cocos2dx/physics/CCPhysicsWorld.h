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

#ifndef __CCPHYSICS_WORLD_H__
#define __CCPHYSICS_WORLD_H__

#include "CCObject.h"
#include "CCGeometry.h"
#include "CCPhysicsSetting.h"

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsWorldInfo;
class PhysicsContactDelegate;

class PhysicsWorld : public Object
{
public:
    static PhysicsWorld* create();
    void addChild(PhysicsBody* body);
    
    void addJoint(PhysicsJoint* joint);
    void removeJoint(PhysicsJoint* joint);
    void removeAllJoints();
    
    Array* bodysAlongRay(Point start, Point end);
    Array* bodysAtPoint(Point point);
    Array* bodysInRect(Rect rect);
    Array* getAllBody();
    
    void registerContactDelegate(PhysicsContactDelegate* delegate);
    
protected:
    bool init();
    
protected:
    Point _gravity;
    float _speed;
    
    class PhysicsWorldInfo* _worldInfo;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
};

NS_CC_END

#endif // __CCPHYSICS_WORLD_H__
