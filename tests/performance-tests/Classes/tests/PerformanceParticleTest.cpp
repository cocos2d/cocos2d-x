#include "PerformanceParticleTest.h"
#include "Profile.h"

USING_NS_CC;

#define MAX_SUB_TEST_NUM        3
#define DELAY_TIME              4
#define STAT_TIME               3

enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagParticleSystem = 3,
    kTagLabelAtlas = 4,
    kTagTitle = 5,
    kTagMenuLayer = 1000,

    TEST_COUNT = 4,
};

enum {
    kMaxParticles = 14000,
    kNodesIncrease = 500,
};

int ParticleMainScene::quantityParticles = kNodesIncrease;
int ParticleMainScene::subtestNumber = 1;

static int autoTestParticleCounts[] = {
    1000, 2000, 3000
};

PerformceParticleTests::PerformceParticleTests()
{
    ADD_TEST_CASE(ParticlePerformTest1);
    ADD_TEST_CASE(ParticlePerformTest2);
    ADD_TEST_CASE(ParticlePerformTest3);
    ADD_TEST_CASE(ParticlePerformTest4);
}

////////////////////////////////////////////////////////
//
// ParticleMainScene
//
////////////////////////////////////////////////////////
ParticleMainScene::ParticleMainScene()
: particleSize(4)
{
    
}

bool ParticleMainScene::init()
{
    if (TestCase::init())
    {
        initWithSubTest(subtestNumber, quantityParticles);
        return true;
    }

    return false;
}

void ParticleMainScene::initWithSubTest(int asubtest, int particles)
{
    //srandom(0);

    isStating = false;
    subtestNumber = asubtest;
    auto s = Director::getInstance()->getWinSize();

    lastRenderedCount = 0;
    quantityParticles = particles;

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Ref *sender) {
		quantityParticles -= kNodesIncrease;
		if( quantityParticles < 0 )
			quantityParticles = 0;

		updateQuantityLabel();
		createParticleSystem();
	});
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [&](Ref *sender) {
		quantityParticles += kNodesIncrease;
		if( quantityParticles > kMaxParticles )
			quantityParticles = kMaxParticles;

		updateQuantityLabel();
		createParticleSystem();
	});
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = Label::createWithTTF("0 nodes", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height - 90));
    addChild(infoLabel, 1, kTagInfoLayer);

    // particles on stage
    auto labelAtlas = LabelAtlas::create("0000", "fps_images.png", 12, 32, '.');
    addChild(labelAtlas, 0, kTagLabelAtlas);
    labelAtlas->setPosition(Vec2(s.width-66,50));

    // Sub Tests
    MenuItemFont::setFontSize(40);
    auto pSubMenu = Menu::create();
    for (int i = 1; i <= MAX_SUB_TEST_NUM; ++i)
    {
        char str[10] = {0};
        sprintf(str, "%d ", i);
        auto itemFont = MenuItemFont::create(str, CC_CALLBACK_1(ParticleMainScene::testNCallback, this));
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
    pSubMenu->setPosition(Vec2(s.width/2, 80));
    addChild(pSubMenu, 2);

    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32);
    addChild(label, 1, kTagTitle);
    label->setPosition(Vec2(s.width/2, s.height-50));

    updateQuantityLabel();
    createParticleSystem();

    schedule(CC_SCHEDULE_SELECTOR(ParticleMainScene::step));
}

void ParticleMainScene::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();

    sched->unscheduleAllForTarget(this);
}

void ParticleMainScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();

    if (this->isAutoTesting()) {
        Profile::getInstance()->testCaseBegin("ParticleTest",
                                              genStrVector("Size", "TextureFormat", "ParticleCount", nullptr),
                                              genStrVector("Avg", "Min", "Max", nullptr));
        autoTestIndex = 0;
        subtestNumber = 1;
        
        doAutoTest();
    }
}

void ParticleMainScene::doAutoTest()
{
    isStating = false;
    statCount = 0;
    totalStatTime = 0.0f;
    minFrameRate = -1.0f;
    maxFrameRate = -1.0f;
    
    quantityParticles = autoTestParticleCounts[autoTestIndex];
    updateQuantityLabel();
    updateTitle();
    createParticleSystem();

    schedule(CC_SCHEDULE_SELECTOR(ParticleMainScene::beginStat), DELAY_TIME);
    schedule(CC_SCHEDULE_SELECTOR(ParticleMainScene::endStat), DELAY_TIME + STAT_TIME);
}

void ParticleMainScene::beginStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(ParticleMainScene::beginStat));
    isStating = true;
}

void ParticleMainScene::endStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(ParticleMainScene::endStat));
    isStating = false;

    // record test data
    std::string tf;
    switch (subtestNumber) {
        case 1:
            tf = "RGBA8888";
            break;
        case 2:
            tf = "RGBA4444";
            break;
        case 3:
            tf = "A8";
            break;
        default:
            tf = "unknown";
            break;
    }
    auto avgStr = genStr("%.2f", (float) statCount / totalStatTime);
    Profile::getInstance()->addTestResult(genStrVector(genStr("%d", particleSize).c_str(), tf.c_str(),
                                                       genStr("%d", quantityParticles).c_str(), nullptr),
                                          genStrVector(avgStr.c_str(), genStr("%.2f", minFrameRate).c_str(),
                                                       genStr("%.2f", maxFrameRate).c_str(), nullptr));

    // check the auto test is end or not
    int autoTestCount = sizeof(autoTestParticleCounts) / sizeof(int);
    if (autoTestIndex >= (autoTestCount - 1) &&
        subtestNumber >= MAX_SUB_TEST_NUM)
    {
        // auto test end
        Profile::getInstance()->testCaseEnd();
        setAutoTesting(false);
        return;
    }

    if (autoTestIndex >= (autoTestCount - 1))
    {
        autoTestIndex = 0;
        subtestNumber++;
    }
    else
    {
        autoTestIndex++;
    }
    doAutoTest();
}

