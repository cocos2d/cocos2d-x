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

#ifndef __CC_FRAMEWORK_COMCONTAINER_H__
#define __CC_FRAMEWORK_COMCONTAINER_H__

/// @cond DO_NOT_SHOW

#include "base/CCMap.h"
#include <string>

NS_CC_BEGIN

class Component;
class Node;

class CC_DLL ComponentContainer
{
protected:
    /**
     * @js ctor
     */
    ComponentContainer(Node* node);
    
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ComponentContainer();
    
    template<typename T>
    T* getComponent() const
    {
        auto typeName = typeid(T).name();
        auto iter = _components.find(typeName);
        if (iter != _components.end())
        {
            return static_cast<T*>(iter->second);
        }
        
        return nullptr;
    }
    
	/**
     * @js getComponent
     */
	virtual Component* get(const std::string& name) const;
    virtual bool add(Component *com);
    virtual bool remove(const std::string& name);
    virtual bool remove(Component *com);
    virtual void removeAll();
    virtual void visit(float delta);
    
    virtual void onEnter();
    virtual void onExit();
    
    bool isEmpty() const { return _componentMap.empty(); }
    
private:
    Map<std::string, Component*> _components;
    std::unordered_map<std::string, Component*> _componentMap;
    Node *_owner;
    
    friend class Node;
};

NS_CC_END

/// @endcond
#endif  // __FUNDATION__CCCOMPONENT_H__
