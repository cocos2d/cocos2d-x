#include "NotificationCenterTest.h"
#include "../ExtensionsTest.h"
#include "support/CCNotificationCenter.h"

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
    NotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_SWITCH_STATE);
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
        NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Light::switchStateChanged), MSG_SWITCH_STATE, NULL);
    }
    else
    {
        NotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_SWITCH_STATE);
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
    Size s = Director::sharedDirector()->getWinSize();

    MenuItemFont* pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(NotificationCenterTest::toExtensionsMainLayer, this));
    pBackItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    Menu* pBackMenu = Menu::create(pBackItem, NULL);
    pBackMenu->setPosition( PointZero );
    addChild(pBackMenu);

    LabelTTF *label1 = LabelTTF::create("switch off", "Marker Felt", 26);
    LabelTTF *label2 = LabelTTF::create("switch on", "Marker Felt", 26);
    MenuItemLabel *item1 = MenuItemLabel::create(label1);
    MenuItemLabel *item2 = MenuItemLabel::create(label2);
    MenuItemToggle *item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(NotificationCenterTest::toggleSwitch, this), item1, item2, NULL);
    // turn on
    item->setSelectedIndex(1);
    Menu *menu = Menu::create(item, NULL);
    menu->setPosition(ccp(s.width/2+100, s.height/2));
    addChild(menu);

    Menu *menuConnect = Menu::create();
    menuConnect->setPosition(PointZero);
    addChild(menuConnect);

    for (int i = 1; i <= 3; i++)
    {
        Light* light = Light::lightWithFile("Images/Pea.png");
        light->setTag(kTagLight+i);
        light->setPosition(ccp(100, s.height/4*i));
        addChild(light);

        LabelTTF *label1 = LabelTTF::create("not connected", "Marker Felt", 26);
        LabelTTF *label2 = LabelTTF::create("connected", "Marker Felt", 26);
        MenuItemLabel *item1 = MenuItemLabel::create(label1);
        MenuItemLabel *item2 = MenuItemLabel::create(label2);
        MenuItemToggle *item = MenuItemToggle::createWithCallback( CC_CALLBACK_1(NotificationCenterTest::connectToSwitch, this), item1, item2, NULL);
        item->setTag(kTagConnect+i);
        item->setPosition(ccp(light->getPosition().x, light->getPosition().y+50));
        menuConnect->addChild(item, 0);
        if (i == 2)
        {
            item->setSelectedIndex(1);
        }
        bool bConnected = item->getSelectedIndex() == 1 ? true : false;
        light->setIsConnectToSwitch(bConnected);
    }

    NotificationCenter::sharedNotificationCenter()->postNotification(MSG_SWITCH_STATE, (Object*)(intptr_t)item->getSelectedIndex());

    /* for testing removeAllObservers */
    NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer1", NULL);
    NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer2", NULL);
    NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer3", NULL);
}

void NotificationCenterTest::toExtensionsMainLayer(cocos2d::Object* sender)
{
    /* for testing removeAllObservers */
    int CC_UNUSED numObserversRemoved = NotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    CCAssert(numObserversRemoved >= 3, "All observers were not removed!");

    ExtensionsTestScene* pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void NotificationCenterTest::toggleSwitch(Object *sender)
{
    MenuItemToggle* item = (MenuItemToggle*)sender;
    int index = item->getSelectedIndex();
    NotificationCenter::sharedNotificationCenter()->postNotification(MSG_SWITCH_STATE, (Object*)(intptr_t)index);
}

void NotificationCenterTest::connectToSwitch(Object *sender)
{
    MenuItemToggle* item = (MenuItemToggle*)sender;
    bool bConnected = item->getSelectedIndex() == 0 ? false : true;
    Light* pLight = (Light*)this->getChildByTag(item->getTag()-kTagConnect+kTagLight);
    pLight->setIsConnectToSwitch(bConnected);
}

void NotificationCenterTest::doNothing(cocos2d::Object *sender)
{

}

void runNotificationCenterTest()
{
    Scene* pScene = Scene::create();
    NotificationCenterTest* pLayer = new NotificationCenterTest();
    pScene->addChild(pLayer);
    Director::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}
