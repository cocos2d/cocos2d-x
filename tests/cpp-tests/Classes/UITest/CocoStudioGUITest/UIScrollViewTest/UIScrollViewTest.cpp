#include "UIScrollViewTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIScrollViewTests::UIScrollViewTests()
{
    ADD_TEST_CASE(UIScrollViewTest_Vertical);
    ADD_TEST_CASE(UIScrollViewTest_Horizontal);
    ADD_TEST_CASE(UIScrollViewTest_Both);
    ADD_TEST_CASE(UIScrollViewTest_ScrollToPercentBothDirection);
    ADD_TEST_CASE(UIScrollViewTest_ScrollToPercentBothDirection_Bounce);
    ADD_TEST_CASE(UIScrollViewNestTest);
    ADD_TEST_CASE(UIScrollViewRotated);
    ADD_TEST_CASE(UIScrollViewDisableTest);
    ADD_TEST_CASE(UIScrollViewInnerSize);
}
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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = Text::create("Move by vertical direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("ScrollView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the scrollview by vertical
        ui::ScrollView* scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(280.0f, 100.0f));
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                               (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
                               (widgetSize.height - backgroundSize.height) / 2.0f +
                               (backgroundSize.height - scrollView->getContentSize().height) / 2.0f));
		scrollView->setScrollBarWidth(4);
		scrollView->setScrollBarPositionFromCorner(Vec2(2, 2));
		scrollView->setScrollBarColor(Color3B::WHITE);
        _uiLayer->addChild(scrollView);
        
        ImageView* imageView = ImageView::create("cocosui/ccicon.png");
        
        float innerWidth = scrollView->getContentSize().width;
        float innerHeight = scrollView->getContentSize().height + imageView->getContentSize().height;
        
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));                
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(innerWidth / 2.0f, scrollView->getInnerContainerSize().height - button->getContentSize().height / 2.0f));
        scrollView->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(innerWidth / 2.0f, button->getBottomBoundary() - button->getContentSize().height));
        scrollView->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(innerWidth / 2.0f, titleButton->getBottomBoundary() - titleButton->getContentSize().height));
        scrollView->addChild(button_scale9);
        
        imageView->setPosition(Vec2(innerWidth / 2.0f, imageView->getContentSize().height / 2.0f));
        scrollView->addChild(imageView);            
        scrollView->scrollToBottom(2.0, true);
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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = Text::create("Move by horizontal direction","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);            
        
        Text* alert = Text::create("ScrollView horizontal","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the scrollview by horizontal
        ui::ScrollView* scrollView = ui::ScrollView::create();
        scrollView->setBounceEnabled(true);
        scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
        scrollView->setContentSize(Size(280.0f, 150.0f));
        scrollView->setInnerContainerSize(scrollView->getContentSize());
		scrollView->setScrollBarPositionFromCorner(Vec2(4, 4));
		scrollView->setScrollBarColor(Color3B::YELLOW);
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition((widgetSize - scrollView->getContentSize()) / 2.0f);
        _uiLayer->addChild(scrollView);
        
        ImageView* imageView = ImageView::create("cocosui/ccicon.png");
        
        float innerWidth = scrollView->getContentSize().width + imageView->getContentSize().width;
        float innerHeight = scrollView->getContentSize().height;
        
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                                scrollView->getInnerContainerSize().height - button->getContentSize().height / 2.0f));
        scrollView->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(button->getRightBoundary() + button->getContentSize().width / 2.0f,
                                    button->getBottomBoundary() - button->getContentSize().height / 2.0f));
        scrollView->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(titleButton->getRightBoundary() + titleButton->getContentSize().width / 2.0f,
                                       titleButton->getBottomBoundary() - titleButton->getContentSize().height / 2.0f));
        scrollView->addChild(button_scale9);
                
        imageView->setPosition(Vec2(innerWidth - imageView->getContentSize().width / 2.0f,
                                   button_scale9->getBottomBoundary() - button_scale9->getContentSize().height / 2.0f));
        scrollView->addChild(imageView);

        // Jump to right
        scrollView->jumpToRight();

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
        Size widgetSize = _widget->getContentSize();;
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("Move by any direction","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("ScrollView both","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the dragpanel
        ui::ScrollView* scrollView = ui::ScrollView::create();
        scrollView->setDirection(ui::ScrollView::Direction::BOTH);
        scrollView->setTouchEnabled(true);
        scrollView->setBounceEnabled(true);
        scrollView->setBackGroundImageScale9Enabled(true);
        scrollView->setBackGroundImage("cocosui/green_edit.png");
        scrollView->setContentSize(Size(210, 122.5));
		scrollView->setScrollBarWidth(4);
		scrollView->setScrollBarPositionFromCorner(Vec2(6, 6));
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - scrollView->getContentSize().height) / 2.0f));
        ImageView* imageView = ImageView::create("Hello.png");
        scrollView->addChild(imageView);
        
        scrollView->setInnerContainerSize(imageView->getContentSize());
        Size innerSize = scrollView->getInnerContainerSize();
        imageView->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height / 2.0f));
        
        _uiLayer->addChild(scrollView);

        // Jump to right bottom
        scrollView->jumpToBottomRight();

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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf",30);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("ScrollView scroll to percent both direction without scroll bar","fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        ui::ScrollView* sc = ui::ScrollView::create();
        sc->setBackGroundColor(Color3B::GREEN);
        sc->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        sc->setDirection(ui::ScrollView::Direction::BOTH);
        sc->setInnerContainerSize(Size(480, 320));
        sc->setContentSize(Size(100,100));
		sc->setScrollBarEnabled(false);
        Size backgroundSize = background->getContentSize();
        sc->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                              (backgroundSize.width - sc->getContentSize().width) / 2.0f,
                              (widgetSize.height - backgroundSize.height) / 2.0f +
                              (backgroundSize.height - sc->getContentSize().height) / 2.0f));
        sc->scrollToPercentBothDirection(Vec2(50, 50), 1, true);
        ImageView* iv = ImageView::create("cocosui/Hello.png");
        iv->setPosition(Vec2(240, 160));
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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the dragpanel events will be displayed
        _displayValueLabel = Text::create("No Event","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("ScrollView scroll to percent both direction bounce","fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        ui::ScrollView* sc = ui::ScrollView::create();
        sc->setBackGroundColor(Color3B::GREEN);
        sc->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        sc->setBounceEnabled(true);
        sc->setDirection(ui::ScrollView::Direction::BOTH);
        sc->setInnerContainerSize(Size(480, 320));
        sc->setContentSize(Size(100,100));
		sc->setScrollBarPositionFromCornerForHorizontal(Vec2(5, sc->getContentSize().height - 5));
		sc->setScrollBarPositionFromCornerForVertical(Vec2(sc->getContentSize().width - 5, 5));
		sc->setScrollBarAutoHideEnabled(false);
        Size backgroundSize = background->getContentSize();
        sc->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                              (backgroundSize.width - sc->getContentSize().width) / 2.0f,
                              (widgetSize.height - backgroundSize.height) / 2.0f +
                              (backgroundSize.height - sc->getContentSize().height) / 2.0f));
        sc->scrollToPercentBothDirection(Vec2(50, 50), 1, true);
        ImageView* iv = ImageView::create("cocosui/Hello.png");
        iv->setPosition(Vec2(240, 160));
        sc->addChild(iv);
        _uiLayer->addChild(sc);
        return true;
    }
    
    return false;
}

