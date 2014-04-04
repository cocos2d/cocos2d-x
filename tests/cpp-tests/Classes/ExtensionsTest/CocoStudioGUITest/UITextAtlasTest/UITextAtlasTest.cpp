

#include "UITextAtlasTest.h"


// UITextAtlasTest

bool UITextAtlasTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        Text* alert = Text::create();
        alert->setText("TextAtlas");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the text atlas
        TextAtlas* textAtlas = TextAtlas::create();
        textAtlas->setProperty("1234567890", "cocosui/labelatlas.png", 17, 22, "0");
        textAtlas->setPosition(Point((widgetSize.width) / 2, widgetSize.height / 2.0f));
        _uiLayer->addChild(textAtlas);                
        
        return true;
    }
    return false;
}
