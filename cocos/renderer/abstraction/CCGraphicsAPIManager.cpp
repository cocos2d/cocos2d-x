
/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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

#include <memory>
#include "renderer/abstraction/CCGraphicsAPIManager.h"
#include "renderer/abstraction/interface/CCGraphicsInterface.h"
#include "base/CCConsole.h"

//#if ALL_PLATFORMS
#include "renderer/abstraction/opengles2.0/CCGraphicsOpenGLES2.0.h"
//#endif ALL_PLATFORMS

NS_CC_BEGIN

auto GraphicsAPIManager::create() -> GraphicsAPIManager*
{
    auto manager = new (std::nothrow) GraphicsAPIManager;
    if (manager)
    {
        manager->registerFactories();
        manager->autorelease();
        return manager;
    }
    return nullptr;
}

auto GraphicsAPIManager::registerFactories() -> void
{
    #define REGISTER_FACTORY(name, cls) \
    { \
        auto constructor = tConstructor{[](const char* title) -> GraphicsInterface* { \
            return cls::create(title); \
        }}; \
        auto destructor = tDestructor{[](GraphicsInterface* instance) -> void { \
            static_cast<cls*>(instance)->release(); \
        }}; \
        auto pair = std::pair<tConstructor, tDestructor>{constructor, destructor}; \
        auto hash = std::hash<std::string>{}; \
        _factories.insert(tRegisteredGraphicsAPIFactories::value_type(size_t{hash(name)}, pair)); \
        CCLOG("Registered factory for graphics API %s", name); \
    }
    
    REGISTER_FACTORY("opengles2.0", GraphicsOpenGLES20);
        
    #undef REGISTER_FACTORY
}

GraphicsInterface* GraphicsAPIManager::createAPI(const char* name, const char* title)
{
    auto hash = std::hash<std::string>{};
    auto hval = size_t{hash(name)};
    
    auto fi = _factories.find(hval);
    if (fi == _factories.end())
        return nullptr;
    return (*fi).second.first(title);
}

void GraphicsAPIManager::destroyAPI(GraphicsInterface* api)
{
    
}

NS_CC_END
