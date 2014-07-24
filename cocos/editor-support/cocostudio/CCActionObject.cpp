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

#include "cocostudio/CCActionObject.h"
#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocoLoader.h"

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "2d/CCActionInstant.h"
#include "base/ccUtils.h"

using namespace cocos2d;

namespace cocostudio {

ActionObject::ActionObject()
: _name("")
, _loop(false)
, _bPause(false)
, _bPlaying(false)
, _fUnitTime(0.1f)
, _currentTime(0.0f)
, _pScheduler(nullptr)
, _CallBack(nullptr)
, _fTotalTime(0.0f)
{
    _pScheduler = Director::getInstance()->getScheduler();
    CC_SAFE_RETAIN(_pScheduler);
}

ActionObject::~ActionObject()
{
    _actionNodeList.clear();
    CC_SAFE_RELEASE(_pScheduler);
    CC_SAFE_RELEASE(_CallBack);
}

void ActionObject::setName(const char* name)
{
    _name.assign(name);
}
const char* ActionObject::getName()
{
    return _name.c_str();
}

void ActionObject::setLoop(bool bLoop)
{
    _loop = bLoop;
}
bool ActionObject::getLoop()
{
    return _loop;
}

void ActionObject::setUnitTime(float fTime)
{
    _fUnitTime = fTime;
    for(const auto &e : _actionNodeList)
    {
        e->setUnitTime(_fUnitTime);
    }
}
float ActionObject::getUnitTime()
{
    return _fUnitTime;
}

float ActionObject::getCurrentTime()
{
    return _currentTime;
}

void ActionObject::setCurrentTime(float fTime)
{
    _currentTime = fTime;
}

float ActionObject::getTotalTime()
{
    return _fTotalTime;
}
bool ActionObject::isPlaying()
{
    return _bPlaying;
}

void ActionObject::initWithDictionary(const rapidjson::Value& dic, Ref* root)
{
    setName(DICTOOL->getStringValue_json(dic, "name"));
    setLoop(DICTOOL->getBooleanValue_json(dic, "loop"));
    setUnitTime(DICTOOL->getFloatValue_json(dic, "unittime"));
    int actionNodeCount = DICTOOL->getArrayCount_json(dic, "actionnodelist");
    int maxLength = 0;
    for (int i=0; i<actionNodeCount; i++) {
        ActionNode* actionNode = new ActionNode();
        actionNode->autorelease();
        const rapidjson::Value& actionNodeDic = DICTOOL->getDictionaryFromArray_json(dic, "actionnodelist", i);
        actionNode->initWithDictionary(actionNodeDic,root);
        actionNode->setUnitTime(getUnitTime());
        _actionNodeList.pushBack(actionNode);
        
        int length = actionNode->getLastFrameIndex() - actionNode->getFirstFrameIndex();
        if(length > maxLength)
            maxLength = length;
    }
    _fTotalTime = maxLength*_fUnitTime;
}

void ActionObject::initWithBinary(CocoLoader *cocoLoader,
                                  stExpCocoNode *cocoNode,
                                  cocos2d::Ref *root)
{
    stExpCocoNode *stChildNode = cocoNode->GetChildArray(cocoLoader);
    stExpCocoNode *actionNodeList = nullptr;
    int count = cocoNode->GetChildNum();
    for (int i = 0; i < count; ++i) {
        std::string key = stChildNode[i].GetName(cocoLoader);
        std::string value = stChildNode[i].GetValue(cocoLoader);
        if (key == "name") {
            setName(value.c_str());
        }else if (key == "loop"){
            setLoop(valueToBool(value));
        }else if(key == "unittime"){
            setUnitTime(valueToFloat(value));
        }else if (key == "actionnodelist"){
            actionNodeList = &stChildNode[i];
        }
    }
    
    if(nullptr != actionNodeList)
    {
        int actionNodeCount = actionNodeList->GetChildNum();
        stExpCocoNode *actionNodeArray = actionNodeList->GetChildArray(cocoLoader);
        int maxLength = 0;
        for (int i=0; i<actionNodeCount; i++) {
            ActionNode* actionNode = new ActionNode();
            actionNode->autorelease();
            
            actionNode->initWithBinary(cocoLoader, &actionNodeArray[i] , root);
            
            actionNode->setUnitTime(getUnitTime());
            
            _actionNodeList.pushBack(actionNode);
            
            int length = actionNode->getLastFrameIndex() - actionNode->getFirstFrameIndex();
            if(length > maxLength)
                maxLength = length;
        }
        
        
        _fTotalTime = maxLength* _fUnitTime;
    }
}

int ActionObject::valueToInt(const std::string& value)
{
    return atoi(value.c_str());
}
bool ActionObject::valueToBool(const std::string& value)
{
    int intValue = valueToInt(value);
    if (1 == intValue) {
        return true;
    }else{
        return false;
    }
}
float ActionObject::valueToFloat(const std::string& value)
{
    return utils::atof(value.c_str());
}

void ActionObject::addActionNode(ActionNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    _actionNodeList.pushBack(node);
    node->setUnitTime(_fUnitTime);
}
void ActionObject::removeActionNode(ActionNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    _actionNodeList.eraseObject(node);
}

void ActionObject::play()
{
    stop();
    this->updateToFrameByTime(0.0f);
    for(const auto &e : _actionNodeList)
    {
        e->playAction();
    }
    if (_loop)
    {
        _pScheduler->schedule(schedule_selector(ActionObject::simulationActionUpdate), this, 0.0f , kRepeatForever, 0.0f, false);
    }
    else
    {
        _pScheduler->schedule(schedule_selector(ActionObject::simulationActionUpdate), this, 0.0f, false);
    }
}

void ActionObject::play(CallFunc* func)
{
    this->play();
	this->_CallBack = func;
	CC_SAFE_RETAIN(_CallBack);
}
void ActionObject::pause()
{
	_bPause = true;
}

void ActionObject::stop()
{
    for(const auto &e : _actionNodeList)
	{
		e->stopAction();
	}
	_pScheduler->unschedule(schedule_selector(ActionObject::simulationActionUpdate), this);
	_bPause = false;
}

void ActionObject::updateToFrameByTime(float fTime)
{
	_currentTime = fTime;
    for(const auto &e : _actionNodeList)
	{
		e->updateActionToTimeLine(fTime);
	}
}

void ActionObject::simulationActionUpdate(float dt)
{
	bool isEnd = true;
    
    for(const auto &e : _actionNodeList)
	{
		if (!e->isActionDoneOnce())
		{
			isEnd = false;
			break;
		}
	}
    
	if (isEnd)
	{
		if (_CallBack != nullptr)
		{
			_CallBack->execute();
		}
		if (_loop)
		{
			this->play();
		}
		else
		{
			_pScheduler->unschedule(schedule_selector(ActionObject::simulationActionUpdate), this);
		}
	}
}
}