// UIScrollViewNestTest

UIScrollViewNestTest::UIScrollViewNestTest()
: _displayValueLabel(nullptr)
{
}

UIScrollViewNestTest::~UIScrollViewNestTest()
{
}

bool UIScrollViewNestTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = Text::create("Move by vertical direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("ScrollView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the scrollview by vertical
        ui::ScrollView* scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(280.0f, 150.0f));
        scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
		scrollView->setScrollBarPositionFromCorner(Vec2(4, 4));
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                     (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
                                     (widgetSize.height - backgroundSize.height) / 2.0f +
                                     (backgroundSize.height - scrollView->getContentSize().height) / 2.0f));
		scrollView->setScrollBarPositionFromCornerForVertical(Vec2(scrollView->getContentSize().width - 4, 4));
		scrollView->setScrollBarColor(Color3B::BLUE);
        _uiLayer->addChild(scrollView);
        
        ImageView* imageView = ImageView::create("cocosui/ccicon.png");
        
        float innerWidth = scrollView->getContentSize().width;
        float innerHeight = scrollView->getContentSize().height + imageView->getContentSize().height;
        
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(innerWidth / 2.0f, scrollView->getInnerContainerSize().height - button->getContentSize().height / 2.0f));
        scrollView->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(innerWidth / 2.0f, button->getBottomBoundary() - button->getContentSize().height));
        scrollView->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(innerWidth / 2.0f, titleButton->getBottomBoundary() - titleButton->getContentSize().height));
        scrollView->addChild(button_scale9);
        
        imageView->setPosition(Vec2(innerWidth / 2.0f, imageView->getContentSize().height / 2.0f));
        scrollView->addChild(imageView);
        
        
        
        // Create the scrollview by both
        ui::ScrollView* sc = ui::ScrollView::create();
        sc->setBackGroundColor(Color3B::GREEN);
        sc->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        sc->setBounceEnabled(true);
        sc->setDirection(ui::ScrollView::Direction::BOTH);
        sc->setInnerContainerSize(Size(480, 320));
        sc->setContentSize(Size(100,100));
        sc->setPropagateTouchEvents(false);
        sc->setPosition(Vec2(180,100));
        sc->scrollToPercentBothDirection(Vec2(50, 50), 1, true);
		sc->setScrollBarPositionFromCorner(Vec2(4, 4));
        ImageView* iv = ImageView::create("cocosui/Hello.png");
        iv->setPosition(Vec2(240, 160));
        sc->addChild(iv);

        
        scrollView->addChild(sc);
        
        return true;
    }
    
    return false;
}




