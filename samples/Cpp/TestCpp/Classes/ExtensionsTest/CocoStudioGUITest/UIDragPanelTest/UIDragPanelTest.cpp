

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
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UIDragPanelTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("DragPanel");
        alert->setFontName(font_UIDragPanelTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the dragpanel
        UIDragPanel* dragPanel = UIDragPanel::create();
        dragPanel->setTouchEnabled(true);
        dragPanel->setBackGroundImageScale9Enabled(true);
        dragPanel->setBackGroundImage("cocosgui/scrollviewbg.png");
        dragPanel->setSize(Size(210, 122.5));        
        Size backgroundSize = background->getContentSize();
        dragPanel->setPosition(Point((widgetSize.width - backgroundSize.width) / 2 +
                                   (backgroundSize.width - dragPanel->getSize().width) / 2,
                                   (widgetSize.height - backgroundSize.height) / 2 +
                                   (backgroundSize.height - dragPanel->getSize().height) / 2));
        dragPanel->addEventListener(this, dragpaneleventselector(UIDragPanelTest::dragPanelEvent));
        
        UIImageView* imageView = UIImageView::create();
        imageView->setTouchEnabled(true);
        imageView->loadTexture("cocosgui/b11.png");
        dragPanel->addChild(imageView);
        
        dragPanel->setInnerContainerSize(imageView->getContentSize());
        Size innerSize = dragPanel->getInnerContainerSize();
        imageView->setPosition(Point(innerSize.width / 2, innerSize.height / 2));                
        
        m_pUiLayer->addWidget(dragPanel);
        
        return true;
    }
    return false;
}

void UIDragPanelTest::dragPanelEvent(Object *pSender, DragPanelEventType type)
{
    switch (type)
    {
        case DRAGPANEL_EVENT_BERTH_LEFTBOTTOM:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left Bottom")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BERTH_LFETTOP:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left Top")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BERTH_RIGHTBOTTOM:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right Bottom")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BERTH_RIGHTTOP:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right Top")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BERTH_LEFT:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BERTH_TOP:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Top")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BERTH_RIGHT:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BERTH_BOTTOM:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Bottom")->getCString());
            break;
            
        default:
            break;
    }
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
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName(font_UIDragPanelTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("DragPanel Bounce");
        alert->setFontName(font_UIDragPanelTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        Layout *background = dynamic_cast<Layout*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the dragpanel
        UIDragPanel* dragPanel = UIDragPanel::create();
        dragPanel->setTouchEnabled(true);
        dragPanel->setBounceEnable(true);
        dragPanel->setBackGroundImageScale9Enabled(true);
        dragPanel->setBackGroundImage("cocosgui/green_edit.png");
        dragPanel->setSize(Size(210, 122.5));
        Size backgroundSize = background->getContentSize();
        dragPanel->setPosition(Point((widgetSize.width - backgroundSize.width) / 2 +
                                   (backgroundSize.width - dragPanel->getSize().width) / 2,
                                   (widgetSize.height - backgroundSize.height) / 2 +
                                   (backgroundSize.height - dragPanel->getSize().height) / 2));
        dragPanel->addEventListener(this, dragpaneleventselector(UIDragPanelTest_Bounce::dragPanelEvent));
        
        UIImageView* imageView = UIImageView::create();
        imageView->setTouchEnabled(true);
        imageView->loadTexture("cocosgui/b11.png");
        dragPanel->addChild(imageView);
        
        dragPanel->setInnerContainerSize(imageView->getContentSize());
        Size innerSize = dragPanel->getInnerContainerSize();
        imageView->setPosition(Point(innerSize.width / 2, innerSize.height / 2));
        
        m_pUiLayer->addWidget(dragPanel);
        
        return true;
    }
    
    return false;
}

void UIDragPanelTest_Bounce::dragPanelEvent(Object *pSender, DragPanelEventType type)
{
    switch (type)
    {
        case DRAGPANEL_EVENT_BOUNCE_LEFTBOTTOM:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left Bottom")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BOUNCE_LEFTTOP:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left Top")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BOUNCE_RIGHTBOTTOM:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right Bottom")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BOUNCE_RIGHTTOP:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right Top")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BOUNCE_LEFT:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BOUNCE_TOP:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Top")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BOUNCE_RIGHT:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right")->getCString());
            break;
            
        case DRAGPANEL_EVENT_BOUNCE_BOTTOM:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Bottom")->getCString());
            break;
            
        default:
            break;
    }
}
