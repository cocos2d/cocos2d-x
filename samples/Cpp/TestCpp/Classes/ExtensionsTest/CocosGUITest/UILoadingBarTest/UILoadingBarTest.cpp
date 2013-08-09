

#include "UILoadingBarTest.h"

// UILoadingBarTest

UILoadingBarTest::UILoadingBarTest()
: m_nCount(0)
{
    
}

UILoadingBarTest::~UILoadingBarTest()
{
    unscheduleUpdate();
}

bool UILoadingBarTest::init()
{
    if (UIScene::init())
    {
        scheduleUpdate();
        
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LoadingBar");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the loading bar
        UILoadingBar* loadingBar = UILoadingBar::create();
        loadingBar->setName("LoadingBar");
        loadingBar->setTexture("cocosgui/sliderProgress.png");
        loadingBar->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + loadingBar->getRect().size.height / 4.0f));
        m_pUiLayer->addWidget(loadingBar);
        
        return true;
    }
    return false;
}

void UILoadingBarTest::update(float delta)
{
    m_nCount++;
    if (m_nCount > 100)
    {
        m_nCount = 0;
    }
        
    UILoadingBar* loadingBar = dynamic_cast<UILoadingBar*>(m_pUiLayer->getWidgetByName("LoadingBar"));
    loadingBar->setPercent(m_nCount);
}