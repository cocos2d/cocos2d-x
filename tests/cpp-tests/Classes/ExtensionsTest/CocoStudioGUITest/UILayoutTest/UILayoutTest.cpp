

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
        Text* alert = Text::create("Layout", "fonts/Marker Felt.ttf", 30 );
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81)) ;
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vector2(button->getSize().width / 2.0f,
                                  layout->getSize().height - button->getSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vector2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vector2(layout->getSize().width - button_scale9->getSize().width / 2.0f,
                                         button_scale9->getSize().height / 2.0f));
        
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
        Text* alert = Text::create("Layout color render", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with color render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(Color3B(128, 128, 128));
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vector2(button->getSize().width / 2.0f,
                                  layout->getSize().height - button->getSize().height / 2.0f));
        
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vector2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vector2(layout->getSize().width - button_scale9->getSize().width / 2.0f,
                                         button_scale9->getSize().height / 2.0f));
        
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
        Text* alert = Text::create("Layout gradient render", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getSize().height * 3.075f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with gradient render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_GRADIENT);
        layout->setBackGroundColor(Color3B(64, 64, 64), Color3B(192, 192, 192));
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vector2(button->getSize().width / 2.0f,
                                  layout->getSize().height - button->getSize().height / 2.0f));
        
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vector2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vector2(layout->getSize().width - button_scale9->getSize().width / 2.0f,
                                         button_scale9->getSize().height / 2.0f));
        
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
        Text* alert = Text::create("Layout background image", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setClippingEnabled(true);
        layout->setBackGroundImage("cocosui/Hello.png");
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vector2(button->getSize().width / 2.0f,
                                  layout->getSize().height - button->getSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vector2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vector2(layout->getSize().width - button_scale9->getSize().width / 2.0f,
                                         button_scale9->getSize().height / 2.0f));
        
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
        Text* alert = Text::create("Layout background image scale9", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setBackGroundImageScale9Enabled(true);
        layout->setBackGroundImage("cocosui/green_edit.png");
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vector2(button->getSize().width / 2.0f,
                                  layout->getSize().height - button->getSize().height / 2.0f));
        
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vector2(layout->getSize().width / 2.0f, layout->getSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vector2(layout->getSize().width - button_scale9->getSize().width / 2.0f,
                                         button_scale9->getSize().height / 2.0f));
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
        Text* alert = Text::create("Layout Linear Vertical", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_LINEAR_VERTICAL);
        layout->setSize(Size(280, 150));        
        Size backgroundSize = background->getSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp1->setMargin(Margin(0.0f, 5.0f, 0.0f, 10.0f));
        
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp2->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp3->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
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
        Text* alert = Text::create("Layout Linear Horizontal", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_LINEAR_HORIZONTAL);
        layout->setClippingEnabled(true);
        layout->setSize(Size(280, 150));        
        Size backgroundSize = background->getSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp1->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp2->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp3->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
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
        Text* alert = Text::create("Layout Relative Align Parent", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
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
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                (backgroundSize.width - layout->getSize().width) / 2.0f,
                                (widgetSize.height - backgroundSize.height) / 2.0f +
                                (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        // top left
        Button* button_TopLeft = Button::create("cocosui/animationbuttonnormal.png",
                                                "cocosui/animationbuttonpressed.png");
        layout->addChild(button_TopLeft);
        
        RelativeLayoutParameter* rp_TopLeft = RelativeLayoutParameter::create();
        rp_TopLeft->setAlign(RELATIVE_ALIGN_PARENT_TOP_LEFT);
        button_TopLeft->setLayoutParameter(rp_TopLeft);
        
        
        // top center horizontal
        Button* button_TopCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                  "cocosui/animationbuttonpressed.png");
        layout->addChild(button_TopCenter);
        
        RelativeLayoutParameter* rp_TopCenter = RelativeLayoutParameter::create();
        rp_TopCenter->setAlign(RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL);
        button_TopCenter->setLayoutParameter(rp_TopCenter);
        
        
        // top right
        Button* button_TopRight = Button::create("cocosui/animationbuttonnormal.png",
                                                 "cocosui/animationbuttonpressed.png");
        layout->addChild(button_TopRight);
        
        RelativeLayoutParameter* rp_TopRight = RelativeLayoutParameter::create();
        rp_TopRight->setAlign(RELATIVE_ALIGN_PARENT_TOP_RIGHT);
        button_TopRight->setLayoutParameter(rp_TopRight);
        
        
        // left center
        Button* button_LeftCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                   "cocosui/animationbuttonpressed.png");
        layout->addChild(button_LeftCenter);
        
        RelativeLayoutParameter* rp_LeftCenter = RelativeLayoutParameter::create();
        rp_LeftCenter->setAlign(RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL);
        button_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        // center
        Button* buttonCenter = Button::create("cocosui/animationbuttonnormal.png",
                                              "cocosui/animationbuttonpressed.png");
        layout->addChild(buttonCenter);
        
        RelativeLayoutParameter* rpCenter = RelativeLayoutParameter::create();
        rpCenter->setAlign(RELATIVE_CENTER_IN_PARENT);
        buttonCenter->setLayoutParameter(rpCenter);
        
        
        // right center
        Button* button_RightCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                    "cocosui/animationbuttonpressed.png");
        layout->addChild(button_RightCenter);
        
        RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
        rp_RightCenter->setAlign(RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL);
        button_RightCenter->setLayoutParameter(rp_RightCenter);
        
        
        // left bottom
        Button* button_LeftBottom = Button::create("cocosui/animationbuttonnormal.png",
                                                   "cocosui/animationbuttonpressed.png");
        layout->addChild(button_LeftBottom);
        
        RelativeLayoutParameter* rp_LeftBottom = RelativeLayoutParameter::create();
        rp_LeftBottom->setAlign(RELATIVE_ALIGN_PARENT_LEFT_BOTTOM);
        button_LeftBottom->setLayoutParameter(rp_LeftBottom);
        
        
        // bottom center
        Button* button_BottomCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                     "cocosui/animationbuttonpressed.png");
        layout->addChild(button_BottomCenter);
        
        RelativeLayoutParameter* rp_BottomCenter = RelativeLayoutParameter::create();
        rp_BottomCenter->setAlign(RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL);
        button_BottomCenter->setLayoutParameter(rp_BottomCenter);
        
        
        // right bottom
        Button* button_RightBottom = Button::create("cocosui/animationbuttonnormal.png",
                                                    "cocosui/animationbuttonpressed.png");
        layout->addChild(button_RightBottom);
        
        RelativeLayoutParameter* rp_RightBottom = RelativeLayoutParameter::create();
        rp_RightBottom->setAlign(RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM);
        button_RightBottom->setLayoutParameter(rp_RightBottom);
        
        
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
        Text* alert = Text::create("Layout Relative Location", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_RELATIVE);
        layout->setSize(Size(280, 150));
        Size backgroundSize = background->getSize();
        layout->setPosition(Vector2((widgetSize.width - backgroundSize.width) / 2.0f +
                                (backgroundSize.width - layout->getSize().width) / 2.0f,
                                (widgetSize.height - backgroundSize.height) / 2.0f +
                                (backgroundSize.height - layout->getSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        // center
        ImageView* imageView_Center = ImageView::create("cocosui/scrollviewbg.png");
        layout->addChild(imageView_Center);
        
        RelativeLayoutParameter* rp_Center = RelativeLayoutParameter::create();
        rp_Center->setRelativeName("rp_Center");
        rp_Center->setAlign(RELATIVE_CENTER_IN_PARENT);
        imageView_Center->setLayoutParameter(rp_Center);
        
        
        // above center
        ImageView* imageView_AboveCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_AboveCenter);
        
        RelativeLayoutParameter* rp_AboveCenter = RelativeLayoutParameter::create();
        rp_AboveCenter->setRelativeToWidgetName("rp_Center");
        rp_AboveCenter->setAlign(RELATIVE_LOCATION_ABOVE_CENTER);
        imageView_AboveCenter->setLayoutParameter(rp_AboveCenter);
        
        
        // below center
        ImageView* imageView_BelowCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_BelowCenter);
        
        RelativeLayoutParameter* rp_BelowCenter = RelativeLayoutParameter::create();
        rp_BelowCenter->setRelativeToWidgetName("rp_Center");
        rp_BelowCenter->setAlign(RELATIVE_LOCATION_BELOW_CENTER);
        imageView_BelowCenter->setLayoutParameter(rp_BelowCenter);
        
        
        // left center
        ImageView* imageView_LeftCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_LeftCenter);
        
        RelativeLayoutParameter* rp_LeftCenter = RelativeLayoutParameter::create();
        rp_LeftCenter->setRelativeToWidgetName("rp_Center");
        rp_LeftCenter->setAlign(RELATIVE_LOCATION_LEFT_OF_CENTER);
        imageView_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        
        // right center
        ImageView* imageView_RightCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_RightCenter);
        
        RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
        rp_RightCenter->setRelativeToWidgetName("rp_Center");
        rp_RightCenter->setAlign(RELATIVE_LOCATION_RIGHT_OF_CENTER);
        imageView_RightCenter->setLayoutParameter(rp_RightCenter);
        
        
        return true;
    }
    
    return false;
}

