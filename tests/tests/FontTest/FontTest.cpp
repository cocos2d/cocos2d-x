#include "FontTest.h"
#include "../testResource.h"

enum {
	kTagLabel1,
	kTagLabel2,
	kTagLabel3,
	kTagLabel4,
};

static int fontIdx = 0;

static std::string fontList[] =
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    "American Typewriter",
	"Marker Felt",
#endif
	"fonts/A Damn Mess.ttf",
	"fonts/Abberancy.ttf",
	"fonts/Abduction.ttf",
	"fonts/Paint Boy.ttf",
	"fonts/Schwarzwald Regular.ttf",
	"fonts/Scissor Cuts.ttf",
};

static const char* nextAction(void)
{
	fontIdx++;
	fontIdx = fontIdx % (sizeof(fontList) / sizeof(fontList[0]));
	return fontList[fontIdx].c_str();
}

static const char* backAction(void)
{
	fontIdx--;
	if (fontIdx < 0)
	{
		fontIdx += (sizeof(fontList) / sizeof(fontList[0]));
	}

	return fontList[fontIdx].c_str();
}

static const char* restartAction(void)
{
	return fontList[fontIdx].c_str();
}


FontTest::FontTest()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(FontTest::backCallback));
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(FontTest::restartCallback));
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(FontTest::nextCallback));

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);
	menu->setPosition(CCPointZero);
	item1->setPosition(ccp(size.width/2 - 100,30));
	item2->setPosition(ccp(size.width/2, 30));
	item3->setPosition(ccp(size.width/2 + 100,30));
	addChild(menu, 1);
    
    showFont(restartAction());
}

void FontTest::showFont(const char *pFont)
{
	removeChildByTag(kTagLabel1, true);
	removeChildByTag(kTagLabel2, true);
	removeChildByTag(kTagLabel3, true);
	removeChildByTag(kTagLabel4, true);

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF *top = CCLabelTTF::labelWithString(pFont, pFont, 24);
	CCLabelTTF *left = CCLabelTTF::labelWithString("alignment left", CCSizeMake(s.width, 50), CCTextAlignmentLeft, pFont, 32);
	CCLabelTTF *center = CCLabelTTF::labelWithString("alignment center", CCSizeMake(s.width, 50), CCTextAlignmentCenter, pFont, 32);
	CCLabelTTF *right = CCLabelTTF::labelWithString("alignment right", CCSizeMake(s.width, 50), CCTextAlignmentRight, pFont, 32);

	top->setPosition(ccp(s.width/2, 250));
	left->setPosition(ccp(s.width/2, 200));
	center->setPosition(ccp(s.width/2, 150));
	right->setPosition(ccp(s.width/2, 100));

	addChild(left, 0, kTagLabel1);
	addChild(right, 0, kTagLabel2);
	addChild(center, 0, kTagLabel3);
	addChild(top, 0, kTagLabel4);
}

void FontTest::backCallback(CCObject* pSender)
{
	showFont(backAction());
}

void FontTest::nextCallback(CCObject* pSender)
{
	showFont(nextAction());
}

std::string FontTest::title()
{
	return "Font test";
}

void FontTest::restartCallback(CCObject* pSender)
{
	showFont(restartAction());
}

///---------------------------------------
// 
// DirectorTestScene
// 
///---------------------------------------
void FontTestScene::runThisTest()
{
	CCLayer* pLayer = FontTest::node();
	addChild(pLayer);

	CCDirector::sharedDirector()->replaceScene(this);
}
