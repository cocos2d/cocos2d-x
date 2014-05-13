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
        auto item1 = MenuItemFont::create("restart", CC_CALLBACK_1(BugChild::switchChild, this));
        
        menu = Menu::create(item1, NULL);
        
        menu->alignItemsVertically();
        menu->setPosition(size.width/2, 100);
        addChild(menu);
        
        parent1 = Sprite::create("grossini.png");
        parent1->setPosition(100, size.height/2);
        addChild(parent1);
        
        parent2 = Sprite::create("grossini_sister1.png");
        parent2->setPosition(300, size.height/2);
        addChild(parent2);
        
        child = Sprite::create("grossini_sister2.png");
        
        return true;
    }
    
    return false;
}

void BugChild::switchChild(Ref *sender)
{
    if(parent1->getChildrenCount() > 0)
    {
        child->removeFromParent();
        parent2->addChild(child);
    }
    else
    {
        child->removeFromParent();
        parent1->addChild(child);
    }
}
