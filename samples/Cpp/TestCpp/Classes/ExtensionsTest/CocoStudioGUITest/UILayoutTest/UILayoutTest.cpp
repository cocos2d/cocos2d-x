

#include "UILayoutTest.h"


// UILayoutTest

UILayoutTest::UILayoutTest()
{
}

UILayoutTest::~UILayoutTest()
{
}

bool UILayoutTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81)) ;
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(button->getSize().width / 2.0f, layout->getSize().height - button->getSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Point(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        button_scale9->setPosition(Point(layout->getSize().width - button_scale9->getSize().width / 2.0f, button_scale9->getSize().height / 2.0f));
        layout->addChild(button_scale9);
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Color

UILayoutTest_Color::UILayoutTest_Color()
{
}

UILayoutTest_Color::~UILayoutTest_Color()
{
}

bool UILayoutTest_Color::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout color render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with color render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(Color3B(128, 128, 128));
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(button->getSize().width / 2.0f, layout->getSize().height - button->getSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Point(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        button_scale9->setPosition(Point(layout->getSize().width - button_scale9->getSize().width / 2.0f, button_scale9->getSize().height / 2.0f));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UILayoutTest_Gradient

UILayoutTest_Gradient::UILayoutTest_Gradient()
{    
}

UILayoutTest_Gradient::~UILayoutTest_Gradient()
{
}

bool UILayoutTest_Gradient::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout gradient render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with gradient render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_GRADIENT);
        layout->setBackGroundColor(Color3B(64, 64, 64), Color3B(192, 192, 192));
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(button->getSize().width / 2.0f, layout->getSize().height - button->getSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Point(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        button_scale9->setPosition(Point(layout->getSize().width - button_scale9->getSize().width / 2.0f, button_scale9->getSize().height / 2.0f));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UILayoutTest_BackGroundImage

UILayoutTest_BackGroundImage::UILayoutTest_BackGroundImage()
{
}

UILayoutTest_BackGroundImage::~UILayoutTest_BackGroundImage()
{
}

bool UILayoutTest_BackGroundImage::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout background image");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setClippingEnabled(true);
        layout->setBackGroundImage("cocosgui/Hello.png");
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(button->getSize().width / 2.0f, layout->getSize().height - button->getSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Point(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        button_scale9->setPosition(Point(layout->getSize().width - button_scale9->getSize().width / 2.0f, button_scale9->getSize().height / 2.0f));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UILayoutTest_BackGroundImage_Scale9

UILayoutTest_BackGroundImage_Scale9::UILayoutTest_BackGroundImage_Scale9()
{
}

UILayoutTest_BackGroundImage_Scale9::~UILayoutTest_BackGroundImage_Scale9()
{
}

bool UILayoutTest_BackGroundImage_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout background image scale9");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setBackGroundImageScale9Enabled(true);
        layout->setBackGroundImage("cocosgui/green_edit.png");
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(button->getSize().width / 2.0f, layout->getSize().height - button->getSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Point(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        button_scale9->setPosition(Point(layout->getSize().width - button_scale9->getSize().width / 2.0f, button_scale9->getSize().height / 2.0f));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UILayoutTest_Layout_Linear_Vertical

UILayoutTest_Layout_Linear_Vertical::UILayoutTest_Layout_Linear_Vertical()
{
}

UILayoutTest_Layout_Linear_Vertical::~UILayoutTest_Layout_Linear_Vertical()
{
}

bool UILayoutTest_Layout_Linear_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout Linear Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_LINEAR_VERTICAL);
        layout->setSize(Size(280, 150));        
        Size backgroundSize = background->getSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp1->setMargin(Margin(0.0f, 5.0f, 0.0f, 10.0f));
        
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp2->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp3->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
//        layout->doLayout();
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Layout_Linear_Horizontal

UILayoutTest_Layout_Linear_Horizontal::UILayoutTest_Layout_Linear_Horizontal()
{
}

UILayoutTest_Layout_Linear_Horizontal::~UILayoutTest_Layout_Linear_Horizontal()
{
}

bool UILayoutTest_Layout_Linear_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout Linear Horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_LINEAR_HORIZONTAL);
        layout->setClippingEnabled(true);
        layout->setSize(Size(280, 150));        
        Size backgroundSize = background->getSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp1->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* titleButton = Button::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp2->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* button_scale9 = Button::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getContentSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp3->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
//        layout->doLayout();
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Layout_Relative_Align_Parent

UILayoutTest_Layout_Relative_Align_Parent::UILayoutTest_Layout_Relative_Align_Parent()
{
}

UILayoutTest_Layout_Relative_Align_Parent::~UILayoutTest_Layout_Relative_Align_Parent()
{
}

bool UILayoutTest_Layout_Relative_Align_Parent::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout Relative Align Parent");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_RELATIVE);
        layout->setSize(Size(280, 150));
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(Color3B::GREEN);
        Size backgroundSize = background->getSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                (backgroundSize.width - layout->getSize().width) / 2.0f,
                                (widgetSize.height - backgroundSize.height) / 2.0f +
                                (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        // top left
        Button* button_TopLeft = Button::create();
        button_TopLeft->setTouchEnabled(true);
        button_TopLeft->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_TopLeft);
        
        RelativeLayoutParameter* rp_TopLeft = RelativeLayoutParameter::create();
        rp_TopLeft->setAlign(RELATIVE_ALIGN_PARENT_TOP_LEFT);
        button_TopLeft->setLayoutParameter(rp_TopLeft);
        
        
        // top center horizontal
        Button* button_TopCenter = Button::create();
        button_TopCenter->setTouchEnabled(true);
        button_TopCenter->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_TopCenter);
        
        RelativeLayoutParameter* rp_TopCenter = RelativeLayoutParameter::create();
        rp_TopCenter->setAlign(RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL);
        button_TopCenter->setLayoutParameter(rp_TopCenter);
        
        
        // top right
        Button* button_TopRight = Button::create();
        button_TopRight->setTouchEnabled(true);
        button_TopRight->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_TopRight);
        
        RelativeLayoutParameter* rp_TopRight = RelativeLayoutParameter::create();
        rp_TopRight->setAlign(RELATIVE_ALIGN_PARENT_TOP_RIGHT);
        button_TopRight->setLayoutParameter(rp_TopRight);
        
        
        // left center
        Button* button_LeftCenter = Button::create();
        button_LeftCenter->setTouchEnabled(true);
        button_LeftCenter->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_LeftCenter);
        
        RelativeLayoutParameter* rp_LeftCenter = RelativeLayoutParameter::create();
        rp_LeftCenter->setAlign(RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL);
        button_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        // center
        Button* buttonCenter = Button::create();
        buttonCenter->setTouchEnabled(true);
        buttonCenter->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(buttonCenter);
        
        RelativeLayoutParameter* rpCenter = RelativeLayoutParameter::create();
        rpCenter->setAlign(RELATIVE_CENTER_IN_PARENT);
        buttonCenter->setLayoutParameter(rpCenter);
        
        
        // right center
        Button* button_RightCenter = Button::create();
        button_RightCenter->setTouchEnabled(true);
        button_RightCenter->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_RightCenter);
        
        RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
        rp_RightCenter->setAlign(RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL);
        button_RightCenter->setLayoutParameter(rp_RightCenter);
        
        
        // left bottom
        Button* button_LeftBottom = Button::create();
        button_LeftBottom->setTouchEnabled(true);
        button_LeftBottom->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_LeftBottom);
        
        RelativeLayoutParameter* rp_LeftBottom = RelativeLayoutParameter::create();
        rp_LeftBottom->setAlign(RELATIVE_ALIGN_PARENT_LEFT_BOTTOM);
        button_LeftBottom->setLayoutParameter(rp_LeftBottom);
        
        
        // bottom center
        Button* button_BottomCenter = Button::create();
        button_BottomCenter->setTouchEnabled(true);
        button_BottomCenter->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_BottomCenter);
        
        RelativeLayoutParameter* rp_BottomCenter = RelativeLayoutParameter::create();
        rp_BottomCenter->setAlign(RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL);
        button_BottomCenter->setLayoutParameter(rp_BottomCenter);
        
        
        // right bottom
        Button* button_RightBottom = Button::create();
        button_RightBottom->setTouchEnabled(true);
        button_RightBottom->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button_RightBottom);
        
        RelativeLayoutParameter* rp_RightBottom = RelativeLayoutParameter::create();
        rp_RightBottom->setAlign(RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM);
        button_RightBottom->setLayoutParameter(rp_RightBottom);
        
        
