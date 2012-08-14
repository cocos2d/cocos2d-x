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

static int fontCount = sizeof(fontList) / sizeof(*fontList);

static int vAlignIdx = 0;
static CCVerticalTextAlignment verticalAlignment[] =
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
};
static int vAlignCount = sizeof(verticalAlignment) / sizeof(*verticalAlignment);

static const char* nextAction(void)
{
    fontIdx++;
    if(fontIdx >= fontCount) {
        fontIdx = 0;
        vAlignIdx = (vAlignIdx + 1) % vAlignCount;
    }
    return fontList[fontIdx].c_str();
}

static const char* backAction(void)
{
    fontIdx--;
    if( fontIdx < 0 ) {
        fontIdx = fontCount - 1;
        vAlignIdx--;
        if(vAlignIdx < 0)
            vAlignIdx = vAlignCount - 1;
    }

    return fontList[fontIdx].c_str();
}

static const char* restartAction(void)
{
    return fontList[fontIdx].c_str();
}


FontTest::FontTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(FontTest::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(FontTest::restartCallback));
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(FontTest::nextCallback));

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);
    menu->setPosition(CCPointZero);
    item1->setPosition(ccp( s.width/2 - item2->getContentSize().width*2, item2->getContentSize().height/2));
    item2->setPosition(ccp( s.width/2, item2->getContentSize().height/2));
    item3->setPosition(ccp( s.width/2 + item2->getContentSize().width*2, item2->getContentSize().height/2));
    addChild(menu, 1);
    
    showFont(restartAction());
}

void FontTest::showFont(const char *pFont)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSize blockSize = CCSizeMake(s.width/3, 200);
    float fontSize = 26;

    removeChildByTag(kTagLabel1, true);
    removeChildByTag(kTagLabel2, true);
    removeChildByTag(kTagLabel3, true);
    removeChildByTag(kTagLabel4, true);

    CCLabelTTF *top = CCLabelTTF::create(pFont, pFont, 24);
    CCLabelTTF *left = CCLabelTTF::create("alignment left", pFont, fontSize,
                                          blockSize, kCCTextAlignmentLeft, verticalAlignment[vAlignIdx]);
    CCLabelTTF *center = CCLabelTTF::create("alignment center", pFont, fontSize,
                                            blockSize, kCCTextAlignmentCenter, verticalAlignment[vAlignIdx]);
    CCLabelTTF *right = CCLabelTTF::create("alignment right", pFont, fontSize,
                                           blockSize, kCCTextAlignmentRight, verticalAlignment[vAlignIdx]);

    CCLayerColor *leftColor = CCLayerColor::create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height);
    CCLayerColor *centerColor = CCLayerColor::create(ccc4(200, 100, 100, 255), blockSize.width, blockSize.height);
    CCLayerColor *rightColor = CCLayerColor::create(ccc4(100, 100, 200, 255), blockSize.width, blockSize.height);

    leftColor->ignoreAnchorPointForPosition(false);
    centerColor->ignoreAnchorPointForPosition(false);
    rightColor->ignoreAnchorPointForPosition(false);


    top->setAnchorPoint(ccp(0.5, 1));
    left->setAnchorPoint(ccp(0,0.5));
    leftColor->setAnchorPoint(ccp(0,0.5));
    center->setAnchorPoint(ccp(0,0.5));
    centerColor->setAnchorPoint(ccp(0,0.5));
    right->setAnchorPoint(ccp(0,0.5));
    rightColor->setAnchorPoint(ccp(0,0.5));

    top->setPosition(ccp(s.width/2,s.height-20));
    left->setPosition(ccp(0,s.height/2));
    leftColor->setPosition(left->getPosition());
    center->setPosition(ccp(blockSize.width, s.height/2));
    centerColor->setPosition(center->getPosition());
    right->setPosition(ccp(blockSize.width*2, s.height/2));
    rightColor->setPosition(right->getPosition());

    this->addChild(leftColor, -1);
    this->addChild(left, 0, kTagLabel1);
    this->addChild(rightColor, -1);
    this->addChild(right, 0, kTagLabel2);
    this->addChild(centerColor, -1);
    this->addChild(center, 0, kTagLabel3);
    this->addChild(top, 0, kTagLabel4);
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
    CCLayer* pLayer = FontTest::create();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
