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

#ifndef __cocos2d_tests__CocostudioParserTest__
#define __cocos2d_tests__CocostudioParserTest__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../../testBasic.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class CocostudioParserTestMainLayer : public Layer
{
public:
    virtual void onEnter();
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    
    void touchEvent(Ref* pSender, Widget::TouchEventType type);
    
private:
    Vec2 _beginPos;
    Menu* _itemMenu;
};

class CocostudioParserTestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(Ref* pSender);
};

#endif /* defined(__cocos2d_tests__CocostudioParserTest__) */
