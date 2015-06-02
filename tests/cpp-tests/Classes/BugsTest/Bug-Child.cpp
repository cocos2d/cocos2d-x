//
//  Bug-Child.cpp
//  cocos2d_tests
//
//  Created by NiTe Luo on 5/12/14.
//
//

#include "Bug-Child.h"

USING_NS_CC;

bool BugChild::init()
{
    if (BugsTestBase::init())
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

bool BugCameraMask::init()
{
    if (!BugsTestBase::init()) return false;
    
    auto size = Director::getInstance()->getWinSize();
    
    auto node = Node::create();
    node->setPosition(size.width/4, size.height/3);
    _sprite = Sprite::create("Images/grossini.png");
    node->addChild(_sprite);
    node->setCameraMask((unsigned short)CameraFlag::USER1);
    auto move = MoveBy::create(2, Vec2(200,0));
    
    node->runAction(RepeatForever::create(Sequence::createWithTwoActions(move, move->reverse())));
    addChild(node);
    
    auto camera = Camera::create();
    camera->setCameraFlag(CameraFlag::USER1);
    addChild(camera);
    
    
    auto item1 = MenuItemFont::create("Switch Child", CC_CALLBACK_1(BugCameraMask::switchSpriteFlag, this));
    
    auto menu = Menu::create(item1, nullptr);
    
    menu->alignItemsVertically();
    menu->setPosition(size.width/2, 100);
    addChild(menu);
    
    _spriteMaskLabel = Label::create();
    _spriteMaskLabel->setPosition(size.width/2, 120);
    addChild(_spriteMaskLabel);
    updateSpriteMaskLabel();
    
    auto label = Label::create();
    label->setPosition(size.width/2, size.height * 0.9);
    label->setString("Sprite should always run action.");
    addChild(label);
    
    return true;
}

void BugCameraMask::switchSpriteFlag(Ref *sender)
{
    if((unsigned short) CameraFlag::USER1 == _sprite->getCameraMask())
    {
        _sprite->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    }
    else
    {
        _sprite->setCameraMask((unsigned short)CameraFlag::USER1);
    }
    
    updateSpriteMaskLabel();
}

void BugCameraMask::updateSpriteMaskLabel()
{
    std::stringstream stream;
    stream<<"The camera Mask is "<<(_sprite->getCameraMask() == 1 ? "CamereFlag::Default" : "CameraFlag::User1")<<std::endl;
    _spriteMaskLabel->setString(stream.str());
}
