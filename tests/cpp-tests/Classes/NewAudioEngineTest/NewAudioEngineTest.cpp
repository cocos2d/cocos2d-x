/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "NewAudioEngineTest.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;

namespace {
    
std::function<Layer*()> createFunctions[] =
{
    CL(AudioControlTest),
    CL(PlaySimultaneouslyTest),
    CL(AudioProfileTest),
    CL(InvalidAudioFileTest),
    CL(LargeAudioFileTest)
};

unsigned int TEST_CASE_COUNT = sizeof(createFunctions) / sizeof(createFunctions[0]);

int s_sceneIdx = -1;
Layer* createTest(int index)
{
    auto layer = (createFunctions[index])();;    
    return layer;
}

Layer* nextAction()
{
    s_sceneIdx++;
    s_sceneIdx = s_sceneIdx % TEST_CASE_COUNT;
    
    return createTest(s_sceneIdx);
}

Layer* backAction()
{
    s_sceneIdx--;
    if( s_sceneIdx < 0 )
        s_sceneIdx = TEST_CASE_COUNT -1;
    
    return createTest(s_sceneIdx);
}

Layer* restartAction()
{
    return createTest(s_sceneIdx);
}

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
        : _enabled(true)
        , _onTriggered(nullptr)
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
        
        std::function<void(TextButton*)> _onTriggered;
        
