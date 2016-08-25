#include "UILoadingBarTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UILoadingBarTests::UILoadingBarTests()
{
    ADD_TEST_CASE(UILoadingBarTest_Left);
    ADD_TEST_CASE(UILoadingBarTest_Right);
    ADD_TEST_CASE(UILoadingBarTest_Left_Scale9);
    ADD_TEST_CASE(UILoadingBarTest_Right_Scale9);
    ADD_TEST_CASE(UILoadingBarTest_Scale9_State_Change);
    ADD_TEST_CASE(UILoadingBarReloadTexture);
    ADD_TEST_CASE(UILoadingBarIssue12249);
    ADD_TEST_CASE(UILoadingBarTest_Direction);
}

// UILoadingBarTest_Left

UILoadingBarTest_Left::UILoadingBarTest_Left()
: _count(0)
{
    
}

UILoadingBarTest_Left::~UILoadingBarTest_Left()
{
    unscheduleUpdate();
}

bool UILoadingBarTest_Left::init()
{
    if (UIScene::init())
    {
        scheduleUpdate();
        
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Test LoadingBar Change Direction",
                                   "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/sliderProgress.png");
        loadingBar->setTag(0);
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));

        auto loadingBarCopy = (LoadingBar*)loadingBar->clone();
        loadingBarCopy->setTag(1);
        loadingBarCopy->setPosition(loadingBar->getPosition()
                                    + Vec2(0, -40));
        loadingBarCopy->setDirection(LoadingBar::Direction::RIGHT);

        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 50));
        button->setTitleText("Click to change direction!");

        button->addTouchEventListener([=](Ref*, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED)
            {
                if (loadingBar->getDirection() == LoadingBar::Direction::LEFT)
                {
                    loadingBar->setDirection(LoadingBar::Direction::RIGHT);
                    loadingBarCopy->setDirection(LoadingBar::Direction::LEFT);
                }
                else
                {
                    loadingBar->setDirection(LoadingBar::Direction::LEFT);
                    loadingBarCopy->setDirection(LoadingBar::Direction::RIGHT);
                }
            }
        });
         _uiLayer->addChild(loadingBar,1);
        _uiLayer->addChild(loadingBarCopy,2);
        _uiLayer->addChild(button);

        _loadingBar = loadingBar;

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UILoadingBarTest_Left::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0, 0));
        this->addChild(pMenu1, 10);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Left::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    LoadingBar* loadingBar = static_cast<LoadingBar*>(_uiLayer->getChildByTag(0));
    LoadingBar* loadingBarCopy = static_cast<LoadingBar*>(_uiLayer->getChildByTag(1));
    loadingBar->setPercent(_count);
    loadingBarCopy->setPercent(_count);
}

void UILoadingBarTest_Left::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData textureFile = _loadingBar->getRenderFile();
    CCLOG("textureFile  Name : %s, Type: %d", textureFile.file.c_str(), textureFile.type);
}

// UILoadingBarTest_Right

UILoadingBarTest_Right::UILoadingBarTest_Right()
: _count(0)
{
    
}

UILoadingBarTest_Right::~UILoadingBarTest_Right()
{
    unscheduleUpdate();
}

