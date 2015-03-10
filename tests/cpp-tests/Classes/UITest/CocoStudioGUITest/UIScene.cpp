
#include "extensions/cocos-ext.h"
#include "UIScene.h"
#include "UISceneManager.h"
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
    if (Layer::init())
    {
        _uiLayer = Layer::create();
        addChild(_uiLayer);
        
        auto rootPanel = Layout::create();
        rootPanel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        rootPanel->setPosition(Vec2::ZERO);
        rootPanel->setName("root_Panel");
        rootPanel->setTag(81);
        rootPanel->setContentSize(Size(480,320));
        rootPanel->setBackGroundImage("cocosui/UITest/background.png");
        _widget = rootPanel;
        _uiLayer->addChild(_widget);
        
        auto backgroundPanel = Layout::create();
        backgroundPanel->setName("background_Panel");
        backgroundPanel->setTag(83);
        backgroundPanel->setBackGroundImage("cocosui/UITest/buttonBackground.png");
        backgroundPanel->setBackGroundImageScale9Enabled(true);
        backgroundPanel->setContentSize(Size(300,170));
        backgroundPanel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        backgroundPanel->setPosition(Vec2(90, 75));
        _widget->addChild(backgroundPanel);
        
        _sceneTitle = Text::create("", "fonts/arial.ttf", 20);
        _sceneTitle->setPosition(Vec2(240,307));
        _widget->addChild(_sceneTitle);
        
        auto backLabel = Text::create("Back", "fonts/arial.ttf", 20);
        backLabel->setTouchEnabled(true);
        backLabel->setLocalZOrder(6);
        backLabel->setTouchScaleChangeEnabled(true);
        backLabel->setPosition(Vec2(430,30));
        _widget->addChild(backLabel);
        backLabel->addTouchEventListener(CC_CALLBACK_2(UIScene::toCocosGUITestScene, this));
        
        auto leftButton = Button::create("cocosui/UITest/b1.png", "cocosui/UITest/b2.png");
        leftButton->setPosition(Vec2(142,23));
        _widget->addChild(leftButton);
        leftButton->addTouchEventListener(CC_CALLBACK_2(UIScene::previousCallback, this));
        
        auto middleButton = Button::create("cocosui/UITest/r1.png", "cocosui/UITest/r2.png");
        middleButton->setPosition(Vec2(240,23));
        _widget->addChild(middleButton);
        middleButton->addTouchEventListener(CC_CALLBACK_2(UIScene::restartCallback, this));
        
        auto rightButton = Button::create("cocosui/UITest/f1.png", "cocosui/UITest/f2.png");
        rightButton->setPosition(Vec2(338,23));
        _widget->addChild(rightButton);
        rightButton->addTouchEventListener(CC_CALLBACK_2(UIScene::nextCallback, this));
        
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
        
        CocosGUITestScene* pScene = new (std::nothrow) CocosGUITestScene();
        pScene->runThisTest();
        pScene->release();
    }
}

void UIScene::previousCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
    }
}

void UIScene::restartCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->currentUIScene());
    }
}

void UIScene::nextCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->replaceScene(UISceneManager::sharedUISceneManager()->nextUIScene());
    }
}
