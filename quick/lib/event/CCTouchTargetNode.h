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

#ifndef __CCTOUCH_TARGET_NODE_H_
#define __CCTOUCH_TARGET_NODE_H_

#include "2d/CCNode.h"

NS_CC_BEGIN

/**
 * @addtogroup scene
 * @{
 */

class CC_DLL CCTouchTargetNode : public Ref
{
public:
    static CCTouchTargetNode *create(Node *node);
    ~CCTouchTargetNode();

    Node *getNode();

    int getTouchMode();

    int getTouchId();
    void setTouchId(int touchId);

    Touch *findTouch(const std::vector<Touch*>& touches);
    static Touch *findTouchFromTouchesSet(const std::vector<Touch*>& touches, int touchId);

private:
    CCTouchTargetNode(Node *node);

    Node *m_node;
    int m_touchMode;
    int m_touchId;
};

NS_CC_END

#endif // __CCTOUCH_TARGET_NODE_H_