bool UILoadingBarTest_Right::init()
{
    if (UIScene::init())
    {
        scheduleUpdate();
        
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text *alert = Text::create("LoadingBar right", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/sliderProgress.png");
        loadingBar->setTag(0);
        loadingBar->setDirection(LoadingBar::Direction::RIGHT);
        
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));
        
        _uiLayer->addChild(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Right::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    LoadingBar* loadingBar = static_cast<LoadingBar*>(_uiLayer->getChildByTag(0));
    loadingBar->setPercent(_count);
}

// UILoadingBarTest_Left_Scale9

UILoadingBarTest_Left_Scale9::UILoadingBarTest_Left_Scale9()
: _count(0)
{
    
}

UILoadingBarTest_Left_Scale9::~UILoadingBarTest_Left_Scale9()
{
    unscheduleUpdate();
}

bool UILoadingBarTest_Left_Scale9::init()
{
    if (UIScene::init())
    {
        scheduleUpdate();
        
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("LoadingBar left scale9 render", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 2.7f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/slider_bar_active_9patch.png");
        loadingBar->setTag(0);
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setContentSize(Size(300, 13));
        
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));
        
        _uiLayer->addChild(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Left_Scale9::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    LoadingBar* loadingBar = static_cast<LoadingBar*>(_uiLayer->getChildByTag(0));
    loadingBar->setPercent(_count);
}

// UILoadingBarTest_Right_Scale9

UILoadingBarTest_Right_Scale9::UILoadingBarTest_Right_Scale9()
: _count(0)
{
    
}

UILoadingBarTest_Right_Scale9::~UILoadingBarTest_Right_Scale9()
{
    unscheduleUpdate();
}

bool UILoadingBarTest_Right_Scale9::init()
{
    if (UIScene::init())
    {
        scheduleUpdate();
        
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text *alert = Text::create("LoadingBar right scale9 render", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 2.7f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/slider_bar_active_9patch.png");
        loadingBar->setTag(0);
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setContentSize(Size(300, 13));
        loadingBar->setDirection(LoadingBar::Direction::RIGHT);
        
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));
        
        _uiLayer->addChild(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Right_Scale9::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    LoadingBar* loadingBar = static_cast<LoadingBar*>(_uiLayer->getChildByTag(0));
    loadingBar->setPercent(_count);
}

// UILoadingBarTest_Scale9_State_Change

UILoadingBarTest_Scale9_State_Change::UILoadingBarTest_Scale9_State_Change()
    : _count(0)
{

}

UILoadingBarTest_Scale9_State_Change::~UILoadingBarTest_Scale9_State_Change()
{

}

bool UILoadingBarTest_Scale9_State_Change::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("LoadingBar right scale9 render", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 2.7f));
        _uiLayer->addChild(alert);

        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/sliderThumb.png");
        loadingBar->setTag(0);
        loadingBar->ignoreContentAdaptWithSize(false);
        //loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setContentSize(Size(200, 80));
        loadingBar->setDirection(LoadingBar::Direction::LEFT);
        loadingBar->setPercent(100);

        loadingBar->setTouchEnabled(true);
        loadingBar->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
            if (type == Widget::TouchEventType::ENDED) {
                if (loadingBar->isScale9Enabled())
                {
                    loadingBar->setScale9Enabled(false);
                }
                else
                    loadingBar->setScale9Enabled(true);
            }
        });

        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
            widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));

        _uiLayer->addChild(loadingBar);

        return true;
    }
    return false;
}


// UILoadingBarReloadTexture

UILoadingBarReloadTexture::UILoadingBarReloadTexture()
: _count(0)
{
    
}

UILoadingBarReloadTexture::~UILoadingBarReloadTexture()
{
    
}

bool UILoadingBarReloadTexture::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text *alert = Text::create("Click button to Toggle Scale9 and switch Texture.", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 2.7f));
        _uiLayer->addChild(alert);
        
        LoadingBar* loadingBar = LoadingBar::create("cocosui/slider_bar_active_9patch.png");
        loadingBar->setTag(0);
        loadingBar->ignoreContentAdaptWithSize(false);
//        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setContentSize(Size(300, 13));
        loadingBar->setName("texture0");
        loadingBar->setDirection(LoadingBar::Direction::RIGHT);
        loadingBar->setPercent(70);
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                     widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));
        
        _uiLayer->addChild(loadingBar);
        
        auto buttonScale9 = Button::create("cocosui/animationbuttonnormal.png",
                                           "cocosui/animationbuttonpressed.png");
        buttonScale9->setTitleText("ToggleScale9");
        buttonScale9->addClickEventListener([=](Ref*){
            loadingBar->setScale9Enabled(!loadingBar->isScale9Enabled());
        });
        buttonScale9->setPosition(loadingBar->getPosition() + Vec2(-50,50));
        _uiLayer->addChild(buttonScale9);
        
        auto buttonChangeTexture = Button::create("cocosui/animationbuttonnormal.png",
                                                  "cocosui/animationbuttonpressed.png");
        buttonChangeTexture->setTitleText("ChangeTexture");
        buttonChangeTexture->addClickEventListener([=](Ref*){
            auto name = loadingBar->getName();
            if (name == "texture0")
            {
                loadingBar->loadTexture("cocosui/slider_bar_active_9patch2.png");
                loadingBar->setName("texture1");
            }
            else
            {
                loadingBar->loadTexture("cocosui/slider_bar_active_9patch.png");
                loadingBar->setName("texture0");
            }
        });
        buttonChangeTexture->setPosition(loadingBar->getPosition() + Vec2(50,50));
        _uiLayer->addChild(buttonChangeTexture);
        
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void UILoadingBarReloadTexture::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    LoadingBar* loadingBar = static_cast<LoadingBar*>(_uiLayer->getChildByTag(0));
    loadingBar->setPercent(_count);
}


