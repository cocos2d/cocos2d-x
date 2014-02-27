

#include "UILabelAtlasTest.h"


// UILabelAtlasTest

bool UILabelAtlasTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        ui::Text* alert = ui::Text::create();
        alert->setText("LabelAtlas");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the label atlas
        ui::TextAtlas* labelAtlas = ui::TextAtlas::create();
        labelAtlas->setProperty("1234567890", "cocosgui/labelatlas.png", 17, 22, "0");
        labelAtlas->setPosition(Point((widgetSize.width) / 2, widgetSize.height / 2.0f));
        _uiLayer->addChild(labelAtlas);                
        
        return true;
    }
    return false;
}
