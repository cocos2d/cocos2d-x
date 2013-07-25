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
    ParticleMainScene* scene = (ParticleMainScene*)getParent();
    int subTest = scene->getSubTestNum();
    int parNum  = scene->getParticlesNum();

    ParticleMainScene* pNewScene = NULL;

    switch (_curCase)
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

    s_nParCurIdx = _curCase;
    if (pNewScene)
    {
        pNewScene->initWithSubTest(subTest, parNum);

        Director::getInstance()->replaceScene(pNewScene);
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
    Size s = Director::getInstance()->getWinSize();

    lastRenderedCount = 0;
    quantityParticles = particles;

    MenuItemFont::setFontSize(65);
    MenuItemFont *decrease = MenuItemFont::create(" - ", [&](Object *sender) {
		quantityParticles -= kNodesIncrease;
		if( quantityParticles < 0 )
			quantityParticles = 0;

		updateQuantityLabel();
		createParticleSystem();
	});
    decrease->setColor(Color3B(0,200,20));
    MenuItemFont *increase = MenuItemFont::create(" + ", [&](Object *sender) {
		quantityParticles += kNodesIncrease;
		if( quantityParticles > kMaxParticles )
			quantityParticles = kMaxParticles;

		updateQuantityLabel();
		createParticleSystem();
	});
    increase->setColor(Color3B(0,200,20));

    Menu *menu = Menu::create(decrease, increase, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(Point(s.width/2, s.height/2+15));
    addChild(menu, 1);

    LabelTTF *infoLabel = LabelTTF::create("0 nodes", "Marker Felt", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Point(s.width/2, s.height - 90));
    addChild(infoLabel, 1, kTagInfoLayer);

    // particles on stage
    LabelAtlas *labelAtlas = LabelAtlas::create("0000", "fps_images.png", 12, 32, '.');
    addChild(labelAtlas, 0, kTagLabelAtlas);
    labelAtlas->setPosition(Point(s.width-66,50));

    // Next Prev Test
    ParticleMenuLayer* menuLayer = new ParticleMenuLayer(true, TEST_COUNT, s_nParCurIdx);
    addChild(menuLayer, 1, kTagMenuLayer);
    menuLayer->release();

    // Sub Tests
    MenuItemFont::setFontSize(40);
    Menu* pSubMenu = Menu::create();
    for (int i = 1; i <= 6; ++i)
    {
        char str[10] = {0};
        sprintf(str, "%d ", i);
        MenuItemFont* itemFont = MenuItemFont::create(str, CC_CALLBACK_1(ParticleMainScene::testNCallback, this));
        itemFont->setTag(i);
        pSubMenu->addChild(itemFont, 10);

        if (i <= 3)
        {
            itemFont->setColor(Color3B(200,20,20));
        }
        else
        {
            itemFont->setColor(Color3B(0,200,20));
        }
    }
    pSubMenu->alignItemsHorizontally();
    pSubMenu->setPosition(Point(s.width/2, 80));
    addChild(pSubMenu, 2);

    LabelTTF *label = LabelTTF::create(title().c_str(), "Arial", 40);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-32));
    label->setColor(Color3B(255,255,40));

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
    LabelAtlas *atlas = (LabelAtlas*) getChildByTag(kTagLabelAtlas);
    ParticleSystem *emitter = (ParticleSystem*) getChildByTag(kTagParticleSystem);

    char str[10] = {0};
    sprintf(str, "%4d", emitter->getParticleCount());
    atlas->setString(str);
}

void ParticleMainScene::createParticleSystem()
{
    ParticleSystem *particleSystem = NULL;

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
    Texture2D *texture = TextureCache::getInstance()->addImage("Images/fire.png");
    TextureCache::getInstance()->removeTexture(texture);

//TODO:     if (subtestNumber <= 3)
//     {
//         particleSystem = new ParticleSystemPoint();
//     }
//     else
    {
        particleSystem = new ParticleSystemQuad();
    }
    
    switch( subtestNumber)
    {
    case 1:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
        break;
    case 2:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
        break;            
    case 3:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::A8);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
        break;                        
//     case 4:
//         particleSystem->initWithTotalParticles(quantityParticles);
//         ////---- particleSystem.texture = [[TextureCache sharedTextureCache] addImage:@"fire.pvr"];
//         particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
//         break;
    case 4:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
        break;
    case 5:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
        break;            
    case 6:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::A8);
        particleSystem->initWithTotalParticles(quantityParticles);
        particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
        break;                        
//     case 8:
//         particleSystem->initWithTotalParticles(quantityParticles);
//         ////---- particleSystem.texture = [[TextureCache sharedTextureCache] addImage:@"fire.pvr"];
//         particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
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
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
}

void ParticleMainScene::testNCallback(Object* sender)
{
    subtestNumber = static_cast<Node*>(sender)->getTag();

    auto menu = static_cast<ParticleMenuLayer*>( getChildByTag(kTagMenuLayer) );
    menu->restartCallback(sender);
}

void ParticleMainScene::updateQuantityLabel()
{
    if( quantityParticles != lastRenderedCount )
    {
        LabelTTF *infoLabel = (LabelTTF *) getChildByTag(kTagInfoLayer);
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
    Size s = Director::getInstance()->getWinSize();
    ParticleSystem *particleSystem = (ParticleSystem*)getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(Point(0,-90));

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
    particleSystem->setPosition(Point(s.width/2, 100));
    particleSystem->setPosVar(Point(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() /particleSystem->getLife());

    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColor(startColor);

    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColorVar( startColorVar);

    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    particleSystem->setEndColor(endColor);

    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
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
    Size s = Director::getInstance()->getWinSize();
    ParticleSystem *particleSystem = (ParticleSystem*) getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(Point(0,-90));

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
    particleSystem->setPosition(Point(s.width/2, 100));
    particleSystem->setPosVar(Point(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() / particleSystem->getLife());

    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColor(startColor);

    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColorVar(startColorVar);

    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    particleSystem->setEndColor(endColor);

    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
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
    Size s = Director::getInstance()->getWinSize();
    ParticleSystem *particleSystem = (ParticleSystem*)getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(Point(0,-90));

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
    particleSystem->setPosition(Point(s.width/2, 100));
    particleSystem->setPosVar(Point(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() / particleSystem->getLife());

    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColor(startColor);

    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColorVar(startColorVar);

    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    particleSystem->setEndColor(endColor);

    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);    
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
    Size s = Director::getInstance()->getWinSize();
    ParticleSystem *particleSystem = (ParticleSystem*) getChildByTag(kTagParticleSystem);

    // duration
    particleSystem->setDuration(-1);

    // gravity
    particleSystem->setGravity(Point(0,-90));

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
    particleSystem->setPosition(Point(s.width/2, 100));
    particleSystem->setPosVar(Point(s.width/2,0));

    // life of particles
    particleSystem->setLife(2.0f);
    particleSystem->setLifeVar(1);

    // emits per frame
    particleSystem->setEmissionRate(particleSystem->getTotalParticles() / particleSystem->getLife());

    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColor(startColor);

    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    particleSystem->setStartColorVar(startColorVar);

    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    particleSystem->setEndColor(endColor);

    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);   
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
    ParticleMainScene* scene = new ParticlePerformTest1;
    scene->initWithSubTest(1, kNodesIncrease);

    Director::getInstance()->replaceScene(scene);
    scene->release();
}
