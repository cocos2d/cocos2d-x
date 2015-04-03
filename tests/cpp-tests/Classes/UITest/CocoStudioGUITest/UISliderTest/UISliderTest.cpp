

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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("Move the slider thumb","Move the slider thumb",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("Slider","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("Move the slider thumb","fonts/Marker Felt.ttf",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text *alert = Text::create("Slider scale9 render","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderTrack2.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/slider_bar_active_9patch.png");
        slider->setScale9Enabled(true);
        slider->setCapInsets(Rect(0, 0, 0, 0));
        slider->setContentSize(Size(250.0f, 19));
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

// UISliderTest_Scale9_State_Change

UISliderTest_Scale9_State_Change::UISliderTest_Scale9_State_Change()
    : _displayValueLabel(nullptr)
{

}

UISliderTest_Scale9_State_Change::~UISliderTest_Scale9_State_Change()
{
}

bool UISliderTest_Scale9_State_Change::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("Click the slider thumb", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text *alert = Text::create("Slider scale9 render", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);

        // Create the slider
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderballnormal.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/slider_bar_active_9patch.png");
        slider->ignoreContentAdaptWithSize(false);
        slider->setScale9Enabled(true);
        slider->setCapInsets(Rect(0, 0, 0, 0));
        slider->setContentSize(Size(200.0f, 60));
        slider->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 3.0f*/));
        slider->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
            if (type == Widget::TouchEventType::ENDED) {
                if (slider->isScale9Enabled())
                {
                    slider->setScale9Enabled(false);
                }
                else
                    slider->setScale9Enabled(true);
            }
        });
        _uiLayer->addChild(slider);


        return true;
    }
    return false;
}

void UISliderTest_Scale9_State_Change::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        _displayValueLabel->setString(String::createWithFormat("Percent %d", percent)->getCString());
    }
}

// UISliderNormalDefaultTest

UISliderNormalDefaultTest::UISliderNormalDefaultTest()
: _displayValueLabel(nullptr)
{
    
}

UISliderNormalDefaultTest::~UISliderNormalDefaultTest()
{
}

bool UISliderNormalDefaultTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("","Arial",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 100));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("when pressed, the slider ball should scale","fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.75f));
        _uiLayer->addChild(alert);
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png");
        slider->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f + 50));
        _uiLayer->addChild(slider);
        
        Slider* sliderScale9 = Slider::create("cocosui/sliderTrack2.png", "cocosui/sliderThumb.png");
        sliderScale9->setScale9Enabled(true);
        sliderScale9->setCapInsets(Rect(0, 0, 0, 0));
        sliderScale9->setZoomScale(1.0);
        sliderScale9->setContentSize(Size(250.0f, 19));
        sliderScale9->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 20));
        _uiLayer->addChild(sliderScale9);
        
        
        return true;
    }
    return false;
}

// UISliderDisabledDefaultTest

UISliderDisabledDefaultTest::UISliderDisabledDefaultTest()
: _displayValueLabel(nullptr)
{
    
}

UISliderDisabledDefaultTest::~UISliderDisabledDefaultTest()
{
}

bool UISliderDisabledDefaultTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("","Arial",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 100));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("slider ball should be gray.","fonts/Marker Felt.ttf",20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.75f));
        _uiLayer->addChild(alert);
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/slidbar.png");
        slider->loadSlidBallTextureNormal("cocosui/sliderballnormal.png");
        slider->setEnabled(false);
        slider->setBright(false);
        slider->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f + 50));
        _uiLayer->addChild(slider);
        
        Slider* sliderScale9 = Slider::create("cocosui/slidbar.png", "cocosui/sliderballnormal.png");
        sliderScale9->setScale9Enabled(true);
        sliderScale9->setEnabled(false);
        sliderScale9->setBright(false);
        sliderScale9->setCapInsets(Rect(0, 0, 0, 0));
        sliderScale9->setContentSize(Size(250.0f, 10));
        sliderScale9->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 20));
        _uiLayer->addChild(sliderScale9);
        
        
        return true;
    }
    return false;
}


