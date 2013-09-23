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
#include "../GUI/BaseClasses/UIWidget.h"
#include "../GUI/System/UIHelper.h"
#include "../Json/DictionaryHelper.h"

NS_CC_EXT_BEGIN

	ActionNode::ActionNode()
	: _currentFrameIndex(0)
	, _destFrameIndex(0)
	, _fUnitTime(0.1f)
	, _actionTag(0)
	, _actionSpawn(NULL)
	, _action(NULL)
	, _object(NULL)
	, _frameArray(NULL)
	, _frameArrayNum(0)
{
	_frameArray = Array::create();
	_frameArray->retain();

	_frameArrayNum = (int)kKeyframeMax;
	for(int i = 0; i < _frameArrayNum; i++)
	{
		Array* cArray = Array::create();
		_frameArray->addObject(cArray);
	}
}

ActionNode::~ActionNode()
{
	if (_action == NULL)
	{
		CC_SAFE_RELEASE(_actionSpawn);
	}
	else
	{
		CC_SAFE_RELEASE(_action);
	}
	
	if (_frameArray != NULL)
	{
		_frameArray->removeAllObjects();
		CC_SAFE_RELEASE(_frameArray);
	}

}

void ActionNode::initWithDictionary(cs::JsonDictionary *dic,Object* root)
{
	setActionTag(DICTOOL->getIntValue_json(dic, "ActionTag"));
	int actionFrameCount = DICTOOL->getArrayCount_json(dic, "actionframelist");
	for (int i=0; i<actionFrameCount; i++) {

		cs::JsonDictionary* actionFrameDic = DICTOOL->getDictionaryFromArray_json(dic, "actionframelist", i);
		int frameInex = DICTOOL->getIntValue_json(actionFrameDic,"frameid");

		bool existPosition = DICTOOL->checkObjectExist_json(actionFrameDic,"positionx");
		if (existPosition)
		{
			float positionX = DICTOOL->getFloatValue_json(actionFrameDic, "positionx");
			float positionY = DICTOOL->getFloatValue_json(actionFrameDic, "positiony");
			ActionMoveFrame* actionFrame = new ActionMoveFrame();
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setPosition(Point(positionX, positionY));
			Array* cActionArray = (Array*)_frameArray->getObjectAtIndex((int)kKeyframeMove);
			cActionArray->addObject(actionFrame);
		}

		bool existScale = DICTOOL->checkObjectExist_json(actionFrameDic,"scalex");
		if (existScale)
		{
			float scaleX = DICTOOL->getFloatValue_json(actionFrameDic, "scalex");
			float scaleY = DICTOOL->getFloatValue_json(actionFrameDic, "scaley");
			ActionScaleFrame* actionFrame = new ActionScaleFrame();
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setScaleX(scaleX);
			actionFrame->setScaleY(scaleY);
			Array* cActionArray = (Array*)_frameArray->getObjectAtIndex((int)kKeyframeScale);
			cActionArray->addObject(actionFrame);
		}

		bool existRotation = DICTOOL->checkObjectExist_json(actionFrameDic,"rotation");
		if (existRotation)
		{
			float rotation = DICTOOL->getFloatValue_json(actionFrameDic, "rotation");
			ActionRotationFrame* actionFrame = new ActionRotationFrame();
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setRotation(rotation);
			Array* cActionArray = (Array*)_frameArray->getObjectAtIndex((int)kKeyframeRotate);
			cActionArray->addObject(actionFrame);
		}

		bool existOpacity = DICTOOL->checkObjectExist_json(actionFrameDic,"opacity");
		if (existOpacity)
		{
			int opacity = DICTOOL->getIntValue_json(actionFrameDic, "opacity");
			ActionFadeFrame* actionFrame = new ActionFadeFrame();
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setOpacity(opacity);
			Array* cActionArray = (Array*)_frameArray->getObjectAtIndex((int)kKeyframeFade);
			cActionArray->addObject(actionFrame);
		}

		bool existColor = DICTOOL->checkObjectExist_json(actionFrameDic,"colorr");
		if (existColor)
		{
			int colorR = DICTOOL->getIntValue_json(actionFrameDic, "colorr");
			int colorG = DICTOOL->getIntValue_json(actionFrameDic, "colorg");
			int colorB = DICTOOL->getIntValue_json(actionFrameDic, "colorb");
			ActionTintFrame* actionFrame = new ActionTintFrame();
			actionFrame->setFrameIndex(frameInex);
			actionFrame->setColor(Color3B(colorR,colorG,colorB));
			Array* cActionArray = (Array*)_frameArray->getObjectAtIndex((int)kKeyframeTint);
			cActionArray->addObject(actionFrame);
		}

		CC_SAFE_DELETE(actionFrameDic);
	}
	initActionNodeFromRoot(root);
}