void ParticleMainScene::step(float dt)
{
    auto atlas = (LabelAtlas*) getChildByTag(kTagLabelAtlas);
    auto emitter = (ParticleSystem*) getChildByTag(kTagParticleSystem);

    char str[10] = {0};
    sprintf(str, "%4d", emitter->getParticleCount());
    atlas->setString(str);
    
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

void ParticleMainScene::createParticleSystem()
{
    ParticleSystemQuad *particleSystem = nullptr;

    /*
    * Tests:
    * 1: Vec2 Particle System using 32-bit textures (PNG)
    * 2: Vec2 Particle System using 16-bit textures (PNG)
    * 3: Vec2 Particle System using 8-bit textures (PNG)
    * 4: Vec2 Particle System using 4-bit textures (PVRTC)

    * 5: Quad Particle System using 32-bit textures (PNG)
    * 6: Quad Particle System using 16-bit textures (PNG)
    * 7: Quad Particle System using 8-bit textures (PNG)
    * 8: Quad Particle System using 4-bit textures (PVRTC)
    */
    removeChildByTag(kTagParticleSystem, true);

    // remove the "fire.png" from the TextureCache cache. 
    auto texture = Director::getInstance()->getTextureCache()->addImage("Images/fire.png");
    Director::getInstance()->getTextureCache()->removeTexture(texture);

//TODO:     if (subtestNumber <= 3)
//     {
//         particleSystem = new (std::nothrow) ParticleSystemPoint();
//     }
//     else
    {
        particleSystem = ParticleSystemQuad::createWithTotalParticles(quantityParticles);
    }

    switch( subtestNumber)
    {
    case 1:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
        particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
        break;
    case 2:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
        particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
        break;            
    case 3:
        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::A8);
        particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
        break;                        
//     case 4:
//         particleSystem->initWithTotalParticles(quantityParticles);
//         ////---- particleSystem.texture = [[TextureCache sharedTextureCache] addImage:@"fire.pvr"];
//         particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
//         break;
//    case 4:
//        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
//        particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
//        break;
//    case 5:
//        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
//        particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
//        break;            
//    case 6:
//        Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::A8);
//        particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
//        break;                        
//     case 8:
//         ////---- particleSystem.texture = [[TextureCache sharedTextureCache] addImage:@"fire.pvr"];
//         particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
//         break;
    default:
        particleSystem = nullptr;
        CCLOG("Shall not happen!");
        break;
    }
    addChild(particleSystem, 0, kTagParticleSystem);

    doTest();

    // restore the default pixel format
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
}

void ParticleMainScene::doTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto particleSystem = (ParticleSystem*)getChildByTag(kTagParticleSystem);
    
    // duration
    particleSystem->setDuration(-1);
    
    // gravity
    particleSystem->setGravity(Vec2(0,-90));
    
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
    particleSystem->setPosition(Vec2(s.width/2, 100));
    particleSystem->setPosVar(Vec2(s.width/2,0));
    
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
    particleSystem->setEndSize(particleSize);
    particleSystem->setStartSize(particleSize);
    particleSystem->setEndSizeVar(0);
    particleSystem->setStartSizeVar(0);

    // additive
    particleSystem->setBlendAdditive(false);
}

void ParticleMainScene::testNCallback(Ref* sender)
{
    subtestNumber = static_cast<Node*>(sender)->getTag();

    this->restartTestCallback(sender);
}

void ParticleMainScene::updateQuantityLabel()
{
    if( quantityParticles != lastRenderedCount )
    {
        auto infoLabel = (Label *) getChildByTag(kTagInfoLayer);
        char str[20] = {0};
        sprintf(str, "%u particles", quantityParticles);
        infoLabel->setString(str);

        lastRenderedCount = quantityParticles;
    }
}

void ParticleMainScene::updateTitle()
{
    auto titleLabel = (Label *) getChildByTag(kTagTitle);
    titleLabel->setString(this->title());
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest1
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest1::title() const
{
    char str[32] = {0};
    sprintf(str, "A (%d) size=%d", subtestNumber, particleSize);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest1::initWithSubTest(int subtest, int particles)
{
    particleSize = 4;
    ParticleMainScene::initWithSubTest(subtest, particles);
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest2
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest2::title() const
{
    char str[20] = {0};
    sprintf(str, "B (%d) size=%d", subtestNumber, particleSize);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest2::initWithSubTest(int subtest, int particles)
{
    particleSize = 8;
    ParticleMainScene::initWithSubTest(subtest, particles);
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest3
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest3::title() const
{
    char str[20] = {0};
    sprintf(str, "C (%d) size=%d", subtestNumber, particleSize);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest3::initWithSubTest(int subtest, int particles)
{
    particleSize = 32;
    ParticleMainScene::initWithSubTest(subtest, particles);
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest4
//
////////////////////////////////////////////////////////
std::string ParticlePerformTest4::title() const
{
    char str[20] = {0};
    sprintf(str, "D (%d) size=%d", subtestNumber, particleSize);
    std::string strRet = str;
    return strRet;
}

void ParticlePerformTest4::initWithSubTest(int subtest, int particles)
{
    particleSize = 64;
    ParticleMainScene::initWithSubTest(subtest, particles);
}
