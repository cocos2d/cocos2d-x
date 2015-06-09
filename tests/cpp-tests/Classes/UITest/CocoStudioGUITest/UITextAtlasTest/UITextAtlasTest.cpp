#include "UITextAtlasTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITextAtlasTests::UITextAtlasTests()
{
    ADD_TEST_CASE(UITextAtlasTest);
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
        TextAtlas* textAtlas = TextAtlas::create("1234567890", "cocosui/labelatlas.png", 17, 22, "0");
        textAtlas->setPosition(Vec2((widgetSize.width) / 2, widgetSize.height / 2.0f));
        _uiLayer->addChild(textAtlas);                
        
        return true;
    }
    return false;
}
