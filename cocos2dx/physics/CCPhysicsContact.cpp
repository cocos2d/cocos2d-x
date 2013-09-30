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
#include "CCPhysicsContact.h"
#ifdef CC_USE_PHYSICS

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include "chipmunk.h"
#elif (CC_PHYSICS_ENGINE == CCPHYSICS_BOX2D)
#include "Box2D.h"
#endif

#include "chipmunk/CCPhysicsContactInfo.h"
#include "Box2D/CCPhysicsContactInfo.h"

NS_CC_BEGIN

PhysicsContact::PhysicsContact()
: _shapeA(nullptr)
, _shapeB(nullptr)
, _info(nullptr)
, _data(nullptr)
{
    
}

PhysicsContact::~PhysicsContact()
{
    CC_SAFE_DELETE(_info);
}

PhysicsContact* PhysicsContact::create(PhysicsShape* a, PhysicsShape* b)
{
    PhysicsContact * contact = new PhysicsContact();
    if(contact && contact->init(a, b))
    {
        return contact;
    }
    
    CC_SAFE_DELETE(contact);
    return nullptr;
}

bool PhysicsContact::init(PhysicsShape* a, PhysicsShape* b)
{
    do
    {
        CC_BREAK_IF(a == nullptr || b == nullptr);
        
        CC_BREAK_IF(!(_info = new PhysicsContactInfo(this)));
        
        _shapeA = a;
        _shapeB = b;
        
        return true;
    } while(false);
    
    return false;
}

// PhysicsContactPreSolve implementation
PhysicsContactPreSolve::PhysicsContactPreSolve()
{
    
}

PhysicsContactPreSolve::~PhysicsContactPreSolve()
{
    
}

PhysicsContactPreSolve* PhysicsContactPreSolve::create()
{
    PhysicsContactPreSolve * solve = new PhysicsContactPreSolve();
    if(solve && solve->init())
    {
        return solve;
    }
    
    CC_SAFE_DELETE(solve);
    return nullptr;
}

bool PhysicsContactPreSolve::init()
{
    return true;
}


// PhysicsContactPostSolve implementation
PhysicsContactPostSolve::PhysicsContactPostSolve()
{
    
}

PhysicsContactPostSolve::~PhysicsContactPostSolve()
{
    
}

PhysicsContactPostSolve* PhysicsContactPostSolve::create()
{
    PhysicsContactPostSolve * solve = new PhysicsContactPostSolve();
    if(solve && solve->init())
    {
        return solve;
    }
    
    CC_SAFE_DELETE(solve);
    return nullptr;
}

bool PhysicsContactPostSolve::init()
{
    return true;
}

PhysicsContactListener::PhysicsContactListener()
: onContactBegin(nullptr)
, onContactPreSolve(nullptr)
, onContactPostSolve(nullptr)
, onContactEnd(nullptr)
{
    
}

PhysicsContactListener::~PhysicsContactListener()
{
    
}

NS_CC_END
#endif // CC_USE_PHYSICS
