//
//  Bug-Child.cpp
//  cocos2d_tests
//
//  Created by NiTe Luo on 5/12/14.
//
//

#include "Bug-Child.h"

Scene* BugChild::scene()
{
    // 'scene' is an autorelease object.
    auto scene = Scene::create();
    // 'layer' is an autorelease object.
    auto layer = BugChild::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool BugChild::init()
{
    if (BugsTestBaseLayer::init())
    {
        auto size = Director::getInstance()->getWinSize();
        
        // create and initialize a Label
        auto item1 = MenuItemFont::create("Switch Child", CC_CALLBACK_1(BugChild::switchChild, this));
        
        menu = Menu::create(item1, nullptr);
        
        menu->alignItemsVertically();
        menu->setPosition(size.width/2, 100);
        addChild(menu);
        
        parent1 = Sprite::create("Images/grossini.png");
        parent1->setPosition(size.width/4, size.height/2);
        addChild(parent1);
        
        parent2 = Sprite::create("Images/grossinis_sister1.png");
        parent2->setPosition(size.width*3/4, size.height/2);
        addChild(parent2);
        
        child = Sprite::create("Images/grossinis_sister2.png");
        child->setPosition(20, 20);
        child->retain();
        parent1->addChild(child);
        return true;
    }
    
    return false;
}

void BugChild::switchChild(Ref *sender)
{
    if(parent1->getChildrenCount() > 0)
    {
        parent1->removeChild(child, false);
        parent2->addChild(child);
        CCLOG("Child attached to parent2");
    }
    else
    {
        parent2->removeChild(child, false);
        parent1->addChild(child);
        CCLOG("Child attached to parent1");
    }
}