// UIScrollViewRotated

UIScrollViewRotated::UIScrollViewRotated()
: _displayValueLabel(nullptr)
{
}

UIScrollViewRotated::~UIScrollViewRotated()
{
}

bool UIScrollViewRotated::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = Text::create("Move by vertical direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                             widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("ScrollView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the scrollview by vertical
        ui::ScrollView* scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(280.0f, 150.0f));
        scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                     (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
                                     (widgetSize.height - backgroundSize.height) / 2.0f +
                                     (backgroundSize.height - scrollView->getContentSize().height) / 2.0f + 100) );
        scrollView->setRotation(45);
		scrollView->setScrollBarPositionFromCorner(Vec2(4, 4));
		scrollView->setScrollBarColor(Color3B::WHITE);
        _uiLayer->addChild(scrollView);
        
        ImageView* imageView = ImageView::create("cocosui/ccicon.png");
        
        float innerWidth = scrollView->getContentSize().width;
        float innerHeight = scrollView->getContentSize().height + imageView->getContentSize().height;
        
        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(innerWidth / 2.0f, scrollView->getInnerContainerSize().height - button->getContentSize().height / 2.0f));
        scrollView->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(innerWidth / 2.0f, button->getBottomBoundary() - button->getContentSize().height));
        scrollView->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(innerWidth / 2.0f, titleButton->getBottomBoundary() - titleButton->getContentSize().height));
        scrollView->addChild(button_scale9);
        
        imageView->setPosition(Vec2(innerWidth / 2.0f, imageView->getContentSize().height / 2.0f));
        scrollView->addChild(imageView);
        
     
        
        return true;
    }
    
    return false;
}

// UIScrollViewDisableTest

UIScrollViewDisableTest::UIScrollViewDisableTest()
: _displayValueLabel(nullptr)
{
}

UIScrollViewDisableTest::~UIScrollViewDisableTest()
{
}

bool UIScrollViewDisableTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = Text::create("ScrollView Disable Test", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("ScrollView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));

        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));

        // Create the scrollview by vertical
        ui::ScrollView* scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(280.0f, 100.0f));
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                               (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
                               (widgetSize.height - backgroundSize.height) / 2.0f +
                               (backgroundSize.height - scrollView->getContentSize().height) / 2.0f));
        scrollView->setScrollBarWidth(4);
        scrollView->setTouchEnabled(false);
        scrollView->setScrollBarPositionFromCorner(Vec2(2, 2));
        scrollView->setScrollBarColor(Color3B::WHITE);
        _uiLayer->addChild(scrollView);

        ImageView* imageView = ImageView::create("cocosui/ccicon.png");

        float innerWidth = scrollView->getContentSize().width;
        float innerHeight = scrollView->getContentSize().height + imageView->getContentSize().height;

        scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));

        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(innerWidth / 2.0f, scrollView->getInnerContainerSize().height - button->getContentSize().height / 2.0f));
        scrollView->addChild(button);

        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(innerWidth / 2.0f, button->getBottomBoundary() - button->getContentSize().height));
        scrollView->addChild(titleButton);

        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(innerWidth / 2.0f, titleButton->getBottomBoundary() - titleButton->getContentSize().height));
        scrollView->addChild(button_scale9);

        imageView->setPosition(Vec2(innerWidth / 2.0f, imageView->getContentSize().height / 2.0f));
        scrollView->addChild(imageView);


        return true;
    }

    return false;
}

// UIScrollViewInnerSize

UIScrollViewInnerSize::UIScrollViewInnerSize()
    : _displayValueLabel(nullptr)
{
}

UIScrollViewInnerSize::~UIScrollViewInnerSize()
{
}

bool UIScrollViewInnerSize::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the scrollview alert will be displayed
        _displayValueLabel = Text::create("ScrollView InnerSize Test", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
            widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("ScrollView & InnerContainer should be align to the left and top point", "fonts/Marker Felt.ttf", 10);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);

        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));

        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));

        // Create the scrollview by vertical
        ui::ScrollView* scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(200.0f, 50.0f));
        Size backgroundSize = background->getContentSize();
        scrollView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
            (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
            (widgetSize.height - backgroundSize.height) / 2.0f +
            (backgroundSize.height - scrollView->getContentSize().height) / 2.0f));
        scrollView->setScrollBarWidth(4);
        scrollView->setTouchEnabled(false);
        scrollView->setScrollBarPositionFromCorner(Vec2(2, 2));
        scrollView->setScrollBarColor(Color3B::WHITE);
        scrollView->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        scrollView->setBackGroundColor(Color3B(150, 150, 100));
        scrollView->getInnerContainer()->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        scrollView->getInnerContainer()->setBackGroundColor(Color3B(50, 100, 50));
        scrollView->getInnerContainer()->setBackGroundColorOpacity(100);
        scrollView->setClippingEnabled(false);
        _uiLayer->addChild(scrollView);

        scrollView->setInnerContainerSize(Size(250.f, 100.f));

        return true;
    }

    return false;
}