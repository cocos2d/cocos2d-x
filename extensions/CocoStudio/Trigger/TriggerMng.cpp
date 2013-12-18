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

#include "TriggerMng.h"
#include "TriggerObj.h"
#include "TriggerBase.h"

NS_CC_EXT_BEGIN

TriggerMng* TriggerMng::_sharedTriggerMng = NULL;

TriggerMng::TriggerMng(void)
: _eventTriggers(NULL)
{
    
}

TriggerMng::~TriggerMng(void)
{
    CC_SAFE_RELEASE(_eventTriggers);
}

const char* TriggerMng::triggerMngVersion()
{
    return "1.0.0.0";
}

TriggerMng* TriggerMng::sharedTriggerMng()
{
    if (NULL == _sharedTriggerMng)
    {
        _sharedTriggerMng = new TriggerMng();
    }
    return _sharedTriggerMng;
}

void TriggerMng::purgeTriggerMng()
{
    CC_SAFE_DELETE(_sharedTriggerMng);
}

void TriggerMng::parse(const rapidjson::Value &root)
{
    CCLOG("%s", triggerMngVersion());
    do {
          int count = DICTOOL->getArrayCount_json(root, "Triggers");
          for (int i = 0; i < count; ++i)
          {
                const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(root, "Triggers", i);
                TriggerObj *obj = TriggerObj::create();
                obj->serialize(subDict);
				int length = DICTOOL->getArrayCount_json(subDict, "events");
				for (int i = 0; i < length; ++i)
				{
					const rapidjson::Value &sub = DICTOOL->getSubDictionary_json(subDict, "events", i);
					int event = DICTOOL->getIntValue_json(sub, "id");
					if (event < 0)
					{
						continue;
					}
					add((unsigned int)(event), obj);
				}    
          }
        
    } while (0);
}

CCArray* TriggerMng::get(unsigned int event) const
{
    CCArray* pRet = NULL;
    CCAssert(event >= 0, "Argument must be larger than 0");
    do {
        CC_BREAK_IF(NULL == _eventTriggers);
        pRet = dynamic_cast<CCArray*>(_eventTriggers->objectForKey(event));
        
    } while (0);
    return pRet;
}

bool TriggerMng::add(unsigned int event, TriggerObj *pObj)
{
    bool bRet = false;
    CCAssert(pObj != NULL, "Argument must be non-nil");
    do
    {
        if (_eventTriggers == NULL)
        {
            alloc();
        }
        CCArray *pArray = dynamic_cast<CCArray*>(_eventTriggers->objectForKey(event));
        if (pArray == NULL)
        {
            pArray = CCArray::create();
        }
		if (pArray->indexOfObject(pObj) == UINT_MAX)
		{
			pArray->addObject(pObj);
			_eventTriggers->setObject(pArray, event);
		}
        bRet = true;
    } while(0);
    return bRet;
}

void TriggerMng::removeAll(void)
{
    if(_eventTriggers != NULL)
    {
        CCDictElement *pElement, *tmp;
        HASH_ITER(hh, _eventTriggers->m_pElements, pElement, tmp)
        {
            HASH_DEL(_eventTriggers->m_pElements, pElement);
            CCObject* pObj = NULL;
            CCARRAY_FOREACH(((CCArray*)pElement->getObject()), pObj)
            {
                TriggerObj* triobj = dynamic_cast<TriggerObj*>(pObj);
                if (triobj != NULL)
                {
                    triobj->removeAll();
                }
            }
            CC_SAFE_DELETE(pElement);
        }
    }
}

bool TriggerMng::remove(unsigned int event)
{
    bool bRet = false;
    CCAssert(event >= 0, "event must be larger than 0");
    do 
    {        
        CC_BREAK_IF(!_eventTriggers);
        CCObject* pRetObject = NULL;
        pRetObject = _eventTriggers->objectForKey(event);
        CC_BREAK_IF(!pRetObject);
        CCArray *array = dynamic_cast<CCArray*>(pRetObject);
        CC_BREAK_IF(!array);
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(array, pObj)
        {
            TriggerObj* triobj = dynamic_cast<TriggerObj*>(pObj);
            if (triobj != NULL)
            {
                triobj->removeAll();
            }
        }
        _eventTriggers->removeObjectForKey(event);
        bRet = true;
    } while(0);
    return bRet;
}


bool TriggerMng::isEmpty(void) const
{
    return (bool)(!(_eventTriggers && _eventTriggers->count()));
}

void TriggerMng::alloc(void)
{
    _eventTriggers = CCDictionary::create();
    _eventTriggers->retain();
}


NS_CC_EXT_END