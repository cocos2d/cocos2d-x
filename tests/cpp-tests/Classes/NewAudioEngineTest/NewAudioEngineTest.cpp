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
#include "NewAudioEngineTest.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;

AudioEngineTests::AudioEngineTests()
{
    ADD_TEST_CASE(AudioIssue11143Test);
    ADD_TEST_CASE(AudioControlTest);
    ADD_TEST_CASE(AudioLoadTest);
    ADD_TEST_CASE(PlaySimultaneouslyTest);
    ADD_TEST_CASE(AudioProfileTest);
    ADD_TEST_CASE(InvalidAudioFileTest);
    ADD_TEST_CASE(LargeAudioFileTest);
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
        : _onTriggered(nullptr)
        , _enabled(true)
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
        static SliderEx* create(){
            auto ret = new (std::nothrow) SliderEx();
            if (ret && ret->init())
            {
                ret->loadBarTexture("cocosui/sliderTrack.png");
                ret->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
                ret->loadProgressBarTexture("cocosui/sliderProgress.png");
                ret->setTouchEnabled(true);
                
                ret->autorelease();
                
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return ret;
        }
        
        void setRatio(float ratio) {
            ratio = clampf(ratio, 0.0f, 1.0f);
            
            _ratio = ratio;
            setPercent(100 * _ratio);
        }
        
        float getRatio () {
            _ratio = 1.0f * _percent / _maxPercent;
            return _ratio;
        }
        
    private:
        float _ratio;
    };
}

void AudioEngineTestDemo::onExit()
{
    AudioEngine::stopAll();
    TestCase::onExit();
}

std::string AudioEngineTestDemo::title() const
{
    return "New Audio Engine Test";
}

