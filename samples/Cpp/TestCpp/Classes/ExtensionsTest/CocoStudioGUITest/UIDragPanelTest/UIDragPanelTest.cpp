

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
        dragPanel->addBerthToLeftBottomEvent(this, coco_DragPane_BerthToLeftBottom_selector(UIDragPanelTest::berthToLeftBottomEvent));
        dragPanel->addBerthToLeftTopEvent(this, coco_DragPanel_BerthToLeftTop_selector(UIDragPanelTest::berthToLeftTopEvent));
        dragPanel->addBerthToRightBottomEvent(this, coco_DragPanel_BerthToRightBottom_selector(UIDragPanelTest::berthToRightBottomEvent));
        dragPanel->addBerthToRightTopEvent(this,  coco_DragPanel_BerthToRightTop_selector(UIDragPanelTest::berthToRightTopEvent));
        dragPanel->addBerthToLeftEvent(this, coco_DragPanel_BerthToLeft_selector(UIDragPanelTest::berthToLeftEvent));
        dragPanel->addBerthToTopEvent(this, coco_DragPanel_BerthToTop_selector(UIDragPanelTest::berthToTopEvent));
        dragPanel->addBerthToRightEvent(this, coco_DragPanel_BerthToRight_selector(UIDragPanelTest::berthToRightEvent));
        dragPanel->addBerthToBottomEvent(this, coco_DragPanel_BerthToBottom_selector(UIDragPanelTest::berthToBottomEvent));
        
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

void UIDragPanelTest::berthToLeftBottomEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left Bottom")->getCString());
}

void UIDragPanelTest::berthToLeftTopEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left Top")->getCString());
}

void UIDragPanelTest::berthToRightBottomEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right Bottom")->getCString());
}

void UIDragPanelTest::berthToRightTopEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right Top")->getCString());
}

void UIDragPanelTest::berthToLeftEvent(Object* pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left")->getCString());
}

void UIDragPanelTest::berthToTopEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Top")->getCString());
}

void UIDragPanelTest::berthToRightEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right")->getCString());
}

void UIDragPanelTest::berthToBottomEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Bottom")->getCString());
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
        dragPanel->addBounceToLeftBottomEvent(this, coco_DragPanel_BounceToLeftBottom_selector(UIDragPanelTest_Bounce::bounceToLeftBottomEvent));
        dragPanel->addBounceToLeftTopEvent(this, coco_DragPanel_BounceToLeftTop_selector(UIDragPanelTest_Bounce::bounceToLeftTopEvent));
        dragPanel->addBounceToRightBottomEvent(this, coco_DragPanel_BounceToRightBottom_selector(UIDragPanelTest_Bounce::bounceToRightBottomEvent));
        dragPanel->addBounceToRightTopEvent(this, coco_DragPanel_BounceToRightTop_selector(UIDragPanelTest_Bounce::bounceToRightTopEvent));
        dragPanel->addBounceToLeftEvent(this, coco_DragPanel_BounceToLeft_selector(UIDragPanelTest_Bounce::bounceToLeftEvent));
        dragPanel->addBounceToTopEvent(this, coco_DragPanel_BounceToTop_selector(UIDragPanelTest_Bounce::bounceToTopEvent));
        dragPanel->addBounceToRightEvent(this, coco_DragPanel_BounceToRight_selector(UIDragPanelTest_Bounce::bounceToRightEvent));
        dragPanel->addBounceToBottomEvent(this, coco_DragPanel_BounceToBottom_selector(UIDragPanelTest_Bounce::bounceToBottomEvent));
        
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

void UIDragPanelTest_Bounce::bounceToLeftBottomEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left Bottom")->getCString());
}

void UIDragPanelTest_Bounce::bounceToLeftTopEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left Top")->getCString());
}

void UIDragPanelTest_Bounce::bounceToRightBottomEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right Bottom")->getCString());
}

void UIDragPanelTest_Bounce::bounceToRightTopEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right Top")->getCString());
}

void UIDragPanelTest_Bounce::bounceToLeftEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left")->getCString());
}

void UIDragPanelTest_Bounce::bounceToTopEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Top")->getCString());
}

void UIDragPanelTest_Bounce::bounceToRightEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right")->getCString());
}

void UIDragPanelTest_Bounce::bounceToBottomEvent(Object *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Bottom")->getCString());
}
