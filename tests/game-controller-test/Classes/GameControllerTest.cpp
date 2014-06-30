#include "GameControllerTest.h"
#include "AppMacros.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


Scene* GameControllerTest::scene()
{
    auto scene = Scene::create();
    GameControllerTest *layer = GameControllerTest::create();
    scene->addChild(layer);
    
    return scene;
}

GameControllerTest::~GameControllerTest()
{
    Controller::stopDiscoveryController();
}

bool GameControllerTest::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto tmpPos = Vec2(visibleSize / 2) + origin;
    _actor = Sprite::create("CloseNormal.png");
    _actor->setPosition(tmpPos);
    this->addChild(_actor,10);

    tmpPos.y -= 35;
    _statusLabel = Label::createWithTTF("status", "fonts/Marker Felt.ttf", 40);
    _statusLabel->setPosition(tmpPos);
    this->addChild(_statusLabel, 0, 100);

    tmpPos.y += 65;
    _leftTriggerLabel = Label::createWithTTF("left trigger", "fonts/Marker Felt.ttf", 40);
    _leftTriggerLabel->setPosition(tmpPos);
    this->addChild(_leftTriggerLabel, 0, 100);

    tmpPos.y += 40;
    _rightTriggerLabel = Label::createWithTTF("right trigger", "fonts/Marker Felt.ttf", 40);
    _rightTriggerLabel->setPosition(tmpPos);
    this->addChild(_rightTriggerLabel, 0, 100);

    _listener = EventListenerController::create();
    _listener->onConnected = [=](Controller* controller, Event* event){
        _player1 = controller;
        _statusLabel->setString("controller connected!");
    };

    _listener->onDisconnected = [=](Controller* controller, Event* event){
        _player1 = nullptr;
        _statusLabel->setString("controller disconnected!");
    };

    _listener->onButtonPressed = CC_CALLBACK_3(GameControllerTest::onButtonPressed, this);
    _listener->onButtonReleased = CC_CALLBACK_3(GameControllerTest::onButtonReleased, this);
    _listener->onAxisValueChanged = CC_CALLBACK_3(GameControllerTest::onAxisValueChanged, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    Controller::startDiscoveryController();
    
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameControllerTest::menuCloseCallback, this));
    closeItem->setPosition(origin + visibleSize - closeItem->getContentSize() / 2);
    
    auto menu = Menu::create(closeItem,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    //get game pad status in polling mode
    scheduleUpdate();

    return true;
}

void GameControllerTest::onButtonPressed(cocos2d::Controller *controller, cocos2d::ControllerButtonInput *button, cocos2d::Event *event)
{
    if (controller == nullptr)
    {
        return;
    }
    _player1 = controller;

    auto gamePad = controller->getGamepad();

    if (button == gamePad->getButtonA())
    {
        _statusLabel->setString("button A pressed!");
    }

    if (button == gamePad->getButtonB())
    {
        _statusLabel->setString("button B pressed!");
    }

    if (button == gamePad->getButtonX())
    {
        _statusLabel->setString("button X pressed!");
    }

    if (button == gamePad->getButtonY())
    {
        _statusLabel->setString("button Y pressed!");
    }

    if (button == gamePad->getDirectionPad()->getUp())
    {
        _statusLabel->setString("Dpad up pressed!");
    }

    if (button == gamePad->getDirectionPad()->getDown())
    {
        _statusLabel->setString("Dpad down pressed!");
    }

    if (button == gamePad->getDirectionPad()->getLeft())
    {
        _statusLabel->setString("Dpad left pressed!");
    }

    if (button == gamePad->getDirectionPad()->getRight())
    {
        _statusLabel->setString("Dpad right pressed!");
    }

    if (button == gamePad->getLeftShoulder())
    {
        _statusLabel->setString("Left shoulder pressed!");
    }

    if (button == gamePad->getRightShoulder())
    {
        _statusLabel->setString("Right shoulder pressed!");
    }
}

void GameControllerTest::onButtonReleased(cocos2d::Controller *controller, cocos2d::ControllerButtonInput *button, cocos2d::Event *event)
{
    if (controller == nullptr)
    {
        return;
    }
    _player1 = controller;

    auto gamePad = controller->getGamepad();

    if (button == gamePad->getButtonA())
    {
        _statusLabel->setString("button A released!");
    }

    if (button == gamePad->getButtonB())
    {
        _statusLabel->setString("button B released!");
    }

    if (button == gamePad->getButtonX())
    {
        _statusLabel->setString("button X released!");
    }

    if (button == gamePad->getButtonY())
    {
        _statusLabel->setString("button Y released!");
    }

    if (button == gamePad->getDirectionPad()->getUp())
    {
        _statusLabel->setString("Dpad up released!");
    }

    if (button == gamePad->getDirectionPad()->getDown())
    {
        _statusLabel->setString("Dpad down released!");
    }

    if (button == gamePad->getDirectionPad()->getLeft())
    {
        _statusLabel->setString("Dpad left released!");
    }

    if (button == gamePad->getDirectionPad()->getRight())
    {
        _statusLabel->setString("Dpad right released!");
    }

    if (button == gamePad->getLeftShoulder())
    {
        _statusLabel->setString("Left shoulder released!");
    }

    if (button == gamePad->getRightShoulder())
    {
        _statusLabel->setString("Right shoulder released!");
    }
}

void GameControllerTest::onAxisValueChanged(cocos2d::Controller* controller, cocos2d::ControllerAxisInput* axis, cocos2d::Event* event)
{
    if (controller == nullptr)
    {
        return;
    }
    _player1 = controller;

    auto moveDelta = axis->getValue();
    Vec2 newPos = _actor->getPosition();
    auto gamePad = controller->getGamepad();

    if (axis == gamePad->getLeftThumbstick()->getAxisX() || axis == gamePad->getRightThumbstick()->getAxisX())
    {
        newPos.x += moveDelta;
    }
    else if (axis == gamePad->getLeftThumbstick()->getAxisY() || axis == gamePad->getRightThumbstick()->getAxisY())
    {
        newPos.y -= moveDelta;
    }
    _actor->setPosition(newPos);
}

void GameControllerTest::update(float dt)
{
    if (_player1 && _player1->isConnected())
    {
        Vec2 newPos = _actor->getPosition();
        auto gamePad = _player1->getGamepad();

        newPos.x += gamePad->getLeftThumbstick()->getAxisX()->getValue();
        newPos.y -= gamePad->getLeftThumbstick()->getAxisY()->getValue();

        newPos.x += gamePad->getRightThumbstick()->getAxisX()->getValue();
        newPos.y -= gamePad->getRightThumbstick()->getAxisY()->getValue();

        _actor->setPosition(newPos);

        char triggerStatus[50];
        sprintf(triggerStatus,"left trigger:%f",gamePad->getLeftTrigger()->getValue());
        _leftTriggerLabel->setString(triggerStatus);
        sprintf(triggerStatus,"right trigger:%f",gamePad->getRightTrigger()->getValue());
        _rightTriggerLabel->setString(triggerStatus);
    }
}

void GameControllerTest::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}