//        layout->doLayout();
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Layout_Relative_Location

UILayoutTest_Layout_Relative_Location::UILayoutTest_Layout_Relative_Location()
{
}

UILayoutTest_Layout_Relative_Location::~UILayoutTest_Layout_Relative_Location()
{
}

bool UILayoutTest_Layout_Relative_Location::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Layout Relative Location");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_RELATIVE);
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                (backgroundSize.width - layout->getSize().width) / 2.0f,
                                (widgetSize.height - backgroundSize.height) / 2.0f +
                                (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        // center
        ImageView* imageView_Center = ImageView::create();
        imageView_Center->loadTexture("cocosgui/scrollviewbg.png");
        layout->addChild(imageView_Center);
        
        RelativeLayoutParameter* rp_Center = RelativeLayoutParameter::create();
        rp_Center->setRelativeName("rp_Center");
        rp_Center->setAlign(RELATIVE_CENTER_IN_PARENT);
        imageView_Center->setLayoutParameter(rp_Center);
        
        
        // above center
        ImageView* imageView_AboveCenter = ImageView::create();
        imageView_AboveCenter->loadTexture("cocosgui/switch-mask.png");
        layout->addChild(imageView_AboveCenter);
        
        RelativeLayoutParameter* rp_AboveCenter = RelativeLayoutParameter::create();
        rp_AboveCenter->setRelativeToWidgetName("rp_Center");
        rp_AboveCenter->setAlign(RELATIVE_LOCATION_ABOVE_CENTER);
        imageView_AboveCenter->setLayoutParameter(rp_AboveCenter);
        
        
        // below center
        ImageView* imageView_BelowCenter = ImageView::create();
        imageView_BelowCenter->loadTexture("cocosgui/switch-mask.png");
        layout->addChild(imageView_BelowCenter);
        
        RelativeLayoutParameter* rp_BelowCenter = RelativeLayoutParameter::create();
        rp_BelowCenter->setRelativeToWidgetName("rp_Center");
        rp_BelowCenter->setAlign(RELATIVE_LOCATION_BELOW_CENTER);
        imageView_BelowCenter->setLayoutParameter(rp_BelowCenter);
        
        
        // left center
        ImageView* imageView_LeftCenter = ImageView::create();
        imageView_LeftCenter->loadTexture("cocosgui/switch-mask.png");
        layout->addChild(imageView_LeftCenter);
        
        RelativeLayoutParameter* rp_LeftCenter = RelativeLayoutParameter::create();
        rp_LeftCenter->setRelativeToWidgetName("rp_Center");
        rp_LeftCenter->setAlign(RELATIVE_LOCATION_LEFT_OF_CENTER);
        imageView_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        
        // right center
        ImageView* imageView_RightCenter = ImageView::create();
        imageView_RightCenter->loadTexture("cocosgui/switch-mask.png");
        layout->addChild(imageView_RightCenter);
        
        RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
        rp_RightCenter->setRelativeToWidgetName("rp_Center");
        rp_RightCenter->setAlign(RELATIVE_LOCATION_RIGHT_OF_CENTER);
        imageView_RightCenter->setLayoutParameter(rp_RightCenter);
        
        
//        layout->doLayout();
        
        return true;
    }
    
    return false;
}

