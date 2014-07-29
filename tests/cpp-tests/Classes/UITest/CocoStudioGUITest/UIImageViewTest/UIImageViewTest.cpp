

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

// UIImageViewTest_ContentSize

bool UIImageViewTest_ContentSize::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("ImageView ContentSize Change", "fonts/Marker Felt.ttf", 26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 2.125f));
        
        _uiLayer->addChild(alert);
        
        Text *status = Text::create("child ImageView position percent", "fonts/Marker Felt.ttf", 16);
        status->setColor(Color3B::RED);
        status->setPosition(Vec2(widgetSize.width/2, widgetSize.height/2 + 80));
        _uiLayer->addChild(status,20);
        
        // Create the imageview
        ImageView* imageView = ImageView::create("cocosui/buttonHighlighted.png");
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(200, 80));
        imageView->setPosition(Vec2(widgetSize.width / 2.0f,
                                    widgetSize.height / 2.0f ));
       
        
        ImageView* imageViewChild = ImageView::create("cocosui/buttonHighlighted.png");
        imageViewChild->setScale9Enabled(true);
        imageViewChild->setSizeType(Widget::SizeType::PERCENT);
        imageViewChild->setPositionType(Widget::PositionType::PERCENT);
        imageViewChild->setSizePercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild->setPositionPercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild->setPosition(Vec2(widgetSize.width / 2.0f,
                                    widgetSize.height / 2.0f));
        
        ImageView* imageViewChild2 = ImageView::create("cocosui/buttonHighlighted.png");
        imageViewChild2->setScale9Enabled(true);
        imageViewChild2->setSizeType(Widget::SizeType::PERCENT);
        imageViewChild2->setPositionType(Widget::PositionType::PERCENT);
        imageViewChild2->setSizePercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild2->setPositionPercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild->addChild(imageViewChild2);
        
        
        imageView->addChild(imageViewChild);
        
        imageView->setTouchEnabled(true);
        imageView->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
            if (type == Widget::TouchEventType::ENDED) {
                float width = CCRANDOM_0_1() * 200 + 50;
                float height = CCRANDOM_0_1() * 80 + 30;
                imageView->setContentSize(Size(width, height));
                
                imageViewChild->setPositionPercent(Vec2(CCRANDOM_0_1(), CCRANDOM_0_1()));
                status->setString(StringUtils::format("child ImageView position percent: %f, %f",
                                                      imageViewChild->getPositionPercent().x, imageViewChild->getPositionPercent().y));
            }
        });
        
        _uiLayer->addChild(imageView);
        
        return true;
    }
    return false;
}
