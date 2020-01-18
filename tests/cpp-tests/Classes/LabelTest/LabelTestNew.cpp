/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "LabelTestNew.h"
#include "../testResource.h"
#include "renderer/CCRenderer.h"
#include "2d/CCFontAtlasCache.h"

USING_NS_CC;
using namespace ui;
using namespace extension;

enum {
    kTagTileMap = 1,
    kTagSpriteManager = 1,
    kTagAnimation1 = 1,
    kTagBitmapAtlas1 = 1,
    kTagBitmapAtlas2 = 2,
    kTagBitmapAtlas3 = 3,
};

enum {
    kTagSprite1,
    kTagSprite2,
    kTagSprite3,
    kTagSprite4,
    kTagSprite5,
    kTagSprite6,
    kTagSprite7,
    kTagSprite8,
};

//------------------------------------------------------------------
//
// AtlasDemoNew
//
//------------------------------------------------------------------

NewLabelTests::NewLabelTests()
{
    ADD_TEST_CASE(LabelFNTGlyphDesigner);
    ADD_TEST_CASE(LabelFNTColor);
    ADD_TEST_CASE(LabelFNTOpacity);
    ADD_TEST_CASE(LabelFNTColorAndOpacity);
    ADD_TEST_CASE(LabelFNTSpriteActions);
    ADD_TEST_CASE(LabelFNTMultiLine);
    ADD_TEST_CASE(LabelFNTRetina);
    ADD_TEST_CASE(LabelFNTMultiLineAlignment);
    ADD_TEST_CASE(LabelFNTMultiLineAlignmentUNICODE);
    ADD_TEST_CASE(LabelFNTUNICODELanguages);
    ADD_TEST_CASE(LabelFNTBounds);
    ADD_TEST_CASE(LabelFNTandTTFEmpty);
    ADD_TEST_CASE(LabelFNTHundredLabels);
    ADD_TEST_CASE(LabelFNTPadding);
    ADD_TEST_CASE(LabelFNTOffset);
    ADD_TEST_CASE(LabelFNTMultiFontAtlasNoRotation);
    ADD_TEST_CASE(LabelFNTMultiFontAtlasWithRotation);

    ADD_TEST_CASE(LabelTTFFontsTestNew);
    ADD_TEST_CASE(LabelTTFLongLineWrapping);
    ADD_TEST_CASE(LabelTTFCJKWrappingTest);
    ADD_TEST_CASE(LabelTTFColor);
    ADD_TEST_CASE(LabelTTFDynamicAlignment);
    ADD_TEST_CASE(LabelTTFEmoji);
    ADD_TEST_CASE(LabelAlignmentTest);
    ADD_TEST_CASE(LabelTTFUnicodeNew);
    ADD_TEST_CASE(LabelTTFDistanceField);
    ADD_TEST_CASE(LabelOutlineAndGlowTest);
    ADD_TEST_CASE(LabelMultilineWithOutline);
    ADD_TEST_CASE(LabelShadowTest);
    ADD_TEST_CASE(LabelLineHeightTest);
    ADD_TEST_CASE(LabelAdditionalKerningTest);
    ADD_TEST_CASE(LabelAddChildTest);
    ADD_TEST_CASE(LabelSmallDimensionsTest);

    ADD_TEST_CASE(LabelCharMapTest);
    ADD_TEST_CASE(LabelCharMapColorTest);

    ADD_TEST_CASE(LabelSystemFontColor);
    ADD_TEST_CASE(LabelTTFOldNew);
    ADD_TEST_CASE(LabelFontNameTest);

    ADD_TEST_CASE(LabelCrashTest);
    ADD_TEST_CASE(LabelIssue12775Test);
    ADD_TEST_CASE(LabelIssue11585Test);
    ADD_TEST_CASE(LabelIssue10773Test);
    ADD_TEST_CASE(LabelIssue11576Test);
    ADD_TEST_CASE(LabelIssue11699Test);
    ADD_TEST_CASE(LabelIssue12409Test);
    ADD_TEST_CASE(LabelIssue10089Test);
    ADD_TEST_CASE(LabelIssue9255Test);
    ADD_TEST_CASE(LabelIssue8492Test);
    ADD_TEST_CASE(LabelIssue4428Test);
    ADD_TEST_CASE(LabelIssue4999Test);
    ADD_TEST_CASE(LabelIssue10688Test);
    ADD_TEST_CASE(LabelIssue13202Test);
    ADD_TEST_CASE(LabelIssue9500Test);
    ADD_TEST_CASE(LabelWrapByWordTest);
    ADD_TEST_CASE(LabelWrapByCharTest);
    ADD_TEST_CASE(LabelWrapNoBreakSpaceTest);
    ADD_TEST_CASE(LabelShrinkByWordTest);
    ADD_TEST_CASE(LabelShrinkByCharTest);
    ADD_TEST_CASE(LabelResizeTest);
    ADD_TEST_CASE(LabelToggleTypeTest);
    ADD_TEST_CASE(LabelSystemFontTest);
    ADD_TEST_CASE(LabelCharMapFontTest);
    ADD_TEST_CASE(LabelIssue13846Test);

    ADD_TEST_CASE(LabelRichText);
    ADD_TEST_CASE(LabelStrikethrough);
    ADD_TEST_CASE(LabelUnderline);
    ADD_TEST_CASE(LabelUnderlineMultiline);
    ADD_TEST_CASE(LabelItalics);
    ADD_TEST_CASE(LabelBold);

    ADD_TEST_CASE(LabelLocalizationTest);

    ADD_TEST_CASE(LabelIssue15214);
    ADD_TEST_CASE(LabelIssue16293);
    ADD_TEST_CASE(LabelIssue16471);
    ADD_TEST_CASE(LabelIssue16717);
    ADD_TEST_CASE(LabelIssueLineGap);
    ADD_TEST_CASE(LabelIssue17902);
    ADD_TEST_CASE(LabelLetterColorsTest);
};

LabelFNTColorAndOpacity::LabelFNTColorAndOpacity()
{
    _time = 0;

    auto col = LayerColor::create( Color4B(128,128,128,255) );
    addChild(col, -10);
    
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Test");
    
    label1->setAnchorPoint( Vec2(0,0) );
    addChild(label1, 0, kTagBitmapAtlas1);
    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto seq = Sequence::create(fade, fade_in, nullptr);
    auto repeat = RepeatForever::create(seq);
    label1->runAction(repeat);
    
    auto label2 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Test");
    label2->setColor( Color3B::RED );
    addChild(label2, 0, kTagBitmapAtlas2);
    auto tint = Sequence::create(TintTo::create(1, 255, 0, 0),
        TintTo::create(1, 0, 255, 0),
        TintTo::create(1, 0, 0, 255),
        nullptr);
    label2->runAction( RepeatForever::create(tint) );
    
    auto label3 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Test");
    label3->setAnchorPoint( Vec2(1,1) );
    addChild(label3, 0, kTagBitmapAtlas3);
    
    label1->setPosition( VisibleRect::leftBottom() );
    label2->setPosition( VisibleRect::center() );
    label3->setPosition( VisibleRect::rightTop() );
    
    schedule(CC_CALLBACK_1(LabelFNTColorAndOpacity::step, this), "step_key");
}

void LabelFNTColorAndOpacity::step(float dt)
{
    _time += dt;
    char string[15] = {0};
    sprintf(string, "%2.2f Test j", _time);
    
    auto label1 = (Label*) getChildByTag(kTagBitmapAtlas1);
    label1->setString(string);
    
    auto label2 = (Label*) getChildByTag(kTagBitmapAtlas2);
    label2->setString(string);
    
    auto label3 = (Label*) getChildByTag(kTagBitmapAtlas3);
    label3->setString(string);
}

std::string LabelFNTColorAndOpacity::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTColorAndOpacity::subtitle() const
{
    return "Testing fade/tint action";
}

LabelFNTSpriteActions::LabelFNTSpriteActions()
{
    _time = 0;
    
    auto s = Director::getInstance()->getWinSize();
    
    auto drawNode = DrawNode::create();
    drawNode->drawLine( Vec2(0.0f, s.height/2), Vec2(s.width, s.height/2), Color4F(1.0f, 1.0f, 1.0f, 1.0f) );
    drawNode->drawLine( Vec2(s.width/2, 0.0f), Vec2(s.width/2, s.height), Color4F(1.0f, 1.0f, 1.0f, 1.0f) );
    addChild(drawNode, -1);

    // Upper Label
    auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "Bitmap Font Atlas");
    addChild(label);
    
    
    label->setPosition( Vec2(s.width/2, s.height/2) ); 
    
    auto BChar = (Sprite*) label->getLetter(0);
    auto FChar = (Sprite*) label->getLetter(7);
    auto AChar = (Sprite*) label->getLetter(12);
    
    
    auto rotate = RotateBy::create(2, 360);
    auto rot_4ever = RepeatForever::create(rotate);
    
    auto scale = ScaleBy::create(2, 1.5f);
    auto scale_back = scale->reverse();
    auto scale_seq = Sequence::create(scale, scale_back,nullptr);
    auto scale_4ever = RepeatForever::create(scale_seq);
    
    auto jump = JumpBy::create(0.5f, Vec2::ZERO, 60, 1);
    auto jump_4ever = RepeatForever::create(jump);
    
    auto fade_out = FadeOut::create(1);
    auto fade_in = FadeIn::create(1);
    auto seq = Sequence::create(fade_out, fade_in, nullptr);
    auto fade_4ever = RepeatForever::create(seq);
    
    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
    
    
    // Bottom Label
    auto label2 = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "00.0");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition( Vec2(s.width/2.0f, 80.0f) );
    
    auto lastChar = (Sprite*) label2->getLetter(3);
    lastChar->runAction( rot_4ever->clone() );
    
    schedule(CC_CALLBACK_1(LabelFNTSpriteActions::step, this), 0.1f, "step_key");
}

void LabelFNTSpriteActions::step(float dt)
{
    _time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", _time);
    auto label1 = (Label*) getChildByTag(kTagBitmapAtlas2);
    label1->setString(string);
}

std::string LabelFNTSpriteActions::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTSpriteActions::subtitle() const
{
    return "Testing run action on the specified character";
}

LabelFNTPadding::LabelFNTPadding()
{
    auto label = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "abcdefg");
    addChild(label);
    
    auto s = Director::getInstance()->getWinSize();
    
    label->setPosition( Vec2(s.width/2, s.height/2) );
}

std::string LabelFNTPadding::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTPadding::subtitle() const
{
    return "Testing padding";
}

LabelFNTOffset::LabelFNTOffset()
{
    auto s = Director::getInstance()->getWinSize();

    Label* label = nullptr;
    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "FaFeFiFoFu");
    addChild(label);
    label->setPosition( Vec2(s.width/2, s.height/2+50) );
    
    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "fafefifofu");
    addChild(label);
    label->setPosition( Vec2(s.width/2, s.height/2) );

    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "aeiou");
    addChild(label);
    label->setPosition( Vec2(s.width/2, s.height/2-50) );
}

std::string LabelFNTOffset::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTOffset::subtitle() const
{
    return "Rendering should be OK. Testing offset";
}

LabelFNTColor::LabelFNTColor()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    auto label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Blue");
    label->setColor( Color3B::BLUE );
    addChild(label);
    label->setPosition(winSize.width / 2, winSize.height * 0.7f);

    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Red");
    addChild(label);
    label->setPosition(winSize.width / 2, winSize.height * 0.5f);
    label->setColor( Color3B::RED );

    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Green");
    addChild(label);
    label->setPosition(winSize.width / 2, winSize.height  * 0.3f);
    label->setColor( Color3B::GREEN );
    label->setString("Green");
}

std::string LabelFNTColor::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTColor::subtitle() const
{
    return "Testing color";
}

LabelFNTOpacity::LabelFNTOpacity()
{
    auto winSize = Director::getInstance()->getWinSize();

    auto label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Opacity 100");
    label->setOpacity(100);
    addChild(label);
    label->setPosition(winSize.width / 2, winSize.height * 0.6f);

    label = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "Opacity 200");
    label->setOpacity(200);
    addChild(label);
    label->setPosition(winSize.width / 2, winSize.height * 0.4f);
}

std::string LabelFNTOpacity::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTOpacity::subtitle() const
{
    return "Testing opacity";
}

LabelFNTHundredLabels::LabelFNTHundredLabels()
{
    // Upper Label
    for ( int i=0 ; i < 100;i ++ ) 
    {
        char str[6] = {0};
        sprintf(str, "-%d-", i);
        auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt", str);
        addChild(label);
        
        auto s = Director::getInstance()->getWinSize();

        auto p = Vec2( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
        label->setPosition( p );
    }
}

std::string LabelFNTHundredLabels::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTHundredLabels::subtitle() const
{
    return "Creating several Labels using the same FNT file; should be fast";
}

LabelFNTMultiLine::LabelFNTMultiLine()
{
    Size s;

    // Left
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", " Multi line\nLeft");
    label1->setAnchorPoint(Vec2(0,0));
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    auto label2 = Label::createWithBMFont( "fonts/bitmapFontTest3.fnt", "Multi line\nCenter");
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    auto label3 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "Multi line\nRight\nThree lines Three");
    label3->setAnchorPoint(Vec2(1, 1));
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    label1->setPosition(VisibleRect::leftBottom());
    label2->setPosition(VisibleRect::center());
    label3->setPosition(VisibleRect::rightTop());
}

std::string LabelFNTMultiLine::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTMultiLine::subtitle() const
{
    return "Multiline + anchor point";
}

LabelFNTandTTFEmpty::LabelFNTandTTFEmpty()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "", TextHAlignment::CENTER, s.width);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(Vec2(s.width/2, s.height - 100));

    // LabelTTF
    TTFConfig ttfConfig("fonts/arial.ttf",24);
    auto label2 = Label::createWithTTF(ttfConfig,"", TextHAlignment::CENTER,s.width);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(Vec2(s.width/2, s.height / 2));
    
    auto label3 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.plist");
    addChild(label3, 0, kTagBitmapAtlas3);
    label3->setPosition(Vec2(s.width/2, 100.0f));

    schedule(CC_CALLBACK_1(LabelFNTandTTFEmpty::updateStrings, this), 1.0f, "update_strings_key");

    setEmpty = false;
}

