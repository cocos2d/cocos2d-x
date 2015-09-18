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


#include "2d/CCComponentContainer.h"
#include "2d/CCComponent.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

ComponentContainer::ComponentContainer(Node* node)
: _owner(node)
{
}

ComponentContainer::~ComponentContainer()
{  
}

Component* ComponentContainer::get(const std::string& name) const
{
    Component* ret = nullptr;

    auto it = _componentMap.find(name);
    if (it != _componentMap.end())
    {
        ret = it->second;
    }

    return ret;
}

bool ComponentContainer::add(Component *com)
{
    bool ret = false;
    CCASSERT(com != nullptr, "Component must be non-nil");
    CCASSERT(com->getOwner() == nullptr, "Component already added. It can't be added again");
    do
    {
        auto typeName = typeid(*com).name();
        if (_components.find(typeName) != _components.end())
        {
            CCASSERT(true,"ComponentContainer already have this kind of component");
            break;
        }
        com->setOwner(_owner);
        _components.insert(typeName, com);
        _componentMap[com->getName()] = com;
        com->onAdd();

        ret = true;
    } while(0);
    return ret;
}

bool ComponentContainer::remove(const std::string& name)
{
    bool ret = false;
    do 
    {        
        auto iter = _componentMap.find(name);
        CC_BREAK_IF(iter == _componentMap.end());      
        remove(iter->second);

        ret = true;
    } while(0);

    return ret;
 }

bool ComponentContainer::remove(Component *com)
{
    bool ret = false;
    do
    {
        auto iter = _components.find(typeid(*com).name());
        if (iter != _components.end())
        {
            _componentMap.erase(com->getName());

            com->onRemove();
            com->setOwner(nullptr);
            _components.erase(iter);
        }
        
        ret = true;
    } while(0);

    return ret;
}

void ComponentContainer::removeAll()
{
    if (!_componentMap.empty())
    {
        for (auto iter = _components.begin(); iter != _components.end(); ++iter)
        {
            iter->second->onRemove();
            iter->second->setOwner(nullptr);
        }
        
        _components.clear();
        _componentMap.clear();
        _owner->unscheduleUpdate();
    }
}

void ComponentContainer::visit(float delta)
{
    if (!_components.empty())
    {
        CC_SAFE_RETAIN(_owner);
        auto iterEnd = _components.end();
        for (auto iter = _components.begin(); iter != iterEnd; ++iter)
        {
            iter->second->update(delta);
        }
        CC_SAFE_RELEASE(_owner);
    }
}

void ComponentContainer::onEnter()
{
    for (auto iter = _components.begin(); iter != _components.end(); ++iter)
    {
        iter->second->onEnter();
    }
}

void ComponentContainer::onExit()
{
    for (auto iter = _components.begin(); iter != _components.end(); ++iter)
    {
        iter->second->onExit();
    }
}

NS_CC_END
