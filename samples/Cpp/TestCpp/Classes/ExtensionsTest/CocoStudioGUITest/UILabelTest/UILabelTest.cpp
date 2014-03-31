

#include "UILabelTest.h"


// UILabelTest

bool UILabelTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel* alert = UILabel::create();
        alert->setText("Label");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the label
        UILabel* label = UILabel::create();
        label->setText("Label");
        label->setFontName("AmericanTypewriter");
        label->setFontSize(30);
        label->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 + label->getSize().height / 4));
        m_pUiLayer->addWidget(label);
        
        return true;
    }
    return false;
}

// UILabelTest_LineWrap

bool UILabelTest_LineWrap::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel* alert = UILabel::create();
        alert->setText("Label line wrap");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the line wrap
        UILabel* label = UILabel::create();
        label->ignoreContentAdaptWithSize(false);
        label->setSize(CCSizeMake(280, 150));
        label->setTextHorizontalAlignment(kCCTextAlignmentCenter);
        label->setText("Label can line wrap");
        label->setFontName("AmericanTypewriter");
        label->setFontSize(32);
        label->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 - label->getSize().height / 8));
        m_pUiLayer->addWidget(label);
        
        return true;
    }
    return false;
}

/*===*/
/*
// UILabelTest_Effect

bool UILabelTest_Effect::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel *alert = UILabel::create();
        alert->setText("Label Effect");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.05));
        m_pUiLayer->addWidget(alert);
        
        
        // create the shadow only label
        UILabel* shadow_label = UILabel::create();
        
        ccColor3B tintColorRed      =  { 255, 0, 0   };
        CCSize shadowOffset(12.0, 12.0);
        
        ccFontDefinition shadowTextDef;
        shadowTextDef.m_fontSize = 20;
        shadowTextDef.m_fontName = std::string("Marker Felt");
        
        shadowTextDef.m_shadow.m_shadowEnabled = true;
        shadowTextDef.m_shadow.m_shadowOffset  = shadowOffset;
        shadowTextDef.m_shadow.m_shadowOpacity = 1.0;
        shadowTextDef.m_shadow.m_shadowBlur    = 1.0;
        shadowTextDef.m_fontFillColor   = tintColorRed;
        
        shadow_label->setTextDefinition(&shadowTextDef);
        shadow_label->setText("Shadow");
        shadow_label->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 + shadow_label->getSize().height));
        
        m_pUiLayer->addWidget(shadow_label);
        
        
        // create the stroke only label
        UILabel* stroke_label = UILabel::create();
        
        ccColor3B tintColorYellow   =  { 255, 255, 0 };
        ccColor3B strokeColor       =  { 0, 10, 255  };
        
        ccFontDefinition strokeTextDef;
        strokeTextDef.m_fontSize = 20;
        strokeTextDef.m_fontName = std::string("Marker Felt");
        
        strokeTextDef.m_stroke.m_strokeEnabled = true;
        strokeTextDef.m_stroke.m_strokeColor   = strokeColor;
        strokeTextDef.m_stroke.m_strokeSize    = 1.5;
        
        strokeTextDef.m_fontFillColor   = tintColorYellow;
        
        stroke_label->setTextDefinition(&strokeTextDef);
        stroke_label->setText("Stroke");
        stroke_label->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2));
        
        m_pUiLayer->addWidget(stroke_label);
        
        
        // create the label stroke and shadow
        UILabel* strokeAndShadow_label = UILabel::create();
        
        ccColor3B tintColorBlue     =  { 0, 0, 255   };
        ccColor3B strokeShadowColor =  { 255, 0, 0   };
        
        ccFontDefinition strokeShaodwTextDef;
        strokeShaodwTextDef.m_fontSize = 20;
        strokeShaodwTextDef.m_fontName = std::string("Marker Felt");
        
        strokeShaodwTextDef.m_stroke.m_strokeEnabled = true;
        strokeShaodwTextDef.m_stroke.m_strokeColor   = strokeShadowColor;
        strokeShaodwTextDef.m_stroke.m_strokeSize    = 1.5;
        
        strokeShaodwTextDef.m_shadow.m_shadowEnabled = true;
        strokeShaodwTextDef.m_shadow.m_shadowOffset  = shadowOffset;
        strokeShaodwTextDef.m_shadow.m_shadowOpacity = 1.0;
        strokeShaodwTextDef.m_shadow.m_shadowBlur    = 1.0;
        
        strokeShaodwTextDef.m_fontFillColor   = tintColorBlue;
        
        strokeAndShadow_label->setTextDefinition(&strokeShaodwTextDef);
//        strokeAndShadow_label->setFontFillColor(tintColorRed);
        strokeAndShadow_label->setText("Stroke and Shadow");
        strokeAndShadow_label->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 - shadow_label->getSize().height));
        
        m_pUiLayer->addWidget(strokeAndShadow_label);
        
        
        return true;
    }
    return false;
}
 */

// UILabelTest_TTF

bool UILabelTest_TTF::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        UILabel* alert = UILabel::create();
        alert->setText("Label set TTF font");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the label
        UILabel* label = UILabel::create();
        label->setText("Label");
        label->setFontName("fonts/A Damn Mess.ttf");
        label->setFontSize(30);
        label->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 + label->getSize().height / 4));
        m_pUiLayer->addWidget(label);
        
        return true;
    }
    return false;
}
/*=*/