/*
// UILayoutTest_Layout_Grid

UILayoutTest_Layout_Grid::UILayoutTest_Layout_Grid()
{
}

UILayoutTest_Layout_Grid::~UILayoutTest_Layout_Grid()
{
}

bool UILayoutTest_Layout_Grid::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Layout Grid");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_GRID_MODE_COLUMN);
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getSize();
        layout->setPosition(Point((widgetSize.width - backgroundSize.width) / 2.0f +
                                (backgroundSize.width - layout->getSize().width) / 2.0f,
                                (widgetSize.height - backgroundSize.height) / 2.0f +
                                (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        
        // create items
        for (int i = 0; i < 14; ++i)
        {
            Button* button = Button::create();
            button->setName("TextButton");
            button->setTouchEnabled(true);
            button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
            button->setScale9Enabled(true);
            AffineTransform transform = AffineTransformMakeIdentity();
            transform = AffineTransformScale(transform, 3.0f, 1.3f);
            button->setSize(SizeApplyAffineTransform(button->getContentSize(), transform));
            button->setTitleText(CCString::createWithFormat("grid_%d", i)->getCString());
            
            Layout* item = Layout::create();
            item->setTouchEnabled(true);
            item->setSize(button->getSize());
            button->setPosition(Point(item->getSize().width / 2.0f, item->getSize().height / 2.0f));
            item->addChild(button);
            
            GridLayoutParameter* gp = GridLayoutParameter::create();
            item->setLayoutParameter(gp);
            gp->setMargin(Margin(0.0f, 0.0f, 0.0f, 0.0f));
            
            layout->addChild(item);
        }
        
        // set grid view row and column
        Widget* item = static_cast<Widget*>(layout->getChildren().at(0));
        int rowCount = layout->getSize().height / item->getSize().height;
        int columnCount = layout->getSize().width / item->getSize().width;
        layout->setGridLayoutRowAndColumnCount(rowCount, columnCount);                
        
//        layout->doLayout();
        
        return true;
    }
    
    return false;
}
 */

