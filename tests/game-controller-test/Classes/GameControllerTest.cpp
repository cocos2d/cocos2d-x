#include "GameControllerTest.h"
#include "AppMacros.h"

USING_NS_CC;

GameControllerTest::~GameControllerTest()
{
    Controller::stopDiscoveryController();
}

void GameControllerTest::registerControllerListener()
{
    _listener = EventListenerController::create();

    _listener->onConnected = CC_CALLBACK_2(GameControllerTest::onConnectController,this);
    _listener->onDisconnected = CC_CALLBACK_2(GameControllerTest::onDisconnectedController,this);
    _listener->onKeyDown = CC_CALLBACK_3(GameControllerTest::onKeyDown, this);
    _listener->onKeyUp = CC_CALLBACK_3(GameControllerTest::onKeyUp, this);
    _listener->onAxisEvent = CC_CALLBACK_3(GameControllerTest::onAxisEvent, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    Controller::startDiscoveryController();

    //get game pad status in polling mode
    //scheduleUpdate();
}

void GameControllerTest::onConnectController(Controller* controller, Event* event)
{
    if (controller == nullptr || controller == _firstHolder.controller || controller == _secondHolder.controller)
    {
        return;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //receive back key
    controller->receiveExternalKeyEvent(4,true);
    //receive menu key
    controller->receiveExternalKeyEvent(82,true);
#endif

    char deviceInfo[50];
    sprintf(deviceInfo,"%s id:%d",controller->getDeviceName().c_str(), controller->getDeviceId());

    if (_firstHolder.controller == nullptr && _secondHolder.controller == nullptr)
    {
        if (_firstHolder._holderNode)
        {
            _firstHolder.controller = controller;
            _firstHolder._deviceLabel->setString(deviceInfo);
        }
        else
        {
            _secondHolder.controller = controller;
            _secondHolder._deviceLabel->setString(deviceInfo);
        }
    }
    else if(_secondHolder.controller == nullptr)
    {
        _secondHolder.controller = controller;
        if (_secondHolder._holderNode == nullptr)
        {
            createControllerSprite(_secondHolder);

            _firstHolder._holderNode->runAction(ScaleTo::create(0.3f,0.5f,0.5f));
            _firstHolder._holderNode->runAction(MoveTo::create(0.3f,Vec2(_visibleQuarterX, _visibleCentreY)));

            _secondHolder._holderNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            _secondHolder._holderNode->setScale(0.1f);
            _secondHolder._holderNode->runAction(ScaleTo::create(0.3f,0.5f,0.5f));
            _secondHolder._holderNode->setPosition(_visibleThreeQuarterX, _visibleCentreY);
            this->addChild(_secondHolder._holderNode);
        }

        _secondHolder._deviceLabel->setString(deviceInfo);
    }
    else
    {
        _firstHolder.controller = controller;
        if (_firstHolder._holderNode == nullptr)
        {
            createControllerSprite(_firstHolder);

            _secondHolder._holderNode->runAction(ScaleTo::create(0.3f,0.5f,0.5f));
            _secondHolder._holderNode->runAction(MoveTo::create(0.3f,Vec2(_visibleQuarterX, _visibleCentreY)));

            _firstHolder._holderNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            _firstHolder._holderNode->setScale(0.1f);
            _firstHolder._holderNode->runAction(ScaleTo::create(0.3f,0.5f,0.5f));
            _firstHolder._holderNode->setPosition(_visibleThreeQuarterX, _visibleCentreY);
            this->addChild(_firstHolder._holderNode);
        }

        _firstHolder._deviceLabel->setString(deviceInfo);
    }
}

void GameControllerTest::onDisconnectedController(Controller* controller, Event* event)
{
    log("onDisconnectedController:%d",controller->getDeviceId());
    if (_firstHolder.controller == controller)
    {
        _firstHolder.controller = nullptr;

        if (_secondHolder.controller != nullptr)
        {
            _firstHolder._holderNode->runAction(MoveBy::create(0.3f,Vec2(0,_visibleSize.height)));

            _secondHolder._holderNode->runAction(MoveTo::create(0.3f,Vec2(_visibleCentreX,_visibleCentreY) ));
            _secondHolder._holderNode->runAction(ScaleTo::create(0.3f,1.0f,1.0f));
        }
        else
        {
            resetControllerHolderState(_firstHolder);
        }
    }
    else if (_secondHolder.controller == controller)
    {
        _secondHolder.controller = nullptr;

        if (_firstHolder.controller != nullptr)
        {
            _secondHolder._holderNode->runAction(MoveBy::create(0.3f,Vec2(0,_visibleSize.height)));

            _firstHolder._holderNode->runAction(MoveTo::create(0.3f,Vec2(_visibleCentreX,_visibleCentreY) ));
            _firstHolder._holderNode->runAction(ScaleTo::create(0.3f,1.0f,1.0f));
        }
        else
        {
            resetControllerHolderState(_secondHolder);
        }
    }
}

void GameControllerTest::resetControllerHolderState(ControllerHolder& holder)
{
    holder._buttonA->setColor(Color3B::WHITE);
    holder._buttonB->setColor(Color3B::WHITE);
    holder._buttonX->setColor(Color3B::WHITE);
    holder._buttonY->setColor(Color3B::WHITE);
    holder._dpadUp->setColor(Color3B::WHITE);
    holder._dpadDown->setColor(Color3B::WHITE);
    holder._dpadLeft->setColor(Color3B::WHITE);
    holder._dpadRight->setColor(Color3B::WHITE);
    holder._buttonL1->setColor(Color3B::WHITE);
    holder._buttonR1->setColor(Color3B::WHITE);

    holder._leftJoystick->setPosition(238,460);
    holder._rightJoystick->setPosition(606,293);
    holder._deviceLabel->setString("Disconnected");
}

void GameControllerTest::showButtonState(cocos2d::Controller *controller, int keyCode, bool isPressed)
{
    onConnectController(controller,nullptr);
    ControllerHolder* holder = nullptr;
    if (controller == _firstHolder.controller)
        holder = &_firstHolder;
    else if(controller == _secondHolder.controller)
        holder = &_secondHolder;
    else
        return;

    if (isPressed)
    {
        switch (keyCode)
        {
        case Controller::Key::BUTTON_A:
            holder->_buttonA->setColor(Color3B(250,103,93));
            break;
        case Controller::Key::BUTTON_B:
            holder->_buttonB->setColor(Color3B(92,214,183));
            break;
        case Controller::Key::BUTTON_X:
            holder->_buttonX->setColor(Color3B(96,113,192));
            break;
        case Controller::Key::BUTTON_Y:
            holder->_buttonY->setColor(Color3B(199,222,118));
            break;
        case Controller::Key::BUTTON_DPAD_UP:
            holder->_dpadUp->setColor(Color3B(0,115,158));
            break;
        case Controller::Key::BUTTON_DPAD_DOWN:
            holder->_dpadDown->setColor(Color3B(0,115,158));
            break;
        case Controller::Key::BUTTON_DPAD_LEFT:
            holder->_dpadLeft->setColor(Color3B(170,216,0));
            break;
        case Controller::Key::BUTTON_DPAD_RIGHT:
            holder->_dpadRight->setColor(Color3B(170,216,0));
            break;
        case Controller::Key::BUTTON_LEFT_SHOULDER:
            holder->_buttonL1->setColor(Color3B(19,231,238));
            break;
        case Controller::Key::BUTTON_RIGHT_SHOULDER:
            holder->_buttonR1->setColor(Color3B(19,231,238));
            break;
        case Controller::Key::BUTTON_LEFT_THUMBSTICK:
            holder->_leftJoystick->setColor(Color3B(19,231,238));
            break;
        case Controller::Key::BUTTON_RIGHT_THUMBSTICK:
            holder->_rightJoystick->setColor(Color3B(19,231,238));
            break;
        default:
            {
                char ketStatus[30];
                sprintf(ketStatus,"Key Down:%d",keyCode);
                holder->_externalKeyLabel->setString(ketStatus);
                break;
            }
        }
    } 
    else
    {
        switch (keyCode)
        {
        case Controller::Key::BUTTON_A:
            holder->_buttonA->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_B:
            holder->_buttonB->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_X:
            holder->_buttonX->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_Y:
            holder->_buttonY->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_DPAD_UP:
            holder->_dpadUp->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_DPAD_DOWN:
            holder->_dpadDown->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_DPAD_LEFT:
            holder->_dpadLeft->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_DPAD_RIGHT:
            holder->_dpadRight->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_LEFT_SHOULDER:
            holder->_buttonL1->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_RIGHT_SHOULDER:
            holder->_buttonR1->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_LEFT_THUMBSTICK:
            holder->_leftJoystick->setColor(Color3B::WHITE);
            break;
        case Controller::Key::BUTTON_RIGHT_THUMBSTICK:
            holder->_rightJoystick->setColor(Color3B::WHITE);
            break;
        default:
            {
                char ketStatus[30];
                sprintf(ketStatus,"Key Up:%d",keyCode);
                holder->_externalKeyLabel->setString(ketStatus);
                break;
            }
        }
    }
}

void GameControllerTest::onKeyDown(cocos2d::Controller *controller, int keyCode, cocos2d::Event *event)
{
    showButtonState(controller, keyCode, true);
}

void GameControllerTest::onKeyUp(cocos2d::Controller *controller, int keyCode, cocos2d::Event *event)
{
    showButtonState(controller, keyCode, false);
}

void GameControllerTest::onAxisEvent(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event)
{
    ControllerHolder* holder = nullptr;
    if (controller == _firstHolder.controller)
        holder = &_firstHolder;
    else if(controller == _secondHolder.controller)
        holder = &_secondHolder;
    else
        return;

    const auto& ketStatus = controller->getKeyStatus(keyCode);
    switch (keyCode)
    {
    case Controller::Key::JOYSTICK_LEFT_X:
        holder->_leftJoystick->setPositionX(238 + ketStatus.value * 24);
        break;
    case Controller::Key::JOYSTICK_LEFT_Y:
        holder->_leftJoystick->setPositionY(460 - ketStatus.value * 24);
        break;
    case Controller::Key::JOYSTICK_RIGHT_X:
        holder->_rightJoystick->setPositionX(606 + ketStatus.value * 24);
        break;
    case Controller::Key::JOYSTICK_RIGHT_Y:
        holder->_rightJoystick->setPositionY(293 - ketStatus.value * 24);
        break;
    case Controller::Key::AXIS_LEFT_TRIGGER:
        holder->_buttonL2->setOpacity(200 * controller->getKeyStatus(keyCode).value);
        break;
    case Controller::Key::AXIS_RIGHT_TRIGGER:
        holder->_buttonR2->setOpacity(200 * controller->getKeyStatus(keyCode).value);
        break;
    default:
        break;
    }
}

bool GameControllerTest::init()
{
    if ( !Layer::init() )
        return false;

    _currControllerCount = 0;

    _visibleSize = Director::getInstance()->getVisibleSize();
    _visibleOrigin = Director::getInstance()->getVisibleOrigin();


    auto tmpPos = Vec2(_visibleSize / 2) + _visibleOrigin;

    _visibleCentreX = _visibleOrigin.x + _visibleSize.width / 2;
    _visibleCentreY = _visibleOrigin.y + _visibleSize.height / 2;
    _visibleQuarterX = _visibleOrigin.x + _visibleSize.width / 4;
    _visibleThreeQuarterX = _visibleOrigin.x + _visibleSize.width * 0.75f;

    _firstHolder.controller = nullptr;
    _secondHolder.controller = nullptr;

    createControllerSprite(_firstHolder);
    _firstHolder._holderNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _firstHolder._holderNode->setPosition(tmpPos);
    this->addChild(_firstHolder._holderNode);

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameControllerTest::menuCloseCallback, this));
    closeItem->setPosition(_visibleOrigin + _visibleSize - closeItem->getContentSize() / 2);

    auto menu = Menu::create(closeItem,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    registerControllerListener();

    return true;
}

void GameControllerTest::createControllerSprite(ControllerHolder& holder)
{
    holder._holderNode = Node::create();
    holder._holderNode->setContentSize(Size(998,1000));

    auto controllerBg1 = Sprite::create("controller-1.png");
    controllerBg1->setPosition(Vec2::ZERO);
    controllerBg1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    holder._holderNode->addChild(controllerBg1);

    auto controllerBg2 = Sprite::create("controller-2.png");
    controllerBg2->setPosition(499,1000);
    controllerBg2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    holder._holderNode->addChild(controllerBg2);

    holder._leftJoystick = Sprite::create("joystick.png");
    holder._leftJoystick->setPosition(238,460);
    holder._holderNode->addChild(holder._leftJoystick);

    holder._rightJoystick = Sprite::create("joystick.png");
    holder._rightJoystick->setPosition(606,293);
    holder._holderNode->addChild(holder._rightJoystick);

    holder._deviceLabel = Label::createWithTTF("Disconnected","fonts/Marker Felt.ttf",36);
    holder._deviceLabel->setPosition(499,650);
    holder._deviceLabel->setTextColor(Color4B::RED);
    holder._holderNode->addChild(holder._deviceLabel);

    holder._externalKeyLabel = Label::createWithTTF("Key event","fonts/Marker Felt.ttf",36);
    holder._externalKeyLabel->setPosition(499,500);
    holder._externalKeyLabel->setTextColor(Color4B::RED);
    holder._holderNode->addChild(holder._externalKeyLabel);
    //-----------------------------------------------------------------
    auto dPadTexture = Director::getInstance()->getTextureCache()->addImage("dPad.png");

    auto dPadCenter = Sprite::createWithTexture(dPadTexture,Rect(60,60,68,68));
    dPadCenter->setPosition(371,294);
    holder._holderNode->addChild(dPadCenter);

    holder._dpadLeft = Sprite::createWithTexture(dPadTexture,Rect(0,60,60,60));
    holder._dpadLeft->setPosition(371 - 64,296);
    holder._holderNode->addChild(holder._dpadLeft);

    holder._dpadRight = Sprite::createWithTexture(dPadTexture,Rect(128,60,60,60));
    holder._dpadRight->setPosition(371 + 64,296);
    holder._holderNode->addChild(holder._dpadRight);

    holder._dpadUp = Sprite::createWithTexture(dPadTexture,Rect(60,0,60,60));
    holder._dpadUp->setPosition(369,294 + 64);
    holder._holderNode->addChild(holder._dpadUp);

    holder._dpadDown = Sprite::createWithTexture(dPadTexture,Rect(60,128,60,60));
    holder._dpadDown->setPosition(369,294 - 64);
    holder._holderNode->addChild(holder._dpadDown);
    //-----------------------------------------------------------------
    holder._buttonL1 = Sprite::create("L1.png");
    holder._buttonL1->setPosition(290,792);
    holder._holderNode->addChild(holder._buttonL1);

    holder._buttonR1 = Sprite::create("R1.png");
    holder._buttonR1->setPosition(998 - 290,792);
    holder._holderNode->addChild(holder._buttonR1);

    auto buttonL2 = Sprite::create("L2.png");
    buttonL2->setPosition(220,910);
    holder._holderNode->addChild(buttonL2);

    auto buttonR2 = Sprite::create("R2.png");
    buttonR2->setPosition(998-220,910);
    holder._holderNode->addChild(buttonR2);

    holder._buttonL2 = Sprite::create("L2.png");
    holder._buttonL2->setOpacity(0);
    holder._buttonL2->setColor(Color3B::RED);
    holder._buttonL2->setPosition(220,910);
    holder._holderNode->addChild(holder._buttonL2);

    holder._buttonR2 = Sprite::create("R2.png");
    holder._buttonR2->setOpacity(0);
    holder._buttonR2->setColor(Color3B::RED);
    holder._buttonR2->setPosition(998-220,910);
    holder._holderNode->addChild(holder._buttonR2);
    //-----------------------------------------------------------------
    holder._buttonX = Sprite::create("X.png");
    holder._buttonX->setPosition(750 - 70,460);
    holder._holderNode->addChild(holder._buttonX);

    holder._buttonY = Sprite::create("Y.png");
    holder._buttonY->setPosition(750,460 + 70);
    holder._holderNode->addChild(holder._buttonY);

    holder._buttonA = Sprite::create("A.png");
    holder._buttonA->setPosition(750,460 - 70);
    holder._holderNode->addChild(holder._buttonA);

    holder._buttonB = Sprite::create("B.png");
    holder._buttonB->setPosition(750 + 70,460);
    holder._holderNode->addChild(holder._buttonB);
}

void GameControllerTest::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}