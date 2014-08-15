#include "NotificationCenterTest.h"
#include "../ExtensionsTest.h"

#define kTagLight 100
#define kTagConnect 200

#define MSG_SWITCH_STATE  "SwitchState"

USING_NS_CC;

class LightTexture : public Sprite
{
public:
    LightTexture();
    ~LightTexture();

    static LightTexture* lightWithFile(const char* name);

    void setIsConnectToSwitch(bool bConnectToSwitch);
    void switchStateChanged(Ref* obj);
    void updateLightState();

private:
    bool _connected;
    static bool s_bSwitchOn;
};

bool LightTexture::s_bSwitchOn = false;

LightTexture::LightTexture()
    : _connected(false)
{}

LightTexture::~LightTexture()
{
    NotificationCenter::getInstance()->removeObserver(this, MSG_SWITCH_STATE);
}

LightTexture* LightTexture::lightWithFile(const char* name)
{
    LightTexture* pLight = new LightTexture();
    pLight->initWithFile(name);
    pLight->autorelease();
    return pLight;
}

void LightTexture::setIsConnectToSwitch(bool bConnectToSwitch)
{
    _connected = bConnectToSwitch;
    if (_connected)
    {
        NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LightTexture::switchStateChanged), MSG_SWITCH_STATE, nullptr);
    }
    else
    {
        NotificationCenter::getInstance()->removeObserver(this, MSG_SWITCH_STATE);
    }
    updateLightState();
}

void LightTexture::switchStateChanged(Ref* obj)
{
    s_bSwitchOn = obj == 0x00 ? false : true;
    updateLightState();
}

void LightTexture::updateLightState()
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
    pBackItem->setPosition(Vec2(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto pBackMenu = Menu::create(pBackItem, nullptr);
    pBackMenu->setPosition( Vec2::ZERO );
    addChild(pBackMenu);

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
        LightTexture* light = LightTexture::lightWithFile("Images/Pea.png");
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

    NotificationCenter::getInstance()->postNotification(MSG_SWITCH_STATE, (Ref*)(intptr_t)item->getSelectedIndex());

    /* for testing removeAllObservers */
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer1", nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer2", nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer3", nullptr);
}

void NotificationCenterTest::toExtensionsMainLayer(cocos2d::Ref* sender)
{
    /* for testing removeAllObservers */
    int CC_UNUSED numObserversRemoved = NotificationCenter::getInstance()->removeAllObservers(this);
    CCASSERT(numObserversRemoved >= 3, "All observers were not removed!");

    auto scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();
}

void NotificationCenterTest::toggleSwitch(Ref *sender)
{
    auto item = (MenuItemToggle*)sender;
    int index = item->getSelectedIndex();
    NotificationCenter::getInstance()->postNotification(MSG_SWITCH_STATE, (Ref*)(intptr_t)index);
}

void NotificationCenterTest::connectToSwitch(Ref *sender)
{
    auto item = (MenuItemToggle*)sender;
    bool bConnected = item->getSelectedIndex() == 0 ? false : true;
    LightTexture* pLight = (LightTexture*)this->getChildByTag(item->getTag()-kTagConnect+kTagLight);
    pLight->setIsConnectToSwitch(bConnected);
}

void NotificationCenterTest::doNothing(cocos2d::Ref *sender)
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