void LabelFNTandTTFEmpty::updateStrings(float dt)
{
    auto label1 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas1) );
    auto label2 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas2) );
    auto label3 = static_cast<Label*>( getChildByTag(kTagBitmapAtlas3) );

    if( ! setEmpty )
    {
        label1->setString("not empty");
        label2->setString("not empty");
        label3->setString("hi");
    
        setEmpty = true;
    }
    else
    {
        label1->setString("");
        label2->setString("");
        label3->setString("");
    
        setEmpty = false;
    }
}

std::string LabelFNTandTTFEmpty::title() const
{
    return "New Label + FNT/TTF/CharMap";
}

std::string LabelFNTandTTFEmpty::subtitle() const
{
    return "Testing empty string.";
}

LabelFNTRetina::LabelFNTRetina()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/konqa32.fnt", "TESTING RETINA DISPLAY");
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/2));
}

std::string LabelFNTRetina::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTRetina::subtitle() const
{
    return "loading arista16 or arista16-hd";
}

LabelFNTGlyphDesigner::LabelFNTGlyphDesigner()
{
    auto winSize = Director::getInstance()->getWinSize();

    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);

    auto label1 = Label::createWithBMFont("fonts/futura-48.fnt", "Testing Glyph Designer");
    // Demo for reloadFontAtlasFNT function, after it been called, all UI widget
    //  use the special font must reset font, because the old one is invalid.
    FontAtlasCache::reloadFontAtlasFNT("fonts/futura-48.fnt");
    label1->setBMFontFilePath("fonts/futura-48.fnt");
    addChild(label1);
    label1->setPosition(Vec2(winSize.width / 2, winSize.height * 0.4f));

    auto label2 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "Hello World");
    label2->setPosition(Vec2(winSize.width / 2, winSize.height * 0.6f));
    addChild(label2);
}

std::string LabelFNTGlyphDesigner::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTGlyphDesigner::subtitle() const
{
    return "Testing Glyph Designer";
}

/// BitmapFontMultiLineAlignmentNew

#define LongSentencesExample "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
#define LineBreaksExample    "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah"
#define MixedExample         "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF"

#define ArrowsMax 0.95
#define ArrowsMin 0.7

#define LeftAlign 0
#define CenterAlign 1
#define RightAlign 2

#define LongSentences 0
#define LineBreaks 1
#define Mixed 2

static float alignmentItemPadding  = 50;
static float menuItemPaddingCenter = 50;

bool LabelFNTMultiLineAlignment::init()
{
    if (!AtlasDemoNew::init())
    {
        return false;
    }

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(LabelFNTMultiLineAlignment::onTouchesEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // ask director the the window size
    auto size = Director::getInstance()->getWinSize();

    // create and initialize a Label
    this->_label = Label::createWithBMFont("fonts/markerFelt.fnt", "", TextHAlignment::CENTER, size.width/1.5);

    this->_arrowsBar = Sprite::create("Images/arrowsBar.png");
    this->_arrows = Sprite::create("Images/arrows.png");

    MenuItemFont::setFontSize(20);
    auto longSentences = MenuItemFont::create("Long Flowing Sentences", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto lineBreaks    = MenuItemFont::create("Short Sentences With Intentional Line Breaks", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto mixed         = MenuItemFont::create("Long Sentences Mixed With Intentional Line Breaks", CC_CALLBACK_1(LabelFNTMultiLineAlignment::stringChanged, this));
    auto stringMenu    = Menu::create(longSentences, lineBreaks, mixed, nullptr);
    stringMenu->alignItemsVertically();

    longSentences->setTag(LongSentences);
    lineBreaks->setTag(LineBreaks);
    mixed->setTag(Mixed);

    _menuItems.push_back(longSentences);
    _menuItems.push_back(lineBreaks);
    _menuItems.push_back(mixed);

    MenuItemFont::setFontSize(30);

    auto left = MenuItemFont::create("Left", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto center = MenuItemFont::create("Center", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));
    auto right = MenuItemFont::create("Right", CC_CALLBACK_1(LabelFNTMultiLineAlignment::alignmentChanged, this));

    auto alignmentMenu = Menu::create(left, center, right, nullptr);
    alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

    left->setTag(LeftAlign);
    center->setTag(CenterAlign);
    right->setTag(RightAlign);

    // position the label on the center of the screen
    this->_label->setPosition(Vec2(size.width/2, size.height/2));

    this->_arrowsBar->setVisible(false);

    float arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
    this->_arrowsBar->setScaleX(arrowsWidth / this->_arrowsBar->getContentSize().width);
    this->_arrowsBar->setPosition(Vec2(((ArrowsMax + ArrowsMin) / 2) * size.width, this->_label->getPosition().y));

    stringMenu->setPosition(Vec2(size.width/2, size.height - menuItemPaddingCenter));
    alignmentMenu->setPosition(Vec2(size.width/2, menuItemPaddingCenter+15));

    this->selectSentenceItem(longSentences);
    this->selectAlignmentItem(center);
    this->snapArrowsToEdge();

    this->addChild(this->_label);
    this->addChild(this->_arrowsBar);
    this->addChild(this->_arrows);
    this->addChild(stringMenu);
    this->addChild(alignmentMenu);

    return true;
}

std::string LabelFNTMultiLineAlignment::title() const
{
    return "";
}

std::string LabelFNTMultiLineAlignment::subtitle() const
{
    return "";
}

void LabelFNTMultiLineAlignment::selectAlignmentItem(cocos2d::MenuItemFont * item)
{
    if (this->_lastAlignmentItem && this->_lastAlignmentItem != item)
    {
        this->_lastAlignmentItem->setColor(Color3B::WHITE);
    }

    this->_lastAlignmentItem = item;
    item->setColor(Color3B::RED);

    switch (item->getTag())
    {
    case LeftAlign:
        this->_label->setAlignment(TextHAlignment::LEFT);
        break;
    case CenterAlign:
        this->_label->setAlignment(TextHAlignment::CENTER);
        break;
    case RightAlign:
        this->_label->setAlignment(TextHAlignment::RIGHT);
        break;

    default:
        break;
    }
}

void LabelFNTMultiLineAlignment::selectSentenceItem(cocos2d::MenuItemFont* item)
{
    if (this->_lastSentenceItem && this->_lastSentenceItem != item)
    {
        this->_lastSentenceItem->setColor(Color3B::WHITE);
    }

    this->_lastSentenceItem = item;
    item->setColor(Color3B::RED);

    auto str = this->getItemString(item);
    this->_label->setString(str);
}

std::string LabelFNTMultiLineAlignment::getItemString(cocos2d::MenuItemFont* item)
{
    std::string str;

    switch (item->getTag())
    {
    case LongSentences:
        str = LongSentencesExample;
        break;
    case LineBreaks:
        str = LineBreaksExample;
        break;
    case Mixed:
        str = MixedExample;
        break;

    default:
        break;
    }

    return str;
}

void LabelFNTMultiLineAlignment::stringChanged(cocos2d::Ref *sender)
{
    auto item = (MenuItemFont*)sender;

    selectSentenceItem(item);

    this->snapArrowsToEdge();
}

void LabelFNTMultiLineAlignment::alignmentChanged(cocos2d::Ref *sender)
{
    auto item = static_cast<MenuItemFont*>(sender);

    selectAlignmentItem(item);

    this->snapArrowsToEdge();
}

void LabelFNTMultiLineAlignment::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches[0];
    auto location = touch->getLocationInView();

    if (this->_arrows->getBoundingBox().containsPoint(location))
    {
        _drag = true;
        this->_arrowsBar->setVisible(true);
    }
}

void LabelFNTMultiLineAlignment::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    _drag = false;
    this->snapArrowsToEdge();

    this->_arrowsBar->setVisible(false);
}

void LabelFNTMultiLineAlignment::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (! _drag)
    {
        return;
    }

    auto touch = touches[0];
    auto location = touch->getLocationInView();

    auto winSize = Director::getInstance()->getWinSize();

    this->_arrows->setPosition(Vec2(MAX(MIN(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
        this->_arrows->getPosition().y));

    float labelWidth = fabs(this->_arrows->getPosition().x - this->_label->getPosition().x) * 2;

    this->_label->setMaxLineWidth(labelWidth);
}

void LabelFNTMultiLineAlignment::snapArrowsToEdge()
{
    this->_arrows->setPosition(Vec2(this->_label->getPosition().x + this->_label->getContentSize().width/2,
        this->_label->getPosition().y));
}

/// LabelFNTMultiLineAlignmentUNICODE

bool LabelFNTMultiLineAlignmentUNICODE::init()
{
    if (!LabelFNTMultiLineAlignment::init())
    {
        return false;
    }

    this->_menuItems[0]->setString("French");
    this->_menuItems[1]->setString("Spanish");
    this->_menuItems[2]->setString("Ukrainian");

    auto ttfConfig = this->_label->getTTFConfig();
    ttfConfig.fontSize = 20;
    ttfConfig.fontFilePath = "fonts/tahoma.ttf";
    this->_label->setTTFConfig(ttfConfig);

    this->selectSentenceItem(this->_menuItems[0]);
    this->snapArrowsToEdge();

    return true;
}

std::string LabelFNTMultiLineAlignmentUNICODE::title() const
{
    return "";
}

std::string LabelFNTMultiLineAlignmentUNICODE::subtitle() const
{
    return "";
}

std::string LabelFNTMultiLineAlignmentUNICODE::getItemString(cocos2d::MenuItemFont* item)
{
    std::string str;

    auto strings = FileUtils::getInstance()->getValueMapFromFile("strings/LabelFNTMultiLineAlignmentUNICODE.xml");

    switch (item->getTag())
    {
    case LongSentences:
        str = strings["french"].asString();
        break;
    case LineBreaks:
        str = strings["spanish"].asString();
        break;
    case Mixed:
        str = strings["ukrainian"].asString();
        break;

    default:
        break;
    }

    return str;
}

/// BMFontUnicodeNew
LabelFNTUNICODELanguages::LabelFNTUNICODELanguages()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("strings/LabelFNTUNICODELanguages.xml");
    std::string chinese  = strings["chinese1"].asString();
    std::string russian  = strings["russian"].asString();
    std::string spanish  = strings["spanish"].asString();
    std::string japanese = strings["japanese"].asString();

    auto s = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithBMFont("fonts/arial-unicode-26.fnt", spanish, TextHAlignment::CENTER, 200);
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/5*3));
    
    auto label2 = Label::createWithBMFont("fonts/arial-unicode-26.fnt", chinese);
    addChild(label2);
    label2->setPosition(Vec2(s.width/2, s.height/5*2.5));

    auto label3 = Label::createWithBMFont("fonts/arial-26-en-ru.fnt", russian);
    addChild(label3);
    label3->setPosition(Vec2(s.width/2, s.height/5*2));

    auto label4 = Label::createWithBMFont("fonts/arial-unicode-26.fnt", japanese);
    addChild(label4);
    label4->setPosition(Vec2(s.width/2, s.height/5*1.5));
}

std::string LabelFNTUNICODELanguages::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTUNICODELanguages::subtitle() const
{
    return "Testing Unicode.You should see 4 different labels:In Spanish, Chinese, Russian and Japanese";
}

LabelFNTBounds::LabelFNTBounds()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(128,128,128,255));
    addChild(layer, -10);
    
    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/boundsTestFont.fnt", "Testing Glyph Designer", TextHAlignment::CENTER,s.width);
    addChild(label1);
    label1->setPosition(Vec2(s.width/2, s.height/2));

    auto drawNode = DrawNode::create();
    auto labelSize = label1->getContentSize();
    auto origin    = Director::getInstance()->getWinSize();
    
    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Vec2 vertices[4]=
    {
        Vec2(origin.width, origin.height),
        Vec2(labelSize.width + origin.width, origin.height),
        Vec2(labelSize.width + origin.width, labelSize.height + origin.height),
        Vec2(origin.width, labelSize.height + origin.height)
    };
    drawNode->drawPoly(vertices, 4, true, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    addChild(drawNode);
}

std::string LabelFNTBounds::title() const
{
    return "New Label + Bitmap font";
}

std::string LabelFNTBounds::subtitle() const
{
    return "Testing bounding-box";
}

LabelFNTMultiFontAtlasNoRotation::LabelFNTMultiFontAtlasNoRotation()
{
    auto s = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithBMFont("fonts/helvetica-32.fnt", "This is Helvetica");
    addChild(label1);
    label1->setPosition(Vec2(s.width / 2, s.height / 3 * 2));

    auto label2 = Label::createWithBMFont("fonts/geneva-32.fnt", "And this is Geneva", TextHAlignment::LEFT, 0, Rect(0, 128, 0, 0), false);
    addChild(label2);
    label2->setPosition(Vec2(s.width / 2, s.height / 3 * 1));
}

std::string LabelFNTMultiFontAtlasNoRotation::title() const
{
    return "New Label + Multi-BM Font Atlas Test1";
}

std::string LabelFNTMultiFontAtlasNoRotation::subtitle() const
{
    return "Using 2 .fnt definitions that share the same texture atlas.";
}

LabelFNTMultiFontAtlasWithRotation::LabelFNTMultiFontAtlasWithRotation()
{
    auto s = Director::getInstance()->getWinSize();

    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("fonts/bmfont-rotated-test.plist");

    // Label BMFont
    auto label1 = Label::createWithBMFont("fonts/helvetica-regular-32.fnt", "Helvetica with SubTextureKey", TextHAlignment::CENTER, 0, "helvetica-regular-32.png");
    label1->setPosition(Vec2(s.width / 2, s.height / 3 * 2));
    this->addChild(label1);

    const auto frame = spriteCache->getSpriteFrameByName("geneva-regular-32.png");
    auto label2 = Label::createWithBMFont("fonts/geneva-regular-32.fnt", "Geneva with Rect and Rotated", TextHAlignment::CENTER, 0, frame->getRectInPixels(), frame->isRotated());
    label2->setPosition(Vec2(s.width / 2, s.height / 3 * 1));
    this->addChild(label2);
}

std::string LabelFNTMultiFontAtlasWithRotation::title() const
{
    return "New Label + Multi-BM Font Atlas Test2";
}

std::string LabelFNTMultiFontAtlasWithRotation::subtitle() const
{
    return "Using 2 .fnt definitions that share a PLIST texture atlas (rotated).";
}

