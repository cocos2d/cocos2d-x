

#include "UIWidgetAddNodeTest.h"


// UIWidgetAddNodeTest

UIWidgetAddNodeTest::UIWidgetAddNodeTest()
{
    
}

UIWidgetAddNodeTest::~UIWidgetAddNodeTest()
{
}

bool UIWidgetAddNodeTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Widget Add Node");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the ui node container
        UIWidget* widget = UIWidget::create();
        widget->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(widget);
        
        CCSprite* sprite = CCSprite::create("cocosui/ccicon.png");
        sprite->setPosition(ccp(0, sprite->boundingBox().size.height / 4));
        widget->addNode(sprite);
        
        return true;
    }
    return false;
}
