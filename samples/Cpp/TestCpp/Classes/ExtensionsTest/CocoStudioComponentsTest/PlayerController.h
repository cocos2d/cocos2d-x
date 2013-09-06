#ifndef __CC_PLAYERCONTROLLER_H__
#define __CC_PLAYERCONTROLLER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class PlayerController : public cocos2d::extension::CCComController
{
protected:
    PlayerController(void);
    virtual ~PlayerController(void);
    
public:
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
   
   static PlayerController* create(void);
};


#endif  // __FUNDATION__CCCOMPONENT_H__
