#include "PerformanceParticle3DTest.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"


enum {
    kTagInfoLayer = 1,
    kTagMainLayer = 2,
    kTagLabelAtlas = 3,
    kTagMenuLayer = 1000,
    kTagParticleSystem = 1001,
    TEST_COUNT = 2,
};

enum {
    kMaxParticles = 14000,
    kNodesIncrease = 1,
};

static int s_nParCurIdx = 0;

////////////////////////////////////////////////////////
//
// ParticleMenuLayer
//
////////////////////////////////////////////////////////
Particle3DMenuLayer::Particle3DMenuLayer(bool bControlMenuVisible, int nMaxCases, int nCurCase)
: PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
{

}

void Particle3DMenuLayer::showCurrentTest()
{
    auto scene = (Particle3DMainScene*)getParent();
    int subTest = scene->getSubTestNum();
    int parNum  = scene->getParticlesNum();

    Particle3DMainScene* pNewScene = nullptr;

    switch (_curCase)
    {
    case 0:
        pNewScene = new (std::nothrow) Particle3DPerformTest;
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
void Particle3DMainScene::initWithSubTest(int asubtest, int particles)
{
    //srandom(0);

    subtestNumber = asubtest;
    auto s = Director::getInstance()->getWinSize();

    lastRenderedCount = 0;
    quantityParticles = 0;

    MenuItemFont::setFontSize(65);
    auto decrease = MenuItemFont::create(" - ", [=](Ref *sender) {
        quantityParticles -= kNodesIncrease;
        if( quantityParticles < 0 )
            quantityParticles = 0;

        updateQuantityLabel();
        removeChildByTag(kTagParticleSystem + quantityParticles, true);
    });
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", [=](Ref *sender) {
        quantityParticles += kNodesIncrease;
        if( quantityParticles > kMaxParticles )
            quantityParticles = kMaxParticles;

        updateQuantityLabel();
        createParticleSystem(quantityParticles - 1);
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

    //// particles on stage
    //auto labelAtlas = LabelAtlas::create("0000", "fps_images.png", 12, 32, '.');
    //addChild(labelAtlas, 0, kTagLabelAtlas);
    //labelAtlas->setPosition(Vec2(s.width-66,50));

    // Next Prev Test
    auto menuLayer = new (std::nothrow) Particle3DMenuLayer(true, TEST_COUNT, s_nParCurIdx);
    addChild(menuLayer, 1, kTagMenuLayer);
    menuLayer->release();

    //// Sub Tests
    //MenuItemFont::setFontSize(40);
    //auto pSubMenu = Menu::create();
    //for (int i = 1; i <= 6; ++i)
    //{
    //    char str[10] = {0};
    //    sprintf(str, "%d ", i);
    //    auto itemFont = MenuItemFont::create(str, CC_CALLBACK_1(Particle3DMainScene::testNCallback, this));
    //    itemFont->setTag(i);
    //    pSubMenu->addChild(itemFont, 10);

    //    if (i <= 3)
    //    {
    //        itemFont->setColor(Color3B(200,20,20));
    //    }
    //    else
    //    {
    //        itemFont->setColor(Color3B(0,200,20));
    //    }
    //}
    //pSubMenu->alignItemsHorizontally();
    //pSubMenu->setPosition(Vec2(s.width/2, 80));
    //addChild(pSubMenu, 2);

    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-50));

    auto camera = Camera::createPerspective(30.0f, s.width / s.height, 1.0f, 1000.0f);
    camera->setPosition3D(Vec3(0.0f, 0.0f, 150.0f));
    camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);

    schedule(CC_SCHEDULE_SELECTOR(Particle3DMainScene::step));
}

std::string Particle3DMainScene::title() const
{
    return "No title";
}

void Particle3DMainScene::step(float dt)
{
    auto atlas = (LabelAtlas*) getChildByTag(kTagLabelAtlas);
}

void Particle3DMainScene::createParticleSystem(int idx)
{
   // removeChildByTag(kTagParticleSystem, true);

    auto ps = PUParticleSystem3D::create("Particle3D/scripts/lineStreak.pu", "Particle3D/materials/pu_mediapack_01.material");
    ps->setCameraMask((unsigned short)CameraFlag::USER1);
    ps->setPosition(CCRANDOM_MINUS1_1() * 50.0f, CCRANDOM_MINUS1_1() * 20.0f);
    ps->startParticleSystem();
    addChild(ps, 0, kTagParticleSystem + idx);


    //doTest();
}

void Particle3DMainScene::testNCallback(Ref* sender)
{
    subtestNumber = static_cast<Node*>(sender)->getTag();

    auto menu = static_cast<Particle3DMenuLayer*>( getChildByTag(kTagMenuLayer) );
    menu->restartCallback(sender);
}

void Particle3DMainScene::updateQuantityLabel()
{
    if( quantityParticles != lastRenderedCount )
    {
        auto infoLabel = (Label *) getChildByTag(kTagInfoLayer);
        char str[20] = {0};
        sprintf(str, "%u Particle Systems", quantityParticles);
        infoLabel->setString(str);

        lastRenderedCount = quantityParticles;
    }
}

////////////////////////////////////////////////////////
//
// ParticlePerformTest1
//
////////////////////////////////////////////////////////
std::string Particle3DPerformTest::title() const
{
    char str[20] = {0};
    sprintf(str, "Particle3D Test"/*, subtestNumber*/);
    std::string strRet = str;
    return strRet;
}

void Particle3DPerformTest::doTest()
{
    auto s = Director::getInstance()->getWinSize();
}

void runParticle3DTest()
{
    auto scene = new (std::nothrow) Particle3DPerformTest;
    scene->initWithSubTest(1, kNodesIncrease);

    Director::getInstance()->replaceScene(scene);
    scene->release();
}
