

#include "UILabelBMFontTest.h"

const char* font_UILabelBMFontTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UILabelBMFontTest

bool UILabelBMFontTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        UILabel *alert = UILabel::create();
        alert->setText("LabelBMFont");
        alert->setFontName(font_UILabelBMFontTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the LabelBMFont
        UILabelBMFont* labelBMFont = UILabelBMFont::create();
        labelBMFont->setFntFile("cocosgui/bitmapFontTest2.fnt");
        labelBMFont->setText("BMFont");
        labelBMFont->setPosition(Point(widgetSize.width / 2, widgetSize.height / 2.0f + labelBMFont->getSize().height / 8.0f));
        m_pUiLayer->addWidget(labelBMFont);
        
        return true;
    }
    return false;
}