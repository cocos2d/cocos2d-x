/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "editor-support/cocostudio/CCActionNode.h"
#include "editor-support/cocostudio/CCActionFrameEasing.h"
#include "ui/UIWidget.h"
#include "ui/UIHelper.h"
#include "ui/UILayout.h"
#include "editor-support/cocostudio/CocoLoader.h"
#include "base/ccUtils.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"


using namespace cocos2d;
using namespace ui;

namespace cocostudio {

ActionNode::ActionNode()
: _currentFrameIndex(0)
, _destFrameIndex(0)
, _fUnitTime(0.1f)
, _actionTag(0)
, _actionSpawn(nullptr)
, _action(nullptr)
, _object(nullptr)
, _frameArrayNum(0)
{
    _frameArrayNum = (int)kKeyframeMax;
    for(int i = 0; i < _frameArrayNum; i++)
    {
        _frameArray.push_back( new cocos2d::Vector<ActionFrame*>());
    }
}

ActionNode::~ActionNode()
{
    if (_action == nullptr)
    {
        CC_SAFE_RELEASE_NULL(_actionSpawn);
    }
    else
    {
        CC_SAFE_RELEASE_NULL(_action);
        CC_SAFE_RELEASE_NULL(_actionSpawn);
    }
    
    CC_SAFE_RELEASE(_object);

    for (auto object : _frameArray)
    {
        object->clear();
        CC_SAFE_DELETE(object);
    }
    _frameArray.clear();
}

void ActionNode::initWithDictionary(const rapidjson::Value& dic, Ref* root)
{
    Widget * rw = dynamic_cast<Widget *>(root);
    if (nullptr == rw)
        return;

    setActionTag(DICTOOL->getIntValue_json(dic, "ActionTag"));
    Widget* node = Helper::seekActionWidgetByActionTag(rw, getActionTag());
    bool positionOffset = node && (nullptr == (dynamic_cast<Layout *>(node)));

    int actionFrameCount = DICTOOL->getArrayCount_json(dic, "actionframelist");
    for (int i=0; i<actionFrameCount; i++)
    {
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
            if (positionOffset && (nullptr != node->getParent()) && ActionManagerEx::getInstance()->getStudioVersionNumber() < 1600)
            {
                Vec2 AnchorPointIn = node->getParent()->getAnchorPointInPoints();
                positionX += AnchorPointIn.x;
                positionY += AnchorPointIn.y;
            }
            ActionMoveFrame* actionFrame = new (std::nothrow) ActionMoveFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setPosition(Vec2(positionX, positionY));
            auto cActionArray = _frameArray.at((int)kKeyframeMove);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }

        bool existScale = DICTOOL->checkObjectExist_json(actionFrameDic,"scalex");
        if (existScale)
        {
            float scaleX = DICTOOL->getFloatValue_json(actionFrameDic, "scalex");
            float scaleY = DICTOOL->getFloatValue_json(actionFrameDic, "scaley");
            ActionScaleFrame* actionFrame = new (std::nothrow) ActionScaleFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setScaleX(scaleX);
            actionFrame->setScaleY(scaleY);
            auto cActionArray = _frameArray.at((int)kKeyframeScale);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();             
        }

        bool existRotation = DICTOOL->checkObjectExist_json(actionFrameDic,"rotation");
        if (existRotation)
        {
            float rotation = DICTOOL->getFloatValue_json(actionFrameDic, "rotation");
            ActionRotationFrame* actionFrame = new (std::nothrow) ActionRotationFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setRotation(rotation);
            auto cActionArray = _frameArray.at((int)kKeyframeRotate);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }

        bool existOpacity = DICTOOL->checkObjectExist_json(actionFrameDic,"opacity");
        if (existOpacity)
        {
            int opacity = DICTOOL->getIntValue_json(actionFrameDic, "opacity");
            ActionFadeFrame* actionFrame = new (std::nothrow) ActionFadeFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setOpacity(opacity);
            auto cActionArray = _frameArray.at((int)kKeyframeTint);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }

        bool existColor = DICTOOL->checkObjectExist_json(actionFrameDic,"colorr");
        if (existColor)
        {
            int colorR = DICTOOL->getIntValue_json(actionFrameDic, "colorr");
            int colorG = DICTOOL->getIntValue_json(actionFrameDic, "colorg");
            int colorB = DICTOOL->getIntValue_json(actionFrameDic, "colorb");
            ActionTintFrame* actionFrame = new (std::nothrow) ActionTintFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setColor(Color3B(colorR,colorG,colorB));
            auto cActionArray = _frameArray.at((int)kKeyframeFade);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }
    }
    initActionNodeFromRoot(root);
}
    
    int ActionNode::valueToInt(const std::string& value)
    {
        return atoi(value.c_str());
    }
    bool ActionNode::valueToBool(const std::string& value)
    {
        int intValue = valueToInt(value);
        if (1 == intValue) {
            return true;
        }else{
            return false;
        }
    }
    float ActionNode::valueToFloat(const std::string& value)
    {
        return utils::atof(value.c_str());
    }
    
    void ActionNode::initWithBinary(CocoLoader *cocoLoader,
                                    stExpCocoNode *cocoNode,
                                    cocos2d::Ref *root)
    {
        
        stExpCocoNode *stChildNode = cocoNode;
        
        int actionNodeCount =  stChildNode->GetChildNum();
        stChildNode = stChildNode[0].GetChildArray(cocoLoader);
        stExpCocoNode *frameListNode = nullptr;
        for (int i = 0; i < actionNodeCount; ++i) {
            std::string key = stChildNode[i].GetName(cocoLoader);
            std::string value = stChildNode[i].GetValue(cocoLoader);
            if (key == "ActionTag") {
                setActionTag(valueToInt(value));
            }else if (key == "actionframelist"){
                frameListNode = &stChildNode[i];
            }
        }
        
        int actionFrameCount = frameListNode->GetChildNum();
        stExpCocoNode *stFrameChildNode = frameListNode->GetChildArray(cocoLoader);
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
            stExpCocoNode *innerFrameNode = stFrameChildNode[i].GetChildArray(cocoLoader);
            for (int j = 0; j < framesCount; j++) {
                std::string key = innerFrameNode[j].GetName(cocoLoader);
                std::string value = innerFrameNode[j].GetValue(cocoLoader);
                
                if (key == "frameid") {
                    frameIndex = valueToInt(value);
                }else if(key == "tweenType"){
                    frameTweenType = valueToInt(value);
                }else if (key == "tweenParameter"){
                    //  There are no tweenParameter args in the json file
                    int tweenParameterCount = innerFrameNode[j].GetChildNum();
                    stExpCocoNode *tweenParameterArray = innerFrameNode[j].GetChildArray(cocoLoader);
                    for (int k = 0; k < tweenParameterCount; ++k) {
                        std::string t_key = tweenParameterArray[j].GetName(cocoLoader);
                        std::string t_value = tweenParameterArray[j].GetValue(cocoLoader);
                        frameTweenParameter.push_back(valueToFloat(t_value));
                    }
                }else if (key == "positionx"){
                    positionX = valueToFloat(value);
                }else if (key == "positiony"){
                    positionY = valueToFloat(value);
                    ActionMoveFrame* actionFrame = new (std::nothrow) ActionMoveFrame();
                    actionFrame->autorelease();
                    actionFrame->setEasingType(frameTweenType);
                    actionFrame->setEasingParameter(frameTweenParameter);
                    actionFrame->setFrameIndex(frameIndex);
                    actionFrame->setPosition(Vec2(positionX, positionY));
                    auto cActionArray = _frameArray.at((int)kKeyframeMove);
                    cActionArray->pushBack(actionFrame);
                }else if(key == "scalex"){
                    scaleX = valueToFloat(value);
                }else if(key == "scaley"){
                    scaleY = valueToFloat(value);
                    ActionScaleFrame* actionFrame = new (std::nothrow) ActionScaleFrame();
                    actionFrame->autorelease();
                    actionFrame->setEasingType(frameTweenType);
                    actionFrame->setEasingParameter(frameTweenParameter);
                    actionFrame->setFrameIndex(frameIndex);
                    actionFrame->setScaleX(scaleX);
                    actionFrame->setScaleY(scaleY);
                    auto cActionArray = _frameArray.at((int)kKeyframeScale);
                    cActionArray->pushBack(actionFrame);
                }else if (key == "rotation"){
                    rotation = valueToFloat(value);
                    ActionRotationFrame* actionFrame = new (std::nothrow) ActionRotationFrame();
                    actionFrame->autorelease();
                    actionFrame->setEasingType(frameTweenType);
                    actionFrame->setEasingParameter(frameTweenParameter);
                    actionFrame->setFrameIndex(frameIndex);
                    actionFrame->setRotation(rotation);
                    auto cActionArray = _frameArray.at((int)kKeyframeRotate);
                    cActionArray->pushBack(actionFrame);
                }else if (key == "opacity"){
                    opacity = valueToInt(value);
                    ActionFadeFrame* actionFrame = new (std::nothrow) ActionFadeFrame();
                    actionFrame->autorelease();
                    actionFrame->setEasingType(frameTweenType);
                    actionFrame->setEasingParameter(frameTweenParameter);
                    actionFrame->setFrameIndex(frameIndex);
                    actionFrame->setOpacity(opacity);
                    auto cActionArray = _frameArray.at((int)kKeyframeFade);
                    cActionArray->pushBack(actionFrame);
                }else if (key == "colorb"){
                    colorB = valueToInt(value);
                }else if(key == "colorg"){
                    colorG = valueToInt(value);
                }else if(key == "colorr"){
                    colorR = valueToInt(value);
                    
                    ActionTintFrame* actionFrame = new (std::nothrow) ActionTintFrame();
                    actionFrame->autorelease();
                    actionFrame->setEasingType(frameTweenType);
                    actionFrame->setEasingParameter(frameTweenParameter);
                    actionFrame->setFrameIndex(frameIndex);
                    actionFrame->setColor(Color3B(colorR,colorG,colorB));
                    auto cActionArray = _frameArray.at((int)kKeyframeTint);
                    cActionArray->pushBack(actionFrame);
                }
                
                
            }
            
        }
        initActionNodeFromRoot(root);
    }

