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

void SubTest::initWithSubTest(int nSubTest, CCNode* p)
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
    CCTextureCache *mgr = CCTextureCache::sharedTextureCache();
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
            CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
            batchNode = CCSpriteBatchNode::create("Images/grossinis_sister1.png", 100);
            p->addChild(batchNode, 0);
            break;
        case 3:
            CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
            batchNode = CCSpriteBatchNode::create("Images/grossinis_sister1.png", 100);
            p->addChild(batchNode, 0);
            break;

            ///
        case 5:
            CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
            batchNode = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
            p->addChild(batchNode, 0);
            break;                
        case 6:
            CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
            batchNode = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
            p->addChild(batchNode, 0);
            break;

            ///
        case 8:
            CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
            batchNode = CCSpriteBatchNode::create("Images/spritesheet1.png", 100);
            p->addChild(batchNode, 0);
            break;
        case 9:
            CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
            batchNode = CCSpriteBatchNode::create("Images/spritesheet1.png", 100);
            p->addChild(batchNode, 0);
            break;

        default:
            break;
    }

    if (batchNode)
    {
        batchNode->retain();
    }

    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);
}

CCSprite* SubTest::createSpriteWithTag(int tag)
{
    // create 
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);

    CCSprite* sprite = NULL;
    switch (subtestNumber)
    {
        case 1:
            {
                sprite = CCSprite::create("Images/grossinis_sister1.png");
                parent->addChild(sprite, 0, tag+100);
                break;
            }
        case 2:
        case 3: 
            {
                sprite = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(0, 0, 52, 139));
                batchNode->addChild(sprite, 0, tag+100);
                break;
            }
        case 4:
            {
                int idx = (CCRANDOM_0_1() * 1400 / 100) + 1;
                char str[32] = {0};
                sprintf(str, "Images/grossini_dance_%02d.png", idx);
                sprite = CCSprite::create(str);
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
                sprite = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(x,y,85,121));
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
                sprite = CCSprite::create(str);
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
                sprite = CCSprite::createWithTexture(batchNode->getTexture(), CCRectMake(x,y,32,32));
                batchNode->addChild(sprite, 0, tag+100);
                break;
            }

        default:
            break;
    }

    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);

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
    SpriteMainScene* pScene = NULL;
    SpriteMainScene* pPreScene = (SpriteMainScene*) getParent();
    int nSubTest = pPreScene->getSubTestNum();
    int nNodes   = pPreScene->getNodesNum();

    switch (m_nCurCase)
    {
    case 0:
        pScene = new SpritePerformTest1;
        break;
    case 1:
        pScene = new SpritePerformTest2;
        break;
    case 2:
        pScene = new SpritePerformTest3;
        break;
    case 3:
        pScene = new SpritePerformTest4;
        break;
    case 4:
        pScene = new SpritePerformTest5;
        break;
    case 5:
        pScene = new SpritePerformTest6;
        break;
    case 6:
        pScene = new SpritePerformTest7;
        break;
    }
    s_nSpriteCurCase = m_nCurCase;

    if (pScene)
    {
        pScene->initWithSubTest(nSubTest, nNodes);
        CCDirector::sharedDirector()->replaceScene(pScene);
        pScene->release();
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
    m_pSubTest = new SubTest;
    m_pSubTest->initWithSubTest(asubtest, this);

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    lastRenderedCount = 0;
    quantityNodes = 0;

    CCMenuItemFont::setFontSize(65);
    CCMenuItemFont *decrease = CCMenuItemFont::create(" - ", this, menu_selector(SpriteMainScene::onDecrease));
    decrease->setColor(ccc3(0,200,20));
    CCMenuItemFont *increase = CCMenuItemFont::create(" + ", this, menu_selector(SpriteMainScene::onIncrease));
    increase->setColor(ccc3(0,200,20));

    CCMenu *menu = CCMenu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(s.width/2, s.height-65));
    addChild(menu, 1);

    CCLabelTTF *infoLabel = CCLabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(ccc3(0,200,20));
    infoLabel->setPosition(ccp(s.width/2, s.height-90));
    addChild(infoLabel, 1, kTagInfoLayer);

    // add menu
    SpriteMenuLayer* pMenu = new SpriteMenuLayer(true, TEST_COUNT, s_nSpriteCurCase);
    addChild(pMenu, 1, kTagMenuLayer);
    pMenu->release();

    // Sub Tests
    CCMenuItemFont::setFontSize(32);
    CCMenu* pSubMenu = CCMenu::create();
    for (int i = 1; i <= 9; ++i)
    {
        char str[10] = {0};
        sprintf(str, "%d ", i);
        CCMenuItemFont* itemFont = CCMenuItemFont::create(str, this, menu_selector(SpriteMainScene::testNCallback));
        itemFont->setTag(i);
        pSubMenu->addChild(itemFont, 10);

        if( i<= 3)
            itemFont->setColor(ccc3(200,20,20));
        else if(i <= 6)
            itemFont->setColor(ccc3(0,200,20));
        else
            itemFont->setColor(ccc3(0,20,200));
    }

    pSubMenu->alignItemsHorizontally();
    pSubMenu->setPosition(ccp(s.width/2, 80));
    addChild(pSubMenu, 2);

    // add title label
    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-32));
    label->setColor(ccc3(255,255,40));

    while(quantityNodes < nNodes)
        onIncrease(this);
}

std::string SpriteMainScene::title()
{
    return "No title";
}

