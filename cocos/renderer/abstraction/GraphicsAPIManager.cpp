
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
#include "renderer/abstraction/GraphicsAPIManager.h"
#include "renderer/abstraction/interface/GraphicsInterface.h"
#include "base/CCConsole.h"

//#if ALL_PLATFORMS
#include "renderer/abstraction/opengles2.0/GraphicsOpenGLES2.0.h"
//#endif ALL_PLATFORMS

NS_CC_BEGIN

auto GraphicsAPIManager::create() -> std::unique_ptr<GraphicsAPIManager>
{
    auto manager = new (std::nothrow) GraphicsAPIManager;
    if (manager)
    {
        manager->registerFactories();
        return std::unique_ptr<GraphicsAPIManager>(manager);
    }
    return nullptr;
}

auto GraphicsAPIManager::registerFactories() -> void
{
    #define REGISTER_FACTORY(name, cls) \
    { \
        auto factory = []() -> std::unique_ptr<GraphicsInterface> { \
            return cls::create(); \
        }; \
        auto hash = std::hash<std::string>{}; \
        auto hval = size_t{hash(name)}; \
        _factories.insert(tRegisteredGraphicsAPIFactories::value_type(hval, factory)); \
        CCLOG("Registered factory for graphics API %s", name); \
    }
    
    REGISTER_FACTORY("opengles2.0", GraphicsOpenGLES20);
        
    #undef REGISTER_FACTORY
}

auto GraphicsAPIManager::createAPI(const char* name) -> std::unique_ptr<GraphicsInterface>
{
    auto hash = std::hash<std::string>{};
    auto hval = size_t{hash(name)};
    
    auto fi = _factories.find(hval);
    if (fi == _factories.end())
        return nullptr;
    return (*fi).second();
}

NS_CC_END