// UILoadingBarIssue12249

UILoadingBarIssue12249::UILoadingBarIssue12249()
: _count(0)
{
    
}

UILoadingBarIssue12249::~UILoadingBarIssue12249()
{
    unscheduleUpdate();
}

bool UILoadingBarIssue12249::init()
{
    if (UIScene::init())
    {
        scheduleUpdate();
        
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Test LoadingBar Change Direction",
                                   "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/sliderProgress.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setContentSize(Size(200, loadingBar->getContentSize().height * 1.5));
        loadingBar->setTag(0);
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                     widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));
        
        LoadingBar* loadingBarCopy = LoadingBar::create();
        loadingBarCopy->setScale9Enabled(true);
        loadingBarCopy->loadTexture("cocosui/sliderProgress.png");
        loadingBarCopy->setContentSize(Size(200, loadingBarCopy->getContentSize().height * 1.5));
        loadingBarCopy->setTag(1);
        loadingBarCopy->setPosition(loadingBar->getPosition()
                                    + Vec2(0, -40));
        loadingBarCopy->setDirection(LoadingBar::Direction::RIGHT);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png",
                                        "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 50));
        button->setTitleText("Click to change direction!");
        
        button->addTouchEventListener([=](Ref*, Widget::TouchEventType type)
                                      {
                                          if (type == Widget::TouchEventType::ENDED)
                                          {
                                              if (loadingBar->getDirection() == LoadingBar::Direction::LEFT)
                                              {
                                                  loadingBar->setDirection(LoadingBar::Direction::RIGHT);
                                                  loadingBarCopy->setDirection(LoadingBar::Direction::LEFT);
                                              }
                                              else
                                              {
                                                  loadingBar->setDirection(LoadingBar::Direction::LEFT);
                                                  loadingBarCopy->setDirection(LoadingBar::Direction::RIGHT);
                                              }
                                          }
                                      });
        _uiLayer->addChild(loadingBar,1);
        _uiLayer->addChild(loadingBarCopy,2);
        _uiLayer->addChild(button);
        
        return true;
    }
    return false;
}

void UILoadingBarIssue12249::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    LoadingBar* loadingBar = static_cast<LoadingBar*>(_uiLayer->getChildByTag(0));
    LoadingBar* loadingBarCopy = static_cast<LoadingBar*>(_uiLayer->getChildByTag(1));
    loadingBar->setPercent(_count);
    loadingBarCopy->setPercent(_count);
}

// UILoadingBarTest_Direction

UILoadingBarTest_Direction::UILoadingBarTest_Direction()
    : _count(0)
{

}

UILoadingBarTest_Direction::~UILoadingBarTest_Direction()
{
    //unscheduleUpdate();
}

bool UILoadingBarTest_Direction::init()
{
    if (UIScene::init())
    {
        //scheduleUpdate();

        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text* alert = Text::create("Test LoadingBar Change Direction",
            "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
            widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);

        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/sliderProgress.png");
        loadingBar->setTag(0);
        loadingBar->setPercent(80);
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
            widgetSize.height / 2.0f + loadingBar->getContentSize().height / 4.0f));

        auto loadingBarCopy = (LoadingBar*)loadingBar->clone();
        loadingBarCopy->setTag(1);
        loadingBarCopy->setPosition(loadingBar->getPosition()
            + Vec2(0, -40));
        loadingBarCopy->setDirection(LoadingBar::Direction::RIGHT);

        Button* button = Button::create("cocosui/animationbuttonnormal.png",
            "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 50));
        button->setTitleText("Click to change direction!");

        button->addTouchEventListener([=](Ref*, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED)
            {
                if (loadingBar->getDirection() == LoadingBar::Direction::LEFT)
                {
                    loadingBar->setDirection(LoadingBar::Direction::RIGHT);
                    loadingBarCopy->setDirection(LoadingBar::Direction::LEFT);
                }
                else
                {
                    loadingBar->setDirection(LoadingBar::Direction::LEFT);
                    loadingBarCopy->setDirection(LoadingBar::Direction::RIGHT);
                }
            }
        });
        _uiLayer->addChild(loadingBar, 1);
        _uiLayer->addChild(loadingBarCopy, 2);
        _uiLayer->addChild(button);

        _loadingBar = loadingBar;
        return true;
    }
    return false;
}