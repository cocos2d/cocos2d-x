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

#include "CCActionNode.h"
#include "CCActionFrameEasing.h"
#include "CCActionObject.h"
#include "../GUI/BaseClasses/UIWidget.h"
#include "../GUI/System/UIHelper.h"
#include "../Json/DictionaryHelper.h"
#include "../Json/CocoLoader.h"


NS_CC_EXT_BEGIN

	ActionNode::ActionNode()
	: currentFrameIndex(0)
	, destFrameIndex(0)
	, m_fUnitTime(0.1f)
	, m_ActionTag(0)
	, m_Object(NULL)
	, m_actionSpawn(NULL)
	, m_action(NULL)
	, m_FrameArray(NULL)
	, frameArrayNum(0)
{
	m_FrameArray = CCArray::create();
	m_FrameArray->retain();

	frameArrayNum = (int)kKeyframeMax;
	for(int i = 0; i < frameArrayNum; i++)
	{
		CCArray* cArray = CCArray::create();
		m_FrameArray->addObject(cArray);
	}
}

ActionNode::~ActionNode()
{
	if (m_action == NULL)
	{
		CC_SAFE_RELEASE_NULL(m_actionSpawn);
	}
	else
	{
		CC_SAFE_RELEASE_NULL(m_action);
	}

	if (m_FrameArray != NULL)
	{
		//m_FrameArray->removeAllObjects();
		CC_SAFE_RELEASE_NULL(m_FrameArray);
	}

}

void ActionNode::initWithDictionary(const rapidjson::Value& dic,CCObject* root)
{
	setActionTag(DICTOOL->getIntValue_json(dic, "ActionTag"));
	int actionFrameCount = DICTOOL->getArrayCount_json(dic, "actionframelist");
	for (int i=0; i<actionFrameCount; i++) {

		const rapidjson::Value& actionFrameDic = DICTOOL->getDictionaryFromArray_json(dic, "actionframelist", i);
		int frameInex = DICTOOL->getIntValue_json(actionFrameDic,"frameid");
        int frameTweenType = DICTOOL->getIntValue_json(actionFrameDic,"tweenType");
        
        std::vector<float> frameTweenParameter;
        int frameTweenParameterNum = DICTOOL->getArrayCount_json(actionFrameDic, "tweenParameter");
        
        for (int j = 0; j < frameTweenParameterNum; j++)
        {
            float value = DICTOOL->getFloatValueFromArray_json(actionFrameDic, "tweenParameter", j);
            frameTweenParameter.push_back(value);
        }

		bool existPosition = DICTOOL->checkObjectExist_json(actionFrameDic,"positionx");
		if (existPosition)
		{
			float positionX = DICTOOL->getFloatValue_json(actionFrameDic, "positionx");
			float positionY = DICTOOL->getFloatValue_json(actionFrameDic, "positiony");
			ActionMoveFrame* actionFrame = new ActionMoveFrame();
			actionFrame->autorelease();
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setPosition(CCPointMake(positionX, positionY));
			CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeMove);
			cActionArray->addObject(actionFrame);
		}

		bool existScale = DICTOOL->checkObjectExist_json(actionFrameDic,"scalex");
		if (existScale)
		{
			float scaleX = DICTOOL->getFloatValue_json(actionFrameDic, "scalex");
			float scaleY = DICTOOL->getFloatValue_json(actionFrameDic, "scaley");
			ActionScaleFrame* actionFrame = new ActionScaleFrame();
			actionFrame->autorelease();
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setScaleX(scaleX);
			actionFrame->setScaleY(scaleY);
			CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeScale);
			cActionArray->addObject(actionFrame);
		}

		bool existRotation = DICTOOL->checkObjectExist_json(actionFrameDic,"rotation");
		if (existRotation)
		{
			float rotation = DICTOOL->getFloatValue_json(actionFrameDic, "rotation");
			ActionRotationFrame* actionFrame = new ActionRotationFrame();
			actionFrame->autorelease();
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setRotation(rotation);
			CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeRotate);
			cActionArray->addObject(actionFrame);
		}

		bool existOpacity = DICTOOL->checkObjectExist_json(actionFrameDic,"opacity");
		if (existOpacity)
		{
			int opacity = DICTOOL->getIntValue_json(actionFrameDic, "opacity");
			ActionFadeFrame* actionFrame = new ActionFadeFrame();
			actionFrame->autorelease();
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setOpacity(opacity);
			CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeFade);
			cActionArray->addObject(actionFrame);
		}

		bool existColor = DICTOOL->checkObjectExist_json(actionFrameDic,"colorr");
		if (existColor)
		{
			int colorR = DICTOOL->getIntValue_json(actionFrameDic, "colorr");
			int colorG = DICTOOL->getIntValue_json(actionFrameDic, "colorg");
			int colorB = DICTOOL->getIntValue_json(actionFrameDic, "colorb");
			ActionTintFrame* actionFrame = new ActionTintFrame();
			actionFrame->autorelease();
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setColor(ccc3(colorR,colorG,colorB));
			CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeTint);
			cActionArray->addObject(actionFrame);
		}
	}
	initActionNodeFromRoot(root);
}

