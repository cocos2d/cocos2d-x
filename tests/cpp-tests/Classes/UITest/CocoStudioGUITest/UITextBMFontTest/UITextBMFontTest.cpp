#include "UITextBMFontTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITextBMFontTests::UITextBMFontTests()
{
    ADD_TEST_CASE(UITextBMFontTest);
}
// UITextBMFontTest

bool UITextBMFontTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("TextBMFont","TextBMFont",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the TextBMFont
        TextBMFont* textBMFont = TextBMFont::create("BMFont", "cocosui/bitmapFontTest2.fnt");
        textBMFont->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + textBMFont->getContentSize().height / 8.0f));
        _uiLayer->addChild(textBMFont);
        
        return true;
    }
    return false;
}
