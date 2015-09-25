#include "NotificationCenterTest.h"
#include "../ExtensionsTest.h"

#define kTagLight 100
#define kTagConnect 200

#define MSG_SWITCH_STATE  "SwitchState"

USING_NS_CC;

NotificationCenterTests::NotificationCenterTests()
{
    ADD_TEST_CASE(NotificationCenterTest);
}

class Light : public Sprite
{
public:
    Light();
    ~Light();

    static Light* lightWithFile(const char* name);

    void setIsConnectToSwitch(bool bConnectToSwitch);
    void switchStateChanged(Ref* obj);
    void updateLightState();

private:
    bool _connected;
    static bool s_bSwitchOn;
};

bool Light::s_bSwitchOn = false;

Light::Light()
    : _connected(false)
{}

Light::~Light()
{
    __NotificationCenter::getInstance()->removeObserver(this, MSG_SWITCH_STATE);
}

Light* Light::lightWithFile(const char* name)
{
    Light* pLight = new (std::nothrow) Light();
    pLight->initWithFile(name);
    pLight->autorelease();
    return pLight;
}

void Light::setIsConnectToSwitch(bool bConnectToSwitch)
{
    _connected = bConnectToSwitch;
    if (_connected)
    {
        __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(Light::switchStateChanged), MSG_SWITCH_STATE, nullptr);
    }
    else
    {
        __NotificationCenter::getInstance()->removeObserver(this, MSG_SWITCH_STATE);
    }
    updateLightState();
}

void Light::switchStateChanged(Ref* obj)
{
    s_bSwitchOn = obj == 0x00 ? false : true;
    updateLightState();
}

void Light::updateLightState()
{
    if (s_bSwitchOn && _connected)
    {
        this->setOpacity(255);
    }
    else
    {
        this->setOpacity(50);
    }
}

NotificationCenterTest::NotificationCenterTest()
{
    auto s = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithTTF("switch off", "fonts/Marker Felt.ttf", 26);
    auto label2 = Label::createWithTTF("switch on", "fonts/Marker Felt.ttf", 26);
    auto item1 = MenuItemLabel::create(label1);
    auto item2 = MenuItemLabel::create(label2);
    auto item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(NotificationCenterTest::toggleSwitch, this), item1, item2, nullptr);
    // turn on
    item->setSelectedIndex(1);
    auto menu = Menu::create(item, nullptr);
    menu->setPosition(Vec2(s.width/2+100, s.height/2));
    addChild(menu);

    auto menuConnect = Menu::create();
    menuConnect->setPosition(Vec2::ZERO);
    addChild(menuConnect);

    for (int i = 1; i <= 3; i++)
    {
        Light* light = Light::lightWithFile("Images/Pea.png");
        light->setTag(kTagLight+i);
        light->setPosition(Vec2(100, s.height/4*i));
        addChild(light);

        auto label1 = Label::createWithTTF("not connected", "fonts/Marker Felt.ttf", 26);
        auto label2 = Label::createWithTTF("connected", "fonts/Marker Felt.ttf", 26);
        auto item1 = MenuItemLabel::create(label1);
        auto item2 = MenuItemLabel::create(label2);
        auto item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(NotificationCenterTest::connectToSwitch, this), item1, item2, nullptr);
        item->setTag(kTagConnect+i);
        item->setPosition(Vec2(light->getPosition().x, light->getPosition().y+50));
        menuConnect->addChild(item, 0);
        if (i == 2)
        {
            item->setSelectedIndex(1);
        }
        bool bConnected = item->getSelectedIndex() == 1 ? true : false;
        light->setIsConnectToSwitch(bConnected);
    }

    __NotificationCenter::getInstance()->postNotification(MSG_SWITCH_STATE, (Ref*)(intptr_t)item->getSelectedIndex());

    /* for testing removeAllObservers */
    __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(NotificationCenterTest::doNothing), "random-observer1", nullptr);
    __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(NotificationCenterTest::doNothing), "random-observer2", nullptr);
    __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(NotificationCenterTest::doNothing), "random-observer3", nullptr);
}

NotificationCenterTest::~NotificationCenterTest()
{
    /* for testing removeAllObservers */
    int CC_UNUSED numObserversRemoved = __NotificationCenter::getInstance()->removeAllObservers(this);
    CCASSERT(numObserversRemoved >= 3, "All observers were not removed!");
}

void NotificationCenterTest::toggleSwitch(Ref *sender)
{
    auto item = (MenuItemToggle*)sender;
    int index = item->getSelectedIndex();
    __NotificationCenter::getInstance()->postNotification(MSG_SWITCH_STATE, (Ref*)(intptr_t)index);
}

void NotificationCenterTest::connectToSwitch(Ref *sender)
{
    auto item = (MenuItemToggle*)sender;
    bool bConnected = item->getSelectedIndex() == 0 ? false : true;
    Light* pLight = (Light*)this->getChildByTag(item->getTag()-kTagConnect+kTagLight);
    pLight->setIsConnectToSwitch(bConnected);
}

void NotificationCenterTest::doNothing(cocos2d::Ref *sender)
{

}
