

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
        gui::Text* alert = gui::Text::create();
        alert->setText("LoadingBar left");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create();
        loadingBar->setTag(0);
        loadingBar->loadTexture("cocosgui/sliderProgress.png");
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Left::previousCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Left::restartCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Left::nextCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
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
        gui::Text *alert = gui::Text::create();
        alert->setText("LoadingBar right");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create();
        loadingBar->setTag(0);
        loadingBar->loadTexture("cocosgui/sliderProgress.png");
        loadingBar->setDirection(LoadingBarTypeRight);
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Right::previousCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Right::restartCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Right::nextCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
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
        gui::Text* alert = gui::Text::create();
        alert->setText("LoadingBar left scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create();
        loadingBar->setTag(0);
        loadingBar->loadTexture("cocosgui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setSize(Size(300, loadingBar->getContentSize().height));
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Left_Scale9::previousCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Left_Scale9::restartCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Left_Scale9::nextCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
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
        gui::Text *alert = gui::Text::create();
        alert->setText("LoadingBar right scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7f));
        _uiLayer->addChild(alert);
        
        // Create the loading bar
        LoadingBar* loadingBar = LoadingBar::create();
        loadingBar->setTag(0);
        loadingBar->loadTexture("cocosgui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setSize(Size(300, loadingBar->getContentSize().height));
        loadingBar->setDirection(LoadingBarTypeRight);        
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Right_Scale9::previousCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Right_Scale9::restartCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Right_Scale9::nextCallback(Object* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
}