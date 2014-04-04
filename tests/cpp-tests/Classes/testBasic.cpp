#include "testBasic.h"
#include "controller.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

TestScene::TestScene(bool bPortrait, bool physics/* = false*/)
{
    if (physics)
    {
#if CC_USE_PHYSICS
        TestScene::initWithPhysics();
#else
        Scene::init();
#endif
    }
    else
    {
        Scene::init();
    }
}

void testScene_callback(Ref *sender )
{
    auto scene = Scene::create();

    auto layer = new TestController();
    scene->addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(scene);

    cocostudio::ArmatureDataManager::destroyInstance();
}

void TestScene::onEnter()
{
    Scene::onEnter();

    //add the menu item for back to main menu
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto label = Label::createWithTTF(ttfConfig,"MainMenu");

    auto menuItem = MenuItemLabel::create(label, testScene_callback );
    auto menu = Menu::create(menuItem, NULL);

    menu->setPosition( Point::ZERO );
    menuItem->setPosition( Point( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(menu, 1);
}
