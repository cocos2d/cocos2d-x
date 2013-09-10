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
#include "CCPhysicsBody.h"

#ifdef CC_USE_PHYSICS

NS_CC_BEGIN


#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)

class PhysicsBodyInfo
{
public:
    PhysicsBodyInfo();
    ~PhysicsBodyInfo();
    
public:
    cpBody* body;
    cpShape* shape;
};

PhysicsBodyInfo::PhysicsBodyInfo()
: body(nullptr)
, shape(nullptr)
{
}

PhysicsBodyInfo::~PhysicsBodyInfo()
{
    if (body) cpBodyFree(body);
    if (shape) cpShapeFree(shape);
}

PhysicsBody::PhysicsBody()
{
}

PhysicsBody::~PhysicsBody()
{
    CC_SAFE_DELETE(_info);
}

PhysicsBody* PhysicsBody::create()
{
    PhysicsBody * body = new PhysicsBody();
    if(body && body->init())
    {
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

bool PhysicsBody::init()
{
    do
    {
        _info = new PhysicsBodyInfo();
        CC_BREAK_IF(_info == nullptr);
        
        _info->body = cpBodyNew(1.0, 1.0);
        CC_BREAK_IF(_info->body == nullptr);
        
        return true;
    } while (false);
    
    return false;
}

PhysicsBody* PhysicsBody::createCircle(Point centre, float radius)
{
    PhysicsBody* body = PhysicsBody::create();
    
    if (body == nullptr)
    {
        return nullptr;
    }
    
    cpBodySetPos(body->_info->body, cpv(centre.x, centre.y));
    body->_info->shape = cpCircleShapeNew(body->_info->body, radius, cpvzero);
    
    if (body->_info->shape == nullptr)
    {
        return nullptr;
    }
    
    return body;
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)


#endif

NS_CC_END

#endif // CC_USE_PHYSICS
