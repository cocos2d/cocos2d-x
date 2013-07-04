#ifndef __CC_SceneController_H__
#define __CC_SceneController_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class SceneController : public cocos2d::extension::CCComController
{
protected:
    SceneController(void);
    virtual ~SceneController(void);
        
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
   
   static SceneController* create(void);
   
public:
   cocos2d::CCArray* getTargets() {return _targets;};
   cocos2d::CCArray* getProjectiles() {return _projectiles;};
   void spriteMoveFinished(cocos2d::CCNode* sender);
   void increaseKillCount();
   
   void addTarget();
   float _fAddTargetTime;
   float _fElapsedTime;
   
   
protected:
    cocos2d::CCArray *_targets;
	cocos2d::CCArray *_projectiles;
};


#endif  // __FUNDATION__CCCOMPONENT_H__
