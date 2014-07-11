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
    srand(0);

    subtestNumber = subtest;
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
    */

    // purge textures
    auto mgr = Director::getInstance()->getTextureCache();
    mgr->removeTextureForKey("Images/grossinis_sister1.png");
    mgr->removeTextureForKey("Images/grossini_dance_atlas.png");
    mgr->removeTextureForKey("Images/spritesheet1.png");

    switch ( subtestNumber)
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
    switch (subtestNumber)
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
// SpriteMenuLayer
//
////////////////////////////////////////////////////////
void SpriteMenuLayer::restartCallback(Ref* sender)
{
    if ( SpriteMainScene::_s_autoTest )
    {
        log("It's auto sprite performace testing,so this operation is invalid");
        return;
    }
    
    PerformBasicLayer::restartCallback(sender);
}
void SpriteMenuLayer::nextCallback(Ref* sender)
{
    if ( SpriteMainScene::_s_autoTest )
    {
        log("It's auto sprite performace testing,so this operation is invalid");
        return;
    }
    
    PerformBasicLayer::nextCallback(sender);
}
void SpriteMenuLayer::backCallback(Ref* sender)
{
    if ( SpriteMainScene::_s_autoTest )
    {
        log("It's auto sprite performace testing,so this operation is invalid");
        return;
    }
    
    PerformBasicLayer::backCallback(sender);
}

void SpriteMenuLayer::showCurrentTest()
{
    SpriteMainScene* scene = nullptr;
    auto pPreScene = (SpriteMainScene*) getParent();
    int nSubTest = pPreScene->getSubTestNum();
    int nNodes   = pPreScene->getNodesNum();

    switch (_curCase)
    {
    case 0:
        scene = new SpritePerformTest1;
        break;
    case 1:
        scene = new SpritePerformTest2;
        break;
    case 2:
        scene = new SpritePerformTest3;
        break;
    case 3:
        scene = new SpritePerformTest4;
        break;
    case 4:
        scene = new SpritePerformTest5;
        break;
    case 5:
        scene = new SpritePerformTest6;
        break;
    case 6:
        scene = new SpritePerformTest7;
        break;
    }
    
    SpriteMainScene::_s_nSpriteCurCase = _curCase;

    if (scene)
    {
        scene->initWithSubTest(nSubTest, nNodes);
        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
}
////////////////////////////////////////////////////////
//
// SpriteMainScene
//
////////////////////////////////////////////////////////

bool SpriteMainScene::_s_autoTest = false;
int  SpriteMainScene::_s_nSpriteCurCase = 0;

void SpriteMainScene::initWithSubTest(int asubtest, int nNodes)
{
    //srandom(0);

    subtestNumber = asubtest;
    _subTest = new SubTest;
    _subTest->initWithSubTest(asubtest, this);

    auto s = Director::getInstance()->getWinSize();

    lastRenderedCount = 0;
    quantityNodes = 0;

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

    // add menu
    auto menuLayer = new SpriteMenuLayer(true, TEST_COUNT, SpriteMainScene::_s_nSpriteCurCase);
    addChild(menuLayer, 1, kTagMenuLayer);
    menuLayer->release();
    
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

    while(quantityNodes < nNodes)
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
        log("It's auto sprite performace testing,so this operation is invalid");
        return;
    }
    
    subtestNumber = static_cast<MenuItemFont*>(sender)->getTag();
    auto menu = static_cast<SpriteMenuLayer*>( getChildByTag(kTagMenuLayer) );
    menu->restartCallback(sender);
}

