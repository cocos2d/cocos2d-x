#include "HelloWorldScene.h"
#include "AppMacros.h"
//#include "CCNSLog.h"

USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::~HelloWorld()
{
    //_eventDispatcher->removeEventListener(_listener);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    //_player1 = nullptr;

    /*_statusLabel = Label::createWithTTF("status:", "fonts/Marker Felt.ttf", 20);
    _statusLabel->setPosition(Vec2(visibleSize / 2) + origin + Vec2(0, 50));
    this->addChild(_statusLabel, 0, 100);*/

    _strMap = FileUtils::getInstance()->getValueMapFromFile("test.xml");

    TTFConfig config("fonts/wt021.ttf",25);
    config.outlineSize = 2;
    _statusLabel = Label::createWithTTF(config,_strMap["str1"].asString());
    _statusLabel->enableOutline(Color4B::RED,2);
    _statusLabel->setPosition(Vec2(visibleSize / 2) + origin + Vec2(0, 50));
    this->addChild(_statusLabel,0,100);

    _actor = Sprite::create("CloseNormal.png");
    _actor->setPosition(Vec2(visibleSize / 2) + origin);
    this->addChild(_actor);

    //Controller::startDiscoveryController();
    //        auto controllers = Controller::getControllers();
    //        if (!controllers.empty())
    //        {
    //            _player1 = controllers[0];
    //            statusLabel->setString("Connected");
    //        }
    //    });

    /*CCNSLOG("layer: %p", this);

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

    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

    auto bullet = Sprite::create("CloseSelected.png");
    bullet->setPosition(_actor->getPosition() + Vec2(0, _actor->getContentSize().height/2 + 20));
    this->addChild(bullet);
    bullet->setColor(Color3B::BLUE);

    scheduleUpdate();*/

    srand(time(nullptr));

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch* touch, Event* event){
        static int tmp = 0;
        char key[10];
        sprintf(key,"str%d",tmp + 1);
        tmp = (tmp + 1) % 8;
        _statusLabel->setString(_strMap[key].asString());
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
/*
void HelloWorld::onButtonPressed(cocos2d::Controller *controller, cocos2d::ControllerButtonInput *button, cocos2d::Event *event)
{
    log("HelloWorld::onButtonPressed: %p, %d, %f", button, button->isPressed(), button->getValue());
    if (_player1 == nullptr)
        return;

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
    //CCNSLOG("HelloWorld::onButtonReleased: %p, %d, %f", button, button->isPressed(), button->getValue());
    if (_player1 == nullptr)
        return;

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
        return;

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

        //        if (_player1->getGamepad()->getDirectionPad()->getDown()->isPressed())
        //        {
        //            log("Dpad: down pressed");
        //            _statusLabel->setString("Dpad: down pressed");
        //            newPos.y -= MOVE_DELTA;
        //        }
        //        
        //        if (_player1->getGamepad()->getDirectionPad()->getUp()->isPressed())
        //        {
        //            log("Dpad: up pressed");
        //            _statusLabel->setString("Dpad: up pressed");
        //            newPos.y += MOVE_DELTA;
        //        }
        //        
        //        if (_player1->getGamepad()->getDirectionPad()->getLeft()->isPressed())
        //        {
        //            log("Dpad: left pressed");
        //            _statusLabel->setString("Dpad: left pressed");
        //            newPos.x -= MOVE_DELTA;
        //        }
        //        
        //        if (_player1->getGamepad()->getDirectionPad()->getRight()->isPressed())
        //        {
        //            log("Dpad: right pressed");
        //            _statusLabel->setString("Dpad: right pressed");
        //            newPos.x += MOVE_DELTA;
        //        }

        newPos.x += _player1->getGamepad()->getLeftThumbstick()->getAxisX()->getValue();
        newPos.y -= _player1->getGamepad()->getLeftThumbstick()->getAxisY()->getValue();

        newPos.x += _player1->getGamepad()->getRightThumbstick()->getAxisX()->getValue();
        newPos.y -= _player1->getGamepad()->getRightThumbstick()->getAxisY()->getValue();

        _actor->setPosition(newPos);
    }
}
*/
void HelloWorld::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    //Director::getInstance()->end();
    static int tmp = 0;
    char key[10];
    sprintf(key,"str%d",tmp + 1);
    tmp = (tmp + 1) % 8;
    _statusLabel->setString(_strMap[key].asString());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}