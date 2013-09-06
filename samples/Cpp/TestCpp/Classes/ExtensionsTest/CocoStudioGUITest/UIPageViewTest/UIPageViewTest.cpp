

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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName(font_UIPageViewTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the black background
        UILabel *alert = UILabel::create();
        alert->setText("PageView");
        alert->setFontName(font_UIPageViewTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
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
            Layout* layout = Layout::create();
            layout->setSize(CCSizeMake(240, 130));
            
            UIImageView* imageView = UIImageView::create();
            imageView->setTouchEnable(true);
            imageView->setScale9Enabled(true);
            imageView->loadTexture("cocosgui/scrollviewbg.png");
            imageView->setSize(CCSizeMake(240, 130));
            imageView->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
            layout->addChild(imageView);
            
            UILabel* label = UILabel::create();
            label->setText(CCString::createWithFormat("page %d", (i + 1))->getCString());
            label->setFontName(font_UIPageViewTest);
            label->setFontSize(30);
            label->setColor(ccc3(192, 192, 192));
            label->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
            layout->addChild(label);
            
            pageView->addPage(layout);
        }
        
        pageView->addPageTurningEvent(this, coco_PageView_PageTurning_selector(UIPageViewTest::pageTurningEvent));
        
        m_pUiLayer->addWidget(pageView);
        
        return true;
    }
    return false;
}

void UIPageViewTest::pageTurningEvent(CCObject *pSender)
{
    UIPageView* pageView = dynamic_cast<UIPageView*>(pSender);
    CCLOG("page = %d", pageView->getPage());
    
    m_pDisplayValueLabel->setText(CCString::createWithFormat("page = %d", pageView->getPage() + 1)->getCString());
}