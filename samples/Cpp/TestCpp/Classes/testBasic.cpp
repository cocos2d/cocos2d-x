#include "testBasic.h"
#include "controller.h"

TestScene::TestScene(bool bPortrait)
{
    
    Scene::init();
}

void TestScene::onEnter()
{
    Scene::onEnter();

    //add the menu item for back to main menu
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    LabelBMFont* label = LabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
//#else
    LabelTTF* label = LabelTTF::create("MainMenu", "Arial", 20);
//#endif
    MenuItemLabel* menuItem = MenuItemLabel::create(label, [](Object *sender) {
        /*
            ******    GCC Compiler issue on Android and Linux (CLANG compiler is ok)   ******
        We couldn't use 'Scene::create' directly since gcc will trigger
        an error called "error: 'this' was not captured for this lambda function".
        This is because 'Scene' is the super class of TestScene, if we invoke 'Scene::create'
        directly in this lambda expression, gcc compiler found 'Scene::create' and it think
        that was the member function of 'TestScene' 's super class, but this lambda function doesn't
        capture anything like 'this', so it has no access to invoke 'Scene::create'.
         
        Solution (1): Passing 'this' to this lambda function.
        Solution (2): Don't use 'Scene::create' and don't pass 'this' to this lambda function,
                      instead, we just need to new the 'Scene' and initialize the Scene.
         
        Semantically, I think in this lambda function, we shouldn't capture any varibles
                      outside the scope. So I choose the (2) solution. Commented by James Chen.
        */

//        Scene *scene = Scene::create();
        Scene *scene = new Scene();
        if (scene && scene->init())
        {
            Layer* layer = new TestController();
            scene->addChild(layer);
            layer->release();
            Director::getInstance()->replaceScene(scene);
            scene->release();
        }
	});

    Menu* menu =Menu::create(menuItem, NULL);

    menu->setPosition( Point::ZERO );
    menuItem->setPosition( Point( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(menu, 1);
}
