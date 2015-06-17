#ifndef __CC_SceneController_H__
#define __CC_SceneController_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"

class SceneController : public cocostudio::ComController
{
protected:
    SceneController();
    virtual ~SceneController();
        
public:
    virtual bool init() override;
    virtual void onAdd() override;
    virtual void onRemove() override;
    virtual void update(float delta) override;
   
   static SceneController* create();
   
public:
    cocos2d::Vector<cocos2d::Node*>& getTargets() {return _targets;};
    cocos2d::Vector<cocos2d::Node*>& getProjectiles() {return _projectiles;};
    void spriteMoveFinished(cocos2d::Node* sender);
    void increaseKillCount();

    void addTarget();
    float _fAddTargetTime;
    float _fElapsedTime;
   
protected:
    cocos2d::Vector<cocos2d::Node*> _targets;
	cocos2d::Vector<cocos2d::Node*> _projectiles;
};


#endif  // __FUNDATION__CCCOMPONENT_H__