LabelTTFLongLineWrapping::LabelTTFLongLineWrapping()
{
    auto size = Director::getInstance()->getWinSize();

    // Long sentence
    TTFConfig ttfConfig("fonts/arial.ttf", 14);
    auto label1 = Label::createWithTTF(ttfConfig, LongSentencesExample, TextHAlignment::CENTER,size.width);
    label1->setPosition( Vec2(size.width/2, size.height/2) );
    label1->setAnchorPoint(Vec2(0.5f, 1.0f));
    addChild(label1);
}

std::string LabelTTFLongLineWrapping::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFLongLineWrapping::subtitle() const
{
    return "Testing auto-wrapping";
}

LabelTTFColor::LabelTTFColor()
{
    auto size = Director::getInstance()->getWinSize();

    TTFConfig ttfConfig("fonts/arial.ttf", 18);
    // Green
    auto label1 = Label::createWithTTF(ttfConfig,"Green", TextHAlignment::CENTER, size.width);
    label1->setPosition(size.width/2, size.height * 0.5f);
    label1->setTextColor( Color4B::GREEN );
    addChild(label1);

    // Red
    auto label2 = Label::createWithTTF(ttfConfig,"Red", TextHAlignment::CENTER, size.width);
    label2->setPosition(size.width/2, size.height * 0.65f);
    label2->setTextColor( Color4B::RED );
    addChild(label2);

    // Blue
    auto label3 = Label::createWithTTF(ttfConfig,"Blue", TextHAlignment::CENTER, size.width);
    label3->setPosition(size.width/2, size.height * 0.35f);
    label3->setTextColor( Color4B::BLUE );
    addChild(label3);
}

std::string LabelTTFColor::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFColor::subtitle() const
{
    return "Testing Color";
}

LabelTTFDynamicAlignment::LabelTTFDynamicAlignment()
{
    auto winSize = Director::getInstance()->getWinSize();

    TTFConfig ttfConfig("fonts/arial.ttf", 23);
    _label = Label::createWithTTF(ttfConfig, LongSentencesExample, TextHAlignment::CENTER, winSize.width);
    _label->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(_label);

    auto menu = Menu::create(
                              MenuItemFont::create("Left", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentLeft, this)),
                              MenuItemFont::create("Center", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentCenter, this)),
                              MenuItemFont::create("Right", CC_CALLBACK_1(LabelTTFDynamicAlignment::setAlignmentRight, this)),
                              nullptr);
    
    menu->alignItemsHorizontallyWithPadding(20);
    menu->setPosition(winSize.width / 2, winSize.height * 0.25f);
    addChild(menu);
}

void  LabelTTFDynamicAlignment::updateAlignment()
{
    if (_label)
    {
        _label->setAlignment(_horizAlign);
    }
}

void LabelTTFDynamicAlignment::setAlignmentLeft(Ref* sender)
{
    _horizAlign = TextHAlignment::LEFT;
    this->updateAlignment();
}

void LabelTTFDynamicAlignment::setAlignmentCenter(Ref* sender)
{
    _horizAlign = TextHAlignment::CENTER;
    this->updateAlignment();
}

void LabelTTFDynamicAlignment::setAlignmentRight(Ref* sender)
{
    _horizAlign = TextHAlignment::RIGHT;
    this->updateAlignment();
}

std::string LabelTTFDynamicAlignment::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFDynamicAlignment::subtitle() const
{
    return "Testing text alignment";
}

//
// NewLabelTTF Chinese/Japanese/Korean wrapping test
//
LabelTTFCJKWrappingTest::LabelTTFCJKWrappingTest()
{
    auto size = Director::getInstance()->getWinSize();
    
    auto drawNode = DrawNode::create();
    drawNode->setAnchorPoint(Vec2(0, 0));
    this->addChild(drawNode);
    drawNode->drawSegment(
        Vec2(size.width * 0.1f, size.height * 0.8f),
        Vec2(size.width * 0.1, 0.0f), 1, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
    drawNode->drawSegment(
        Vec2(size.width * 0.85f, size.height * 0.8f),
        Vec2(size.width * 0.85f, 0.0f), 1, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
    
    TTFConfig ttfConfig("fonts/HKYuanMini.ttf", 25, GlyphCollection::DYNAMIC);
    auto label1 = Label::createWithTTF(ttfConfig,
        "你好，Cocos2d-x v3的New Label.", TextHAlignment::LEFT, size.width * 0.75f);
    if(label1) {
        label1->setTextColor(Color4B(128, 255, 255, 255));
        label1->setPosition(Vec2(size.width * 0.1f, size.height * 0.6f));
        label1->setAnchorPoint(Vec2(0.0f, 0.5f));
        this->addChild(label1);
        // Demo for unloadFontAtlasTTF function, after it been called, all UI widget
        //  use the special font must reset font, because the old one is invalid.
        FontAtlasCache::unloadFontAtlasTTF("fonts/HKYuanMini.ttf");
        label1->setTTFConfig(ttfConfig);
    }

    auto label2 = Label::createWithTTF(ttfConfig,
        "早上好，Cocos2d-x v3的New Label.", TextHAlignment::LEFT, size.width * 0.75f);
    if(label2) {
        label2->setTextColor(Color4B(255, 128, 255, 255));
        label2->setPosition(Vec2(size.width * 0.1f, size.height * 0.4f));
        label2->setAnchorPoint(Vec2(0.0f, 0.5f));
        this->addChild(label2);
    }

    auto label3 = Label::createWithTTF(ttfConfig,
        "美好的一天啊美好的一天啊美好的一天啊", TextHAlignment::LEFT, size.width * 0.75f);
    if(label3) {
        label3->setTextColor(Color4B(255, 255, 128, 255));
        label3->setPosition(Vec2(size.width * 0.1f, size.height * 0.2f));
        label3->setAnchorPoint(Vec2(0.0f, 0.5f));
        this->addChild(label3);
    }
}

std::string LabelTTFCJKWrappingTest::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFCJKWrappingTest::subtitle() const
{
    return "New Label with CJK + ASCII characters\n"
        "Characters should stay in the correct position";
}

//
// NewLabelTTF unicode test
//
LabelTTFUnicodeNew::LabelTTFUnicodeNew()
{
    auto strings = FileUtils::getInstance()->getValueMapFromFile("strings/LabelFNTUNICODELanguages.xml");
    std::string chinese  = strings["chinese1"].asString();
    auto winSize = Director::getInstance()->getWinSize();

    // Spanish
    auto label1 = Label::createWithTTF("Buen día, ¿cómo te llamas?", "fonts/arial.ttf", 23);
    label1->setPosition(winSize.width / 2, winSize.height * 0.65f);
    addChild(label1);
    
    // German
    auto label2 = Label::createWithTTF("In welcher Straße haben Sie gelebt?", "fonts/arial.ttf", 23);
    label2->setPosition(winSize.width / 2, winSize.height * 0.5f);
    addChild(label2);
    
    // Chinese
    auto label3 = Label::createWithTTF(chinese, "fonts/HKYuanMini.ttf", 24);
    label3->setPosition(winSize.width / 2, winSize.height * 0.35f);
    addChild(label3);
}

std::string LabelTTFUnicodeNew::title() const
{
    return "New Label + TTF unicode";
}

std::string LabelTTFUnicodeNew::subtitle() const
{
    return "Uses the new Label with TTF. Testing unicode";
}

//
// LabelTTFEmoji emoji test
//
LabelTTFEmoji::LabelTTFEmoji()
{
    std::string emojiString = FileUtils::getInstance()->getStringFromFile("fonts/emoji.txt");
    auto winSize = Director::getInstance()->getWinSize();
    
    auto label = Label::createWithTTF(emojiString, "fonts/NotoEmoji-Regular.ttf", 23);
    label->setPosition(winSize.width / 2, winSize.height / 2);
    label->setDimensions(winSize.width, winSize.height);
    label->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    label->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    addChild(label);
}

std::string LabelTTFEmoji::title() const
{
    return "New Label + Emoji";
}

std::string LabelTTFEmoji::subtitle() const
{
    return "Uses the new Label with TTF. Testing Emoji";
}


LabelTTFFontsTestNew::LabelTTFFontsTestNew()
{
    const char *ttfpaths[] = {
        "fonts/A Damn Mess.ttf",
        "fonts/Abberancy.ttf",
        "fonts/Abduction.ttf",
        "fonts/American Typewriter.ttf",
        "fonts/Paint Boy.ttf",
        "fonts/Schwarzwald.ttf",
        "fonts/Scissor Cuts.ttf",
    };

    int fontCount = sizeof(ttfpaths) / sizeof(ttfpaths[0]);
    auto size = Director::getInstance()->getWinSize();
    TTFConfig ttfConfig(ttfpaths[0],20, GlyphCollection::NEHE);

    for (int i = 0; i < fontCount; ++i) {
        ttfConfig.fontFilePath = ttfpaths[i];
        auto label = Label::createWithTTF(ttfConfig, ttfpaths[i], TextHAlignment::CENTER,0);
        if( label ) {            
            label->setPosition(size.width / 2, ((size.height * 0.6) / fontCount * i) + (size.height / 4));
            addChild(label);
        } else {
            log("ERROR: Cannot load: %s", ttfpaths[i]);
        }
    }
}

std::string LabelTTFFontsTestNew::title() const
{
    return "New Label + TTF";
}

std::string LabelTTFFontsTestNew::subtitle() const
{
    return "";
}

LabelTTFDistanceField::LabelTTFDistanceField()
{
    auto size = Director::getInstance()->getWinSize();
    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    auto label1 = Label::createWithTTF(ttfConfig,"Distance Field",TextHAlignment::CENTER,size.width);
    label1->setPosition( Vec2(size.width/2, size.height * 0.6f) );
    label1->setTextColor( Color4B::GREEN );
    addChild(label1);

    auto action = Sequence::create(
        DelayTime::create(1.0f),
        ScaleTo::create(6.0f,5.0f,5.0f),
        ScaleTo::create(6.0f,1.0f,1.0f),
        nullptr);
    label1->runAction(RepeatForever::create(action));

    // Draw the label border
    auto& labelContentSize = label1->getContentSize();
    auto borderDraw = DrawNode::create();
    label1->addChild(borderDraw);
    borderDraw->clear();
    borderDraw->setLineWidth(1);
    Vec2 vertices[4] =
    {
        Vec2::ZERO,
        Vec2(labelContentSize.width, 0.0f),
        Vec2(labelContentSize.width, labelContentSize.height),
        Vec2(0.0f, labelContentSize.height)
    };
    borderDraw->drawPoly(vertices, 4, true, Color4F::RED);

    auto label2 = Label::createWithTTF(ttfConfig,"Distance Field",TextHAlignment::CENTER,size.width);
    label2->setPosition( Vec2(size.width/2, size.height * 0.3f) );
    label2->setTextColor( Color4B::RED );
    addChild(label2);
    
    // Draw the label border
    auto& labelContentSize2 = label2->getContentSize();
    auto borderDraw2 = DrawNode::create();
    label2->addChild(borderDraw2);
    borderDraw2->clear();
    borderDraw2->setLineWidth(1);
    Vec2 vertices2[4] =
    {
        Vec2::ZERO,
        Vec2(labelContentSize2.width, 0.0f),
        Vec2(labelContentSize2.width, labelContentSize2.height),
        Vec2(0.0f, labelContentSize2.height)
    };
    borderDraw2->drawPoly(vertices2, 4, true, Color4F::GREEN);
}

std::string LabelTTFDistanceField::title() const
{
    return "New Label + .TTF";
}

std::string LabelTTFDistanceField::subtitle() const
{
    return "Testing rendering base on DistanceField";
}

LabelOutlineAndGlowTest::LabelOutlineAndGlowTest()
{
    auto size = Director::getInstance()->getWinSize();

    auto bg = LayerColor::create(Color4B(200,191,231,255));
    this->addChild(bg);

    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    auto label1 = Label::createWithTTF(ttfConfig,"Glow", TextHAlignment::CENTER, size.width);
    label1->setPosition( Vec2(size.width/2, size.height*0.7) );
    label1->setTextColor( Color4B::GREEN );
    label1->enableGlow(Color4B::YELLOW);
    addChild(label1);

    ttfConfig.outlineSize = 1;
    auto label2 = Label::createWithTTF(ttfConfig,"Outline", TextHAlignment::CENTER, size.width);
    label2->setPosition( Vec2(size.width/2, size.height*0.6) );
    label2->setTextColor( Color4B::RED );
    label2->enableOutline(Color4B::BLUE);
    addChild(label2);

    ttfConfig.outlineSize = 2;
    auto label3 = Label::createWithTTF(ttfConfig,"Outline", TextHAlignment::CENTER, size.width);
    label3->setPosition( Vec2(size.width/2, size.height*0.48) );
    label3->setTextColor( Color4B::RED );
    label3->enableOutline(Color4B::BLUE);
    addChild(label3);

    ttfConfig.outlineSize = 3;
    auto label4 = Label::createWithTTF(ttfConfig,"Outline", TextHAlignment::CENTER, size.width);
    label4->setPosition( Vec2(size.width/2, size.height*0.36) );
    label4->setTextColor( Color4B::RED );
    label4->enableOutline(Color4B::BLUE);
    addChild(label4);
}

std::string LabelOutlineAndGlowTest::title() const
{
    return "New Label + .TTF";
}

std::string LabelOutlineAndGlowTest::subtitle() const
{
    return "Testing outline and glow of label";
}

LabelShadowTest::LabelShadowTest()
{

}

void LabelShadowTest::onEnter()
{
    AtlasDemoNew::onEnter();

    auto size = Director::getInstance()->getWinSize();

    auto bg = LayerColor::create(Color4B(200,191,231,255));
    this->addChild(bg);

    auto slider = ui::Slider::create();
    slider->setTag(1);
    slider->setTouchEnabled(true);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Vec2(size.width / 2.0f, size.height * 0.15f + slider->getContentSize().height * 2.0f));
    slider->setPercent(52);
    slider->addEventListener(CC_CALLBACK_2(LabelShadowTest::sliderEvent, this));
    addChild(slider, 999);

    auto slider2 = ui::Slider::create();
    slider2->setTag(2);
    slider2->setTouchEnabled(true);
    slider2->loadBarTexture("cocosui/sliderTrack.png");
    slider2->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider2->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider2->setPosition(Vec2(size.width * 0.15f, size.height / 2.0f));
    slider2->setRotation(90);
    slider2->setPercent(52);
    slider2->addEventListener(CC_CALLBACK_2(LabelShadowTest::sliderEvent, this));
    addChild(slider2, 999);

    float subtitleY = _subtitleLabel->getPosition().y;
    float horizontalSliderY = slider->getPosition().y;
    float step = (subtitleY - horizontalSliderY) / 4;

    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    shadowLabelTTF = Label::createWithTTF(ttfConfig,"TTF:Shadow");
    shadowLabelTTF->setPosition( Vec2(size.width/2, horizontalSliderY + step * (0.5f + 3)) );
    shadowLabelTTF->setTextColor( Color4B::RED );
    shadowLabelTTF->enableShadow(Color4B::BLACK);
    addChild(shadowLabelTTF);

    shadowLabelOutline = Label::createWithTTF(ttfConfig,"TTF:Shadow");
    shadowLabelOutline->setPosition( Vec2(size.width/2, horizontalSliderY + step * (0.5f + 2)) );
    shadowLabelOutline->setTextColor( Color4B::RED );
    shadowLabelOutline->enableOutline(Color4B::YELLOW,1);
    shadowLabelOutline->enableShadow(Color4B::GREEN);
    addChild(shadowLabelOutline);

    shadowLabelGrow = Label::createWithTTF(ttfConfig,"TTF:Shadow");
    shadowLabelGrow->setPosition( Vec2(size.width/2, horizontalSliderY + step * (0.5f + 1)) );
    shadowLabelGrow->setTextColor( Color4B::RED );
    shadowLabelGrow->enableGlow(Color4B::YELLOW);
    shadowLabelGrow->enableShadow(Color4B::BLUE);
    addChild(shadowLabelGrow);

    shadowLabelBMFont = Label::createWithBMFont("fonts/bitmapFontTest.fnt", "BMFont:Shadow");
    shadowLabelBMFont->setPosition( Vec2(size.width/2, horizontalSliderY + step * 0.5f));
    shadowLabelBMFont->setColor( Color3B::RED );
    shadowLabelBMFont->enableShadow(Color4B::GREEN);
    addChild(shadowLabelBMFont);
}

void LabelShadowTest::sliderEvent(Ref *pSender, ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider*  slider = (Slider*)this->getChildByTag(1);
        Slider*  slider2 = (Slider*)this->getChildByTag(2);

        auto offset = Size(slider->getPercent()-50,50 - slider2->getPercent());
        shadowLabelTTF->enableShadow(Color4B::BLACK,offset);
        shadowLabelBMFont->enableShadow(Color4B::GREEN,offset);
        shadowLabelOutline->enableShadow(Color4B::GREEN,offset);
        shadowLabelGrow->enableShadow(Color4B::BLUE,offset);
    }
}

