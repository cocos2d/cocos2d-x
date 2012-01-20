#include "CocosDenshionTest.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#define EFFECT_FILE		"effect2.ogg"
#elif( CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	#define EFFECT_FILE		"effect1.raw"
#else
	#define EFFECT_FILE		"effect1.wav"
#endif // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#define MUSIC_FILE		"music.mid"
#else
	#define MUSIC_FILE		"background.mp3"
#endif // CC_PLATFORM_WIN32

using namespace cocos2d;
using namespace CocosDenshion;

#define LINE_SPACE          40

CocosDenshionTest::CocosDenshionTest()
: m_pItmeMenu(NULL),
m_tBeginPos(CCPointZero),
m_nSoundId(0)
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
	m_pItmeMenu = CCMenu::menuWithItems(NULL);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_nTestCount = sizeof(testItems) / sizeof(testItems[0]);

	for (int i = 0; i < m_nTestCount; ++i)
	{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//		CCLabelBMFont* label = CCLabelBMFont::labelWithString(testItems[i].c_str(),  "fonts/arial16.fnt");
//#else
        CCLabelTTF* label = CCLabelTTF::labelWithString(testItems[i].c_str(), "Arial", 24);
//#endif		
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(CocosDenshionTest::menuCallback));
		
		m_pItmeMenu->addChild(pMenuItem, i + 10000);
		pMenuItem->setPosition( CCPointMake( s.width / 2, (s.height - (i + 1) * LINE_SPACE) ));
	}

	m_pItmeMenu->setContentSize(CCSizeMake(s.width, (m_nTestCount + 1) * LINE_SPACE));
	m_pItmeMenu->setPosition(CCPointZero);
	addChild(m_pItmeMenu);

	setIsTouchEnabled(true);

	// preload background music and effect
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( CCFileUtils::fullPathFromRelativePath(MUSIC_FILE) );
	SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::fullPathFromRelativePath(EFFECT_FILE) );
    
    // set default volume
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
}

CocosDenshionTest::~CocosDenshionTest()
{
}

void CocosDenshionTest::onExit()
{
	CCLayer::onExit();

	SimpleAudioEngine::sharedEngine()->end();
}

void CocosDenshionTest::menuCallback(CCObject * pSender)
{
	// get the userdata, it's the index of the menu item clicked
	CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
	int nIdx = pMenuItem->getZOrder() - 10000;

	switch(nIdx)
	{
	// play background music
	case 0:

		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::fullPathFromRelativePath(MUSIC_FILE)).c_str(), true);
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
		m_nSoundId = SimpleAudioEngine::sharedEngine()->playEffect(std::string(CCFileUtils::fullPathFromRelativePath(EFFECT_FILE)).c_str());
		break;
    // play effect
    case 7:
        m_nSoundId = SimpleAudioEngine::sharedEngine()->playEffect(std::string(CCFileUtils::fullPathFromRelativePath(EFFECT_FILE)).c_str(), true);
        break;
    // stop effect
	case 8:
		SimpleAudioEngine::sharedEngine()->stopEffect(m_nSoundId);
		break;
	// unload effect
	case 9:
		SimpleAudioEngine::sharedEngine()->unloadEffect(std::string(CCFileUtils::fullPathFromRelativePath(EFFECT_FILE)).c_str());
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
		SimpleAudioEngine::sharedEngine()->pauseEffect(m_nSoundId);
		break;
	case 15:
		SimpleAudioEngine::sharedEngine()->resumeEffect(m_nSoundId);
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

void CocosDenshionTest::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_tBeginPos = touch->locationInView( touch->view() );	
	m_tBeginPos = CCDirector::sharedDirector()->convertToGL( m_tBeginPos );
}

void CocosDenshionTest::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->locationInView( touch->view() );	
	touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CCPoint curPos  = m_pItmeMenu->getPosition();
	CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (nextPos.y < 0.0f)
	{
		m_pItmeMenu->setPosition(CCPointZero);
		return;
	}

	if (nextPos.y > ((m_nTestCount + 1)* LINE_SPACE - winSize.height))
	{
		m_pItmeMenu->setPosition(ccp(0, ((m_nTestCount + 1)* LINE_SPACE - winSize.height)));
		return;
	}

	m_pItmeMenu->setPosition(nextPos);
	m_tBeginPos = touchLocation;
}

void CocosDenshionTestScene::runThisTest()
{
	CCLayer* pLayer = new CocosDenshionTest();
	addChild(pLayer);
	pLayer->autorelease();

	CCDirector::sharedDirector()->replaceScene(this);
}
