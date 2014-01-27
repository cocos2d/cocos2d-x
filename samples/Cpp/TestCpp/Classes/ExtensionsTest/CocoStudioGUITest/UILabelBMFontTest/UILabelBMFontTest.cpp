

#include "UILabelBMFontTest.h"


// UILabelBMFontTest

bool UILabelBMFontTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        gui::Text* alert = gui::Text::create();
        alert->setText("LabelBMFont");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the LabelBMFont
        gui::TextBMFont* labelBMFont = gui::TextBMFont::create();
        labelBMFont->setFntFile("cocosgui/bitmapFontTest2.fnt");
        labelBMFont->setText("BMFont");
        labelBMFont->setPosition(Point(widgetSize.width / 2, widgetSize.height / 2.0f + labelBMFont->getSize().height / 8.0f));
        _uiLayer->addChild(labelBMFont);
        
        return true;
    }
    return false;
}