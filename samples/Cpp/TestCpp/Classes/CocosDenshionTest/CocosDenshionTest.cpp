#include "CocosDenshionTest.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/GUI/CCControlExtension/CCControlSlider.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #define EFFECT_FILE        "effect2.ogg"
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    #define EFFECT_FILE        "effect1.raw"
#else
    #define EFFECT_FILE        "effect1.wav"
#endif // CC_PLATFOR_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #define MUSIC_FILE        "music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
    #define MUSIC_FILE        "background.ogg"
#else
    #define MUSIC_FILE        "background.mp3"
#endif // CC_PLATFOR_WIN32

USING_NS_CC;
using namespace CocosDenshion;

#define LINE_SPACE          40

class Button : public Node//, public TargetedTouchDelegate
{
public:
    static Button *createWithSprite(const char *filePath)
    {
        auto b = new Button();
        if (b && !b->initSpriteButton(filePath)) {
            delete b;
            b = NULL;
        }
        return b;
    }

    static Button *createWithText(const char *text)
    {
        auto b = new Button();
        if (b && !b->initTextButton(text)) {
            delete b;
            b = NULL;
        }
        return b;
    }

    ~Button()
    {
//        Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
    }

    void onTriggered(const std::function<void(void)> &onTriggered)
    {
        _onTriggered = onTriggered;
    }

private:
    Button()
        : _child(NULL)
    {
//        Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 100, true);
        
        // Register Touch Event
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
        listener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(Button::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
    }

    bool initSpriteButton(const char *filePath)
    {
        _child = Sprite::create(filePath);
        addChild(_child);
        return true;
    }

    bool initTextButton(const char *text)
    {
        _child = LabelTTF::create(text, "Arial", 16);
        addChild(_child);
        return true;
    }

    bool touchHits(Touch  *touch)
    {
        const Rect area(0, 0, _child->getContentSize().width, _child->getContentSize().height);
        return area.containsPoint(_child->convertToNodeSpace(touch->getLocation()));
    }

    bool onTouchBegan(Touch  *touch, Event  *event)
    {
        CC_UNUSED_PARAM(event);
        const bool hits = touchHits(touch);
        if (hits)
            scaleButtonTo(0.9f);
        return hits;
    }

    void onTouchEnded(Touch  *touch, Event  *event)
    {
        CC_UNUSED_PARAM(event);
        const bool hits = touchHits(touch);
        if (hits && _onTriggered)
            _onTriggered();
        scaleButtonTo(1);
    }

    void onTouchCancelled(Touch  *touch, Event  *event)
    {
        CC_UNUSED_PARAM(event);
        scaleButtonTo(1);
    }

    void scaleButtonTo(float scale)
    {
        auto action = ScaleTo::create(0.1f, scale);
        action->setTag(900);
        stopActionByTag(900);
        runAction(action);
    }

    Node *_child;
    std::function<void(void)> _onTriggered;
};

class AudioSlider : public Node
{
public:
    enum Direction {
        Vertical,
        Horizontal
    };

    static AudioSlider *create(Direction direction)
    {
        auto ret = new AudioSlider(direction);
        if (ret && !ret->init()) {
            delete ret;
            ret = NULL;
        }
        return ret;
    }

    float getValue() const
    {
        return _slider->getValue();
    }

    void setValue(float minValue, float maxValue, float value)
    {
        _slider->setMinimumValue(minValue);
        _slider->setMaximumValue(maxValue);
        _slider->setValue(value);

        char buffer[32];

        sprintf(buffer, "%.2f", minValue);
        if (!_lblMinValue) {
            _lblMinValue = LabelTTF::create(buffer, "Arial", 8);
            addChild(_lblMinValue);
            if (_direction == Vertical)
                _lblMinValue->setPosition(Point(12.0, -50.0));
            else
                _lblMinValue->setPosition(Point(-50, 12.0));
        } else {
            _lblMinValue->setString(buffer);
        }

        sprintf(buffer, "%.2f", maxValue);
        if (!_lblMaxValue) {
            _lblMaxValue = LabelTTF::create(buffer, "Arial", 8);
            addChild(_lblMaxValue);
            if (_direction == Vertical)
                _lblMaxValue->setPosition(Point(12.0, 50.0));
            else
                _lblMaxValue->setPosition(Point(50, 12.0));
        } else {
            _lblMaxValue->setString(buffer);
        }
    }

private:
    AudioSlider(Direction direction)
        : _direction(direction)
        , _slider(NULL)
        , _lblMinValue(NULL)
        , _lblMaxValue(NULL)
    {
    }

