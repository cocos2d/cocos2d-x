/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "PerformanceSpriteTest.h"
#include "Profile.h"

#include <cmath>

USING_NS_CC;

#if defined(_MSC_VER) && _MSC_VER<1800
#define CC_ROUND(__f__) __f__
#else
#define CC_ROUND(__f__) roundf(__f__)
#endif

#define MAX_SUB_TEST_NUM        16
#define DELAY_TIME              2
#define STAT_TIME               3

enum {
    kMaxNodes = 50000,
    kNodesIncrease = 250,
};

enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagTitle     = 3,
    kTagMenuLayer = (kMaxNodes + 1000),
};

PerformceSpriteTests::PerformceSpriteTests()
{
    ADD_TEST_CASE(SpritePerformTestA);
    ADD_TEST_CASE(SpritePerformTestB);
    ADD_TEST_CASE(SpritePerformTestC);
    ADD_TEST_CASE(SpritePerformTestD);
    ADD_TEST_CASE(SpritePerformTestE);
    ADD_TEST_CASE(SpritePerformTestF);
    ADD_TEST_CASE(SpritePerformTestG);
}

int SpriteMainScene::_quantityNodes = 50;
int SpriteMainScene::_subtestNumber = 1;

static int autoTestSpriteCounts[] = {
    1000, 2000, 3000
};

////////////////////////////////////////////////////////
//
// SubTest
//
////////////////////////////////////////////////////////
SubTest::~SubTest()
{
    _parentNode->release();
}

void SubTest::initWithSubTest(int subtest, Node* p)
{
    std::srand(0);

    _subtestNumber = subtest;
    _parentNode = nullptr;
    /*
     * Tests:
     * 1: 1 (32-bit) PNG sprite of 52 x 139
     * 2: 1 (32-bit) PNG sprite of 52 x 139 (same as 1)
     * 3: 1 (32-bit) PNG Batch Node using 1 sprite of 52 x 139
     * 4: 1 (16-bit) PNG Batch Node using 1 sprite of 52 x 139

     * 5: 14 (32-bit) PNG sprites of 85 x 121 each
     * 6: 14 (32-bit) PNG sprites of 85 x 121 each that belong to on texture atlas
     * 7: 14 (32-bit) PNG Batch Node of 85 x 121 each
     * 8: 14 (16-bit) PNG Batch Node of 85 x 121 each

     * 9: 64 (32-bit) sprites of 32 x 32 each
     *10: 64 (32-bit) sprites of 32 x 32 each that belong to on texture atlas
     *11: 64 (32-bit) PNG Batch Node of 32 x 32 each
     *12: 64 (16-bit) PNG Batch Node of 32 x 32 each
     *
     *13:    (16-bit) PNG sprites. 33% from test4, 33% from test8, 33% from test12
     *14:    (32-bit) PNG sprites: Batched Quads
     *15:    (32-bit) PNG sprites: Batched Triangles
     *16:    (16-bit) Similar to test 13, but uses polygon sprites instead of quads
    */

    // purge textures
    auto mgr = Director::getInstance()->getTextureCache();
    mgr->removeTextureForKey("Images/grossinis_sister1.png");
    mgr->removeTextureForKey("Images/grossini_dance_atlas.png");
    mgr->removeTextureForKey("Images/spritesheet1.png");
    SpriteFrameCache::getInstance()->removeSpriteFrames();

    switch ( _subtestNumber)
    {
            ///
        case 1:
        case 2:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = Node::create();
            break;
        case 3:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = SpriteBatchNode::create("Images/grossinis_sister1.png", 100);
            break;
        case 4:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            _parentNode = SpriteBatchNode::create("Images/grossinis_sister1.png", 100);
            break;

            ///
        case 5:
        case 6:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = Node::create();
            break;
        case 7:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
            break;
        case 8:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            _parentNode = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
            break;

            ///
        case 9:
        case 10:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = Node::create();
            break;
        case 11:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = SpriteBatchNode::create("Images/spritesheet1.png", 100);
            break;
        case 12:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            _parentNode = SpriteBatchNode::create("Images/spritesheet1.png", 100);
            break;

            ///
        case 13:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            _parentNode = Node::create();
            break;

        case 14:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = Node::create();
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/grossini_quad.plist"); // sprite sheet with rectangular frames
            break;
        case 15:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            _parentNode = Node::create();
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/grossini_polygon.plist"); // sprite sheet with triangulation of sprite outlines
            break;

        case 16:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            _parentNode = Node::create();
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/grossinis_sister1_sp.plist");
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/grossinis_sister2_sp.plist");
            break;

        default:
            break;
    }

    p->addChild(_parentNode);
    _parentNode->retain();
}

