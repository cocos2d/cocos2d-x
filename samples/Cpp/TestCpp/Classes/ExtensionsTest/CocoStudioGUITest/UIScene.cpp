
#include "extensions/cocos-ext.h"
#include "UIScene.h"
#include "UISceneManager.h"
#include "../ExtensionsTest.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

using namespace gui;

UIScene::UIScene()
: m_pSceneTitle(NULL)
, m_pUiLayer(NULL)
{
    
}

UIScene::~UIScene()
{
	
}

bool UIScene::init()
{
    if (CCLayer::init())
    {
        m_pUiLayer = Layout::create();
        addChild(m_pUiLayer);
        
        m_pWidget = dynamic_cast<Layout*>(cocostudio::GUIReader::shareReader()->widgetFromJsonFile("cocosgui/UITest/UITest.json"));
        m_pUiLayer->addChild(m_pWidget);
        
        m_pSceneTitle = dynamic_cast<cocos2d::gui::Label*>(UIHelper::seekWidgetByName(m_pUiLayer, "UItest"));
        
        cocos2d::gui::Label *back_label = dynamic_cast<cocos2d::gui::Label*>(UIHelper::seekWidgetByName(m_pUiLayer, "back"));
        back_label->setVisible(false);
//        back_label->addReleaseEvent(this, coco_releaseselector(UIScene::toExtensionsMainLayer));
        
        Button *left_button = dynamic_cast<Button*>(UIHelper::seekWidgetByName(m_pUiLayer, "left_Button"));
        left_button->addTouchEventListener(this, toucheventselector(UIScene::previousCallback));
        
        Button *middle_button = dynamic_cast<Button*>(UIHelper::seekWidgetByName(m_pUiLayer, "middle_Button"));
        middle_button->addTouchEventListener(this, toucheventselector(UIScene::restartCallback));
        
        Button *right_button = dynamic_cast<Button*>(UIHelper::seekWidgetByName(m_pUiLayer, "right_Button"));
        right_button->addTouchEventListener(this, toucheventselector(UIScene::nextCallback));
        
        
        cocos2d::gui::Label* mainMenuLabel = cocos2d::gui::Label::create();
        mainMenuLabel->setText("MainMenu");
        mainMenuLabel->setFontSize(20);
        mainMenuLabel->setTouchScaleChangeEnabled(true);
        mainMenuLabel->setPosition(Point(430,30));
        mainMenuLabel->setTouchEnabled(true);
        mainMenuLabel->addTouchEventListener(this, toucheventselector(UIScene::menuCloseCallback));
        m_pUiLayer->addChild(mainMenuLabel);
    
        
        return true;
    }
    return false;
}

void UIScene::menuCloseCallback(Object* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        m_pUiLayer->removeFromParent();
        auto scene = new ExtensionsTestScene();
        scene->runThisTest();
        scene->release();
    }
}

void UIScene::previousCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        m_pUiLayer->removeFromParent();
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
    }
}

void UIScene::restartCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        m_pUiLayer->removeFromParent();
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->currentUIScene());
    }
}

void UIScene::nextCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        m_pUiLayer->removeFromParent();
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->nextUIScene());
    }
}
