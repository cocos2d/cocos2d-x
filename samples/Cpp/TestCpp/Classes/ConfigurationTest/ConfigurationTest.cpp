
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
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* restartAction()
{
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

void ConfigurationTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    Director::sharedDirector()->replaceScene(this);
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

void ConfigurationBase::restartCallback(Object* pSender)
{
    Scene* s = new ConfigurationTestScene();
    s->addChild( restartAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ConfigurationBase::nextCallback(Object* pSender)
{
    Scene* s = new ConfigurationTestScene();
    s->addChild( nextAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ConfigurationBase::backCallback(Object* pSender)
{
    Scene* s = new ConfigurationTestScene();
    s->addChild( backAction() );
    Director::sharedDirector()->replaceScene(s);
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

	Configuration::sharedConfiguration()->loadConfigFile("configs/config-test-ok.plist");
	Configuration::sharedConfiguration()->dumpInfo();

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

	CCLOG("cocos2d version: %s", Configuration::sharedConfiguration()->getCString("cocos2d.version") );
	CCLOG("OpenGL version: %s", Configuration::sharedConfiguration()->getCString("gl.version") );
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

	Configuration::sharedConfiguration()->loadConfigFile("configs/config-test-invalid.plist");
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

	const char *c_value = Configuration::sharedConfiguration()->getCString("invalid.key", "no key");
	if( strcmp(c_value, "no key") != 0 )
		CCLOG("1. Test failed!");
	else
		CCLOG("1. Test OK!");

	bool b_value = Configuration::sharedConfiguration()->getBool("invalid.key", true);
	if( ! b_value )
		CCLOG("2. Test failed!");
	else
		CCLOG("2. Test OK!");

	double d_value = Configuration::sharedConfiguration()->getNumber("invalid.key", 42.42);
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

	Configuration *conf = Configuration::sharedConfiguration();

	conf->setObject("this.is.an.int.value", Integer::create(10) );
	conf->setObject("this.is.a.bool.value", Bool::create(true) );
	conf->setObject("this.is.a.string.value", String::create("hello world") );

	conf->dumpInfo();
}

std::string ConfigurationSet::subtitle()
{
    return "Tests setting values manually";
}

