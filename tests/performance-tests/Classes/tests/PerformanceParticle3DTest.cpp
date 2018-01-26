#include "PerformanceParticle3DTest.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
#include "Profile.h"

#define DELAY_TIME              4
#define STAT_TIME               3

USING_NS_CC;
using namespace cocos2d::ui;

static int kTagInfoLayer = 1;
static int kTagParticleSystem = 1001;

static int kMaxParticles = 14000;
static int kNodesIncrease = 1;

static int autoTestParticleCounts[] = {
    200, 500, 800
};

PerformceParticle3DTests::PerformceParticle3DTests()
{
    ADD_TEST_CASE(Particle3DPerformTest);
}

////////////////////////////////////////////////////////
//
// Particle3DMainScene
//
////////////////////////////////////////////////////////
void Particle3DMainScene::initScene()
{
    //srandom(0);

    isStating = false;
    auto s = Director::getInstance()->getWinSize();

    _lastRenderedCount = 0;
    _quantityParticles = 0;

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [=](Ref *sender) {
        _quantityParticles -= kNodesIncrease;
        if( _quantityParticles < 0 )
            _quantityParticles = 0;

        updateQuantityLabel();
        removeChildByTag(kTagParticleSystem + _quantityParticles, true);
    });
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [=](Ref *sender) {
        _quantityParticles += kNodesIncrease;
        if( _quantityParticles > kMaxParticles )
            _quantityParticles = kMaxParticles;

        updateQuantityLabel();
        createParticleSystem(_quantityParticles - 1);
    });
    increase->setColor(Color3B(0,200,20));

    auto menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width/2, s.height/2+15));
    addChild(menu, 1);

    auto infoLabel = Label::createWithTTF("0 Particle Systems", "fonts/Marker Felt.ttf", 30);
    infoLabel->setColor(Color3B(0,200,20));
    infoLabel->setPosition(Vec2(s.width/2, s.height - 90));
    addChild(infoLabel, 1, kTagInfoLayer);

    auto camera = Camera::createPerspective(30.0f, s.width / s.height, 1.0f, 1000.0f);
    camera->setPosition3D(Vec3(0.0f, 0.0f, 150.0f));
    camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);

    TTFConfig config("fonts/tahoma.ttf",10);
    _particleLab = Label::createWithTTF(config,"Particle Count: 0",TextHAlignment::LEFT);
    _particleLab->setPosition(Vec2(0.0f, s.height / 6.0f));
    _particleLab->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(_particleLab);
    _quantityParticles = 1;
    updateQuantityLabel();
    createParticleSystem(_quantityParticles - 1);
    
    schedule(CC_SCHEDULE_SELECTOR(Particle3DMainScene::step));
}

void Particle3DMainScene::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    
    auto director = Director::getInstance();
    auto sched = director->getScheduler();
    
    sched->unscheduleAllForTarget(this);
}

void Particle3DMainScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    
    if (this->isAutoTesting()) {
        Profile::getInstance()->testCaseBegin("Particle3DTest",
                                              genStrVector("ParticleSystemCount", nullptr),
                                              genStrVector("Avg", "Min", "Max", nullptr));
        autoTestIndex = 0;
        
        doAutoTest();
    }
}

void Particle3DMainScene::removeAllParticles()
{
    for (int i = 0; i < _quantityParticles; i++) {
        removeChildByTag(kTagParticleSystem + i, true);
    }
    _quantityParticles = 0;
}

void Particle3DMainScene::doAutoTest()
{
    isStating = false;
    statCount = 0;
    totalStatTime = 0.0f;
    minFrameRate = -1.0f;
    maxFrameRate = -1.0f;
    
    removeAllParticles();
    _quantityParticles = autoTestParticleCounts[autoTestIndex];
    updateQuantityLabel();
    for (int i = 0; i < _quantityParticles; i++) {
        createParticleSystem(i);
    }
    
    schedule(CC_SCHEDULE_SELECTOR(Particle3DMainScene::beginStat), DELAY_TIME);
    schedule(CC_SCHEDULE_SELECTOR(Particle3DMainScene::endStat), DELAY_TIME + STAT_TIME);
}

void Particle3DMainScene::beginStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(Particle3DMainScene::beginStat));
    isStating = true;
}

void Particle3DMainScene::endStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(Particle3DMainScene::endStat));
    isStating = false;

    // record test data
    auto avgStr = genStr("%.2f", (float) statCount / totalStatTime);
    Profile::getInstance()->addTestResult(genStrVector(genStr("%d", _quantityParticles).c_str(), nullptr),
                                          genStrVector(avgStr.c_str(), genStr("%.2f", minFrameRate).c_str(),
                                                       genStr("%.2f", maxFrameRate).c_str(), nullptr));

    // check the auto test is end or not
    int autoTestCount = sizeof(autoTestParticleCounts) / sizeof(int);
    if (autoTestIndex >= (autoTestCount - 1))
    {
        // auto test end
        Profile::getInstance()->testCaseEnd();
        setAutoTesting(false);
    }
    else
    {
        autoTestIndex++;
    }
    doAutoTest();
}

void Particle3DMainScene::step(float dt)
{
    unsigned int count = 0;
    for (int i = 0; i < _quantityParticles; i++)
    {
         ParticleSystem3D *ps = static_cast<ParticleSystem3D *>(this->getChildByTag(kTagParticleSystem + i));
         if (ps){
            auto children = ps->getChildren();
            for (auto iter : children){
                ParticleSystem3D *child = dynamic_cast<ParticleSystem3D *>(iter);
                if (child){
                    count += child->getAliveParticleCount();
                }
            }
            
            char str[128];
            sprintf(str, "Particle Count: %d", count);
            _particleLab->setString(str);
        }
    }
    
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

void Particle3DMainScene::createParticleSystem(int idx)
{
    auto ps = PUParticleSystem3D::create("Particle3D/scripts/example_004.pu", "Particle3D/materials/pu_example.material");
    ps->setCameraMask((unsigned short)CameraFlag::USER1);
    ps->setPosition(CCRANDOM_MINUS1_1() * 50.0f, CCRANDOM_MINUS1_1() * 20.0f);
    ps->startParticleSystem();
    addChild(ps, 0, kTagParticleSystem + idx);
}

void Particle3DMainScene::updateQuantityLabel()
{
    if( _quantityParticles != _lastRenderedCount )
    {
        auto infoLabel = (Label *) getChildByTag(kTagInfoLayer);
        char str[64] = {0};
        sprintf(str, "%u Particle Systems", _quantityParticles);
        infoLabel->setString(str);

        _lastRenderedCount = _quantityParticles;
    }
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest1
//
////////////////////////////////////////////////////////
std::string Particle3DPerformTest::title() const
{
    return "Particle3D Test";
}

bool Particle3DPerformTest::init()
{
    if (Particle3DMainScene::init())
    {
        initScene();
        return true;
    }

    return false;
}
