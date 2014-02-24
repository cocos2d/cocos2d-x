

#include "UIScrollViewTest.h"


// UIScrollViewTest_Vertical

UIScrollViewTest_Vertical::UIScrollViewTest_Vertical()
: _displayValueLabel(nullptr)
{
}

UIScrollViewTest_Vertical::~UIScrollViewTest_Vertical()
{
}

bool UIScrollViewTest_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("Move by vertical direction");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("ScrollView vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the scrollview by vertical
        gui::ScrollView* scrollView = gui::ScrollView::create();
        scrollView->setTouchEnabled(true);
        scrollView->setSize(Size(280.0f, 150.0f));        
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                               (backgroundSize.width - scrollView->getSize().width) / 2.0f,
                               (widgetSize.height - backgroundSize.height) / 2.0f +
                               (backgroundSize.height - scrollView->getSize().height) / 2.0f));
        _uiLayer->addChild(scrollView);
        
        ImageView* imageView = ImageView::create();
        imageView->loadTexture("cocosgui/ccicon.png");
        
        float innerWidth = scrollView->getSize().width;
        float innerHeight = scrollView->getSize().height + imageView->getSize().height;
        
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));                
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(innerWidth / 2.0f, scrollView->getInnerContainerSize().height - button->getSize().height / 2.0f));
        scrollView->addChild(button);
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Point(innerWidth / 2.0f, button->getBottomInParent() - button->getSize().height));
        scrollView->addChild(titleButton);
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->setScale9Enabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        button_scale9->setPosition(Point(innerWidth / 2.0f, titleButton->getBottomInParent() - titleButton->getSize().height));
        scrollView->addChild(button_scale9);
        
        imageView->setPosition(Point(innerWidth / 2.0f, imageView->getSize().height / 2.0f));
        scrollView->addChild(imageView);            
        
        return true;
    }
    
    return false;
}

// UIScrollViewTest_Horizontal

UIScrollViewTest_Horizontal::UIScrollViewTest_Horizontal()
: _displayValueLabel(nullptr)
{
}

UIScrollViewTest_Horizontal::~UIScrollViewTest_Horizontal()
{
}

bool UIScrollViewTest_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("Move by horizontal direction");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);            
        
        gui::Text* alert = gui::Text::create();
        alert->setText("ScrollView horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the scrollview by horizontal
        gui::ScrollView* scrollView = gui::ScrollView::create();
        scrollView->setBounceEnabled(true);
        scrollView->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
        scrollView->setTouchEnabled(true);
        scrollView->setSize(Size(280.0f, 150.0f));
        scrollView->setInnerContainerSize(scrollView->getSize());
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - scrollView->getSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - scrollView->getSize().height) / 2.0f));
        _uiLayer->addChild(scrollView);
        
        ImageView* imageView = ImageView::create();
        imageView->loadTexture("cocosgui/ccicon.png");
        
        float innerWidth = scrollView->getSize().width + imageView->getSize().width;
        float innerHeight = scrollView->getSize().height;
        
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(button->getSize().width / 2.0f,
                                scrollView->getInnerContainerSize().height - button->getSize().height / 2.0f));
        scrollView->addChild(button);
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Point(button->getRightInParent() + button->getSize().width / 2.0f,
                                    button->getBottomInParent() - button->getSize().height / 2.0f));
        scrollView->addChild(titleButton);
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->setScale9Enabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        button_scale9->setPosition(Point(titleButton->getRightInParent() + titleButton->getSize().width / 2.0f,
                                       titleButton->getBottomInParent() - titleButton->getSize().height / 2.0f));
        scrollView->addChild(button_scale9);                
                
        imageView->setPosition(Point(innerWidth - imageView->getSize().width / 2.0f,
                                   button_scale9->getBottomInParent() - button_scale9->getSize().height / 2.0f));
        scrollView->addChild(imageView);                
        
        return true;
    }
    
    return false;
}

// UIScrollViewTest_Both
UIScrollViewTest_Both::UIScrollViewTest_Both()
: _displayValueLabel(nullptr)
{
    
}

UIScrollViewTest_Both::~UIScrollViewTest_Both()
{
}

