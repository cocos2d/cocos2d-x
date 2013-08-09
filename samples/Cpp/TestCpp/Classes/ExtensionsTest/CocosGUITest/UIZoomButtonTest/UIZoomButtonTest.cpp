

#include "UIZoomButtonTest.h"

// UIZoomButtonTest
UIZoomButtonTest::UIZoomButtonTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UIZoomButtonTest::~UIZoomButtonTest()
{
    
}

bool UIZoomButtonTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the zoom button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("ZoomButton");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the zoom button
        UIZoomButton* zoomButton = UIZoomButton::create();
        zoomButton->setTouchEnable(true);
        zoomButton->setTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "cocosgui/button.png");
        zoomButton->setTitle("Normal", "Down", "Up");
        zoomButton->setNormalFontSize(32);
        zoomButton->setNormalFontName("Marker Felt");
        zoomButton->setPressedFontSize(32);
        zoomButton->setPressedFontName("Marker Felt");
        zoomButton->setDisabledFontSize(32);
        zoomButton->setDisabledFontName("Marker Felt");
        zoomButton->setPreferredSize(CCSizeMake(150, zoomButton->getContentSize().height * 2.0f));
        zoomButton->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        zoomButton->addPushDownEvent(this, coco_pushselector(UIZoomButtonTest::touchBeganEvent));
        zoomButton->addMoveEvent(this, coco_moveselector(UIZoomButtonTest::touchMovedEvent));
        zoomButton->addReleaseEvent(this, coco_releaseselector(UIZoomButtonTest::touchEndedEvent));
        m_pUiLayer->addWidget(zoomButton);
        
        return true;
    }
    return false;
}

void UIZoomButtonTest::touchBeganEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
}

void UIZoomButtonTest::touchMovedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
}

void UIZoomButtonTest::touchEndedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
}