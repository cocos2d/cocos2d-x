

#include "UILabelBMFontTest.h"

// UILabelBMFontTest

bool UILabelBMFontTest::init()
{
    if (UIScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        UILabel *alert = UILabel::create();
        alert->setText("LabelBMFont");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the LabelBMFont
        UILabelBMFont* labelBMFont = UILabelBMFont::create();
        labelBMFont->setFntFile("cocosgui/bitmapFontTest2.fnt");
        labelBMFont->setText("BMFont");
        labelBMFont->setPosition(ccp(screenSize.width / 2, screenSize.height / 2.0f + labelBMFont->getRect().size.height / 8.0f));
        m_pUiLayer->addWidget(labelBMFont);
        
        return true;
    }
    return false;
}