        bool _enabled;
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
                ret->loadBarTexture("cocosui/sliderTrack.png");
                ret->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
                ret->loadProgressBarTexture("cocosui/sliderProgress.png");
                
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

void AudioEngineTestScene::runThisTest()
{
    CCASSERT(AudioEngine::lazyInit(),"Fail to initialize AudioEngine!");
    
    s_sceneIdx = -1;
    auto layer = nextAction();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

void AudioEngineTestDemo::onExit()
{
    AudioEngine::stopAll();
    BaseTest::onExit();
}

void AudioEngineTestDemo::backCallback(Ref* sender)
{
    auto scene = new AudioEngineTestScene();
    auto layer = backAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void AudioEngineTestDemo::nextCallback(Ref* sender)
{
    auto scene = new AudioEngineTestScene();
    auto layer = nextAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void AudioEngineTestDemo::restartCallback(Ref* sender)
{
    auto scene = new AudioEngineTestScene();
    auto layer = restartAction();
    
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

std::string AudioEngineTestDemo::title() const
{
    return "New Audio Engine Test";
}

// AudioControlTest
bool AudioControlTest::init()
{
    auto ret = AudioEngineTestDemo::init();
    _audioID = AudioEngine::INVAILD_AUDIO_ID;
    _loopEnabled = false;
    _volume = 1.0f;
    _duration = AudioEngine::TIME_UNKNOWN;
    _timeRatio = 0.0f;
    _updateTimeSlider = true;
    
    std::string fontFilePath = "fonts/arial.ttf";
    
    auto& layerSize = this->getContentSize();
    
    auto playItem = TextButton::create("play", [&](TextButton* button){
        if (_audioID == AudioEngine::INVAILD_AUDIO_ID) {
            _audioID = AudioEngine::play2d("background.mp3", _loopEnabled, _volume);
            
            if(_audioID != AudioEngine::INVAILD_AUDIO_ID) {
                button->setEnabled(false);
                AudioEngine::setFinishCallback(_audioID, [&](int id, const std::string& filePath){
                    _audioID = AudioEngine::INVAILD_AUDIO_ID;
                    ((TextButton*)_playItem)->setEnabled(true);
                    
                    _timeRatio = 0.0f;
                    ((SliderEx*)_timeSlider)->setRatio(_timeRatio);
                });
            }
        }
    });
    _playItem = playItem;
    playItem->setPosition(layerSize.width * 0.3f,layerSize.height * 0.7f);
    addChild(playItem);
    
    auto stopItem = TextButton::create("stop", [&](TextButton* button){
        if (_audioID != AudioEngine::INVAILD_AUDIO_ID ) {
            AudioEngine::stop(_audioID);
            
            _audioID = AudioEngine::INVAILD_AUDIO_ID;
            ((TextButton*)_playItem)->setEnabled(true);
        }
    });
    stopItem->setPosition(layerSize.width * 0.7f,layerSize.height * 0.7f);
    addChild(stopItem);
    
    auto pauseItem = TextButton::create("pause", [&](TextButton* button){
        if (_audioID != AudioEngine::INVAILD_AUDIO_ID ) {
            AudioEngine::pause(_audioID);
        }
    });
    pauseItem->setPosition(layerSize.width * 0.3f,layerSize.height * 0.6f);
    addChild(pauseItem);
    
    auto resumeItem = TextButton::create("resume", [&](TextButton* button){
        if (_audioID != AudioEngine::INVAILD_AUDIO_ID ) {
            AudioEngine::resume(_audioID);
        }
    });
    resumeItem->setPosition(layerSize.width * 0.7f,layerSize.height * 0.6f);
    addChild(resumeItem);
    
    auto loopItem = TextButton::create("enable-loop", [&](TextButton* button){
        _loopEnabled = !_loopEnabled;
        
        if (_audioID != AudioEngine::INVAILD_AUDIO_ID ) {
            AudioEngine::setLoop(_audioID, _loopEnabled);
        }
        if(_loopEnabled){
            button->setString("disable-loop");
        }
        else {
            button->setString("enable-loop");
        }
    });
    loopItem->setPosition(layerSize.width * 0.3f,layerSize.height * 0.5f);
    addChild(loopItem);
    
    auto uncacheItem = TextButton::create("uncache", [&](TextButton* button){
        AudioEngine::uncache("background.mp3");
        
        _audioID = AudioEngine::INVAILD_AUDIO_ID;
        ((TextButton*)_playItem)->setEnabled(true);
    });
    uncacheItem->setPosition(layerSize.width * 0.7f,layerSize.height * 0.5f);
    addChild(uncacheItem);
    
    auto volumeSlider = SliderEx::create();
    volumeSlider->setPercent(100);
    volumeSlider->setCallBack([&](SliderEx* sender,float ratio,SliderEx::TouchEvent event){
        _volume = ratio;
        if (_audioID != AudioEngine::INVAILD_AUDIO_ID ) {
            AudioEngine::setVolume(_audioID, _volume);
        }
    });
    volumeSlider->setPosition(Vec2(layerSize.width * 0.5f,layerSize.height * 0.35f));
    addChild(volumeSlider);
    
    auto timeSlider = SliderEx::create();
    timeSlider->setCallBack([&](SliderEx* sender,float ratio,SliderEx::TouchEvent event){
        switch(event){
            case SliderEx::TouchEvent::MOVE:
            case SliderEx::TouchEvent::DOWN:
                _updateTimeSlider = false;
                break;
            case SliderEx::TouchEvent::UP:
                if (_audioID != AudioEngine::INVAILD_AUDIO_ID && _duration != AudioEngine::TIME_UNKNOWN) {
                    AudioEngine::setCurrentTime(_audioID,_duration * ratio);
                }
            case SliderEx::TouchEvent::CANCEL:
                _updateTimeSlider = true;
                break;
        }
    });
    timeSlider->setPosition(Vec2(layerSize.width * 0.5f,layerSize.height * 0.25f));
    addChild(timeSlider);
    _timeSlider = timeSlider;
    
    auto& volumeSliderPos = volumeSlider->getPosition();
    auto& sliderSize = volumeSlider->getContentSize();
    auto volumeLabel = Label::createWithTTF("volume:  ", fontFilePath, 20);
    volumeLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    volumeLabel->setPosition(volumeSliderPos.x - sliderSize.width / 2, volumeSliderPos.y);
    addChild(volumeLabel);
    
    auto& timeSliderPos = timeSlider->getPosition();
    auto timeLabel = Label::createWithTTF("time:  ", fontFilePath, 20);
    timeLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    timeLabel->setPosition(timeSliderPos.x - sliderSize.width / 2, timeSliderPos.y);
    addChild(timeLabel);
    
    this->schedule(CC_CALLBACK_1(AudioControlTest::update, this), 0.1f, "update_key");
    
    return ret;
}

void AudioControlTest::update(float dt)
{
    if (_audioID != AudioEngine::INVAILD_AUDIO_ID ) {
        if(_duration == AudioEngine::TIME_UNKNOWN){
            _duration = AudioEngine::getDuration(_audioID);
        }
        if(_duration != AudioEngine::TIME_UNKNOWN){
            auto time = AudioEngine::getCurrentTime(_audioID);
            _timeRatio = time / _duration;
            if(_updateTimeSlider){
                ((SliderEx*)_timeSlider)->setRatio(_timeRatio);
            }
        }
    }
}

AudioControlTest::~AudioControlTest()
{
}

std::string AudioControlTest::title() const
{
    return "audio control test";
}

// PlaySimultaneouslyTest
bool PlaySimultaneouslyTest::init()
{
    auto ret = AudioEngineTestDemo::init();
    
    char text[36];
    int tmp = 81;
    for(int index = 0; index < TEST_COUNT; ++index){
        sprintf(text,"audio/SoundEffectsFX009/FX0%d.mp3",tmp + index);
        _files[index] = text;
    }
    _playingcount = 0;
    
    auto playItem = TextButton::create("play-simultaneously", [&](TextButton* button){
        int audioId;
        _playingcount = 0;
        button->setEnabled(false);
        auto startTime = utils::gettime();
        for(int index = 0; index < TEST_COUNT; ++index){
            audioId = AudioEngine::play2d(_files[index]);
            if(audioId != AudioEngine::INVAILD_AUDIO_ID){
                _playingcount += 1;
                
                AudioEngine::setFinishCallback(audioId, [&](int id, const std::string& filePath){
                    _playingcount -= 1;
                    if(_playingcount <= 0){
                        ((TextButton*)_playItem)->setEnabled(true);
                    }
                });
            }
            else {
                log("%s,%d,Fail to play file:%s",__FILE__,__LINE__ ,_files[index].c_str());
            }
        }
        log("diff time:%lf",utils::gettime() - startTime);
    });
    playItem->setNormalizedPosition(Vec2(0.5f,0.5f));
    this->addChild(playItem);
    _playItem = playItem;
    
    return ret;
}

PlaySimultaneouslyTest::~PlaySimultaneouslyTest()
{
}

std::string PlaySimultaneouslyTest::title() const
{
    return "Simultaneously play multiple audio";
}

// AudioProfileTest
bool AudioProfileTest::init()
{
    auto ret = AudioEngineTestDemo::init();
    
    char text[30];
    _files[0] = "background.mp3";
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    _files[1] = "background.caf";
#else
    _files[1] = "background.ogg";
#endif
    
    std::string fontFilePath = "fonts/arial.ttf";
    _minDelay = 1.0f;
    _time = 0.0f;

    _audioProfile.name = "AudioProfileTest";
    _audioProfile.maxInstances = 3;
    _audioProfile.minDelay = 1.0;
    
    Vec2 pos(0.5f,0.7f);
    for(int index = 0; index < FILE_COUNT; ++index){
        sprintf(text,"play %s",_files[index].c_str());
        
        auto playItem = TextButton::create(text, [&](TextButton* button){
            int index = button->getTag();
            auto id = AudioEngine::play2d(_files[index], false, 1.0f, &_audioProfile);
            if(id != AudioEngine::INVAILD_AUDIO_ID){
                _time = _minDelay;
                _audioCount += 1;
                char show[30];
                sprintf(show,"audio count:%d",_audioCount);
                _showLabel->setString(show);
                
                AudioEngine::setFinishCallback(id, [&](int id, const std::string& filePath){
                    _audioCount -= 1;
                    char show[30];
                    sprintf(show,"audio count:%d",_audioCount);
                    _showLabel->setString(show);
                });
            }
            
        });
        playItem->setTag(index);
        playItem->setNormalizedPosition(pos);
        this->addChild(playItem);
        pos.y -= 0.15f;
        
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto profileInfoLabel = Label::createWithTTF("AudioProfile Info:\n    max instance:3  \n    minimum delay:1.0", fontFilePath, 12);
    profileInfoLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    profileInfoLabel->setPosition(Vec2(origin.x, origin.y + size.height * 0.65f));
    addChild(profileInfoLabel);
    
    _audioCount = 0;
    _showLabel = Label::createWithTTF("audio count:0", fontFilePath, 12);
    _showLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _showLabel->setPosition(Vec2(origin.x, origin.y + size.height * 0.5f));
    addChild(_showLabel);
    
    auto timeSlider = SliderEx::create();
    timeSlider->setEnabled(false);
    timeSlider->setNormalizedPosition(pos);
    addChild(timeSlider);
    _timeSlider = timeSlider;
    
    this->schedule(CC_CALLBACK_1(AudioProfileTest::update, this), 0.05f, "update_key");
    
    return ret;
}

void AudioProfileTest::update(float dt)
{
    if(_time > 0.0f)
    {
        _time -= dt;
        ((SliderEx*)_timeSlider)->setRatio(_time / _minDelay);
    }
}

AudioProfileTest::~AudioProfileTest()
{
}

std::string AudioProfileTest::title() const
{
    return "AudioProfileTest";
}

std::string AudioProfileTest::subtitle() const
{
    return "See the console.";
}

// InvalidAudioFileTest
bool InvalidAudioFileTest::init()
{
    auto ret = AudioEngineTestDemo::init();
    
    auto playItem = TextButton::create("play unsupported media type", [&](TextButton* button){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        AudioEngine::play2d("background.ogg");
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
        AudioEngine::play2d("background.caf"); 
#endif
    });
    playItem->setNormalizedPosition(Vec2(0.5f, 0.6f));
    this->addChild(playItem);
    
    auto playItem2 = TextButton::create("play not-existent file", [&](TextButton* button){
        AudioEngine::play2d("not-existent file.mp3");
    });
    playItem2->setNormalizedPosition(Vec2(0.5f, 0.4f));
    this->addChild(playItem2);
    
    return ret;
}

InvalidAudioFileTest::~InvalidAudioFileTest()
{
}

std::string InvalidAudioFileTest::title() const
{
    return "Test invalid audio file";
}

std::string InvalidAudioFileTest::subtitle() const
{
    return "Not crash,please see the console.";
}

// LargeAudioFileTest
bool LargeAudioFileTest::init()
{
    auto ret = AudioEngineTestDemo::init();
    
    auto playItem = TextButton::create("play large audio file", [&](TextButton* button){
        AudioEngine::play2d("audio/LuckyDay.mp3");
    });
    playItem->setNormalizedPosition(Vec2::ANCHOR_MIDDLE);
    this->addChild(playItem);
    
    return ret;
}

LargeAudioFileTest::~LargeAudioFileTest()
{
}

std::string LargeAudioFileTest::title() const
{
    return "Test large audio file";
}

#endif