std::string LabelShadowTest::title() const
{
    return "New Label";
}

std::string LabelShadowTest::subtitle() const
{
    return "Testing shadow of label";
}

LabelCharMapTest::LabelCharMapTest()
{
    _time = 0.0f;

    auto label1 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.plist");
    addChild(label1, 0, kTagSprite1);
    label1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    label1->setPosition( Vec2(10,100) );
    label1->setOpacity( 200 );

    auto label2 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.plist");
    addChild(label2, 0, kTagSprite2);
    label2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    label2->setPosition( Vec2(10,200) );
    label2->setOpacity( 32 );

    schedule(CC_CALLBACK_1(LabelCharMapTest::step, this), "step_key");
}

void LabelCharMapTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);

    auto label1 = (Label*)getChildByTag(kTagSprite1);
    label1->setString(string);

    auto label2 = (Label*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    label2->setString(string);
}

std::string LabelCharMapTest::title() const
{
    return "New Label + char map file";
}

std::string LabelCharMapTest::subtitle() const
{
    return "Updating label should be fast.";
}

//------------------------------------------------------------------
//
// LabelCharMapColorTest
//
//------------------------------------------------------------------
LabelCharMapColorTest::LabelCharMapColorTest()
{
    auto label1 = Label::createWithCharMap( "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label1, 0, kTagSprite1);
    label1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    label1->setPosition( Vec2(10,100) );
    label1->setOpacity( 200 );

    auto label2 = Label::createWithCharMap("fonts/tuffy_bold_italic-charmap.plist");
    addChild(label2, 0, kTagSprite2);
    label2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    label2->setPosition( Vec2(10,200) );
    label2->setColor( Color3B::RED );

    auto fade = FadeOut::create(1.0f);
    auto fade_in = fade->reverse();
    auto cb = CallFunc::create(CC_CALLBACK_0(LabelCharMapColorTest::actionFinishCallback, this));
    auto seq = Sequence::create(fade, fade_in, cb, nullptr);
    auto repeat = RepeatForever::create( seq );
    label2->runAction( repeat );    

    _time = 0;

    schedule(CC_CALLBACK_1(LabelCharMapColorTest::step, this), "step_key");
}

void LabelCharMapColorTest::actionFinishCallback()
{
    CCLOG("Action finished");
}

void LabelCharMapColorTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    auto label1 = (Label*)getChildByTag(kTagSprite1);
    label1->setString(string);

    auto label2 = (Label*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    label2->setString( string );    
}

std::string LabelCharMapColorTest::title() const
{
    return "New Label + CharMap";
}

std::string LabelCharMapColorTest::subtitle() const
{
    return "Opacity + Color should work at the same time";
}

LabelCrashTest::LabelCrashTest()
{
    auto size = Director::getInstance()->getWinSize();

    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,true);

    auto label1 = Label::createWithTTF(ttfConfig,"Test崩溃123", TextHAlignment::CENTER, size.width);
    label1->setPosition( Vec2(size.width/2, size.height/2) );
    addChild(label1);
}

std::string LabelCrashTest::title() const
{
    return "New Label Crash Test";
}

std::string LabelCrashTest::subtitle() const
{
    return "Not crash when use character that is not contained in font.";
}

LabelTTFOldNew::LabelTTFOldNew()
{
    auto s = Director::getInstance()->getWinSize();
    float delta = s.height/4;

    auto label1 = Label::createWithSystemFont("Cocos2d-x Label Test", "arial", 24);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(Vec2(s.width/2, delta * 2));
    label1->setColor(Color3B::RED);

    TTFConfig ttfConfig("fonts/arial.ttf", 24);
    auto label2 = Label::createWithTTF(ttfConfig, "Cocos2d-x Label Test");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(Vec2(s.width/2, delta * 2));

    auto drawNode = DrawNode::create();
    auto labelSize = label1->getContentSize();
    auto origin    = Director::getInstance()->getWinSize();
    
    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Vec2 vertices[4]=
    {
        Vec2(origin.width, origin.height),
        Vec2(labelSize.width + origin.width, origin.height),
        Vec2(labelSize.width + origin.width, labelSize.height + origin.height),
        Vec2(origin.width, labelSize.height + origin.height)
    };
    drawNode->drawPoly(vertices, 4, true, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
    
    labelSize = label2->getContentSize();
    origin    = Director::getInstance()->getWinSize();
    
    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    Vec2 vertices2[4]=
    {
        Vec2(origin.width, origin.height),
        Vec2(labelSize.width + origin.width, origin.height),
        Vec2(labelSize.width + origin.width, labelSize.height + origin.height),
        Vec2(origin.width, labelSize.height + origin.height)
    };
    drawNode->drawPoly(vertices2, 4, true, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    
    addChild(drawNode);
}

std::string LabelTTFOldNew::title() const
{
    return "New / Old TTF";
}

std::string LabelTTFOldNew::subtitle() const
{
    return "Comparison between old(red) and new(white) TTF label";
}

LabelFontNameTest::LabelFontNameTest()
{
    auto size = Director::getInstance()->getWinSize();

    auto label1 = Label::create();
    label1->setString("Default Font");
    label1->setPosition( Vec2(size.width/2, size.height * 0.7) );
    addChild(label1);

    auto label3 = Label::createWithSystemFont("Marker Felt","Marker Felt",32);
    label3->setPosition( Vec2(size.width/2, size.height * 0.5) );
    addChild(label3);
}

std::string LabelFontNameTest::title() const
{
    return "New Label Test";
}

std::string LabelFontNameTest::subtitle() const
{
    return "create label by font name,compatible with old labelTTF";
}

LabelAlignmentTest::LabelAlignmentTest()
{
    auto blockSize = Size(200, 160);
    auto s = Director::getInstance()->getWinSize();

    auto pos = Vec2((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2);
    auto colorLayer = LayerColor::create(Color4B(100, 100, 100, 255), blockSize.width, blockSize.height);
    colorLayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    colorLayer->setPosition(pos);

    this->addChild(colorLayer);

    MenuItemFont::setFontSize(30);
    auto menu = Menu::create(
        MenuItemFont::create("Left", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentLeft, this)),
        MenuItemFont::create("Center", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentCenter, this)),
        MenuItemFont::create("Right", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentRight, this)),
        nullptr);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Vec2(50.0f, s.height / 2 - 20));
    this->addChild(menu);

    menu = Menu::create(
        MenuItemFont::create("Top", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentTop, this)),
        MenuItemFont::create("Middle", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentMiddle, this)),
        MenuItemFont::create("Bottom", CC_CALLBACK_1(LabelAlignmentTest::setAlignmentBottom, this)),
        nullptr);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Vec2(s.width - 50, s.height / 2 - 20));
    this->addChild(menu);

    TTFConfig ttfConfig("fonts/arial.ttf", 50);
    _label = Label::createWithTTF(ttfConfig, "abc efg hijk lmn opq rst uvw xyz");
    _label->setDimensions(200, 160);
    _label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _label->setPosition(pos);
    addChild(_label);
}

void LabelAlignmentTest::setAlignmentLeft(Ref* sender)
{
    _label->setHorizontalAlignment(TextHAlignment::LEFT);
}

void LabelAlignmentTest::setAlignmentCenter(Ref* sender)
{
    _label->setHorizontalAlignment(TextHAlignment::CENTER);
}

void LabelAlignmentTest::setAlignmentRight(Ref* sender)
{
    _label->setHorizontalAlignment(TextHAlignment::RIGHT);
}

void LabelAlignmentTest::setAlignmentTop(Ref* sender)
{
    _label->setVerticalAlignment(TextVAlignment::TOP);
}

void LabelAlignmentTest::setAlignmentMiddle(Ref* sender)
{
    _label->setVerticalAlignment(TextVAlignment::CENTER);
}

void LabelAlignmentTest::setAlignmentBottom(Ref* sender)
{
    _label->setVerticalAlignment(TextVAlignment::BOTTOM);
}

std::string LabelAlignmentTest::title() const
{
    return "Testing New Label";
}

std::string LabelAlignmentTest::subtitle() const
{
    return "Test text alignment";
}

LabelIssue4428Test::LabelIssue4428Test()
{
    auto size = Director::getInstance()->getWinSize();

    auto label = Label::createWithBMFont( "fonts/bitmapFontTest3.fnt", "123\n456");
    label->setPosition(Vec2(size.width /2.0f, size.height / 2.0f));
    label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(label);

    int len = label->getStringLength();
    for (int i = 0; i < len; ++i)
    {
        auto sprite = label->getLetter(i);
        if (sprite != nullptr)
        {
            sprite->setFlippedY(true);
        }
    }
}

std::string LabelIssue4428Test::title() const
{
    return "New Label Bugs Test";
}

std::string LabelIssue4428Test::subtitle() const
{
    return "Reorder issue #4428.The label should be flipped vertically.";
}

LabelIssue4999Test::LabelIssue4999Test()
{
    auto label = Label::createWithTTF("Smaller font test", "fonts/arial.ttf",5);
    label->setPosition(VisibleRect::center());
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(label);
}

std::string LabelIssue4999Test::title() const
{
    return "New Label Bugs Test";
}

std::string LabelIssue4999Test::subtitle() const
{
    return "Reorder issue #4999.The label should be display cleanly.";
}

LabelLineHeightTest::LabelLineHeightTest()
{
    auto size = Director::getInstance()->getWinSize();

    auto bg = LayerColor::create(Color4B(200,191,231,255));
    this->addChild(bg);

    TTFConfig ttfConfig("fonts/arial.ttf", 25, GlyphCollection::DYNAMIC,nullptr,false);

    label = Label::createWithTTF(ttfConfig,"Test\nLine\nHeight");
    label->setPosition( Vec2(size.width/2, size.height*0.5f) );
    label->setTextColor( Color4B::RED );
    addChild(label);

    auto slider = ui::Slider::create();
    slider->setTouchEnabled(true);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Vec2(size.width / 2.0f, size.height * 0.15f + slider->getContentSize().height * 2.0f));
    slider->setPercent(label->getLineHeight());
    slider->addEventListener(CC_CALLBACK_2(LabelLineHeightTest::sliderEvent, this));
    addChild(slider);
}

void LabelLineHeightTest::sliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider*  slider = (Slider*)sender;
        label->setLineHeight(slider->getPercent());
    }
}

std::string LabelLineHeightTest::title() const
{
    return "New Label";
}

std::string LabelLineHeightTest::subtitle() const
{
    return "Testing line height of label";
}

LabelAdditionalKerningTest::LabelAdditionalKerningTest()
{
    auto size = Director::getInstance()->getWinSize();

    auto bg = LayerColor::create(Color4B(200,191,231,255));
    this->addChild(bg);

    TTFConfig ttfConfig("fonts/arial.ttf", 40, GlyphCollection::DYNAMIC,nullptr,false);

    label = Label::createWithTTF(ttfConfig,"Test additional kerning");
    label->setPosition(size.width/2, size.height * 0.5f);
    label->setTextColor( Color4B::RED );
    addChild(label);

    auto slider = ui::Slider::create();
    slider->setTouchEnabled(true);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Vec2(size.width / 2.0f, size.height * 0.15f + slider->getContentSize().height * 2.0f));
    slider->setPercent(0);
    slider->addEventListener(CC_CALLBACK_2(LabelAdditionalKerningTest::sliderEvent, this));
    addChild(slider);
}

void LabelAdditionalKerningTest::sliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        Slider*  slider = (Slider*)sender;
        label->setAdditionalKerning(slider->getPercent());
    }
}

std::string LabelAdditionalKerningTest::title() const
{
    return "New Label";
}

