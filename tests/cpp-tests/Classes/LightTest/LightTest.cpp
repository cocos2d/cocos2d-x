#include "LightTest.h"

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    CL(LightTest)
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextSpriteTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backSpriteTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartSpriteTestAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

LightTest::LightTest()
    : _directionalLight(nullptr)
    , _pointLight(nullptr)
    , _spotLight(nullptr)
{
    addSprite();
    addLights();
    scheduleUpdate();

    auto s = Director::getInstance()->getWinSize();
    auto camera = Camera::createPerspective(60, (GLfloat)s.width/s.height, 1.0f, 1000.0f);
    camera->setCameraFlag(CameraFlag::USER1);
    camera->setPosition3D(Vec3(0.0, 100, 100));
    camera->lookAt(Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
    addChild(camera);

    TTFConfig ttfConfig("fonts/arial.ttf", 15);
    _directionalLightLabel = Label::createWithTTF(ttfConfig,"Directional Light ON");
    _directionalLightLabel->retain();
    auto menuItem1 = MenuItemLabel::create(_directionalLightLabel, CC_CALLBACK_1(LightTest::SwitchLight,this,Light3D::LightType::DIRECTIONAL));
    _pointLightLabel = Label::createWithTTF(ttfConfig,"Point Light OFF");
    _pointLightLabel->retain();
    auto menuItem2 = MenuItemLabel::create(_pointLightLabel, CC_CALLBACK_1(LightTest::SwitchLight,this,Light3D::LightType::POINT));
    _spotLightLabel = Label::createWithTTF(ttfConfig,"Spot Light OFF");
    _spotLightLabel->retain();
    auto menuItem3 = MenuItemLabel::create(_spotLightLabel, CC_CALLBACK_1(LightTest::SwitchLight,this,Light3D::LightType::SPOT));
    auto menu = Menu::create(menuItem1,menuItem2,menuItem3,NULL);
    menu->setPosition(Vec2::ZERO);
    menuItem1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    menuItem1->setPosition( Vec2(VisibleRect::left().x, VisibleRect::top().y-50) );
    menuItem2->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    menuItem2->setPosition( Vec2(VisibleRect::left().x, VisibleRect::top().y -100));
    menuItem3->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    menuItem3->setPosition( Vec2(VisibleRect::left().x, VisibleRect::top().y -150));
    addChild(menu);
}


LightTest::~LightTest()
{
    if (_spotLightLabel)
        _spotLightLabel->release();

    if (_pointLightLabel)
        _pointLightLabel->release();

    if (_directionalLightLabel)
        _directionalLightLabel->release();

    if (_directionalLight)
        _directionalLight->release();

    if (_pointLight)
        _pointLight->release();

    if (_spotLight)
        _spotLight->release();
}

std::string LightTest::title() const
{
    return "Light Test";
}

std::string LightTest::subtitle() const
{
    return "";
}

void LightTest::restartCallback( Ref* sender )
{
    auto s = new LightTestScene();
    s->addChild(restartSpriteTestAction());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LightTest::nextCallback( Ref* sender )
{
    auto s = new LightTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LightTest::backCallback( Ref* sender )
{
    auto s = new LightTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LightTest::onEnter()
{
    BaseTest::onEnter();
}

void LightTest::onExit()
{
    BaseTest::onExit();
}

void LightTest::addSprite()
{
    auto s = Director::getInstance()->getWinSize();

    //{
    //    std::string fileName = "Sprite3DTest/plane.c3b";
    //    auto sprite = Sprite3D::create(fileName);
    //    sprite->setRotation3D(Vec3(-90.0, 0.0, 0.0));
    //    sprite->setScale(5.0f);
    //    sprite->setPosition(Vec2(0.0, -50.0));
    //    addChild(sprite);
    //    sprite->setCameraMask(2);
    //}

    {
        std::string fileName = "Sprite3DTest/orc.c3b";
        auto sprite = Sprite3D::create(fileName);
        sprite->setRotation3D(Vec3(0.0, 180.0, 0.0));
        sprite->setPosition(Vec2(0.0, 0.0));
        sprite->setScale(2.0);
        auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
        sprite->getAttachNode("Bip001 R Hand")->addChild(sp);
        auto animation = Animation3D::create(fileName);
        if (animation)
        {
            auto animate = Animate3D::create(animation);
            sprite->runAction(RepeatForever::create(animate));
        }

        addChild(sprite);
        sprite->setCameraMask(2);
    }

    {
        std::string fileName = "Sprite3DTest/sphere.c3b";
        auto sprite = Sprite3D::create(fileName);
        sprite->setPosition(Vec2(30.0, 0.0));
        addChild(sprite);
        sprite->setCameraMask(2);
    }

    {
        std::string fileName = "Sprite3DTest/sphere.c3b";
        auto sprite = Sprite3D::create(fileName);
        sprite->setScale(0.5f);
        sprite->setPosition(Vec2(-50.0, 0.0));
        addChild(sprite);
        sprite->setCameraMask(2);
    }

    {
        std::string fileName = "Sprite3DTest/sphere.c3b";
        auto sprite = Sprite3D::create(fileName);
        sprite->setScale(0.5f);
        sprite->setPosition(Vec2(-30.0, 10.0));
        addChild(sprite);
        sprite->setCameraMask(2);
    }
}

void LightTest::addLights()
{
    auto s = Director::getInstance()->getWinSize();
    _directionalLight = Light3D::createDirectionalLight(Vec3(-1.0f, -1.0f, 0.0f), Color3B(200, 200, 200));
    _directionalLight->retain();
    addChild(_directionalLight);
    _directionalLight->setCameraMask(2);

    _pointLight = Light3D::createPointLight(Vec3(0.0f, 0.0f, 0.0f), Color3B(200, 200, 200), 10000.0f);
    _pointLight->retain();
    _pointLight->setEnabled(false);
    addChild(_pointLight);
    _pointLight->setCameraMask(2);

    _spotLight = Light3D::createSpotLight(Vec3(-1.0f, -1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Color3B(200, 200, 200), 0.0, 0.5, 10000.0f);
    _spotLight->retain();
    _spotLight->setEnabled(false);
    addChild(_spotLight);
    _spotLight->setCameraMask(2);

    {
        auto tintto1 = TintTo::create(4, 255, 0, 0);
        auto tintto2 = TintTo::create(4, 0, 255, 0);
        auto tintto3 = TintTo::create(4, 0, 0, 255);
        auto tintto4 = TintTo::create(4, 255, 255, 255);
        auto seq = Sequence::create(tintto1,tintto2, tintto3, tintto4, NULL);
        _directionalLight->runAction(RepeatForever::create(seq));
    }

    {
        auto tintto1 = TintTo::create(4, 255, 0, 0);
        auto tintto2 = TintTo::create(4, 0, 255, 0);
        auto tintto3 = TintTo::create(4, 0, 0, 255);
        auto tintto4 = TintTo::create(4, 255, 255, 255);
        auto seq = Sequence::create(tintto2, tintto1, tintto3, tintto4, NULL);
        _pointLight->runAction(RepeatForever::create(seq));
    }

    {
        auto tintto1 = TintTo::create(4, 255, 0, 0);
        auto tintto2 = TintTo::create(4, 0, 255, 0);
        auto tintto3 = TintTo::create(4, 0, 0, 255);
        auto tintto4 = TintTo::create(4, 255, 255, 255);
        auto seq = Sequence::create(tintto3, tintto2, tintto1, tintto4, NULL);
        _spotLight->runAction(RepeatForever::create(seq));
    }
}

void LightTest::update( float delta )
{
    static float angleDelta = 0.0;
    if (_directionalLight)
        _directionalLight->setRotation3D(Vec3(-45.0, -CC_RADIANS_TO_DEGREES(angleDelta), 0.0f));

    if (_pointLight)
    {
        _pointLight->setPositionX(100.0f * cosf(angleDelta + 2.0 * delta));
        _pointLight->setPositionY(100.0f);
        _pointLight->setPositionZ(100.0f * sinf(angleDelta + 2.0 * delta));
    }

    if (_spotLight)
    {
        _spotLight->setPositionX(100.0f * cosf(angleDelta + 4.0 * delta));
        _spotLight->setPositionY(100.0f);
        _spotLight->setPositionZ(100.0f * sinf(angleDelta + 4.0 * delta));
        _spotLight->setDirection(-Vec3(cosf(angleDelta + 4.0 * delta), 1.0, sinf(angleDelta + 4.0 * delta)));
    }

    angleDelta += delta;

    BaseTest::update(delta);
}

void LightTest::SwitchLight( Ref* sender,Light3D::LightType lightType )
{
    switch (lightType)
    {
    case Light3D::LightType::DIRECTIONAL:
        {
            char str[32];
            bool isON = !_directionalLight->getEnabled();
            sprintf(str, "Directional Light %s", isON == true? "ON":"OFF");
            _directionalLight->setEnabled(isON);
            _directionalLightLabel->setString(str);
        }
        break;

    case Light3D::LightType::POINT:
        {
            char str[32];
            bool isON = !_pointLight->getEnabled();
            sprintf(str, "Point Light %s", isON == true? "ON":"OFF");
            _pointLight->setEnabled(isON);
            _pointLightLabel->setString(str);
        }
        break;

    case Light3D::LightType::SPOT:
        {
            char str[32];
            bool isON = !_spotLight->getEnabled();
            sprintf(str, "Spot Light %s", isON == true? "ON":"OFF");
            _spotLight->setEnabled(isON);
            _spotLightLabel->setString(str);
        }
        break;

    default:
        break;
    }
}

void LightTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

LightTestScene::LightTestScene()
{
    setAmbientColor(Color4F(0.2f, 0.2f, 0.2f, 1.0f));
}