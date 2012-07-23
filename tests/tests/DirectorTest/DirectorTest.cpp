#include "DirectorTest.h"
#include "../testResource.h"

#define MAX_LAYER	1

CCLayer* nextDirectorTestCase();
CCLayer* backDirectorTestCase();
CCLayer* restartDirectorTestCase();

static int sceneIdx=-1;
static ccDeviceOrientation s_currentOrientation = CCDeviceOrientationPortrait;

CCLayer* createTestCaseLayer(int index)
{
    switch (index)
    {
    case 0:
        {
            Director1* pRet = new Director1();
            pRet->init();
            pRet->autorelease();
            return pRet;
        }
    default:
        return NULL;
    }
}

CCLayer* nextDirectorTestCase()
{	
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	return createTestCaseLayer(sceneIdx);
}

CCLayer* backDirectorTestCase()
{
	sceneIdx--;
	if( sceneIdx < 0 )
		sceneIdx += MAX_LAYER;

    return createTestCaseLayer(sceneIdx);
}

CCLayer* restartDirectorTestCase()
{
    return createTestCaseLayer(sceneIdx);
}

///---------------------------------------
// 
// DirectorTest
// 
///---------------------------------------
bool DirectorTest::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
        CCSize s = CCDirector::sharedDirector()->getWinSize();

        CCLabelTTF *label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 26);
        addChild(label, 1);
        label->setPosition(ccp(s.width/2, s.height-50));

        std::string sSubtitle = subtitle();
        if (sSubtitle.length())
        {
            CCLabelTTF *l = CCLabelTTF::labelWithString(sSubtitle.c_str(), "Thonburi", 16);
            addChild(l, 1);
            l->setPosition(ccp(s.width/2, s.height-80));
        }

        CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(DirectorTest::backCallback));
        CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(DirectorTest::restartCallback));
        CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(DirectorTest::nextCallback));

        CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);
        menu->setPosition(CCPointZero);
        item1->setPosition(ccp( s.width/2 - 100,30));
        item2->setPosition(ccp( s.width/2, 30));
        item3->setPosition(ccp( s.width/2 + 100,30));

        bRet = true;
    } while (0);

    return bRet;
}

void DirectorTest::restartCallback(CCObject* pSender)
{
    CCScene *s = new DirectorTestScene();
	s->addChild(restartDirectorTestCase());
    CCDirector::sharedDirector()->replaceScene(s);
    s->autorelease();
}

void DirectorTest::nextCallback(CCObject* pSender)
{
    CCScene *s = new DirectorTestScene();
    s->addChild(nextDirectorTestCase());
    CCDirector::sharedDirector()->replaceScene(s);
    s->autorelease();
}

void DirectorTest::backCallback(CCObject* pSender)
{
    CCScene *s = new DirectorTestScene();
    s->addChild(backDirectorTestCase());
    CCDirector::sharedDirector()->replaceScene(s);
    s->autorelease();
}

std::string DirectorTest::title()
{
	return "No title";
}

std::string DirectorTest::subtitle()
{
	return "";
}

///---------------------------------------
// 
// Director1
// 
///---------------------------------------
bool Director1::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(! DirectorTest::init());

		setIsTouchEnabled(true);
        CCSize s = CCDirector::sharedDirector()->getWinSize();

        CCMenuItem *item = CCMenuItemFont::itemFromString("Rotate Device", this, menu_selector(Director1::rotateDevice));
        CCMenu *menu = CCMenu::menuWithItems(item, NULL);
		menu->setPosition(ccp( s.width/2, s.height/2));
		addChild(menu);

        bRet = true;
	} while (0);

	return bRet;
}

void Director1::newOrientation()
{
	switch (s_currentOrientation)
    {
		case CCDeviceOrientationLandscapeLeft:
			s_currentOrientation = CCDeviceOrientationPortrait;
			break;
		case CCDeviceOrientationPortrait:
			s_currentOrientation = CCDeviceOrientationLandscapeRight;
			break;						
		case CCDeviceOrientationLandscapeRight:
			s_currentOrientation = CCDeviceOrientationPortraitUpsideDown;
			break;
		case CCDeviceOrientationPortraitUpsideDown:
			s_currentOrientation = CCDeviceOrientationLandscapeLeft;
			break;
	}
    CCDirector::sharedDirector()->setDeviceOrientation(s_currentOrientation);
}

void Director1::rotateDevice(CCObject* pSender)
{
	newOrientation();
    restartCallback(NULL);
}

void Director1::ccTouchesEnded(CCSet * touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;
		CCPoint a = touch->locationInView();

        CCDirector *director = CCDirector::sharedDirector();
		CCPoint b = director->convertToUI(director->convertToGL(a));
		CCLog("(%d,%d) == (%d,%d)", (int) a.x, (int)a.y, (int)b.x, (int)b.y );
	}
}

std::string Director1::title()
{
	return "Testing conversion";
}

std::string Director1::subtitle()
{
	return "Tap screen and see the debug console";
}

///---------------------------------------
// 
// DirectorTestScene
// 
///---------------------------------------
void DirectorTestScene::runThisTest()
{
    s_currentOrientation = CCDeviceOrientationPortrait;
    CCLayer* pLayer = nextDirectorTestCase();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}

void DirectorTestScene::MainMenuCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationPortrait);
    TestScene::MainMenuCallback(pSender);
}