std::string LabelAdditionalKerningTest::subtitle() const
{
    return "Testing additional kerning of label";
}

LabelIssue8492Test::LabelIssue8492Test()
{
    auto label = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", "中国中国中国中国中国");
    label->setDimensions(5,100);
    label->setPosition(VisibleRect::center());
    addChild(label);
}

std::string LabelIssue8492Test::title() const
{
    return "Reorder issue #8492";
}

std::string LabelIssue8492Test::subtitle() const
{
    return "Work fine when dimensions are not enough to fit one character";
}

LabelMultilineWithOutline::LabelMultilineWithOutline()
{
    auto label =  Label::createWithTTF("Multi-line text\nwith\noutline feature", "fonts/arial.ttf", 24);
    label->enableOutline(Color4B::ORANGE,1);
    label->setPosition(VisibleRect::center());
    addChild(label);
}

std::string LabelMultilineWithOutline::title() const
{
    return "Reorder issue #9095";
}

std::string LabelMultilineWithOutline::subtitle() const
{
    return "end in string 'outline feature'";
}


LabelIssue9255Test::LabelIssue9255Test()
{
    Size s = Director::getInstance()->getWinSize();
    auto parent = Node::create();
    parent->setPosition(s.width/2, s.height/2);
    parent->setVisible(false);
    this->addChild(parent);

    auto label =  Label::createWithTTF("Crashed!!!", "fonts/HKYuanMini.ttf", 24);
    label->setPosition(VisibleRect::center());
    parent->addChild(label);
}

std::string LabelIssue9255Test::title() const
{
    return "Test for Issue #9255";
}

std::string LabelIssue9255Test::subtitle() const
{
    return "switch to desktop and switch back. Crashed!!!";
}

LabelSmallDimensionsTest::LabelSmallDimensionsTest()
{
    auto label = Label::createWithSystemFont("Hello World!", "fonts/arial.ttf", 24, Size(30.0f,100.0f));
    label->setPosition(VisibleRect::center());
    addChild(label);
}

std::string LabelSmallDimensionsTest::title() const
{
    return "New Label + System font";
}

std::string LabelSmallDimensionsTest::subtitle() const
{
    return "Testing create Label with small dimensions.Program should not dead loop";
}

LabelIssue10089Test::LabelIssue10089Test()
{
    auto center = VisibleRect::center();

    auto labelA = Label::createWithSystemFont("create label with system font", "fonts/arial.ttf", 24);
    auto size = labelA->getContentSize();
    labelA->setDimensions(size.width, size.height);
    labelA->setPosition(center.x, center.y + 50);
    addChild(labelA);

    auto labelB = Label::createWithTTF("create label with TTF", "fonts/arial.ttf", 24);
    size = labelB->getContentSize();
    labelB->setDimensions(size.width, size.height);
    labelB->setPosition(center.x, center.y - 50);
    addChild(labelB);
}

std::string LabelIssue10089Test::title() const
{
    return "Test for Issue #10089";
}

std::string LabelIssue10089Test::subtitle() const
{
    return "Should be able to see two single-line text";
}

LabelSystemFontColor::LabelSystemFontColor()
{
    auto size = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithSystemFont("Color4B::Red", "fonts/arial.ttf", 20);
    label1->setPosition(Vec2(size.width / 2, size.height * 0.3f));
    label1->setTextColor(Color4B::RED);
    addChild(label1);

    auto label2 = Label::createWithSystemFont("Color4B::Green", "fonts/arial.ttf", 20);
    label2->setPosition(Vec2(size.width / 2, size.height * 0.4f));
    label2->setTextColor(Color4B::GREEN);
    addChild(label2);

    auto label3 = Label::createWithSystemFont("Color4B::Blue", "fonts/arial.ttf", 20);
    label3->setPosition(Vec2(size.width / 2, size.height * 0.5f));
    label3->setTextColor(Color4B::BLUE);
    addChild(label3);

    auto label4 = Label::createWithSystemFont("Color4B(0, 0, 255, 100)", "fonts/arial.ttf", 20);
    label4->setPosition(Vec2(size.width / 2, size.height * 0.6f));
    label4->setTextColor(Color4B(0, 0, 255, 100));
    addChild(label4);
}

std::string LabelSystemFontColor::title() const
{
    return "New Label + system font";
}

std::string LabelSystemFontColor::subtitle() const
{
    return "Testing text color of system font";
}

LabelIssue10773Test::LabelIssue10773Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("create label with TTF", "fonts/arial.ttf", 24);
    label->getLetter(5);
    label->setString("Hi");
    label->setPosition(center.x, center.y);
    addChild(label);
}

std::string LabelIssue10773Test::title() const
{
    return "Test for Issue #10773";
}

std::string LabelIssue10773Test::subtitle() const
{
    return "Should not crash!";
}

LabelIssue11576Test::LabelIssue11576Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("abcdefg", "fonts/arial.ttf", 24);
    for (int index = 0; index < label->getStringLength(); ++index)
    {
        label->getLetter(index);
    }

    this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([label](){
        label->setString("Hello World!");
    }), nullptr));

    label->setPosition(center.x, center.y);
    addChild(label);
}

std::string LabelIssue11576Test::title() const
{
    return "Test for Issue #11576";
}

std::string LabelIssue11576Test::subtitle() const
{
    return "You should see another string displayed correctly after 2 seconds.";
}

LabelIssue11699Test::LabelIssue11699Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("中国", "fonts/HKYuanMini.ttf", 150);
    label->enableOutline(Color4B::RED, 2);
    label->setPosition(center.x, center.y);
    addChild(label);
}

std::string LabelIssue11699Test::title() const
{
    return "Test for Issue #11699";
}

std::string LabelIssue11699Test::subtitle() const
{
    return "Outline should match with the characters exactly.";
}

LabelIssue12409Test::LabelIssue12409Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("abcdefghijklmn", "fonts/arial.ttf", 30);
    label->setWidth(70);
    label->setLineBreakWithoutSpace(true);
    label->setPosition(center.x, center.y);
    addChild(label);

    auto labelSize = label->getContentSize();
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 labelOrigin;
    labelOrigin.x = winSize.width / 2 - (labelSize.width / 2);
    labelOrigin.y = winSize.height / 2 - (labelSize.height / 2);
    Vec2 vertices[4] =
    {
        Vec2(labelOrigin.x, labelOrigin.y),
        Vec2(labelOrigin.x + labelSize.width, labelOrigin.y),
        Vec2(labelOrigin.x + labelSize.width, labelOrigin.y + labelSize.height),
        Vec2(labelOrigin.x, labelOrigin.y + labelSize.height)
    };

    auto drawNode = DrawNode::create();
    drawNode->drawPoly(vertices, 4, true, Color4F::WHITE);
    addChild(drawNode);
}

std::string LabelIssue12409Test::title() const
{
    return "Test for Issue #12409";
}

std::string LabelIssue12409Test::subtitle() const
{
    return "Testing auto-wrapping without space.";
}

LabelAddChildTest::LabelAddChildTest()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("Label with child node:", "fonts/arial.ttf", 24);
    label->setPosition(center.x, center.y);
    addChild(label);

    auto jump = JumpBy::create(1.0f, Vec2::ZERO, 60, 1);
    auto jump_4ever = RepeatForever::create(jump);
    label->runAction(jump_4ever);

    auto spite = Sprite::create("Images/SpookyPeas.png");
    spite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    spite->setPosition(label->getContentSize().width, label->getContentSize().height/2);
    label->addChild(spite);
}

std::string LabelAddChildTest::title() const
{
    return "Label support add child nodes";
}

LabelIssue12775Test::LabelIssue12775Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("Hello", "fonts/xingkai-incomplete.ttf", 30);
    label->setPosition(center.x, center.y);
    addChild(label);
}

std::string LabelIssue12775Test::title() const
{
    return "Test for Issue #12775";
}

std::string LabelIssue12775Test::subtitle() const
{
    return "Should not crash if the font not contain a Unicode charmap.";
}

LabelIssue11585Test::LabelIssue11585Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", 24);
    label->setPosition(center.x, center.y);
    addChild(label);

    label->getLetter(0)->setColor(Color3B::RED);
    label->getLetter(1)->setColor(Color3B::GREEN);
    label->getLetter(2)->setColor(Color3B::BLUE);
    auto action = RepeatForever::create(Sequence::create( 
        FadeOut::create(2), FadeIn::create(2),nullptr));
    label->runAction(action);
}

std::string LabelIssue11585Test::title() const
{
    return "Test for Issue #11585";
}

std::string LabelIssue11585Test::subtitle() const
{
    return "The color of letter should not be overridden by fade action.";
}

LabelIssue10688Test::LabelIssue10688Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("Glow MenuItemLabel", "fonts/arial.ttf", 30);
    label->setTextColor(Color4B::RED);
    label->enableGlow(Color4B::YELLOW);
    auto menuItem1 = MenuItemLabel::create(label, [](Ref*){});
    menuItem1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    menuItem1->setPosition(center.x - label->getContentSize().width/2, center.y);

    auto menu = Menu::create(menuItem1, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
}

std::string LabelIssue10688Test::title() const
{
    return "Test for Issue #10688";
}

std::string LabelIssue10688Test::subtitle() const
{
    return "The MenuItemLabel should be displayed in the middle of the screen.";
}

LabelIssue13202Test::LabelIssue13202Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("asdfghjklzxcvbnmqwertyuiop", "fonts/arial.ttf", 150);
    label->setPosition(center);
    addChild(label);

    label->getContentSize();
    label->setString("A");
    this->scheduleOnce([](float dt){
        FontAtlasCache::purgeCachedData();
    }, 0.15f, "FontAtlasCache::purgeCachedData");
}

std::string LabelIssue13202Test::title() const
{
    return "Test for Issue #13202";
}

std::string LabelIssue13202Test::subtitle() const
{
    return "FontAtlasCache::purgeCachedData should not cause crash.";
}

LabelIssue9500Test::LabelIssue9500Test()
{
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("Spaces should not be lost", "fonts/Fingerpop.ttf", 20);
    label->setPosition(center);
    addChild(label);
}

std::string LabelIssue9500Test::title() const
{
    return "Test for Issue #9500";
}

std::string LabelIssue9500Test::subtitle() const
{
    return "Spaces should not be lost if label created with Fingerpop.ttf";
}

ControlStepper *LabelLayoutBaseTest::makeControlStepper()
{
    auto minusSprite       = Sprite::create("extensions/stepper-minus.png");
    auto plusSprite        = Sprite::create("extensions/stepper-plus.png");
    
    return ControlStepper::create(minusSprite, plusSprite);
}

LabelLayoutBaseTest::LabelLayoutBaseTest()
{
    auto size = Director::getInstance()->getVisibleSize();
    
    this->initTestLabel(size);

    this->initFontSizeChange(size);
    this->initToggleLabelTypeOption(size);

    this->initWrapOption(size);

    this->initAlignmentOption(size);

    this->initDrawNode(size);

    this->initSliders(size);
}

void LabelLayoutBaseTest::initFontSizeChange(const cocos2d::Size& size)
{
    auto fontSizeLabel = Label::createWithSystemFont("font size:20", "Arial", 10);
    fontSizeLabel->setName("fontSize");

    ControlStepper *stepper   = this->makeControlStepper();
    stepper->setPosition(size.width * 0.5 - stepper->getContentSize().width / 2,
                         size.height * 0.8);
    stepper->setValue(20);
    stepper->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(LabelLayoutBaseTest::valueChanged),
                                                 Control::EventType::VALUE_CHANGED);
    this->addChild(stepper);
    stepper->setName("stepper");
    stepper->setScale(0.5);

    fontSizeLabel->setPosition(stepper->getPosition() -
                               Vec2(stepper->getContentSize().width/2  + fontSizeLabel->getContentSize().width/2,0.0f));
    this->addChild(fontSizeLabel);
}

void LabelLayoutBaseTest::initWrapOption(const cocos2d::Size& size)
{
    auto label = Label::createWithSystemFont("Enable Wrap:", "Arial", 10);
    label->setColor(Color3B::WHITE);
    label->setPosition(Vec2(size.width * 0.8f - 100, size.height * 0.8f));
    this->addChild(label);

    CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                          "cocosui/check_box_normal_press.png",
                                          "cocosui/check_box_active.png",
                                          "cocosui/check_box_normal_disable.png",
                                          "cocosui/check_box_active_disable.png");
    checkBox->setPosition(Vec2(size.width * 0.8f - 55, size.height * 0.8f));
    checkBox->setScale(0.5);
    checkBox->setSelected(true);
    checkBox->setName("toggleWrap");

    checkBox->addEventListener([=](Ref* ref, CheckBox::EventType event){
        if (event == CheckBox::EventType::SELECTED) {
            _label->enableWrap(true);
        }else{
            _label->enableWrap(false);
        }
        this->updateDrawNodeSize(_label->getContentSize());
    });
    this->addChild(checkBox);
}

void LabelLayoutBaseTest::initToggleLabelTypeOption(const cocos2d::Size& size)
{
    auto label = Label::createWithSystemFont("Toggle Label Type:", "Arial", 10);
    label->setColor(Color3B::WHITE);
    label->setPosition(Vec2(size.width * 0.8f + 15, size.height * 0.8f));
    this->addChild(label);
    
    CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                          "cocosui/check_box_normal_press.png",
                                          "cocosui/check_box_active.png",
                                          "cocosui/check_box_normal_disable.png",
                                          "cocosui/check_box_active_disable.png");
    checkBox->setPosition(Vec2(size.width * 0.8f + 70, size.height * 0.8f));
    checkBox->setScale(0.5);
    checkBox->setName("toggleType");
    checkBox->setSelected(true);

   auto stepper = (ControlStepper*)this->getChildByName("stepper");

    checkBox->addEventListener([=](Ref* ref, CheckBox::EventType event){
       float fontSize = stepper->getValue();

        if (event == CheckBox::EventType::SELECTED) {
            _labelType = 0;
            auto ttfConfig = _label->getTTFConfig();
            ttfConfig.fontSize = fontSize;
            _label->setTTFConfig(ttfConfig);
        }else{
            _labelType = 1;
            _label->setBMFontFilePath("fonts/enligsh-chinese.fnt");
            _label->setBMFontSize(fontSize);
        }
    });
    this->addChild(checkBox);

}

