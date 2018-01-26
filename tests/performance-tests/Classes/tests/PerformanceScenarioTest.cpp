#include "PerformanceScenarioTest.h"
#include "Profile.h"

USING_NS_CC;

#define DELAY_TIME              4
#define STAT_TIME               3

PerformceScenarioTests::PerformceScenarioTests()
{
    ADD_TEST_CASE(ScenarioTest);
}

////////////////////////////////////////////////////////
//
// ScenarioTest
//
////////////////////////////////////////////////////////
int ScenarioTest::_initParticleNum = 500;
int ScenarioTest::_parStepNum = 500;
int ScenarioTest::_initSpriteNum = 2000;
int ScenarioTest::_spriteStepNum = 500;
int ScenarioTest::_initParsysNum = 10;
int ScenarioTest::_parsysStepNum = 5;

typedef struct
{
    int spriteCount;
    int particleCount;
    int particleSystemCount;
} TestCaseInfo;

static TestCaseInfo autoTestCounts[] = {
    { 500, 500, 50 },
    { 1000, 1000, 100 },
    { 1500, 1500, 150 }
};

bool ScenarioTest::init()
{
    if (TestCase::init())
    {
        performTests();
        return true;
    }

    return false;
}

void ScenarioTest::performTests()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(ScenarioTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    _particleNumber = _initParticleNum;

    // get the window size & origin position
    auto s = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // add tile map
    _map1 = TMXTiledMap::create("TileMaps/iso-test.tmx");
    _map1->setAnchorPoint( Vec2(0.5, 0.5) );
    _map1->setPosition(origin);
    this->addChild(_map1);

    _map2 = TMXTiledMap::create("TileMaps/iso-test2.tmx");
    _map2->setAnchorPoint( Vec2(0.5, 0.5) );
    _map2->setPosition(origin);
    this->addChild(_map2);

    // add toggle menu item
    MenuItemFont::setFontSize(20);
    _itemToggle = MenuItemToggle::createWithCallback(nullptr,
                                                    MenuItemFont::create( "Add/Remove Sprite" ),
                                                    MenuItemFont::create( "Add/Remove Particle"),
                                                    MenuItemFont::create( "Add/Remove Particle System"),
                                                    nullptr);
    _itemToggle->setAnchorPoint(Vec2(0.0f, 0.5f));
    _itemToggle->setPosition(Vec2(origin.x, origin.y + s.height / 2));

    // add decrease & increase menu item
    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Ref *sender) {
		int idx = _itemToggle->getSelectedIndex();
        switch (idx) {
        case 0:
            removeSprites();
            break;
        case 1:
            removeParticles();
            break;
        case 2:
            removeParticleSystem();
            break;
        default:
            break;
        }
	});
    decrease->setPosition(Vec2(origin.x + s.width / 2 - 80, origin.y + 80));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [&](Ref *sender) {
		int idx = _itemToggle->getSelectedIndex();
        switch (idx) {
        case 0:
            addNewSprites(_spriteStepNum);
            break;
        case 1:
            addParticles(_parStepNum);
            break;
        case 2:
            addParticleSystem(_parsysStepNum);
            break;
        default:
            break;
        }
	});
    increase->setColor(Color3B(0,200,20));
    increase->setPosition(Vec2(origin.x + s.width / 2 + 80, origin.y + 80));
    
    auto menu = Menu::create(_itemToggle, decrease, increase, nullptr);
    menu->setPosition(Vec2(0.0f, 0.0f));
    addChild(menu, 10);

    
    // add tip labels
    _spriteLabel = Label::createWithTTF("Sprites : 0", "fonts/arial.ttf", 15);
    _spriteLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    addChild(_spriteLabel, 10);
    _spriteLabel->setPosition(Vec2(origin.x, origin.y + s.height/2 + 70));
    
    char str[32] = { 0 };
    sprintf(str, "Particles : %d", _particleNumber);
    _particleLabel = Label::createWithTTF(str, "fonts/arial.ttf", 15);
    _particleLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    addChild(_particleLabel, 10);
    _particleLabel->setPosition(Vec2(origin.x, origin.y + s.height/2 + 45));
    
    _parsysLabel = Label::createWithTTF("Particle System : 0", "fonts/arial.ttf", 15);
    _parsysLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    addChild(_parsysLabel, 10);
    _parsysLabel->setPosition(Vec2(origin.x, origin.y + s.height/2 + 20));

    // add sprites
    addNewSprites(_initSpriteNum);
    
    // add particle system
    addParticleSystem(_initParsysNum);
}

