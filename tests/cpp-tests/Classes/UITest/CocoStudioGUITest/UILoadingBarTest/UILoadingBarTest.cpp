

#include "UILoadingBarTest.h"


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
        
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        Text* alert = Text::create("LoadingBar left", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/sliderProgress.png");
        loadingBar->setTag(0);
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        
        _uiLayer->addChild(loadingBar);
        
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
    loadingBar->setPercent(_count);
}

void UILoadingBarTest_Left::previousCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Left::restartCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Left::nextCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
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
        
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        Text *alert = Text::create("LoadingBar right", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/sliderProgress.png");
        loadingBar->setTag(0);
        loadingBar->setDirection(LoadingBar::Direction::RIGHT);
        
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        
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

void UILoadingBarTest_Right::previousCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Right::restartCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Right::nextCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
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
        
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        Text* alert = Text::create("LoadingBar left scale9 render", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/slider_bar_active_9patch.png");
        loadingBar->setTag(0);
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setSize(Size(300, 13));
        
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        
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

void UILoadingBarTest_Left_Scale9::previousCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Left_Scale9::restartCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender,  type);
    }
}

void UILoadingBarTest_Left_Scale9::nextCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
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
        
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        Text *alert = Text::create("LoadingBar right scale9 render", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create("cocosui/slider_bar_active_9patch.png");
        loadingBar->setTag(0);
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setSize(Size(300, 13));
        loadingBar->setDirection(LoadingBar::Direction::RIGHT);
        
        loadingBar->setPosition(Vec2(widgetSize.width / 2.0f,
                                      widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        
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

void UILoadingBarTest_Right_Scale9::previousCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Right_Scale9::restartCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender,  type);
    }
}

void UILoadingBarTest_Right_Scale9::nextCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
}