void LabelLayoutBaseTest::initAlignmentOption(const cocos2d::Size& size)
{
    //add text alignment settings
    MenuItemFont::setFontSize(30);
    auto menu = Menu::create(
        MenuItemFont::create("Left", CC_CALLBACK_1(LabelLayoutBaseTest::setAlignmentLeft, this)),
        MenuItemFont::create("Center", CC_CALLBACK_1(LabelLayoutBaseTest::setAlignmentCenter, this)),
        MenuItemFont::create("Right", CC_CALLBACK_1(LabelLayoutBaseTest::setAlignmentRight, this)),
        nullptr);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Vec2(50.0f, size.height / 2 - 20));
    this->addChild(menu);

    menu = Menu::create(
        MenuItemFont::create("Top", CC_CALLBACK_1(LabelLayoutBaseTest::setAlignmentTop, this)),
        MenuItemFont::create("Middle", CC_CALLBACK_1(LabelLayoutBaseTest::setAlignmentMiddle, this)),
        MenuItemFont::create("Bottom", CC_CALLBACK_1(LabelLayoutBaseTest::setAlignmentBottom, this)),
        nullptr);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(Vec2(size.width - 50, size.height / 2 - 20));
    this->addChild(menu);
}

void LabelLayoutBaseTest::initSliders(const cocos2d::Size& size)
{
    auto slider = ui::Slider::create();
    slider->setTag(1);
    slider->setTouchEnabled(true);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Vec2(size.width / 2.0f, size.height * 0.15f + slider->getContentSize().height * 2.0f - 5));
    slider->setPercent(52);
    addChild(slider);

    auto slider2 = ui::Slider::create();
    slider2->setTag(2);
    slider2->setTouchEnabled(true);
    slider2->loadBarTexture("cocosui/sliderTrack.png");
    slider2->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider2->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider2->setPosition(Vec2(size.width * 0.2f, size.height / 2.0f));
    slider2->setRotation(90);
    slider2->setPercent(52);
    addChild(slider2);
    auto winSize = Director::getInstance()->getVisibleSize();

    slider->addEventListener([=](Ref* ref, Slider::EventType event){
        float percent = slider->getPercent();
        auto labelSize = _label->getContentSize();
        auto drawNodeSize = Size(percent / 100.0 * winSize.width, labelSize.height);
        if(drawNodeSize.width <=0){
            drawNodeSize.width = 0.1f;
        }
        _label->setDimensions(drawNodeSize.width, drawNodeSize.height);
        this->updateDrawNodeSize(drawNodeSize);
    });

    slider2->addEventListener([=](Ref* ref, Slider::EventType event){
        float percent = slider2->getPercent();
        auto labelSize = _label->getContentSize();
        auto drawNodeSize = Size( labelSize.width, percent / 100.0 * winSize.height);
        if(drawNodeSize.height <= 0){
            drawNodeSize.height = 0.1f;
        }
        _label->setDimensions(drawNodeSize.width, drawNodeSize.height);
        this->updateDrawNodeSize(drawNodeSize);
    });
}

void LabelLayoutBaseTest::initTestLabel(const cocos2d::Size& size)
{
    auto center = VisibleRect::center();
    _label = Label::createWithTTF("五六七八This is a very long sentence一二三四.", "fonts/HKYuanMini.ttf", 20);
    _label->setDimensions(size.width/2, size.height/2);
    _label->setPosition(center);
    _label->setName("Label");
    _label->setString("五六七八This is a very long sentence一二三.");
    addChild(_label);
    _labelType = 0;
}

void LabelLayoutBaseTest::initDrawNode(const cocos2d::Size& size)
{
    _drawNode = DrawNode::create();

    _drawNode->setTag(3);
    addChild(_drawNode);
    this->updateDrawNodeSize(_label->getContentSize());
}


void LabelLayoutBaseTest::setAlignmentLeft(Ref* sender)
{
    _label->setHorizontalAlignment(TextHAlignment::LEFT);
}

void LabelLayoutBaseTest::setAlignmentCenter(Ref* sender)
{
    _label->setHorizontalAlignment(TextHAlignment::CENTER);
}

void LabelLayoutBaseTest::setAlignmentRight(Ref* sender)
{
    _label->setHorizontalAlignment(TextHAlignment::RIGHT);
}

void LabelLayoutBaseTest::setAlignmentTop(Ref* sender)
{
    _label->setVerticalAlignment(TextVAlignment::TOP);
}

void LabelLayoutBaseTest::setAlignmentMiddle(Ref* sender)
{
    _label->setVerticalAlignment(TextVAlignment::CENTER);
}

void LabelLayoutBaseTest::setAlignmentBottom(Ref* sender)
{
    _label->setVerticalAlignment(TextVAlignment::BOTTOM);
}


void LabelLayoutBaseTest::valueChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType controlEvent)
{
    ControlStepper* pControl = (ControlStepper*)sender;
    // Change value of label.
    auto fontSizeLabel = (Label*)this->getChildByName("fontSize");
    float fontSize = (float)pControl->getValue();
    fontSizeLabel->setString(StringUtils::format("font size:%d", (int)fontSize));
    
    if (_labelType == 0) {
        auto ttfConfig = _label->getTTFConfig();
        ttfConfig.fontSize = fontSize;
        _label->setTTFConfig(ttfConfig);
    }else if(_labelType == 1){
        _label->setBMFontSize(fontSize);
    }else if (_labelType == 2) {
        _label->setSystemFontSize(fontSize);
    }
    this->updateDrawNodeSize(_label->getContentSize());
    
    //FIXME::When calling getLetter, the label Overflow feature will be invalid.
//    auto letterSprite = _label->getLetter(1);
//    auto moveBy = ScaleBy::create(1.0,2.0);
//    letterSprite->stopAllActions();
//    letterSprite->runAction(Sequence::create(moveBy, moveBy->clone()->reverse(), nullptr ));
//    
//    CCLOG("label line height = %f", _label->getLineHeight());
}

void LabelLayoutBaseTest::updateDrawNodeSize(const cocos2d::Size &drawNodeSize)
{
    auto origin    = Director::getInstance()->getWinSize();
    auto labelSize = _label->getContentSize();

    origin.width = origin.width   / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);

    Vec2 vertices[4]=
    {
        Vec2(origin.width, origin.height),
        Vec2(drawNodeSize.width + origin.width, origin.height),
        Vec2(drawNodeSize.width + origin.width, drawNodeSize.height + origin.height),
        Vec2(origin.width, drawNodeSize.height + origin.height)
    };
    _drawNode->clear();
    _drawNode->drawLine(vertices[0], vertices[1], Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    _drawNode->drawLine(vertices[0], vertices[3], Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    _drawNode->drawLine(vertices[2], vertices[3], Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    _drawNode->drawLine(vertices[1], vertices[2], Color4F(1.0f, 1.0f, 1.0f, 1.0f));

}

LabelWrapByWordTest::LabelWrapByWordTest()
{
    _label->setLineSpacing(5);
    _label->setAdditionalKerning(2);
    _label->setVerticalAlignment(TextVAlignment::CENTER);
    _label->setOverflow(Label::Overflow::CLAMP);

}

std::string LabelWrapByWordTest::title() const
{
    return "Clamp content Test: Word Wrap";
}

std::string LabelWrapByWordTest::subtitle() const
{
    return "";
}

LabelWrapByCharTest::LabelWrapByCharTest()
{
   _label->setLineBreakWithoutSpace(true);
    _label->setString("五六七八This \nis a very long sentence一二三四.");
    _label->setLineSpacing(5);
    _label->setAdditionalKerning(2);
    _label->setVerticalAlignment(TextVAlignment::TOP);
    _label->setOverflow(Label::Overflow::CLAMP);

}

std::string LabelWrapByCharTest::title() const
{
    return "Clamp content Test: Char Wrap";
}

std::string LabelWrapByCharTest::subtitle() const
{
    return "";
}

/////////////////////////////////////////////////

LabelWrapNoBreakSpaceTest::LabelWrapNoBreakSpaceTest()
{
    _label->setLineBreakWithoutSpace(false);
    const char* no_break_space_utf8 = "\xC2\xA0"; // 0xA0 - no-break space
    auto str = StringUtils::format("The price is $%s1.25. \n\nthe space between \"$\" and \"1.25\" is a no break space.", no_break_space_utf8);
    _label->setString(str);
    _label->setVerticalAlignment(TextVAlignment::TOP);
    _label->setOverflow(Label::Overflow::CLAMP);
}

std::string LabelWrapNoBreakSpaceTest::title() const
{
    return "Wrap Test: No break space";
}

std::string LabelWrapNoBreakSpaceTest::subtitle() const
{
    return "";
}

/////////////////////////////////////////////////

LabelShrinkByWordTest::LabelShrinkByWordTest()
{
    _label->setLineSpacing(5);
    _label->setAdditionalKerning(2);
    _label->setString("This is  Hello World  hehe I love 一二三");
    _label->setVerticalAlignment(TextVAlignment::TOP);
    _label->setOverflow(Label::Overflow::SHRINK);
}

std::string LabelShrinkByWordTest::title() const
{
    return "Shrink content Test: Word Wrap";
}

std::string LabelShrinkByWordTest::subtitle() const
{
    return "";
}

LabelShrinkByCharTest::LabelShrinkByCharTest()
{
    _label->setLineSpacing(5);
    _label->setAdditionalKerning(2);
    _label->setLineBreakWithoutSpace(true);
    _label->setString("This is  Hello World  hehe I love 一二三");
    _label->setVerticalAlignment(TextVAlignment::CENTER);
    _label->setOverflow(Label::Overflow::SHRINK);
}

std::string LabelShrinkByCharTest::title() const
{
    return "Shrink content Test: Char Wrap";
}

std::string LabelShrinkByCharTest::subtitle() const
{
    return "";
}

LabelResizeTest::LabelResizeTest()
{
    _label->setLineSpacing(5);
    _label->setAdditionalKerning(2);
    _label->setVerticalAlignment(TextVAlignment::TOP);
    _label->setOverflow(Label::Overflow::RESIZE_HEIGHT);


    this->updateDrawNodeSize(_label->getContentSize());

    auto slider1 = (ui::Slider*)this->getChildByTag(1);

     auto slider2 = (ui::Slider*)this->getChildByTag(2);
     slider2->setVisible(false);
    
    auto winSize = Director::getInstance()->getVisibleSize();
    slider1->addEventListener([=](Ref* ref, Slider::EventType event){
        float percent = slider1->getPercent();
        auto drawNodeSize = Size(percent / 100.0 * winSize.width,_label->getContentSize().height);
        if(drawNodeSize.height <= 0){
            drawNodeSize.height = 0.1f;
        }
        _label->setDimensions(drawNodeSize.width, drawNodeSize.height);
        this->updateDrawNodeSize(drawNodeSize);
    });

    auto stepper = (ControlStepper*)this->getChildByName("stepper");
    stepper->setValue(12);
    
    auto label = Label::createWithSystemFont("Char Line break:", "Arial", 10);
    label->setColor(Color3B::WHITE);
    label->setPosition(Vec2(winSize.width * 0.1f, winSize.height * 0.8f));
    this->addChild(label);
    
    CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                          "cocosui/check_box_normal_press.png",
                                          "cocosui/check_box_active.png",
                                          "cocosui/check_box_normal_disable.png",
                                          "cocosui/check_box_active_disable.png");
    checkBox->setPosition(Vec2(winSize.width * 0.2f , winSize.height * 0.8f));
    checkBox->setScale(0.5);
    checkBox->setSelected(false);
    checkBox->setName("LineBreak");
    
    checkBox->addEventListener([=](Ref* ref, CheckBox::EventType event){
        if (event == CheckBox::EventType::SELECTED) {
            _label->setLineBreakWithoutSpace(true);
        }else{
            _label->setLineBreakWithoutSpace(false);
        }
        this->updateDrawNodeSize(_label->getContentSize());
    });
    this->addChild(checkBox);

}

std::string LabelResizeTest::title() const
{
    return "Resize content Test";
}

std::string LabelResizeTest::subtitle() const
{
    return "";
}

LabelToggleTypeTest::LabelToggleTypeTest()
{
    _label->setLineSpacing(5);
    _label->setAdditionalKerning(2);
    _label->setVerticalAlignment(TextVAlignment::CENTER);
    _label->setOverflow(Label::Overflow::NONE);


    this->updateDrawNodeSize(_label->getContentSize());

    auto slider1 = (ui::Slider*)this->getChildByTag(1);

     auto slider2 = (ui::Slider*)this->getChildByTag(2);
     slider2->setVisible(false);

    auto winSize = Director::getInstance()->getVisibleSize();
    slider1->addEventListener([=](Ref* ref, Slider::EventType event){
        float percent = slider1->getPercent();
        auto drawNodeSize = Size(percent / 100.0 * winSize.width,_label->getContentSize().height);
        if(drawNodeSize.height <= 0){
            drawNodeSize.height = 0.1f;
        }
        _label->setDimensions(drawNodeSize.width, drawNodeSize.height);
        this->updateDrawNodeSize(drawNodeSize);
    });

    auto stepper = (ControlStepper*)this->getChildByName("stepper");
    stepper->setValue(12);

    auto label = Label::createWithSystemFont("Char Line break:", "Arial", 10);
    label->setColor(Color3B::WHITE);
    label->setPosition(Vec2(winSize.width * 0.1f, winSize.height * 0.8f));
    this->addChild(label);

    CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                          "cocosui/check_box_normal_press.png",
                                          "cocosui/check_box_active.png",
                                          "cocosui/check_box_normal_disable.png",
                                          "cocosui/check_box_active_disable.png");
    checkBox->setPosition(Vec2(winSize.width * 0.2f , winSize.height * 0.8f));
    checkBox->setScale(0.5);
    checkBox->setSelected(false);
    checkBox->setName("LineBreak");

    checkBox->addEventListener([=](Ref* ref, CheckBox::EventType event){
        if (event == CheckBox::EventType::SELECTED) {
            _label->setLineBreakWithoutSpace(true);
        }else{
            _label->setLineBreakWithoutSpace(false);
        }
        this->updateDrawNodeSize(_label->getContentSize());
    });
    this->addChild(checkBox);

    this->initToggleCheckboxes();
}

