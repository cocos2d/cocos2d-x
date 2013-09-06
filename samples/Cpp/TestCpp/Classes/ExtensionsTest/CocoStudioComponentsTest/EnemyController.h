#ifndef __CC_ENEMYCONTROLLER_H__
#define __CC_ENEMYCONTROLLER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class EnemyController : public cocos2d::extension::CCComController
{
protected:
    EnemyController(void);
    virtual ~EnemyController(void);
        
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
   
    static EnemyController* create(void);
public:
    void die();
};


#endif  // __FUNDATION__CCCOMPONENT_H__
