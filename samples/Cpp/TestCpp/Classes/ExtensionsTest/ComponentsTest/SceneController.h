#ifndef __CC_SceneController_H__
#define __CC_SceneController_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class SceneController : public cc::extension::ComController
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
   cc::Array* getTargets() {return _targets;};
   cc::Array* getProjectiles() {return _projectiles;};
   void spriteMoveFinished(cc::Node* sender);
   void increaseKillCount();
   
   void addTarget();
   float _fAddTargetTime;
   float _fElapsedTime;
   
   
protected:
    cc::Array *_targets;
	cc::Array *_projectiles;
};


#endif  // __FUNDATION__CCCOMPONENT_H__
