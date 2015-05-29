/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include <cmath>

USING_NS_CC;

#if defined(_MSC_VER) && _MSC_VER<1800
#define CC_ROUND(__f__) __f__
#else
#define CC_ROUND(__f__) roundf(__f__)
#endif

enum {
    kMaxNodes = 50000,
    kNodesIncrease = 250,

    TEST_COUNT = 7,
};

enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagAutoTestMenu = 3,
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
    */

    // purge textures
    auto mgr = Director::getInstance()->getTextureCache();
    mgr->removeTextureForKey("Images/grossinis_sister1.png");
    mgr->removeTextureForKey("Images/grossini_dance_atlas.png");
    mgr->removeTextureForKey("Images/spritesheet1.png");

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

// FIXME: This should be part of the class, but VC2013 doesn't support constexpr as static members yet
static const float SECONDS_PER_TESTS = 4.0f;
static const int MAX_SPRITE_TEST_CASE = 7; // A...G
static const int MAX_SUB_TEST_NUMS = 13;  // 1...13

// 500 sprites, 1500 sprites, etc...
bool SpriteMainScene::_s_autoTest = false;
int SpriteMainScene::_s_nSpriteCurCase = 0;
int SpriteMainScene::_s_spritesQuatityIndex = 0;
int SpriteMainScene::_s_spritesQuanityArray[] = {1000, 3000, 0};
// FIXME: to make VS2012 happy. Once VS2012 is deprecated, we can just simply replace it with {}
std::vector<float> SpriteMainScene::_s_saved_fps = std::vector<float>(); 

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
    
    MenuItemFont* autoTestItem = nullptr;
    if (SpriteMainScene::_s_autoTest)
    {
        autoTestItem = MenuItemFont::create("Auto Test On",CC_CALLBACK_1(SpriteMainScene::onAutoTest, this));
    }
    else
    {
        autoTestItem = MenuItemFont::create("Auto Test Off",CC_CALLBACK_1(SpriteMainScene::onAutoTest, this));
    }
    autoTestItem->setTag(1);
    autoTestItem->setPosition(Vec2( s.width - 90, s.height / 2));
    menuAutoTest->addChild(autoTestItem);
    addChild( menuAutoTest, 3, kTagAutoTestMenu );
    
    // Sub Tests
    MenuItemFont::setFontSize(28);
    auto subMenu = Menu::create();
    for (int i = 1; i <= 13; ++i)
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
    addChild(label, 1);
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
    if (SpriteMainScene::_s_autoTest)
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

void  SpriteMainScene::dumpProfilerFPS()
{
    log("COPY & PASTE into Cocos2d-x Performance Test spreadsheet");
    log("https://docs.google.com/spreadsheets/d/1XolpgYfoWszA2rxnVRCAVS7ILAGiV049o5mpL29cwLs/edit#gid=1561044615");
    log("");
    int index = 0;
    int sprites = 0;
    while((sprites = _s_spritesQuanityArray[index])) {
        log("Number of sprites: %d", sprites);
        for(int i=0; i < MAX_SPRITE_TEST_CASE; i++)
        {
            char buffer[512];
            buffer[0]=0;
            for(int j=0; j < MAX_SUB_TEST_NUMS; j++)
            {
                float fps = _s_saved_fps[j + i*MAX_SUB_TEST_NUMS + MAX_SUB_TEST_NUMS * MAX_SPRITE_TEST_CASE * index];
                char fps_str[64];
                sprintf(fps_str, "\t%d", (int)CC_ROUND(fps));
                strcat(buffer, fps_str);
            }
            log("%c%s", i + 'A', buffer);
        }

        index++;
    };
}

void SpriteMainScene::saveFPS()
{
    float fps = Director::getInstance()->getFrameRate();
    _s_saved_fps.push_back(fps);
    log("Nodes: %d, Test: %c, SubTest: %d = %.1f", _quantityNodes, 'A'+_s_nSpriteCurCase, _subtestNumber, fps);
}

void SpriteMainScene::updateAutoTest(float dt)
{
    saveFPS();
    nextAutoTest();
}

void SpriteMainScene::onEnter()
{
    Scene::onEnter();
    
    if ( SpriteMainScene::_s_autoTest )
    {
        auto director = Director::getInstance();
        auto sched = director->getScheduler();

        // schedule it only once. Call me after 3 seconds
        sched->schedule(CC_SCHEDULE_SELECTOR(SpriteMainScene::updateAutoTest), this, SECONDS_PER_TESTS, 0, 0, false);
    }
}