Sprite* SubTest::createSpriteWithTag(int tag)
{
    TextureCache *cache = Director::getInstance()->getTextureCache();

    Sprite* sprite = nullptr;
    switch (_subtestNumber)
    {
        ///
        case 1:
        case 2:
        {
            sprite = Sprite::create("Images/grossinis_sister1.png");
            _parentNode->addChild(sprite, 0, tag+100);
            break;
        }
        case 3:
        case 4:
        {
            Texture2D *texture = cache->addImage("Images/grossinis_sister1.png");
            sprite = Sprite::createWithTexture(texture, Rect(0, 0, 52, 139));
            _parentNode->addChild(sprite, 0, tag+100);
            break;
        }

        ///
        case 5:
        {
            int idx = (CCRANDOM_0_1() * 1400 / 100) + 1;
            char str[32] = {0};
            sprintf(str, "Images/grossini_dance_%02d.png", idx);
            sprite = Sprite::create(str);
            _parentNode->addChild(sprite, 0, tag+100);
            break;
        }
        case 6:
        case 7:
        case 8:
        {
            int y,x;
            int r = (CCRANDOM_0_1() * 1400 / 100);

            y = r / 5;
            x = r % 5;

            x *= 85;
            y *= 121;
            Texture2D *texture = cache->addImage("Images/grossini_dance_atlas.png");
            sprite = Sprite::createWithTexture(texture, Rect(x,y,85,121));
            _parentNode->addChild(sprite, 0, tag+100);
            break;
        }

        ///
        case 9:
            {
                int y,x;
                int r = (CCRANDOM_0_1() * 6400 / 100);

                y = r / 8;
                x = r % 8;

                char str[40] = {0};
                sprintf(str, "Images/sprites_test/sprite-%d-%d.png", x, y);
                sprite = Sprite::create(str);
                _parentNode->addChild(sprite, 0, tag+100);
                break;
            }

        case 10:
        case 11:
        case 12:
        {
            int y,x;
            int r = (CCRANDOM_0_1() * 6400 / 100);

            y = r / 8;
            x = r % 8;

            x *= 32;
            y *= 32;
            Texture2D *texture = cache->addImage("Images/spritesheet1.png");
            sprite = Sprite::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(x,y,32,32)));
            _parentNode->addChild(sprite, 0, tag+100);
            break;
        }
            ///
        case 13:
        {
            int test = (CCRANDOM_0_1() * 3);

            if(test==0) {
                // Switch case 1
                sprite = Sprite::create("Images/grossinis_sister1.png");
                _parentNode->addChild(sprite, 0, tag+100);
            }
            else if(test==1)
            {
                // Switch case 6
                int y,x;
                int r = (CCRANDOM_0_1() * 1400 / 100);

                y = r / 5;
                x = r % 5;

                x *= 85;
                y *= 121;
                Texture2D *texture = cache->addImage("Images/grossini_dance_atlas.png");
                sprite = Sprite::createWithTexture(texture, Rect(x,y,85,121));
                _parentNode->addChild(sprite, 0, tag+100);

            }
            else if(test==2)
            {
                int y,x;
                int r = (CCRANDOM_0_1() * 6400 / 100);

                y = r / 8;
                x = r % 8;

                x *= 32;
                y *= 32;
                Texture2D *texture = cache->addImage("Images/spritesheet1.png");
                sprite = Sprite::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(x,y,32,32)));
                _parentNode->addChild(sprite, 0, tag+100);
            }
            break;
        }
        case 14:
        case 15:
        {
            sprite = Sprite::createWithSpriteFrameName("grossini_dance_05.png");
            _parentNode->addChild(sprite, 0, tag+100);
            break;
        }
        case 16:
        {
            int test = (CCRANDOM_0_1() * 2);
            if(test==0) {
                sprite = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
                _parentNode->addChild(sprite, 0, tag+100);
            }
            else if(test==1)
            {
                sprite = Sprite::createWithSpriteFrameName("grossinis_sister2.png");
                _parentNode->addChild(sprite, 0, tag+100);
            }
            break;
        }

        default:
            break;
    }

    return sprite;
}

