

#include "UILabelTest.h"

const char* font_UILabelTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UILabelTest

bool UILabelTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        UILabel *alert = UILabel::create();
        alert->setText("Label");
        alert->setFontName(font_UILabelTest);
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the label
        UILabel* label = UILabel::create();
        label->setText("Label");
        label->setFontName("AmericanTypewriter");
        label->setFontSize(30);
        label->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 + label->getRect().size.height / 4));
        m_pUiLayer->addWidget(label);
        
        return true;
    }
    return false;
}