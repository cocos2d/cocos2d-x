

#include "UIDragPanelTest.h"

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
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("DragPanel");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the dragpanel
        UIDragPanel* dragPanel = UIDragPanel::create();
        dragPanel->setClippingEnable(true);
        dragPanel->setTouchEnable(true);
        dragPanel->setBackGroundImageScale9Enable(true);
        dragPanel->setBackGroundImage("cocosgui/scrollviewbg.png");
        dragPanel->setSize(CCSizeMake(210, 122.5));        
        CCSize backgroundSize = background->getContentSize();
        dragPanel->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                   (backgroundSize.width - dragPanel->getRect().size.width) / 2,
                                   (widgetSize.height - backgroundSize.height) / 2 +
                                   (backgroundSize.height - dragPanel->getRect().size.height) / 2));
        dragPanel->addBerthToLeftBottomEvent(this, coco_DragPane_BerthToLeftBottom_selector(UIDragPanelTest::berthToLeftBottomEvent));
        dragPanel->addBerthToLeftTopEvent(this, coco_DragPanel_BerthToLeftTop_selector(UIDragPanelTest::berthToLeftTopEvent));
        dragPanel->addBerthToRightBottomEvent(this, coco_DragPanel_BerthToRightBottom_selector(UIDragPanelTest::berthToRightBottomEvent));
        dragPanel->addBerthToRightTopEvent(this,  coco_DragPanel_BerthToRightTop_selector(UIDragPanelTest::berthToRightTopEvent));
        dragPanel->addBerthToLeftEvent(this, coco_DragPanel_BerthToLeft_selector(UIDragPanelTest::berthToLeftEvent));
        dragPanel->addBerthToTopEvent(this, coco_DragPanel_BerthToTop_selector(UIDragPanelTest::berthToTopEvent));
        dragPanel->addBerthToRightEvent(this, coco_DragPanel_BerthToRight_selector(UIDragPanelTest::berthToRightEvent));
        dragPanel->addBerthToBottomEvent(this, coco_DragPanel_BerthToBottom_selector(UIDragPanelTest::berthToBottomEvent));
        
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

void UIDragPanelTest::berthToLeftBottomEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left Bottom")->getCString());
}

void UIDragPanelTest::berthToLeftTopEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left Top")->getCString());
}

void UIDragPanelTest::berthToRightBottomEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right Bottom")->getCString());
}

void UIDragPanelTest::berthToRightTopEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right Top")->getCString());
}

void UIDragPanelTest::berthToLeftEvent(CCObject* pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Left")->getCString());
}

void UIDragPanelTest::berthToTopEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Top")->getCString());
}

void UIDragPanelTest::berthToRightEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Berth To Right")->getCString());
}

void UIDragPanelTest::berthToBottomEvent(CCObject *pSender)
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
        CCSize widgetSize = m_pWidget->getRect().size;;
        
        // Add a label in which the dragpanel events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getRect().size.height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("DragPanel Bounce");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 2.925));
        m_pUiLayer->addWidget(alert);
        
        UIPanel *background = dynamic_cast<UIPanel*>(m_pUiLayer->getWidgetByName("background_Panel"));
        
        // Create the dragpanel
        UIDragPanel* dragPanel = UIDragPanel::create();
        dragPanel->setClippingEnable(true);
        dragPanel->setTouchEnable(true);
        dragPanel->setBounceEnable(true);
        dragPanel->setBackGroundImageScale9Enable(true);
        dragPanel->setBackGroundImage("extensions/green_edit.png");
        dragPanel->setSize(CCSizeMake(210, 122.5));
        CCSize backgroundSize = background->getContentSize();
        dragPanel->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                                   (backgroundSize.width - dragPanel->getRect().size.width) / 2,
                                   (widgetSize.height - backgroundSize.height) / 2 +
                                   (backgroundSize.height - dragPanel->getRect().size.height) / 2));
        dragPanel->addBounceToLeftBottomEvent(this, coco_DragPanel_BounceToLeftBottom_selector(UIDragPanelTest_Bounce::bounceToLeftBottomEvent));
        dragPanel->addBounceToLeftTopEvent(this, coco_DragPanel_BounceToLeftTop_selector(UIDragPanelTest_Bounce::bounceToLeftTopEvent));
        dragPanel->addBounceToRightBottomEvent(this, coco_DragPanel_BounceToRightBottom_selector(UIDragPanelTest_Bounce::bounceToRightBottomEvent));
        dragPanel->addBounceToRightTopEvent(this, coco_DragPanel_BounceToRightTop_selector(UIDragPanelTest_Bounce::bounceToRightTopEvent));
        dragPanel->addBounceToLeftEvent(this, coco_DragPanel_BounceToLeft_selector(UIDragPanelTest_Bounce::bounceToLeftEvent));
        dragPanel->addBounceToTopEvent(this, coco_DragPanel_BounceToTop_selector(UIDragPanelTest_Bounce::bounceToTopEvent));
        dragPanel->addBounceToRightEvent(this, coco_DragPanel_BounceToRight_selector(UIDragPanelTest_Bounce::bounceToRightEvent));
        dragPanel->addBounceToBottomEvent(this, coco_DragPanel_BounceToBottom_selector(UIDragPanelTest_Bounce::bounceToBottomEvent));
        
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

void UIDragPanelTest_Bounce::bounceToLeftBottomEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left Bottom")->getCString());
}

void UIDragPanelTest_Bounce::bounceToLeftTopEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left Top")->getCString());
}

void UIDragPanelTest_Bounce::bounceToRightBottomEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right Bottom")->getCString());
}

void UIDragPanelTest_Bounce::bounceToRightTopEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right Top")->getCString());
}

void UIDragPanelTest_Bounce::bounceToLeftEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Left")->getCString());
}

void UIDragPanelTest_Bounce::bounceToTopEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Top")->getCString());
}

void UIDragPanelTest_Bounce::bounceToRightEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Right")->getCString());
}

void UIDragPanelTest_Bounce::bounceToBottomEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Bounce To Bottom")->getCString());
}
