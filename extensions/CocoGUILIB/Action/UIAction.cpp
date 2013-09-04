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

#include "UIAction.h"
#include "UIActionNode.h"
#include "../../CocostudioReader/DictionaryHelper.h"


NS_CC_EXT_BEGIN

UIAction::UIAction()
{
	m_ActionNodeList = CCArray::create();
	m_ActionNodeList->retain();
}

UIAction::~UIAction()
{
	m_ActionNodeList->removeAllObjects();
	m_ActionNodeList->release();
}

void UIAction::initWithDictionary(cs::CSJsonDictionary *dic,UIWidget* root)
{
    setName(DICTOOL->getStringValue_json(dic, "name"));
    setLoop(DICTOOL->getBooleanValue_json(dic, "loop"));
    setUnitTime(DICTOOL->getFloatValue_json(dic, "unittime"));
    int actionNodeCount = DICTOOL->getArrayCount_json(dic, "actionnodelist");
    for (int i=0; i<actionNodeCount; i++)
    {
        UIActionNode* actionNode = new UIActionNode();
        actionNode->autorelease();
        cs::CSJsonDictionary* actionNodeDic = DICTOOL->getDictionaryFromArray_json(dic, "actionnodelist", i);
        actionNode->initWithDictionary(actionNodeDic,root);
        m_ActionNodeList->addObject(actionNode);
		CC_SAFE_DELETE(actionNodeDic);
    }
}

void UIAction::Play()
{
    Stop();
	int frameNum = m_ActionNodeList->count();
	for ( int i = 0; i < frameNum; i++ )
	{
		UIActionNode* actionNode = (UIActionNode*)m_ActionNodeList->objectAtIndex(i);
		actionNode->RunAction( getUnitTime(),getLoop() );
	}
}

void UIAction::Pause()
{

}

void UIAction::Stop()
{
	int frameNum = m_ActionNodeList->count();

	for ( int i = 0; i < frameNum; i++ )
	{
		UIActionNode* actionNode = (UIActionNode*)m_ActionNodeList->objectAtIndex(i);
		actionNode->StopAction();
	}
}

void UIAction::UpdateToFrameByIndex(int index)
{
	int frameNum = m_ActionNodeList->count();

	for ( int i = 0; i < frameNum; i++ )
	{
		UIActionNode* actionNode = (UIActionNode*)m_ActionNodeList->objectAtIndex(i);

		actionNode->UpdateToFrameByIndex(index);
	}
}

void UIAction::setName(const char* name)
{
    m_name = name;
}

const char* UIAction::getName() const
{
    return m_name.c_str();
}

NS_CC_EXT_END