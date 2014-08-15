
#include "extensions/cocos-ext.h"
#include "UIScene.h"
#include "UISceneManager.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "CocosGUIScene.h"

using namespace ui;

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
        
        _widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UITest/UITest.json"));
        _uiLayer->addChild(_widget);
        
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _widget->getContentSize();
        _uiLayer->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        _sceneTitle = dynamic_cast<Text*>(root->getChildByName("UItest"));
        
        Text* back_label = dynamic_cast<Text*>(root->getChildByName("back"));
        back_label->addTouchEventListener(CC_CALLBACK_2(UIScene::toCocosGUITestScene, this));
        
        Button* left_button = dynamic_cast<Button*>(root->getChildByName("left_Button"));
        left_button->addTouchEventListener(CC_CALLBACK_2(UIScene::previousCallback, this));
        
        Button* middle_button = dynamic_cast<Button*>(root->getChildByName("middle_Button"));
        middle_button->addTouchEventListener(CC_CALLBACK_2(UIScene::restartCallback, this));
        
        Button* right_button = dynamic_cast<Button*>(root->getChildByName("right_Button"));
        right_button->addTouchEventListener(CC_CALLBACK_2(UIScene::nextCallback, this));
        
        /*
        Text* mainMenuLabel = Text::create();
        mainMenuLabel->setText("MainMenu");
        mainMenuLabel->setFontSize(20);
        mainMenuLabel->setTouchScaleChangeEnabled(true);
        mainMenuLabel->setPosition(Vec2(430,30));
        mainMenuLabel->setTouchEnabled(true);
        mainMenuLabel->addTouchEventListener(this, toucheventselector(UIScene::menuCloseCallback));
        _uiLayer->addWidget(mainMenuLabel);
         */
    
        
        return true;
    }
    return false;
}

void UIScene::menuCloseCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        _uiLayer->removeFromParent();
        
    }
}

void UIScene::toCocosGUITestScene(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        UISceneManager::purgeUISceneManager();
        
        CocosGUITestScene* pScene = new CocosGUITestScene();
        pScene->runThisTest();
        pScene->release();
    }
}

void UIScene::previousCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
    }
}

void UIScene::restartCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->currentUIScene());
    }
}

void UIScene::nextCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        CCDirector::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->nextUIScene());
    }
}
