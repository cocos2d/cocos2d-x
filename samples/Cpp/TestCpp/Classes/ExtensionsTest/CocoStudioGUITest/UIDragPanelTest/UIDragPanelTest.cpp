

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
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UIDragPanelTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("DragPanel");
        alert->setFontName(font_UIDragPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the dragpanel
        UIDragPanel* dragPanel = UIDragPanel::create();
        dragPanel->setTouchEnable(true);
        dragPanel->setBackGroundImageScale9Enabled(true);
        dragPanel->setBackGroundImage("cocosgui/scrollviewbg.png");
        dragPanel->setSize(CCSizeMake(210, 122.5));        
        CCSize backgroundSize = background->getContentSize();
        dragPanel->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                   (backgroundSize.width - dragPanel->getRect().size.width) / 2,
                                   (widgetSize.height - backgroundSize.height) / 2 +
                                   (backgroundSize.height - dragPanel->getRect().size.height) / 2));
        
        UIImageView* imageView = UIImageView::create();
        imageView->setTouchEnable(true);
        imageView->setTexture("cocosgui/b11.png");
        dragPanel->addChild(imageView);
        
        dragPanel->setInnerContainerSize(imageView->getContentSize());
        CCSize innerSize = dragPanel->getInnerContainerSize();
        imageView->setPosition(ccp(innerSize.width / 2, innerSize.height / 2));                
        
        m_pUiLayer->addWidget(dragPanel);
        
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
        CCSize widgetSize = m_pWidget->getRect().size;;
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UIDragPanelTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("DragPanel Bounce");
        alert->setFontName(font_UIDragPanelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UILayout *background = dynamic_cast<UILayout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the dragpanel
        UIDragPanel* dragPanel = UIDragPanel::create();
        dragPanel->setTouchEnabled(true);
        dragPanel->setBounceEnabled(true);
        dragPanel->setBackGroundImageScale9Enabled(true);
        dragPanel->setBackGroundImage("cocosgui/green_edit.png");
        dragPanel->setSize(CCSizeMake(210, 122.5));
        CCSize backgroundSize = background->getContentSize();
        dragPanel->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                   (backgroundSize.width - dragPanel->getRect().size.width) / 2,
                                   (widgetSize.height - backgroundSize.height) / 2 +
                                   (backgroundSize.height - dragPanel->getRect().size.height) / 2));        
        UIImageView* imageView = UIImageView::create();
        imageView->setTouchEnable(true);
        imageView->setTexture("cocosgui/b11.png");
        dragPanel->addChild(imageView);
        
        dragPanel->setInnerContainerSize(imageView->getContentSize());
        CCSize innerSize = dragPanel->getInnerContainerSize();
        imageView->setPosition(ccp(innerSize.width / 2, innerSize.height / 2));
        
        m_pUiLayer->addWidget(dragPanel);
        
        return true;
    }
    
    return false;
}
