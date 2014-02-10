#include "PerformanceScenarioTest.h"
#include "../testResource.h"

enum
{
    TEST_COUNT = 1,
};

static int s_nScenarioCurCase = 0;

////////////////////////////////////////////////////////
//
// ScenarioMenuLayer
//
////////////////////////////////////////////////////////
void ScenarioMenuLayer::showCurrentTest()
{
    Scene* scene = NULL;

    switch (_curCase)
    {
    case 0:
        scene = ScenarioTest::scene();
        break;
    }
    s_nScenarioCurCase = _curCase;

    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void ScenarioMenuLayer::onEnter()
{
    PerformBasicLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    // Title
    auto label = LabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition(Point(s.width/2, s.height-50));

    // Subtitle
    std::string strSubTitle = subtitle();
    if(strSubTitle.length())
    {
        auto l = LabelTTF::create(strSubTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(Point(s.width/2, s.height-80));
    }

    performTests();
}

std::string ScenarioMenuLayer::title() const
{
    return "no title";
}

std::string ScenarioMenuLayer::subtitle() const
{
    return "";
}

////////////////////////////////////////////////////////
//
// ScenarioTest
//
////////////////////////////////////////////////////////
static const int parStepNumber = 500;
void ScenarioTest::performTests()
{
    auto tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();
    
    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint( Point(0, 0) );
    
    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
    
    this->addChild(tilemap);
    
    auto s = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    _spriteLabel = LabelTTF::create("Sprites : 0", "Arial", 15);
    _spriteLabel->setAnchorPoint(Point(0.0f, 0.5f));
    addChild(_spriteLabel, 10);
    _spriteLabel->setPosition(Point(origin.x, origin.y + s.height/2 + 60));

    MenuItemFont::setFontSize(20);
    _itemToggle = MenuItemToggle::createWithCallback(nullptr,
                                                    MenuItemFont::create( "Add/Remove Sprite" ),
                                                    MenuItemFont::create( "Add/Remove Particle"),
                                                    NULL);
    _itemToggle->setAnchorPoint(Point(0.0f, 0.5f));
    _itemToggle->setPosition(Point(origin.x, origin.y + s.height / 2));

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [&](Object *sender) {
		int idx = _itemToggle->getSelectedIndex();
        switch (idx) {
        case 0:
            removeSprites();
            break;
        case 1:
            removeParticles();
            break;
        default:
            break;
        }
	});
    decrease->setPosition(Point(origin.x + s.width / 2 - 80, origin.y + 80));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [&](Object *sender) {
		int idx = _itemToggle->getSelectedIndex();
        switch (idx) {
        case 0:
            addNewSprites();
            break;
        case 1:
            addParticles();
            break;
        default:
            break;
        }
	});
    increase->setColor(Color3B(0,200,20));
    increase->setPosition(Point(origin.x + s.width / 2 + 80, origin.y + 80));
    
    auto menu = Menu::create(_itemToggle, decrease, increase, NULL);
    menu->setPosition(Point(0.0f, 0.0f));
    addChild(menu, 10);

    _particleNumber = parStepNumber;
    createParticle();

    char str[25] = { 0 };
    sprintf(str, "Particles : %d", _particleNumber);
    _particleLabel = LabelTTF::create(str, "Arial", 15);
    _particleLabel->setAnchorPoint(Point(0.0f, 0.5f));
    addChild(_particleLabel, 10);
    _particleLabel->setPosition(Point(origin.x, origin.y + s.height/2 + 30));
}

void ScenarioTest::addParticles()
{
    _particleNumber += parStepNumber;

    createParticle();

    char str[25] = { 0 };
    sprintf(str, "Particles : %d", _particleNumber);
    _particleLabel->setString(str);
}

void ScenarioTest::removeParticles()
{
    if (_particleNumber <= 0) {
        return;
    }
    
    int removeNum = MIN(_particleNumber, parStepNumber);
    _particleNumber -= removeNum;

    createParticle();

    char str[25] = { 0 };
    sprintf(str, "Particles : %d", _particleNumber);
    _particleLabel->setString(str);
}