    bool init()
    {
        _slider = extension::ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        _slider->setScale(0.5);
        if (_direction == Vertical)
            _slider->setRotation(-90.0);
        addChild(_slider);
        return true;
    }

    Direction _direction;
    extension::ControlSlider *_slider;
    LabelTTF *_lblMinValue;
    LabelTTF *_lblMaxValue;
};

CocosDenshionTest::CocosDenshionTest()
: _soundId(0),
_musicVolume(1),
_effectsVolume(1),
_sliderPitch(NULL),
_sliderPan(NULL),
_sliderGain(NULL),
_sliderEffectsVolume(NULL),
_sliderMusicVolume(NULL)
{
    addButtons();
    addSliders();
    schedule(schedule_selector(CocosDenshionTest::updateVolumes));

    // preload background music and effect
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic( MUSIC_FILE );
    SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_FILE );

    // set default volume
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
}

CocosDenshionTest::~CocosDenshionTest()
{
}

void CocosDenshionTest::onExit()
{
    Layer::onExit();

    SimpleAudioEngine::end();
}

void CocosDenshionTest::addButtons()
{
    auto lblMusic = LabelTTF::create("Control Music", "Arial", 24);
    addChildAt(lblMusic, 0.25f, 0.9f);

    Button *btnPlay = Button::createWithText("play");
    btnPlay->onTriggered([]() {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
    });
    addChildAt(btnPlay, 0.1f, 0.75f);

    Button *btnStop = Button::createWithText("stop");
    btnStop->onTriggered([]() {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    });
    addChildAt(btnStop, 0.25f, 0.75f);

    Button *btnRewindMusic = Button::createWithText("rewind");
    btnRewindMusic->onTriggered([]() {
        SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
    });
    addChildAt(btnRewindMusic, 0.4f, 0.75f);

    Button *btnPause = Button::createWithText("pause");
    btnPause->onTriggered([]() {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    });
    addChildAt(btnPause, 0.1f, 0.65f);

    Button *btnResumeMusic = Button::createWithText("resume");
    btnResumeMusic->onTriggered([]() {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    });
    addChildAt(btnResumeMusic, 0.25f, 0.65f);

    Button *btnIsPlayingMusic = Button::createWithText("is playing");
    btnIsPlayingMusic->onTriggered([]() {
        if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
            CCLOG("background music is playing");
        else
            CCLOG("background music is not playing");
    });
    addChildAt(btnIsPlayingMusic, 0.4f, 0.65f);

    auto lblSound = LabelTTF::create("Control Effects", "Arial", 24);
    addChildAt(lblSound, 0.75f, 0.9f);

    Button *btnPlayEffect = Button::createWithText("play");
    btnPlayEffect->onTriggered([this]() {
        const float pitch = _sliderPitch->getValue();
        const float pan = _sliderPan->getValue();
        const float gain = _sliderGain->getValue();
        _soundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE, false, pitch, pan, gain);
    });
    addChildAt(btnPlayEffect, 0.6f, 0.8f);

    Button *btnPlayEffectInLoop = Button::createWithText("play in loop");
    btnPlayEffectInLoop->onTriggered([this]() {
        const float pitch = _sliderPitch->getValue();
        const float pan = _sliderPan->getValue();
        const float gain = _sliderGain->getValue();
        _soundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE, true, pitch, pan, gain);
    });
    addChildAt(btnPlayEffectInLoop, 0.75f, 0.8f);

    Button *btnStopEffect = Button::createWithText("stop");
    btnStopEffect->onTriggered([this]() {
        SimpleAudioEngine::getInstance()->stopEffect(_soundId);
    });
    addChildAt(btnStopEffect, 0.9f, 0.8f);

    Button *btnUnloadEffect = Button::createWithText("unload");
    btnUnloadEffect->onTriggered([this]() {
        SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_FILE);
    });
    addChildAt(btnUnloadEffect, 0.6f, 0.7f);

    Button *btnPauseEffect = Button::createWithText("pause");
    btnPauseEffect->onTriggered([this]() {
        SimpleAudioEngine::getInstance()->pauseEffect(_soundId);
    });
    addChildAt(btnPauseEffect, 0.75f, 0.7f);

    Button *btnResumeEffect = Button::createWithText("resume");
    btnResumeEffect->onTriggered([this]() {
        SimpleAudioEngine::getInstance()->resumeEffect(_soundId);
    });
    addChildAt(btnResumeEffect, 0.9f, 0.7f);

    Button *btnPauseAll = Button::createWithText("pause all");
    btnPauseAll->onTriggered([this]() {
        SimpleAudioEngine::getInstance()->pauseAllEffects();
    });
    addChildAt(btnPauseAll, 0.6f, 0.6f);

    Button *btnResumeAll = Button::createWithText("resume all");
    btnResumeAll->onTriggered([this]() {
        SimpleAudioEngine::getInstance()->resumeAllEffects();
    });
    addChildAt(btnResumeAll, 0.75f, 0.6f);

    Button *btnStopAll = Button::createWithText("stop all");
    btnStopAll->onTriggered([this]() {
        SimpleAudioEngine::getInstance()->stopAllEffects();
    });
    addChildAt(btnStopAll, 0.9f, 0.6f);
}

