

#include "UIPageViewTest.h"

const char* font_UIPageViewTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

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
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName(font_UIPageViewTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the black background
        UILabel *alert = UILabel::create();
        alert->setText("PageView");
        alert->setFontName(font_UIPageViewTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the page view
        UIPageView* pageView = UIPageView::create();
        pageView->setTouchEnabled(true);
        pageView->setSize(Size(240, 130));
        Size backgroundSize = background->getContentSize();
        pageView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2 +
                                  (backgroundSize.width - pageView->getSize().width) / 2,
                                  (widgetSize.height - backgroundSize.height) / 2 +
                                  (backgroundSize.height - pageView->getSize().height) / 2));
        
        for (int i = 0; i < 3; ++i)
        {
            UILayout* layout = UILayout::create();
            layout->setSize(Size(240, 130));
            
            UIImageView* imageView = UIImageView::create();
            imageView->setTouchEnabled(true);
            imageView->setScale9Enabled(true);
            imageView->loadTexture("cocosgui/scrollviewbg.png");
            imageView->setSize(Size(240, 130));
            imageView->setPosition(Point(layout->getSize().width / 2, layout->getSize().height / 2));
            layout->addChild(imageView);
            
            UILabel* label = UILabel::create();
            label->setText(CCString::createWithFormat("page %d", (i + 1))->getCString());
            label->setFontName(font_UIPageViewTest);
            label->setFontSize(30);
            label->setColor(Color3B(192, 192, 192));
            label->setPosition(Point(layout->getSize().width / 2, layout->getSize().height / 2));
            layout->addChild(label);
            
            pageView->addPage(layout);
        }
        pageView->addEventListener(this, pagevieweventselector(UIPageViewTest::pageViewEvent));
        
        m_pUiLayer->addWidget(pageView);
        
        return true;
    }
    return false;
}

void UIPageViewTest::pageViewEvent(Object *pSender, PageViewEventType type)
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
