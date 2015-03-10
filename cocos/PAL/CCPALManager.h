
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

#ifndef _CC_PAL_MANAGER_H_
#define _CC_PAL_MANAGER_H_

#include <memory>
#include <string>
#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"

NS_CC_BEGIN

class GraphicsInterface;

class PALManager
    : public Ref
{
public:
    
    PALManager();
    virtual ~PALManager();
    
    template <class T>
    T* createObject(const char* impls[])
    {
        auto range = _factories.equal_range(typeHash<T>());
        for (auto it = range.first; it != range.second; ++it)
        {
            auto& factory = it->second;
            auto imp = *impls;
            do
            {
                if (factory._name == imp)
                {
                    auto instance = static_cast<T*>(factory._constructor());
                    return instance;
                }
                ++imp;
            }
            while (imp);
        }
        return nullptr;
    }
    
    template <class T>
    bool destroyObject(T* instance)
    {
        auto range = _factories.equal_range(typeHash<T>());
        for (auto it = range.first; it != range.second; ++it)
        {
            auto& factory = it->second;
            
            if (factory._name == instance->implName())
            {
                factory._destructor(instance);
                return true;
            }
        }
        return false;
    }
    
protected:
    
    template <class T>
    const char* typeName() const
    {
        return typeid(T).name();
    }
    
    template <class T>
    size_t typeHash() const
    {
        auto hash = std::hash<std::string>();
        return size_t{hash(typeName<T>())};
    }
    
    using tConstructor = std::function<void* ()>;
    using tDestructor  = std::function<void (void*)>;

    template <class T>
    void registerFactory(const char* impl, tConstructor constructor, tDestructor destructor)
    {
        auto fact = tFactoryType{constructor, destructor, impl};
        _factories.insert(tRegisteredFactories::value_type(typeHash<T>(), fact));
        CCLOG("Registered factory for %s implementation %s", typeName<T>(), impl);
    }
    
    void registerFactories();
    
protected:
    
    static int _instances;
    
    struct tFactoryType
    {
        tConstructor _constructor;
        tDestructor  _destructor;
        std::string  _name;
    };
    
    using tRegisteredFactories = std::unordered_multimap<size_t, tFactoryType>;
    tRegisteredFactories _factories;
};

NS_CC_END

#endif // _CC_PAL_MANAGER_H_
