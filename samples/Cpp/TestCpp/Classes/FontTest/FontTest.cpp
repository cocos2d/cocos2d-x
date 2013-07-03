#include "FontTest.h"
#include "../testResource.h"

enum {
    kTagLabel1,
    kTagLabel2,
    kTagLabel3,
    kTagLabel4,
    
    kTagColor1,
    kTagColor2,
    kTagColor3,
};

static int fontIdx = 0;

static std::string fontList[] =
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // custom ttf files are defined in Test-info.plist
    "American Typewriter",
    "Marker Felt",
    "A Damn Mess",
    "Abberancy",
    "Abduction",
    "Paint Boy",
    "Schwarzwald Regular",
    "Scissor Cuts",
#else
    "fonts/A Damn Mess.ttf",
    "fonts/Abberancy.ttf",
    "fonts/Abduction.ttf",
    "fonts/Paint Boy.ttf",
    "fonts/Schwarzwald Regular.ttf",
    "fonts/Scissor Cuts.ttf",
#endif
};

static int fontCount = sizeof(fontList) / sizeof(*fontList);

static int vAlignIdx = 0;
static VerticalTextAlignment verticalAlignment[] =
{
    kVerticalTextAlignmentTop,
    kVerticalTextAlignmentCenter,
    kVerticalTextAlignmentBottom,
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
: BaseTest()
{
    showFont(restartAction());
}

void FontTest::showFont(const char *pFont)
{
    Size s = Director::sharedDirector()->getWinSize();

    Size blockSize = CCSizeMake(s.width/3, 200);
    float fontSize = 26;

    removeChildByTag(kTagLabel1, true);
    removeChildByTag(kTagLabel2, true);
    removeChildByTag(kTagLabel3, true);
    removeChildByTag(kTagLabel4, true);
    removeChildByTag(kTagColor1, true);
    removeChildByTag(kTagColor2, true);
    removeChildByTag(kTagColor3, true);

    LabelTTF *top = LabelTTF::create(pFont, pFont, 24);
    LabelTTF *left = LabelTTF::create("alignment left", pFont, fontSize,
                                          blockSize, kTextAlignmentLeft, verticalAlignment[vAlignIdx]);
    LabelTTF *center = LabelTTF::create("alignment center", pFont, fontSize,
                                            blockSize, kTextAlignmentCenter, verticalAlignment[vAlignIdx]);
    LabelTTF *right = LabelTTF::create("alignment right", pFont, fontSize,
                                           blockSize, kTextAlignmentRight, verticalAlignment[vAlignIdx]);

    LayerColor *leftColor = LayerColor::create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height);
    LayerColor *centerColor = LayerColor::create(ccc4(200, 100, 100, 255), blockSize.width, blockSize.height);
    LayerColor *rightColor = LayerColor::create(ccc4(100, 100, 200, 255), blockSize.width, blockSize.height);

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

    this->addChild(leftColor, -1, kTagColor1);
    this->addChild(left, 0, kTagLabel1);
    this->addChild(rightColor, -1, kTagColor2);
    this->addChild(right, 0, kTagLabel2);
    this->addChild(centerColor, -1, kTagColor3);
    this->addChild(center, 0, kTagLabel3);
    this->addChild(top, 0, kTagLabel4);
}

void FontTest::backCallback(Object* pSender)
{
    showFont(backAction());
}

void FontTest::nextCallback(Object* pSender)
{
    showFont(nextAction());
}

std::string FontTest::title()
{
    return "Font test";
}

void FontTest::restartCallback(Object* pSender)
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
    Layer* pLayer = FontTest::create();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
}
