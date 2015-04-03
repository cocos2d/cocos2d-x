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

#include "CCPhysics3D.h"

#if (CC_ENABLE_BULLET_INTEGRATION)



NS_CC_EXT_BEGIN

Physics3DComponent::~Physics3DComponent()
{
    
}

std::string& Physics3DComponent::getPhysics3DComponentName()
{
    static std::string comName = "___Physics3DComponent___";
    return comName;
}

bool Physics3DComponent::init()
{
    setName(getPhysics3DComponentName());
    return Component::init();
}

Physics3DComponent* Physics3DComponent::create(Physics3DObject* physicsObj)
{
    auto ret = new (std::nothrow) Physics3DComponent();
    if (ret && ret->init())
    {
        ret->setPhysics3DObject(physicsObj);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//virtual void update(float delta);
bool Physics3DComponent::serialize(void* r)
{
    //TODO: FIXME
    return Component::serialize(r);
}

void Physics3DComponent::setPhysics3DObject(Physics3DObject* physicsObj)
{
    CC_SAFE_RETAIN(physicsObj);
    CC_SAFE_RELEASE(_physics3DObj);
    _physics3DObj = physicsObj;
}

Physics3DComponent::Physics3DComponent()
: _physics3DObj(nullptr)
{
    
}

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION
