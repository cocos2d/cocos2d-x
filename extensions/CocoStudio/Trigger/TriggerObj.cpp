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

#include "TriggerObj.h"
#include "ObjectFactory.h"

NS_CC_EXT_BEGIN

BaseTriggerCondition::BaseTriggerCondition(void)
{
}

BaseTriggerCondition::~BaseTriggerCondition(void)
{
}

bool BaseTriggerCondition::init()
{
    return true;
}

bool BaseTriggerCondition::detect()
{
    return true;
}

void BaseTriggerCondition::serialize(const rapidjson::Value &val)
{
}

void BaseTriggerCondition::removeAll()
{
}

BaseTriggerAction::BaseTriggerAction(void)
{
}

BaseTriggerAction::~BaseTriggerAction(void)
{
}

bool BaseTriggerAction::init()
{
    return true;
}

void BaseTriggerAction::done()
{

}

void BaseTriggerAction::serialize(const rapidjson::Value &val)
{
}

void BaseTriggerAction::removeAll()
{
}

TriggerObj::TriggerObj(void)
:_cons(NULL)
,_acts(NULL)
,_id(UINT_MAX)
,_bEnable(true)
{
	_vInt.clear();
}

TriggerObj::~TriggerObj(void)
{
	_vInt.clear();
    CC_SAFE_RELEASE_NULL(_cons);
    CC_SAFE_RELEASE_NULL(_acts);
}

bool TriggerObj::init()
{
    bool bRet = false;
    do {
         _cons = CCArray::create();
         _acts = CCArray::create();
         CC_BREAK_IF(_cons == NULL || _acts == NULL);
         _cons->retain();
         _acts->retain();
         bRet = true;
    } while (0);
    return bRet;
}

TriggerObj* TriggerObj::create()
{
    TriggerObj * pRet = new TriggerObj();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool TriggerObj::detect()
{
	if (!_bEnable || _cons == NULL || _cons->count() == 0)
	{
		return true;
	}
    bool bRet = false;  
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_cons, pObj)
    {
        BaseTriggerCondition* con = (BaseTriggerCondition*)pObj;
        bRet = bRet || con->detect();
    }

    return bRet;
}

void TriggerObj::done()
{
	if (!_bEnable || _acts == NULL || _acts->count() == 0)
	{
		return;
	}

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_acts, pObj)
    {
        BaseTriggerAction *act = (BaseTriggerAction*)pObj;
        act->done();
    }
}

void TriggerObj::removeAll()
{
    CCObject* pObj = NULL;
    if (_cons != NULL)
    {
        CCARRAY_FOREACH(_cons, pObj)
        {
            BaseTriggerCondition* con = (BaseTriggerCondition*)pObj;
            con->removeAll();
        }
        _cons->removeAllObjects();
    }
    if (_acts != NULL)
    {
        CCARRAY_FOREACH(_acts, pObj)
        {
            BaseTriggerAction* act = (BaseTriggerAction*)pObj;
            act->removeAll();
        }
        _acts->removeAllObjects();
    }
}

void TriggerObj::serialize(const rapidjson::Value &val)
{
	_id = (unsigned int)(DICTOOL->getIntValue_json(val, "id"));
    int count = DICTOOL->getArrayCount_json(val, "conditions");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "conditions", i);
        const char *classname = DICTOOL->getStringValue_json(subDict, "classname");
        if (classname == NULL)
        {
            continue;
        }
        BaseTriggerCondition *con = dynamic_cast<BaseTriggerCondition*>(ObjectFactory::getInstance()->createObject(classname));
        CCAssert(con != NULL, "class named classname can not implement!");
        con->serialize(subDict);
		con->init();
        con->autorelease();
        _cons->addObject(con);
    }
    
	count = DICTOOL->getArrayCount_json(val, "actions");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "actions", i);
		const char *classname = DICTOOL->getStringValue_json(subDict, "classname");
		if (classname == NULL)
		{
			continue;
		}
		BaseTriggerAction *act = dynamic_cast<BaseTriggerAction*>(ObjectFactory::getInstance()->createObject(classname));
		CCAssert(act != NULL, "class named classname can not implement!");
		act->serialize(subDict);
		act->init();
		act->autorelease();
		_acts->addObject(act);
	}

	int length = DICTOOL->getArrayCount_json(val, "events");
	for (int i = 0; i < length; ++i)
	{
		const rapidjson::Value &sub = DICTOOL->getSubDictionary_json(val, "events", i);
		int event = DICTOOL->getIntValue_json(sub, "id");
		if (event < 0)
		{
			continue;
		}
		_vInt.push_back(event);
	}  
}

unsigned int TriggerObj::getId()
{
	return _id;
}

void TriggerObj::setEnable(bool bEnable)
{
	_bEnable = bEnable;
}

std::vector<int>& TriggerObj::getEvents()
{
	return _vInt;
}

NS_CC_EXT_END