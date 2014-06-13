#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "base/CCGameController.h"

class HelloWorld : public cocos2d::Layer
{
public:
    virtual ~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    void update(float dt);
    void onButtonPressed(cocos2d::Controller* controller, cocos2d::ControllerButtonInput* button, cocos2d::Event* event);
    void onButtonReleased(cocos2d::Controller* controller, cocos2d::ControllerButtonInput* button, cocos2d::Event* event);
    void onAxisValueChanged(cocos2d::Controller* controller, cocos2d::ControllerAxisInput* axis, cocos2d::Event* event);
private:
    cocos2d::Controller* _player1;
    cocos2d::Sprite* _actor;
    cocos2d::Label* _statusLabel;
    cocos2d::EventListenerController* _listener;
};

#endif // __HELLOWORLD_SCENE_H__