void SpriteMainScene::updateNodes()
{
    if( quantityNodes != lastRenderedCount )
    {
        auto infoLabel = (Label *) getChildByTag(kTagInfoLayer);
        char str[16] = {0};
        sprintf(str, "%u nodes", quantityNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityNodes;
    }
}

void SpriteMainScene::onIncrease(Ref* sender)
{    
    if( quantityNodes >= kMaxNodes)
        return;

    for( int i=0;i< kNodesIncrease;i++)
    {
        auto sprite = _subTest->createSpriteWithTag(quantityNodes);
        doTest(sprite);
        quantityNodes++;
    }

    updateNodes();
}

void SpriteMainScene::onDecrease(Ref* sender)
{
    
    if( quantityNodes <= 0 )
        return;

    for( int i=0;i < kNodesIncrease;i++)
    {
        quantityNodes--;
        _subTest->removeByTag(quantityNodes);
    }

    updateNodes();
}

void  SpriteMainScene::dumpProfilerFPS()
{
    if (_vecFPS.empty())
    {
        log("Error: the FPS vector is empty");
        return;
    }
    
    auto iter = _vecFPS.begin();
    float minFPS = *iter;
    float maxFPS = *iter;
    float totalFPS = 0.0f;
    float averagerFPS = 0.0f;
    for (auto fps : _vecFPS)
    {
        CCLOG("fps is :%f\n",fps);
        minFPS = std::min(minFPS, fps);
        maxFPS = std::max(maxFPS, fps);
        totalFPS += fps;
    }
    
    averagerFPS = totalFPS / _vecFPS.size();
    log("Cur test: %d, cur sub item :%d,cur sprite nums:%d, the min FPS value is %.1f,the max FPS value is %.1f,the averager FPS is %.1f", SpriteMainScene::_s_nSpriteCurCase, subtestNumber, quantityNodes, minFPS, maxFPS, averagerFPS);
    
}

void SpriteMainScene::updateAutoTest(float dt)
{
    if (SpriteMainScene::_s_autoTest)
    {
        _executeTimes += 1;
        _vecFPS.push_back(Director::getInstance()->getFrameRate());
        if ( _executeTimes >= SpriteMainScene::MAX_AUTO_TEST_TIMES )
        {
            dumpProfilerFPS();
            nextAutoTest();
        }
    }
}

void SpriteMainScene::onEnter()
{
    Scene::onEnter();
    
    if ( SpriteMainScene::_s_autoTest )
    {
        _vecFPS.clear();
        _executeTimes = 0;
        
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        sched->schedule(schedule_selector(SpriteMainScene::updateAutoTest), this, 0.2f, false);
        
    }
}

void SpriteMainScene::onExit()
{
    if ( SpriteMainScene::_s_autoTest )
    {
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        
        sched->unschedule(schedule_selector(SpriteMainScene::updateAutoTest), this );
    }
    
    Scene::onExit();
}

void  SpriteMainScene::autoShowSpriteTests(int curCase, int subTest,int nodes)
{
    
    SpriteMainScene* scene = nullptr;
    
    switch (curCase)
    {
        case 0:
            scene = new SpritePerformTest1;
            break;
        case 1:
            scene = new SpritePerformTest2;
            break;
        case 2:
            scene = new SpritePerformTest3;
            break;
        case 3:
            scene = new SpritePerformTest4;
            break;
        case 4:
            scene = new SpritePerformTest5;
            break;
        case 5:
            scene = new SpritePerformTest6;
            break;
        case 6:
            scene = new SpritePerformTest7;
            break;
    }
    
    SpriteMainScene::_s_nSpriteCurCase = curCase;
    
    if (scene)
    {
        scene->initWithSubTest(subTest, nodes);
        Director::getInstance()->replaceScene(scene);
        scene->release();
    }
}

void SpriteMainScene::beginAutoTest()
{
    if (0 != SpriteMainScene::_s_nSpriteCurCase)
    {
        SpriteMainScene::_s_nSpriteCurCase = 0;
    }
    
    auto scene = new SpritePerformTest1;
    scene->initWithSubTest(1, 500);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void  SpriteMainScene::endAutoTest()
{
    SpriteMainScene::_s_autoTest = false;
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    
    sched->unschedule( schedule_selector( SpriteMainScene::updateAutoTest ), this );
}

void  SpriteMainScene::nextAutoTest()
{
    if ( SpriteMainScene::_s_nSpriteCurCase < SpriteMainScene::MAX_SPRITE_TEST_CASE )
    {
        if ( subtestNumber < SpriteMainScene::MAX_SUB_TEST_NUMS )
        {
            subtestNumber += 1;
            autoShowSpriteTests(SpriteMainScene::_s_nSpriteCurCase, subtestNumber, quantityNodes);
        }
        else if ( subtestNumber == SpriteMainScene::MAX_SUB_TEST_NUMS )
        {
            if (quantityNodes == SpriteMainScene::AUTO_TEST_NODE_NUM1)
            {
                autoShowSpriteTests(SpriteMainScene::_s_nSpriteCurCase, 1, SpriteMainScene::AUTO_TEST_NODE_NUM2);
            }
            else
            {
                if (SpriteMainScene::_s_nSpriteCurCase + 1 < SpriteMainScene::MAX_SPRITE_TEST_CASE)
                {
                    SpriteMainScene::_s_nSpriteCurCase += 1;
                    autoShowSpriteTests(SpriteMainScene::_s_nSpriteCurCase, 1, SpriteMainScene::AUTO_TEST_NODE_NUM1);
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
    sched->unschedule( schedule_selector( SpriteMainScene::updateAutoTest ), this);
    
    auto autoTestMenu = dynamic_cast<Menu*>(getChildByTag(kTagAutoTestMenu));
    if (nullptr != autoTestMenu)
    {
        auto menuItemFont = dynamic_cast<MenuItemFont*>(autoTestMenu->getChildByTag(1));
        if (nullptr != menuItemFont)
        {
            menuItemFont->setString("Auto Test finish");
        }
    }
    
    log("Sprite performance test is  finish ");
}

void  SpriteMainScene::onAutoTest(Ref* sender)
{
    SpriteMainScene::_s_autoTest = !SpriteMainScene::_s_autoTest;
    MenuItemFont* menuItem = dynamic_cast<MenuItemFont*>(sender);
    if (nullptr != menuItem)
    {
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
// SpritePerformTest1
//
////////////////////////////////////////////////////////
std::string SpritePerformTest1::title() const
{
    char str[32] = {0};
    sprintf(str, "A (%d) position", subtestNumber);
    std::string strRet = str;
    return strRet;
}

std::string SpritePerformTest1::subtitle() const
{
    return "test 1";
}


void SpritePerformTest1::doTest(Sprite* sprite)
{
    performancePosition(sprite);
}
////////////////////////////////////////////////////////
//
// SpritePerformTest2
//
////////////////////////////////////////////////////////
std::string SpritePerformTest2::title() const
{
    char str[32] = {0};
    sprintf(str, "B (%d) scale", subtestNumber);
    std::string strRet = str;
    return strRet;
}

std::string SpritePerformTest2::subtitle() const
{
    return "test 2";
}

void SpritePerformTest2::doTest(Sprite* sprite)
{
    performanceScale(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTest3
//
////////////////////////////////////////////////////////
std::string SpritePerformTest3::title() const
{
    char str[32] = {0};
    sprintf(str, "C (%d) scale + rot", subtestNumber);
    std::string strRet = str;
    return strRet;
}

std::string SpritePerformTest3::subtitle() const
{
    return "test 3";
}

void SpritePerformTest3::doTest(Sprite* sprite)
{
    performanceRotationScale(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTest4
//
////////////////////////////////////////////////////////
std::string SpritePerformTest4::title() const
{
    char str[32] = {0};
    sprintf(str, "D (%d) 100%% out", subtestNumber);
    std::string strRet = str;
    return strRet;
}

std::string SpritePerformTest4::subtitle() const
{
    return "test 4";
}

void SpritePerformTest4::doTest(Sprite* sprite)
{
    performanceOut100(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTest5
//
////////////////////////////////////////////////////////
std::string SpritePerformTest5::title() const
{
    char str[32] = {0};
    sprintf(str, "E (%d) 80%% out", subtestNumber);
    std::string strRet = str;
    return strRet;
}

std::string SpritePerformTest5::subtitle() const
{
    return "test 5";
}

void SpritePerformTest5::doTest(Sprite* sprite)
{
    performanceout20(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTest6
//
////////////////////////////////////////////////////////
std::string SpritePerformTest6::title() const
{
    char str[32] = {0};
    sprintf(str, "F (%d) actions", subtestNumber);
    std::string strRet = str;
    return strRet;
}

std::string SpritePerformTest6::subtitle() const
{
    return "test 6";
}

void SpritePerformTest6::doTest(Sprite* sprite)
{
    performanceActions(sprite);
}

////////////////////////////////////////////////////////
//
// SpritePerformTest7
//
////////////////////////////////////////////////////////
std::string SpritePerformTest7::title() const
{
    char str[32] = {0};
    sprintf(str, "G (%d) actions 80%% out", subtestNumber);
    std::string strRet = str;
    return strRet;
}

std::string SpritePerformTest7::subtitle() const
{
    return "test 7";
}

void SpritePerformTest7::doTest(Sprite* sprite)
{
    performanceActions20(sprite);
}

void runSpriteTest()
{
    SpriteMainScene::_s_autoTest = false;
    auto scene = new SpritePerformTest1;
    scene->initWithSubTest(1, 50);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}
