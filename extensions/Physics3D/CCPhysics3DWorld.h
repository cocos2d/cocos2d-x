/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __PHYSICS_3D_WORLD_H__
#define __PHYSICS_3D_WORLD_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"


#if (CC_ENABLE_BULLET_INTEGRATION)

class btDynamicsWorld;

NS_CC_EXT_BEGIN

class Physics3DObject;
class Physics3DConstraint;

CC_EX_DLL struct Physics3DWorldDes
{
    
};

CC_EX_DLL class Physics3DWorld : Ref
{
public:
    Physics3DWorld* create(const Physics3DWorldDes* info);
    
    void addPhysics3DObject(Physics3DObject* physicsObj);
    
    void removePhysics3DObject(Physics3DObject* physicsObj);
    
    void removeAllPhysics3DObjects();
    
    void addPhysics3DConstraint(Physics3DConstraint* constraint);
    
    void removePhysics3DConstraint(Physics3DConstraint* constraint);
    
    void removeAllPhysics3DConstraints();
    
    void stepSimulate(float dt);
    
protected:
    Physics3DWorld();
    virtual ~Physics3DWorld();
    
#if (CC_ENABLE_BULLET_INTEGRATION)
    btDynamicsWorld* _phyiscsWorld;
#endif // CC_ENABLE_BULLET_INTEGRATION
};

NS_CC_EXT_END

#endif

#endif // __PHYSICS_3D_WORLD_H__
