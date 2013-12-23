

#include "UIDragPanelTest.h"

const char* font_UIDragPanelTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UIDragPanelTest
UIDragPanelTest::UIDragPanelTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UIDragPanelTest::~UIDragPanelTest()
{
}

bool UIDragPanelTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = cocos2d::gui::Label::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UIDragPanelTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addChild(m_pDisplayValueLabel);
        
        // Add the alert
        cocos2d::gui::Label *alert = cocos2d::gui::Label::create();
        alert->setText("DragPanel");
        alert->setFontName(font_UIDragPanelTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addChild(alert);
        
        cocos2d::gui::ScrollView* sc = cocos2d::gui::ScrollView::create();
        sc->setBackGroundColor(Color3B::GREEN);
        sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        sc->setDirection(SCROLLVIEW_DIR_BOTH);
        sc->setInnerContainerSize(Size(480, 320));
        sc->setSize(Size(100,100));
        sc->setPosition(Point(100,100));
        sc->scrollToPercentBothDirection(Point(50, 50), 1, true);
        cocos2d::gui::ImageView* iv = cocos2d::gui::ImageView::create();
        iv->loadTexture("cocosgui/Hello.png");
        iv->setPosition(Point(240, 160));
        sc->addChild(iv);
        m_pUiLayer->addChild(sc);
        
        return true;
    }
    return false;
}

// UIDragPanelTest_Bounce
UIDragPanelTest_Bounce::UIDragPanelTest_Bounce()
: m_pDisplayValueLabel(NULL)
{
    
}

UIDragPanelTest_Bounce::~UIDragPanelTest_Bounce()
{
}

bool UIDragPanelTest_Bounce::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = cocos2d::gui::Label::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UIDragPanelTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addChild(m_pDisplayValueLabel);        
        
        // Add the alert
        cocos2d::gui::Label *alert = cocos2d::gui::Label::create();
        alert->setText("DragPanel Bounce");
        alert->setFontName(font_UIDragPanelTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addChild(alert);
        
        cocos2d::gui::ScrollView* sc = cocos2d::gui::ScrollView::create();
        sc->setBackGroundColor(Color3B::GREEN);
        sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        sc->setBounceEnabled(true);
        sc->setDirection(SCROLLVIEW_DIR_BOTH);
        sc->setInnerContainerSize(Size(480, 320));
        sc->setSize(Size(100,100));
        sc->setPosition(Point(100,100));
        sc->scrollToPercentBothDirection(Point(50, 50), 1, true);
        cocos2d::gui::ImageView* iv = cocos2d::gui::ImageView::create();
        iv->loadTexture("cocosgui/Hello.png");
        iv->setPosition(Point(240, 160));
        sc->addChild(iv);
        m_pUiLayer->addChild(sc);
        return true;
    }
    
    return false;
}

