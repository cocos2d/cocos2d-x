

#include "UIImageViewTest.h"


// UIImageViewTest

bool UIImageViewTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        gui::Text* alert = gui::Text::create();
        alert->setText("ImageView");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the imageview
        ImageView* imageView = ImageView::create();
        imageView->loadTexture("cocosgui/ccicon.png");
        imageView->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
        
//        imageView->setOpacity(64);
        _uiLayer->addChild(imageView);
        
        /*
        NodeRGBA* root = NodeRGBA::create();
        root->setCascadeOpacityEnabled(true);
        NodeRGBA* render = Sprite::create();
        static_cast<Sprite*>(render)->setTexture("cocosgui/ccicon.png");
        root->addChild(render);
//        root->setOpacity(64);
        root->setPosition(Point(200, 180));
        _uiLayer->addChild(root);
         */
        
        /*
        NodeRGBA* nodergba = NodeRGBA::create();
        Sprite* child = Sprite::create();
        child->setTexture("cocosgui/ccicon.png");
        nodergba->addChild(child);
        nodergba->setPosition(Point(120, 80));
        nodergba->setOpacity(64);
        _uiLayer->addChild(nodergba);
         */
        
        /*
        Sprite* sprite = Sprite::create();
        sprite->setTexture("cocosgui/ccicon.png");
        sprite->setPosition(Point(200, 180));
//        sprite->setOpacity(64);
        _uiLayer->addChild(sprite);
         */
        
//        imageView->setLocalZOrder(20);
        
        return true;
    }
    return false;
}


// UIImageViewTest_Scale9

bool UIImageViewTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        gui::Text* alert = gui::Text::create();
        alert->setText("ImageView scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125f));
        _uiLayer->addChild(alert);        
        
        // Create the imageview
        ImageView* imageView = ImageView::create();
        imageView->setScale9Enabled(true);
        imageView->loadTexture("cocosgui/buttonHighlighted.png");
        imageView->setSize(Size(200, 85));
        imageView->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
        _uiLayer->addChild(imageView);                
        
        return true;
    }
    return false;
}