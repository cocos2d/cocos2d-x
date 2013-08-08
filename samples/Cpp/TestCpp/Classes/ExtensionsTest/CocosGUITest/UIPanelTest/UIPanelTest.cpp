

#include "UIPanelTest.h"

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
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the panel
        UIPanel* panel = UIPanel::create();
        panel->setClippingEnable(true);
        panel->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getRect().size;
        panel->setPosition(ccp((screenSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - panel->getRect().size.width) / 2,
                               (screenSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - panel->getRect().size.height) / 2));
        m_pUiLayer->addWidget(panel);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, panel->getRect().size.height - button->getRect().size.height / 2));
        panel->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
        panel->addChild(textButton);
        
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
        zoomButton->setPosition(ccp(panel->getRect().size.width - zoomButton->getRect().size.width / 2,
                                    zoomButton->getRect().size.height / 2));
        panel->addChild(zoomButton);
        
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
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel color render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the panel with color render
        UIPanel* panel = UIPanel::create();
        panel->setBackGroundColorType(PANEL_COLOR_SOLID);
        panel->setBackGroundColor(ccc3(128, 128, 128));
        panel->setClippingEnable(true);
        panel->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        panel->setPosition(ccp((screenSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - panel->getRect().size.width) / 2,
                               (screenSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - panel->getRect().size.height) / 2));
        m_pUiLayer->addWidget(panel);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, panel->getRect().size.height - button->getRect().size.height / 2));
        panel->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
        panel->addChild(textButton);
        
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
        zoomButton->setPosition(ccp(panel->getRect().size.width - zoomButton->getRect().size.width / 2,
                                       zoomButton->getRect().size.height / 2));
        panel->addChild(zoomButton);
        
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
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel gradient render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the panel with gradient render
        UIPanel* panel = UIPanel::create();
        panel->setBackGroundColorType(PANEL_COLOR_GRADIENT);
        panel->setBackGroundColor(ccc3(64, 64, 64), ccc3(192, 192, 192));
        panel->setClippingEnable(true);
        panel->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        panel->setPosition(ccp((screenSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - panel->getRect().size.width) / 2,
                               (screenSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - panel->getRect().size.height) / 2));
        m_pUiLayer->addWidget(panel);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, panel->getRect().size.height - button->getRect().size.height / 2));
        panel->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
        panel->addChild(textButton);
        
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
        zoomButton->setPosition(ccp(panel->getRect().size.width - zoomButton->getRect().size.width / 2,
                                       zoomButton->getRect().size.height / 2));
        panel->addChild(zoomButton);
        
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
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();                
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel background image");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the panel with background image
        UIPanel* panel = UIPanel::create();
        panel->setBackGroundImage("cocosgui/Hello.png");
        panel->setClippingEnable(true);
        panel->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        panel->setPosition(ccp((screenSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - panel->getRect().size.width) / 2,
                               (screenSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - panel->getRect().size.height) / 2));
        m_pUiLayer->addWidget(panel);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, panel->getRect().size.height - button->getRect().size.height / 2));
        panel->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
        panel->addChild(textButton);
        
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
        zoomButton->setPosition(ccp(panel->getRect().size.width - zoomButton->getRect().size.width / 2,
                                       zoomButton->getRect().size.height / 2));
        panel->addChild(zoomButton);
        
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
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Panel background image scale9");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the panel with background image
        UIPanel* panel = UIPanel::create();
        panel->setBackGroundImageScale9Enable(true);
        panel->setBackGroundImage("cocosgui/green_edit.png");
        panel->setClippingEnable(true);
        panel->setSize(CCSizeMake(280, 150));
        CCSize backgroundSize = background->getContentSize();
        panel->setPosition(ccp((screenSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - panel->getRect().size.width) / 2,
                               (screenSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - panel->getRect().size.height) / 2));
        m_pUiLayer->addWidget(panel);
        
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(button->getRect().size.width / 2, panel->getRect().size.height - button->getRect().size.height / 2));
        panel->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(panel->getRect().size.width / 2, panel->getRect().size.height / 2));
        panel->addChild(textButton);
        
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
        zoomButton->setPosition(ccp(panel->getRect().size.width - zoomButton->getRect().size.width / 2,
                                    zoomButton->getRect().size.height / 2));
        panel->addChild(zoomButton);
        
        return true;
    }
    return false;
}