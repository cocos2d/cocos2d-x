

#include "UIImageViewTest.h"


// UIImageViewTest

bool UIImageViewTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("ImageView", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        
        _uiLayer->addChild(alert);        
        
        // Create the imageview
        ImageView* imageView = ImageView::create("cocosui/ccicon.png");
        imageView->setPosition(Vec2(widgetSize.width / 2.0f,
                                     widgetSize.height / 2.0f));
        
        _uiLayer->addChild(imageView);
        
      
        
        return true;
    }
    return false;
}


// UIImageViewTest_Scale9

bool UIImageViewTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("ImageView scale9 render", "fonts/Marker Felt.ttf", 26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 2.125f));
        
        _uiLayer->addChild(alert);        
        
        // Create the imageview
        ImageView* imageView = ImageView::create("cocosui/buttonHighlighted.png");
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(300, 115));
        imageView->setPosition(Vec2(widgetSize.width / 2.0f,
                                     widgetSize.height / 2.0f));
        
        _uiLayer->addChild(imageView);                
        
        return true;
    }
    return false;
}
