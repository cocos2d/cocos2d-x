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
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
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
static TextVAlignment verticalAlignment[] =
{
    TextVAlignment::TOP,
    TextVAlignment::CENTER,
    TextVAlignment::BOTTOM,
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
    auto s = Director::getInstance()->getWinSize();

    auto blockSize = Size(s.width/3, 200);
    float fontSize = 26;

    removeChildByTag(kTagLabel1, true);
    removeChildByTag(kTagLabel2, true);
    removeChildByTag(kTagLabel3, true);
    removeChildByTag(kTagLabel4, true);
    removeChildByTag(kTagColor1, true);
    removeChildByTag(kTagColor2, true);
    removeChildByTag(kTagColor3, true);

    auto top = LabelTTF::create(pFont, pFont, 24);
    auto left = LabelTTF::create("alignment left", pFont, fontSize,
                                          blockSize, TextHAlignment::LEFT, verticalAlignment[vAlignIdx]);
    auto center = LabelTTF::create("alignment center", pFont, fontSize,
                                            blockSize, TextHAlignment::CENTER, verticalAlignment[vAlignIdx]);
    auto right = LabelTTF::create("alignment right", pFont, fontSize,
                                           blockSize, TextHAlignment::RIGHT, verticalAlignment[vAlignIdx]);

    auto leftColor = LayerColor::create(Color4B(100, 100, 100, 255), blockSize.width, blockSize.height);
    auto centerColor = LayerColor::create(Color4B(200, 100, 100, 255), blockSize.width, blockSize.height);
    auto rightColor = LayerColor::create(Color4B(100, 100, 200, 255), blockSize.width, blockSize.height);

    leftColor->ignoreAnchorPointForPosition(false);
    centerColor->ignoreAnchorPointForPosition(false);
    rightColor->ignoreAnchorPointForPosition(false);


    top->setAnchorPoint(Point(0.5, 1));
    left->setAnchorPoint(Point(0,0.5));
    leftColor->setAnchorPoint(Point(0,0.5));
    center->setAnchorPoint(Point(0,0.5));
    centerColor->setAnchorPoint(Point(0,0.5));
    right->setAnchorPoint(Point(0,0.5));
    rightColor->setAnchorPoint(Point(0,0.5));

    top->setPosition(Point(s.width/2,s.height-20));
    left->setPosition(Point(0,s.height/2));
    leftColor->setPosition(left->getPosition());
    center->setPosition(Point(blockSize.width, s.height/2));
    centerColor->setPosition(center->getPosition());
    right->setPosition(Point(blockSize.width*2, s.height/2));
    rightColor->setPosition(right->getPosition());

    this->addChild(leftColor, -1, kTagColor1);
    this->addChild(left, 0, kTagLabel1);
    this->addChild(rightColor, -1, kTagColor2);
    this->addChild(right, 0, kTagLabel2);
    this->addChild(centerColor, -1, kTagColor3);
    this->addChild(center, 0, kTagLabel3);
    this->addChild(top, 0, kTagLabel4);
}

void FontTest::backCallback(Object* sender)
{
    showFont(backAction());
}

void FontTest::nextCallback(Object* sender)
{
    showFont(nextAction());
}

std::string FontTest::title() const
{
    return "Font test";
}

void FontTest::restartCallback(Object* sender)
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
    auto layer = FontTest::create();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
