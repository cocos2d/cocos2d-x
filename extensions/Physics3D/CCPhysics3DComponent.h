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

#ifndef __PHYSICS_3D_COMPONENT_H__
#define __PHYSICS_3D_COMPONENT_H__

#include "math/CCMath.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "2d/CCComponent.h"

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_EXT_BEGIN

class Physics3DObject;

class CC_EX_DLL Physics3DComponent : public cocos2d::Component
{
public:
    CREATE_FUNC(Physics3DComponent);
    virtual ~Physics3DComponent();
    virtual bool init() override;
    
    //virtual void update(float delta);
    virtual bool serialize(void* r) override;
    static Physics3DComponent* create(Physics3DObject* physicsObj);
    
    void setPhysics3DObject(Physics3DObject* physicsObj);
    
    Physics3DObject* getPhysics3DObject() const { return _physics3DObj; }
    
    static std::string& getPhysics3DComponentName();
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DComponent();
    
protected:
    Physics3DObject* _physics3DObj;
};

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // __PHYSICS_3D_COMPONENT_H__
