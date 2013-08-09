

#include "UIImageViewTest.h"

// UIImageViewTest

bool UIImageViewTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        UILabel *alert = UILabel::create();
        alert->setText("ImageView");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the imageview
        UIImageView *imageView = UIImageView::create();
        imageView->setTexture("cocosgui/ccicon.png");
        imageView->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getRect().size.height / 4.0f));
        m_pUiLayer->addWidget(imageView);
        
        return true;
    }
    return false;
}


// UIImageViewTest_Scale9

bool UIImageViewTest_Scale9::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        UILabel *alert = UILabel::create();
        alert->setText("ImageView scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the ui layer
        UILayer *ul = UILayer::create();
        ul->scheduleUpdate();
        addChild(ul);
        
        // Create the imageview
        UIImageView *imageView = UIImageView::create();
        imageView->setScale9Enable(true);
        imageView->setTexture("cocosgui/buttonHighlighted.png");
        imageView->setScale9Size(CCSizeMake(200, 85));
        imageView->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getRect().size.height / 4.0f));
        ul->addWidget(imageView);
        
        return true;
    }
    return false;
}