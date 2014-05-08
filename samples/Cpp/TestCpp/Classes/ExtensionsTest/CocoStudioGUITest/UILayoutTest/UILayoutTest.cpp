

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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        UILayout* background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        UILayout* layout = UILayout::create();
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getSize().width / 2, layout->getSize().height - button->getSize().height / 2));
        layout->addChild(button);
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(ccp(layout->getSize().width / 2, layout->getSize().height / 2));
        layout->addChild(titleButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getSize().width - button_scale9->getSize().width / 2, button_scale9->getSize().height / 2));
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout color render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with color render
        UILayout* layout = UILayout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(ccc3(128, 128, 128));
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getSize().width / 2, layout->getSize().height - button->getSize().height / 2));
        layout->addChild(button);
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(ccp(layout->getSize().width / 2, layout->getSize().height / 2));
        layout->addChild(titleButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getSize().width - button_scale9->getSize().width / 2, button_scale9->getSize().height / 2));
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout gradient render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.075));
        m_pUiLayer->addWidget(alert);
        
        UILayout* background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with gradient render
        UILayout* layout = UILayout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_GRADIENT);
        layout->setBackGroundColor(ccc3(64, 64, 64), ccc3(192, 192, 192));
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getSize().width / 2, layout->getSize().height - button->getSize().height / 2));
        layout->addChild(button);
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(ccp(layout->getSize().width / 2, layout->getSize().height / 2));
        layout->addChild(titleButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getSize().width - button_scale9->getSize().width / 2, button_scale9->getSize().height / 2));
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout background image");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5f));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with background image
        UILayout* layout = UILayout::create();
        layout->setClippingEnabled(true);
        layout->setBackGroundImage("cocosui/Hello.png");
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getSize().width / 2, layout->getSize().height - button->getSize().height / 2));
        layout->addChild(button);
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(ccp(layout->getSize().width / 2, layout->getSize().height / 2));
        layout->addChild(titleButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getSize().width - button_scale9->getSize().width / 2, button_scale9->getSize().height / 2));
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout background image scale9");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        UILayout* background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with background image
        UILayout* layout = UILayout::create();
        layout->setBackGroundImageScale9Enabled(true);
        layout->setBackGroundImage("cocosui/green_edit.png");
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getSize().width / 2, layout->getSize().height - button->getSize().height / 2));
        layout->addChild(button);
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(ccp(layout->getSize().width / 2, layout->getSize().height / 2));
        layout->addChild(titleButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getSize().width - button_scale9->getSize().width / 2, button_scale9->getSize().height / 2));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

