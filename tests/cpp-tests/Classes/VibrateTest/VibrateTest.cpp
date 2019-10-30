/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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

#include "platform/CCPlatformConfig.h"

#include "VibrateTest.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

VibrateTests::VibrateTests()
{
    ADD_TEST_CASE(VibrateControlTest);
}

namespace {
    class TextButton : public cocos2d::Label
    {
    public:
        
        static TextButton *create(const std::string& text, const std::function<void(TextButton*)> &onTriggered)
        {
            auto ret = new (std::nothrow) TextButton();
            
            TTFConfig ttfconfig("fonts/arial.ttf",25);
            if (ret && ret->setTTFConfig(ttfconfig)) {
                ret->setString(text);
                ret->_onTriggered = onTriggered;
                
                ret->autorelease();
                
                return ret;
            }
            
            delete ret;
            return nullptr;
        }
        
        void setEnabled(bool enabled)
        {
            _enabled = enabled;
            if(_enabled){
                this->setColor(Color3B::WHITE);
            }
            else {
                this->setColor(Color3B::GRAY);
            }
        }
        
    private:
        TextButton()
        {
            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            
            listener->onTouchBegan = CC_CALLBACK_2(TextButton::onTouchBegan, this);
            listener->onTouchEnded = CC_CALLBACK_2(TextButton::onTouchEnded, this);
            listener->onTouchCancelled = CC_CALLBACK_2(TextButton::onTouchCancelled, this);
            
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);            
        }
        
        bool touchHits(Touch  *touch)
        {
            auto hitPos = this->convertToNodeSpace(touch->getLocation());
            if (hitPos.x >= 0 && hitPos.y >= 0 && hitPos.x <= _contentSize.width && hitPos.y <= _contentSize.height) {
                return true;
            }
            return false;
        }
        
        bool onTouchBegan(Touch  *touch, Event  *event)
        {
            auto hits = touchHits(touch);
            if (hits){
                scaleButtonTo(0.95f);
            }
            return hits;
        }
        
        void onTouchEnded(Touch  *touch, Event  *event)
        {
            if(_enabled) {
                auto hits = touchHits(touch);
                if (hits && _onTriggered){
                    _onTriggered(this);
                }
            }
            
            scaleButtonTo(1);
        }
        
        void onTouchCancelled(Touch  *touch, Event  *event)
        {
            scaleButtonTo(1);
        }
        
        void scaleButtonTo(float scale)
        {
            auto action = ScaleTo::create(0.05f, scale);
            action->setTag(10000);
            stopActionByTag(10000);
            runAction(action);
        }
        
        std::function<void(TextButton*)> _onTriggered = nullptr;
        
