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

#include "CCActionObject.h"
#include "../Json/DictionaryHelper.h"

NS_CC_EXT_BEGIN

ActionObject::ActionObject()
: _actionNodeList(NULL)
, _name("")
, _loop(false)
, _bPause(false)
, _bPlaying(false)
, _fUnitTime(0.1f)
, _currentTime(0.0f)
{
	_actionNodeList = Array::create();
	_actionNodeList->retain();
}

ActionObject::~ActionObject()
{
	_actionNodeList->removeAllObjects();
	_actionNodeList->release();
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
	int nodeNum = _actionNodeList->count();
	for ( int i = 0; i < nodeNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)_actionNodeList->getObjectAtIndex(i);
		actionNode->setUnitTime(_fUnitTime);
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

bool ActionObject::isPlaying()
{
	return _bPlaying;
}

void ActionObject::initWithDictionary(cs::JsonDictionary *dic,Object* root)
{
    setName(DICTOOL->getStringValue_json(dic, "name"));
    setLoop(DICTOOL->getBooleanValue_json(dic, "loop"));
	setUnitTime(DICTOOL->getFloatValue_json(dic, "unittime"));
    int actionNodeCount = DICTOOL->getArrayCount_json(dic, "actionnodelist");
    for (int i=0; i<actionNodeCount; i++) {
        ActionNode* actionNode = new ActionNode();
		actionNode->autorelease();
        cs::JsonDictionary* actionNodeDic = DICTOOL->getDictionaryFromArray_json(dic, "actionnodelist", i);
        actionNode->initWithDictionary(actionNodeDic,root);
		actionNode->setUnitTime(getUnitTime());
        _actionNodeList->addObject(actionNode);
		CC_SAFE_DELETE(actionNodeDic);
    }
}

void ActionObject::addActionNode(ActionNode* node)
{
	if (node == NULL)
	{
		return;
	}
	_actionNodeList->addObject(node);
	node->setUnitTime(_fUnitTime);
}
void ActionObject::removeActionNode(ActionNode* node)
{
	if (node == NULL)
	{
		return;
	}
	_actionNodeList->removeObject(node);
}

void ActionObject::play()
{
    stop();
	int frameNum = _actionNodeList->count();
	for ( int i = 0; i < frameNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)_actionNodeList->getObjectAtIndex(i);
		actionNode->playAction( getLoop());
	}
}

void ActionObject::pause()
{
	_bPause = true;
}

void ActionObject::stop()
{
	int frameNum = _actionNodeList->count();

	for ( int i = 0; i < frameNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)_actionNodeList->getObjectAtIndex(i);
		actionNode->stopAction();
	}

	_bPause = false;
}

void ActionObject::updateToFrameByTime(float fTime)
{
	_currentTime = fTime;

	int nodeNum = _actionNodeList->count();

	for ( int i = 0; i < nodeNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)_actionNodeList->getObjectAtIndex(i);

		actionNode->updateActionToTimeLine(fTime);
	}
}

NS_CC_EXT_END