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

#include "CCPhysicsWorld.h"

NS_CC_BEGIN

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)

class PhysicsWorldInfo
{
public:
    cpSpace* space;
    
public:
    PhysicsWorldInfo();
    ~PhysicsWorldInfo();
};

PhysicsWorldInfo::PhysicsWorldInfo()
{
    space = cpSpaceNew();
}

PhysicsWorldInfo::~PhysicsWorldInfo()
{
    cpSpaceFree(space);
}

bool PhysicsWorld::init()
{
    _worldInfo = new PhysicsWorldInfo();
    
    cpSpaceSetGravity(_worldInfo->space, cpv(_gravity.x, _gravity.y));
    
    return true;
}

void PhysicsWorld::addChild(PhysicsBody* body)
{
    
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

struct PhysicsInfo
{
    
};
#endif

PhysicsWorld* PhysicsWorld::create()
{
    PhysicsWorld * world = new PhysicsWorld();
    if(world && world->init())
    {
        return world;
    }
    
    CC_SAFE_DELETE(world);
    return nullptr;
}

PhysicsWorld::PhysicsWorld()
: _gravity(Point(0, -9.8))
, _speed(1.0)
, _worldInfo(nullptr)
{
    
}

PhysicsWorld::~PhysicsWorld()
{
    CC_SAFE_DELETE(_worldInfo);
}

NS_CC_END
