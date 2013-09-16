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

#ifndef __CCPHYSICS_CONTACT_H__
#define __CCPHYSICS_CONTACT_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN

class PhysicsShape;
class PhysicsWorld;

class PhysicsContactInfo;

class PhysicsContact
{
public:
    inline PhysicsShape* getShapeA() { return _shapeA; }
    inline PhysicsShape* getShapeB() { return _shapeB; }
    inline void* getData() { return _data; }
    
private:
    static PhysicsContact* create(PhysicsShape* a, PhysicsShape* b);
    bool init(PhysicsShape* a, PhysicsShape* b);
    
private:
    PhysicsContact();
    ~PhysicsContact();
    
private:
    PhysicsShape* _shapeA;
    PhysicsShape* _shapeB;
    PhysicsContactInfo* _info;
    void* _data;
    
    friend class PhysicsWorld;
};

class PhysicsContactPreSolve
{
private:
    PhysicsContactPreSolve();
    ~PhysicsContactPreSolve();
    
    static PhysicsContactPreSolve* create();
    bool init();
    
    friend class PhysicsWorld;
};

class PhysicsContactPostSolve
{
private:
    PhysicsContactPostSolve();
    ~PhysicsContactPostSolve();
    
    static PhysicsContactPostSolve* create();
    bool init();
    
    friend class PhysicsWorld;
};

class PhysicsContactListener
{
public:
    PhysicsContactListener();
    virtual ~PhysicsContactListener();
    
public:
    std::function<bool(const PhysicsContact& contact)> onContactBegin;
    std::function<bool(const PhysicsContact& contact, const PhysicsContactPreSolve& solve)> onContactPreSolve;
    
    std::function<void(const PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    std::function<void(const PhysicsContact& contact)> onContactEnd;
};

NS_CC_END
#endif //__CCPHYSICS_CONTACT_H__

#endif // CC_USE_PHYSICS
