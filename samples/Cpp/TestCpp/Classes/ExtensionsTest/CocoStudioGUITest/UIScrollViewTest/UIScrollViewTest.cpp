

#include "UIScrollViewTest.h"


// UIScrollViewTest_Vertical

UIScrollViewTest_Vertical::UIScrollViewTest_Vertical()
: m_pDisplayValueLabel(NULL)
{
}

UIScrollViewTest_Vertical::~UIScrollViewTest_Vertical()
{
}

bool UIScrollViewTest_Vertical::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by vertical direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("ScrollView vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the scrollview by vertical
        UIScrollView* scrollView = UIScrollView::create();
        scrollView->setTouchEnabled(true);
        scrollView->setBounceEnabled(true);
        scrollView->setSize(CCSizeMake(280, 150));        
        CCSize backgroundSize = background->getContentSize();
        scrollView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - scrollView->getSize().width) / 2,
                               (widgetSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - scrollView->getSize().height) / 2));
        scrollView->addEventListenerScrollView(this, scrollvieweventselector(UIScrollViewTest_Vertical::scrollEvent));
        m_pUiLayer->addWidget(scrollView);
        
        UIImageView* imageView = UIImageView::create();
        imageView->loadTexture("cocosui/ccicon.png");
        
        float innerWidth = scrollView->getSize().width;
        float innerHeight = scrollView->getSize().height + imageView->getSize().height * 2;
        
        scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
        
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setPosition(ccp(innerWidth / 2, scrollView->getInnerContainerSize().height - button->getSize().height / 2));
        scrollView->addChild(button);
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(ccp(innerWidth / 2, button->getBottomInParent() - button->getSize().height));
        scrollView->addChild(titleButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->setScale9Enabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(innerWidth / 2, titleButton->getBottomInParent() - titleButton->getSize().height));
        scrollView->addChild(button_scale9);
        
        imageView->setPosition(ccp(innerWidth / 2, imageView->getSize().height / 2));
        scrollView->addChild(imageView);        
        return true;
    }
    
    return false;
}

void UIScrollViewTest_Vertical::scrollEvent(cocos2d::CCObject *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SCROLLING:
            CCLOG("Scrolling");
            break;
            
        default:
            break;
    }
}

void UIScrollViewTest_Vertical::touchEvent(CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCLOG("button touch ended");
            break;
            
        default:
            break;
    }
}

// UIScrollViewTest_Horizontal

UIScrollViewTest_Horizontal::UIScrollViewTest_Horizontal()
: m_pDisplayValueLabel(NULL)
{
}

UIScrollViewTest_Horizontal::~UIScrollViewTest_Horizontal()
{
}

bool UIScrollViewTest_Horizontal::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);            
        
        UILabel *alert = UILabel::create();
        alert->setText("ScrollView horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the scrollview by horizontal
        UIScrollView* scrollView = UIScrollView::create();        
        scrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        scrollView->setBounceEnabled(true);
        scrollView->setTouchEnabled(true);
        scrollView->setSize(CCSizeMake(280, 150));
        scrollView->setInnerContainerSize(scrollView->getSize());
        CCSize backgroundSize = background->getContentSize();
        scrollView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - scrollView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - scrollView->getSize().height) / 2));
        m_pUiLayer->addWidget(scrollView);
        
        UIImageView* imageView = UIImageView::create();
        imageView->loadTexture("cocosui/ccicon.png");
        
        float innerWidth = scrollView->getSize().width + imageView->getSize().width * 2;
        float innerHeight = scrollView->getSize().height;
        
        scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getSize().width / 2,
                                scrollView->getInnerContainerSize().height - button->getSize().height / 2));
        scrollView->addChild(button);
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(ccp(button->getRightInParent() + button->getSize().width / 2,
                                    button->getBottomInParent() - button->getSize().height / 2));
        scrollView->addChild(titleButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->setScale9Enabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(titleButton->getRightInParent() + titleButton->getSize().width / 2,
                                       titleButton->getBottomInParent() - titleButton->getSize().height / 2));
        scrollView->addChild(button_scale9);                
                
        imageView->setPosition(ccp(innerWidth - imageView->getSize().width / 2,
                                   button_scale9->getBottomInParent() - button_scale9->getSize().height / 2));
        scrollView->addChild(imageView);                
        
        return true;
    }
    
    return false;
}

