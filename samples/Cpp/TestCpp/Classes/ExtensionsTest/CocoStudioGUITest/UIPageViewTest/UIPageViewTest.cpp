

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
        CCSize widgetSize = m_pWidget->getSize();
        
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
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the page view
        UIPageView* pageView = UIPageView::create();
        pageView->setTouchEnabled(true);
        pageView->setSize(CCSizeMake(240, 130));
        CCSize backgroundSize = background->getContentSize();
        pageView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                  (backgroundSize.width - pageView->getSize().width) / 2,
                                  (widgetSize.height - backgroundSize.height) / 2 +
                                  (backgroundSize.height - pageView->getSize().height) / 2));
        
        for (int i = 0; i < 3; ++i)
        {
            UILayout* layout = UILayout::create();
            layout->setSize(CCSizeMake(240, 130));
            
            UIImageView* imageView = UIImageView::create();
            imageView->setTouchEnabled(true);
            imageView->setScale9Enabled(true);
            imageView->loadTexture("cocosui/scrollviewbg.png");
            imageView->setSize(CCSizeMake(240, 130));
            imageView->setPosition(ccp(layout->getSize().width / 2, layout->getSize().height / 2));
            layout->addChild(imageView);
            
            UILabel* label = UILabel::create();
            label->setText(CCString::createWithFormat("page %d", (i + 1))->getCString());
            label->setFontName("Marker Felt");
            label->setFontSize(30);
            label->setColor(ccc3(192, 192, 192));
            label->setPosition(ccp(layout->getSize().width / 2, layout->getSize().height / 2));
            layout->addChild(label);
            
            pageView->addPage(layout);
        }        
        pageView->addEventListenerPageView(this, pagevieweventselector(UIPageViewTest::pageViewEvent));
        
        m_pUiLayer->addWidget(pageView);
        
        return true;
    }
    return false;
}

void UIPageViewTest::pageViewEvent(CCObject *pSender, PageViewEventType type)
{
    switch (type)
    {
        case PAGEVIEW_EVENT_TURNING:
        {
            UIPageView* pageView = dynamic_cast<UIPageView*>(pSender);
            
            m_pDisplayValueLabel->setText(CCString::createWithFormat("page = %d", pageView->getCurPageIndex() + 1)->getCString());
        }
            break;
            
        default:
            break;
    }
}