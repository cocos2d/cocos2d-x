

#include "UIPageViewTest.h"

// UIPageViewTest
UIPageViewTest::UIPageViewTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UIPageViewTest::~UIPageViewTest()
{
}

bool UIPageViewTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the black background
        UILabel *alert = UILabel::create();
        alert->setText("PageView");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));        
        
        // Create the page view
        UIPageView* pageView = UIPageView::create();
        pageView->setTouchEnable(true);
        pageView->setSize(CCSizeMake(240, 130));
        CCSize backgroundSize = background->getContentSize();
        pageView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                  (backgroundSize.width - pageView->getRect().size.width) / 2,
                                  (widgetSize.height - backgroundSize.height) / 2 +
                                  (backgroundSize.height - pageView->getRect().size.height) / 2));
        
        for (int i = 0; i < 3; ++i)
        {
            UIPanel* panel = UIPanel::create();
            panel->setSize(CCSizeMake(240, 130));
            
            UIImageView* imageView = UIImageView::create();
            imageView->setTouchEnable(true);
            imageView->setScale9Enable(true);
            imageView->setTexture("cocosgui/scrollviewbg.png");
            imageView->setScale9Size(CCSizeMake(240, 130));
            imageView->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
            panel->addChild(imageView);
            
            UILabel* label = UILabel::create();
            label->setText(CCString::createWithFormat("page %d", (i + 1))->getCString());
            label->setFontName("Marker Felt");
            label->setFontSize(30);
            label->setColor(ccc3(192, 192, 192));
            label->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
            panel->addChild(label);
            
            pageView->addPage(panel);
        }
        
        m_pUiLayer->addWidget(pageView);
        
        return true;
    }
    return false;
}