void SpriteMainScene::onExit()
{
    if ( SpriteMainScene::_s_autoTest )
    {
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        sched->unschedule(CC_SCHEDULE_SELECTOR(SpriteMainScene::updateAutoTest), this );
    }
    
    Scene::onExit();
}

void  SpriteMainScene::autoShowSpriteTests(int curCase, int subTest, int nodes)
{
    
    SpriteMainScene* scene = nullptr;
    
    switch (curCase)
    {
        case 0:
            scene = new (std::nothrow) SpritePerformTestA;
            break;
        case 1:
            scene = new (std::nothrow) SpritePerformTestB;
            break;
        case 2:
            scene = new (std::nothrow) SpritePerformTestC;
            break;
        case 3:
            scene = new (std::nothrow) SpritePerformTestD;
            break;
        case 4:
            scene = new (std::nothrow) SpritePerformTestE;
            break;
        case 5:
            scene = new (std::nothrow) SpritePerformTestF;
            break;
        case 6:
            scene = new (std::nothrow) SpritePerformTestG;
            break;
        default:
            CCASSERT(false, "Invalid scene value");
            break;
    }

    if (scene)
    {
        scene->initWithSubTest(subTest, nodes);
        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
}

void SpriteMainScene::beginAutoTest()
{
    _s_spritesQuatityIndex = 0;
    _s_nSpriteCurCase = 0;
    _s_saved_fps.clear();

    _subtestNumber = 0;
    _quantityNodes = _s_spritesQuanityArray[_s_spritesQuatityIndex];

    nextAutoTest();
}

void  SpriteMainScene::endAutoTest()
{
    SpriteMainScene::_s_autoTest = false;
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    
    sched->unschedule( CC_SCHEDULE_SELECTOR( SpriteMainScene::updateAutoTest ), this );
}

void  SpriteMainScene::nextAutoTest()
{
    if (SpriteMainScene::_s_nSpriteCurCase < MAX_SPRITE_TEST_CASE)
    {
        if (_subtestNumber < MAX_SUB_TEST_NUMS)
        {
            // Increase Sub Main Test (1, 2, 3, 4, ...)
            _subtestNumber += 1;
            autoShowSpriteTests(_s_nSpriteCurCase, _subtestNumber, _quantityNodes);
        }
        else if (_subtestNumber == MAX_SUB_TEST_NUMS)
        {
            if (SpriteMainScene::_s_nSpriteCurCase + 1 < MAX_SPRITE_TEST_CASE)
            {
                // Increase Main Test (A, B, C, ...)
                _subtestNumber = 1;
                _s_nSpriteCurCase++;
                autoShowSpriteTests(_s_nSpriteCurCase, _subtestNumber, _quantityNodes);
            }
            else
            {
                // Increase quanity of sprites, or finish
                int sprites = _s_spritesQuanityArray[++_s_spritesQuatityIndex];
                if (sprites != 0) {
                    _quantityNodes = sprites;
                    _subtestNumber = 1;
                    _s_nSpriteCurCase = 0;
                    autoShowSpriteTests(_s_nSpriteCurCase, _subtestNumber, _quantityNodes);
                }
                else
                {
                    finishAutoTest();
                }
            }
        }
    }
}

void  SpriteMainScene::finishAutoTest()
{
    SpriteMainScene::_s_autoTest = false;
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->unschedule( CC_SCHEDULE_SELECTOR( SpriteMainScene::updateAutoTest ), this);
    
    auto autoTestMenu = dynamic_cast<Menu*>(getChildByTag(kTagAutoTestMenu));
    if (nullptr != autoTestMenu)
    {
        auto menuItemFont = dynamic_cast<MenuItemFont*>(autoTestMenu->getChildByTag(1));
        if (nullptr != menuItemFont)
        {
            menuItemFont->setString("Auto Test finish");
        }
    }
    
    log("Sprite performance test is finished");

    dumpProfilerFPS();
}

void  SpriteMainScene::onAutoTest(Ref* sender)
{
    SpriteMainScene::_s_autoTest = !SpriteMainScene::_s_autoTest;
    MenuItemFont* menuItem = dynamic_cast<MenuItemFont*>(sender);

    if (SpriteMainScene::_s_autoTest)
    {
        menuItem->setString("Auto Test On");
        beginAutoTest();
    }
    else
    {
        menuItem->setString("Auto Test Off");
        endAutoTest();
    }
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