void ActionNode::initActionNodeFromRoot(Ref* root)
{
    Widget* rootWidget = dynamic_cast<Widget*>(root);
    if (rootWidget != nullptr)
    {
        Widget* widget = Helper::seekActionWidgetByActionTag(rootWidget, getActionTag());
        if (widget != nullptr)
        {
            setObject(widget);
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

void ActionNode::setObject(Ref* node)
{
    CC_SAFE_RELEASE(_object);
    _object = node;
    CC_SAFE_RETAIN(_object);
}

Ref*  ActionNode::getObject()
{
    return _object;
}

Node* ActionNode::getActionNode()
{
    Node* cNode = dynamic_cast<Node*>(_object);
    if (cNode != nullptr)
    {
        return cNode;
    }
    return nullptr;
}

void ActionNode::insertFrame(int index, ActionFrame* frame)
{
    if (frame == nullptr)
    {
        return;
    }
    int frameType = frame->getFrameType();
    if(frameType < (int)_frameArray.size())
    {
        auto cArray = _frameArray.at(frameType);
        cArray->insert(index, frame);
    }
}

void ActionNode::addFrame(ActionFrame* frame)
{
    if (frame == nullptr)
    {
        return;
    }
    int frameType = frame->getFrameType();

    if(frameType < (int)_frameArray.size())
    {
        auto cArray = _frameArray.at(frameType);
        cArray->pushBack(frame);
    }
}

void ActionNode::deleteFrame(ActionFrame* frame)
{
    if (frame == nullptr)
    {
        return;
    }
    int frameType = frame->getFrameType();
    if(frameType < (int)_frameArray.size())
    {
        auto cArray = _frameArray.at(frameType);
        cArray->eraseObject(frame);
    }
}

void ActionNode::clearAllFrame()
{
    for(auto array : _frameArray)
    {
        array->clear();
    }
}

Spawn * ActionNode::refreshActionProperty()
{
    if ( _object == nullptr )
    {
        return nullptr;
    }
    Vector<FiniteTimeAction*> cSpawnArray;

    for (int n = 0; n < _frameArrayNum; n++)
    {
        auto cArray = _frameArray.at(n);
        if (cArray->size() <= 0)
        {
            continue;
        }

        Vector<FiniteTimeAction*> cSequenceArray;
        auto frameCount = cArray->size();
		if(frameCount > 1)
 		{ 
 			for (int i = 0; i < frameCount; i++)
 			{
 				auto frame = cArray->at(i);
 				if (i == 0)
 				{
// #11173 Fixed every node of UI animation(json) is starting at frame 0.                     
//                  if (frame->getFrameIndex() > 0)
//				    {
//					    DelayTime* cDelayTime = DelayTime::create(frame->getFrameIndex() * getUnitTime());
//					    if (cDelayTime != nullptr)
//						    cSequenceArray.pushBack(static_cast<FiniteTimeAction*>(cDelayTime));
//				    }
 				}
 				else
 				{
 					auto srcFrame = cArray->at(i-1);
 					float duration = (frame->getFrameIndex() - srcFrame->getFrameIndex()) * getUnitTime();
 					Action* cAction = frame->getAction(duration);
 					if(cAction != nullptr)
 					cSequenceArray.pushBack(static_cast<FiniteTimeAction*>(cAction));
 				}
 			}
 		}
 		else if (frameCount == 1)
 		{
 			auto frame = cArray->at(0);
 			float duration = 0.0f;
 			Action* cAction = frame->getAction(duration);
 			if (cAction != nullptr)
 				cSequenceArray.pushBack(static_cast<FiniteTimeAction*>(cAction));
 		}
 		Sequence* cSequence = Sequence::create(cSequenceArray);
 		if (cSequence != nullptr)
 		{
 			cSpawnArray.pushBack(cSequence);
 		}
    }

    if (_action == nullptr)
    {
    CC_SAFE_RELEASE_NULL(_actionSpawn);
    }
    else
    {
    CC_SAFE_RELEASE_NULL(_action);
    CC_SAFE_RELEASE_NULL(_actionSpawn);
    }

    _actionSpawn = Spawn::create(cSpawnArray);
    CC_SAFE_RETAIN(_actionSpawn);
    return _actionSpawn;
}

void ActionNode::playAction()
{
    if ( _object == nullptr || _actionSpawn == nullptr)
    {
        return;
    }

    if (_action!=nullptr)
    {
        _action->release();
    }

    _action = Sequence::create(_actionSpawn, nullptr);
    _action->retain();

    this->runAction();

}

void ActionNode::runAction()
{
    Node* cNode = this->getActionNode();
    if (cNode != nullptr && _action != nullptr)
    {
        cNode->runAction(_action);
    }
}

void ActionNode::stopAction()
{
    Node* cNode = this->getActionNode();
    if (cNode != nullptr && _action != nullptr)
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
        auto cArray = _frameArray.at(n);
        if (cArray->empty())
        {
            continue;
        }
        bFindFrame = true;
        auto frame = cArray->at(0);
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
        auto cArray = _frameArray.at(n);
        if (cArray->empty())
        {
            continue;
        }
        bFindFrame = true;
        ssize_t lastInex = cArray->size() - 1;
        auto frame = cArray->at(lastInex);
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

    ActionFrame* srcFrame = nullptr;
    for (int n = 0; n < _frameArrayNum; n++)
    {
        auto cArray = _frameArray.at(n);
        if (cArray->empty())
        {
            continue;
        }
        ssize_t frameCount = cArray->size();
        for (int i = 0; i < frameCount; i++)
        {
            auto frame = cArray->at(i);

            if (frame->getFrameIndex()*getUnitTime() == fTime)
            {
                this->easingToFrame(1.0f,1.0f,nullptr,frame);
                bFindFrame = true;
                break;
            }
            else if (frame->getFrameIndex()*getUnitTime() > fTime)
            {
                if (i == 0)
                {
                    this->easingToFrame(1.0f,1.0f,nullptr,frame);
                    bFindFrame = false;
                }
                else
                {
                    srcFrame = cArray->at(i-1);
                    float duration = (frame->getFrameIndex() - srcFrame->getFrameIndex())*getUnitTime();
                    float delaytime = fTime - srcFrame->getFrameIndex()*getUnitTime();
                    this->easingToFrame(duration,1.0f,nullptr,srcFrame);
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
    Action* cAction = destFrame->getAction(duration,srcFrame);
    Node* cNode = this->getActionNode();
    if (cAction == nullptr || cNode == nullptr)
    {
        return;
    }   
    cAction->startWithTarget(cNode);
    cAction->update(delayTime);
}


bool ActionNode::isActionDoneOnce()
{
    if (_action == nullptr)
    {
        return true;
    }
    return _action->isDone();
}

}
