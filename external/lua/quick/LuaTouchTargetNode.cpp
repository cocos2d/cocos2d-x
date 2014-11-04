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

#include "LuaTouchTargetNode.h"


NS_CC_BEGIN

LuaTouchTargetNode *LuaTouchTargetNode::create(LuaEventNode *node)
{
    LuaTouchTargetNode *touchableNode = new LuaTouchTargetNode(node);
    touchableNode->autorelease();
    return touchableNode;
}

LuaTouchTargetNode::LuaTouchTargetNode(LuaEventNode *node)
: _touchId(0)
{
    _node = node;
    _node->retain();
    _touchMode = node->getTouchMode();
}

LuaTouchTargetNode::~LuaTouchTargetNode()
{
    CC_SAFE_RELEASE(_node);
}

LuaEventNode *LuaTouchTargetNode::getNode()
{
    return  _node;
}

int LuaTouchTargetNode::getTouchMode()
{
    return _touchMode;
}

int LuaTouchTargetNode::getTouchId()
{
    return _touchId;
}

void LuaTouchTargetNode::setTouchId(int touchId)
{
    _touchId = touchId;
}

Touch *LuaTouchTargetNode::findTouch(const std::vector<Touch*>& touches)
{
    return findTouchFromTouchesSet(touches, getTouchId());
}

Touch *LuaTouchTargetNode::findTouchFromTouchesSet(const std::vector<Touch*>& touches, int touchId)
{
    Touch *touch = nullptr;
    for (auto it = touches.begin(); it != touches.end(); ++it)
    {
        touch = (Touch*)*it;
        if (touch->getID() == touchId) return touch;
    }
    return nullptr;
}

NS_CC_END
