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

#pragma once

#include <string>
#include "base/CCScriptComponent.h"
#include "jsapi.h"
#include "mozilla/Maybe.h"

NS_CC_BEGIN

class CC_DLL ComponentJS : public ScriptComponent
{
public:
    ComponentJS(const std::string& scriptFileName);
    
    /**
     * This function is used to be invoked from JS side to get the corresponding script object of this component.
     */
    void* getScriptObject() const override;
    
    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
private:
    // The returned value from require
    mozilla::Maybe<JS::PersistentRootedObject> _jsObj;
};

NS_CC_END

