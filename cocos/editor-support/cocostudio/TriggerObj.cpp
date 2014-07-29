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
    
void BaseTriggerCondition::serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode)
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

void BaseTriggerAction::serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode)
{
}

void BaseTriggerAction::removeAll()
{
}

TriggerObj::TriggerObj(void)
:_id(UINT_MAX)
,_enabled(true)
{
}

TriggerObj::~TriggerObj(void)
{
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
    if (!_enabled || _cons.empty())
    {
        return true;
    }
    
    bool ret = false;

    for (const auto& con : _cons)
    {
        ret = ret || con->detect();
    }

    return ret;
}

void TriggerObj::done()
{
    if (!_enabled || _acts.empty())
    {
        return;
    }

    for (const auto& act : _acts)
    {
        act->done();
    }
}

void TriggerObj::removeAll()
{
    for (const auto& con : _cons)
    {
        con->removeAll();
    }
    
    for (const auto& act : _acts)
    {
        act->removeAll();
    }

    for (const auto& lis : _listeners)
    {
        TriggerMng::getInstance()->removeEventListener(lis);
    }
    
    _cons.clear();
    _acts.clear();
    _listeners.clear();
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
        if(con == nullptr)
        {
            CCLOG("class %s can not be implemented!", classname);
            CCASSERT(con != nullptr, "");
        }
        
        CCASSERT(con != nullptr, "");
        con->serialize(subDict);
        con->init();
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
        if(act == nullptr)
        {
            CCLOG("class %s can not be implemented!", classname);
            CCASSERT(act != nullptr, "");
        }
        act->serialize(subDict);
        act->init();
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

        char* buf = new char[10];
        sprintf(buf, "%d", event);
        std::string custom_event_name(buf);
        CC_SAFE_DELETE_ARRAY(buf);

        EventListenerCustom* listener = EventListenerCustom::create(custom_event_name, [=](EventCustom* evt){
            if (detect())
            {
                done();
            }
        });
        _listeners.pushBack(listener);
        TriggerMng::getInstance()->addEventListenerWithFixedPriority(listener, 1);
    }  
}

    
void TriggerObj::serialize(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
    int length = pCocoNode->GetChildNum();
    int count = 0;
    int num = 0;
    stExpCocoNode *pTriggerObjArray = pCocoNode->GetChildArray(pCocoLoader);
    for (int i0 = 0; i0 < length; ++i0)
    {
        std::string key = pTriggerObjArray[i0].GetName(pCocoLoader);
        const char* str0 = pTriggerObjArray[i0].GetValue(pCocoLoader);
        if (key.compare("id") == 0)
        {
            if (str0 != nullptr)
            {
                _id = atoi(str0); 
            }
        }
        else if (key.compare("conditions") == 0)
        {
            count = pTriggerObjArray[i0].GetChildNum();
            stExpCocoNode *pConditionsArray = pTriggerObjArray[i0].GetChildArray(pCocoLoader);
            for (int i1 = 0; i1 < count; ++i1)
            {
                num = pConditionsArray[i1].GetChildNum();
                stExpCocoNode *pConditionArray = pConditionsArray[i1].GetChildArray(pCocoLoader);
                const char *classname = pConditionArray[0].GetValue(pCocoLoader);
                if (classname == nullptr)
                {
                    continue;
                }
                BaseTriggerCondition *con = dynamic_cast<BaseTriggerCondition*>(ObjectFactory::getInstance()->createObject(classname));
                CCAssert(con != nullptr, "class named classname can not implement!");
                con->serialize(pCocoLoader, &pConditionArray[1]);
                con->init();
                _cons.pushBack(con);
            }
        }
        else if (key.compare("actions") == 0)
        {
            count = pTriggerObjArray[i0].GetChildNum();
            stExpCocoNode *pActionsArray = pTriggerObjArray[i0].GetChildArray(pCocoLoader);
            for (int i2 = 0; i2 < count; ++i2)
            {
                num = pActionsArray[i2].GetChildNum();
                stExpCocoNode *pActionArray = pActionsArray[i2].GetChildArray(pCocoLoader);
                const char *classname = pActionArray[0].GetValue(pCocoLoader);
                if (classname == nullptr)
                {
                    continue;
                }
                BaseTriggerAction *act = dynamic_cast<BaseTriggerAction*>(ObjectFactory::getInstance()->createObject(classname));
                CCAssert(act != nullptr, "class named classname can not implement!");
                act->serialize(pCocoLoader, &pActionArray[1]);
                act->init();
                _acts.pushBack(act);
            }
        }
        else if (key.compare("events") == 0)
        {
            count = pTriggerObjArray[i0].GetChildNum();
            stExpCocoNode *pEventsArray = pTriggerObjArray[i0].GetChildArray(pCocoLoader);
            for (int i3 = 0; i3 < count; ++i3)
            {
                num = pEventsArray[i3].GetChildNum();
                stExpCocoNode *pEventArray = pEventsArray[i3].GetChildArray(pCocoLoader);
                const char *str1 = pEventArray[0].GetValue(pCocoLoader);
                if (str1 == nullptr)
                {
                    continue;
                }
                int event = atoi(str1);
                if (event < 0)
                {
                    continue;
                }
                char* buf = new char[10];
                sprintf(buf, "%d", event);
                std::string custom_event_name(buf);
                CC_SAFE_DELETE_ARRAY(buf);
                
                EventListenerCustom* listener = EventListenerCustom::create(custom_event_name, [=](EventCustom* evt){
                    if (detect())
                    {
                        done();
                    }
                });
                _listeners.pushBack(listener);
                TriggerMng::getInstance()->addEventListenerWithFixedPriority(listener, 1);
            }
        }
    }
}
    


unsigned int TriggerObj::getId()
{
    return _id;
}

void TriggerObj::setEnabled(bool enabled)
{
    _enabled = enabled;
}
  
}
