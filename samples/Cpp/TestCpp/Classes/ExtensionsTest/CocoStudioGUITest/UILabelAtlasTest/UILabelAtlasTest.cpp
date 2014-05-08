

#include "UILabelAtlasTest.h"

// UILabelAtlasTest

bool UILabelAtlasTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel* alert = UILabel::create();
        alert->setText("LabelAtlas");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        
        // Create the label atlas
        UILabelAtlas* labelAtlas = UILabelAtlas::create();
        labelAtlas->setProperty("1234567890", "cocosui/labelatlas.png", 17, 22, "0");
        labelAtlas->setPosition(ccp((widgetSize.width) / 2, widgetSize.height / 2.0f));
        
        m_pUiLayer->addWidget(labelAtlas);                
        
        return true;
    }
    return false;
}