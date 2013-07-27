#include "PerformanceSpriteTest.h"

enum {
    kMaxNodes = 50000,
    kNodesIncrease = 250,

    TEST_COUNT = 7,
};

enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagMenuLayer = (kMaxNodes + 1000),
};

static int s_nSpriteCurCase = 0;

////////////////////////////////////////////////////////
//
// SubTest
//
////////////////////////////////////////////////////////
SubTest::~SubTest()
{
    if (batchNode)
    {
        batchNode->release();
        batchNode = NULL;
    }
}

void SubTest::initWithSubTest(int nSubTest, Node* p)
{
    subtestNumber = nSubTest;
    parent = p;
    batchNode = NULL;
    /*
    * Tests:
    * 1: 1 (32-bit) PNG sprite of 52 x 139
    * 2: 1 (32-bit) PNG Batch Node using 1 sprite of 52 x 139
    * 3: 1 (16-bit) PNG Batch Node using 1 sprite of 52 x 139
    * 4: 1 (4-bit) PVRTC Batch Node using 1 sprite of 52 x 139

    * 5: 14 (32-bit) PNG sprites of 85 x 121 each
    * 6: 14 (32-bit) PNG Batch Node of 85 x 121 each
    * 7: 14 (16-bit) PNG Batch Node of 85 x 121 each
    * 8: 14 (4-bit) PVRTC Batch Node of 85 x 121 each

    * 9: 64 (32-bit) sprites of 32 x 32 each
    *10: 64 (32-bit) PNG Batch Node of 32 x 32 each
    *11: 64 (16-bit) PNG Batch Node of 32 x 32 each
    *12: 64 (4-bit) PVRTC Batch Node of 32 x 32 each
    */

    // purge textures
    TextureCache *mgr = TextureCache::getInstance();
    //        [mgr removeAllTextures];
    mgr->removeTexture(mgr->addImage("Images/grossinis_sister1.png"));
    mgr->removeTexture(mgr->addImage("Images/grossini_dance_atlas.png"));
    mgr->removeTexture(mgr->addImage("Images/spritesheet1.png"));

    switch ( subtestNumber)
    {
        case 1:
        case 4:
        case 7:
            break;
            ///
        case 2:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            batchNode = SpriteBatchNode::create("Images/grossinis_sister1.png", 100);
            p->addChild(batchNode, 0);
            break;
        case 3:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            batchNode = SpriteBatchNode::create("Images/grossinis_sister1.png", 100);
            p->addChild(batchNode, 0);
            break;

            ///
        case 5:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            batchNode = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
            p->addChild(batchNode, 0);
            break;                
        case 6:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            batchNode = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
            p->addChild(batchNode, 0);
            break;

            ///
        case 8:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
            batchNode = SpriteBatchNode::create("Images/spritesheet1.png", 100);
            p->addChild(batchNode, 0);
            break;
        case 9:
            Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
            batchNode = SpriteBatchNode::create("Images/spritesheet1.png", 100);
            p->addChild(batchNode, 0);
            break;

        default:
            break;
    }

    if (batchNode)
    {
        batchNode->retain();
    }

    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
}

Sprite* SubTest::createSpriteWithTag(int tag)
{
    // create 
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);

    Sprite* sprite = NULL;
    switch (subtestNumber)
    {
        case 1:
            {
                sprite = Sprite::create("Images/grossinis_sister1.png");
                parent->addChild(sprite, 0, tag+100);
                break;
            }
        case 2:
        case 3: 
            {
                sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 52, 139));
                batchNode->addChild(sprite, 0, tag+100);
                break;
            }
        case 4:
            {
                int idx = (CCRANDOM_0_1() * 1400 / 100) + 1;
                char str[32] = {0};
                sprintf(str, "Images/grossini_dance_%02d.png", idx);
                sprite = Sprite::create(str);
                parent->addChild(sprite, 0, tag+100);
                break;
            }
        case 5:
        case 6:
            {
                int y,x;
                int r = (CCRANDOM_0_1() * 1400 / 100);

                y = r / 5;
                x = r % 5;

                x *= 85;
                y *= 121;
                sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(x,y,85,121));
                batchNode->addChild(sprite, 0, tag+100);
                break;
            }

        case 7:
            {
                int y,x;
                int r = (CCRANDOM_0_1() * 6400 / 100);

                y = r / 8;
                x = r % 8;

                char str[40] = {0};
                sprintf(str, "Images/sprites_test/sprite-%d-%d.png", x, y);
                sprite = Sprite::create(str);
                parent->addChild(sprite, 0, tag+100);
                break;
            }

        case 8:
        case 9:
            {
                int y,x;
                int r = (CCRANDOM_0_1() * 6400 / 100);

                y = r / 8;
                x = r % 8;

                x *= 32;
                y *= 32;
                sprite = Sprite::createWithTexture(batchNode->getTexture(), Rect(x,y,32,32));
                batchNode->addChild(sprite, 0, tag+100);
                break;
            }

        default:
            break;
    }

    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);

    return sprite;
}