bool UIScrollViewTest_Both::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();;
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("Move by any direction");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("ScrollView both");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the dragpanel
        gui::ScrollView* scrollView = gui::ScrollView::create();
        scrollView->setDirection(SCROLLVIEW_DIR_BOTH);
        scrollView->setTouchEnabled(true);
        scrollView->setBounceEnabled(true);
        scrollView->setBackGroundImageScale9Enabled(true);
        scrollView->setBackGroundImage("cocosgui/green_edit.png");
        scrollView->setSize(Size(210, 122.5));
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - scrollView->getSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - scrollView->getSize().height) / 2.0f));
        ImageView* imageView = ImageView::create();
        imageView->setTouchEnabled(true);
        imageView->loadTexture("Hello.png");
        scrollView->addChild(imageView);
        
        scrollView->setInnerContainerSize(imageView->getContentSize());
        Size innerSize = scrollView->getInnerContainerSize();
        imageView->setPosition(Point(innerSize.width / 2.0f, innerSize.height / 2.0f));
        
        _uiLayer->addChild(scrollView);
        
        return true;
    }
    
    return false;
}

// UIScrollViewTest_ScrollToPercentBothDirection
UIScrollViewTest_ScrollToPercentBothDirection::UIScrollViewTest_ScrollToPercentBothDirection()
: _displayValueLabel(nullptr)
{
    
}

UIScrollViewTest_ScrollToPercentBothDirection::~UIScrollViewTest_ScrollToPercentBothDirection()
{
}

bool UIScrollViewTest_ScrollToPercentBothDirection::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = gui::Text::create();
//        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("ScrollView scroll to percent both directrion");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        gui::ScrollView* sc = gui::ScrollView::create();
        sc->setBackGroundColor(Color3B::GREEN);
        sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        sc->setDirection(SCROLLVIEW_DIR_BOTH);
        sc->setInnerContainerSize(Size(480, 320));
        sc->setSize(Size(100,100));
        Size backgroundSize = background->getContentSize();
        sc->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                              (backgroundSize.width - sc->getSize().width) / 2.0f,
                              (widgetSize.height - backgroundSize.height) / 2.0f +
                              (backgroundSize.height - sc->getSize().height) / 2.0f));
        sc->scrollToPercentBothDirection(Point(50, 50), 1, true);
        ImageView* iv = ImageView::create();
        iv->loadTexture("cocosgui/Hello.png");
        iv->setPosition(Point(240, 160));
        sc->addChild(iv);
        _uiLayer->addChild(sc);
        
        return true;
    }
    return false;
}

// UIScrollViewTest_ScrollToPercentBothDirection_Bounce
UIScrollViewTest_ScrollToPercentBothDirection_Bounce::UIScrollViewTest_ScrollToPercentBothDirection_Bounce()
: _displayValueLabel(nullptr)
{
    
}

UIScrollViewTest_ScrollToPercentBothDirection_Bounce::~UIScrollViewTest_ScrollToPercentBothDirection_Bounce()
{
}

bool UIScrollViewTest_ScrollToPercentBothDirection_Bounce::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = gui::Text::create();
//        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("ScrollView scroll to percent both directrion bounce");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        gui::ScrollView* sc = gui::ScrollView::create();
        sc->setBackGroundColor(Color3B::GREEN);
        sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        sc->setBounceEnabled(true);
        sc->setDirection(SCROLLVIEW_DIR_BOTH);
        sc->setInnerContainerSize(Size(480, 320));
        sc->setSize(Size(100,100));
        Size backgroundSize = background->getContentSize();
        sc->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                              (backgroundSize.width - sc->getSize().width) / 2.0f,
                              (widgetSize.height - backgroundSize.height) / 2.0f +
                              (backgroundSize.height - sc->getSize().height) / 2.0f));
        sc->scrollToPercentBothDirection(Point(50, 50), 1, true);
        ImageView* iv = ImageView::create();
        iv->loadTexture("cocosgui/Hello.png");
        iv->setPosition(Point(240, 160));
        sc->addChild(iv);
        _uiLayer->addChild(sc);
        return true;
    }
    
    return false;
}
