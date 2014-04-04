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

