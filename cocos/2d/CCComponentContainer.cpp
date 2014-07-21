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
#include "base/CCDirector.h"

NS_CC_BEGIN

ComponentContainer::ComponentContainer(Node *node)
: _components(nullptr)
, _owner(node)
{
}

ComponentContainer::~ComponentContainer(void)
{
    CC_SAFE_DELETE(_components);
}

Component* ComponentContainer::get(const std::string& name) const
{
    Component* ret = nullptr;
    do {
        CC_BREAK_IF(nullptr == _components);
        ret = _components->at(name);
        
    } while (0);
    return ret;
}

bool ComponentContainer::add(Component *com)
{
    bool ret = false;
    CCASSERT(com != nullptr, "Argument must be non-nil");
    CCASSERT(com->getOwner() == nullptr, "Component already added. It can't be added again");
    do
    {
        if (_components == nullptr)
        {
            _components = new Map<std::string, Component*>();
        }
        Component *component = _components->at(com->getName());
        
        CCASSERT(component == nullptr, "Component already added. It can't be added again");
        CC_BREAK_IF(component);
        com->setOwner(_owner);
        _components->insert(com->getName(), com);
        com->onEnter();
        ret = true;
    } while(0);
    return ret;
}

bool ComponentContainer::remove(const std::string& name)
{
    bool ret = false;
    do 
    {        
        CC_BREAK_IF(!_components);
        
        auto iter = _components->find(name);
        CC_BREAK_IF(iter == _components->end());
        
        auto com = iter->second;
        com->onExit();
        com->setOwner(nullptr);
        
        _components->erase(iter);
        ret = true;
    } while(0);
    return ret;
 }

bool ComponentContainer::remove(Component *com)
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(!_components);
        
        for (auto iter = _components->begin(); iter != _components->end(); ++iter)
        {
            if (iter->second == com)
            {
                com->onExit();
                com->setOwner(nullptr);
                _components->erase(iter);
                break;
            }
        }
        ret = true;
    } while(0);
    return ret;
}

void ComponentContainer::removeAll()
{
    if (_components != nullptr)
    {
        for (auto iter = _components->begin(); iter != _components->end(); ++iter)
        {
            iter->second->onExit();
            iter->second->setOwner(nullptr);
        }
        
        _components->clear();
        CC_SAFE_DELETE(_components);
        
        _owner->unscheduleUpdate();
    }
}

void ComponentContainer::alloc(void)
{
    _components = new Map<std::string, Component*>();
}

void ComponentContainer::visit(float delta)
{
    if (_components != nullptr)
    {
        CC_SAFE_RETAIN(_owner);
        for (auto iter = _components->begin(); iter != _components->end(); ++iter)
        {
            iter->second->update(delta);
        }
        CC_SAFE_RELEASE(_owner);
    }
}

bool ComponentContainer::isEmpty() const
{
    return (_components == nullptr || _components->empty());
}

NS_CC_END
