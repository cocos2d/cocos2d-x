
/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef _CC_GRAPHICS_API_MANAGER_H_
#define _CC_GRAPHICS_API_MANAGER_H_

#include <memory>
#include <string>
#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"

NS_CC_BEGIN

class GraphicsInterface;

class GraphicsAPIManager
    : public Ref
{
public:
    
    // @brief creates the Graphics API Manager
    static GraphicsAPIManager* create();
    
    // @brief creates a specific graphics API instance
    // @usage take a null terminated pointer to array of const char*
    GraphicsInterface* createAPI(const char* apis[], const char* title);
    
    // @brief destroy a graphics API instance
    void destroyAPI(GraphicsInterface* api);
    
protected:
    
    void registerFactories();
    
protected:
    
    using tConstructor = std::function<GraphicsInterface* (const char* title)>;
    using tDestructor  = std::function<void (GraphicsInterface* instance)>;
    struct tFactoryType
    {
        tConstructor _constructor;
        tDestructor  _destructor;
        std::string  _name;
    };
    using tRegisteredGraphicsAPIFactories = std::unordered_map<size_t, tFactoryType>;
    tRegisteredGraphicsAPIFactories _factories;
    tFactoryType _currentAPIFactory;
};

NS_CC_END

#endif // _CC_GRAPHICS_API_MANAGER_H_
