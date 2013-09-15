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


#include "support/component/CCComponentContainer.h"
#include "support/component/CCComponent.h"
#include "CCDirector.h"

NS_CC_BEGIN

ComponentContainer::ComponentContainer(Node *pNode)
: _components(NULL)
, _owner(pNode)
{
}

ComponentContainer::~ComponentContainer(void)
{
    CC_SAFE_RELEASE(_components);
}

Component* ComponentContainer::get(const char *pName) const
{
    Component* pRet = NULL;
    CCASSERT(pName != NULL, "Argument must be non-nil");
    do {
        CC_BREAK_IF(NULL == pName);
        CC_BREAK_IF(NULL == _components);
        pRet = dynamic_cast<Component*>(_components->objectForKey(pName));
        
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
        if (_components == NULL)
        {
            _components = Dictionary::create();
            _components->retain();
            _owner->scheduleUpdate();
        }
        Component *pComponent = dynamic_cast<Component*>(_components->objectForKey(pCom->getName()));
        
        CCASSERT(pComponent == NULL, "Component already added. It can't be added again");
        CC_BREAK_IF(pComponent);
        pCom->setOwner(_owner);
        _components->setObject(pCom, pCom->getName());
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
        Object* pRetObject = NULL;
        DictElement *pElement = NULL;
        HASH_FIND_PTR(_components->_elements, pName, pElement);
        if (pElement != NULL)
        {
           pRetObject = pElement->getObject();
        }
        Component *com = dynamic_cast<Component*>(pRetObject);
        CC_BREAK_IF(!com);
        com->onExit();
        com->setOwner(NULL);
        HASH_DEL(_components->_elements, pElement);
        pElement->getObject()->release();
        CC_SAFE_DELETE(pElement);
        bRet = true;
    } while(0);
    return bRet;
 }

void ComponentContainer::removeAll()
{
    if (_components != NULL)
    {
        DictElement *pElement, *tmp;
        HASH_ITER(hh, _components->_elements, pElement, tmp)
        {
            HASH_DEL(_components->_elements, pElement);
            ((Component*)pElement->getObject())->onExit();
            ((Component*)pElement->getObject())->setOwner(NULL);
            pElement->getObject()->release();
            CC_SAFE_DELETE(pElement);
        }
        _owner->unscheduleUpdate();
    }
}

void ComponentContainer::alloc(void)
{
    _components = Dictionary::create();
    _components->retain();
}

void ComponentContainer::visit(float fDelta)
{
    if (_components != NULL)
    {
        DictElement *pElement, *tmp;
        HASH_ITER(hh, _components->_elements, pElement, tmp)
        {
            ((Component*)pElement->getObject())->update(fDelta);
        }
    }
}

bool ComponentContainer::isEmpty() const
{
    return (bool)(!(_components && _components->count()));
}

NS_CC_END
