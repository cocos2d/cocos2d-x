#include "FontTest.h"
#include "../testResource.h"

USING_NS_CC;

enum {
    kTagLabel1,
    kTagLabel2,
    kTagLabel3,
    kTagLabel4,
    
    kTagColor1,
    kTagColor2,
    kTagColor3,
};

//you don't need any ifdef anymore
static std::string fontList[] =
{
    "fonts/A Damn Mess.ttf",
    "fonts/Abberancy.ttf",
    "fonts/Abduction.ttf",
    "fonts/Paint Boy.ttf",
    "fonts/Schwarzwald.ttf",
    "fonts/Scissor Cuts.ttf",
};

static int vAlignIdx = 0;
static TextVAlignment verticalAlignment[] =
{
    TextVAlignment::TOP,
    TextVAlignment::CENTER,
    TextVAlignment::BOTTOM,
};


FontTests::FontTests()
{
    for (auto& fontFile : fontList)
    {
        addTestCase("FontTests", [&](){vAlignIdx = 0; return FontTest::create(fontFile); });
    }
    
    for (auto& fontFile : fontList)
    {
        addTestCase("FontTests", [&](){ vAlignIdx = 1;  return FontTest::create(fontFile); });
    }
    
    for (auto& fontFile : fontList)
    {
        addTestCase("FontTests", [&](){vAlignIdx = 2; return FontTest::create(fontFile); });
    }
}

void FontTest::showFont(const std::string& fontFile)
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

    auto top = Label::createWithSystemFont(fontFile, fontFile, 24);
    auto left = Label::createWithSystemFont("alignment left", fontFile, fontSize,
                                          blockSize, TextHAlignment::LEFT, verticalAlignment[vAlignIdx]);
    auto center = Label::createWithSystemFont("alignment center", fontFile, fontSize,
                                            blockSize, TextHAlignment::CENTER, verticalAlignment[vAlignIdx]);
    auto right = Label::createWithSystemFont("alignment right", fontFile, fontSize,
                                           blockSize, TextHAlignment::RIGHT, verticalAlignment[vAlignIdx]);

    auto leftColor = LayerColor::create(Color4B(100, 100, 100, 255), blockSize.width, blockSize.height);
    auto centerColor = LayerColor::create(Color4B(200, 100, 100, 255), blockSize.width, blockSize.height);
    auto rightColor = LayerColor::create(Color4B(100, 100, 200, 255), blockSize.width, blockSize.height);

    leftColor->ignoreAnchorPointForPosition(false);
    centerColor->ignoreAnchorPointForPosition(false);
    rightColor->ignoreAnchorPointForPosition(false);


    top->setAnchorPoint(Vec2(0.5, 1));
    left->setAnchorPoint(Vec2(0,0.5));
    leftColor->setAnchorPoint(Vec2(0,0.5));
    center->setAnchorPoint(Vec2(0,0.5));
    centerColor->setAnchorPoint(Vec2(0,0.5));
    right->setAnchorPoint(Vec2(0,0.5));
    rightColor->setAnchorPoint(Vec2(0,0.5));

    top->setPosition(s.width/2,s.height-20);
    left->setPosition(0,s.height/2);
    leftColor->setPosition(left->getPosition());
    center->setPosition(blockSize.width, s.height/2);
    centerColor->setPosition(center->getPosition());
    right->setPosition(blockSize.width*2, s.height/2);
    rightColor->setPosition(right->getPosition());

    this->addChild(leftColor, -1, kTagColor1);
    this->addChild(left, 0, kTagLabel1);
    this->addChild(rightColor, -1, kTagColor2);
    this->addChild(right, 0, kTagLabel2);
    this->addChild(centerColor, -1, kTagColor3);
    this->addChild(center, 0, kTagLabel3);
    this->addChild(top, 0, kTagLabel4);
}

std::string FontTest::title() const
{
    return "Font test";
}
