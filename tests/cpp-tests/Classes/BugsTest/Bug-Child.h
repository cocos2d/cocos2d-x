//
//  Bug-Child.h
//  cocos2d_tests
//
//  Created by NiTe Luo on 5/12/14.
//
//

#ifndef __Bug_Child__
#define __Bug_Child__

#include "BugsTest.h"

class BugChild : public BugsTestBase
{
public:
    CREATE_FUNC(BugChild);

    virtual bool init() override;
    
    void switchChild(cocos2d::Ref* sender);
    
protected:
    
    cocos2d::Sprite* parent1;
    cocos2d::Sprite* parent2;
    
    cocos2d::Sprite* child;
    
    cocos2d::Menu* menu;
};

class BugCameraMask : public BugsTestBase
{
public:
    CREATE_FUNC(BugCameraMask);
    
    virtual bool init() override;
    
    void switchSpriteFlag(cocos2d::Ref* sender);
    void updateSpriteMaskLabel();
    Node* _sprite;
    cocos2d::Label* _spriteMaskLabel;
};

#endif /* defined(__Bug_Child__) */
