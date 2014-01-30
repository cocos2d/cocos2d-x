#include "NotificationCenterTest.h"
#include "../ExtensionsTest.h"
#include "CCNotificationCenter.h"

#define kTagLight 100
#define kTagConnect 200

#define MSG_SWITCH_STATE  "SwitchState"

USING_NS_CC;

class Light : public Sprite
{
public:
    Light();
    ~Light();

    static Light* lightWithFile(const char* name);

    void setIsConnectToSwitch(bool bConnectToSwitch);
    void switchStateChanged(Object* obj);
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
    NotificationCenter::getInstance()->removeObserver(this, MSG_SWITCH_STATE);
}

Light* Light::lightWithFile(const char* name)
{
    Light* pLight = new Light();
    pLight->initWithFile(name);
    pLight->autorelease();
    return pLight;
}

void Light::setIsConnectToSwitch(bool bConnectToSwitch)
{
    _connected = bConnectToSwitch;
    if (_connected)
    {
        NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Light::switchStateChanged), MSG_SWITCH_STATE, NULL);
    }
    else
    {
        NotificationCenter::getInstance()->removeObserver(this, MSG_SWITCH_STATE);
    }
    updateLightState();
}

void Light::switchStateChanged(Object* obj)
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
: _showImage(false)
{
    auto s = Director::getInstance()->getWinSize();

    auto pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(NotificationCenterTest::toExtensionsMainLayer, this));
    pBackItem->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto pBackMenu = Menu::create(pBackItem, NULL);
    pBackMenu->setPosition( Point::ZERO );
    addChild(pBackMenu);

    auto label1 = LabelTTF::create("switch off", "Marker Felt", 26);
    auto label2 = LabelTTF::create("switch on", "Marker Felt", 26);
    auto item1 = MenuItemLabel::create(label1);
    auto item2 = MenuItemLabel::create(label2);
    auto item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(NotificationCenterTest::toggleSwitch, this), item1, item2, NULL);
    // turn on
    item->setSelectedIndex(1);
    auto menu = Menu::create(item, NULL);
    menu->setPosition(Point(s.width/2+100, s.height/2));
    addChild(menu);

    auto menuConnect = Menu::create();
    menuConnect->setPosition(Point::ZERO);
    addChild(menuConnect);

    for (int i = 1; i <= 3; i++)
    {
        Light* light = Light::lightWithFile("Images/Pea.png");
        light->setTag(kTagLight+i);
        light->setPosition(Point(100, s.height/4*i));
        addChild(light);

        auto label1 = LabelTTF::create("not connected", "Marker Felt", 26);
        auto label2 = LabelTTF::create("connected", "Marker Felt", 26);
        auto item1 = MenuItemLabel::create(label1);
        auto item2 = MenuItemLabel::create(label2);
        auto item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(NotificationCenterTest::connectToSwitch, this), item1, item2, NULL);
        item->setTag(kTagConnect+i);
        item->setPosition(Point(light->getPosition().x, light->getPosition().y+50));
        menuConnect->addChild(item, 0);
        if (i == 2)
        {
            item->setSelectedIndex(1);
        }
        bool bConnected = item->getSelectedIndex() == 1 ? true : false;
        light->setIsConnectToSwitch(bConnected);
    }

    NotificationCenter::getInstance()->postNotification(MSG_SWITCH_STATE, (Object*)(intptr_t)item->getSelectedIndex());

    /* for testing removeAllObservers */
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer1", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer2", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer3", NULL);
}

void NotificationCenterTest::toExtensionsMainLayer(cocos2d::Object* sender)
{
    /* for testing removeAllObservers */
    int CC_UNUSED numObserversRemoved = NotificationCenter::getInstance()->removeAllObservers(this);
    CCASSERT(numObserversRemoved >= 3, "All observers were not removed!");

    auto scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();
}

void NotificationCenterTest::toggleSwitch(Object *sender)
{
    auto item = (MenuItemToggle*)sender;
    int index = item->getSelectedIndex();
    NotificationCenter::getInstance()->postNotification(MSG_SWITCH_STATE, (Object*)(intptr_t)index);
}

void NotificationCenterTest::connectToSwitch(Object *sender)
{
    auto item = (MenuItemToggle*)sender;
    bool bConnected = item->getSelectedIndex() == 0 ? false : true;
    Light* pLight = (Light*)this->getChildByTag(item->getTag()-kTagConnect+kTagLight);
    pLight->setIsConnectToSwitch(bConnected);
}

void NotificationCenterTest::doNothing(cocos2d::Object *sender)
{

}

void runNotificationCenterTest()
{
    auto scene = Scene::create();
    NotificationCenterTest* layer = new NotificationCenterTest();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    layer->release();
}
