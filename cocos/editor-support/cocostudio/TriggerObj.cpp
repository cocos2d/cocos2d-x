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

using namespace cocos2d;

namespace cocostudio {
    
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
:_id(UINT_MAX)
,_bEnable(true)
{
	_vInt.clear();
}

TriggerObj::~TriggerObj(void)
{
	_vInt.clear();
}

bool TriggerObj::init()
{
    return true;
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
	if (!_bEnable || _cons.size() == 0)
	{
		return true;
	}
    bool bRet = true;  

    for(auto con : _cons)
    {
        bRet = bRet && con->detect();
    }

    return bRet;
}

void TriggerObj::done()
{
	if (!_bEnable || _acts.size() == 0)
	{
		return;
	}

    for(auto act : _acts)
    {
        act->done();
    }
}

void TriggerObj::removeAll()
{
    for(auto con : _cons)
    {
        con->removeAll();
    }
    for(auto act : _acts)
    {
        act->removeAll();
    }
    
    _cons.clear();
    _acts.clear();
}

void TriggerObj::serialize(const rapidjson::Value &val)
{
	_id = (unsigned int)(DICTOOL->getIntValue_json(val, "id"));
    int count = DICTOOL->getArrayCount_json(val, "conditions");
    for (int i = 0; i < count; ++i)
    {
        const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "conditions", i);
        const char *classname = DICTOOL->getStringValue_json(subDict, "classname");
        if (classname == nullptr)
        {
            continue;
        }
        BaseTriggerCondition *con = dynamic_cast<BaseTriggerCondition*>(ObjectFactory::getInstance()->createObject(classname));
        CCAssert(con != nullptr, "class named classname can not implement!");
        con->serialize(subDict);
		con->init();
        con->autorelease();
        _cons.pushBack(con);
    }
    
	count = DICTOOL->getArrayCount_json(val, "actions");
	for (int i = 0; i < count; ++i)
	{
		const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(val, "actions", i);
		const char *classname = DICTOOL->getStringValue_json(subDict, "classname");
		if (classname == nullptr)
		{
			continue;
		}
		BaseTriggerAction *act = dynamic_cast<BaseTriggerAction*>(ObjectFactory::getInstance()->createObject(classname));
		CCAssert(act != nullptr, "class named classname can not implement!");
		act->serialize(subDict);
		act->init();
		act->autorelease();
		_acts.pushBack(act);
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
  
}