void ActionNode::initWithBinary(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode, cocos2d::CCObject *root)
{
    
    stExpCocoNode *stChildNode = pCocoNode;
    
	int actionNodeCount =  stChildNode->GetChildNum();
    stChildNode = stChildNode[0].GetChildArray(pCocoLoader);
    stExpCocoNode *frameListNode = NULL;
    for (int i = 0; i < actionNodeCount; ++i) {
        std::string key = stChildNode[i].GetName(pCocoLoader);
        std::string value = stChildNode[i].GetValue(pCocoLoader);
        if (key == "ActionTag") {
            setActionTag(valueToInt(value));
        }else if (key == "actionframelist"){
            frameListNode = &stChildNode[i];
        }
    }
    
    int actionFrameCount = frameListNode->GetChildNum();
    stExpCocoNode *stFrameChildNode = frameListNode->GetChildArray(pCocoLoader);
	for (int i=0; i<actionFrameCount; i++) {
        
        int frameIndex;
        int frameTweenType;
        float positionX;
        float positionY;
        float scaleX;
        float scaleY;
        float rotation;
        int opacity;
        int colorR = -1;
        int colorG = -1;
        int colorB = -1;
        std::vector<float> frameTweenParameter;
        
        int framesCount = stFrameChildNode[i].GetChildNum();
        stExpCocoNode *innerFrameNode = stFrameChildNode[i].GetChildArray(pCocoLoader);
        for (int j = 0; j < framesCount; j++) {
            std::string key = innerFrameNode[j].GetName(pCocoLoader);
            std::string value = innerFrameNode[j].GetValue(pCocoLoader);
            
            if (key == "frameid") {
                frameIndex = valueToInt(value);
            }else if(key == "tweenType"){
                frameTweenType = valueToInt(value);
            }else if (key == "tweenParameter"){
              //  There are no tweenParameter args in the json file
                int tweenParameterCount = innerFrameNode[j].GetChildNum();
                stExpCocoNode *tweenParameterArray = innerFrameNode[j].GetChildArray(pCocoLoader);
                for (int k = 0; k < tweenParameterCount; ++k) {
                    std::string t_key = tweenParameterArray[j].GetName(pCocoLoader);
                    std::string t_value = tweenParameterArray[j].GetValue(pCocoLoader);
                    frameTweenParameter.push_back(valueToFloat(t_value));
                }
            }else if (key == "positionx"){
                positionX = valueToFloat(value);
            }else if (key == "positiony"){
                positionY = valueToFloat(value);
                ActionMoveFrame* actionFrame = new ActionMoveFrame();
                actionFrame->autorelease();
                actionFrame->setEasingType(frameTweenType);
                actionFrame->setEasingParameter(frameTweenParameter);
                actionFrame->setFrameIndex(frameIndex);
                actionFrame->setPosition(CCPointMake(positionX, positionY));
                CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeMove);
                cActionArray->addObject(actionFrame);
            }else if(key == "scalex"){
                scaleX = valueToFloat(value);
            }else if(key == "scaley"){
                scaleY = valueToFloat(value);
                ActionScaleFrame* actionFrame = new ActionScaleFrame();
                actionFrame->autorelease();
                actionFrame->setEasingType(frameTweenType);
                actionFrame->setEasingParameter(frameTweenParameter);
                actionFrame->setFrameIndex(frameIndex);
                actionFrame->setScaleX(scaleX);
                actionFrame->setScaleY(scaleY);
                CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeScale);
                cActionArray->addObject(actionFrame);
            }else if (key == "rotation"){
                rotation = valueToFloat(value);
                ActionRotationFrame* actionFrame = new ActionRotationFrame();
                actionFrame->autorelease();
                actionFrame->setEasingType(frameTweenType);
                actionFrame->setEasingParameter(frameTweenParameter);
                actionFrame->setFrameIndex(frameIndex);
                actionFrame->setRotation(rotation);
                CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeRotate);
                cActionArray->addObject(actionFrame);
            }else if (key == "opacity"){
                opacity = valueToInt(value);
                ActionFadeFrame* actionFrame = new ActionFadeFrame();
                actionFrame->autorelease();
                actionFrame->setEasingType(frameTweenType);
                actionFrame->setEasingParameter(frameTweenParameter);
                actionFrame->setFrameIndex(frameIndex);
                actionFrame->setOpacity(opacity);
                CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeFade);
                cActionArray->addObject(actionFrame);
            }else if (key == "colorb"){
                colorB = valueToInt(value);
            }else if(key == "colorg"){
                colorG = valueToInt(value);
            }else if(key == "colorr"){
                colorR = valueToInt(value);
                
                ActionTintFrame* actionFrame = new ActionTintFrame();
                actionFrame->autorelease();
                actionFrame->setEasingType(frameTweenType);
                actionFrame->setEasingParameter(frameTweenParameter);
                actionFrame->setFrameIndex(frameIndex);
                actionFrame->setColor(ccc3(colorR,colorG,colorB));
                CCArray* cActionArray = (CCArray*)m_FrameArray->objectAtIndex((int)kKeyframeTint);
                cActionArray->addObject(actionFrame);
            }
            
           
        }

	}
	initActionNodeFromRoot(root);
}

