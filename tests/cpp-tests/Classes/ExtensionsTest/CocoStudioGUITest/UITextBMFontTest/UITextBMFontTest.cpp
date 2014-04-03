

#include "UITextBMFontTest.h"


// UITextBMFontTest

bool UITextBMFontTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        Text* alert = Text::create("TextBMFont","TextBMFont",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the TextBMFont
        TextBMFont* textBMFont = TextBMFont::create("BMFont", "cocosui/bitmapFontTest2.fnt");
        textBMFont->setPosition(Point(widgetSize.width / 2, widgetSize.height / 2.0f + textBMFont->getSize().height / 8.0f));
        _uiLayer->addChild(textBMFont);
        
        return true;
    }
    return false;
}
