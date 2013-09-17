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

#include "UIActionNode.h"
#include "UIActionFrame.h"
#include "../../Json/DictionaryHelper.h"
#include "../System/UIHelper.h"

NS_CC_EXT_BEGIN

UIActionNode::UIActionNode()
{
	currentIndex = 0;
	m_actionNode = NULL;

	m_action = NULL;

	m_ActionFrameList = Array::create();
	m_ActionFrameList->retain();
}

UIActionNode::~UIActionNode()
{
	if (m_action != NULL)
	{
		m_action->release();
	}
    if (m_actionNode)
    {
        m_actionNode->setBindingAction(NULL);
    }
	m_ActionFrameList->removeAllObjects();
	m_ActionFrameList->release();
}

void UIActionNode::initWithDictionary(cs::JsonDictionary *dic,UIWidget* root)
{
    setActionTag(DICTOOL->getIntValue_json(dic, "ActionTag"));
    int actionFrameCount = DICTOOL->getArrayCount_json(dic, "actionframelist");
	UIWidget* bindingWidget = CCUIHELPER->seekActionWidgetByActionTag(root, getActionTag());
	if (bindingWidget)
	{
		SetActionNode(bindingWidget);
		bindingWidget->setBindingAction(this);
	}
    
    for (int i=0; i<actionFrameCount; i++)
    {
        UIActionFrame* actionFrame = new UIActionFrame();
        actionFrame->autorelease();
        cs::JsonDictionary* actionFrameDic = DICTOOL->getDictionaryFromArray_json(dic, "actionframelist", i);
        actionFrame->initWithDictionary(actionFrameDic);
        m_ActionFrameList->addObject(actionFrame);
		CC_SAFE_DELETE(actionFrameDic);
    }
}

void UIActionNode::SetActionNode(UIWidget* widget)
{
	m_actionNode = widget;

	//UpdateToFrameByIndex(currentIndex);
}

void UIActionNode::releaseBindingWidget()
{
    m_actionNode = NULL;
}

void UIActionNode::InsertFrame(int index, UIActionFrame* frame)
{
	m_ActionFrameList->insertObject(frame,index);
}

void UIActionNode::AddFrame(UIActionFrame* frame)
{
	m_ActionFrameList->addObject(frame);
}

void UIActionNode::DeleteFrame(UIActionFrame* frame)
{
	m_ActionFrameList->removeObject(frame);
}

void UIActionNode::ClearAllFrame()
{
	m_ActionFrameList->removeAllObjects();
}

void UIActionNode::UpdateToFrameByIndex(int index)
{
	currentIndex = index;

	int frameNum = m_ActionFrameList->count();

	bool bFindFrame = false;

	UIActionFrame* frame = NULL;
	for (int i = 0; i < frameNum; i++)
	{
		frame = (UIActionFrame*)m_ActionFrameList->getObjectAtIndex(index);
		if (frame->getFrameId() == index)
		{
			bFindFrame = true;
			UpdateToFrame(frame);
			break;
		}
	}

	if (!bFindFrame)
	{
		m_actionNode->setVisible(false);
	}
}

void UIActionNode::UpdateToFrame(UIActionFrame* frame)
{
	if ( m_actionNode == NULL || frame == NULL )
	{
		return;
	}

	m_actionNode->setRotation(frame->getRotation());
	m_actionNode->setScaleX(frame->getScaleX());
	m_actionNode->setScaleY(frame->getScaleY());
	m_actionNode->setPosition(frame->getPosition());
	m_actionNode->setOpacity(frame->getOpacity());
	m_actionNode->setColor(frame->getColor());

}

void UIActionNode::RunAction(float fUnitTime, bool bloop)
{
	int frameNum = m_ActionFrameList->count();

	if ( m_actionNode == NULL || frameNum <= 0 )
	{
		return;
	}	

	Array* actionFrame = Array::create();

	for ( int i = 0; i < frameNum; i++ )
	{
		float duration;

		UIActionFrame* frame = (UIActionFrame*)m_ActionFrameList->getObjectAtIndex(i);

		if ( i == 0 )
		{
			//duration = frame->getFrameId() * fUnitTime;
			duration = 0.01f;
		}
		else
		{
			UIActionFrame* frame_pre = (UIActionFrame*)m_ActionFrameList->getObjectAtIndex(i-1);
			duration = (frame->getFrameId() - frame_pre->getFrameId()) * fUnitTime;
		}

		MoveTo* action_1 = MoveTo::create(duration,frame->getPosition());
		RotateTo* action_2 = RotateTo::create(duration,frame->getRotation());
		ScaleTo* action_3 = ScaleTo::create(duration,frame->getScaleX(),frame->getScaleY());
		FadeTo* action_4 = FadeTo::create(duration,frame->getOpacity());
		TintTo* action_5 = TintTo::create(duration,frame->getColor().r,frame->getColor().g,frame->getColor().b);

		Spawn * actionSpawn = Spawn::create(action_1,action_2,action_3,action_4,action_5, NULL);
		actionFrame->addObject( actionSpawn );
	}

	if (bloop)
	{
        ActionInterval* actionInterval = dynamic_cast<ActionInterval*>(Sequence::create(actionFrame));
        if (actionInterval)
        {
            if (m_actionNode) {
				if (m_action!=NULL)
				{
					m_action->release();
				}
				m_action = RepeatForever::create(actionInterval);
				m_action->retain();
                m_actionNode->runAction(m_action);
            }
        }
	}
	else
	{
        if (m_actionNode) {
			if (m_action!=NULL)
			{
				m_action->release();
			}
			m_action = Sequence::create(actionFrame);
			m_action->retain();
            m_actionNode->runAction(m_action);
        }
	}
}

void UIActionNode::StopAction()
{
    if (m_actionNode) {
        m_actionNode->stopAction(m_action);
    }
}

NS_CC_EXT_END