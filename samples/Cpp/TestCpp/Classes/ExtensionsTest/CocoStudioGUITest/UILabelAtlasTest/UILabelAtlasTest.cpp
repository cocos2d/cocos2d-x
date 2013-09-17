

#include "UILabelAtlasTest.h"

const char* font_UILabelAtlasTest =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Marker Felt";
#else
"cocosgui/Marker Felt.ttf";
#endif

// UILabelAtlasTest

bool UILabelAtlasTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("LabelAtlas");
        alert->setFontName(font_UILabelAtlasTest);
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the label atlas
        UILabelAtlas* labelAtlas = UILabelAtlas::create();
        labelAtlas->setProperty("1234567890", "cocosgui/labelatlas.png", 17, 22, "0");
        labelAtlas->setPosition(Point((widgetSize.width) / 2, widgetSize.height / 2.0f));        
        
        m_pUiLayer->addWidget(labelAtlas);                
        
        return true;
    }
    return false;
}