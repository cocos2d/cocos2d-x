

#include "UITextTest.h"


// UITextTest

bool UITextTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        Text* alert = Text::create("Text","fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the text
        Text* text = Text::create("Text", "AmericanTypewriter", 30);
        text->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + text->getSize().height / 4.0f));
        _uiLayer->addChild(text);
        
        return true;
    }
    return false;
}

// UITextTest_LineWrap

bool UITextTest_LineWrap::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        Text* alert = Text::create("Text line wrap","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the line wrap
        Text* text = Text::create("Text can line wrap","AmericanTypewriter",32);
        text->ignoreContentAdaptWithSize(false);
        text->setSize(Size(280, 150));
        text->setTextHorizontalAlignment(TextHAlignment::CENTER);
        text->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - text->getSize().height / 8.0f));
        _uiLayer->addChild(text);
        
        return true;
    }
    return false;
}

// UILabelTest_Effect

/*
bool UILabelTest_Effect::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        Text* alert = Text::create();
        alert->setText("Label Effect");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.05f));
        _uiLayer->addChild(alert);
        
        
        // create the shadow only label
        Text* shadow_label = Text::create();
        
        Color3B tintColorRed      =  { 255, 0, 0   };
        Size shadowOffset(12.0f, 12.0f);
        
        FontDefinition shadowTextDef;
        shadowTextDef._fontSize = 20;
        shadowTextDef._fontName = std::string("fonts/Marker Felt.ttf");
        
        shadowTextDef._shadow._shadowEnabled = true;
        shadowTextDef._shadow._shadowOffset  = shadowOffset;
        shadowTextDef._shadow._shadowOpacity = 1.0f;
        shadowTextDef._shadow._shadowBlur    = 1.0f;
        shadowTextDef._fontFillColor   = tintColorRed;
        
        shadow_label->setTextDefinition(shadowTextDef);
        shadow_label->setText("Shadow");
        shadow_label->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + shadow_label->getSize().height));
        
        _uiLayer->addChild(shadow_label);
        
        
        // create the stroke only label
        Text* stroke_label = Text::create();
        
        Color3B tintColorYellow   =  { 255, 255, 0 };
        Color3B strokeColor       =  { 0, 10, 255  };
        
        FontDefinition strokeTextDef;
        strokeTextDef._fontSize = 20;
        strokeTextDef._fontName = std::string("fonts/Marker Felt.ttf");
        
        strokeTextDef._stroke._strokeEnabled = true;
        strokeTextDef._stroke._strokeColor   = strokeColor;
        strokeTextDef._stroke._strokeSize    = 1.5f;
        
        strokeTextDef._fontFillColor   = tintColorYellow;
        
        stroke_label->setTextDefinition(strokeTextDef);
        stroke_label->setText("Stroke");
        stroke_label->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        
        _uiLayer->addChild(stroke_label);
        
        
        // create the label stroke and shadow
        Text* strokeAndShadow_label = Text::create();
        
        Color3B tintColorBlue     =  { 0, 0, 255   };
        Color3B strokeShadowColor =  { 255, 0, 0   };
        
        FontDefinition strokeShaodwTextDef;
        strokeShaodwTextDef._fontSize = 20;
        strokeShaodwTextDef._fontName = std::string("fonts/Marker Felt.ttf");
        
        strokeShaodwTextDef._stroke._strokeEnabled = true;
        strokeShaodwTextDef._stroke._strokeColor   = strokeShadowColor;
        strokeShaodwTextDef._stroke._strokeSize    = 1.5f;
        
        strokeShaodwTextDef._shadow._shadowEnabled = true;
        strokeShaodwTextDef._shadow._shadowOffset  = shadowOffset;
        strokeShaodwTextDef._shadow._shadowOpacity = 1.0f;
        strokeShaodwTextDef._shadow._shadowBlur    = 1.0f;
        
        strokeShaodwTextDef._fontFillColor   = tintColorBlue;
        
        strokeAndShadow_label->setTextDefinition(strokeShaodwTextDef);
//        strokeAndShadow_label->setFontFillColor(tintColorRed);
        strokeAndShadow_label->setText("Stroke and Shadow");
        strokeAndShadow_label->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - shadow_label->getSize().height));
        
        _uiLayer->addChild(strokeAndShadow_label);
        
        
        return true;
    }
    return false;
}
 */

// UITextTest_TTF

bool UITextTest_TTF::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        Text* alert = Text::create("Text set TTF font","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the text, and set font with .ttf
        Text* text = Text::create("Text","fonts/A Damn Mess.ttf",30);
        text->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + text->getSize().height / 4.0f));
        _uiLayer->addChild(text);
        
        return true;
    }
    return false;
}
