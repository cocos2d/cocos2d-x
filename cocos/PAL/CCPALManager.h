
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

#include "PAL/CCPALMacros.h"
#include "base/CCRef.h"

NS_PAL_BEGIN

class GraphicsInterface;

class PALManager
    : public NS_CC::Ref
{
public:
    
    PALManager();
    virtual ~PALManager();
    
    template <class T = PALManager>
    static T* create()
    {
        auto result = new (std::nothrow) T;
        if (result)
        {
            result->autorelease();
            return result;
        }
        delete result;
        return nullptr;
    }
    
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
                if (factory._impl == imp)
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

    template <class T>
    void registerFactory(const char* impl, tConstructor constructor)
    {
        auto fact = tFactoryType{constructor, impl};
        _factories.insert(tRegisteredFactories::value_type(typeHash<T>(), fact));
    }
    
    void registerFactories();
    
protected:
    
    static int _instances;
    
    struct tFactoryType
    {
        tConstructor _constructor;
        std::string  _impl;
    };
    
    using tRegisteredFactories = std::unordered_multimap<size_t, tFactoryType>;
    tRegisteredFactories _factories;
};

NS_PAL_END

#endif//_CC_PAL_MANAGER_H_
