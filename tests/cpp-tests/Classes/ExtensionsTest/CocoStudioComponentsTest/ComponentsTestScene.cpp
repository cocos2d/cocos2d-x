#include "ComponentsTestScene.h"
#include "GameOverScene.h"
#include "PlayerController.h"
#include "SceneController.h"
#include "../ExtensionsTest.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocostudio;

CocoStudioComponentsTests::CocoStudioComponentsTests()
{
    ADD_TEST_CASE(CocoStudioComponentsTest);
}

bool CocoStudioComponentsTest::init()
{
    if (TestCase::init())
    {
        auto bg = LayerColor::create(Color4B(0, 128, 255, 255));
        addChild(bg);

        auto root = createGameScene();
        this->addChild(root, 0, 1);

        root->getChildByTag(1)->addComponent(ComAudio::create());
        root->getChildByTag(1)->addComponent(PlayerController::create());

        root->addComponent(ComAudio::create());
        root->addComponent(ComAttribute::create());
        root->addComponent(SceneController::create());

        return true;
    }

    return false;
}

cocos2d::Node* CocoStudioComponentsTest::createGameScene()
{
    Node *root = nullptr;
    do 
	{
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

       
        auto player = Sprite::create("components/Player.png", Rect(0, 0, 27, 40) );
        
        player->setPosition(origin.x + player->getContentSize().width/2,
                                 origin.y + visibleSize.height/2);
        
        root = cocos2d::Node::create();
        root->addChild(player, 1, 1);
        
    }while (0);
    
    return root;
}