void SubTest::removeByTag(int tag)
{
    _parentNode->removeChildByTag(tag+100, true);
}

////////////////////////////////////////////////////////
//
// SpriteMainScene
//
////////////////////////////////////////////////////////

bool SpriteMainScene::init()
{
    if (TestCase::init())
    {
        initWithSubTest(_subtestNumber, _quantityNodes);
        return true;
    }

    return false;
}

void SpriteMainScene::initWithSubTest(int asubtest, int nNodes)
{
     std::srand(0);

    _subtestNumber = asubtest;
    _subTest = new (std::nothrow) SubTest;
    _subTest->initWithSubTest(asubtest, this);

    auto s = Director::getInstance()->getWinSize();

    _lastRenderedCount = 0;
    _quantityNodes = 0;

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(SpriteMainScene::onDecrease, this));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(SpriteMainScene::onIncrease, this));
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height-65));
    addChild(menu, 1);

    auto infoLabel = Label::createWithTTF("0 nodes", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height-90));
    addChild(infoLabel, 1, kTagInfoLayer);
    
    /**
     *  auto test menu
     */
    
    auto menuAutoTest = Menu::create();
    menuAutoTest->setPosition( Vec2::ZERO );
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    
    // Sub Tests
    MenuItemFont::setFontSize(28);
    auto subMenu = Menu::create();
    for (int i = 1; i <= MAX_SUB_TEST_NUM; ++i)
    {
        char str[10] = {0};
        sprintf(str, "%d ", i);
        auto itemFont = MenuItemFont::create(str, CC_CALLBACK_1(SpriteMainScene::testNCallback, this));
        itemFont->setTag(i);
        subMenu->addChild(itemFont, 10);

        if( i<= 4)
            itemFont->setColor(Color3B(200,20,20));
        else if(i <= 8)
            itemFont->setColor(Color3B(0,200,20));
        else if( i<=12)
            itemFont->setColor(Color3B(0,20,200));
        else
            itemFont->setColor(Color3B::GRAY);
    }

    subMenu->alignItemsHorizontally();
    subMenu->setPosition(Vec2(s.width/2, 80));
    addChild(subMenu, 2);

    // add title label
    auto label = Label::createWithTTF(title(), "fonts/arial.ttf", 32);
    addChild(label, 1, kTagTitle);
    label->setPosition(Vec2(s.width/2, s.height-50));


    // subtitle
    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() )
    {
        auto l = Label::createWithTTF(strSubtitle.c_str(), "fonts/Thonburi.ttf", 16);
        addChild(l, 9999);
        l->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }

    while(_quantityNodes < nNodes)
        onIncrease(this);
}

std::string SpriteMainScene::title() const
{
    return "No title";
}

std::string SpriteMainScene::subtitle() const
{
    return ""; // override me
}

SpriteMainScene::~SpriteMainScene()
{
    if (_subTest)
    {
        delete _subTest;
        _subTest = nullptr;
    }
}

void SpriteMainScene::testNCallback(Ref* sender)
{
    if (isAutoTesting())
    {
        log("It's auto sprite performance testing,so this operation is invalid");
        return;
    }
    
    _subtestNumber = static_cast<MenuItemFont*>(sender)->getTag();
    
    this->restartTestCallback(sender);
}

void SpriteMainScene::updateNodes()
{
    if( _quantityNodes != _lastRenderedCount )
    {
        auto infoLabel = (Label *) getChildByTag(kTagInfoLayer);
        char str[16] = {0};
        sprintf(str, "%u nodes", _quantityNodes);
        infoLabel->setString(str);

        _lastRenderedCount = _quantityNodes;
    }
}

void SpriteMainScene::updateTitle()
{
    auto titleLabel = (Label *) getChildByTag(kTagTitle);
    titleLabel->setString(this->title());
}

void SpriteMainScene::onIncrease(Ref* sender)
{    
    if( _quantityNodes >= kMaxNodes)
        return;

    for( int i=0;i< kNodesIncrease;i++)
    {
        auto sprite = _subTest->createSpriteWithTag(_quantityNodes);
        doTest(sprite);
        _quantityNodes++;
    }

    updateNodes();
}

void SpriteMainScene::onDecrease(Ref* sender)
{
    
    if( _quantityNodes <= 0 )
        return;

    for( int i=0;i < kNodesIncrease;i++)
    {
        _quantityNodes--;
        _subTest->removeByTag(_quantityNodes);
    }

    updateNodes();
}

