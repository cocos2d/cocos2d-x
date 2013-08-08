

#include "UITextAreaTest.h"

// UITextAreaTest

bool UITextAreaTest::init()
{
    if (UIScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        UILabel *alert = UILabel::create();
        alert->setText("TextArea");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the text area
        UITextArea* textArea = UITextArea::create();
        textArea->setTextAreaSize(CCSizeMake(280, 150));
        textArea->setTextHorizontalAlignment(kCCTextAlignmentCenter);
        textArea->setText("TextArea widget can line wrap");
        textArea->setFontName("AmericanTypewriter");
        textArea->setFontSize(32);
        textArea->setPosition(ccp(screenSize.width / 2, screenSize.height / 2 - textArea->getRect().size.height / 8));
        m_pUiLayer->addWidget(textArea);
        
        return true;
    }
    return false;
}