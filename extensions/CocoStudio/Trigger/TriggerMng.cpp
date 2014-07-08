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

#include "TriggerBase.h"
#include "../Json/rapidjson/prettywriter.h"
#include "../Json/rapidjson/filestream.h"
#include "../Json/rapidjson/stringbuffer.h"

NS_CC_EXT_BEGIN

TriggerMng* TriggerMng::_sharedTriggerMng = NULL;

TriggerMng::TriggerMng(void)
: _eventTriggers(NULL)
,_triggerObjs(NULL)
,_movementDispatches(NULL)
{
	_triggerObjs = CCDictionary::create();
	_triggerObjs->retain();
	_movementDispatches = new std::map<CCArmature*, ArmatureMovementDispatcher*>;
}

TriggerMng::~TriggerMng(void)
{
    removeAll();
    CC_SAFE_DELETE(_eventTriggers);
	CC_SAFE_RELEASE_NULL(_triggerObjs);

	removeAllArmatureMovementCallBack();
	CC_SAFE_DELETE(_movementDispatches);
}

const char* TriggerMng::triggerMngVersion()
{
    return "1.0.0.0";
}

TriggerMng* TriggerMng::getInstance()
{
    if (NULL == _sharedTriggerMng)
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
    
    CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    bool useBindings = engine != NULL;    
    
    if (useBindings)
    {
        if (count > 0 )
        {
            const rapidjson::Value& subDict = DICTOOL->getSubDictionary_json(root, "Triggers");
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            subDict.Accept(writer);
            
            engine->parseConfig(CCScriptEngineProtocol::COCOSTUDIO, buffer.GetString());
        }
    }
    else
    {
        for (int i = 0; i < count; ++i)
        {
            const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(root, "Triggers", i);
            TriggerObj *obj = TriggerObj::create();
            obj->serialize(subDict);
            std::vector<int> &_vInt = obj->getEvents();
            for (std::vector<int>::iterator iter = _vInt.begin(); iter != _vInt.end(); ++iter)
            {
                add((unsigned int)(*iter), obj);
            }
            if (_triggerObjs != NULL)
            {
                _triggerObjs->setObject(obj, obj->getId());
            }
        }
    }
}

void TriggerMng::parse(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	CCLOG("%s", triggerMngVersion());

	int count = pCocoNode[13].GetChildNum();
	stExpCocoNode *pTriggersArray = pCocoNode[13].GetChildArray(pCocoLoader);

	CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
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

			engine->parseConfig(CCScriptEngineProtocol::COCOSTUDIO, buffer.GetString());
		}
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			TriggerObj *obj = TriggerObj::create();
			obj->serialize(pCocoLoader, &pTriggersArray[i]);
			std::vector<int> &_vInt = obj->getEvents();
			for (std::vector<int>::iterator iter = _vInt.begin(); iter != _vInt.end(); ++iter)
			{
				add((unsigned int)(*iter), obj);
			}
			if (_triggerObjs != NULL)
			{
				_triggerObjs->setObject(obj, obj->getId());
			}
		}
	}
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

TriggerObj* TriggerMng::getTriggerObj(unsigned int id) const
{
	if (_triggerObjs == NULL)
	{
		return NULL;
	}
	TriggerObj *obj = dynamic_cast<TriggerObj *>(_triggerObjs->objectForKey(id));

	return obj;
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
            CC_SAFE_RELEASE(pElement->getObject());
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

bool TriggerMng::remove(unsigned int event, TriggerObj *Obj)
{
	bool bRet = false;
	CCAssert(event >= 0, "event must be larger than 0");
	CCAssert(Obj != 0, "TriggerObj must be not 0");
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
			if (triobj != NULL && triobj == Obj)
			{
				triobj->removeAll();
			}
			array->removeObject(triobj);
			break;
		}
		bRet = true;
	} while(0);
	return bRet;
}