void ScenarioTest::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = touches[0];
    
    auto diff = touch->getDelta();
    auto currentPos1 = _map1->getPosition();
    _map1->setPosition(currentPos1 + diff);
    
    auto currentPos2 = _map2->getPosition();
    _map2->setPosition(currentPos2 + diff);
}

void ScenarioTest::addParticles(int num)
{
    _particleNumber += num;

    for (auto par : _parsysArray) {
        par->setTotalParticles(_particleNumber);
    }

    char str[25] = { 0 };
    sprintf(str, "Particles : %d", _particleNumber);
    _particleLabel->setString(str);
}

void ScenarioTest::removeParticles()
{
    if (_particleNumber <= 0) {
        return;
    }
    
    int removeNum = MIN(_particleNumber, _parStepNum);
    _particleNumber -= removeNum;

    for (auto par : _parsysArray) {
        par->setTotalParticles(_particleNumber);
    }

    char str[25] = { 0 };
    sprintf(str, "Particles : %d", _particleNumber);
    _particleLabel->setString(str);
}

void ScenarioTest::addNewSprites(int num)
{
    auto s = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < num; ++i) {
        int idx = (int)(CCRANDOM_0_1() * 1400.0f / 100.0f);
        int x = (idx%5) * 85;
        int y = (idx/5) * 121;

        auto sprite = Sprite::create("Images/grossini_dance_atlas.png", Rect(x,y,85,121) );
        addChild( sprite );
        
        float randomx = CCRANDOM_0_1();
        float randomy = CCRANDOM_0_1();
        sprite->setPosition(origin + Vec2(randomx * s.width, randomy * s.height));
        
        ActionInterval* action;
        float random = CCRANDOM_0_1();
        
        if( random < 0.20 )
            action = ScaleBy::create(3, 2);
        else if(random < 0.40)
            action = RotateBy::create(3, 360);
        else if( random < 0.60)
            action = Blink::create(1, 3);
        else if( random < 0.8 )
            action = TintBy::create(2, 0, -255, -255);
        else
            action = FadeOut::create(2);
        auto action_back = action->reverse();
        auto seq = Sequence::create( action, action_back, nullptr );
        
        sprite->runAction( RepeatForever::create(seq) );

        _spriteArray.pushBack(sprite);
    }

    char str[20] = {0};
    sprintf(str, "Sprites : %d", (int)_spriteArray.size());
    _spriteLabel->setString(str);
}

void ScenarioTest::removeSprites()
{
    ssize_t number = _spriteArray.size();
    if (number <= 0) {
        return;
    }

    ssize_t removeNum = MIN(number, _spriteStepNum);
    for (int i = 0; i < removeNum; ++i) {
        auto sprite = _spriteArray.getRandomObject();
        removeChild(sprite);
        _spriteArray.eraseObject(sprite);
    }
    
    char str[20] = {0};
    sprintf(str, "Sprites : %d", (int)_spriteArray.size());
    _spriteLabel->setString(str);
}

static const std::string _particleFiles[] = {
    "Particles/BoilingFoam.plist",
    "Particles/Galaxy.plist",
    "Particles/SmallSun.plist",
    "Particles/lines.plist",
    "Particles/Comet.plist",
    "Particles/LavaFlow.plist",
    "Particles/SpinningPeas.plist",
    "Particles/Flower.plist",
    "Particles/Phoenix.plist",
    "Particles/debian.plist",
};
void ScenarioTest::addParticleSystem(int num)
{
    int filesSize = sizeof(_particleFiles) / sizeof(std::string);
    auto s = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < num; ++i)
    {
        float randomIdx = CCRANDOM_0_1();
        int idx = (filesSize - 1) * randomIdx;
        std::string fileName = _particleFiles[idx];
        auto par = ParticleSystemQuad::create(fileName);

        float randomx = CCRANDOM_0_1();
        float randomy = CCRANDOM_0_1();
        par->setPosition(origin + Vec2(s.width * randomx, s.height * randomy));
        par->setTotalParticles(_particleNumber);
        addChild(par, 9);

        _parsysArray.pushBack(par);
    }

    char str[40] = {0};
    sprintf(str, "Particle System : %d", (int)_parsysArray.size());
    _parsysLabel->setString(str);
}

