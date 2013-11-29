#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "CCEventListenerTouch.h"
#include "CCVector.h"

USING_NS_CC;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void showSprites(const Vector<Sprite*>& sprites)
{
    log("container size = %ld", sprites.count());
    for (auto& sp : sprites)
    {
        log("sp tag: %d, ref count = %d", sp->getTag(), sp->retainCount());
    }
}

Vector<Sprite*> createAllSprites()
{
    Vector<Sprite*> ret;
    ret.addObject(Sprite::create());
    ret.addObject(Sprite::create());
    return ret;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    Vector<Sprite*> container;
    
    for (int i = 0; i < 10; ++i)
    {
        auto sp = Sprite::create();
        sp->setTag(i);
        container.addObject(sp);
    }

//
//    showSprites(container);
//    
//    Vector<Sprite*> containerCopy = container;
//    
//    showSprites(containerCopy);
//    
//    containerCopy = container;
//    
//    showSprites(containerCopy);
    
//    Vector<Sprite*> moveVector(createAllSprites());
//    showSprites(moveVector);
//    
//    CCLOG("-------------  2  ----------");
//    moveVector = createAllSprites();
//    showSprites(moveVector);
//    
//    CCLOG("-------------  3  ----------");
//    Vector<Sprite*> aaa;
//    aaa.addObject(Sprite::create());
//    moveVector = aaa;
//    showSprites(moveVector);
    
    log("size of Vector = %ld", sizeof(Vector<Sprite*>));
    
    Map<std::string, Sprite*> map;
    map.setObject(Sprite::create(), "1");
    map.setObject(Sprite::create(), "2");
    map.setObject(Sprite::create(), "3");

    auto showMap = [](const Map<std::string, Sprite*>& map)
    {
        for (auto iter = map.begin(); iter != map.end(); ++iter)
        {
            log("key = %s, value = %p, ref = %d", iter->first.c_str(), iter->second, iter->second ? iter->second->retainCount() : 0);
        }
    };
    
    showMap(map);
    
//    auto iter = std::find(map.begin(), map.end(), std::string("111"));
//    if (iter != map.end())
//    {
//        log("found!");
//    }
//    else
//    {
//        log("not found!");
//    }
    
//    map["111"];
//    log("key[1]=%p", map["1"]);
//    log("----------------------");
//    map["11"]->setPosition(Point(100, 100));
    
    showMap(map);
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(origin + Point(visibleSize) - Point(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    this->getChildren().forEach([](Node* node){
        log("node = %p, name = %s", node, typeid(*node).name());
    });
    
    return true;
}

void HelloWorld::menuCloseCallback(Object* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
