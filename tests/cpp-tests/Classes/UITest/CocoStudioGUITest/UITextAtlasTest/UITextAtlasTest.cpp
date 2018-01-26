#include "UITextAtlasTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITextAtlasTests::UITextAtlasTests()
{
    ADD_TEST_CASE(UITextAtlasTest);
    ADD_TEST_CASE(UITextAtlasETC1ShadowTest);
}
// UITextAtlasTest

bool UITextAtlasTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("TextAtlas","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the text atlas
        TextAtlas* textAtlas = nullptr;
        if (Director::getInstance()->getWinSizeInPixels().height > 320.f)
        {
            textAtlas = TextAtlas::create("1234567890", "cocosui/labelatlas.png", 34, 44, "0");
        }
        else
        {
            textAtlas = TextAtlas::create("1234567890", "cocosui/labelatlas.png", 17, 22, "0");
        }
        textAtlas->setPosition(Vec2((widgetSize.width) / 2, widgetSize.height / 2.0f));
        _uiLayer->addChild(textAtlas);                
        _textAtlas = textAtlas;

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UITextAtlasTest::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0, 0));
        this->addChild(pMenu1, 10);
        return true;
    }
    return false;
}
void UITextAtlasTest::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData textureFile = _textAtlas->getRenderFile();
    CCLOG("textureFile  Name : %s, Type: %d", textureFile.file.c_str(), textureFile.type);
}

// UITextAtlasETC1ShadowTest

bool UITextAtlasETC1ShadowTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("TextAtlas With ETC1 format","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the text atlas
        TextAtlas* textAtlas = nullptr;
        if (Director::getInstance()->getWinSizeInPixels().height > 320.f)
        {
            textAtlas = TextAtlas::create("1234567890", "cocosui/labelatlas.pkm", 34, 44, "0");
        }
        else
        {
            textAtlas = TextAtlas::create("1234567890", "cocosui/labelatlas.pkm", 17, 22, "0");
        }
        textAtlas->setPosition(Vec2((widgetSize.width) / 2, widgetSize.height / 2.0f));
        _uiLayer->addChild(textAtlas);
        auto labelAtlas = (Label*)textAtlas->getVirtualRenderer();
        labelAtlas->enableShadow(Color4B::GREEN);
        _textAtlas = textAtlas;
        
        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UITextAtlasETC1ShadowTest::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0, 0));
        this->addChild(pMenu1, 10);
        return true;
    }
    return false;
}
void UITextAtlasETC1ShadowTest::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData textureFile = _textAtlas->getRenderFile();
    CCLOG("textureFile  Name : %s, Type: %d", textureFile.file.c_str(), textureFile.type);
}
