#ifndef __CC_PLAYERCONTROLLER_H__
#define __CC_PLAYERCONTROLLER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class PlayerController : public cc::extension::ComController
{
protected:
    PlayerController(void);
    virtual ~PlayerController(void);
    
public:
    virtual void ccTouchesEnded(cc::Set *pTouches, cc::Event *pEvent);
    
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
   
   static PlayerController* create(void);
};


#endif  // __FUNDATION__CCCOMPONENT_H__
