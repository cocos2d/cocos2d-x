
#include "ConfigurationTest.h"
#include "../testResource.h"
#include "cocos2d.h"

static std::function<Layer*()> createFunctions[] = {
    CL(ConfigurationLoadConfig),
	CL(ConfigurationQuery),
	CL(ConfigurationInvalid),
	CL(ConfigurationDefault),
	CL(ConfigurationSet)
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartAction()
{
    auto layer = (createFunctions[sceneIdx])();    
    return layer;
}

void ConfigurationTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    Director::getInstance()->replaceScene(this);
}


std::string ConfigurationBase::title() const
{
    return "Configuration Test";
}

std::string ConfigurationBase::subtitle() const
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

void ConfigurationBase::restartCallback(Ref* sender)
{
    auto s = new ConfigurationTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ConfigurationBase::nextCallback(Ref* sender)
{
    auto s = new ConfigurationTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ConfigurationBase::backCallback(Ref* sender)
{
    auto s = new ConfigurationTestScene();
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
    std::string config = Configuration::getInstance()->getInfo();
    log("%s\n", config.c_str());

}

std::string ConfigurationLoadConfig::subtitle() const
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

	CCLOG("cocos2d version: %s", Configuration::getInstance()->getValue("cocos2d.x.version").asString().c_str() );
	CCLOG("OpenGL version: %s", Configuration::getInstance()->getValue("gl.version").asString().c_str() );
}

std::string ConfigurationQuery::subtitle() const
{
    return "Check the console";
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

std::string ConfigurationInvalid::subtitle() const
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

    std::string c_value = Configuration::getInstance()->getValue("invalid.key", Value("no key")).asString();
	if( c_value != "no key" )
		CCLOG("1. Test failed!");
	else
		CCLOG("1. Test OK!");

	bool b_value = Configuration::getInstance()->getValue("invalid.key", Value(true)).asBool();
	if( ! b_value )
		CCLOG("2. Test failed!");
	else
		CCLOG("2. Test OK!");

	double d_value = Configuration::getInstance()->getValue("invalid.key", Value(42.42)).asDouble();
	if( d_value != 42.42 )
		CCLOG("3. Test failed!");
	else
		CCLOG("3. Test OK!");

}

std::string ConfigurationDefault::subtitle() const
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

	conf->setValue("this.is.an.int.value", Value(10) );
	conf->setValue("this.is.a.bool.value", Value(true) );
	conf->setValue("this.is.a.string.value", Value("hello world") );

	auto str = conf->getInfo();
    log("%s\n", str.c_str());
}

std::string ConfigurationSet::subtitle() const
{
    return "Tests setting values manually";
}

