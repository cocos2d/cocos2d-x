

#include "UIImageViewTest.h"


// UIImageViewTest

bool UIImageViewTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel* alert = UILabel::create("ImageView","Marker Felt",30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f,
                               widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the imageview
        UIImageView* imageView = UIImageView::create("cocosgui/ccicon.png");
        imageView->setPosition(ccp(widgetSize.width / 2.0f,
                                   widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
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
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel* alert = UILabel::create("ImageView scale9 render","Marker Felt",26);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f,
                               widgetSize.height / 2.0f - alert->getSize().height * 2.125));
        m_pUiLayer->addWidget(alert);        
        
        // Create the imageview
        UIImageView* imageView = UIImageView::create("cocosgui/buttonHighlighted.png");
        imageView->setScale9Enabled(true);
        imageView->setSize(CCSizeMake(200, 85));
        imageView->setPosition(ccp(widgetSize.width / 2.0f,
                                   widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
        m_pUiLayer->addWidget(imageView);
        
        return true;
    }
    return false;
}