

#include "UIPanelTest.h"

const char* font_UIPanelTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UIPanelTest

UIPanelTest::UIPanelTest()
{
}

UIPanelTest::~UIPanelTest()
{
}

bool UIPanelTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getRect().size;
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, layout->getRect().size.height - button->getRect().size.height / 2));
        layout->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
        layout->addChild(textButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getRect().size.width - button_scale9->getRect().size.width / 2, button_scale9->getRect().size.height / 2));
        layout->addChild(button_scale9);        
        
        return true;
    }
    
    return false;
}

// UIPanelTest_Color

UIPanelTest_Color::UIPanelTest_Color()
{
}

UIPanelTest_Color::~UIPanelTest_Color()
{
}

bool UIPanelTest_Color::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel color render");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with color render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(ccc3(128, 128, 128));
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, layout->getRect().size.height - button->getRect().size.height / 2));
        layout->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
        layout->addChild(textButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getRect().size.width - button_scale9->getRect().size.width / 2, button_scale9->getRect().size.height / 2));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UIPanelTest_Gradient

UIPanelTest_Gradient::UIPanelTest_Gradient()
{    
}

UIPanelTest_Gradient::~UIPanelTest_Gradient()
{
}

bool UIPanelTest_Gradient::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel gradient render");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with gradient render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(LAYOUT_COLOR_GRADIENT);
        layout->setBackGroundColor(ccc3(64, 64, 64), ccc3(192, 192, 192));
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, layout->getRect().size.height - button->getRect().size.height / 2));
        layout->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
        layout->addChild(textButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getRect().size.width - button_scale9->getRect().size.width / 2, button_scale9->getRect().size.height / 2));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UIPanelTest_BackGroundImage

UIPanelTest_BackGroundImage::UIPanelTest_BackGroundImage()
{
}

UIPanelTest_BackGroundImage::~UIPanelTest_BackGroundImage()
{
}

bool UIPanelTest_BackGroundImage::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel background image");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setClippingEnabled(true);
        layout->setBackGroundImage("cocosgui/Hello.png");
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, layout->getRect().size.height - button->getRect().size.height / 2));
        layout->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
        layout->addChild(textButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getRect().size.width - button_scale9->getRect().size.width / 2, button_scale9->getRect().size.height / 2));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UIPanelTest_BackGroundImage_Scale9

UIPanelTest_BackGroundImage_Scale9::UIPanelTest_BackGroundImage_Scale9()
{
}

UIPanelTest_BackGroundImage_Scale9::~UIPanelTest_BackGroundImage_Scale9()
{
}

bool UIPanelTest_BackGroundImage_Scale9::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel background image scale9");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setBackGroundImageScale9Enabled(true);
        layout->setBackGroundImage("cocosgui/green_edit.png");
        layout->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, layout->getRect().size.height - button->getRect().size.height / 2));
        layout->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(layout->getRect().size.width / 2, layout->getRect().size.height / 2));
        layout->addChild(textButton);
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        button_scale9->setPosition(ccp(layout->getRect().size.width - button_scale9->getRect().size.width / 2, button_scale9->getRect().size.height / 2));
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UIPanelTest_Layout_Linear_Vertical

UIPanelTest_Layout_Linear_Vertical::UIPanelTest_Layout_Linear_Vertical()
{
}

UIPanelTest_Layout_Linear_Vertical::~UIPanelTest_Layout_Linear_Vertical()
{
}

bool UIPanelTest_Layout_Linear_Vertical::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel Layout Linear Vertical");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setSize(CCSizeMake(280, 150));        
        CCSize backgroundSize = background->getRect().size;
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp1->setMargin(UIMargin(0, 5, 0, 10));
        
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        layout->addChild(textButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        textButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp2->setMargin(UIMargin(0, 10, 0, 10));
        
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
        lp3->setMargin(UIMargin(0, 10, 0, 10));
        
        
        LinearVerticalLayoutExecutant* exe = LinearVerticalLayoutExecutant::create();
        layout->setLayoutExecutant(exe);
        exe->doLayout();
        
        return true;
    }
    
    return false;
}

// UIPanelTest_Layout_Linear_Horizontal

UIPanelTest_Layout_Linear_Horizontal::UIPanelTest_Layout_Linear_Horizontal()
{
}

UIPanelTest_Layout_Linear_Horizontal::~UIPanelTest_Layout_Linear_Horizontal()
{
}

bool UIPanelTest_Layout_Linear_Horizontal::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel Layout Linear Horizontal");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setClippingEnabled(true);
        layout->setSize(CCSizeMake(280, 150));        
        CCSize backgroundSize = background->getRect().size;
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp1->setMargin(UIMargin(0, 10, 0, 10));
        
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        layout->addChild(textButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        textButton->setLayoutParameter(lp2);
        lp2->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp2->setMargin(UIMargin(0, 10, 0, 10));
        
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
        lp3->setMargin(UIMargin(0, 10, 0, 10));
        
        
        LinearHorizontalLayoutExecutant* exe = LinearHorizontalLayoutExecutant::create();
        layout->setLayoutExecutant(exe);
        exe->doLayout();
        
        return true;
    }
    
    return false;
}

// UIPanelTest_Layout_Relative

UIPanelTest_Layout_Relative::UIPanelTest_Layout_Relative()
{
}

UIPanelTest_Layout_Relative::~UIPanelTest_Layout_Relative()
{
}

bool UIPanelTest_Layout_Relative::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel Layout Relative");
        alert->setFontName(font_UIPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setSize(CCSizeMake(280, 150));
        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        layout->setBackGroundColor(ccGREEN);
        CCSize backgroundSize = background->getRect().size;
        layout->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout->getRect().size.width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout->getRect().size.height) / 2));
        m_pUiLayer->addWidget(layout);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        layout->addChild(button);
        
        RelativeLayoutParameter* rp1 = RelativeLayoutParameter::create();
        button->setLayoutParameter(rp1);
        rp1->setAlign(RELATIVE_ALIGN_PARENT_BOTTOM);
//        rp1->setMargin(UIMargin(0, 10, 0, 10));
        
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        layout->addChild(textButton);
        
        RelativeLayoutParameter* rp2 = RelativeLayoutParameter::create();
        textButton->setLayoutParameter(rp2);
        rp2->setAlign(RELATIVE_ALIGN_PARENT_LEFT);
        
        
        UIButton* button_scale9 = UIButton::create();
        button_scale9->setTouchEnable(true);
        button_scale9->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button_scale9->setScale9Enabled(true);
        button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        layout->addChild(button_scale9);
        
        RelativeLayoutParameter* rp3 = RelativeLayoutParameter::create();
        textButton->setLayoutParameter(rp3);
        rp3->setAlign(RELATIVE_ALIGN_PARENT_RIGHT);
        
        
        RelativeLayoutExecutant* exe = RelativeLayoutExecutant::create();
        layout->setLayoutExecutant(exe);        
        exe->doLayout();
        
        return true;
    }
    
    return false;
}