void ActionNode::initActionNodeFromRoot(CCObject* root)
{	
	CCNode* rootNode = dynamic_cast<CCNode*>(root);
	if (rootNode != NULL)
	{
        cocos2d::ui::Widget* rootWidget = dynamic_cast<cocos2d::ui::Widget*>(root);
		if (rootWidget != NULL)
		{
			cocos2d::ui::Widget* widget = cocos2d::ui::UIHelper::seekActionWidgetByActionTag(rootWidget, getActionTag());
			if (widget != NULL)
			{
				setObject(widget);
			}
		}
	}
}

void ActionNode::setUnitTime(float fTime)
{
	m_fUnitTime = fTime;
	this->refreshActionProperty();
}

float ActionNode::getUnitTime()
{
	return m_fUnitTime;
}

void ActionNode::setActionTag(int tag)
{
	m_ActionTag = tag;
}

int ActionNode::getActionTag()
{
	return m_ActionTag;
}

void ActionNode::setObject(CCObject* node)
{
	m_Object = node;
}

CCObject* ActionNode::getObject()
{
	return m_Object;
}

CCNode* ActionNode::getActionNode()
{
	CCNode* cNode = dynamic_cast<CCNode*>(m_Object);
	if (cNode != NULL)
	{
		return cNode;
	}
	else
	{
		cocos2d::ui::Widget* rootWidget = dynamic_cast<cocos2d::ui::Widget*>(m_Object);
		if (rootWidget != NULL)
		{
			return rootWidget;
		}
	}
	return NULL;
}

