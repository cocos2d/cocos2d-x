#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "RectGame.h"

class BetweenGame : public RectGame
{
public:
    static cocos2d::Scene* createGameScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BetweenGame);
};

#endif // __HELLOWORLD_SCENE_H__
