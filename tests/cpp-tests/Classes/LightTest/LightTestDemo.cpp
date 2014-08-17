#include "LightTestDemo.h"
#include "3d/CCLight.h"

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
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
{
	addSprite();
	addLights();
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

void LightTestDemo::addSprite()
{
	auto s = Director::getInstance()->getWinSize();
	std::string fileName = "Sprite3DTest/orc.c3b";
	auto sprite = Sprite3D::create(fileName);
	sprite->setScale(5.0f);
	sprite->setRotation3D(Vec3(0,180,0));
	sprite->setPosition(Vec2(s.width/2, s.height/2));
	addChild(sprite);

	auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
	sprite->getAttachNode("Bip001 R Hand")->addChild(sp);

	auto animation = Animation3D::create(fileName);
	if (animation)
	{
		auto animate = Animate3D::create(animation);

		sprite->runAction(RepeatForever::create(animate));
	}
}

void LightTestDemo::onEnter()
{
	BaseTest::onEnter();
}

void LightTestDemo::onExit()
{
	BaseTest::onExit();
}

void LightTestDemo::addLights()
{
	auto s = Director::getInstance()->getWinSize();
	auto light1 = Light3D::Create(Light3D::POINT);
	light1->setEnabled(true);
	light1->setPosition(Vec2(s.width/2, s.height));
	light1->setColor(Color3B(255, 255, 255));

	addChild(light1);
}

void LightTestScene::runThisTest()
{
	auto layer = nextSpriteTestAction();
	addChild(layer);

	Director::getInstance()->replaceScene(this);
}