void ScenarioTest::removeParticleSystem()
{
    ssize_t number = _parsysArray.size();
    if (number <= 0) {
        return;
    }
    
    ssize_t removeNum = MIN(number, _parsysStepNum);
    for (int i = 0; i < removeNum; ++i) {
        auto par = _parsysArray.getRandomObject();
        removeChild(par);
        _parsysArray.eraseObject(par);
    }
    
    char str[40] = {0};
    sprintf(str, "Particle System : %d", (int)_parsysArray.size());
    _parsysLabel->setString(str);
}

void ScenarioTest::onEnter()
{
    TestCase::onEnter();
    
    if (isAutoTesting()) {
        autoTestIndex = 0;
        Profile::getInstance()->testCaseBegin("ScenarioTest",
                                              genStrVector("SpriteCount", "ParticleCount", "ParticleSystemCount", nullptr),
                                              genStrVector("Avg", "Min", "Max", nullptr));
        doAutoTest();
        scheduleUpdate();
    }
}

void ScenarioTest::onExit()
{
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    TestCase::onExit();
}

void ScenarioTest::update(float dt)
{
    if (isStating) {
        totalStatTime += dt;
        statCount++;
        
        auto curFrameRate = Director::getInstance()->getFrameRate();
        if (maxFrameRate < 0 || curFrameRate > maxFrameRate)
            maxFrameRate = curFrameRate;
        
        if (minFrameRate < 0 || curFrameRate < minFrameRate)
            minFrameRate = curFrameRate;
    }
}

void ScenarioTest::beginStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(ScenarioTest::beginStat));
    isStating = true;
}

void ScenarioTest::endStat(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(ScenarioTest::endStat));
    isStating = false;
    
    // record test data
    auto avgStr = genStr("%.2f", (float) statCount / totalStatTime);
    Profile::getInstance()->addTestResult(genStrVector(genStr("%d", _spriteArray.size()).c_str(),
                                                       genStr("%d", _particleNumber).c_str(),
                                                       genStr("%d", _parsysArray.size()).c_str(),
                                                       nullptr),
                                          genStrVector(avgStr.c_str(), genStr("%.2f", minFrameRate).c_str(),
                                                       genStr("%.2f", maxFrameRate).c_str(), nullptr));

    // check the auto test is end or not
    int autoTestCount = sizeof(autoTestCounts) / sizeof(TestCaseInfo);
    if (autoTestIndex >= (autoTestCount - 1))
    {
        // auto test end
        Profile::getInstance()->testCaseEnd();
        setAutoTesting(false);
        return;
    }

    autoTestIndex++;
    doAutoTest();
}

void ScenarioTest::doAutoTest()
{
    isStating = false;
    statCount = 0;
    totalStatTime = 0.0f;
    minFrameRate = -1.0f;
    maxFrameRate = -1.0f;
    
    // remove all nodes
    while (_spriteArray.size() > 0) {
        removeSprites();
    }
    while (_parsysArray.size() > 0) {
        removeParticleSystem();
    }
    
    // add nodes
    auto caseInfo = autoTestCounts[autoTestIndex];
    _particleNumber = 0;
    addNewSprites(caseInfo.spriteCount);
    addParticleSystem(caseInfo.particleSystemCount);
    addParticles(caseInfo.particleCount);

    schedule(CC_SCHEDULE_SELECTOR(ScenarioTest::beginStat), DELAY_TIME);
    schedule(CC_SCHEDULE_SELECTOR(ScenarioTest::endStat), DELAY_TIME + STAT_TIME);
}

std::string ScenarioTest::title() const
{
    return "Scenario Performance Test";
}
