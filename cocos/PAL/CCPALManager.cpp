
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

//#include <memory>
#include "base/ccMacros.h"
#include "PAL/CCPALManager.h"
#include "PAL/graphics/opengles2.0/CCGraphicsOpenGLES2.0.h"
#include "PAL/graphics/metal/CCGraphicsMetal.h"

NS_CC_BEGIN

// we only allow a single PAL manager instance
int PALManager::_instances = 0;

PALManager::PALManager()
{
    CCASSERT(++_instances == 1, "Only a single PAL manager instance is allowed");
    registerFactories();
}

PALManager::~PALManager()
{
    --_instances;
    CCASSERT(++_instances == 0, "Only a single PAL manager instance is allowed");
}

//
// Protected Methods
//

void PALManager::registerFactories()
{
    #define REGISTER_FACTORY(T, impl, cls) \
    { \
        auto constructor = tConstructor{[]() -> void* { \
            return cls::create(); \
        }}; \
        auto destructor = tDestructor{[](void* instance) -> void { \
            static_cast<cls*>(instance)->release(); \
        }}; \
        registerFactory<T>(impl, constructor, destructor); \
    }

    REGISTER_FACTORY(GraphicsInterface, "opengles2.0", GraphicsOpenGLES20);
#ifdef CC_METAL_AVAILABLE
    REGISTER_FACTORY(GraphicsInterface, "metal", GraphicsMetal);
#endif//CC_METAL_AVAILABLE

    #undef REGISTER_FACTORY
}

//GraphicsInterface* GraphicsAPIManager::createAPI(const char* apis[], const char* title)
//{
//    GraphicsInterface* api = nullptr;
//    
//    while (apis && *apis)
//    {
//        auto name = *apis++;
//        
//        auto hash = std::hash<std::string>{};
//        auto hval = size_t{hash(name)};
//        
//        auto fi = _factories.find(hval);
//        if (fi == _factories.end())
//            return nullptr;
//        
//        _currentAPIFactory = (*fi).second;
//        api = _currentAPIFactory._constructor(title);
//    }
//    
//    return api;
//}
//
//void GraphicsAPIManager::destroyAPI(GraphicsInterface* api)
//{
//    if (_currentAPIFactory._destructor)
//        _currentAPIFactory._destructor(api);
//    _currentAPIFactory = tFactoryType();
//}

NS_CC_END