void LabelToggleTypeTest::initToggleCheckboxes()
{
    const float BUTTON_WIDTH = 100;
    float startPosX = 0;
    Size winSize = Director::getInstance()->getVisibleSize();

    // Create a radio button group
    auto radioButtonGroup = RadioButtonGroup::create();
    this->addChild(radioButtonGroup);

    // Create the radio buttons
    static const int NUMBER_OF_BUTTONS = 4;
    startPosX = winSize.width / 2.0f - (NUMBER_OF_BUTTONS - 1 ) * 0.5 * BUTTON_WIDTH - 30;
    std::vector<std::string> labelTypes = {"Normal", "Clamp", "Shrink", "RESIZE"};
    
    for(int i = 0; i < NUMBER_OF_BUTTONS; ++i)
    {

        RadioButton* radioButton = RadioButton::create("cocosui/radio_button_off.png", "cocosui/radio_button_on.png");
        float posX = startPosX + BUTTON_WIDTH * i;
        radioButton->setPosition(Vec2(posX, winSize.height / 2.0f + 70));
        radioButton->setScale(1.2f);
        radioButton->addEventListener(CC_CALLBACK_2(LabelToggleTypeTest::onChangedRadioButtonSelect, this));
        radioButton->setTag(i);
        radioButtonGroup->addRadioButton(radioButton);
        this->addChild(radioButton);
        
        auto label = Label::createWithSystemFont(labelTypes.at(i), "Arial", 20);
        label->setPosition(radioButton->getPosition() + Vec2(50.0f,0.0f));
        this->addChild(label);
    }
}

std::string LabelToggleTypeTest::title() const
{
    return "Toggle Label Type Test";
}

std::string LabelToggleTypeTest::subtitle() const
{
    return "";
}


void LabelToggleTypeTest::onChangedRadioButtonSelect(RadioButton* radioButton, RadioButton::EventType type)
{
    if(radioButton == nullptr)
    {
        return;
    }
    
    switch (type)
    {
    case RadioButton::EventType::SELECTED:
    {
        switch (radioButton->getTag()) {
            case 0:
                _label->setOverflow(Label::Overflow::NONE);
                break;
            case 1:
                _label->setOverflow(Label::Overflow::CLAMP);
                break;
            case 2:
                _label->setOverflow(Label::Overflow::SHRINK);
                break;
            case 3:
                _label->setOverflow(Label::Overflow::RESIZE_HEIGHT);
                break;
            default:
                break;
        }
        break;
    }
    default:
        break;
    }
    auto checkbox = (CheckBox*)(this->getChildByName("toggleWrap"));
    checkbox->setSelected(_label->isWrapEnabled());
    this->updateDrawNodeSize(_label->getContentSize());
}

LabelSystemFontTest::LabelSystemFontTest()
{
    _label->setLineSpacing(5);
    _label->setVerticalAlignment(TextVAlignment::CENTER);
    _label->setOverflow(Label::Overflow::NONE);
    _label->setSystemFontName("Hiragino Sans GB");
    _label->setSystemFontSize(20);
    _label->enableOutline(Color4B::RED, 1.0);
    _label->setString("This is a very\n 我爱你中国\n long sentence");
    _labelType = 2;
    
    auto stepper = (ControlStepper*)this->getChildByName("stepper");
    stepper->setEnabled(true);
    
    auto checkbox = (CheckBox*)(this->getChildByName("toggleType"));
    checkbox->setEnabled(false);

    this->updateDrawNodeSize(_label->getContentSize());

    auto slider1 = (ui::Slider*)this->getChildByTag(1);

    auto winSize = Director::getInstance()->getVisibleSize();
    slider1->addEventListener([=](Ref* ref, Slider::EventType event){
        float percent = slider1->getPercent();
        auto drawNodeSize = Size(percent / 100.0 * winSize.width,_label->getContentSize().height);
        if(drawNodeSize.height <= 0){
            drawNodeSize.height = 0.1f;
        }
        _label->setDimensions(drawNodeSize.width, drawNodeSize.height);
        this->updateDrawNodeSize(drawNodeSize);
    });


    auto label = Label::createWithSystemFont("char Line break:", "Arial", 10);
    label->setColor(Color3B::WHITE);
    label->setPosition(Vec2(winSize.width * 0.1f, winSize.height * 0.8f));
    this->addChild(label);

    CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                          "cocosui/check_box_normal_press.png",
                                          "cocosui/check_box_active.png",
                                          "cocosui/check_box_normal_disable.png",
                                          "cocosui/check_box_active_disable.png");
    checkBox->setPosition(Vec2(winSize.width * 0.2f , winSize.height * 0.8f));
    checkBox->setScale(0.5);
    checkBox->setSelected(false);
    checkBox->setName("LineBreak");

    checkBox->addEventListener([=](Ref* ref, CheckBox::EventType event){
        if (event == CheckBox::EventType::SELECTED) {
            _label->setLineBreakWithoutSpace(true);
        }else{
            _label->setLineBreakWithoutSpace(false);
        }
        this->updateDrawNodeSize(_label->getContentSize());
    });
    this->addChild(checkBox);

    this->initToggleCheckboxes();

    auto checkboxToggleWrap = (CheckBox*)(this->getChildByName("toggleWrap"));
    checkboxToggleWrap->setEnabled(true);
}

void LabelSystemFontTest::initToggleCheckboxes()
{
    const float BUTTON_WIDTH = 100;
    float startPosX = 0;
    Size winSize = Director::getInstance()->getVisibleSize();

    // Create a radio button group
    auto radioButtonGroup = RadioButtonGroup::create();
    this->addChild(radioButtonGroup);

    // Create the radio buttons
    static const int NUMBER_OF_BUTTONS = 4;
    startPosX = winSize.width / 2.0f - (NUMBER_OF_BUTTONS - 1 ) * 0.5 * BUTTON_WIDTH - 30;
    std::vector<std::string> labelTypes = {"Normal", "Clamp", "Shrink", "RESIZE"};

    for(int i = 0; i < NUMBER_OF_BUTTONS; ++i)
    {

        RadioButton* radioButton = RadioButton::create("cocosui/radio_button_off.png", "cocosui/radio_button_on.png");
        float posX = startPosX + BUTTON_WIDTH * i;
        radioButton->setPosition(Vec2(posX, winSize.height / 2.0f + 70));
        radioButton->setScale(1.2f);
        radioButton->addEventListener(CC_CALLBACK_2(LabelSystemFontTest::onChangedRadioButtonSelect, this));
        radioButton->setTag(i);
        radioButtonGroup->addRadioButton(radioButton);
        this->addChild(radioButton);

        auto label = Label::createWithSystemFont(labelTypes.at(i), "Arial", 20);
        label->setPosition(radioButton->getPosition() + Vec2(50.0f,0.0f));
        this->addChild(label);
    }
}

std::string LabelSystemFontTest::title() const
{
    return "System Font Test";
}

std::string LabelSystemFontTest::subtitle() const
{
    return "";
}


void LabelSystemFontTest::onChangedRadioButtonSelect(RadioButton* radioButton, RadioButton::EventType type)
{
    if(radioButton == nullptr)
    {
        return;
    }

    switch (type)
    {
    case RadioButton::EventType::SELECTED:
    {
        switch (radioButton->getTag()) {
            case 0:
                _label->setOverflow(Label::Overflow::NONE);
                break;
            case 1:
                _label->setOverflow(Label::Overflow::CLAMP);
                break;
            case 2:
                _label->setOverflow(Label::Overflow::SHRINK);
                break;
            case 3:
                _label->setOverflow(Label::Overflow::RESIZE_HEIGHT);
                break;
            default:
                break;
        }
        break;
    }
    default:
        break;
    }
    this->updateDrawNodeSize(_label->getContentSize());
}

LabelCharMapFontTest::LabelCharMapFontTest()
{
    _label->setLineSpacing(5);
    _label->setVerticalAlignment(TextVAlignment::CENTER);
    _label->setOverflow(Label::Overflow::NONE);
    _label->setCharMap("fonts/tuffy_bold_italic-charmap.plist");
    _label->setString("Hello World, This is a char map test.");
    _label->setScale(0.5f);

    auto stepper = (ControlStepper*)this->getChildByName("stepper");
    stepper->setEnabled(true);

    auto checkbox = (CheckBox*)(this->getChildByName("toggleType"));
    checkbox->setEnabled(false);

    this->updateDrawNodeSize(_label->getContentSize());

}


std::string LabelCharMapFontTest::title() const
{
    return "CharMap Font Test";
}

std::string LabelCharMapFontTest::subtitle() const
{
    return "";
}

LabelIssue13846Test::LabelIssue13846Test()
{
    auto center = VisibleRect::center();
    
    auto label = Label::createWithTTF("12345", "fonts/arial.ttf", 26);
    label->setPosition(center);
    addChild(label);
    
    label->getLetter(2)->setVisible(false);
}

std::string LabelIssue13846Test::title() const
{
    return "Test for Issue #13846";
}

std::string LabelIssue13846Test::subtitle() const
{
    return "Test hide label's letter,the label should display '12 45' as expected";
}

//
//

LabelRichText::LabelRichText()
{
    auto center = VisibleRect::center();

    auto richText2 = RichText::createWithXML("Mixing <b>UIRichText</b> with non <i>UIWidget</i> code. For more samples, see the UIRichTextTest.cpp file");
    if (richText2)
    {
        richText2->ignoreContentAdaptWithSize(false);
        richText2->setContentSize(Size(400.0f, 400.0f));
        richText2->setPosition(center);

        addChild(richText2);
    }
}

std::string LabelRichText::title() const
{
    return "RichText";
}

std::string LabelRichText::subtitle() const
{
    return "Testing RichText";
}

LabelItalics::LabelItalics()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "hello non-italics", TextHAlignment::CENTER, s.width);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(Vec2(s.width/2, s.height*4/6));
    // you can enable italics by calling this method

    _label1a = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "hello italics", TextHAlignment::CENTER, s.width);
    addChild(_label1a, 0, kTagBitmapAtlas1);
    _label1a->setPosition(Vec2(s.width/2, s.height*3/6));
    // you can enable italics by calling this method
    _label1a->enableItalics();


    // LabelTTF
    TTFConfig ttfConfig("fonts/arial.ttf",24);
    auto label2 = Label::createWithTTF(ttfConfig, "hello non-italics", TextHAlignment::CENTER,s.width);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(Vec2(s.width/2, s.height*2/6));

    // or by setting the italics parameter on TTFConfig
    ttfConfig.italics = true;
    _label2a = Label::createWithTTF(ttfConfig, "hello italics", TextHAlignment::CENTER,s.width);
    addChild(_label2a, 0, kTagBitmapAtlas2);
    _label2a->setPosition(Vec2(s.width/2, s.height*1/6));

    auto menuItem = MenuItemFont::create("disable italics", [&](cocos2d::Ref* sender) {
        _label2a->disableEffect(LabelEffect::ITALICS);
        _label1a->disableEffect(LabelEffect::ITALICS);
    });
    menuItem->setFontSizeObj(12);
    auto menu = Menu::createWithItem(menuItem);
    addChild(menu);
    auto winSize = Director::getInstance()->getWinSize();
    menu->setPosition(winSize.width * 0.9, winSize.height * 0.25f);
}

std::string LabelItalics::title() const
{
    return "Testing Italics";
}

std::string LabelItalics::subtitle() const
{
    return "italics on TTF and BMfont";
}

///

LabelBold::LabelBold()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "hello non-bold", TextHAlignment::CENTER, s.width);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(Vec2(s.width/2, s.height*4/6));
    // you can enable italics by calling this method

    _label1a = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "hello bold", TextHAlignment::CENTER, s.width);
    addChild(_label1a, 0, kTagBitmapAtlas1);
    _label1a->setPosition(Vec2(s.width/2, s.height*3/6));
    // you can enable italics by calling this method
    _label1a->enableBold();


    // LabelTTF
    TTFConfig ttfConfig("fonts/arial.ttf",24);
    auto label2 = Label::createWithTTF(ttfConfig, "hello non-bold", TextHAlignment::CENTER,s.width);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(Vec2(s.width/2, s.height*2/6));

    // or by setting the italics parameter on TTFConfig
    ttfConfig.bold = true;
    _label2a = Label::createWithTTF(ttfConfig, "hello bold", TextHAlignment::CENTER,s.width);
    addChild(_label2a, 0, kTagBitmapAtlas2);
    _label2a->setPosition(Vec2(s.width/2, s.height*1/6));

    auto menuItem = MenuItemFont::create("disable bold", [&](cocos2d::Ref* sender) {
        _label2a->disableEffect(LabelEffect::BOLD);
        _label1a->disableEffect(LabelEffect::BOLD);
    });
    menuItem->setFontSizeObj(12);
    auto menu = Menu::createWithItem(menuItem);
    addChild(menu);
    auto winSize = Director::getInstance()->getWinSize();
    menu->setPosition(winSize.width * 0.9, winSize.height * 0.25f);
}

std::string LabelBold::title() const
{
    return "Testing Bold";
}

std::string LabelBold::subtitle() const
{
    return "Bold on TTF and BMfont";
}

///

LabelUnderline::LabelUnderline()
{
    auto s = Director::getInstance()->getWinSize();

    // LabelBMFont
    auto label1 = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "hello non-underline", TextHAlignment::CENTER, s.width);
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(Vec2(s.width/2, s.height*4/6));
    // you can enable italics by calling this method

    _label1a = Label::createWithBMFont("fonts/bitmapFontTest2.fnt", "hello underline", TextHAlignment::CENTER, s.width);
    addChild(_label1a, 0, kTagBitmapAtlas1);
    _label1a->setPosition(Vec2(s.width/2, s.height*3/6));
    // you can enable underline by calling this method
    _label1a->enableUnderline();


    // LabelTTF
    TTFConfig ttfConfig("fonts/arial.ttf",24);
    auto label2 = Label::createWithTTF(ttfConfig, "hello non-underline", TextHAlignment::CENTER,s.width);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(Vec2(s.width/2, s.height*2/6));

    // or by setting the italics parameter on TTFConfig
    ttfConfig.underline = true;
    _label2a = Label::createWithTTF(ttfConfig, "hello underline", TextHAlignment::CENTER,s.width);
    addChild(_label2a, 0, kTagBitmapAtlas2);
    _label2a->setPosition(Vec2(s.width/2, s.height*1/6));

    auto menuItem = MenuItemFont::create("disable underline", [&](cocos2d::Ref* sender) {
        _label2a->disableEffect(LabelEffect::UNDERLINE);
        _label1a->disableEffect(LabelEffect::UNDERLINE);
    });
    menuItem->setFontSizeObj(12);
    auto menu = Menu::createWithItem(menuItem);
    addChild(menu);
    auto winSize = Director::getInstance()->getWinSize();
    menu->setPosition(winSize.width * 0.9, winSize.height * 0.25f);
}

