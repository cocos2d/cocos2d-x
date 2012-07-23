//
//  HelloWorldScene.h
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//

#ifndef __HELLOW_WORLD_H__
#define __HELLOW_WORLD_H__

#include "cocos2d.h"

// include Chipmunk headers
#include "chipmunk.h"

// HelloWorld Layer
class HelloWorld : public cocos2d::CCLayer {
public:
        HelloWorld();
        ~HelloWorld();
    
        static cocos2d::CCScene* scene();
        void step(cocos2d::ccTime dt);
        void addNewSpriteX(float x, float y);
        virtual void onEnter();
        virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent *event);
        
        LAYER_NODE_FUNC(HelloWorld);
    
private:
        bool init();
        cpSpace *space;
};

#endif // __HELLOW_WORLD_H__
