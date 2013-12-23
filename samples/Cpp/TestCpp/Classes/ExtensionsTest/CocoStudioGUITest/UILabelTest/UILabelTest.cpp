

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
        Size widgetSize = m_pWidget->getSize();
        
        cocos2d::gui::Label *alert = cocos2d::gui::Label::create();
        alert->setText("Label");
        alert->setFontName(font_UILabelTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addChild(alert);        
        
        // Create the label
        cocos2d::gui::Label* label = cocos2d::gui::Label::create();
        label->setText("Label");
        label->setFontName("AmericanTypewriter");
        label->setFontSize(30);
        label->setPosition(Point(widgetSize.width / 2, widgetSize.height / 2 + label->getSize().height / 4));
        m_pUiLayer->addChild(label);
        
        return true;
    }
    return false;
}