// AudioControlTest
bool AudioControlTest::init()
{
    auto ret = AudioEngineTestDemo::init();
    _audioID = AudioEngine::INVALID_AUDIO_ID;
    _loopEnabled = false;
    _volume = 1.0f;
    _duration = AudioEngine::TIME_UNKNOWN;
    _timeRatio = 0.0f;
    _updateTimeSlider = true;
    
    std::string fontFilePath = "fonts/arial.ttf";
    
    auto& layerSize = this->getContentSize();
    
    auto playItem = TextButton::create("play", [&](TextButton* button){
        if (_audioID == AudioEngine::INVALID_AUDIO_ID) {
            _audioID = AudioEngine::play2d("background.mp3", _loopEnabled, _volume);
            
            if(_audioID != AudioEngine::INVALID_AUDIO_ID) {
                button->setEnabled(false);
                AudioEngine::setFinishCallback(_audioID, [&](int id, const std::string& filePath){
                    _audioID = AudioEngine::INVALID_AUDIO_ID;
                    ((TextButton*)_playItem)->setEnabled(true);
                    
                    _timeRatio = 0.0f;
                    ((SliderEx*)_timeSlider)->setRatio(_timeRatio);
                });
            }
        }
    });
    _playItem = playItem;
    playItem->setPosition(layerSize.width * 0.3f,layerSize.height * 0.8f);
    addChild(playItem);
    
    auto stopItem = TextButton::create("stop", [&](TextButton* button){
        if (_audioID != AudioEngine::INVALID_AUDIO_ID ) {
            AudioEngine::stop(_audioID);
            
            _audioID = AudioEngine::INVALID_AUDIO_ID;
            ((TextButton*)_playItem)->setEnabled(true);
        }
    });
    stopItem->setPosition(layerSize.width * 0.7f,layerSize.height * 0.8f);
    addChild(stopItem);
    
    auto pauseItem = TextButton::create("pause", [&](TextButton* button){
        if (_audioID != AudioEngine::INVALID_AUDIO_ID ) {
            AudioEngine::pause(_audioID);
        }
    });
    pauseItem->setPosition(layerSize.width * 0.3f,layerSize.height * 0.7f);
    addChild(pauseItem);
    
    auto resumeItem = TextButton::create("resume", [&](TextButton* button){
        if (_audioID != AudioEngine::INVALID_AUDIO_ID ) {
            AudioEngine::resume(_audioID);
        }
    });
    resumeItem->setPosition(layerSize.width * 0.7f,layerSize.height * 0.7f);
    addChild(resumeItem);
    
    auto loopItem = TextButton::create("enable-loop", [&](TextButton* button){
        _loopEnabled = !_loopEnabled;

        if (_audioID != AudioEngine::INVALID_AUDIO_ID) {
            AudioEngine::setLoop(_audioID, _loopEnabled);
        }
        if (_loopEnabled){
            button->setString("disable-loop");
        }
        else {
            button->setString("enable-loop");
        }
    });
    loopItem->setPosition(layerSize.width * 0.5f, layerSize.height * 0.5f);
    addChild(loopItem);
    
    auto volumeSlider = SliderEx::create();
    volumeSlider->setPercent(100);
    volumeSlider->addEventListener([&](Ref* sender, Slider::EventType event){
        SliderEx *slider = dynamic_cast<SliderEx *>(sender);
        _volume = slider->getRatio();
        if (_audioID != AudioEngine::INVALID_AUDIO_ID ) {
            AudioEngine::setVolume(_audioID, _volume);
        }
    });
    volumeSlider->setPosition(Vec2(layerSize.width * 0.5f,layerSize.height * 0.35f));
    addChild(volumeSlider);
    
    auto timeSlider = SliderEx::create();
    timeSlider->addEventListener([&](Ref* sender, Slider::EventType event){
        SliderEx *slider = dynamic_cast<SliderEx *>(sender);
        switch(event){
            case Slider::EventType::ON_PERCENTAGE_CHANGED:
            case Slider::EventType::ON_SLIDEBALL_DOWN:
                _updateTimeSlider = false;
                break;
            case Slider::EventType::ON_SLIDEBALL_UP:
                if (_audioID != AudioEngine::INVALID_AUDIO_ID && _duration != AudioEngine::TIME_UNKNOWN) {
                    float ratio = (float)slider->getPercent() / 100;
                    ratio = clampf(ratio, 0.0f, 1.0f);
                    AudioEngine::setCurrentTime(_audioID, _duration * ratio);
                }
            case Slider::EventType::ON_SLIDEBALL_CANCEL:
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
    if (_audioID != AudioEngine::INVALID_AUDIO_ID ) {
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
    return "Audio control test";
}

bool AudioLoadTest::init()
{
    if (AudioEngineTestDemo::init())
    {
        auto& layerSize = this->getContentSize();

        auto stateLabel = Label::createWithTTF("status:", "fonts/arial.ttf", 30);
        stateLabel->setPosition(layerSize.width / 2, layerSize.height * 0.7f);
        addChild(stateLabel);

        auto preloadItem = TextButton::create("preload", [&, stateLabel](TextButton* button){
            stateLabel->setString("status:loading...");
            AudioEngine::preload("audio/SoundEffectsFX009/FX082.mp3", [stateLabel](bool isSuccess){
                if (isSuccess)
                {
                    stateLabel->setString("status:load success");
                }
                else
                {
                    stateLabel->setString("status:load fail");
                }
            });
        });
        preloadItem->setPosition(layerSize.width * 0.35f, layerSize.height * 0.5f);
        addChild(preloadItem);

        auto uncacheItem = TextButton::create("uncache", [&, stateLabel](TextButton* button){
            stateLabel->setString("status:uncache");
            AudioEngine::uncache("audio/SoundEffectsFX009/FX082.mp3");
        });
        uncacheItem->setPosition(layerSize.width * 0.65f, layerSize.height * 0.5f);
        addChild(uncacheItem);
        
        return true;
    }

    return false;
}

std::string AudioLoadTest::title() const
{
    return "Audio preload/uncache test";
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
            if(audioId != AudioEngine::INVALID_AUDIO_ID){
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
            if(id != AudioEngine::INVALID_AUDIO_ID){
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

bool AudioIssue11143Test::init()
{
    if (AudioEngineTestDemo::init())
    {
        auto& layerSize = this->getContentSize();

        auto playItem = TextButton::create("play", [](TextButton* button){
            auto audioId = AudioEngine::play2d("audio/SoundEffectsFX009/FX082.mp3", true);
            button->scheduleOnce([audioId](float dt){
                AudioEngine::stop(audioId);
                AudioEngine::play2d("audio/SoundEffectsFX009/FX083.mp3");
            }, 2.f, "play another sound");
        });
        playItem->setPosition(layerSize.width * 0.5f, layerSize.height * 0.5f);
        addChild(playItem);

        return true;
    }

    return false;
}

std::string AudioIssue11143Test::title() const
{
    return "Test for issue 11143";
}

std::string AudioIssue11143Test::subtitle() const
{
    return "2 seconds after first sound play,you should hear another sound.";
}

