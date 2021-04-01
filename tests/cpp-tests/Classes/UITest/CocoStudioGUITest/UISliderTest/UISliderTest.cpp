/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UISliderTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UISliderTests::UISliderTests()
{
    ADD_TEST_CASE(UISliderTest);
    ADD_TEST_CASE(UISliderTest_Scale9);
    ADD_TEST_CASE(UISliderTest_Scale9_State_Change);
    ADD_TEST_CASE(UISliderNormalDefaultTest);
    ADD_TEST_CASE(UISliderDisabledDefaultTest);
    ADD_TEST_CASE(UISliderNewEventCallbackTest);
    ADD_TEST_CASE(UISliderIssue12249Test);
}

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
        _displayValueLabel = TextBMFont::create("Move the slider thumb", "ccb/markerfelt24shadow.fnt");
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
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
        slider->setMaxPercent(10000);
        slider->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 2.0f*/));
        slider->addEventListener(CC_CALLBACK_2(UISliderTest::sliderEvent, this));
        _uiLayer->addChild(slider);

        _slider = slider;

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UISliderTest::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0.0f, 0.0f));
        this->addChild(pMenu1, 10);
        
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
        int maxPercent = slider->getMaxPercent();
        _displayValueLabel->setString(StringUtils::format("Percent %f", 10000.0 * percent / maxPercent));
    }
}
void UISliderTest::printWidgetResources(cocos2d::Ref* /*sender*/)
{
    cocos2d::ResourceData textureFile = _slider->getBackFile();
    CCLOG("textureFile  Name : %s, Type: %d", textureFile.file.c_str(), textureFile.type);
    cocos2d::ResourceData progressBarTextureFile = _slider->getProgressBarFile();
    CCLOG("progressBarTextureFile  Name : %s, Type: %d", progressBarTextureFile.file.c_str(), progressBarTextureFile.type);
    cocos2d::ResourceData slidBallNormalTextureFile = _slider->getBallNormalFile();
    CCLOG("slidBallNormalTextureFile  Name : %s, Type: %d", slidBallNormalTextureFile.file.c_str(), slidBallNormalTextureFile.type);
    cocos2d::ResourceData slidBallPressedTextureFile = _slider->getBallPressedFile();
    CCLOG("slidBallPressedTextureFile  Name : %s, Type: %d", slidBallPressedTextureFile.file.c_str(), slidBallPressedTextureFile.type);
    cocos2d::ResourceData slidBallDisabledTextureFile = _slider->getBallDisabledFile();
    CCLOG("slidBallDisabledTextureFile  Name : %s, Type: %d", slidBallDisabledTextureFile.file.c_str(), slidBallDisabledTextureFile.type);
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
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
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
        slider->setCapInsets(Rect(0.0f, 0.0f, 0.0f, 0.0f));
        slider->setContentSize(Size(250.0f, 19.0f));
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
        _displayValueLabel->setString(StringUtils::format("Percent %d", percent));
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
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
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
        slider->setCapInsets(Rect(0.0f, 0.0f, 0.0f, 0.0f));
        slider->setContentSize(Size(200.0f, 60.0f));
        slider->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 3.0f*/));
        slider->addTouchEventListener([=](Ref* /*sender*/, Widget::TouchEventType type){
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
        _displayValueLabel->setString(StringUtils::format("Percent %d", percent));
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
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
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
        
        Slider* sliderScale9 = (Slider*)slider->clone();
        sliderScale9->setScale9Enabled(true);
        sliderScale9->setCapInsets(Rect(0.0f, 0.0f, 0.0f, 0.0f));
        sliderScale9->setZoomScale(1.0);
        sliderScale9->setContentSize(Size(250.0f, 19.0f));
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
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
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
        
        Slider* sliderScale9 = (Slider*)slider->clone();
        sliderScale9->setScale9Enabled(true);
        sliderScale9->setEnabled(false);
        sliderScale9->setBright(false);
        sliderScale9->setCapInsets(Rect(0.0f, 0.0f, 0.0f, 0.0f));
        sliderScale9->setContentSize(Size(250.0f, 10.0f));
        sliderScale9->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 20));
        _uiLayer->addChild(sliderScale9);
        
        
        return true;
    }
    return false;
}



// UISliderNewEventCallbackTest

UISliderNewEventCallbackTest::UISliderNewEventCallbackTest()
: _displayValueLabel(nullptr)
{

}

UISliderNewEventCallbackTest::~UISliderNewEventCallbackTest()
{
}

bool UISliderNewEventCallbackTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the slider alert will be displayed
        _displayValueLabel = Text::create("","Arial",32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 100));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("See console output for Slider Down and Up event.", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.75f));
        _uiLayer->addChild(alert);

        // Create the slider
        Slider* slider = Slider::create();
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/sliderProgress.png");
        slider->setMaxPercent(1000);
        slider->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f + 50));
        slider->addEventListener([=](Ref* widget,Slider::EventType type)
        {
            Slider* slider = (Slider*)widget;
            CC_UNUSED_PARAM(slider);
            if(type == Slider::EventType::ON_SLIDEBALL_DOWN)
            {
                CCLOG("slider button pressed!");
            }
            else if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
            {
                CCLOG("slider is moving! percent = %f", 100.0f * slider->getPercent() / slider->getMaxPercent() );
            }
            else if(type == Slider::EventType::ON_SLIDEBALL_UP)
            {
                CCLOG("slider button is released.");
            }
        });
        _uiLayer->addChild(slider);


        return true;
    }
    return false;
}


// UISliderIssue12249Test

UISliderIssue12249Test::UISliderIssue12249Test()
: _displayValueLabel(nullptr)
{
    
}

UISliderIssue12249Test::~UISliderIssue12249Test()
{
}

bool UISliderIssue12249Test::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the slider alert will be displayed
        _displayValueLabel = TextBMFont::create("Move the slider thumb", "ccb/markerfelt24shadow.fnt");
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Create the slider
        Slider* slider = Slider::create();
        slider->setScale9Enabled(true);
        slider->loadBarTexture("cocosui/sliderTrack.png");
        slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
        slider->loadProgressBarTexture("cocosui/sliderProgress.png");
        slider->setContentSize(Size(300, slider->getContentSize().height * 1.5));
        slider->setMaxPercent(10000);
        slider->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f/* + slider->getSize().height * 2.0f*/));
        slider->addEventListener(CC_CALLBACK_2(UISliderIssue12249Test::sliderEvent, this));
        _uiLayer->addChild(slider);
        
        
        return true;
    }
    return false;
}

void UISliderIssue12249Test::sliderEvent(Ref *pSender, Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider* slider = dynamic_cast<Slider*>(pSender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        _displayValueLabel->setString(StringUtils::format("Percent %f", 10000.0 * percent / maxPercent));
    }
}
