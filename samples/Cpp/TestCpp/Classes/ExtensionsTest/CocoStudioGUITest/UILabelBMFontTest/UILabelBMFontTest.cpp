

#include "UILabelBMFontTest.h"


// UILabelBMFontTest

bool UILabelBMFontTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel* alert = UILabel::create("LabelBMFont","Marker Felt",30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f,
                               widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        
        m_pUiLayer->addWidget(alert);
        
        // Create the LabelBMFont
        UILabelBMFont* labelBMFont = UILabelBMFont::create("BMFont","cocosgui/bitmapFontTest2.fnt");
        labelBMFont->setPosition(ccp(widgetSize.width / 2,
                                     widgetSize.height / 2.0f + labelBMFont->getSize().height / 8.0f));
        
        m_pUiLayer->addWidget(labelBMFont);
        
        return true;
    }
    return false;
}