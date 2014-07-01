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

#include "TriggerMng.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"

using namespace cocos2d;

namespace cocostudio {
    
TriggerMng* TriggerMng::_sharedTriggerMng = nullptr;

TriggerMng::TriggerMng(void)
: _movementDispatches(new std::unordered_map<Armature*, ArmatureMovementDispatcher*>)
{
    _eventDispatcher = Director::getInstance()->getEventDispatcher();
    _eventDispatcher->retain();
}

TriggerMng::~TriggerMng(void)
{
    removeAll();
	_triggerObjs.clear();

	removeAllArmatureMovementCallBack();
	CC_SAFE_DELETE(_movementDispatches);

    CC_SAFE_RELEASE(_eventDispatcher);
}

const char* TriggerMng::triggerMngVersion()
{
    return "1.0.0.0";
}

TriggerMng* TriggerMng::getInstance()
{
    if (nullptr == _sharedTriggerMng)
    {
        _sharedTriggerMng = new TriggerMng();
    }
    return _sharedTriggerMng;
}

void TriggerMng::destroyInstance()
{
    CC_SAFE_DELETE(_sharedTriggerMng);
}

void TriggerMng::parse(const rapidjson::Value &root)
{
    CCLOG("%s", triggerMngVersion());
    int count = DICTOOL->getArrayCount_json(root, "Triggers");
    
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol* engine = ScriptEngineManager::getInstance()->getScriptEngine();
    bool useBindings = engine != nullptr;

    if (useBindings)
    {
        if (count > 0)
        {
            const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(root, "Triggers");
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            subDict.Accept(writer);
            
            engine->parseConfig(ScriptEngineProtocol::ConfigType::COCOSTUDIO, buffer.GetString());
        }
    }
    else
#endif // #if CC_ENABLE_SCRIPT_BINDING
    {
        for (int i = 0; i < count; ++i)
        {
            const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(root, "Triggers", i);
            TriggerObj *obj = TriggerObj::create();
            obj->serialize(subDict);
            _triggerObjs.insert(std::pair<unsigned int, TriggerObj*>(obj->getId(), obj));
            obj->retain();
        }
    }
}
    
    
void TriggerMng::parse(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
    CCLOG("%s", triggerMngVersion());
    
    int count = pCocoNode[13].GetChildNum();
    stExpCocoNode *pTriggersArray = pCocoNode[13].GetChildArray();

#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol* engine = ScriptEngineManager::getInstance()->getScriptEngine();
    bool useBindings = engine != NULL;
    
    if (useBindings)
    {
        if (count > 0 )
        {
            rapidjson::Document document;
            buildJson(document, pCocoLoader, pCocoNode);
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            
            engine->parseConfig(ScriptEngineProtocol::ConfigType::COCOSTUDIO, buffer.GetString());
        }
    }
    else
#endif // #if CC_ENABLE_SCRIPT_BINDING
    {
        for (int i = 0; i < count; ++i)
        {
            TriggerObj *obj = TriggerObj::create();
            obj->serialize(pCocoLoader, &pTriggersArray[i]);
            _triggerObjs.insert(std::pair<unsigned int, TriggerObj*>(obj->getId(), obj));
            obj->retain();
        }
    }
}

TriggerObj* TriggerMng::getTriggerObj(unsigned int id) const
{
    auto iter = _triggerObjs.find(id);
    if (iter == _triggerObjs.end())
    {
        return nullptr;
    }
    return iter->second;
}

void TriggerMng::removeAll(void)
{
    auto etIter = _triggerObjs.begin();
    for (;etIter != _triggerObjs.end(); ++etIter)
    {
        etIter->second->removeAll();
        CC_SAFE_DELETE(etIter->second);
    }
    _triggerObjs.clear();
}

bool TriggerMng::removeTriggerObj(TriggerObj *Obj)
{
    if (Obj == nullptr)
    {
        return false;
    }
    return removeTriggerObj(Obj->getId());
}

bool TriggerMng::removeTriggerObj(unsigned int id)
{
	TriggerObj *obj = getTriggerObj(id);
	if (obj == nullptr)
	{
		return false;
	}
    obj->removeAll();
    _triggerObjs.erase(id);
	return true;
}

bool TriggerMng::isEmpty(void) const
{
    return _triggerObjs.empty();
}

    
    void TriggerMng::buildJson(rapidjson::Document &document, cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode)
{
    int count = pCocoNode[13].GetChildNum();
    int length = 0;
    int num = 0;
    int size = 0;
    int extent = 0;
    int border = 0;
    std::string key;
    stExpCocoNode *pTriggersArray = pCocoNode[13].GetChildArray();
    
    document.SetArray();
    
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    for (int i = 0; i < count; ++i)
    {
        rapidjson::Value vElemItem(rapidjson::kObjectType);
        
        border = pTriggersArray[i].GetChildNum();
        stExpCocoNode *pTriggerArray = pTriggersArray[i].GetChildArray();
        for (int i = 0; i < border; ++i)
        {
            std::string key = pTriggerArray[i].GetName(pCocoLoader);
            const char *str = pTriggerArray[i].GetValue();
            rapidjson::Type type = pTriggerArray[i].GetType(pCocoLoader);
            
            if (key.compare("actions") == 0)
            {
                rapidjson::Value actionsItem(rapidjson::kArrayType);
                
                length = pTriggerArray[i].GetChildNum();
                stExpCocoNode *pActionsArray = pTriggerArray[i].GetChildArray();
                for (int i = 0; i < length; ++i)
                {
                    rapidjson::Value action(rapidjson::kObjectType);
                    
                    num = pActionsArray[i].GetChildNum();
                    stExpCocoNode *pActionArray = pActionsArray[i].GetChildArray();
                    for (int i = 0; i < num; ++i)
                    {
                        std::string key = pActionArray[i].GetName(pCocoLoader);
                        const char *str = pActionArray[i].GetValue();
                        if (key.compare("classname") == 0)
                        {
                            if (str != NULL)
                            {
                                action.AddMember("classname", str, allocator);
                            }
                        }
                        else if (key.compare("dataitems") == 0)
                        {
                            rapidjson::Value dataitems(rapidjson::kArrayType);
                            size = pActionArray[i].GetChildNum();
                            stExpCocoNode *pDataItemsArray = pActionArray[i].GetChildArray();
                            for (int i = 0; i < size; ++i)
                            {
                                rapidjson::Value dataitem(rapidjson::kObjectType);
                                extent = pDataItemsArray[i].GetChildNum();
                                stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray();
                                for (int i = 0; i < extent; ++i)
                                {
                                    std::string key = pDataItemArray[i].GetName(pCocoLoader);
                                    const char *str = pDataItemArray[i].GetValue();
                                    if (key.compare("key") == 0)
                                    {
                                        if (str != NULL)
                                        {
                                            dataitem.AddMember("key", str, allocator);
                                        }
                                    }
                                    else
                                    {
                                        rapidjson::Type type = pDataItemArray[i].GetType(pCocoLoader);
                                        if (type == rapidjson::kStringType)
                                        {
                                            dataitem.AddMember("value", str, allocator);
                                        }
                                        else if(type == rapidjson::kNumberType)
                                        {
                                            int nV = atoi(str);
                                            float fV = atof(str);
                                            if (fabs(nV - fV) < 0.0000001)
                                            {
                                                dataitem.AddMember("value", nV, allocator);
                                            }
                                            else
                                            {
                                                dataitem.AddMember("value", fV, allocator);
                                            }
                                        }
                                    }
                                }
                                dataitems.PushBack(dataitem, allocator);
                            }
                            action.AddMember("dataitems", dataitems, allocator);
                        }
                    }
                    actionsItem.PushBack(action, allocator);
                }
                
                vElemItem.AddMember("actions", actionsItem, allocator);
            }
            else if (key.compare("conditions") == 0)
            {
                rapidjson::Value condsItem(rapidjson::kArrayType);
                
                length = pTriggerArray[i].GetChildNum();
                stExpCocoNode *pConditionsArray = pTriggerArray[i].GetChildArray();
                for (int i = 0; i < length; ++i)
                {
                    rapidjson::Value cond(rapidjson::kObjectType);
                    
                    num = pConditionsArray[i].GetChildNum();
                    stExpCocoNode *pConditionArray = pConditionsArray[i].GetChildArray();
                    for (int i = 0; i < num; ++i)
                    {
                        std::string key = pConditionArray[i].GetName(pCocoLoader);
                        const char *str = pConditionArray[i].GetValue();
                        if (key.compare("classname") == 0)
                        {
                            if (str != NULL)
                            {
                                cond.AddMember("classname", str, allocator);
                            }
                        }
                        else if (key.compare("dataitems") == 0)
                        {
                            rapidjson::Value dataitems(rapidjson::kArrayType);
                            size = pConditionArray[i].GetChildNum();
                            stExpCocoNode *pDataItemsArray = pConditionArray[i].GetChildArray();
                            for (int i = 0; i < size; ++i)
                            {
                                rapidjson::Value dataitem(rapidjson::kObjectType);
                                extent = pDataItemsArray[i].GetChildNum();
                                stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray();
                                for (int i = 0; i < extent; ++i)
                                {
                                    std::string key = pDataItemArray[i].GetName(pCocoLoader);
                                    const char *str = pDataItemArray[i].GetValue();
                                    if (key.compare("key") == 0)
                                    {
                                        if (str != NULL)
                                        {
                                            dataitem.AddMember("key", str, allocator);
                                        }
                                    }
                                    else
                                    {
                                        rapidjson::Type type = pDataItemArray[i].GetType(pCocoLoader);
                                        if (type == rapidjson::kStringType)
                                        {
                                            dataitem.AddMember("value", str, allocator);
                                        }
                                        else if(type == rapidjson::kNumberType)
                                        {
                                            int nV = atoi(str);
                                            float fV = atof(str);
                                            if (fabs(nV - fV) < 0.0000001)
                                            {
                                                dataitem.AddMember("value", nV, allocator);
                                            }
                                            else
                                            {
                                                dataitem.AddMember("value", fV, allocator);
                                            }
                                        }
                                    }
                                }
                                dataitems.PushBack(dataitem, allocator);
                            }
                            cond.AddMember("dataitems", dataitems, allocator);
                        }
                    }
                    condsItem.PushBack(cond, allocator);
                }
                
                vElemItem.AddMember("conditions", condsItem, allocator);
            }
            else if (key.compare("events") == 0)
            {
                rapidjson::Value eventsItem(rapidjson::kArrayType);
                
                length = pTriggerArray[i].GetChildNum();
                stExpCocoNode *pEventsArray = pTriggerArray[i].GetChildArray();
                for (int i = 0; i < length; ++i)
                {
                    rapidjson::Value event(rapidjson::kObjectType);
                    stExpCocoNode *pEventArray = pEventsArray->GetChildArray();
                    std::string key = pEventArray[0].GetName(pCocoLoader);
                    const char *str = pEventArray[0].GetValue();
                    if (key.compare("id") == 0 && str != NULL)
                    {
                        event.AddMember("id", atoi(str), allocator);
                        eventsItem.PushBack(event, allocator);
                    }
                }
                vElemItem.AddMember("events", eventsItem, allocator);
            }
            else if (key.compare("id") == 0)
            {
                if (str != NULL)
                {
                    vElemItem.AddMember("id", atoi(str), allocator);
                }
            }
        }
        document.PushBack(vElemItem, allocator);
    }
}

void TriggerMng::addArmatureMovementCallBack(Armature *pAr, Ref *pTarget, SEL_MovementEventCallFunc mecf)
{
	if (pAr == nullptr || _movementDispatches == nullptr || pTarget == nullptr || mecf == nullptr)
	{
		return;
	}

	auto iter = _movementDispatches->find(pAr);
	ArmatureMovementDispatcher *amd = nullptr;
	if (iter == _movementDispatches->end())
	{
		amd = new ArmatureMovementDispatcher();
        pAr->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(ArmatureMovementDispatcher::animationEvent, amd, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        amd->addAnimationEventCallBack(pTarget, mecf);
		_movementDispatches->insert(std::make_pair(pAr, amd));

	}
	else
	{
		amd = iter->second;
		amd->addAnimationEventCallBack(pTarget, mecf);
	}
}

void TriggerMng::removeArmatureMovementCallBack(Armature *pAr, Ref *pTarget, SEL_MovementEventCallFunc mecf)
{
	if (pAr == nullptr || _movementDispatches == nullptr || pTarget == nullptr || mecf == nullptr)
	{
		return;
	}
    
    auto iter =_movementDispatches->find(pAr);
	ArmatureMovementDispatcher *amd = nullptr;
	if (iter == _movementDispatches->end())
	{
		return;
	}
	else
	{
		amd = iter->second;
		amd->removeAnnimationEventCallBack(pTarget, mecf);
	}
}

void TriggerMng::removeArmatureAllMovementCallBack(Armature *pAr)
{
	if (pAr == nullptr)
	{
		return;
	}

	auto iter = _movementDispatches->find(pAr);
	if (iter == _movementDispatches->end())
	{
		return;
	}
	else
	{
		CC_SAFE_DELETE(iter->second);
		_movementDispatches->erase(iter);
	}
}

void TriggerMng::removeAllArmatureMovementCallBack()
{
	auto iter = _movementDispatches->begin();
	while (iter != _movementDispatches->end())
	{
		removeArmatureAllMovementCallBack(iter->first);
	}
	_movementDispatches->clear();
}

void TriggerMng::dispatchEvent(cocos2d::EventCustom* tEvent)
{
    _eventDispatcher->dispatchEvent(tEvent);
}

void TriggerMng::removeEventListener(cocos2d::EventListener* listener)
{
    _eventDispatcher->removeEventListener(listener);
}

void TriggerMng::addEventListenerWithFixedPriority(cocos2d::EventListener* listener, int fixedPriority)
{
    _eventDispatcher->addEventListenerWithFixedPriority(listener, fixedPriority);
}

ArmatureMovementDispatcher::ArmatureMovementDispatcher(void)
: _mapEventAnimation(nullptr)
{
	_mapEventAnimation = new std::unordered_map<Ref*, SEL_MovementEventCallFunc> ;
}

ArmatureMovementDispatcher::~ArmatureMovementDispatcher(void)
{
	_mapEventAnimation->clear();
	CC_SAFE_DELETE(_mapEventAnimation);
}

 void ArmatureMovementDispatcher::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
 {
	 for (auto iter = _mapEventAnimation->begin(); iter != _mapEventAnimation->end(); ++iter)
	 {
		   (iter->first->*iter->second)(armature, movementType, movementID);
	 }
 }

  void ArmatureMovementDispatcher::addAnimationEventCallBack(Ref *pTarget, SEL_MovementEventCallFunc mecf)
  {
	  _mapEventAnimation->insert(std::make_pair(pTarget, mecf));
  }

  void ArmatureMovementDispatcher::removeAnnimationEventCallBack(Ref *pTarget, SEL_MovementEventCallFunc mecf)
  {
	  _mapEventAnimation->erase(pTarget);
  }
  
}