        bool _enabled = true;
    };
    
    class SliderEx : public Slider
    {
    public:
        enum class TouchEvent
        {
            DOWN,
            MOVE,
            UP,
            CANCEL
        };
        typedef std::function<void(SliderEx*,float,TouchEvent)> ccSliderExCallback;
        
        static SliderEx* create(){
            auto ret = new (std::nothrow) SliderEx();
            if (ret && ret->init())
            {
                ret->_callback = nullptr;
                ret->loadBarTexture("ccs-res/cocosui/sliderTrack.png");
                ret->loadSlidBallTextures("ccs-res/cocosui/sliderThumb.png", "ccs-res/cocosui/sliderThumb.png", "");
                ret->loadProgressBarTexture("ccs-res/cocosui/sliderProgress.png");
                
                ret->autorelease();
                
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return ret;
        }
        
        void setCallBack(const ccSliderExCallback& callback){
            _callback = callback;
        }
        
        void setRatio(float ratio) {
            if (ratio > 1.0f){
                ratio = 1.0f;
            }
            else if (ratio < 0.0f){
                ratio = 0.0f;
            }
            
            _ratio = ratio;
            _percent = 100 * _ratio;
            
            float dis = _barLength * _ratio;
            _slidBallRenderer->setPosition(Vec2(dis, _contentSize.height / 2.0f));
            if (_scale9Enabled){
                _progressBarRenderer->setPreferredSize(Size(dis,_progressBarTextureSize.height));
            }
            else
            {
                auto spriteRenderer = _progressBarRenderer->getSprite();
                
                if (nullptr != spriteRenderer) {
                    Rect rect = spriteRenderer->getTextureRect();
                    rect.size.width = _progressBarTextureSize.width * _ratio;
                    spriteRenderer->setTextureRect(rect, spriteRenderer->isTextureRectRotated(), rect.size);
                }
            }
        }
        
        virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override{
            auto ret = Slider::onTouchBegan(touch, unusedEvent);
            if(ret && _callback){
                _touchEvent = TouchEvent::DOWN;
                Vec2 nsp = convertToNodeSpace(_touchBeganPosition);
                _ratio = nsp.x / _barLength;
                if(_ratio < 0.0f)
                    _ratio = 0.0f;
                else if(_ratio > 1.0f)
                    _ratio = 1.0f;
                _callback(this,_ratio,_touchEvent);
            }
            return ret;
        }
        
        virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override{
            _touchEvent = TouchEvent::MOVE;
            Slider::onTouchMoved(touch, unusedEvent);
            Vec2 nsp = convertToNodeSpace(_touchMovePosition);
            _ratio = nsp.x / _barLength;
            if(_ratio < 0.0f)
                _ratio = 0.0f;
            else if(_ratio > 1.0f)
                _ratio = 1.0f;
            if(_callback){
                _callback(this,_ratio,_touchEvent);
            }
        }
        
        virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override{
            _touchEvent = TouchEvent::UP;
            Slider::onTouchEnded(touch, unusedEvent);
            Vec2 nsp = convertToNodeSpace(_touchEndPosition);
            _ratio = nsp.x / _barLength;
            if(_ratio < 0.0f)
                _ratio = 0.0f;
            else if(_ratio > 1.0f)
                _ratio = 1.0f;
            if(_callback){
                _callback(this,_ratio,_touchEvent);
            }
        }
        
        virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override{
            _touchEvent = TouchEvent::CANCEL;
            Slider::onTouchCancelled(touch, unusedEvent);
            
            if(_callback){
                _callback(this,_ratio,_touchEvent);
            }
        }
        
    private:
        TouchEvent _touchEvent;
        float _ratio;
        ccSliderExCallback _callback;
    };
}

void VibrateTestDemo::onExit()
{
    TestCase::onExit();
}

std::string VibrateTestDemo::title() const
{
    return "Vibrate Test";
}

// VibrateControlTest
bool VibrateControlTest::init()
{
    auto ret = VibrateTestDemo::init();
    _duration = 0.1f;
    
    std::string fontFilePath = "fonts/arial.ttf";
    
    auto& layerSize = this->getContentSize();

    auto vibrateItem = TextButton::create("vibrate", [&](TextButton* button){
        Device::vibrate(_duration);
    });
    vibrateItem->setPosition(layerSize.width * 0.5f, layerSize.height * 0.7f);
    addChild(vibrateItem);
    
    auto durationLabelValue = StringUtils::format("duration: %.3fs", _duration);

    auto durationLabel = Label::createWithTTF(durationLabelValue, fontFilePath, 20);
    durationLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    durationLabel->setPosition(layerSize.width * 0.5f, layerSize.height * 0.5f);
    addChild(durationLabel);
    _durationLabel = durationLabel;

    auto durationSlider = SliderEx::create();
    durationSlider->setPercent(0);
    durationSlider->setCallBack([&](SliderEx* sender, float ratio, SliderEx::TouchEvent event){
        _duration = ratio * 1.9f + 0.1f; // From 0.1s to 2s
        auto durationLabelValue = StringUtils::format("duration: %.3fs", _duration);
        (static_cast<Label*>(_durationLabel))->setString(durationLabelValue);
    });
    durationSlider->setPosition(Vec2(layerSize.width * 0.5f, layerSize.height * 0.35f));
    addChild(durationSlider);
    _durationSlider = durationSlider;
        
    return ret;
}

VibrateControlTest::~VibrateControlTest()
{
}

std::string VibrateControlTest::title() const
{
    return "vibrate control test";
}