void SpriteMainScene::onEnter()
{
    Scene::onEnter();
    
    if (isAutoTesting())
    {
        scheduleUpdate();
        Profile::getInstance()->testCaseBegin("SpriteTest",
                                              genStrVector("SpriteCount", "Type", "SubTest", nullptr),
                                              genStrVector("Avg", "Min", "Max", nullptr));
        
        autoTestIndex = 0;
        _subtestNumber = 1;

        doAutoTest();
    }
}

void SpriteMainScene::onExit()
{
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->unscheduleAllForTarget(this);
    Scene::onExit();
}

void SpriteMainScene::update(float dt)
{
    if (isStating)
    {
        totalStatTime += dt;
        statCount++;

        auto curFrameRate = Director::getInstance()->getFrameRate();
        if (maxFrameRate < 0 || curFrameRate > maxFrameRate)
            maxFrameRate = curFrameRate;
        
        if (minFrameRate < 0 || curFrameRate < minFrameRate)
            minFrameRate = curFrameRate;
    }
}

void SpriteMainScene::beginStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(SpriteMainScene::beginStat));
    isStating = true;
}

void SpriteMainScene::endStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(SpriteMainScene::endStat));
    isStating = false;
    
    // record test data
    auto typeStr = getTestCaseName();
    auto avgStr = genStr("%.2f", (float) statCount / totalStatTime);
    Profile::getInstance()->addTestResult(genStrVector(genStr("%d", _quantityNodes).c_str(), typeStr.c_str(),
                                                       genStr("%d", _subtestNumber).c_str(), nullptr),
                                          genStrVector(avgStr.c_str(), genStr("%.2f", minFrameRate).c_str(),
                                                       genStr("%.2f", maxFrameRate).c_str(), nullptr));
    
    // check the auto test is end or not
    int autoTestCount = sizeof(autoTestSpriteCounts) / sizeof(int);
    if (autoTestIndex >= (autoTestCount - 1) &&
        _subtestNumber >= MAX_SUB_TEST_NUM)
    {
        // auto test end
        Profile::getInstance()->testCaseEnd();
        setAutoTesting(false);
        return;
    }
    
    if (autoTestIndex >= (autoTestCount - 1))
    {
        autoTestIndex = 0;
        _subtestNumber++;
    }
    else
    {
        autoTestIndex++;
    }
    doAutoTest();
}

void SpriteMainScene::doAutoTest()
{
    isStating = false;
    statCount = 0;
    totalStatTime = 0.0f;
    minFrameRate = -1.0f;
    maxFrameRate = -1.0f;

    // recreate a SubTest object
    this->removeChild(_subTest->getTheParentNode());
    CC_SAFE_DELETE(_subTest);
    _subTest = new (std::nothrow) SubTest;
    _subTest->initWithSubTest(_subtestNumber, this);
    
    // create sprites & update the label
    _quantityNodes = autoTestSpriteCounts[autoTestIndex];
    for( int i = 0; i < _quantityNodes; i++)
    {
        auto sprite = _subTest->createSpriteWithTag(i);
        doTest(sprite);
    }
    updateNodes();
    updateTitle();

    schedule(CC_SCHEDULE_SELECTOR(SpriteMainScene::beginStat), DELAY_TIME);
    schedule(CC_SCHEDULE_SELECTOR(SpriteMainScene::endStat), DELAY_TIME + STAT_TIME);
}

////////////////////////////////////////////////////////
//
// For test functions
//
////////////////////////////////////////////////////////
void performanceActions(Sprite* sprite)
{
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2((rand() % (int)size.width), (rand() % (int)size.height)));

    float period = 0.5f + (rand() % 1000) / 500.0f;
    auto rot = RotateBy::create(period, 360.0f * CCRANDOM_0_1());
    auto rot_back = rot->reverse();
    auto permanentRotation = RepeatForever::create(Sequence::create(rot, rot_back, nullptr));
    sprite->runAction(permanentRotation);

    float growDuration = 0.5f + (rand() % 1000) / 500.0f;
    auto grow = ScaleBy::create(growDuration, 0.5f, 0.5f);
    auto permanentScaleLoop = RepeatForever::create(Sequence::create(grow, grow->reverse(), nullptr));
    sprite->runAction(permanentScaleLoop);
}

