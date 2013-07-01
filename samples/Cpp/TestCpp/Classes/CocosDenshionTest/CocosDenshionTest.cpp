#include "CocosDenshionTest.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #define EFFECT_FILE        "effect2.ogg"
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    #define EFFECT_FILE        "effect1.raw"
#else
    #define EFFECT_FILE        "effect1.wav"
#endif // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #define MUSIC_FILE        "music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
    #define MUSIC_FILE        "background.ogg"
#else
    #define MUSIC_FILE        "background.mp3"
#endif // CC_PLATFORM_WIN32

USING_NS_CC;
using namespace CocosDenshion;

#define LINE_SPACE          40

CocosDenshionTest::CocosDenshionTest()
: _itmeMenu(NULL),
_beginPos(PointZero),
_soundId(0)
{
    std::string testItems[] = {
        "play background music",
        "stop background music",
        "pause background music",
        "resume background music",
        "rewind background music",
        "is background music playing",
        "play effect",
        "play effect repeatly",
        "stop effect",
        "unload effect",
        "add background music volume",
        "sub background music volume",
        "add effects volume",
        "sub effects volume",
        "pause effect",
        "resume effect",
        "pause all effects",
        "resume all effects",
        "stop all effects"
    };

    // add menu items for tests
    _itmeMenu = Menu::create();

    _testCount = sizeof(testItems) / sizeof(testItems[0]);

    for (int i = 0; i < _testCount; ++i)
    {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//        LabelBMFont* label = LabelBMFont::create(testItems[i].c_str(),  "fonts/arial16.fnt");
//#else
        LabelTTF* label = LabelTTF::create(testItems[i].c_str(), "Arial", 24);
//#endif        
        MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CocosDenshionTest::menuCallback, this));
        
        _itmeMenu->addChild(pMenuItem, i + 10000);
        pMenuItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ));
    }

    _itmeMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (_testCount + 1) * LINE_SPACE));
    _itmeMenu->setPosition(PointZero);
    addChild(_itmeMenu);

    setTouchEnabled(true);

    // preload background music and effect
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( MUSIC_FILE );
    SimpleAudioEngine::sharedEngine()->preloadEffect( EFFECT_FILE );
    
    // set default volume
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
}

CocosDenshionTest::~CocosDenshionTest()
{
}

void CocosDenshionTest::onExit()
{
    Layer::onExit();

    SimpleAudioEngine::sharedEngine()->end();
}

void CocosDenshionTest::menuCallback(Object * pSender)
{
    // get the userdata, it's the index of the menu item clicked
    MenuItem* pMenuItem = (MenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 10000;

    switch(nIdx)
    {
    // play background music
    case 0:

        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE, true);
        break;
    // stop background music
    case 1:
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        break;
    // pause background music
    case 2:
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        break;
    // resume background music
    case 3:
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        break;
    // rewind background music
    case 4:
        SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
        break;
    // is background music playing
    case 5:
        if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        {
            CCLOG("background music is playing");
        }
        else
        {
            CCLOG("background music is not playing");
        }
        break;
    // play effect
    case 6:
        _soundId = SimpleAudioEngine::sharedEngine()->playEffect(EFFECT_FILE);
        break;
    // play effect
    case 7:
        _soundId = SimpleAudioEngine::sharedEngine()->playEffect(EFFECT_FILE, true);
        break;
    // stop effect
    case 8:
        SimpleAudioEngine::sharedEngine()->stopEffect(_soundId);
        break;
    // unload effect
    case 9:
        SimpleAudioEngine::sharedEngine()->unloadEffect(EFFECT_FILE);
        break;
        // add bakcground music volume
    case 10:
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + 0.1f);
        break;
        // sub backgroud music volume
    case 11:
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() - 0.1f);
        break;
        // add effects volume
    case 12:
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() + 0.1f);
        break;
        // sub effects volume
    case 13:
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() - 0.1f);
        break;
    case 14:
        SimpleAudioEngine::sharedEngine()->pauseEffect(_soundId);
        break;
    case 15:
        SimpleAudioEngine::sharedEngine()->resumeEffect(_soundId);
        break;
    case 16:
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        break;
    case 17:
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
        break;
    case 18:
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
        break;
    }
    
}

void CocosDenshionTest::ccTouchesBegan(Set *pTouches, Event *pEvent)
{
    Touch* touch = (Touch*)pTouches->anyObject();

    _beginPos = touch->getLocation();    
}

void CocosDenshionTest::ccTouchesMoved(Set *pTouches, Event *pEvent)
{
    Touch* touch = (Touch*)pTouches->anyObject();

    Point touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;

    Point curPos  = _itmeMenu->getPosition();
    Point nextPos = ccp(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        _itmeMenu->setPosition(PointZero);
        return;
    }

    if (nextPos.y > ((_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itmeMenu->setPosition(ccp(0, ((_testCount + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }

    _itmeMenu->setPosition(nextPos);
    _beginPos = touchLocation;
}

void CocosDenshionTestScene::runThisTest()
{
    Layer* pLayer = new CocosDenshionTest();
    addChild(pLayer);
    pLayer->autorelease();

    Director::sharedDirector()->replaceScene(this);
}