SpriteMainScene::~SpriteMainScene()
{
    if (m_pSubTest)
    {
        delete m_pSubTest;
        m_pSubTest = NULL;
    }
}

void SpriteMainScene::testNCallback(CCObject* pSender)
{
    subtestNumber = ((CCMenuItemFont*) pSender)->getTag();
    SpriteMenuLayer* pMenu = (SpriteMenuLayer*)getChildByTag(kTagMenuLayer);
    pMenu->restartCallback(pSender);
}

void SpriteMainScene::updateNodes()
{
    if( quantityNodes != lastRenderedCount )
    {
        CCLabelTTF *infoLabel = (CCLabelTTF *) getChildByTag(kTagInfoLayer);
        char str[16] = {0};
        sprintf(str, "%u nodes", quantityNodes);
        infoLabel->setString(str);

        lastRenderedCount = quantityNodes;
    }
}

void SpriteMainScene::onIncrease(CCObject* pSender)
{
    if( quantityNodes >= kMaxNodes)
        return;

    for( int i=0;i< kNodesIncrease;i++)
    {
        CCSprite *sprite = m_pSubTest->createSpriteWithTag(quantityNodes);
        doTest(sprite);
        quantityNodes++;
    }

    updateNodes();
}

void SpriteMainScene::onDecrease(CCObject* pSender)
{
    if( quantityNodes <= 0 )
        return;

    for( int i=0;i < kNodesIncrease;i++)
    {
        quantityNodes--;
        m_pSubTest->removeByTag(quantityNodes);
    }

    updateNodes();
}

////////////////////////////////////////////////////////
//
// For test functions
//
////////////////////////////////////////////////////////
void performanceActions(CCSprite* pSprite)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite->setPosition(ccp((rand() % (int)size.width), (rand() % (int)size.height)));

    float period = 0.5f + (rand() % 1000) / 500.0f;
    CCRotateBy* rot = CCRotateBy::create(period, 360.0f * CCRANDOM_0_1());
    CCActionInterval* rot_back = rot->reverse();
    CCAction *permanentRotation = CCRepeatForever::create(CCSequence::create(rot, rot_back, NULL));
    pSprite->runAction(permanentRotation);

    float growDuration = 0.5f + (rand() % 1000) / 500.0f;
    CCActionInterval *grow = CCScaleBy::create(growDuration, 0.5f, 0.5f);
    CCAction *permanentScaleLoop = CCRepeatForever::create(CCSequence::create(grow, grow->reverse(), NULL));
    pSprite->runAction(permanentScaleLoop);
}

void performanceActions20(CCSprite* pSprite)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if( CCRANDOM_0_1() < 0.2f )
        pSprite->setPosition(ccp((rand() % (int)size.width), (rand() % (int)size.height)));
    else
        pSprite->setPosition(ccp( -1000, -1000));

    float period = 0.5f + (rand() % 1000) / 500.0f;
    CCRotateBy* rot = CCRotateBy::create(period, 360.0f * CCRANDOM_0_1());
    CCActionInterval* rot_back = rot->reverse();
    CCAction *permanentRotation = CCRepeatForever::create(CCSequence::create(rot, rot_back, NULL));
    pSprite->runAction(permanentRotation);

    float growDuration = 0.5f + (rand() % 1000) / 500.0f;
    CCActionInterval *grow = CCScaleBy::create(growDuration, 0.5f, 0.5f);
    CCAction *permanentScaleLoop = CCRepeatForever::create(CCSequence::createWithTwoActions(grow, grow->reverse()));
    pSprite->runAction(permanentScaleLoop);
}

void performanceRotationScale(CCSprite* pSprite)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite->setPosition(ccp((rand() % (int)size.width), (rand() % (int)size.height)));
    pSprite->setRotation(CCRANDOM_0_1() * 360);
    pSprite->setScale(CCRANDOM_0_1() * 2);
}

void performancePosition(CCSprite* pSprite)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite->setPosition(ccp((rand() % (int)size.width), (rand() % (int)size.height)));
}

void performanceout20(CCSprite* pSprite)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    if( CCRANDOM_0_1() < 0.2f )
        pSprite->setPosition(ccp((rand() % (int)size.width), (rand() % (int)size.height)));
    else
        pSprite->setPosition(ccp( -1000, -1000));
}

void performanceOut100(CCSprite* pSprite)
{
    pSprite->setPosition(ccp( -1000, -1000));
}

void performanceScale(CCSprite* pSprite)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite->setPosition(ccp((rand() % (int)size.width), (rand() % (int)size.height)));
    pSprite->setScale(CCRANDOM_0_1() * 100 / 50);
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

void SpritePerformTest1::doTest(CCSprite* sprite)
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

void SpritePerformTest2::doTest(CCSprite* sprite)
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

void SpritePerformTest3::doTest(CCSprite* sprite)
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

void SpritePerformTest4::doTest(CCSprite* sprite)
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

void SpritePerformTest5::doTest(CCSprite* sprite)
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

void SpritePerformTest6::doTest(CCSprite* sprite)
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

void SpritePerformTest7::doTest(CCSprite* sprite)
{
    performanceActions20(sprite);
}

void runSpriteTest()
{
    SpriteMainScene* pScene = new SpritePerformTest1;
    pScene->initWithSubTest(1, 50);
    CCDirector::sharedDirector()->replaceScene(pScene);
    pScene->release();
}
