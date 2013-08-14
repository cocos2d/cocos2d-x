

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
        CCSize widgetSize = m_pWidget->getRect().size;
        
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
        alert->setText("ScrollView");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the scrollview by vertical
        UIScrollView* scrollView = UIScrollView::create();
        scrollView->setClippingEnable(true);
        scrollView->setTouchEnable(true);
        scrollView->setSize(CCSizeMake(280, 150));        
        CCSize backgroundSize = background->getContentSize();
        scrollView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - scrollView->getRect().size.width) / 2,
                               (widgetSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - scrollView->getRect().size.height) / 2));
        m_pUiLayer->addWidget(scrollView);
        
        UIImageView* imageView = UIImageView::create();
        imageView->setTexture("cocosgui/ccicon.png");
        
        float innerWidth = scrollView->getRect().size.width;
        float innerHeight = scrollView->getRect().size.height + imageView->getRect().size.height;
        
        scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));                
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(innerWidth / 2, scrollView->getInerContainerSize().height - button->getRect().size.height / 2));
        scrollView->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(innerWidth / 2, button->getRelativeBottomPos() - button->getRect().size.height));
        scrollView->addChild(textButton);
        
        UIZoomButton* zoomButton = UIZoomButton::create();
        zoomButton->setTouchEnable(true);
        zoomButton->setTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "cocosgui/button.png");
        zoomButton->setTitle("ZoomButton", "ZoomButton", "ZoomButton");
        zoomButton->setNormalFontSize(16);
        zoomButton->setNormalFontName("Marker Felt");
        zoomButton->setPressedFontSize(16);
        zoomButton->setPressedFontName("Marker Felt");
        zoomButton->setDisabledFontSize(16);
        zoomButton->setDisabledFontName("Marker Felt");
        zoomButton->setPreferredSize(CCSizeMake(100, zoomButton->getContentSize().height * 2.0f));
        zoomButton->setPosition(ccp(innerWidth / 2, textButton->getRelativeBottomPos() - textButton->getRect().size.height));
        scrollView->addChild(zoomButton);
        
        imageView->setPosition(ccp(innerWidth / 2, imageView->getRect().size.height / 2));
        scrollView->addChild(imageView);
        
        return true;
    }
    
    return false;
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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the scrollview alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("Move by horizontal direction");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);            
        
        UILabel *alert = UILabel::create();
        alert->setText("ScrollView");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the scrollview by horizontal
        UIScrollView* scrollView = UIScrollView::create();        
        scrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        scrollView->setClippingEnable(true);
        scrollView->setTouchEnable(true);
        scrollView->setSize(CCSizeMake(280, 150));
        scrollView->setInnerContainerSize(scrollView->getRect().size);
        CCSize backgroundSize = background->getContentSize();
        scrollView->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - scrollView->getRect().size.width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - scrollView->getRect().size.height) / 2));
        m_pUiLayer->addWidget(scrollView);
        
        UIImageView* imageView = UIImageView::create();
        imageView->setTexture("cocosgui/ccicon.png");
        
        float innerWidth = scrollView->getRect().size.width + imageView->getRect().size.width;
        float innerHeight = scrollView->getRect().size.height;
        
        scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2,
                                scrollView->getInerContainerSize().height - button->getRect().size.height / 2));
        scrollView->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(button->getRelativeRightPos() + button->getRect().size.width / 2,
                                    button->getRelativeBottomPos() - button->getRect().size.height / 2));
        scrollView->addChild(textButton);
        
        UIZoomButton* zoomButton = UIZoomButton::create();
        zoomButton->setTouchEnable(true);
        zoomButton->setTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "cocosgui/button.png");
        zoomButton->setTitle("ControlButton", "ControlButton", "ControlButton");
        zoomButton->setNormalFontSize(16);
        zoomButton->setNormalFontName("Marker Felt");
        zoomButton->setPressedFontSize(16);
        zoomButton->setPressedFontName("Marker Felt");
        zoomButton->setDisabledFontSize(16);
        zoomButton->setDisabledFontName("Marker Felt");
        zoomButton->setPreferredSize(CCSizeMake(100, zoomButton->getContentSize().height * 2.0f));
        zoomButton->setPosition(ccp(textButton->getRelativeRightPos() + textButton->getRect().size.width / 2,
                                    textButton->getRelativeBottomPos() - textButton->getRect().size.height / 2));
        scrollView->addChild(zoomButton);
                
        imageView->setPosition(ccp(innerWidth - imageView->getRect().size.width / 2,
                                   zoomButton->getRelativeBottomPos() - zoomButton->getRect().size.height / 2));
        scrollView->addChild(imageView);                
        
        return true;
    }
    
    return false;
}