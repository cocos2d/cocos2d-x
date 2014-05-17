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

#include "cocostudio/CCActionNode.h"
#include "cocostudio/CCActionFrameEasing.h"
#include "cocostudio/DictionaryHelper.h"
#include "ui/UIWidget.h"
#include "ui/UIHelper.h"

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
    }

    for (auto object : _frameArray)
    {
        object->clear();
        CC_SAFE_DELETE(object);
    }
    _frameArray.clear();
}

void ActionNode::initWithDictionary(const rapidjson::Value& dic, Ref* root)
{
    setActionTag(DICTOOL->getIntValue_json(dic, "ActionTag"));
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
            ActionMoveFrame* actionFrame = new ActionMoveFrame();
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
            ActionScaleFrame* actionFrame = new ActionScaleFrame();
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
            ActionRotationFrame* actionFrame = new ActionRotationFrame();
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
            ActionFadeFrame* actionFrame = new ActionFadeFrame();
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
            ActionTintFrame* actionFrame = new ActionTintFrame();
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

void ActionNode::initActionNodeFromRoot(Ref* root)
{	
    Node* rootNode = dynamic_cast<Node*>(root);
    if (rootNode != nullptr)
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
    _object = node;
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
    else
    {
        Widget* rootWidget = dynamic_cast<Widget*>(_object);
        if (rootWidget != nullptr)
        {
            return rootWidget;
        }
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
        for (int i = 0; i < frameCount; i++)
        {
            auto frame = cArray->at(i);
            if (i == 0)
            {
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