void SubTest::removeByTag(int tag)
{
    switch (subtestNumber)
    {
        case 1:
        case 4:
        case 7:
            parent->removeChildByTag(tag+100, true);
            break;
        case 2:
        case 3:
        case 5:
        case 6:
        case 8:
        case 9:
            batchNode->removeChildAtIndex(tag, true);
            //            [batchNode removeChildByTag:tag+100 cleanup:YES];
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////
//
// SpriteMenuLayer
//
////////////////////////////////////////////////////////
void SpriteMenuLayer::showCurrentTest()
{
    SpriteMainScene* scene = NULL;
    SpriteMainScene* pPreScene = (SpriteMainScene*) getParent();
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
    s_nSpriteCurCase = _curCase;

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
void SpriteMainScene::initWithSubTest(int asubtest, int nNodes)
{
    //srandom(0);

    subtestNumber = asubtest;
    _subTest = new SubTest;
    _subTest->initWithSubTest(asubtest, this);

    Size s = Director::getInstance()->getWinSize();

    lastRenderedCount = 0;
    quantityNodes = 0;

    MenuItemFont::setFontSize(65);
    MenuItemFont *decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(SpriteMainScene::onDecrease, this));
    decrease->setColor(Color3B(0,200,20));
    MenuItemFont *increase = MenuItemFont::create(" + ", CC_CALLBACK_1(SpriteMainScene::onIncrease, this));
    increase->setColor(Color3B(0,200,20));

    Menu *menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height-65));
    addChild(menu, 1);

    LabelTTF *infoLabel = LabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height-90));
    addChild(infoLabel, 1, kTagInfoLayer);

    // add menu
    SpriteMenuLayer* menuLayer = new SpriteMenuLayer(true, TEST_COUNT, s_nSpriteCurCase);
    addChild(menuLayer, 1, kTagMenuLayer);
    menuLayer->release();

    // Sub Tests
    MenuItemFont::setFontSize(32);
    Menu* subMenu = Menu::create();
    for (int i = 1; i <= 9; ++i)
    {
        char str[10] = {0};
        sprintf(str, "%d ", i);
        MenuItemFont* itemFont = MenuItemFont::create(str, CC_CALLBACK_1(SpriteMainScene::testNCallback, this));
        itemFont->setTag(i);
        subMenu->addChild(itemFont, 10);

        if( i<= 3)
            itemFont->setColor(Color3B(200,20,20));
        else if(i <= 6)
            itemFont->setColor(Color3B(0,200,20));
        else
            itemFont->setColor(Color3B(0,20,200));
    }

    subMenu->alignItemsHorizontally();
    subMenu->setPosition(Point(s.width/2, 80));
    addChild(subMenu, 2);

    // add title label
    LabelTTF *label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));

    while(quantityNodes < nNodes)
        onIncrease(this);
}

std::string SpriteMainScene::title()
{
    return "No title";
}

SpriteMainScene::~SpriteMainScene()
{
    if (_subTest)
    {
        delete _subTest;
        _subTest = NULL;
    }
}

void SpriteMainScene::testNCallback(Object* sender)
{
    subtestNumber = static_cast<MenuItemFont*>(sender)->getTag();
    auto menu = static_cast<SpriteMenuLayer*>( getChildByTag(kTagMenuLayer) );
    menu->restartCallback(sender);
}

void SpriteMainScene::updateNodes()
{
    if( quantityNodes != lastRenderedCount )
    {
        LabelTTF *infoLabel = (LabelTTF *) getChildByTag(kTagInfoLayer);
        char str[16] = {0};
        sprintf(str, "%u nodes", quantityNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityNodes;
    }
}

void SpriteMainScene::onIncrease(Object* sender)
{
    if( quantityNodes >= kMaxNodes)
        return;

    for( int i=0;i< kNodesIncrease;i++)
    {
        Sprite *sprite = _subTest->createSpriteWithTag(quantityNodes);
        doTest(sprite);
        quantityNodes++;
    }

    updateNodes();
}

void SpriteMainScene::onDecrease(Object* sender)
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

////////////////////////////////////////////////////////
//
// For test functions
//
////////////////////////////////////////////////////////
void performanceActions(Sprite* sprite)
{
    Size size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point((rand() % (int)size.width), (rand() % (int)size.height)));

    float period = 0.5f + (rand() % 1000) / 500.0f;
    RotateBy* rot = RotateBy::create(period, 360.0f * CCRANDOM_0_1());
    ActionInterval* rot_back = rot->reverse();
    Action *permanentRotation = RepeatForever::create(Sequence::create(rot, rot_back, NULL));
    sprite->runAction(permanentRotation);

    float growDuration = 0.5f + (rand() % 1000) / 500.0f;
    ActionInterval *grow = ScaleBy::create(growDuration, 0.5f, 0.5f);
    Action *permanentScaleLoop = RepeatForever::create(Sequence::create(grow, grow->reverse(), NULL));
    sprite->runAction(permanentScaleLoop);
}

