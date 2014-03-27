

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
        _displayValueLabel = Text::create();
        _displayValueLabel->setText("Move the slider thumb");
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create();
        alert->setText("Slider");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->setTouchEnabled(true);
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/sliderProgress.png");
        slider->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 2.0f*/));
        slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest::sliderEvent));
        _uiLayer->addChild(slider);

        /*
        // Create the slider that set allow min progress and allow max progress
        Slider* sliderAllow = Slider::create();
//        sliderAllow->setMinAllowPercent(20);
//        sliderAllow->setMaxAllowPercent(80);
        sliderAllow->setTouchEnabled(true);
        sliderAllow->loadBarTexture("cocosui/sliderTrack.png");
        sliderAllow->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        sliderAllow->loadProgressBarTexture("cocosui/sliderProgress.png");
        sliderAllow->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - sliderAllow->getSize().height * 2.0f));
        sliderAllow->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest::sliderEvent));
        _uiLayer->addChild(sliderAllow);
         */
        
        return true;
    }
    return false;
}

void UISliderTest::sliderEvent(Ref *pSender, SliderEventType type)
{
    if (type == SLIDER_PERCENTCHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        _displayValueLabel->setText(String::createWithFormat("Percent %d", percent)->getCString());
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
        _displayValueLabel = Text::create();
        _displayValueLabel->setText("Move the slider thumb");
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text *alert = Text::create();
        alert->setText("Slider scale9 render");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->setTouchEnabled(true);
        slider->loadBarTexture("cocosui/sliderTrack2.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/slider_bar_active_9patch.png");
        slider->setScale9Enabled(true);
        slider->setCapInsets(Rect(0, 0, 0, 0));
        slider->setSize(Size(250.0f, 19));
        slider->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 3.0f*/));
        slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Scale9::sliderEvent));
        _uiLayer->addChild(slider);
        
        /*
        // Create the slider that set allow min progress and allow max progress
        Slider* sliderAllow = Slider::create();
//        sliderAllow->setMinAllowPercent(20);
//        sliderAllow->setMaxAllowPercent(80);
        sliderAllow->setTouchEnabled(true);
        sliderAllow->loadBarTexture("cocosui/sliderTrack2.png");
        sliderAllow->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        sliderAllow->loadProgressBarTexture("cocosui/slider_bar_active_9patch.png");
        sliderAllow->setScale9Enabled(true);
        sliderAllow->setCapInsets(Rect(0, 0, 0, 0));
        sliderAllow->setSize(Size(250.0f, 10.0f / Director::getInstance()->getContentScaleFactor()));
        sliderAllow->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - slider->getSize().height * 3.0f));
        sliderAllow->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Scale9::sliderEvent));
        _uiLayer->addChild(sliderAllow);
         */
        
        return true;
    }
    return false;
}

void UISliderTest_Scale9::sliderEvent(Ref *pSender, SliderEventType type)
{
    if (type == SLIDER_PERCENTCHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        _displayValueLabel->setText(String::createWithFormat("Percent %d", percent)->getCString());
    }
}
