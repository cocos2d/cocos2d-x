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

#ifndef __CCCOMPONENT_LUA__
#define __CCCOMPONENT_LUA__

#include <string>
#include <unordered_map>
#include "2d/CCComponent.h"

NS_CC_BEGIN

class CC_DLL ComponentLua : public Component
{
public:
    static ComponentLua* create(const std::string& scriptFileName);
    
    virtual void update(float dt);
    
private:
    ComponentLua(const std::string& scriptFileName);
    void loadAndExecuteScript();
    void getUserData();
    
private:
    // lua script file path
    std::string _scriptFileName;
};

NS_CC_END

#endif /* defined(__CCCOMPONENT_LUA__) */
