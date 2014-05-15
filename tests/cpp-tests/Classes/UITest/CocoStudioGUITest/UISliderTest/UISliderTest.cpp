

#include "UISliderTest.h"


// UISliderTest

UISliderTest::UISliderTest()
: _displayValueLabel(nullptr)
{
    
}

UISliderTest::~UISliderTest()
{
}

bool UISliderTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("Move the slider thumb","Move the slider thumb",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("Slider","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/sliderProgress.png");
        slider->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 2.0f*/));
        slider->addEventListener(CC_CALLBACK_2(UISliderTest::sliderEvent, this));
        _uiLayer->addChild(slider);

        
        return true;
    }
    return false;
}

void UISliderTest::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        _displayValueLabel->setString(String::createWithFormat("Percent %d", percent)->getCString());
    }
}

// UISliderTest_Scale9

UISliderTest_Scale9::UISliderTest_Scale9()
: _displayValueLabel(nullptr)
{
    
}

UISliderTest_Scale9::~UISliderTest_Scale9()
{
}

bool UISliderTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("Move the slider thumb","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text *alert = Text::create("Slider scale9 render","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderTrack2.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/slider_bar_active_9patch.png");
        slider->setScale9Enabled(true);
        slider->setCapInsets(Rect(0, 0, 0, 0));
        slider->setSize(Size(250.0f, 19));
        slider->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 3.0f*/));
        slider->addEventListener(CC_CALLBACK_2(UISliderTest_Scale9::sliderEvent, this));
        _uiLayer->addChild(slider);
        
        
        return true;
    }
    return false;
}

void UISliderTest_Scale9::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        _displayValueLabel->setString(String::createWithFormat("Percent %d", percent)->getCString());
    }
}
