#include "LightTestDemo.h"

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    //CL(DirectionalLightTestDemo),
    //CL(PointLightTestDemo),
    //CL(SpotLightTestDemo)
    CL(LightTestDemo)
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

    TTFConfig ttfConfig("fonts/arial.ttf", 10);
    auto label1 = Label::createWithTTF(ttfConfig,"Directional Light");
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(LightTestDemo::SwitchLight,this,Light3D::DIRECTIONAL));
    auto label2 = Label::createWithTTF(ttfConfig,"Point Light");
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(LightTestDemo::SwitchLight,this,Light3D::POINT));
    auto label3 = Label::createWithTTF(ttfConfig,"Spot Light");
    auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(LightTestDemo::SwitchLight,this,Light3D::SPOT));
    auto menu = Menu::create(menuItem1,menuItem2,menuItem3,NULL);
    menu->setPosition(Vec2::ZERO);
    menuItem1->setPosition( Vec2(VisibleRect::left().x + 50, VisibleRect::top().y-50) );
    menuItem2->setPosition( Vec2(VisibleRect::left().x + 50, VisibleRect::top().y -70));
    menuItem3->setPosition( Vec2(VisibleRect::left().x + 50, VisibleRect::top().y -90));
    addChild(menu);
}


LightTestDemo::~LightTestDemo()
{
    if (_directionalLight)
        _directionalLight->release();

    if (_pointLight)
        _pointLight->release();

    if (_spotLight)
        _spotLight->release();
}

std::string LightTestDemo::title() const
{
    return "Light Test";
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

void LightTestDemo::addSprite()
{
    auto s = Director::getInstance()->getWinSize();

    {
        std::string fileName = "Sprite3DTest/plane.c3b";
        auto sprite = Sprite3D::create(fileName);
        sprite->setRotation3D(Vec3(-90.0, 0.0, 0.0));
        sprite->setScale(5.0f);
        sprite->setPosition(Vec2(0.0, -50.0));
        addChild(sprite);
        sprite->setCameraMask(2);
    }

    {
        std::string fileName = "Sprite3DTest/sphere.c3b";
        auto sprite = Sprite3D::create(fileName);
        //sprite->setPosition(Vec2(s.width/2, s.height/2));
        addChild(sprite);
        sprite->setCameraMask(2);
    }

    {
        std::string fileName = "Sprite3DTest/sphere.c3b";
        auto sprite = Sprite3D::create(fileName);
        sprite->setScale(2.0f);
        sprite->setPosition(Vec2(50.0, 0.0));
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

void LightTestDemo::addLights()
{
	auto s = Director::getInstance()->getWinSize();
	_directionalLight = Light3D::CreateDirectionalLight(Vec3(-1.0f, 0.0f, 0.0f), Color3B(200, 200, 200));
	_directionalLight->retain();
	addChild(_directionalLight);

	_pointLight = Light3D::CreatePointLight(Vec3(100.0, 100.0, 100.0), Color3B(200, 200, 200), 1000.0f);
	_pointLight->retain();
	_pointLight->setEnabled(false);
	addChild(_pointLight);

    _spotLight = Light3D::CreateSpotLight(Vec3(-1.0f, 0.0f, 0.0f), Vec3(100.0, 100.0, 100.0), Color3B(200, 200, 200), 0.0, 0.5, 1000.0f);
    _spotLight->retain();
    _spotLight->setEnabled(false);
    addChild(_spotLight);
}

void LightTestDemo::update( float delta )
{
    static float angleDelta = 0.0;
	if (_directionalLight)
		_directionalLight->setDirection(-Vec3(cosf(angleDelta), 1.0f, sinf(angleDelta)));

	if (_pointLight)
	{
		_pointLight->setPositionX(100.0f * cosf(angleDelta));
		_pointLight->setPositionY(100.0f);
		_pointLight->setPositionZ(100.0f * sinf(angleDelta));
	}

	if (_spotLight)
	{
		_spotLight->setPositionX(100.0f * cosf(angleDelta));
		_spotLight->setPositionY(100.0f);
		_spotLight->setPositionZ(100.0f * sinf(angleDelta));
		_spotLight->setDirection(-Vec3(cosf(angleDelta), 1.0f, sinf(angleDelta)));
	}

    angleDelta += delta;

    BaseTest::update(delta);
}

void LightTestDemo::SwitchLight( Ref* sender,Light3D::LightType lightType )
{
    switch (lightType)
    {
    case Light3D::DIRECTIONAL:
        {
			if (_directionalLight)
				_directionalLight->setEnabled(true);
			if (_pointLight)
				_pointLight->setEnabled(false);
			if (_spotLight)
				_spotLight->setEnabled(false);
        }
        break;

    case Light3D::POINT:
        {
			if (_directionalLight)
				_directionalLight->setEnabled(false);
			if (_pointLight)
				_pointLight->setEnabled(true);
			if (_spotLight)
				_spotLight->setEnabled(false);
        }
        break;

    case Light3D::SPOT:
        {
			if (_directionalLight)
				_directionalLight->setEnabled(false);
			if (_pointLight)
				_pointLight->setEnabled(false);
			if (_spotLight)
				_spotLight->setEnabled(true);
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