void ActionNode::insertFrame(int index, ActionFrame* frame)
{
	if (frame == NULL)
	{
		return;
	}
	int frameType = frame->getFrameType();
	CCArray* cArray = (CCArray*)m_FrameArray->objectAtIndex(frameType);
	if (cArray == NULL)
	{
		return;
	}	
	cArray->insertObject(frame,index);
}

void ActionNode::addFrame(ActionFrame* frame)
{
	if (frame == NULL)
	{
		return;
	}
	int frameType = frame->getFrameType();
	CCArray* cArray = (CCArray*)m_FrameArray->objectAtIndex(frameType);
	if (cArray == NULL)
	{
		return;
	}
	cArray->addObject(frame);
}

void ActionNode::deleteFrame(ActionFrame* frame)
{
	if (frame == NULL)
	{
		return;
	}
	int frameType = frame->getFrameType();
	CCArray* cArray = (CCArray*)m_FrameArray->objectAtIndex(frameType);
	if (cArray == NULL)
	{ 
		return;
	}
	cArray->removeObject(frame);
}

void ActionNode::clearAllFrame()
{
	for (int i = 0; i < frameArrayNum; i++)
	{
		m_FrameArray[i].removeAllObjects();
	}
}

CCSpawn * ActionNode::refreshActionProperty()
{
	if ( m_Object == NULL )
	{
		return NULL;
	}
	CCArray* cSpawnArray = CCArray::create();
	for (int n = 0; n < frameArrayNum; n++)
	{
		CCArray* cArray = (CCArray*)(m_FrameArray->objectAtIndex(n));
		if (cArray == NULL || cArray->count() <= 0)
		{
			continue;
		}

		CCArray* cSequenceArray = CCArray::create();
		int frameCount = cArray->count();
		for (int i = 0; i < frameCount; i++)
		{
			ActionFrame* frame = (ActionFrame*)(cArray->objectAtIndex(i));
			if (i == 0)
			{
				CCAction* cAction = frame->getAction(0);
				cSequenceArray->addObject(cAction);
			}
			else
			{
				ActionFrame* srcFrame = (ActionFrame*)(cArray->objectAtIndex(i-1));
				float duration = (frame->getFrameIndex() - srcFrame->getFrameIndex()) * getUnitTime();
				CCAction* cAction = frame->getAction(duration,srcFrame);
				cSequenceArray->addObject(cAction);
			}
		}
		CCSequence* cSequence = CCSequence::create(cSequenceArray);
		if (cSequence != NULL)
		{
			cSpawnArray->addObject(cSequence);
		}
	}

	if (m_action == NULL)
	{
		CC_SAFE_RELEASE_NULL(m_actionSpawn);
	}
	else
	{
		CC_SAFE_RELEASE_NULL(m_action);
	}

	m_actionSpawn = CCSpawn::create(cSpawnArray);
	CC_SAFE_RETAIN(m_actionSpawn);
	return m_actionSpawn;
}

void ActionNode::playAction()
{
	if ( m_Object == NULL || m_actionSpawn == NULL)
	{
		return;
	}

	if (m_action!=NULL)
	{
		m_action->release();
	}

	m_action = CCSequence::create(m_actionSpawn,NULL);
	m_action->retain();

	this->runAction();

}

void ActionNode::runAction()
{
	CCNode* cNode = this->getActionNode();
	if (cNode != NULL && m_action != NULL)
	{
		cNode->runAction(m_action);
	}
}

void ActionNode::stopAction()
{
	CCNode* cNode = this->getActionNode();
	if (cNode != NULL && m_action != NULL)
	{
		cNode->stopAction(m_action);
	}
}

