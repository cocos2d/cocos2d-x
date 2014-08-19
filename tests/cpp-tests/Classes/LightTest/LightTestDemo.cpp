#include "LightTestDemo.h"
#include "3d/CCLight.h"

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    CL(DirectionalLightTestDemo),
    CL(PointLightTestDemo),
    CL(SpotLightTestDemo)
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

LightTestDemo::LightTestDemo()
{
}


LightTestDemo::~LightTestDemo()
{
}

std::string LightTestDemo::title() const
{
    return "Point Light";
}

std::string LightTestDemo::subtitle() const
{
    return "";
}

void LightTestDemo::restartCallback( Ref* sender )
{
    auto s = new LightTestScene();
    s->addChild(restartSpriteTestAction());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LightTestDemo::nextCallback( Ref* sender )
{
    auto s = new LightTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LightTestDemo::backCallback( Ref* sender )
{
    auto s = new LightTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void LightTestDemo::onEnter()
{
    BaseTest::onEnter();
}

void LightTestDemo::onExit()
{
    BaseTest::onExit();
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

PointLightTestDemo::PointLightTestDemo()
    : _pointLight(nullptr)
{
    addSprite();
    addLights();
    scheduleUpdate();
}

PointLightTestDemo::~PointLightTestDemo()
{
    if (_pointLight)
        _pointLight->release();
}

void PointLightTestDemo::addSprite()
{
    auto s = Director::getInstance()->getWinSize();
    std::string fileName = "Sprite3DTest/sphere.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(5.0f);
    sprite->setPosition(Vec2(s.width/2, s.height/2));
    addChild(sprite);
}

void PointLightTestDemo::addLights()
{
    auto s = Director::getInstance()->getWinSize();
    _pointLight = Light3D::CreatePointLight(Vec3(s.width/2, s.height/2, 0.0), Color3B(128, 128, 128), 10000.0f);
    _pointLight->retain();

    addChild(_pointLight);
}

void PointLightTestDemo::update( float delta )
{
    auto s = Director::getInstance()->getWinSize();
    static float angleDelta = 0.0;
    _pointLight->setPositionX(s.width / 2 + s.width / 4 * cosf(angleDelta));
    _pointLight->setPositionY(s.height / 2);
    _pointLight->setPositionZ(s.width / 4 * sinf(angleDelta));

    angleDelta += delta;
    BaseTest::update(delta);
}

std::string PointLightTestDemo::title() const
{
    return "Point Light";
}

DirectionalLightTestDemo::DirectionalLightTestDemo()
    : _directionalLight(nullptr)
{
    addSprite();
    addLights();
    scheduleUpdate();
}

DirectionalLightTestDemo::~DirectionalLightTestDemo()
{
    if (_directionalLight)
        _directionalLight->release();
}

std::string DirectionalLightTestDemo::title() const
{
    return "Directional Light";
}

void DirectionalLightTestDemo::update( float delta )
{
    static float angleDelta = 0.0;
    _directionalLight->setDirection(-Vec3(cosf(angleDelta), 0.0f, sinf(angleDelta)));

    angleDelta += delta;
    BaseTest::update(delta);
}

void DirectionalLightTestDemo::addSprite()
{
    auto s = Director::getInstance()->getWinSize();

	{
		std::string fileName = "Sprite3DTest/sphere.c3b";
		auto sprite = Sprite3D::create(fileName);
		sprite->setScale(5.0f);
		sprite->setRotation3D(Vec3(0,180,0));
		sprite->setPosition(Vec2(s.width/2, s.height/2));
		addChild(sprite);
	}

}

void DirectionalLightTestDemo::addLights()
{
    auto s = Director::getInstance()->getWinSize();
    _directionalLight = Light3D::CreateDirectionalLight(Vec3(-1.0f, 0.0f, 0.0f), Color3B(128, 128, 128));
    _directionalLight->retain();

    addChild(_directionalLight);

}

std::string SpotLightTestDemo::title() const
{
    return "Spot Light";
}

void SpotLightTestDemo::addSprite()
{
    auto s = Director::getInstance()->getWinSize();
    std::string fileName = "Sprite3DTest/sphere.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(5.0f);
    sprite->setPosition(Vec2(s.width/2, s.height/2));
    addChild(sprite);
}

void SpotLightTestDemo::addLights()
{
    auto s = Director::getInstance()->getWinSize();
    _spotLight = Light3D::CreateSpotLight(Vec3(0.0f, 0.0f, -1.0f), Vec3(s.width/2, s.height/2, 0.0), Color3B(128, 128, 128), 0.0f, 0.4f, 10000.0f);
    _spotLight->retain();

    addChild(_spotLight);
}

SpotLightTestDemo::SpotLightTestDemo()
    : _spotLight(nullptr)
{
    addSprite();
    addLights();
    scheduleUpdate();
}

SpotLightTestDemo::~SpotLightTestDemo()
{
    if (_spotLight)
        _spotLight->release();
}

void SpotLightTestDemo::update( float delta )
{
    auto s = Director::getInstance()->getWinSize();
    static float angleDelta = 0.0;
    _spotLight->setDirection(-Vec3(cosf(angleDelta), 0.0f, sinf(angleDelta)));
    _spotLight->setPositionX(s.width / 2 + s.width / 4 * cosf(angleDelta));
    _spotLight->setPositionY(s.height / 2);
    _spotLight->setPositionZ(s.width / 4 * sinf(angleDelta));

    angleDelta += delta;
    BaseTest::update(delta);
}