bool TriggerMng::removeTriggerObj(unsigned int id)
{
	TriggerObj *obj = getTriggerObj(id);
	if (obj == NULL)
	{
		return false;
	}
	std::vector<int> &_vInt = obj->getEvents();
	for (std::vector<int>::iterator iter = _vInt.begin(); iter != _vInt.end(); ++iter)
	{
		remove(*iter, obj);
	}
    _triggerObjs->removeObjectForKey(id);
	return true;
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

void TriggerMng::buildJson(rapidjson::Document &document, cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode)
{
	int count = pCocoNode[13].GetChildNum();
	int length = 0;
	int num = 0;
	int size = 0;
	int extent = 0;
	int border = 0;
	std::string key;
	const char *str = NULL;
	stExpCocoNode *pTriggersArray = pCocoNode[13].GetChildArray(pCocoLoader);

	document.SetArray();

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator(); 
	for (int i = 0; i < count; ++i)
	{
		rapidjson::Value vElemItem(rapidjson::kObjectType);

		border = pTriggersArray[i].GetChildNum();
		stExpCocoNode *pTriggerArray = pTriggersArray[i].GetChildArray(pCocoLoader);
		for (int i = 0; i < border; ++i)
		{
			std::string key = pTriggerArray[i].GetName(pCocoLoader);
			const char *str = pTriggerArray[i].GetValue(pCocoLoader);
			rapidjson::Type type = pTriggerArray[i].GetType(pCocoLoader);

			if (key.compare("actions") == 0)
			{
				rapidjson::Value actionsItem(rapidjson::kArrayType);

				length = pTriggerArray[i].GetChildNum();
				stExpCocoNode *pActionsArray = pTriggerArray[i].GetChildArray(pCocoLoader);
				for (int i = 0; i < length; ++i)
				{
					rapidjson::Value action(rapidjson::kObjectType);

					num = pActionsArray[i].GetChildNum();
					stExpCocoNode *pActionArray = pActionsArray[i].GetChildArray(pCocoLoader);
					for (int i = 0; i < num; ++i)
					{
						std::string key = pActionArray[i].GetName(pCocoLoader);
						const char *str = pActionArray[i].GetValue(pCocoLoader);
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
							stExpCocoNode *pDataItemsArray = pActionArray[i].GetChildArray(pCocoLoader);
							for (int i = 0; i < size; ++i)
							{
								rapidjson::Value dataitem(rapidjson::kObjectType);
								extent = pDataItemsArray[i].GetChildNum();
								stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
								for (int i = 0; i < extent; ++i)
								{
									std::string key = pDataItemArray[i].GetName(pCocoLoader);
									const char *str = pDataItemArray[i].GetValue(pCocoLoader);
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
				stExpCocoNode *pConditionsArray = pTriggerArray[i].GetChildArray(pCocoLoader);
				for (int i = 0; i < length; ++i)
				{
					rapidjson::Value cond(rapidjson::kObjectType);

					num = pConditionsArray[i].GetChildNum();
					stExpCocoNode *pConditionArray = pConditionsArray[i].GetChildArray(pCocoLoader);
					for (int i = 0; i < num; ++i)
					{
						std::string key = pConditionArray[i].GetName(pCocoLoader);
						const char *str = pConditionArray[i].GetValue(pCocoLoader);
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
							stExpCocoNode *pDataItemsArray = pConditionArray[i].GetChildArray(pCocoLoader);
							for (int i = 0; i < size; ++i)
							{
								rapidjson::Value dataitem(rapidjson::kObjectType);
								extent = pDataItemsArray[i].GetChildNum();
								stExpCocoNode *pDataItemArray = pDataItemsArray[i].GetChildArray(pCocoLoader);
								for (int i = 0; i < extent; ++i)
								{
									std::string key = pDataItemArray[i].GetName(pCocoLoader);
									const char *str = pDataItemArray[i].GetValue(pCocoLoader);
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
				stExpCocoNode *pEventsArray = pTriggerArray[i].GetChildArray(pCocoLoader);
				for (int i = 0; i < length; ++i)
				{
					rapidjson::Value event(rapidjson::kObjectType);
					stExpCocoNode *pEventArray = pEventsArray->GetChildArray(pCocoLoader);
					std::string key = pEventArray[0].GetName(pCocoLoader);
					const char *str = pEventArray[0].GetValue(pCocoLoader);
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

void TriggerMng::addArmatureMovementCallBack(CCArmature *pAr, CCObject *pTarget, SEL_MovementEventCallFunc mecf)
{
	if (pAr == NULL || _movementDispatches == NULL || pTarget == NULL || mecf == NULL)
	{
		return;
	}

	std::map<CCArmature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->find(pAr);
	ArmatureMovementDispatcher *amd = NULL;
	if (iter == _movementDispatches->end())
	{
		amd = new ArmatureMovementDispatcher();
		pAr->getAnimation()->setMovementEventCallFunc(amd, movementEvent_selector(ArmatureMovementDispatcher::animationEvent));
		amd->addAnimationEventCallBack(pTarget, mecf);
		_movementDispatches->insert(std::map<CCArmature*, ArmatureMovementDispatcher*>::value_type(pAr, amd));
	}
	else
	{
		amd = iter->second;
		amd->addAnimationEventCallBack(pTarget, mecf);
	}
}

void TriggerMng::removeArmatureMovementCallBack(CCArmature *pAr, CCObject *pTarget, SEL_MovementEventCallFunc mecf)
{
	if (pAr == NULL || _movementDispatches == NULL || pTarget == NULL || mecf == NULL)
	{
		return;
	}

	std::map<CCArmature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->find(pAr);
	ArmatureMovementDispatcher *amd = NULL;
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

void TriggerMng::removeArmatureAllMovementCallBack(CCArmature *pAr)
{
	if (pAr == NULL)
	{
		return;
	}

	std::map<CCArmature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->find(pAr);
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
	std::map<CCArmature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->begin();
	while (iter != _movementDispatches->end())
	{
		removeArmatureAllMovementCallBack(iter->first);
        ++iter;
	}
	_movementDispatches->clear();
}

ArmatureMovementDispatcher::ArmatureMovementDispatcher(void)
: _mapEventAnimation(NULL)
{
	_mapEventAnimation = new std::map<CCObject*, SEL_MovementEventCallFunc> ;
}

ArmatureMovementDispatcher::~ArmatureMovementDispatcher(void)
{
	_mapEventAnimation->clear();
	CC_SAFE_DELETE(_mapEventAnimation);
}

 void ArmatureMovementDispatcher::animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID)
 {
	 for (std::map<CCObject*, SEL_MovementEventCallFunc> ::iterator iter = _mapEventAnimation->begin(); iter != _mapEventAnimation->end(); ++iter)
	 {
		   (iter->first->*iter->second)(armature, movementType, movementID);
	 }
 }

  void ArmatureMovementDispatcher::addAnimationEventCallBack(CCObject *pTarget, SEL_MovementEventCallFunc mecf)
  {
	  _mapEventAnimation->insert(std::map<CCObject*, SEL_MovementEventCallFunc>::value_type(pTarget, mecf));
  }

  void ArmatureMovementDispatcher::removeAnnimationEventCallBack(CCObject *pTarget, SEL_MovementEventCallFunc mecf)
  {
	  _mapEventAnimation->erase(pTarget);
  }


NS_CC_EXT_END