void ActionNode::initActionNodeFromRoot(Object* root)
{	
	Node* rootNode = dynamic_cast<Node*>(root);
	if (rootNode != NULL)
	{
		log("Need a definition of <initActionNodeFromRoot> for gameObject");
	}
	else
	{
		UIWidget* rootWidget = dynamic_cast<UIWidget*>(root);
		if (rootWidget != NULL)
		{
			UIWidget* widget = UIHelper::instance()->seekActionWidgetByActionTag(rootWidget, getActionTag());
			if (widget != NULL)
			{
				setObject(widget);
			}
		}
	}
}

void ActionNode::setUnitTime(float fTime)
{
	_fUnitTime = fTime;
	this->refreshActionProperty();
}

float ActionNode::getUnitTime()
{
	return _fUnitTime;
}

void ActionNode::setActionTag(int tag)
{
	_actionTag = tag;
}

int ActionNode::getActionTag()
{
	return _actionTag;
}

void ActionNode::setObject(Object* node)
{
	_object = node;
}

Object* ActionNode::getObject()
{
	return _object;
}

Node* ActionNode::getActionNode()
{
	Node* cNode = dynamic_cast<Node*>(_object);
	if (cNode != NULL)
	{
		return cNode;
	}
	else
	{
		UIWidget* rootWidget = dynamic_cast<UIWidget*>(_object);
		if (rootWidget != NULL)
		{
			return rootWidget->getRenderer();
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
	Array* cArray = (Array*)_frameArray->getObjectAtIndex(frameType);
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
	Array* cArray = (Array*)_frameArray->getObjectAtIndex(frameType);
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
	Array* cArray = (Array*)_frameArray->getObjectAtIndex(frameType);
	if (cArray == NULL)
	{ 
		return;
	}
	cArray->removeObject(frame);
}

void ActionNode::clearAllFrame()
{
	for (int i = 0; i < _frameArrayNum; i++)
	{
		_frameArray[i].removeAllObjects();
	}
}

Spawn * ActionNode::refreshActionProperty()
{
	if ( _object == NULL )
	{
		return NULL;
	}
	Array* cSpawnArray = Array::create();
	for (int n = 0; n < _frameArrayNum; n++)
	{
		Array* cArray = (Array*)(_frameArray->getObjectAtIndex(n));
		if (cArray == NULL || cArray->count() <= 0)
		{
			continue;
		}

		Array* cSequenceArray = Array::create();
		int frameCount = cArray->count();
		for (int i = 0; i < frameCount; i++)
		{
			ActionFrame* frame = (ActionFrame*)(cArray->getObjectAtIndex(i));
			if (i == 0)
			{
			}
			else
			{
				ActionFrame* srcFrame = (ActionFrame*)(cArray->getObjectAtIndex(i-1));
				float duration = (frame->getFrameIndex() - srcFrame->getFrameIndex()) * getUnitTime();
				Action* cAction = frame->getAction(duration);
				cSequenceArray->addObject(cAction);
			}
		}
		Sequence* cSequence = Sequence::create(cSequenceArray);
		cSpawnArray->addObject(cSequence);
	}

	if (_action == NULL)
	{
		CC_SAFE_RELEASE(_actionSpawn);
	}
	else
	{
		CC_SAFE_RELEASE(_action);
	}

	_actionSpawn = Spawn::create(cSpawnArray);
	return _actionSpawn;
}

void ActionNode::playAction(bool bloop)
{
	if ( _object == NULL || _actionSpawn == NULL)
	{
		return;
	}

	if (_action!=NULL)
	{
		_action->release();
	}
	if (bloop)
	{
		_action = RepeatForever::create(_actionSpawn);
	}
	else
	{
		_action = Sequence::create(_actionSpawn, NULL);
	}
	_action->retain();

	this->runAction();

}

void ActionNode::runAction()
{
	Node* cNode = this->getActionNode();
	if (cNode != NULL && _action != NULL)
	{
		cNode->runAction(_action);
	}
}

void ActionNode::stopAction()
{
	Node* cNode = this->getActionNode();
	if (cNode != NULL && _action != NULL)
	{
		cNode->stopAction(_action);
	}
}

int ActionNode::getFirstFrameIndex()
{
	int frameindex = 99999;
	bool bFindFrame = false;
	for (int n = 0; n < _frameArrayNum; n++)
	{
		Array* cArray = (Array*)(_frameArray->getObjectAtIndex(n));
		if (cArray == NULL || cArray->count() <= 0)
		{
			continue;
		}
		bFindFrame = true;
		ActionFrame* frame = (ActionFrame*)(cArray->getObjectAtIndex(0));
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

int ActionNode::getLastFrameIndex()
{
	int frameindex = -1;
	bool bFindFrame = false;
	for (int n = 0; n < _frameArrayNum; n++)
	{
		Array* cArray = (Array*)(_frameArray->getObjectAtIndex(n));
		if (cArray == NULL || cArray->count() <= 0)
		{
			continue;
		}
		bFindFrame = true;
		int lastInex = cArray->count() - 1;
		ActionFrame* frame = (ActionFrame*)(cArray->getObjectAtIndex(lastInex));
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
	ActionFrame* destFrame = NULL;

	for (int n = 0; n < _frameArrayNum; n++)
	{
		Array* cArray = (Array*)(_frameArray->getObjectAtIndex(n));
		if (cArray == NULL)
		{
			continue;
		}
		int frameCount = cArray->count();
		for (int i = 0; i < frameCount; i++)
		{
			ActionFrame* frame = (ActionFrame*)(cArray->getObjectAtIndex(i));

			if (frame->getFrameIndex()*getUnitTime() == fTime)
			{
				this->easingToFrame(1.0f,1.0f,frame);
				bFindFrame = true;
				break;
			}
			else if (frame->getFrameIndex()*getUnitTime() > fTime)
			{
				if (i == 0)
				{
					this->easingToFrame(1.0f,1.0f,frame);
					bFindFrame = false;
				}
				else
				{
					srcFrame = (ActionFrame*)(cArray->getObjectAtIndex(i-1));
					float duration = (frame->getFrameIndex() - srcFrame->getFrameIndex())*getUnitTime();
					float delaytime = fTime - srcFrame->getFrameIndex()*getUnitTime();
					this->easingToFrame(duration,1.0f,srcFrame);
					//float easingTime = ActionFrameEasing::bounceTime(delaytime);
					this->easingToFrame(duration,delaytime/duration,frame);
					bFindFrame = true;
				}
				break;
			}
		}
	}
	return bFindFrame;
}

void ActionNode::easingToFrame(float duration,float delayTime,ActionFrame* destFrame)
{
	Action* cAction = destFrame->getAction(duration);
	Node* cNode = this->getActionNode();
	if (cAction == NULL || cNode == NULL)
	{
		return;
	}	
	cAction->startWithTarget(cNode);
	cAction->update(delayTime);
}

NS_CC_EXT_END