/*===*/
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout Layout Linear Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_LINEAR_VERTICAL);
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button);
        
        UILinearLayoutParameter* lp1 = UILinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp1->setMargin(UIMargin(0, 5, 0, 10));
        
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        UILinearLayoutParameter* lp2 = UILinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp2->setMargin(UIMargin(0, 10, 0, 10));
        
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        layout->addChild(button_scale9);
        
        UILinearLayoutParameter* lp3 = UILinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp3->setMargin(UIMargin(0, 10, 0, 10));
        
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout Layout Linear Horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_LINEAR_HORIZONTAL);
        layout->setClippingEnabled(true);
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button);
        
        UILinearLayoutParameter* lp1 = UILinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp1->setMargin(UIMargin(0, 10, 0, 10));
        
        
        UIButton* titleButton = UIButton::create();
        titleButton->setTouchEnabled(true);
        titleButton->loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        UILinearLayoutParameter* lp2 = UILinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp2->setMargin(UIMargin(0, 10, 0, 10));
        
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnabled(true);
        button_scale9->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        layout->addChild(button_scale9);
        
        UILinearLayoutParameter* lp3 = UILinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp3->setMargin(UIMargin(0, 10, 0, 10));
        
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout Relative Align Parent");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_RELATIVE);
        layout->setSize(CCSizeMake(280, 150));
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(ccGREEN);
        CCSize backgroundSize = background->getSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        // top left
        UIButton* button_TopLeft = UIButton::create();
        button_TopLeft->setTouchEnabled(true);
        button_TopLeft->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_TopLeft);
        
        UIRelativeLayoutParameter* rp_TopLeft = UIRelativeLayoutParameter::create();
        rp_TopLeft->setAlign(RELATIVE_ALIGN_PARENT_TOP_LEFT);
        button_TopLeft->setLayoutParameter(rp_TopLeft);
        
        
        // top center horizontal
        UIButton* button_TopCenter = UIButton::create();
        button_TopCenter->setTouchEnabled(true);
        button_TopCenter->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_TopCenter);
        
        UIRelativeLayoutParameter* rp_TopCenter = UIRelativeLayoutParameter::create();
        rp_TopCenter->setAlign(RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL);
        button_TopCenter->setLayoutParameter(rp_TopCenter);
        
        
        // top right
        UIButton* button_TopRight = UIButton::create();
        button_TopRight->setTouchEnabled(true);
        button_TopRight->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_TopRight);
        
        UIRelativeLayoutParameter* rp_TopRight = UIRelativeLayoutParameter::create();
        rp_TopRight->setAlign(RELATIVE_ALIGN_PARENT_TOP_RIGHT);
        button_TopRight->setLayoutParameter(rp_TopRight);
        
        
        // left center
        UIButton* button_LeftCenter = UIButton::create();
        button_LeftCenter->setTouchEnabled(true);
        button_LeftCenter->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_LeftCenter);
        
        UIRelativeLayoutParameter* rp_LeftCenter = UIRelativeLayoutParameter::create();
        rp_LeftCenter->setAlign(RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL);
        button_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        // center
        UIButton* buttonCenter = UIButton::create();
        buttonCenter->setTouchEnabled(true);
        buttonCenter->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(buttonCenter);
        
        UIRelativeLayoutParameter* rpCenter = UIRelativeLayoutParameter::create();
        rpCenter->setAlign(RELATIVE_CENTER_IN_PARENT);
        buttonCenter->setLayoutParameter(rpCenter);
        
        
        // right center
        UIButton* button_RightCenter = UIButton::create();
        button_RightCenter->setTouchEnabled(true);
        button_RightCenter->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_RightCenter);
        
        UIRelativeLayoutParameter* rp_RightCenter = UIRelativeLayoutParameter::create();
        rp_RightCenter->setAlign(RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL);
        button_RightCenter->setLayoutParameter(rp_RightCenter);
        
        
        // left bottom
        UIButton* button_LeftBottom = UIButton::create();
        button_LeftBottom->setTouchEnabled(true);
        button_LeftBottom->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_LeftBottom);
        
        UIRelativeLayoutParameter* rp_LeftBottom = UIRelativeLayoutParameter::create();
        rp_LeftBottom->setAlign(RELATIVE_ALIGN_PARENT_LEFT_BOTTOM);
        button_LeftBottom->setLayoutParameter(rp_LeftBottom);
        
        
        // bottom center
        UIButton* button_BottomCenter = UIButton::create();
        button_BottomCenter->setTouchEnabled(true);
        button_BottomCenter->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_BottomCenter);
        
        UIRelativeLayoutParameter* rp_BottomCenter = UIRelativeLayoutParameter::create();
        rp_BottomCenter->setAlign(RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL);
        button_BottomCenter->setLayoutParameter(rp_BottomCenter);
        
        
        // right bottom
        UIButton* button_RightBottom = UIButton::create();
        button_RightBottom->setTouchEnabled(true);
        button_RightBottom->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        layout->addChild(button_RightBottom);
        
        UIRelativeLayoutParameter* rp_RightBottom = UIRelativeLayoutParameter::create();
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout Relative Location");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_RELATIVE);
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        // center
        UIImageView* imageView_Center = UIImageView::create();
        imageView_Center->loadTexture("cocosui/scrollviewbg.png");
        layout->addChild(imageView_Center);
        
        UIRelativeLayoutParameter* rp_Center = UIRelativeLayoutParameter::create();
        rp_Center->setRelativeName("rp_Center");
        rp_Center->setAlign(RELATIVE_CENTER_IN_PARENT);
        imageView_Center->setLayoutParameter(rp_Center);
        
        
        // above center
        UIImageView* imageView_AboveCenter = UIImageView::create();
        imageView_AboveCenter->loadTexture("cocosui/switch-mask.png");
        layout->addChild(imageView_AboveCenter);
        
        UIRelativeLayoutParameter* rp_AboveCenter = UIRelativeLayoutParameter::create();
        rp_AboveCenter->setRelativeToWidgetName("rp_Center");
        rp_AboveCenter->setAlign(RELATIVE_LOCATION_ABOVE_CENTER);
        imageView_AboveCenter->setLayoutParameter(rp_AboveCenter);
        
        
        // below center
        UIImageView* imageView_BelowCenter = UIImageView::create();
        imageView_BelowCenter->loadTexture("cocosui/switch-mask.png");
        layout->addChild(imageView_BelowCenter);
        
        UIRelativeLayoutParameter* rp_BelowCenter = UIRelativeLayoutParameter::create();
        rp_BelowCenter->setRelativeToWidgetName("rp_Center");
        rp_BelowCenter->setAlign(RELATIVE_LOCATION_BELOW_CENTER);
        imageView_BelowCenter->setLayoutParameter(rp_BelowCenter);
        
        
        // left center
        UIImageView* imageView_LeftCenter = UIImageView::create();
        imageView_LeftCenter->loadTexture("cocosui/switch-mask.png");
        layout->addChild(imageView_LeftCenter);
        
        UIRelativeLayoutParameter* rp_LeftCenter = UIRelativeLayoutParameter::create();
        rp_LeftCenter->setRelativeToWidgetName("rp_Center");
        rp_LeftCenter->setAlign(RELATIVE_LOCATION_LEFT_OF_CENTER);
        imageView_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        
        // right center
        UIImageView* imageView_RightCenter = UIImageView::create();
        imageView_RightCenter->loadTexture("cocosui/switch-mask.png");
        layout->addChild(imageView_RightCenter);
        
        UIRelativeLayoutParameter* rp_RightCenter = UIRelativeLayoutParameter::create();
        rp_RightCenter->setRelativeToWidgetName("rp_Center");
        rp_RightCenter->setAlign(RELATIVE_LOCATION_RIGHT_OF_CENTER);
        imageView_RightCenter->setLayoutParameter(rp_RightCenter);
        
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("Layout Grid");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 4.5));
        m_pUiLayer->addWidget(alert);
        
        Layout* background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(LAYOUT_GRID_MODE_COLUMN);
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getSize().height) / 2));
        m_pUiLayer->addWidget(layout);
        
        
        // create items
        for (int i = 0; i < 14; ++i)
        {
            UIButton* button = UIButton::create();
            button->setName("TextButton");
            button->setTouchEnabled(true);
            button->loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "");
            button->setScale9Enabled(true);
            CCAffineTransform transform = CCAffineTransformMakeIdentity();
            transform = CCAffineTransformScale(transform, 3.0f, 1.3f);
            button->setSize(CCSizeApplyAffineTransform(button->getContentSize(), transform));
            button->setTitleText(CCString::createWithFormat("grid_%d", i)->getCString());
            
            Layout* item = Layout::create();
            item->setTouchEnabled(true);
            item->setSize(button->getSize());
            button->setPosition(ccp(item->getSize().width / 2, item->getSize().height / 2));
            item->addChild(button);
            
            UIGridLayoutParameter* gp = UIGridLayoutParameter::create();
            item->setLayoutParameter(gp);
            gp->setMargin(UIMargin(0, 0, 0, 0));
            
            layout->addChild(item);
        }
        
        // set grid view row and column
        UIWidget* item = static_cast<UIWidget*>(layout->getChildren()->objectAtIndex(0));
        int rowCount = layout->getSize().height / item->getSize().height;
        int columnCount = layout->getSize().width / item->getSize().width;
        layout->setGridLayoutRowAndColumnCount(rowCount, columnCount);                
        
        layout->doLayout();
        
        return true;
    }
    
    return false;
}
 */
/*=*/
