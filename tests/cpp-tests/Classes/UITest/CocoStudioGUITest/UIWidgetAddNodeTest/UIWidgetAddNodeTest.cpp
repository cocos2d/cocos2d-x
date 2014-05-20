

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
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        Text* alert = Text::create();
        alert->setString("Widget Add Node");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        _uiLayer->addChild(alert);
        
        // Create the ui node container
        Widget* widget = Widget::create();
        widget->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(widget);
        
        Sprite* sprite = Sprite::create("cocosui/ccicon.png");
        sprite->setPosition(Vec2(0, sprite->getBoundingBox().size.height / 4));
        widget->addChild(sprite);
        
        return true;
    }
    return false;
}
