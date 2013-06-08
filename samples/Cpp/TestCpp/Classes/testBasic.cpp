#include "testBasic.h"
#include "controller.h"

TestScene::TestScene(bool bPortrait)
{
    
    CCScene::init();
}

void TestScene::onEnter()
{
    CCScene::onEnter();

    //add the menu item for back to main menu
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
//#else
    CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
//#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, [](CCObject *sender) {
        /*
            ******    GCC Compiler issue on Android and Linux (CLANG compiler is ok)   ******
        We couldn't use 'CCScene::create' directly since gcc will trigger
        an error called "error: 'this' was not captured for this lambda function".
        This is because 'CCScene' is the super class of TestScene, if we invoke 'CCScene::create'
        directly in this lambda expression, gcc compiler found 'CCScene::create' and it think
        that was the member function of 'TestScene' 's super class, but this lambda function doesn't
        capture anything like 'this', so it has no access to invoke 'CCScene::create'.
         
        Solution (1): Passing 'this' to this lambda function.
        Solution (2): Don't use 'CCScene::create' and don't pass 'this' to this lambda function,
                      instead, we just need to new the 'CCScene' and initialize the Scene.
         
        Semantically, I think in this lambda function, we shouldn't capture any varibles
                      outside the scope. So I choose the (2) solution. Commented by James Chen.
        */

//        CCScene *pScene = CCScene::create();
        CCScene *pScene = new CCScene();
        if (pScene && pScene->init())
        {
            CCLayer* pLayer = new TestController();
            pScene->addChild(pLayer);
            pLayer->release();
            CCDirector::sharedDirector()->replaceScene(pScene);
            pScene->release();
        }
	});

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(pMenu, 1);
}
