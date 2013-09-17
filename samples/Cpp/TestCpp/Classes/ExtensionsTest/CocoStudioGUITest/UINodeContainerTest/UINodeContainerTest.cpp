

#include "UINodeContainerTest.h"
#include "cocos-ext.h"

const char* font_UINodeContainerTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

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
        Size widgetSize = m_pWidget->getSize();
        
        // Add a label in which the UINodeContainer alert will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("NodeContainer Add CCNode");
        m_pDisplayValueLabel->setFontName(font_UINodeContainerTest);
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(Point(0.5f, -1));
        m_pDisplayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + m_pDisplayValueLabel->getContentSize().height * 1.5));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("NodeContainer");
        alert->setFontName(font_UINodeContainerTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the ui node container
        UIWidget* nodeContainer = UIWidget::create();
        nodeContainer->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(nodeContainer);
        
        Sprite* sprite = Sprite::create("cocosgui/ccicon.png");
        sprite->setPosition(Point(0, sprite->boundingBox().size.height / 4));
        nodeContainer->addRenderer(sprite, 0);
        
        return true;
    }
    return false;
}