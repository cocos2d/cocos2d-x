
#include "ConfigurationTest.h"
#include "../testResource.h"
#include "cocos2d.h"

TESTLAYER_CREATE_FUNC(ConfigurationLoadConfig);
TESTLAYER_CREATE_FUNC(ConfigurationQuery);
TESTLAYER_CREATE_FUNC(ConfigurationInvalid);
TESTLAYER_CREATE_FUNC(ConfigurationDefault);
TESTLAYER_CREATE_FUNC(ConfigurationSet);

static NEWTESTFUNC createFunctions[] = {
    CF(ConfigurationLoadConfig),
	CF(ConfigurationQuery),
	CF(ConfigurationInvalid),
	CF(ConfigurationDefault),
	CF(ConfigurationSet)
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    Layer* layer = (createFunctions[sceneIdx])();
    layer->init();
    layer->autorelease();
    
    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* layer = (createFunctions[sceneIdx])();
    layer->init();
    layer->autorelease();
    
    return layer;
}

static Layer* restartAction()
{
    Layer* layer = (createFunctions[sceneIdx])();
    layer->init();
    layer->autorelease();
    
    return layer;
}

void ConfigurationTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    Director::getInstance()->replaceScene(this);
}


std::string ConfigurationBase::title()
{
    return "Configuration Test";
}

std::string ConfigurationBase::subtitle()
{
    return "";
}

void ConfigurationBase::onEnter()
{
    BaseTest::onEnter();
}

void ConfigurationBase::onExit()
{
    BaseTest::onExit();
}

void ConfigurationBase::restartCallback(Object* sender)
{
    Scene* s = new ConfigurationTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ConfigurationBase::nextCallback(Object* sender)
{
    Scene* s = new ConfigurationTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ConfigurationBase::backCallback(Object* sender)
{
    Scene* s = new ConfigurationTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

//------------------------------------------------------------------
//
// ConfigurationLoadConfig
//
//------------------------------------------------------------------
void ConfigurationLoadConfig::onEnter()
{
    ConfigurationBase::onEnter();

	Configuration::getInstance()->loadConfigFile("configs/config-test-ok.plist");
	Configuration::getInstance()->dumpInfo();

}

std::string ConfigurationLoadConfig::subtitle()
{
    return "Loading config file manually. See console";
}

//------------------------------------------------------------------
//
// ConfigurationQuery
//
//------------------------------------------------------------------
void ConfigurationQuery::onEnter()
{
    ConfigurationBase::onEnter();

	CCLOG("cocos2d version: %s", Configuration::getInstance()->getCString("cocos2d.version") );
	CCLOG("OpenGL version: %s", Configuration::getInstance()->getCString("gl.version") );
}

std::string ConfigurationQuery::subtitle()
{
    return "Using getCString(). Check the console";
}

//------------------------------------------------------------------
//
// ConfigurationInvalid
//
//------------------------------------------------------------------
void ConfigurationInvalid::onEnter()
{
    ConfigurationBase::onEnter();

	Configuration::getInstance()->loadConfigFile("configs/config-test-invalid.plist");
}

std::string ConfigurationInvalid::subtitle()
{
    return "Loading an invalid config file";
}

//------------------------------------------------------------------
//
// ConfigurationDefault
//
//------------------------------------------------------------------
void ConfigurationDefault::onEnter()
{
    ConfigurationBase::onEnter();

	const char *c_value = Configuration::getInstance()->getCString("invalid.key", "no key");
	if( strcmp(c_value, "no key") != 0 )
		CCLOG("1. Test failed!");
	else
		CCLOG("1. Test OK!");

	bool b_value = Configuration::getInstance()->getBool("invalid.key", true);
	if( ! b_value )
		CCLOG("2. Test failed!");
	else
		CCLOG("2. Test OK!");

	double d_value = Configuration::getInstance()->getNumber("invalid.key", 42.42);
	if( d_value != 42.42 )
		CCLOG("3. Test failed!");
	else
		CCLOG("3. Test OK!");

}

std::string ConfigurationDefault::subtitle()
{
    return "Tests defaults values";
}

//------------------------------------------------------------------
//
// ConfigurationSet
//
//------------------------------------------------------------------
void ConfigurationSet::onEnter()
{
    ConfigurationBase::onEnter();

	Configuration *conf = Configuration::getInstance();

	conf->setObject("this.is.an.int.value", Integer::create(10) );
	conf->setObject("this.is.a.bool.value", Bool::create(true) );
	conf->setObject("this.is.a.string.value", String::create("hello world") );

	conf->dumpInfo();
}

std::string ConfigurationSet::subtitle()
{
    return "Tests setting values manually";
}

