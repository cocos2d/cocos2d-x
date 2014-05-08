

#include "UILoadingBarTest.h"


// UILoadingBarTest_Left

UILoadingBarTest_Left::UILoadingBarTest_Left()
: m_nCount(0)
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
        
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar left");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosui/sliderProgress.png");        
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        m_pUiLayer->addWidget(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Left::update(float delta)
{
    m_nCount++;
    if (m_nCount > 100)
    {
        m_nCount = 0;
    }
        
    UILoadingBar* loadingBar = dynamic_cast<UILoadingBar*>(m_pUiLayer->getWidgetByName("LoadingBar"));
    loadingBar->setPercent(m_nCount);
}

void UILoadingBarTest_Left::previousCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Left::restartCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Left::nextCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
}

// UILoadingBarTest_Right

UILoadingBarTest_Right::UILoadingBarTest_Right()
: m_nCount(0)
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
        
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar right");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosui/sliderProgress.png");
        loadingBar->setDirection(LoadingBarTypeRight);
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        m_pUiLayer->addWidget(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Right::update(float delta)
{
    m_nCount++;
    if (m_nCount > 100)
    {
        m_nCount = 0;
    }
    
    UILoadingBar* loadingBar = dynamic_cast<UILoadingBar*>(m_pUiLayer->getWidgetByName("LoadingBar"));
    loadingBar->setPercent(m_nCount);
}

void UILoadingBarTest_Right::previousCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Right::restartCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Right::nextCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
}

// UILoadingBarTest_Left_Scale9

UILoadingBarTest_Left_Scale9::UILoadingBarTest_Left_Scale9()
: m_nCount(0)
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
        
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar left scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(CCRectMake(0, 0, 0, 0));
        /*===*/
        loadingBar->setSize(CCSizeMake(300, loadingBar->getContentSize().height));
        /*=*/
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        m_pUiLayer->addWidget(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Left_Scale9::update(float delta)
{
    m_nCount++;
    if (m_nCount > 100)
    {
        m_nCount = 0;
    }
    
    UILoadingBar* loadingBar = dynamic_cast<UILoadingBar*>(m_pUiLayer->getWidgetByName("LoadingBar"));
    loadingBar->setPercent(m_nCount);
}

void UILoadingBarTest_Left_Scale9::previousCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Left_Scale9::restartCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Left_Scale9::nextCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
}

// UILoadingBarTest_Right_Scale9

UILoadingBarTest_Right_Scale9::UILoadingBarTest_Right_Scale9()
: m_nCount(0)
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
        
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar right scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(CCRectMake(0, 0, 0, 0));
        /*===*/
        loadingBar->setSize(CCSizeMake(300, loadingBar->getContentSize().height));
        /*=*/
        loadingBar->setDirection(LoadingBarTypeRight);        
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
        m_pUiLayer->addWidget(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest_Right_Scale9::update(float delta)
{
    m_nCount++;
    if (m_nCount > 100)
    {
        m_nCount = 0;
    }
    
    UILoadingBar* loadingBar = dynamic_cast<UILoadingBar*>(m_pUiLayer->getWidgetByName("LoadingBar"));
    loadingBar->setPercent(m_nCount);
}

void UILoadingBarTest_Right_Scale9::previousCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::previousCallback(sender, type);
    }
}

void UILoadingBarTest_Right_Scale9::restartCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::restartCallback(sender, type);
    }
}

void UILoadingBarTest_Right_Scale9::nextCallback(CCObject* sender, TouchEventType type)
{
    if (type == TOUCH_EVENT_ENDED)
    {
        unscheduleUpdate();
        UIScene::nextCallback(sender, type);
    }
}