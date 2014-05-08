

#include "UIImageViewTest.h"


// UIImageViewTest

bool UIImageViewTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel* alert = UILabel::create();
        alert->setText("ImageView");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the imageview
        UIImageView* imageView = UIImageView::create();
        imageView->loadTexture("cocosui/ccicon.png");
        imageView->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
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
        
        UILabel* alert = UILabel::create();
        alert->setText("ImageView scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125));
        m_pUiLayer->addWidget(alert);        
        
        // Create the imageview
        UIImageView* imageView = UIImageView::create();
        imageView->setScale9Enabled(true);
        imageView->loadTexture("cocosui/buttonHighlighted.png");
        imageView->setSize(CCSizeMake(200, 85));
        imageView->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + imageView->getSize().height / 4.0f));
        m_pUiLayer->addWidget(imageView);
        
        return true;
    }
    return false;
}