static const int kTagParticleSystem = 567;
void ScenarioTest::createParticle()
{
    removeChildByTag(kTagParticleSystem, true);

    auto _particle = ParticleSystemQuad::createWithTotalParticles(_particleNumber);
    _particle->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
    addChild(_particle, 15, kTagParticleSystem);

    auto s = Director::getInstance()->getWinSize();

    // duration
    _particle->setDuration(-1);
    
    // gravity
    _particle->setGravity(Point(0,-90));
    
    // angle
    _particle->setAngle(90);
    _particle->setAngleVar(0);
    
    // radial
    _particle->setRadialAccel(0);
    _particle->setRadialAccelVar(0);
    
    // speed of particles
    _particle->setSpeed(180);
    _particle->setSpeedVar(50);
    
    // emitter position
    _particle->setPosition(Point(s.width/2, 100));
    _particle->setPosVar(Point(s.width/2,0));
    
    // life of particles
    _particle->setLife(2.0f);
    _particle->setLifeVar(1);
    
    // emits per frame
    _particle->setEmissionRate(_particle->getTotalParticles() /_particle->getLife());
    
    // color of particles
    Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
    _particle->setStartColor(startColor);
    
    Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
    _particle->setStartColorVar( startColorVar);
    
    Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
    _particle->setEndColor(endColor);
    
    Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);
    _particle->setEndColorVar(endColorVar);
    
    // size, in pixels
    _particle->setEndSize(4.0f);
    _particle->setStartSize(4.0f);
    _particle->setEndSizeVar(0);
    _particle->setStartSizeVar(0);
    
    // additive
    _particle->setBlendAdditive(false);
}

static const int spriteNumStep = 5;
void ScenarioTest::addNewSprites()
{
    for (int i = 0; i < spriteNumStep; ++i) {
        int idx = (int)(CCRANDOM_0_1() * 1400.0f / 100.0f);
        int x = (idx%5) * 85;
        int y = (idx/5) * 121;
        
        auto s = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        auto sprite = Sprite::create("Images/grossini_dance_atlas.png", Rect(x,y,85,121) );
        addChild( sprite );
        
        float randomx = CCRANDOM_0_1();
        float randomy = CCRANDOM_0_1();
        sprite->setPosition(origin + Point(randomx * s.width, randomy * s.height));
        
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
        auto seq = Sequence::create( action, action_back, NULL );
        
        sprite->runAction( RepeatForever::create(seq) );

        _spriteArray.pushBack(sprite);
    }

    char str[20] = {0};
    sprintf(str, "Sprites : %d", (int)_spriteArray.size());
    _spriteLabel->setString(str);
}

void ScenarioTest::removeSprites()
{
    int number = _spriteArray.size();
    if (number <= 0) {
        return;
    }

    int removeNum = MIN(number, spriteNumStep);
    for (int i = 0; i < removeNum; ++i) {
        auto sprite = _spriteArray.getRandomObject();
        removeChild(sprite);
        _spriteArray.eraseObject(sprite);
    }
    
    char str[20] = {0};
    sprintf(str, "Sprites : %d", (int)_spriteArray.size());
    _spriteLabel->setString(str);
}

std::string ScenarioTest::title() const
{
    return "Scenario Performance Test";
}

//
//std::string ScenarioTest::subtitle() const
//{
//    return "See console for results";
//}

Scene* ScenarioTest::scene()
{
    auto scene = Scene::create();
    ScenarioTest *layer = new ScenarioTest(false, TEST_COUNT, s_nScenarioCurCase);
    scene->addChild(layer);
    layer->release();

    return scene;
}

void runScenarioTest()
{
    s_nScenarioCurCase = 0;
    auto scene = ScenarioTest::scene();
    Director::getInstance()->replaceScene(scene);
}
