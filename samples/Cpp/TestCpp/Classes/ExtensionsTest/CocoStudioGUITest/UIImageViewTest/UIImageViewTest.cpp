

#include "UIImageViewTest.h"

const char* font_UIImageViewTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UIImageViewTest

bool UIImageViewTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        cocos2d::gui::Label *alert = cocos2d::gui::Label::create();
        alert->setText("ImageView");
        alert->setFontName(font_UIImageViewTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addChild(alert);        
        
        // Create the imageview
        cocos2d::gui::ImageView *imageView = cocos2d::gui::ImageView::create();
        imageView->loadTexture("cocosgui/ccicon.png");
        imageView->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
        m_pUiLayer->addChild(imageView);
        
        return true;
    }
    return false;
}


// UIImageViewTest_Scale9

bool UIImageViewTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        cocos2d::gui::Label *alert = cocos2d::gui::Label::create();
        alert->setText("ImageView scale9 render");
        alert->setFontName(font_UIImageViewTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addChild(alert);        
        
        // Create the imageview
        cocos2d::gui::ImageView *imageView = cocos2d::gui::ImageView::create();
        imageView->setScale9Enabled(true);
        imageView->loadTexture("cocosgui/buttonHighlighted.png");
        imageView->setSize(Size(200, 85));
        imageView->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
        m_pUiLayer->addChild(imageView);
        
        return true;
    }
    return false;
}