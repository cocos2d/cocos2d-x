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

#include "CCPhysicsWorldInfo_box2d.h"

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)
#include "CCPhysicsHelper_box2d.h"
#include "CCPhysicsBodyInfo_box2d.h"
NS_CC_BEGIN

PhysicsWorldInfo::PhysicsWorldInfo()
{
    _world = new b2World(b2Vec2(0.0f, 0.0f));
}

PhysicsWorldInfo::~PhysicsWorldInfo()
{
    CC_SAFE_DELETE(_world);
}

void PhysicsWorldInfo::setGravity(const Vect& gravity)
{
    _world->SetGravity(PhysicsHelper::point2Vec2(gravity));
}

void PhysicsWorldInfo::addBody(PhysicsBodyInfo& body)
{
    if (body.getBody() != nullptr)
    {
        removeBody(body);
    }
    
    body.setBody(_world->CreateBody(&body.getBodyDef()));
}

void PhysicsWorldInfo::removeBody(PhysicsBodyInfo& body)
{
    if (body.getBody() != nullptr)
    {
        _world->DestroyBody(body.getBody());
        body.setBody(nullptr);
    }
}

NS_CC_END
#endif // CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D
