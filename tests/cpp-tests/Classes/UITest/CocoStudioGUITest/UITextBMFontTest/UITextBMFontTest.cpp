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
        
        _textBMFont = textBMFont;

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UITextBMFontTest::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0, 0));
        this->addChild(pMenu1, 10);

        return true;
    }
    return false;
}
void UITextBMFontTest::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData textureFile = _textBMFont->getRenderFile();
    CCLOG("textureFile  Name : %s, Type: %d", textureFile.file.c_str(), textureFile.type);
}