/*===*/
// UIScrollViewTest_Both
UIScrollViewTest_Both::UIScrollViewTest_Both()
: m_pDisplayValueLabel(NULL)
{
    
}

UIScrollViewTest_Both::~UIScrollViewTest_Both()
{
}

bool UIScrollViewTest_Both::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();;
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by any direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("ScrollView both");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the dragpanel
        UIScrollView* scrollView = UIScrollView::create();
        scrollView->setDirection(SCROLLVIEW_DIR_BOTH);
        scrollView->setTouchEnabled(true);
        scrollView->setBounceEnabled(true);
        scrollView->setBackGroundImageScale9Enabled(true);
        scrollView->setBackGroundImage("cocosui/green_edit.png");
        scrollView->setSize(CCSizeMake(210, 122.5));
        CCSize backgroundSize = background->getContentSize();
        scrollView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - scrollView->getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - scrollView->getSize().height) / 2));
        UIImageView* imageView = UIImageView::create();
        imageView->setTouchEnabled(true);
        imageView->loadTexture("cocosui/b11.png");
        scrollView->addChild(imageView);
        
        scrollView->setInnerContainerSize(imageView->getContentSize());
        CCSize innerSize = scrollView->getInnerContainerSize();
        imageView->setPosition(ccp(innerSize.width / 2, innerSize.height / 2));
        
        m_pUiLayer->addWidget(scrollView);
        
        return true;
    }
    
    return false;
}

// UIScrollViewTest_ScrollToPercentBothDirection
UIScrollViewTest_ScrollToPercentBothDirection::UIScrollViewTest_ScrollToPercentBothDirection()
: m_pDisplayValueLabel(NULL)
{
    
}

UIScrollViewTest_ScrollToPercentBothDirection::~UIScrollViewTest_ScrollToPercentBothDirection()
{
}

bool UIScrollViewTest_ScrollToPercentBothDirection::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
//        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("ScrollView scroll to percent both directrion");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        UILayout* background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        UIScrollView* sc = UIScrollView::create();
        sc->setBackGroundColor(ccGREEN);
        sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        sc->setDirection(SCROLLVIEW_DIR_BOTH);
        sc->setInnerContainerSize(CCSizeMake(480, 320));
        sc->setSize(CCSizeMake(100,100));
        CCSize backgroundSize = background->getContentSize();
        sc->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                            (backgroundSize.width - sc->getSize().width) / 2,
                            (widgetSize.height - backgroundSize.height) / 2 +
                            (backgroundSize.height - sc->getSize().height) / 2));
        sc->scrollToPercentBothDirection(ccp(50, 50), 1, true);
        UIImageView* iv = UIImageView::create();
        iv->loadTexture("cocosui/Hello.png");
        iv->setPosition(ccp(240, 160));
        sc->addChild(iv);
        m_pUiLayer->addWidget(sc);
        
        return true;
    }
    return false;
}

// UIScrollViewTest_ScrollToPercentBothDirection_Bounce
UIScrollViewTest_ScrollToPercentBothDirection_Bounce::UIScrollViewTest_ScrollToPercentBothDirection_Bounce()
: m_pDisplayValueLabel(NULL)
{
    
}

UIScrollViewTest_ScrollToPercentBothDirection_Bounce::~UIScrollViewTest_ScrollToPercentBothDirection_Bounce()
{
}

bool UIScrollViewTest_ScrollToPercentBothDirection_Bounce::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
//        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("ScrollView scroll to percent both directrion bounce");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        UILayout* background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        UIScrollView* sc = UIScrollView::create();
        sc->setBackGroundColor(ccGREEN);
        sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        sc->setBounceEnabled(true);
        sc->setDirection(SCROLLVIEW_DIR_BOTH);
        sc->setInnerContainerSize(CCSizeMake(480, 320));
        sc->setSize(CCSizeMake(100,100));
        CCSize backgroundSize = background->getContentSize();
        sc->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                            (backgroundSize.width - sc->getSize().width) / 2,
                            (widgetSize.height - backgroundSize.height) / 2 +
                            (backgroundSize.height - sc->getSize().height) / 2));
        sc->scrollToPercentBothDirection(ccp(50, 50), 1, true);
        UIImageView* iv = UIImageView::create();
        iv->loadTexture("cocosui/Hello.png");
        iv->setPosition(ccp(240, 160));
        sc->addChild(iv);
        m_pUiLayer->addWidget(sc);
        return true;
    }
    
    return false;
}
