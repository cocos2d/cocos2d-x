#include "ComponentsTestScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "PlayerController.h"
#include "SceneController.h"
#include "../ExtensionsTest.h"

using namespace cocos2d;
using namespace cocos2d::extension;

ComponentsTestLayer::~ComponentsTestLayer()
{
}

ComponentsTestLayer::ComponentsTestLayer()
{
}

CCScene* ComponentsTestLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		ComponentsTestLayer *layer = ComponentsTestLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ComponentsTestLayer::init()
{
	bool bRet = false;
	do 
	{
        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) );
        
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

        root->getChildByTag(1)->addComponent(CCComAudio::create());
        root->getChildByTag(1)->addComponent(PlayerController::create());  
        
        root->addComponent(CCComAudio::create());
        root->addComponent(CCComAttribute::create());
        root->addComponent(SceneController::create());

		bRet = true;
	} while (0);

	return bRet;
}

cocos2d::CCNode* ComponentsTestLayer::createGameScene()
{
    CCNode *root = NULL;
    do 
	{
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

       
        CCSprite *player = CCSprite::create("components/Player.png", CCRectMake(0, 0, 27, 40) );
        
        player->setPosition( ccp(origin.x + player->getContentSize().width/2,
                                 origin.y + visibleSize.height/2) );
        
        root = cocos2d::CCNode::create();
        root->addChild(player, 1, 1);
        

        CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(ComponentsTestLayer::toExtensionsMainLayer));
        itemBack->setColor(ccc3(0, 0, 0));
        itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        CCMenu *menuBack = CCMenu::create(itemBack, NULL);
        menuBack->setPosition(CCPointZero);
        addChild(menuBack);
        
    }while (0);
    
    return root;
}

void ComponentsTestLayer::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}


void runComponentsTestLayerTest()
{
    CCScene *pScene = ComponentsTestLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