void CocosDenshionTest::addSliders()
{
    auto lblPitch = LabelTTF::create("Pitch", "Arial", 14);
    addChildAt(lblPitch, 0.67f, 0.4f);
    _sliderPitch = AudioSlider::create(AudioSlider::Horizontal);
    _sliderPitch->setValue(0.5, 2, 1);
    addChildAt(_sliderPitch, 0.85f, 0.4f);

    auto lblPan = LabelTTF::create("Pan", "Arial", 14);
    addChildAt(lblPan, 0.67f, 0.3f);
    _sliderPan = AudioSlider::create(AudioSlider::Horizontal);
    _sliderPan->setValue(-1, 1, 0);
    addChildAt(_sliderPan, 0.85f, 0.3f);

    auto lblGain = LabelTTF::create("Gain", "Arial", 14);
    addChildAt(lblGain, 0.67f, 0.2f);
    _sliderGain = AudioSlider::create(AudioSlider::Horizontal);
    _sliderGain->setValue(0, 1, 1);
    addChildAt(_sliderGain, 0.85f, 0.2f);

    auto lblEffectsVolume = LabelTTF::create("Effects Volume", "Arial", 14);
    addChildAt(lblEffectsVolume, 0.62f, 0.5f);
    _sliderEffectsVolume = AudioSlider::create(AudioSlider::Horizontal);
    _sliderEffectsVolume->setValue(0, 1, 1);
    addChildAt(_sliderEffectsVolume, 0.85f, 0.5f);

    auto lblMusicVolume = LabelTTF::create("Music Volume", "Arial", 14);
    addChildAt(lblMusicVolume, 0.12f, 0.5f);
    _sliderMusicVolume = AudioSlider::create(AudioSlider::Horizontal);
    _sliderMusicVolume->setValue(0, 1, 1);
    addChildAt(_sliderMusicVolume, 0.35f, 0.5f);
}

void CocosDenshionTest::addChildAt(Node *node, float percentageX, float percentageY)
{
    const Size size = VisibleRect::getVisibleRect().size;
    node->setPosition(Point(percentageX * size.width, percentageY * size.height));
    addChild(node);
}

void CocosDenshionTest::updateVolumes(float)
{
    const float musicVolume = _sliderMusicVolume->getValue();
    if (fabs(musicVolume - _musicVolume) > 0.001) {
        _musicVolume = musicVolume;
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_musicVolume);
    }

    const float effectsVolume = _sliderEffectsVolume->getValue();
    if (fabs(effectsVolume - _effectsVolume) > 0.001) {
        _effectsVolume = effectsVolume;
        SimpleAudioEngine::getInstance()->setEffectsVolume(_effectsVolume);
    }
}

void CocosDenshionTestScene::runThisTest()
{
    auto layer = new CocosDenshionTest();
    addChild(layer);
    layer->autorelease();

    Director::getInstance()->replaceScene(this);
}