std::string LabelUnderline::title() const
{
    return "Testing Underline";
}

std::string LabelUnderline::subtitle() const
{
    return "Underline on TTF and BMfont";
}

///

LabelUnderlineMultiline::LabelUnderlineMultiline()
{
    auto s = Director::getInstance()->getWinSize();

    // bmfont
    _label1a = Label::createWithBMFont("fonts/bitmapFontTest5.fnt", "hello underline\nand multiline", TextHAlignment::CENTER, s.width);
    addChild(_label1a, 0, kTagBitmapAtlas1);
    _label1a->setPosition(Vec2(s.width/2, s.height*2/3));
    // you can enable underline by calling this method
    _label1a->enableUnderline();

    // ttf
    TTFConfig ttfConfig("fonts/arial.ttf",24);
    ttfConfig.underline = true;
    _label2a = Label::createWithTTF(ttfConfig, "hello\nunderline\nwith multiline", TextHAlignment::LEFT, s.width);
    addChild(_label2a, 0, kTagBitmapAtlas2);
    _label2a->setPosition(Vec2(s.width/2, s.height*1/3));

    auto menuItem = MenuItemFont::create("disable underline", [&](cocos2d::Ref* sender) {
        _label2a->disableEffect(LabelEffect::UNDERLINE);
        _label1a->disableEffect(LabelEffect::UNDERLINE);
    });
    menuItem->setFontSizeObj(12);
    auto menu = Menu::createWithItem(menuItem);
    addChild(menu);
    auto winSize = Director::getInstance()->getWinSize();
    menu->setPosition(winSize.width * 0.9, winSize.height * 0.25f);
}

std::string LabelUnderlineMultiline::title() const
{
    return "Testing Underline + multiline";
}

std::string LabelUnderlineMultiline::subtitle() const
{
    return "Underline on TTF and BMfont with multiline";
}

///

LabelStrikethrough::LabelStrikethrough()
{
    auto s = Director::getInstance()->getWinSize();

    // bmfont
    _label1a = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "hello strikethrough\nand multiline", TextHAlignment::LEFT, s.width);
    addChild(_label1a, 0, kTagBitmapAtlas1);
    _label1a->setPosition(Vec2(s.width/2, s.height*2/3));
    // you can enable underline by calling this method
    _label1a->enableStrikethrough();

    // ttf
    TTFConfig ttfConfig("fonts/arial.ttf",24);
    ttfConfig.strikethrough = true;
    _label2a = Label::createWithTTF(ttfConfig, "hello\nstrikethrough\nwith multiline", TextHAlignment::RIGHT, s.width);
    addChild(_label2a, 0, kTagBitmapAtlas2);
    _label2a->setPosition(Vec2(s.width/2, s.height*1/3));

    auto menuItem = MenuItemFont::create("disable underline", [&](cocos2d::Ref* sender) {
        _label2a->disableEffect(LabelEffect::STRIKETHROUGH);
        _label1a->disableEffect(LabelEffect::STRIKETHROUGH);
    });
    menuItem->setFontSizeObj(12);
    auto menu = Menu::createWithItem(menuItem);
    addChild(menu);
    auto winSize = Director::getInstance()->getWinSize();
    menu->setPosition(winSize.width * 0.9, winSize.height * 0.25f);
}

std::string LabelStrikethrough::title() const
{
    return "Testing Strikethrough + multiline";
}

std::string LabelStrikethrough::subtitle() const
{
    return "Strikethrough on TTF and BMfont with multiline";
}

LabelLocalizationTest::LabelLocalizationTest()
{
    _localizationJson = cocostudio::JsonLocalizationManager::getInstance();
    _localizationJson->initLanguageData("configs/en-US.lang.json");

    _localizationBin = cocostudio::BinLocalizationManager::getInstance();
    _localizationBin->initLanguageData("configs/ENGLISH.lang.csb");

    const float BUTTON_WIDTH = 100;
    float startPosX = 0;
    Size winSize = Director::getInstance()->getVisibleSize();

    // Create a radio button group
    auto radioButtonGroup = RadioButtonGroup::create();
    this->addChild(radioButtonGroup);

    // Create the radio buttons
    const int NUMBER_OF_BUTTONS = 3;
    startPosX = winSize.width / 2.0f - (NUMBER_OF_BUTTONS - 1) * 0.5 * BUTTON_WIDTH - 30;
    std::vector<std::string> labelTypes = { "English", "Chinese", "Japanese" };

    for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
    {
        RadioButton* radioButton = RadioButton::create("cocosui/radio_button_off.png", "cocosui/radio_button_on.png");
        float posX = startPosX + BUTTON_WIDTH * i;
        radioButton->setPosition(Vec2(posX, winSize.height / 2.0f + 70));
        radioButton->setScale(1.2f);
        radioButton->addEventListener(CC_CALLBACK_2(LabelLocalizationTest::onChangedRadioButtonSelect, this));
        radioButton->setTag(i);
        radioButtonGroup->addRadioButton(radioButton);
        this->addChild(radioButton);

        auto label = Label::createWithSystemFont(labelTypes.at(i), "Arial", 20);
        label->setPosition(radioButton->getPosition() + Vec2(50.0f, 0.0f));
        this->addChild(label);
    }

    _label1 = Label::createWithSystemFont(_localizationJson->getLocalizationString("Text Label"), "Arial", 24);
    addChild(_label1, 0);
    _label1->setPosition(Vec2(winSize.width / 2, winSize.height * 1 / 3));

    Label * label = Label::createWithSystemFont("From json data :", "Arial", 24);
    label->setAnchorPoint(Vec2(0.0f, 0.5f));
    addChild(label, 0);
    label->setPosition(Vec2(20.0f, winSize.height * 1 / 3 + 24));

    _label2 = Label::createWithSystemFont(_localizationBin->getLocalizationString("Text Label"), "Arial", 24);
    addChild(_label2, 0);
    _label2->setPosition(Vec2(winSize.width / 2, winSize.height * 1 / 2));

    label = Label::createWithSystemFont("From binary data :", "Arial", 24);
    label->setAnchorPoint(Vec2(0.0f, 0.5f));
    addChild(label, 0);
    label->setPosition(Vec2(20.0f, winSize.height * 1 / 2 + 24));
}

std::string LabelLocalizationTest::title() const
{
    return "Localization Test";
}

std::string LabelLocalizationTest::subtitle() const
{
    return "Change language selected and see label change";
}


void LabelLocalizationTest::onChangedRadioButtonSelect(RadioButton* radioButton, RadioButton::EventType type)
{
    if (radioButton == nullptr)
    {
        return;
    }

    switch (type)
    {
    case RadioButton::EventType::SELECTED:
    {
        switch (radioButton->getTag()) {
        case 0:
            _localizationJson->initLanguageData("configs/en-US.lang.json");
            _label1->setString(_localizationJson->getLocalizationString("Text Label"));
            _localizationBin->initLanguageData("configs/ENGLISH.lang.csb");
            _label2->setString(_localizationBin->getLocalizationString("Text Label"));
            break;
        case 1:
            _localizationJson->initLanguageData("configs/zh-CN.lang.json");
            _label1->setString(_localizationJson->getLocalizationString("Text Label"));
            _localizationBin->initLanguageData("configs/CHINESE.lang.csb");
            _label2->setString(_localizationBin->getLocalizationString("Text Label"));
            break;
        case 2:
            _localizationJson->initLanguageData("configs/ja-JP.lang.json");
            _label1->setString(_localizationJson->getLocalizationString("Text Label"));
            _localizationBin->initLanguageData("configs/JAPANESE.lang.csb");
            _label2->setString(_localizationBin->getLocalizationString("Text Label"));
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

//
// LabelIssue15214
//
LabelIssue15214::LabelIssue15214()
{
    auto size = Director::getInstance()->getVisibleSize();

    // 1
    Label* label = Label::createWithTTF("TTF with setColor()", "fonts/arial.ttf", 24.0f);
    label->enableUnderline();
    label->setColor(cocos2d::Color3B::BLUE);
    label->setPosition(size.width/2, size.height/5*4);
    this->addChild(label);

    // 2
    Label* label2 = Label::createWithSystemFont("System with setColor()", "Verdana", 24.0f);
    label2->enableUnderline();
    label2->setColor(cocos2d::Color3B::BLUE);
    label2->setPosition(size.width/2, size.height/5*3);
    this->addChild(label2);

    // 3
    Label* label3 = Label::createWithTTF("TTF with setTextColor()", "fonts/arial.ttf", 24.0f);
    label3->enableUnderline();
    label3->setTextColor(Color4B::BLUE);
    label3->setPosition(size.width/2, size.height/5*2);
    this->addChild(label3);

    // 4
    Label* label4 = Label::createWithSystemFont("System with setTextColor()", "Verdana", 24.0f);
    label4->enableUnderline();
    label4->setTextColor(Color4B::BLUE);
    label4->setPosition(size.width/2, size.height/5*1);
    this->addChild(label4);
}

std::string LabelIssue15214::title() const
{
    return "Github Issue 15214";
}

std::string LabelIssue15214::subtitle() const
{
    return "Font + underline: same color with setColor()";
}

//
// LabelIssue16293
//
LabelIssue16293::LabelIssue16293()
{
    auto size = Director::getInstance()->getVisibleSize();
    Label* label = Label::createWithTTF("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", "fonts/arial.ttf", 12);
    label->setPosition(size.width/2, size.height/2);
    this->addChild(label);
}

std::string LabelIssue16293::title() const
{
    return "Github Issue 16293";
}

std::string LabelIssue16293::subtitle() const
{
    return "No TextureAtlas resizes";
}

//
// LabelIssue16471
//
LabelIssue16471::LabelIssue16471()
{
    auto size = Director::getInstance()->getVisibleSize();

    auto node = Node::create();
    addChild(node, 100);
    node->setPosition(size.width/2, size.height/2);

    // Used Google Translate to translate from Chinese:
    //    Here is set to false then textLabel: TextColor valid
    //    set to true testLabel: setTextColor invalid
    // Original:
    //    此处设置为false则testLabel:setTextColor有效
    //    设置为true则testLabel:setTextColor无效
    // if set false then  testLabel:setTextColor is useful
    node->setCascadeColorEnabled(true);
    Label* label = Label::createWithTTF("Should be Yellow", "fonts/arial.ttf", 12);
    label->setTextColor(Color4B::YELLOW);
    node->addChild(label);
}

std::string LabelIssue16471::title() const
{
    return "Github Issue 16471";
}

std::string LabelIssue16471::subtitle() const
{
    return "Label should be yellow";
}

//
// LabelIssue16717
//
LabelIssue16717::LabelIssue16717()
{
    auto bg = Sprite::create("cocosui/Hello.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);

    {
        auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", 70);
        label->setPosition(VisibleRect::center() + Vec2(0.0f, 40.0f));
        label->enableOutline(Color4B(0, 255, 0, 100), 10); // Set 100 alpha for outline
        label->setTextColor(Color4B(0, 0, 255, 100)); // Also set 100 alpha for text
        addChild(label);
    }

    {
        auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", 70);
        label->setPosition(VisibleRect::center() + Vec2(0.0f, -40.0f));
        label->enableOutline(Color4B(0, 255, 0, 100), 10); // Set 100 alpha for outline
        label->setTextColor(Color4B(0, 255, 0, 100)); // Also set 100 alpha for text
        addChild(label);
    }
}

std::string LabelIssue16717::title() const
{
    return "Github Issue 16717";
}

std::string LabelIssue16717::subtitle() const
{
    return "";
}

//
// LabelIssueLineGap
//
LabelIssueLineGap::LabelIssueLineGap()
{
    
    auto size = Director::getInstance()->getWinSize();
    
    auto label1 = Label::createWithTTF("test \ntest", "fonts/FingerpopGap.ttf", 30);
    label1->setPosition(Vec2(size.width / 3, size.height / 2));
    addChild(label1);
    
    auto label2 = Label::createWithSystemFont("test \ntest", "fonts/FingerpopGap.ttf", 30);
    label2->setPosition(Vec2(size.width / 3 * 1.8 , size.height / 2));
    addChild(label2);
}

std::string LabelIssueLineGap::title() const
{
    return "Label line gap issue";
}

std::string LabelIssueLineGap::subtitle() const
{
    return "two label must have exactly the same position and distance between lines";
}

//
// LabelIssue17902
//
LabelIssue17902::LabelIssue17902()
{
    auto center = VisibleRect::center();
    
    auto label = Label::createWithTTF("abcdefg\nhijklmn", "fonts/arial.ttf", 26);
    label->setLineHeight(40);
    label->setPosition(center);
    addChild(label);

	scheduleOnce(CC_CALLBACK_0(LabelIssue17902::purgeCachedData, this), 1.0f, "purge_cached_data");
}

void LabelIssue17902::purgeCachedData()
{
    FontAtlasCache::purgeCachedData();
}

std::string LabelIssue17902::title() const
{
    return "Github Issue 17902";
}

std::string LabelIssue17902::subtitle() const
{
    return "";
}

//
// LabelLetterColorsTest
//
LabelLetterColorsTest::LabelLetterColorsTest() {
    auto center = VisibleRect::center();

    auto label = Label::createWithTTF("", "fonts/arial.ttf", 24);
    label->setPosition(center.x, center.y);
    addChild(label);

    label->setString("1\n2\n3");
    setLetterColors(label, Color3B::RED);

    label->setString("abcd\ne");  // Must not crash at here.
}

std::string LabelLetterColorsTest::title() const {
    return "Test for letter colors";
}

std::string LabelLetterColorsTest::subtitle() const {
    return "Should not crash!";
}

void LabelLetterColorsTest::setLetterColors(cocos2d::Label* label, const cocos2d::Color3B& color) {
    int n = label->getStringLength();
    for (int i = 0; i < n; ++i) {
        Sprite* letter = label->getLetter(i);
        if (letter != nullptr)
            letter->setColor(color);
    }
}
