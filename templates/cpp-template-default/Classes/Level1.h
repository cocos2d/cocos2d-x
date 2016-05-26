#ifndef __LEVEL1_H__
#define __LEVEL1_H__

// items from the engine
#include "cocos2d.h"

// standard c++
#include <iostream>

class Level1
{
public:
    Level1();
    
    cocos2d::Scene* createScene();
    
    cocos2d::Node* physics(const cocos2d::Size& size, cocos2d::Scene* scene);
    
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
private:
    cocos2d::Scene* scene;

};

#endif // __LEVEL1_H__
