
#include "extensions/cocos-ext.h"
#include "UIScene.h"
#include "UISceneManager.h"
#include "../ExtensionsTest.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "CocosGUIScene.h"

using namespace gui;

UIScene::UIScene()
: _sceneTitle(nullptr)
, _uiLayer(nullptr)
{
    
}

UIScene::~UIScene()
{
	
}

bool UIScene::init()
{
    if (CCLayer::init())
    {
        _uiLayer = Layer::create();
        addChild(_uiLayer);
        
        _widget = dynamic_cast<Layout*>(cocostudio::GUIReader::shareReader()->widgetFromJsonFile("cocosgui/UITest/UITest.json"));
        _uiLayer->addChild(_widget);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        _sceneTitle = dynamic_cast<gui::Label*>(root->getChildByName("UItest"));
        
        gui::Label* back_label = dynamic_cast<gui::Label*>(root->getChildByName("back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene::toCocosGUITestScene));
        
        Button* left_button = dynamic_cast<Button*>(root->getChildByName("left_Button"));
        left_button->addTouchEventListener(this, toucheventselector(UIScene::previousCallback));
        
        Button* middle_button = dynamic_cast<Button*>(root->getChildByName("middle_Button"));
        middle_button->addTouchEventListener(this, toucheventselector(UIScene::restartCallback));
        
        Button* right_button = dynamic_cast<Button*>(root->getChildByName("right_Button"));
        right_button->addTouchEventListener(this, toucheventselector(UIScene::nextCallback));
        
        /*
        gui::Label* mainMenuLabel = gui::Label::create();
        mainMenuLabel->setText("MainMenu");
        mainMenuLabel->setFontSize(20);
        mainMenuLabel->setTouchScaleChangeEnabled(true);
        mainMenuLabel->setPosition(Point(430,30));
        mainMenuLabel->setTouchEnabled(true);
        mainMenuLabel->addTouchEventListener(this, toucheventselector(UIScene::menuCloseCallback));
        _uiLayer->addWidget(mainMenuLabel);
         */
    
        
        return true;
    }
    return false;
}

void UIScene::menuCloseCallback(Object* pSender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        _uiLayer->removeFromParent();
        auto scene = new ExtensionsTestScene();
        scene->runThisTest();
        scene->release();
    }
}

void UIScene::toCocosGUITestScene(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        UISceneManager::purgeUISceneManager();
        
        CocosGUITestScene* pScene = new CocosGUITestScene();
        pScene->runThisTest();
        pScene->release();
    }
}

void UIScene::previousCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
    }
}

void UIScene::restartCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->currentUIScene());
    }
}

void UIScene::nextCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->nextUIScene());
    }
}
