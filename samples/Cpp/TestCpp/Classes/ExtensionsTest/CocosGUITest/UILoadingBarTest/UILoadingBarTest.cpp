

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
        
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->setTexture("cocosgui/sliderProgress.png");        
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getRect().size.height / 4.0f));
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

void UILoadingBarTest_Left::previousCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::previousCallback(sender);
}

void UILoadingBarTest_Left::restartCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::restartCallback(sender);
}

void UILoadingBarTest_Left::nextCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::nextCallback(sender);
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
        
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->setTexture("cocosgui/sliderProgress.png");
        loadingBar->setDirection(LoadingBarTypeRight);
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getRect().size.height / 4.0f));
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

void UILoadingBarTest_Right::previousCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::previousCallback(sender);
}

void UILoadingBarTest_Right::restartCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::restartCallback(sender);
}

void UILoadingBarTest_Right::nextCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::nextCallback(sender);
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
        
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->setTexture("cocosgui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(CCRectMake(0, 0, 0, 0));
        loadingBar->setSize(CCSizeMake(300, 30));
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getRect().size.height / 4.0f));
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

void UILoadingBarTest_Left_Scale9::previousCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::previousCallback(sender);
}

void UILoadingBarTest_Left_Scale9::restartCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::restartCallback(sender);
}

void UILoadingBarTest_Left_Scale9::nextCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::nextCallback(sender);
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
        
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar");
        alert->setFontName(font_UILoadingBarTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->setTexture("cocosgui/slider_bar_active_9patch.png");
        loadingBar->setScale9Enabled(true);
        loadingBar->setCapInsets(CCRectMake(0, 0, 0, 0));
        loadingBar->setSize(CCSizeMake(300, 30));
        loadingBar->setDirection(LoadingBarTypeRight);        
        loadingBar->setPercent(0);
        
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getRect().size.height / 4.0f));
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

void UILoadingBarTest_Right_Scale9::previousCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::previousCallback(sender);
}

void UILoadingBarTest_Right_Scale9::restartCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::restartCallback(sender);
}

void UILoadingBarTest_Right_Scale9::nextCallback(CCObject* sender)
{
	unscheduleUpdate();
	UIScene::nextCallback(sender);
}