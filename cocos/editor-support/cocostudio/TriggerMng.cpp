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

using namespace cocos2d;

namespace cocostudio {
    
TriggerMng* TriggerMng::_sharedTriggerMng = NULL;

TriggerMng::TriggerMng(void)
    : _movementDispatches(NULL)
{
	_movementDispatches = new std::map<Armature*, ArmatureMovementDispatcher*>;
}

TriggerMng::~TriggerMng(void)
{
    _eventTriggers.clear();
	_triggerObjs.clear();

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
    do {
          int count = DICTOOL->getArrayCount_json(root, "Triggers");
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
				
                _triggerObjs.insert(std::pair<unsigned int, TriggerObj*>(obj->getId(), obj));
          }
        
    } while (0);
}

cocos2d::Vector<TriggerObj*> TriggerMng::get(unsigned int event) const
{
    CCAssert(event >= 0, "Argument must be larger than 0");
    
    return _eventTriggers.at(event);
}

TriggerObj* TriggerMng::getTriggerObj(unsigned int id) const
{
	return _triggerObjs.at(id);
}

bool TriggerMng::add(unsigned int event, TriggerObj *pObj)
{
    bool bRet = false;
    CCAssert(pObj != NULL, "Argument must be non-nil");
    do
    {
        auto iterator = _eventTriggers.find(event);
        if (iterator == _eventTriggers.end())
        {
            _eventTriggers.insert(std::pair<unsigned int, cocos2d::Vector<TriggerObj*>>(event, cocos2d::Vector<TriggerObj*>()));
            iterator = _eventTriggers.find(event);
        }
        else
        {
            Vector<TriggerObj*>& temp = iterator->second;
            if(temp.find(pObj) == temp.end())
            {
                temp.pushBack(pObj);
            }
        }
        bRet = true;
    } while(0);
    return bRet;
}

void TriggerMng::removeAll(void)
{
    for(auto temp : _eventTriggers)
    {
        for(auto obj : temp.second)
        {
            obj->removeAll();
        }
    }
    
    _eventTriggers.clear();
}

bool TriggerMng::remove(unsigned int event)
{
    bool bRet = false;
    CCAssert(event >= 0, "event must be larger than 0");
    do 
    {
        auto iterator = _eventTriggers.find(event);
        if(iterator != _eventTriggers.end())
        {
            for(auto obj : iterator->second)
            {
                obj->removeAll();
            }
        }
        
        _eventTriggers.erase(event);
        
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
        auto iterator = _eventTriggers.find(event);
        if(iterator != _eventTriggers.end())
        {
            for(auto triobj : iterator->second)
            {
                if (triobj != NULL && triobj == Obj)
                {
                    triobj->removeAll();
                    break;
                }
            }
            
            iterator->second.eraseObject(Obj);
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
	return true;
}

bool TriggerMng::isEmpty(void) const
{
    return _eventTriggers.empty();
}

void TriggerMng::addArmatureMovementCallBack(Armature *pAr, Object *pTarget, SEL_MovementEventCallFunc mecf)
{
	if (pAr == NULL || _movementDispatches == NULL || pTarget == NULL || mecf == NULL)
	{
		return;
	}

	std::map<Armature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->find(pAr);
	ArmatureMovementDispatcher *amd = NULL;
	if (iter == _movementDispatches->end())
	{
		amd = new ArmatureMovementDispatcher();
		pAr->getAnimation()->setMovementEventCallFunc(amd, movementEvent_selector(ArmatureMovementDispatcher::animationEvent));
		amd->addAnnimationEventCallBack(pTarget, mecf);
		_movementDispatches->insert(std::map<Armature*, ArmatureMovementDispatcher*>::value_type(pAr, amd));
	}
	else
	{
		amd = iter->second;
		amd->addAnnimationEventCallBack(pTarget, mecf);
	}
}

void TriggerMng::removeArmatureMovementCallBack(Armature *pAr, Object *pTarget, SEL_MovementEventCallFunc mecf)
{
	if (pAr == NULL || _movementDispatches == NULL || pTarget == NULL || mecf == NULL)
	{
		return;
	}

	std::map<Armature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->find(pAr);
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

void TriggerMng::removeArmatureAllMovementCallBack(Armature *pAr)
{
	if (pAr == NULL)
	{
		return;
	}

	std::map<Armature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->find(pAr);
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
	std::map<Armature*, ArmatureMovementDispatcher*>::iterator iter = _movementDispatches->begin();
	while (iter != _movementDispatches->end())
	{
		removeArmatureAllMovementCallBack(iter->first);
	}
	_movementDispatches->clear();
}

ArmatureMovementDispatcher::ArmatureMovementDispatcher(void)
: _mapEventAnimation(NULL)
{
	_mapEventAnimation = new std::map<Object*, SEL_MovementEventCallFunc> ;
}

ArmatureMovementDispatcher::~ArmatureMovementDispatcher(void)
{
	_mapEventAnimation->clear();
	CC_SAFE_DELETE(_mapEventAnimation);
}

 void ArmatureMovementDispatcher::animationEvent(Armature *armature, MovementEventType movementType, const char *movementID)
 {
	 for (std::map<Object*, SEL_MovementEventCallFunc> ::iterator iter = _mapEventAnimation->begin(); iter != _mapEventAnimation->end(); ++iter)
	 {
		   (iter->first->*iter->second)(armature, movementType, movementID);
	 }
 }

  void ArmatureMovementDispatcher::addAnnimationEventCallBack(Object *pTarget, SEL_MovementEventCallFunc mecf)
  {
	  _mapEventAnimation->insert(std::map<Object*, SEL_MovementEventCallFunc>::value_type(pTarget, mecf));
  }

  void ArmatureMovementDispatcher::removeAnnimationEventCallBack(Object *pTarget, SEL_MovementEventCallFunc mecf)
  {
	  _mapEventAnimation->erase(pTarget);
  }
  
}

