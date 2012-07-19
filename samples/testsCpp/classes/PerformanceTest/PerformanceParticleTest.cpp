#include "PerformanceParticleTest.h"


enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagParticleSystem = 3,
    kTagLabelAtlas = 4,
    kTagMenuLayer = 1000,

    TEST_COUNT = 4,
};

enum {
    kMaxParticles = 14000,
    kNodesIncrease = 500,
};

static int s_nParCurIdx = 0;

////////////////////////////////////////////////////////
//
// ParticleMenuLayer
//
////////////////////////////////////////////////////////
ParticleMenuLayer::ParticleMenuLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{

}

void ParticleMenuLayer::showCurrentTest()
{
    ParticleMainScene* pScene = (ParticleMainScene*)getParent();
    int subTest = pScene->getSubTestNum();
    int parNum  = pScene->getParticlesNum();

    ParticleMainScene* pNewScene = NULL;

    switch (m_nCurCase)
    {
    case 0:
        pNewScene = new ParticlePerformTest1;
        break;
    case 1:
        pNewScene = new ParticlePerformTest2;
        break;
    case 2:
        pNewScene = new ParticlePerformTest3;
        break;
    case 3:
        pNewScene = new ParticlePerformTest4;
        break;
    }

    s_nParCurIdx = m_nCurCase;
    if (pNewScene)
    {
        pNewScene->initWithSubTest(subTest, parNum);

        CCDirector::sharedDirector()->replaceScene(pNewScene);
        pNewScene->release();
    }
}

////////////////////////////////////////////////////////
//
// ParticleMainScene
//
////////////////////////////////////////////////////////
void ParticleMainScene::initWithSubTest(int asubtest, int particles)
{
    //srandom(0);

    subtestNumber = asubtest;
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    lastRenderedCount = 0;
    quantityParticles = particles;

    CCMenuItemFont::setFontSize(65);
    CCMenuItemFont *decrease = CCMenuItemFont::create(" - ", this, menu_selector(ParticleMainScene::onDecrease));
    decrease->setColor(ccc3(0,200,20));
    CCMenuItemFont *increase = CCMenuItemFont::create(" + ", this, menu_selector(ParticleMainScene::onIncrease));
    increase->setColor(ccc3(0,200,20));

    CCMenu *menu = CCMenu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(s.width/2, s.height/2+15));
    addChild(menu, 1);

    CCLabelTTF *infoLabel = CCLabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(ccc3(0,200,20));
    infoLabel->setPosition(ccp(s.width/2, s.height - 90));
    addChild(infoLabel, 1, kTagInfoLayer);

    // particles on stage
    CCLabelAtlas *labelAtlas = CCLabelAtlas::create("0000", "fps_images.png", 12, 32, '.');
    addChild(labelAtlas, 0, kTagLabelAtlas);
    labelAtlas->setPosition(ccp(s.width-66,50));

    // Next Prev Test
    ParticleMenuLayer* pMenu = new ParticleMenuLayer(true, TEST_COUNT, s_nParCurIdx);
    addChild(pMenu, 1, kTagMenuLayer);
    pMenu->release();

    // Sub Tests
    CCMenuItemFont::setFontSize(40);
    CCMenu* pSubMenu = CCMenu::create();
    for (int i = 1; i <= 6; ++i)
    {
        char str[10] = {0};
        sprintf(str, "%d ", i);
        CCMenuItemFont* itemFont = CCMenuItemFont::create(str, this, menu_selector(ParticleMainScene::testNCallback));
        itemFont->setTag(i);
        pSubMenu->addChild(itemFont, 10);

        if (i <= 3)
        {
            itemFont->setColor(ccc3(200,20,20));
        }
        else
        {
            itemFont->setColor(ccc3(0,200,20));
        }
    }
    pSubMenu->alignItemsHorizontally();
    pSubMenu->setPosition(ccp(s.width/2, 80));
    addChild(pSubMenu, 2);

    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-32));
    label->setColor(ccc3(255,255,40));

    updateQuantityLabel();
    createParticleSystem();

    schedule(schedule_selector(ParticleMainScene::step));
}

std::string ParticleMainScene::title()
{
    return "No title";
}

