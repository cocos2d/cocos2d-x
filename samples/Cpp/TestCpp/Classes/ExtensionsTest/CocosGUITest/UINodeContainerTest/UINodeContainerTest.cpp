

#include "UINodeContainerTest.h"
#include "cocos-ext.h"

// UINodeContainerTest

UINodeContainerTest::UINodeContainerTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UINodeContainerTest::~UINodeContainerTest()
{
}

bool UINodeContainerTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the UINodeContainer alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("NodeContainer Add CCNode");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("NodeContainer");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the ui node container
        UINodeContainer* nodeContainer = UINodeContainer::create();
        nodeContainer->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(nodeContainer);
        
        CCSprite* sprite = CCSprite::create("cocosgui/ccicon.png");
        sprite->setPosition(ccp(0, sprite->boundingBox().size.height / 4));
        nodeContainer->addCCNode(sprite);
        
        return true;
    }
    return false;
}