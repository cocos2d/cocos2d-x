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

#ifndef __LUA_TOUCH_TARGET_NODE_H_
#define __LUA_TOUCH_TARGET_NODE_H_

#include "LuaEventNode.h"

NS_CC_BEGIN

/**
 * @addtogroup scene
 * @{
 */

class LuaTouchTargetNode : public Ref
{
public:
    static LuaTouchTargetNode *create(LuaEventNode *node);
    ~LuaTouchTargetNode();

    LuaEventNode *getNode();

    int getTouchMode();

    int getTouchId();
    void setTouchId(int touchId);

    Touch *findTouch(const std::vector<Touch*>& touches);
    static Touch *findTouchFromTouchesSet(const std::vector<Touch*>& touches, int touchId);

private:
    LuaTouchTargetNode(LuaEventNode *node);

    LuaEventNode *_node;
    int _touchMode;
    int _touchId;
};

NS_CC_END

#endif // __LUA_TOUCH_TARGET_NODE_H_
