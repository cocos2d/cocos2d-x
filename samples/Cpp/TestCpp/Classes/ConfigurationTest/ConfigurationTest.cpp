
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

static CCLayer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* restartAction()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

void ConfigurationTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    CCDirector::sharedDirector()->replaceScene(this);
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
    CCLayer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char * pTitle = str.c_str();
    CCLabelTTF* label = CCLabelTTF::create(pTitle, "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }    

    // add menu
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(ConfigurationBase::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(ConfigurationBase::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(ConfigurationBase::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);
}

void ConfigurationBase::onExit()
{
    CCLayer::onExit();
}

void ConfigurationBase::restartCallback(CCObject* pSender)
{
    CCScene* s = new ConfigurationTestScene();
    s->addChild( restartAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ConfigurationBase::nextCallback(CCObject* pSender)
{
    CCScene* s = new ConfigurationTestScene();
    s->addChild( nextAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ConfigurationBase::backCallback(CCObject* pSender)
{
    CCScene* s = new ConfigurationTestScene();
    s->addChild( backAction() );
    CCDirector::sharedDirector()->replaceScene(s);
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

	CCConfiguration::sharedConfiguration()->loadConfigFile("configs/config-test-ok.plist");
	CCConfiguration::sharedConfiguration()->dumpInfo();

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

	CCLOG("cocos2d version: %s", CCConfiguration::sharedConfiguration()->getCString("cocos2d.version") );
	CCLOG("OpenGL version: %s", CCConfiguration::sharedConfiguration()->getCString("gl.version") );
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

	CCConfiguration::sharedConfiguration()->loadConfigFile("configs/config-test-invalid.plist");
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

	const char *c_value = CCConfiguration::sharedConfiguration()->getCString("invalid.key", "no key");
	if( strcmp(c_value, "no key") != 0 )
		CCLOG("1. Test failed!");
	else
		CCLOG("1. Test OK!");

	bool b_value = CCConfiguration::sharedConfiguration()->getBool("invalid.key", true);
	if( ! b_value )
		CCLOG("2. Test failed!");
	else
		CCLOG("2. Test OK!");

	double d_value = CCConfiguration::sharedConfiguration()->getNumber("invalid.key", 42.42);
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

	CCConfiguration *conf = CCConfiguration::sharedConfiguration();

	conf->setObject("this.is.an.int.value", CCInteger::create(10) );
	conf->setObject("this.is.a.bool.value", CCBool::create(true) );
	conf->setObject("this.is.a.string.value", CCString::create("hello world") );

	conf->dumpInfo();
}

std::string ConfigurationSet::subtitle()
{
    return "Tests setting values manually";
}

