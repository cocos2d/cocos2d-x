#ifndef __CC_SceneController_H__
#define __CC_SceneController_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

class SceneController : public cocostudio::ComController
{
protected:
    SceneController(void);
    virtual ~SceneController(void);
        
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
   
   static SceneController* create(void);
   
public:
   cocos2d::Array* getTargets() {return _targets;};
   cocos2d::Array* getProjectiles() {return _projectiles;};
   void spriteMoveFinished(cocos2d::Node* sender);
   void increaseKillCount();
   
   void addTarget();
   float _fAddTargetTime;
   float _fElapsedTime;
   
   
protected:
    cocos2d::Array *_targets;
	  cocos2d::Array *_projectiles;
};


#endif  // __FUNDATION__CCCOMPONENT_H__