void ParticleMainScene::step(float dt)
{
    CCLabelAtlas *atlas = (CCLabelAtlas*) getChildByTag(kTagLabelAtlas);
    CCParticleSystem *emitter = (CCParticleSystem*) getChildByTag(kTagParticleSystem);

    char str[10] = {0};
    sprintf(str, "%4d", emitter->getParticleCount());
    atlas->setString(str);
}

void ParticleMainScene::createParticleSystem()
{
    CCParticleSystem *particleSystem = NULL;

    /*
    * Tests:
    * 1: Point Particle System using 32-bit textures (PNG)
    * 2: Point Particle System using 16-bit textures (PNG)
    * 3: Point Particle System using 8-bit textures (PNG)
    * 4: Point Particle System using 4-bit textures (PVRTC)

    * 5: Quad Particle System using 32-bit textures (PNG)
    * 6: Quad Particle System using 16-bit textures (PNG)
    * 7: Quad Particle System using 8-bit textures (PNG)
    * 8: Quad Particle System using 4-bit textures (PVRTC)
    */
    removeChildByTag(kTagParticleSystem, true);

    // remove the "fire.png" from the TextureCache cache. 
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("Images/fire.png");
    CCTextureCache::sharedTextureCache()->removeTexture(texture);

//TODO:     if (subtestNumber <= 3)
//     {
//         particleSystem = new CCParticleSystemPoint();
//     }
//     else
    {
        particleSystem = new CCParticleSystemQuad();
    }
    
    switch( subtestNumber)
    {
    case 1:
        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
        break;
    case 2:
        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
        break;            
    case 3:
        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_A8);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
        break;                        
//     case 4:
//         particleSystem->initWithTotalParticles(quantityParticles);
//         ////---- particleSystem.texture = [[CCTextureCache sharedTextureCache] addImage:@"fire.pvr"];
//         particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
//         break;
    case 4:
        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
        break;
    case 5:
        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
        break;            
    case 6:
        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_A8);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
        break;                        
//     case 8:
//         particleSystem->initWithTotalParticles(quantityParticles);
//         ////---- particleSystem.texture = [[CCTextureCache sharedTextureCache] addImage:@"fire.pvr"];
//         particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/fire.png"));
//         break;
    default:
        particleSystem = NULL;
        CCLOG("Shall not happen!");
        break;
    }
    addChild(particleSystem, 0, kTagParticleSystem);
    particleSystem->release();

    doTest();

    // restore the default pixel format
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
}

void ParticleMainScene::testNCallback(CCObject* pSender)
{
    subtestNumber = ((CCNode*)pSender)->getTag();

    ParticleMenuLayer* pMenu = (ParticleMenuLayer*)getChildByTag(kTagMenuLayer);
    pMenu->restartCallback(pSender);
}

void ParticleMainScene::onIncrease(CCObject* pSender)
{
    quantityParticles += kNodesIncrease;
    if( quantityParticles > kMaxParticles )
        quantityParticles = kMaxParticles;

    updateQuantityLabel();
    createParticleSystem();
}

void ParticleMainScene::onDecrease(CCObject* pSender)
{
    quantityParticles -= kNodesIncrease;
    if( quantityParticles < 0 )
        quantityParticles = 0;

    updateQuantityLabel();
    createParticleSystem();
}

