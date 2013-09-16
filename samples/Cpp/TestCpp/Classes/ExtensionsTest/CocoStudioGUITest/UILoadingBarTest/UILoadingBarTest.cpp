

#include "UILoadingBarTest.h"

const char* font_UILoadingBarTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

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
        
        Size widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosgui/sliderProgress.png");
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Left::previousCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::previousCallback(sender, type);
}

void UILoadingBarTest_Left::restartCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::restartCallback(sender, type);
}

void UILoadingBarTest_Left::nextCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::nextCallback(sender, type);
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
        
        Size widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosgui/sliderProgress.png");
        loadingBar->setDirection(LoadingBarTypeRight);
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Right::previousCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::previousCallback(sender, type);
}

void UILoadingBarTest_Right::restartCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::restartCallback(sender, type);
}

void UILoadingBarTest_Right::nextCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::nextCallback(sender, type);
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
        
        Size widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar Scale9 Render");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosgui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setSize(Size(300, 30));
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Left_Scale9::previousCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::previousCallback(sender, type);
}

void UILoadingBarTest_Left_Scale9::restartCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::restartCallback(sender, type);
}

void UILoadingBarTest_Left_Scale9::nextCallback(Object* sender, TouchEventType type)
{
	unscheduleUpdate();
	UIScene::nextCallback(sender, type);
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
        
        Size widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar Scale9 Render");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->loadTexture("cocosgui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(Rect(0, 0, 0, 0));
        loadingBar->setSize(Size(300, 30));
        loadingBar->setDirection(LoadingBarTypeRight);        
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
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

void UILoadingBarTest_Right_Scale9::previousCallback(Object* sender, TouchEventType type)
{
	UIScene::previousCallback(sender, type);
}

void UILoadingBarTest_Right_Scale9::restartCallback(Object* sender, TouchEventType type)
{
	UIScene::restartCallback(sender, type);
}

void UILoadingBarTest_Right_Scale9::nextCallback(Object* sender, TouchEventType type)
{
	UIScene::nextCallback(sender, type);
}