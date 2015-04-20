/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
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

#ifndef _MENU_TEST_H_
#define _MENU_TEST_H_

////----#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(MenuTests);

class MenuTest : public TestCase
{
public:
    CREATE_FUNC(MenuTest);

    virtual bool init() override;
};

class MenuLayerMainMenu : public cocos2d::Layer
{
protected:
    cocos2d::MenuItem*    _disabledItem;
    cocos2d::EventListenerTouchOneByOne* _touchListener;

public:
    MenuLayerMainMenu();
    ~MenuLayerMainMenu();

public:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

    void allowTouches(float dt);
    void menuCallback(cocos2d::Ref* sender);
    void menuCallbackConfig(cocos2d::Ref* sender);
    void menuCallbackDisabled(cocos2d::Ref* sender);
    void menuCallback2(cocos2d::Ref* sender);
    void menuCallbackPriorityTest(cocos2d::Ref* sender);
    void menuCallbackBugsTest(cocos2d::Ref* pSender);
    void onQuit(cocos2d::Ref* sender);
    void menuMovingCallback(cocos2d::Ref* pSender);

    //CREATE_NODE(MenuLayer1);
};

class MenuLayer2 : public cocos2d::Layer
{
protected:
    cocos2d::Vec2        _centeredMenu;
    bool                _alignedH; 

    void alignMenusH();
    void alignMenusV();

public:
    MenuLayer2();
    ~MenuLayer2();

    void menuCallback(cocos2d::Ref* sender);
    void menuCallbackOpacity(cocos2d::Ref* sender);
    void menuCallbackAlign(cocos2d::Ref* sender);

    //CREATE_NODE(MenuLayer2);
};

class MenuLayer3 : public cocos2d::Layer
{
protected:
    cocos2d::MenuItem*    _disabledItem;

public:
    MenuLayer3();
    ~MenuLayer3();
};

class MenuLayer4 : public cocos2d::Layer
{
public:
    MenuLayer4();
    ~MenuLayer4();

    void menuCallback(cocos2d::Ref* sender);
    void backCallback(cocos2d::Ref* sender);
};

class BugsTest : public cocos2d::Layer
{
public:
    BugsTest();
    
    void issue1410MenuCallback(cocos2d::Ref* pSender);
    void issue1410v2MenuCallback(cocos2d::Ref* pSender);
    void backMenuCallback(cocos2d::Ref* pSender);
};

class RemoveMenuItemWhenMove : public cocos2d::Layer
{
public:
    RemoveMenuItemWhenMove();
    ~RemoveMenuItemWhenMove();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void goBack(cocos2d::Ref* pSender);
    
private:
    cocos2d::MenuItemFont *item;
    cocos2d::EventListenerTouchOneByOne* _touchListener;
};

#endif
