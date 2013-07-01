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

Scene* ComponentsTestLayer::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
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
        CC_BREAK_IF(! LayerColor::initWithColor( ccc4(255,255,255,255) ) );
        
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

        root->getChildByTag(1)->addComponent(ComAudio::create());
        root->getChildByTag(1)->addComponent(PlayerController::create());  
        
        root->addComponent(ComAudio::create());
        root->addComponent(ComAttribute::create());
        root->addComponent(SceneController::create());

		bRet = true;
	} while (0);

	return bRet;
}

cocos2d::Node* ComponentsTestLayer::createGameScene()
{
    Node *root = NULL;
    do 
	{
        Size visibleSize = Director::sharedDirector()->getVisibleSize();
        Point origin = Director::sharedDirector()->getVisibleOrigin();

       
        Sprite *player = Sprite::create("components/Player.png", CCRectMake(0, 0, 27, 40) );
        
        player->setPosition( ccp(origin.x + player->getContentSize().width/2,
                                 origin.y + visibleSize.height/2) );
        
        root = cocos2d::Node::create();
        root->addChild(player, 1, 1);
        

        MenuItemFont *itemBack = MenuItemFont::create("Back", [](Object* sender){
        	ExtensionsTestScene *pScene = new ExtensionsTestScene();
            pScene->runThisTest();
            pScene->release();
        });
        
        itemBack->setColor(ccc3(0, 0, 0));
        itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        Menu *menuBack = Menu::create(itemBack, NULL);
        menuBack->setPosition(PointZero);
        addChild(menuBack);
        
    }while (0);
    
    return root;
}

void runComponentsTestLayerTest()
{
    Scene *pScene = ComponentsTestLayer::scene();
    Director::sharedDirector()->replaceScene(pScene);
}
