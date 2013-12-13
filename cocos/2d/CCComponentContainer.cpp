/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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


#include "CCComponentContainer.h"
#include "CCComponent.h"
#include "CCDirector.h"

NS_CC_BEGIN

ComponentContainer::ComponentContainer(Node *pNode)
: _components(nullptr)
, _owner(pNode)
{
}

ComponentContainer::~ComponentContainer(void)
{
    CC_SAFE_DELETE(_components);
}

Component* ComponentContainer::get(const char *pName) const
{
    Component* pRet = NULL;
    CCASSERT(pName != NULL, "Argument must be non-nil");
    do {
        CC_BREAK_IF(NULL == pName);
        CC_BREAK_IF(NULL == _components);
        pRet = _components->at(pName);
        
    } while (0);
    return pRet;
}

bool ComponentContainer::add(Component *pCom)
{
    bool bRet = false;
    CCASSERT(pCom != NULL, "Argument must be non-nil");
    CCASSERT(pCom->getOwner() == NULL, "Component already added. It can't be added again");
    do
    {
        if (_components == nullptr)
        {
            _components = new Map<std::string, Component*>();
            _owner->scheduleUpdate();
        }
        Component *pComponent = _components->at(pCom->getName());
        
        CCASSERT(pComponent == NULL, "Component already added. It can't be added again");
        CC_BREAK_IF(pComponent);
        pCom->setOwner(_owner);
        _components->insert(pCom->getName(), pCom);
        pCom->onEnter();
        bRet = true;
    } while(0);
    return bRet;
}

bool ComponentContainer::remove(const char *pName)
{
    bool bRet = false;
    CCASSERT(pName != NULL, "Argument must be non-nil");
    do 
    {        
        CC_BREAK_IF(!_components);
        
        auto iter = _components->find(pName);
        CC_BREAK_IF(iter == _components->end());
        
        auto com = iter->second;
        com->onExit();
        com->setOwner(NULL);
        
        _components->erase(iter);
        
        bRet = true;
    } while(0);
    return bRet;
 }

void ComponentContainer::removeAll()
{
    if (_components != nullptr)
    {
        for (auto iter = _components->begin(); iter != _components->end(); ++iter)
        {
            iter->second->onExit();
            iter->second->setOwner(NULL);
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

void ComponentContainer::visit(float fDelta)
{
    if (_components != nullptr)
    {
        for (auto iter = _components->begin(); iter != _components->end(); ++iter)
        {
            iter->second->update(fDelta);
        }
    }
}

bool ComponentContainer::isEmpty() const
{
    return (_components == nullptr || _components->empty());
}

NS_CC_END