void performanceActions20(Sprite* sprite)
{
    auto size = Director::getInstance()->getWinSize();
    if( CCRANDOM_0_1() < 0.2f )
        sprite->setPosition(Vec2((rand() % (int)size.width), (rand() % (int)size.height)));
    else
        sprite->setPosition(Vec2( -1000, -1000));

    float period = 0.5f + (rand() % 1000) / 500.0f;
    auto rot = RotateBy::create(period, 360.0f * CCRANDOM_0_1());
    auto rot_back = rot->reverse();
    auto permanentRotation = RepeatForever::create(Sequence::create(rot, rot_back, nullptr));
    sprite->runAction(permanentRotation);

    float growDuration = 0.5f + (rand() % 1000) / 500.0f;
    auto grow = ScaleBy::create(growDuration, 0.5f, 0.5f);
    auto permanentScaleLoop = RepeatForever::create(Sequence::createWithTwoActions(grow, grow->reverse()));
    sprite->runAction(permanentScaleLoop);
}

void performanceRotationScale(Sprite* sprite)
{
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2((rand() % (int)size.width), (rand() % (int)size.height)));
    sprite->setRotation(CCRANDOM_0_1() * 360);
    sprite->setScale(CCRANDOM_0_1() * 2);
}

void performancePosition(Sprite* sprite)
{
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2((rand() % (int)size.width), (rand() % (int)size.height)));
}

void performanceout20(Sprite* sprite)
{
    auto size = Director::getInstance()->getWinSize();

    if( CCRANDOM_0_1() < 0.2f )
        sprite->setPosition(Vec2((rand() % (int)size.width), (rand() % (int)size.height)));
    else
        sprite->setPosition(Vec2( -1000, -1000));
}

void performanceOut100(Sprite* sprite)
{
    sprite->setPosition(Vec2( -1000, -1000));
}

void performanceScale(Sprite* sprite)
{
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2((rand() % (int)size.width), (rand() % (int)size.height)));
    sprite->setScale(CCRANDOM_0_1() * 100 / 50);
}

////////////////////////////////////////////////////////
//
// SpritePerformTestA
//
////////////////////////////////////////////////////////
std::string SpritePerformTestA::title() const
{
    char str[32] = {0};
    sprintf(str, "A (%d) position", _subtestNumber);
    std::string strRet = str;
    return strRet;
}


void SpritePerformTestA::doTest(Sprite* sprite)
{
    performancePosition(sprite);
}
////////////////////////////////////////////////////////
//
// SpritePerformTestB
//
////////////////////////////////////////////////////////
std::string SpritePerformTestB::title() const
{
    char str[32] = {0};
    sprintf(str, "B (%d) scale", _subtestNumber);
    std::string strRet = str;
    return strRet;
}

void SpritePerformTestB::doTest(Sprite* sprite)
{
    performanceScale(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTestC
//
////////////////////////////////////////////////////////
std::string SpritePerformTestC::title() const
{
    char str[32] = {0};
    sprintf(str, "C (%d) scale + rot", _subtestNumber);
    std::string strRet = str;
    return strRet;
}

void SpritePerformTestC::doTest(Sprite* sprite)
{
    performanceRotationScale(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTestD
//
////////////////////////////////////////////////////////
std::string SpritePerformTestD::title() const
{
    char str[32] = {0};
    sprintf(str, "D (%d) 100%% out", _subtestNumber);
    std::string strRet = str;
    return strRet;
}

void SpritePerformTestD::doTest(Sprite* sprite)
{
    performanceOut100(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTestE
//
////////////////////////////////////////////////////////
std::string SpritePerformTestE::title() const
{
    char str[32] = {0};
    sprintf(str, "E (%d) 80%% out", _subtestNumber);
    std::string strRet = str;
    return strRet;
}

void SpritePerformTestE::doTest(Sprite* sprite)
{
    performanceout20(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTestF
//
////////////////////////////////////////////////////////
std::string SpritePerformTestF::title() const
{
    char str[32] = {0};
    sprintf(str, "F (%d) actions", _subtestNumber);
    std::string strRet = str;
    return strRet;
}

void SpritePerformTestF::doTest(Sprite* sprite)
{
    performanceActions(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTestG
//
////////////////////////////////////////////////////////
std::string SpritePerformTestG::title() const
{
    char str[32] = {0};
    sprintf(str, "G (%d) actions 80%% out", _subtestNumber);
    std::string strRet = str;
    return strRet;
}

void SpritePerformTestG::doTest(Sprite* sprite)
{
    performanceActions20(sprite);
}
