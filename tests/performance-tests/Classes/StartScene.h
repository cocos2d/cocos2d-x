#ifndef __STARTSCENE_SCENE_H__
#define __STARTSCENE_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __STARTSCENE_SCENE_H__