int ActionNode::getFirstFrameIndex()
{
	int frameindex = 99999;
	bool bFindFrame = false;
	for (int n = 0; n < frameArrayNum; n++)
	{
		CCArray* cArray = (CCArray*)(m_FrameArray->objectAtIndex(n));
		if (cArray == NULL || cArray->count() <= 0)
		{
			continue;
		}

		bFindFrame = true;
		ActionFrame* frame = (ActionFrame*)(cArray->objectAtIndex(0));
		int iFrameIndex = frame->getFrameIndex();

		if (frameindex > iFrameIndex)
		{
			frameindex = iFrameIndex;
		}
	}
	if (!bFindFrame)
	{
		frameindex = 0;
	}
	return frameindex;
}

int ActionNode::valueToInt(std::string& value)
{
    return atoi(value.c_str());
}
bool ActionNode::valueToBool(std::string& value)
{
    int intValue = valueToInt(value);
    if (1 == intValue) {
        return true;
    }else{
        return false;
    }
}
float ActionNode::valueToFloat(std::string& value)
{
    return atof(value.c_str());
}

int ActionNode::getLastFrameIndex()
{
	int frameindex = -1;
	bool bFindFrame = false;
	for (int n = 0; n < frameArrayNum; n++)
	{
		CCArray* cArray = (CCArray*)(m_FrameArray->objectAtIndex(n));
		if (cArray == NULL || cArray->count() <= 0)
		{
			continue;
		}

		bFindFrame = true;
		int lastInex = cArray->count() - 1;
		ActionFrame* frame = (ActionFrame*)(cArray->objectAtIndex(lastInex));
		int iFrameIndex = frame->getFrameIndex();

		if (frameindex < iFrameIndex)
		{
			frameindex = iFrameIndex;
		}
	}
	if (!bFindFrame)
	{
		frameindex = 0;
	}
	return frameindex;
}
bool ActionNode::updateActionToTimeLine(float fTime)
{
	bool bFindFrame = false;

	ActionFrame* srcFrame = NULL;

	for (int n = 0; n < frameArrayNum; n++)
	{
		CCArray* cArray = (CCArray*)(m_FrameArray->objectAtIndex(n));
		if (cArray == NULL)
		{
			continue;
		}
		int frameCount = cArray->count();
		for (int i = 0; i < frameCount; i++)
		{
			ActionFrame* frame = (ActionFrame*)(cArray->objectAtIndex(i));

			if (frame->getFrameIndex()*getUnitTime() == fTime)
			{
				this->easingToFrame(1.0f,1.0f,NULL,frame);
				bFindFrame = true;
				break;
			}
			else if (frame->getFrameIndex()*getUnitTime() > fTime)
			{
				if (i == 0)
				{
					this->easingToFrame(1.0f,1.0f,NULL,frame);
					bFindFrame = false;
				}
				else
				{
					srcFrame = (ActionFrame*)(cArray->objectAtIndex(i-1));
					float duration = (frame->getFrameIndex() - srcFrame->getFrameIndex())*getUnitTime();
					float delaytime = fTime - srcFrame->getFrameIndex()*getUnitTime();
					this->easingToFrame(duration,1.0f,NULL,srcFrame);
					//float easingTime = ActionFrameEasing::bounceTime(delaytime);
					this->easingToFrame(duration,delaytime/duration,srcFrame,frame);
					bFindFrame = true;
				}
				break;
			}
		}
	}
	return bFindFrame;
}

void ActionNode::easingToFrame(float duration,float delayTime,ActionFrame* srcFrame,ActionFrame* destFrame)
{
	CCAction* cAction = destFrame->getAction(duration,srcFrame);
	CCNode* cNode = this->getActionNode();
	if (cAction == NULL || cNode == NULL)
	{
		return;
	}	
	cAction->startWithTarget(cNode);
	cAction->update(delayTime);
}


bool ActionNode::isActionDoneOnce()
{
	if (m_action == NULL)
	{
		return true;
	}
	return m_action->isDone();
}
NS_CC_EXT_END