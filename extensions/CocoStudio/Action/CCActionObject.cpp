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
#include "../Json//DictionaryHelper.h"

NS_CC_EXT_BEGIN

ActionObject::ActionObject()
: m_ActionNodeList(NULL)
, m_name("")
, m_loop(false)
, m_bPause(false)
, m_bPlaying(false)
, m_fUnitTime(0.1f)
, m_CurrentTime(0.0f)
{
	m_ActionNodeList = CCArray::create();
	m_ActionNodeList->retain();
}

ActionObject::~ActionObject()
{
	m_ActionNodeList->removeAllObjects();
	m_ActionNodeList->release();
}

void ActionObject::setName(const char* name)
{
	m_name.assign(name);
}
const char* ActionObject::getName()
{
	return m_name.c_str();
}

void ActionObject::setLoop(bool bLoop)
{
	m_loop = bLoop;
}
bool ActionObject::getLoop()
{
	return m_loop;
}

void ActionObject::setUnitTime(float fTime)
{
	m_fUnitTime = fTime;
	int frameNum = m_ActionNodeList->count();
	for ( int i = 0; i < frameNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)m_ActionNodeList->objectAtIndex(i);
		actionNode->setUnitTime(m_fUnitTime);
	}
}
float ActionObject::getUnitTime()
{
	return m_fUnitTime;
}

float ActionObject::getCurrentTime()
{
	return m_CurrentTime;
}

void ActionObject::setCurrentTime(float fTime)
{
	m_CurrentTime = fTime;
}

bool ActionObject::isPlaying()
{
	return m_bPlaying;
}

void ActionObject::initWithDictionary(cs::CSJsonDictionary *dic,CCObject* root)
{
    setName(DICTOOL->getStringValue_json(dic, "name"));
    setLoop(DICTOOL->getBooleanValue_json(dic, "loop"));
	setUnitTime(DICTOOL->getFloatValue_json(dic, "unittime"));
    int actionNodeCount = DICTOOL->getArrayCount_json(dic, "actionnodelist");
    for (int i=0; i<actionNodeCount; i++) {
        ActionNode* actionNode = new ActionNode();
		actionNode->autorelease();
        cs::CSJsonDictionary* actionNodeDic = DICTOOL->getDictionaryFromArray_json(dic, "actionnodelist", i);
        actionNode->initWithDictionary(actionNodeDic,root);
		actionNode->setUnitTime(getUnitTime());
        m_ActionNodeList->addObject(actionNode);
		CC_SAFE_DELETE(actionNodeDic);
    }
}

void ActionObject::addActionNode(ActionNode* node)
{
	if (node == NULL)
	{
		return;
	}
	m_ActionNodeList->addObject(node);
	node->setUnitTime(m_fUnitTime);
}
void ActionObject::removeActionNode(ActionNode* node)
{
	if (node == NULL)
	{
		return;
	}
	m_ActionNodeList->removeObject(node);
}

void ActionObject::play()
{
    stop();
	int frameNum = m_ActionNodeList->count();
	for ( int i = 0; i < frameNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)m_ActionNodeList->objectAtIndex(i);
		actionNode->playAction( getLoop());
	}
}

void ActionObject::pause()
{
	m_bPause = true;
}

void ActionObject::stop()
{
	int frameNum = m_ActionNodeList->count();

	for ( int i = 0; i < frameNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)m_ActionNodeList->objectAtIndex(i);
		actionNode->stopAction();
	}

	m_bPause = false;
}

void ActionObject::updateToFrameByTime(float fTime)
{
	m_CurrentTime = fTime;

	int nodeNum = m_ActionNodeList->count();

	for ( int i = 0; i < nodeNum; i++ )
	{
		ActionNode* actionNode = (ActionNode*)m_ActionNodeList->objectAtIndex(i);

		actionNode->updateActionToTimeLine(fTime);
	}
}

NS_CC_EXT_END