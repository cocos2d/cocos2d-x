#include "NotificationCenterTest.h"
#include "../ExtensionsTest.h"
#include "support/CCNotificationCenter.h"

#define kTagLight 100
#define kTagConnect 200

#define MSG_SWITCH_STATE  "SwitchState"

USING_NS_CC;

class Light : public CCSprite
{
public:
    Light();
    ~Light();

    static Light* lightWithFile(const char* name);

    void setIsConnectToSwitch(bool bConnectToSwitch);
    void switchStateChanged(CCObject* obj);
    void updateLightState();

private:
    bool m_bConnected;
    static bool s_bSwitchOn;
};

bool Light::s_bSwitchOn = false;

Light::Light()
    : m_bConnected(false)
{}

Light::~Light()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_SWITCH_STATE);
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
    m_bConnected = bConnectToSwitch;
    if (m_bConnected)
    {
        CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Light::switchStateChanged), MSG_SWITCH_STATE, NULL);
    }
    else
    {
        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_SWITCH_STATE);
    }
    updateLightState();
}

void Light::switchStateChanged(CCObject* obj)
{
    s_bSwitchOn = obj == 0x00 ? false : true;
    updateLightState();
}

void Light::updateLightState()
{
    if (s_bSwitchOn && m_bConnected)
    {
        this->setOpacity(255);
    }
    else
    {
        this->setOpacity(50);
    }
}

NotificationCenterTest::NotificationCenterTest()
: m_bShowImage(false)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemFont* pBackItem = CCMenuItemFont::create("Back", this,
        menu_selector(NotificationCenterTest::toExtensionsMainLayer));
    pBackItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    CCMenu* pBackMenu = CCMenu::create(pBackItem, NULL);
    pBackMenu->setPosition( CCPointZero );
    addChild(pBackMenu);

    CCLabelTTF *label1 = CCLabelTTF::create("switch off", "Marker Felt", 26);
    CCLabelTTF *label2 = CCLabelTTF::create("switch on", "Marker Felt", 26);
    CCMenuItemLabel *item1 = CCMenuItemLabel::create(label1);
    CCMenuItemLabel *item2 = CCMenuItemLabel::create(label2);
    CCMenuItemToggle *item = CCMenuItemToggle::createWithTarget(this, menu_selector(NotificationCenterTest::toggleSwitch), item1, item2, NULL);
    // turn on
    item->setSelectedIndex(1);
    CCMenu *menu = CCMenu::create(item, NULL);
    menu->setPosition(ccp(s.width/2+100, s.height/2));
    addChild(menu);

    CCMenu *menuConnect = CCMenu::create();
    menuConnect->setPosition(CCPointZero);
    addChild(menuConnect);

    for (int i = 1; i <= 3; i++)
    {
        Light* light = Light::lightWithFile("Images/Pea.png");
        light->setTag(kTagLight+i);
        light->setPosition(ccp(100, s.height/4*i));
        addChild(light);

        CCLabelTTF *label1 = CCLabelTTF::create("not connected", "Marker Felt", 26);
        CCLabelTTF *label2 = CCLabelTTF::create("connected", "Marker Felt", 26);
        CCMenuItemLabel *item1 = CCMenuItemLabel::create(label1);
        CCMenuItemLabel *item2 = CCMenuItemLabel::create(label2);
        CCMenuItemToggle *item = CCMenuItemToggle::createWithTarget(this, menu_selector(NotificationCenterTest::connectToSwitch), item1, item2, NULL);
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

    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_SWITCH_STATE, (CCObject*)(intptr_t)item->getSelectedIndex());

    /* for testing removeAllObservers */
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer1", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer2", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(NotificationCenterTest::doNothing), "random-observer3", NULL);
}

void NotificationCenterTest::toExtensionsMainLayer(cocos2d::CCObject* sender)
{
    /* for testing removeAllObservers */
    int CC_UNUSED numObserversRemoved = CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    CCAssert(numObserversRemoved >= 3, "All observers were not removed!");

    ExtensionsTestScene* pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void NotificationCenterTest::toggleSwitch(CCObject *sender)
{
    CCMenuItemToggle* item = (CCMenuItemToggle*)sender;
    int index = item->getSelectedIndex();
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_SWITCH_STATE, (CCObject*)(intptr_t)index);
}

void NotificationCenterTest::connectToSwitch(CCObject *sender)
{
    CCMenuItemToggle* item = (CCMenuItemToggle*)sender;
    bool bConnected = item->getSelectedIndex() == 0 ? false : true;
    Light* pLight = (Light*)this->getChildByTag(item->getTag()-kTagConnect+kTagLight);
    pLight->setIsConnectToSwitch(bConnected);
}

void NotificationCenterTest::doNothing(cocos2d::CCObject *sender)
{

}

void runNotificationCenterTest()
{
    CCScene* pScene = CCScene::create();
    NotificationCenterTest* pLayer = new NotificationCenterTest();
    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}