void performanceActions20(Sprite* sprite)
{
    Size size = Director::getInstance()->getWinSize();
    if( CCRANDOM_0_1() < 0.2f )
        sprite->setPosition(Point((rand() % (int)size.width), (rand() % (int)size.height)));
    else
        sprite->setPosition(Point( -1000, -1000));

    float period = 0.5f + (rand() % 1000) / 500.0f;
    RotateBy* rot = RotateBy::create(period, 360.0f * CCRANDOM_0_1());
    ActionInterval* rot_back = rot->reverse();
    Action *permanentRotation = RepeatForever::create(Sequence::create(rot, rot_back, NULL));
    sprite->runAction(permanentRotation);

    float growDuration = 0.5f + (rand() % 1000) / 500.0f;
    ActionInterval *grow = ScaleBy::create(growDuration, 0.5f, 0.5f);
    Action *permanentScaleLoop = RepeatForever::create(Sequence::createWithTwoActions(grow, grow->reverse()));
    sprite->runAction(permanentScaleLoop);
}

void performanceRotationScale(Sprite* sprite)
{
    Size size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point((rand() % (int)size.width), (rand() % (int)size.height)));
    sprite->setRotation(CCRANDOM_0_1() * 360);
    sprite->setScale(CCRANDOM_0_1() * 2);
}

void performancePosition(Sprite* sprite)
{
    Size size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point((rand() % (int)size.width), (rand() % (int)size.height)));
}

void performanceout20(Sprite* sprite)
{
    Size size = Director::getInstance()->getWinSize();

    if( CCRANDOM_0_1() < 0.2f )
        sprite->setPosition(Point((rand() % (int)size.width), (rand() % (int)size.height)));
    else
        sprite->setPosition(Point( -1000, -1000));
}

void performanceOut100(Sprite* sprite)
{
    sprite->setPosition(Point( -1000, -1000));
}

void performanceScale(Sprite* sprite)
{
    Size size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point((rand() % (int)size.width), (rand() % (int)size.height)));
    sprite->setScale(CCRANDOM_0_1() * 100 / 50);
}

////////////////////////////////////////////////////////
//
// SpritePerformTest1
//
////////////////////////////////////////////////////////
std::string SpritePerformTest1::title()
{
    char str[32] = {0};
    sprintf(str, "A (%d) position", subtestNumber);
    std::string strRet = str;
    return strRet;
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
std::string SpritePerformTest2::title()
{
    char str[32] = {0};
    sprintf(str, "B (%d) scale", subtestNumber);
    std::string strRet = str;
    return strRet;
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
std::string SpritePerformTest3::title()
{
    char str[32] = {0};
    sprintf(str, "C (%d) scale + rot", subtestNumber);
    std::string strRet = str;
    return strRet;
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
std::string SpritePerformTest4::title()
{
    char str[32] = {0};
    sprintf(str, "D (%d) 100%% out", subtestNumber);
    std::string strRet = str;
    return strRet;
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
std::string SpritePerformTest5::title()
{
    char str[32] = {0};
    sprintf(str, "E (%d) 80%% out", subtestNumber);
    std::string strRet = str;
    return strRet;
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
std::string SpritePerformTest6::title()
{
    char str[32] = {0};
    sprintf(str, "F (%d) actions", subtestNumber);
    std::string strRet = str;
    return strRet;
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
std::string SpritePerformTest7::title()
{
    char str[32] = {0};
    sprintf(str, "G (%d) actions 80%% out", subtestNumber);
    std::string strRet = str;
    return strRet;
}

void SpritePerformTest7::doTest(Sprite* sprite)
{
    performanceActions20(sprite);
}

void runSpriteTest()
{
    SpriteMainScene* scene = new SpritePerformTest1;
    scene->initWithSubTest(1, 50);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}
