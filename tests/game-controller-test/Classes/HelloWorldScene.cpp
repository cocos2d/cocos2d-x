#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "nslog/CCNSLog.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


Scene* HelloWorld::scene()
{
    auto scene = Scene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    
    return scene;
}

HelloWorld::~HelloWorld()
{
    Controller::stopDiscoveryController();
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    _player1 = nullptr;

    _statusLabel = Label::createWithTTF("status:", "fonts/en.ttf", 40);
    _statusLabel->setPosition(Vec2(visibleSize / 2) + origin + Vec2(0, 25));
    this->addChild(_statusLabel, 0, 100);
    
    _actor = Sprite::create("CloseNormal.png");
    _actor->setPosition(Vec2(visibleSize / 2) + origin);
    this->addChild(_actor);

    Controller::startDiscoveryController();
    
    auto controllers = Controller::getControllers();
    if (!controllers.empty()) {
        _player1 = controllers[0];
        _statusLabel->setString("controller connected!");
    }
    
    _listener = EventListenerController::create();
    _listener->onConnected = [=](Controller* controller, Event* event){
        CCNSLOG("%p connected", controller);
        _player1 = controller;
        _statusLabel->setString("controller connected!");
    };

    _listener->onDisconnected = [=](Controller* controller, Event* event){
        CCNSLOG("%p disconnected", controller);
        _player1 = nullptr;
        _statusLabel->setString("controller disconnected!");
    };

    _listener->onButtonPressed = CC_CALLBACK_3(HelloWorld::onButtonPressed, this);
    _listener->onButtonReleased = CC_CALLBACK_3(HelloWorld::onButtonReleased, this);
    _listener->onAxisValueChanged = CC_CALLBACK_3(HelloWorld::onAxisValueChanged, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    auto bullet = Sprite::create("CloseSelected.png");
    bullet->setPosition(_actor->getPosition() + Vec2(0, _actor->getContentSize().height/2 + 20));
    this->addChild(bullet);
    bullet->setColor(Color3B::BLUE);
    
    auto closeItem = MenuItemImage::create("", "", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(origin + visibleSize - closeItem->getContentSize() / 2);
    
    auto menu = Menu::create(closeItem,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    //get game pad status in polling mode
    scheduleUpdate();

    return true;
}

void HelloWorld::onButtonPressed(cocos2d::Controller *controller, cocos2d::ControllerButtonInput *button, cocos2d::Event *event)
{
    CCNSLOG("HelloWorld::onButtonPressed: %p, %d, %f", button, button->isPressed(), button->getValue());
    
    if (_player1 == nullptr)
    {
        if (controller != nullptr)
            _player1 = controller;
        else
            return;
    }

    if (button == _player1->getGamepad()->getButtonA())
    {
        _statusLabel->setString("button A pressed!");
    }

    if (button == _player1->getGamepad()->getButtonB())
    {
        _statusLabel->setString("button B pressed!");
    }

    if (button == _player1->getGamepad()->getButtonX())
    {
        _statusLabel->setString("button X pressed!");
    }

    if (button == _player1->getGamepad()->getButtonY())
    {
        _statusLabel->setString("button Y pressed!");
    }

    if (button == _player1->getGamepad()->getDirectionPad()->getUp())
    {
        _statusLabel->setString("Dpad up pressed!");
    }

    if (button == _player1->getGamepad()->getDirectionPad()->getDown())
    {
        _statusLabel->setString("Dpad down pressed!");
    }

    if (button == _player1->getGamepad()->getDirectionPad()->getLeft())
    {
        _statusLabel->setString("Dpad left pressed!");
    }

    if (button == _player1->getGamepad()->getDirectionPad()->getRight())
    {
        _statusLabel->setString("Dpad right pressed!");
    }


    Size winSize = Director::getInstance()->getWinSize();

    int randX = rand() % static_cast<int>(winSize.width);

    auto bullet = Sprite::create("CloseSelected.png");
    bullet->setPosition(_actor->getPosition() + Vec2(0, _actor->getContentSize().height/2));
    this->addChild(bullet);
    bullet->setColor(Color3B::BLUE);
    bullet->runAction(Sequence::create(MoveTo::create(3.0f, Vec2(randX, winSize.height)), RemoveSelf::create(),  NULL));
}

void HelloWorld::onButtonReleased(cocos2d::Controller *controller, cocos2d::ControllerButtonInput *button, cocos2d::Event *event)
{
    CCNSLOG("HelloWorld::onButtonReleased: %p, %d, %f", button, button->isPressed(), button->getValue());
    
    if (_player1 == nullptr)
    {
        if (controller != nullptr)
            _player1 = controller;
        else
            return;
    }

    Size winSize = Director::getInstance()->getWinSize();

    int randX = rand() % static_cast<int>(winSize.width);

    auto bullet = Sprite::create("CloseSelected.png");
    bullet->setPosition(_actor->getPosition() + Vec2(0, _actor->getContentSize().height/2));
    bullet->setColor(Color3B::RED);
    this->addChild(bullet);
    bullet->runAction(Sequence::create(MoveTo::create(3.0f, Vec2(randX, winSize.height)), RemoveSelf::create(),  NULL));
}

void HelloWorld::onAxisValueChanged(cocos2d::Controller* controller, cocos2d::ControllerAxisInput* axis, cocos2d::Event* event)
{
    if (_player1 == nullptr)
    {
        if (controller != nullptr)
            _player1 = controller;
        else
            return;
    }

    const int MOVE_DELTA = axis->getValue();
    Vec2 newPos = _actor->getPosition();

    if (axis == _player1->getGamepad()->getLeftThumbstick()->getAxisX() || axis == _player1->getGamepad()->getRightThumbstick()->getAxisX())
    {
        newPos.x += MOVE_DELTA;
    }
    else if (axis == _player1->getGamepad()->getLeftThumbstick()->getAxisY() || axis == _player1->getGamepad()->getRightThumbstick()->getAxisY())
    {
        newPos.y -= MOVE_DELTA;
    }
    _actor->setPosition(newPos);
}

void HelloWorld::update(float dt)
{
    if (_player1 && _player1->isConnected())
    {
        const int MOVE_DELTA = dt * 100;

        Vec2 newPos = _actor->getPosition();

        if (_player1->getGamepad()->getDirectionPad()->getDown()->isPressed())
        {
            _statusLabel->setString("Dpad: down pressed");
            newPos.y -= MOVE_DELTA;
        }
        
        if (_player1->getGamepad()->getDirectionPad()->getUp()->isPressed())
        {
            _statusLabel->setString("Dpad: up pressed");
            newPos.y += MOVE_DELTA;
        }
        
        if (_player1->getGamepad()->getDirectionPad()->getLeft()->isPressed())
        {
            _statusLabel->setString("Dpad: left pressed");
            newPos.x -= MOVE_DELTA;
        }
        
        if (_player1->getGamepad()->getDirectionPad()->getRight()->isPressed())
        {
            _statusLabel->setString("Dpad: right pressed");
            newPos.x += MOVE_DELTA;
        }

        newPos.x += _player1->getGamepad()->getLeftThumbstick()->getAxisX()->getValue();
        newPos.y -= _player1->getGamepad()->getLeftThumbstick()->getAxisY()->getValue();

        newPos.x += _player1->getGamepad()->getRightThumbstick()->getAxisX()->getValue();
        newPos.y -= _player1->getGamepad()->getRightThumbstick()->getAxisY()->getValue();

        _actor->setPosition(newPos);
    }
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}