void ParticleMainScene::updateQuantityLabel()
{
    if( quantityParticles != lastRenderedCount )
    {
        CCLabelTTF *infoLabel = (CCLabelTTF *) getChildByTag(kTagInfoLayer);
        char str[20] = {0};
        sprintf(str, "%u particles", quantityParticles);
        infoLabel->setString(str);

        lastRenderedCount = quantityParticles;
    }
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest1
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest1::title()
{
    char str[20] = {0};
    sprintf(str, "A (%d) size=4", subtestNumber);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest1::doTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCParticleSystem *particleSystem = (CCParticleSystem*)getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(ccp(0,-90));

    // angle
    particleSystem->setAngle(90);
    particleSystem->setAngleVar(0);

    // radial
    particleSystem->setRadialAccel(0);
    particleSystem->setRadialAccelVar(0);

    // speed of particles
    particleSystem->setSpeed(180);
    particleSystem->setSpeedVar(50);

    // emitter position
    particleSystem->setPosition(ccp(s.width/2, 100));
    particleSystem->setPosVar(ccp(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() /particleSystem->getLife());

    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColor(startColor);

    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColorVar( startColorVar);

    ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    particleSystem->setEndColor(endColor);

    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};    
    particleSystem->setEndColorVar(endColorVar);

    // size, in pixels
    particleSystem->setEndSize(4.0f);
    particleSystem->setStartSize(4.0f);
    particleSystem->setEndSizeVar(0);
    particleSystem->setStartSizeVar(0);

    // additive
    particleSystem->setBlendAdditive(false);
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest2
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest2::title()
{
    char str[20] = {0};
    sprintf(str, "B (%d) size=8", subtestNumber);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest2::doTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCParticleSystem *particleSystem = (CCParticleSystem*) getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(ccp(0,-90));

    // angle
    particleSystem->setAngle(90);
    particleSystem->setAngleVar(0);

    // radial
    particleSystem->setRadialAccel(0);
    particleSystem->setRadialAccelVar(0);

    // speed of particles
    particleSystem->setSpeed(180);
    particleSystem->setSpeedVar(50);

    // emitter position
    particleSystem->setPosition(ccp(s.width/2, 100));
    particleSystem->setPosVar(ccp(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() / particleSystem->getLife());

    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColor(startColor);

    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColorVar(startColorVar);

    ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    particleSystem->setEndColor(endColor);

    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};    
    particleSystem->setEndColorVar(endColorVar);

    // size, in pixels
    particleSystem->setEndSize(8.0f);
    particleSystem->setStartSize(8.0f);
    particleSystem->setEndSizeVar(0);
    particleSystem->setStartSizeVar(0);

    // additive
    particleSystem->setBlendAdditive(false);
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest3
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest3::title()
{
    char str[20] = {0};
    sprintf(str, "C (%d) size=32", subtestNumber);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest3::doTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCParticleSystem *particleSystem = (CCParticleSystem*)getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(ccp(0,-90));

    // angle
    particleSystem->setAngle(90);
    particleSystem->setAngleVar(0);

    // radial
    particleSystem->setRadialAccel(0);
    particleSystem->setRadialAccelVar(0);

    // speed of particles
    particleSystem->setSpeed(180);
    particleSystem->setSpeedVar(50);

    // emitter position
    particleSystem->setPosition(ccp(s.width/2, 100));
    particleSystem->setPosVar(ccp(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() / particleSystem->getLife());

    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColor(startColor);

    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColorVar(startColorVar);

    ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    particleSystem->setEndColor(endColor);

    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};    
    particleSystem->setEndColorVar(endColorVar);

    // size, in pixels
    particleSystem->setEndSize(32.0f);
    particleSystem->setStartSize(32.0f);
    particleSystem->setEndSizeVar(0);
    particleSystem->setStartSizeVar(0);

    // additive
    particleSystem->setBlendAdditive(false);
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest4
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest4::title()
{
    char str[20] = {0};
    sprintf(str, "D (%d) size=64", subtestNumber);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest4::doTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCParticleSystem *particleSystem = (CCParticleSystem*) getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(ccp(0,-90));

    // angle
    particleSystem->setAngle(90);
    particleSystem->setAngleVar(0);

    // radial
    particleSystem->setRadialAccel(0);
    particleSystem->setRadialAccelVar(0);

    // speed of particles
    particleSystem->setSpeed(180);
    particleSystem->setSpeedVar(50);

    // emitter position
    particleSystem->setPosition(ccp(s.width/2, 100));
    particleSystem->setPosVar(ccp(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() / particleSystem->getLife());

    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColor(startColor);

    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    particleSystem->setStartColorVar(startColorVar);

    ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    particleSystem->setEndColor(endColor);

    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};    
    particleSystem->setEndColorVar(endColorVar);

    // size, in pixels
    particleSystem->setEndSize(64.0f);
    particleSystem->setStartSize(64.0f);
    particleSystem->setEndSizeVar(0);
    particleSystem->setStartSizeVar(0);

    // additive
    particleSystem->setBlendAdditive(false);

}

void runParticleTest()
{
    ParticleMainScene* pScene = new ParticlePerformTest1;
    pScene->initWithSubTest(1, kNodesIncrease);

    CCDirector::sharedDirector()->replaceScene(pScene);
    pScene->release();
}
