#ifndef __GAMECONTROLLER_TEST_H__
#define __GAMECONTROLLER_TEST_H__

#include "cocos2d.h"
#include "base/CCGameController.h"

class GameControllerTest : public cocos2d::Layer
{
public:
    virtual ~GameControllerTest();
    
    virtual bool init();  
    
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameControllerTest);

    void update(float dt);
    void onButtonPressed(cocos2d::Controller* controller, cocos2d::ControllerButtonInput* button, cocos2d::Event* event);
    void onButtonReleased(cocos2d::Controller* controller, cocos2d::ControllerButtonInput* button, cocos2d::Event* event);
    void onAxisValueChanged(cocos2d::Controller* controller, cocos2d::ControllerAxisInput* axis, cocos2d::Event* event);
private:
    cocos2d::Controller* _player1;
    cocos2d::Sprite* _actor;
    cocos2d::Label* _statusLabel;
    cocos2d::Label* _leftTriggerLabel;
    cocos2d::Label* _rightTriggerLabel;
    cocos2d::EventListenerController* _listener;
};

#endif // __GAMECONTROLLER_TEST_H__
