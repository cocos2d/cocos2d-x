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

#ifndef __CCPHYSICS_WORLD_INFO_CHIPMUNK_H__
#define __CCPHYSICS_WORLD_INFO_CHIPMUNK_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include <vector>
#include "base/CCPlatformMacros.h"
#include "math/CCGeometry.h"

struct cpSpace;


NS_CC_BEGIN
typedef Vec2 Vect;
class PhysicsBodyInfo;
class PhysicsJointInfo;
class PhysicsShapeInfo;

class PhysicsWorldInfo
{
public:
    cpSpace* getSpace() const { return _space; }
    void addShape(PhysicsShapeInfo& shape);
    void removeShape(PhysicsShapeInfo& shape);
    void addBody(PhysicsBodyInfo& body);
    void removeBody(PhysicsBodyInfo& body);
    void addJoint(PhysicsJointInfo& joint);
    void removeJoint(PhysicsJointInfo& joint);
    void setGravity(const Vect& gravity);
    bool isLocked();
    void step(float delta);
    
private:
    PhysicsWorldInfo();
    ~PhysicsWorldInfo();
    
private:
    cpSpace* _space;
    
    friend class PhysicsWorld;
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_INFO_CHIPMUNK_H__
