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

#include "FontTest.h"
#include "../testResource.h"
#include "2d/CCFontAtlasCache.h"
#include "2d/CCFontFreeType.h"

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
	ADD_TEST_CASE(FontNoReplacementTest);
	ADD_TEST_CASE(FontReplacementTest);
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

    leftColor->setIgnoreAnchorPointForPosition(false);
    centerColor->setIgnoreAnchorPointForPosition(false);
    rightColor->setIgnoreAnchorPointForPosition(false);


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

FontNoReplacementTest* FontNoReplacementTest::create()
{
	auto ret = new (std::nothrow) FontNoReplacementTest;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}

	return ret;
}

FontNoReplacementTest::FontNoReplacementTest()
{
	_replace = false;
}

FontNoReplacementTest::~FontNoReplacementTest()
{
	// need to clear the caches since we change the lookup dictionary after the application init.
	FontAtlasCache::unloadFontAtlasTTF("fonts/A Damn Mess.ttf");
	FontFreeType::releaseFont("fonts/A Damn Mess.ttf");
	FontAtlasCache::unloadFontAtlasTTF("fonts/Abberancy.ttf");
	FontFreeType::releaseFont("fonts/Abberancy.ttf");
	FontAtlasCache::unloadFontAtlasTTF("fonts/Abduction.ttf");
	FontFreeType::releaseFont("fonts/Abduction.ttf");
	FontAtlasCache::unloadFontAtlasTTF("fonts/Schwarzwald.ttf");
	FontFreeType::releaseFont("fonts/Schwarzwald.ttf");
	FileUtils::getInstance()->setFilenameLookupDictionary(ValueMap());
}

void FontNoReplacementTest::onEnter()
{
	TestCase::onEnter();

	std::string suffix;
	if (_replace)
	{
		ValueMap dict{
			{ "fonts/A Damn Mess.ttf", Value("fonts/arial.ttf") },
			{ "fonts/Abberancy.ttf", Value("fonts/arial.ttf") },
			{ "fonts/Abduction.ttf", Value("fonts/arial.ttf") },
			{ "fonts/Schwarzwald.ttf", Value("fonts/arial.ttf") }
		};

		FileUtils::getInstance()->setFilenameLookupDictionary(dict);
		suffix = " replaced by arial.ttf";
	}

	auto s = Director::getInstance()->getWinSize();

	auto blockSize = Size(s.width / 3, 200);
	float fontSize = 26;

	removeChildByTag(kTagLabel1, true);
	removeChildByTag(kTagLabel2, true);
	removeChildByTag(kTagLabel3, true);
	removeChildByTag(kTagLabel4, true);
	removeChildByTag(kTagColor1, true);
	removeChildByTag(kTagColor2, true);
	removeChildByTag(kTagColor3, true);

	auto top = Label::createWithTTF("fonts/A Damn Mess.ttf" + suffix, "fonts/A Damn Mess.ttf", 24);
	auto left = Label::createWithTTF("fonts/Abberancy.ttf" + suffix, "fonts/Abberancy.ttf", fontSize,
		blockSize, TextHAlignment::LEFT, verticalAlignment[0]);
	auto center = Label::createWithTTF("fonts/Abduction.ttf" + suffix, "fonts/Abduction.ttf", fontSize,
		blockSize, TextHAlignment::CENTER, verticalAlignment[0]);
	auto right = Label::createWithTTF("fonts/Schwarzwald.ttf" + suffix, "fonts/Schwarzwald.ttf", fontSize,
		blockSize, TextHAlignment::RIGHT, verticalAlignment[0]);

	auto leftColor = LayerColor::create(Color4B(100, 100, 100, 255), blockSize.width, blockSize.height);
	auto centerColor = LayerColor::create(Color4B(200, 100, 100, 255), blockSize.width, blockSize.height);
	auto rightColor = LayerColor::create(Color4B(100, 100, 200, 255), blockSize.width, blockSize.height);

	leftColor->setIgnoreAnchorPointForPosition(false);
	centerColor->setIgnoreAnchorPointForPosition(false);
	rightColor->setIgnoreAnchorPointForPosition(false);

	top->setAnchorPoint(Vec2(0.5, 1));
	left->setAnchorPoint(Vec2(0, 0.5));
	leftColor->setAnchorPoint(Vec2(0, 0.5));
	center->setAnchorPoint(Vec2(0, 0.5));
	centerColor->setAnchorPoint(Vec2(0, 0.5));
	right->setAnchorPoint(Vec2(0, 0.5));
	rightColor->setAnchorPoint(Vec2(0, 0.5));

	top->setPosition(s.width / 2, s.height - 20);
	left->setPosition(0, s.height / 2);
	leftColor->setPosition(left->getPosition());
	center->setPosition(blockSize.width, s.height / 2);
	centerColor->setPosition(center->getPosition());
	right->setPosition(blockSize.width * 2, s.height / 2);
	rightColor->setPosition(right->getPosition());

	this->addChild(leftColor, -1, kTagColor1);
	this->addChild(left, 0, kTagLabel1);
	this->addChild(rightColor, -1, kTagColor2);
	this->addChild(right, 0, kTagLabel2);
	this->addChild(centerColor, -1, kTagColor3);
	this->addChild(center, 0, kTagLabel3);
	this->addChild(top, 0, kTagLabel4);
}

std::string FontNoReplacementTest::title() const
{
	return "Font no replacement test";
}

FontReplacementTest* FontReplacementTest::create()
{
	auto ret = new (std::nothrow) FontReplacementTest;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}

	return ret;
}

FontReplacementTest::FontReplacementTest()
{
	_replace = true;
}

std::string FontReplacementTest::title() const
{
	return "Font replacement test";
}
