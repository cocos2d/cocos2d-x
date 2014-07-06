/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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

#include "CCTouchTargetNode.h"


NS_CC_BEGIN

CCTouchTargetNode *CCTouchTargetNode::create(CCNode *node)
{
    CCTouchTargetNode *touchableNode = new CCTouchTargetNode(node);
    touchableNode->autorelease();
    return touchableNode;
}

CCTouchTargetNode::CCTouchTargetNode(CCNode *node)
: m_touchId(0)
{
    m_node = node;
    m_node->retain();
    m_touchMode = node->getTouchMode();
}

CCTouchTargetNode::~CCTouchTargetNode()
{
    CC_SAFE_RELEASE(m_node);
}

CCNode *CCTouchTargetNode::getNode()
{
    return  m_node;
}

int CCTouchTargetNode::getTouchMode()
{
    return m_touchMode;
}

int CCTouchTargetNode::getTouchId()
{
    return m_touchId;
}

void CCTouchTargetNode::setTouchId(int touchId)
{
    m_touchId = touchId;
}

CCTouch *CCTouchTargetNode::findTouch(CCSet *touches)
{
    return findTouchFromTouchesSet(touches, getTouchId());
}

CCTouch *CCTouchTargetNode::findTouchFromTouchesSet(CCSet *touches, int touchId)
{
    CCTouch *touch = NULL;
    for (CCSetIterator it = touches->begin(); it != touches->end(); ++it)
    {
        touch = (CCTouch*)*it;
        if (touch->getID() == touchId) return touch;
    }
    return NULL;
}

NS_CC_END
