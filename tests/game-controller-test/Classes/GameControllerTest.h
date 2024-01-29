/****************************************************************************
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

#ifndef __GAMECONTROLLER_TEST_H__
#define __GAMECONTROLLER_TEST_H__

#include "cocos2d.h"
#include "base/CCGameController.h"

USING_NS_CC;

class GameControllerTest : public cocos2d::Layer
{
public:
    virtual ~GameControllerTest();
    
    CREATE_FUNC(GameControllerTest);

    virtual bool init();
    
    void onKeyDown(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event);
    void onKeyUp(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event);
    void onAxisEvent(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event);
    
    void menuCloseCallback(Ref* sender);
    
private:
    float _visibleCentreX;
    float _visibleCentreY;
    float _visibleQuarterX;
    float _visibleThreeQuarterX;

    int _currControllerCount;

    typedef struct controllerHolder
    {
        cocos2d::Controller *controller;

        cocos2d::Node* _holderNode;

        cocos2d::Sprite* _leftJoystick;
        cocos2d::Sprite* _rightJoystick;

        cocos2d::Sprite* _dpadLeft;
        cocos2d::Sprite* _dpadRight;
        cocos2d::Sprite* _dpadUp;
        cocos2d::Sprite* _dpadDown;

        cocos2d::Sprite* _buttonX;
        cocos2d::Sprite* _buttonY;
        cocos2d::Sprite* _buttonA;
        cocos2d::Sprite* _buttonB;

        cocos2d::Sprite* _buttonL1;
        cocos2d::Sprite* _buttonR1;
        cocos2d::Sprite* _buttonL2;
        cocos2d::Sprite* _buttonR2;

        cocos2d::Label* _deviceLabel;
        cocos2d::Label* _externalKeyLabel;
    }ControllerHolder;

    ControllerHolder _firstHolder;
    ControllerHolder _secondHolder;

    cocos2d::EventListenerController* _listener;

    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _visibleOrigin;

    void registerControllerListener();
    void showButtonState(cocos2d::Controller *controller, int keyCode, bool isPressed);

    void createControllerSprite(ControllerHolder& holder);

    void onConnectController(Controller* controller, Event* event);
    void onDisconnectedController(Controller* controller, Event* event);

    void resetControllerHolderState(ControllerHolder& holder);
};

#endif // __GAMECONTROLLER_TEST_H__
