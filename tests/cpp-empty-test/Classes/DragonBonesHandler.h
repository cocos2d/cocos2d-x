#pragma once

#include <string>
#include <vector>

#include "cocos2d.h"

namespace dragonBones
{
    class CCArmatureDisplay;
    class Armature;
    class EventObject;
    class AnimationState;
}

class DragonBoneBullet;

class DragonBonesHandler : public cocos2d::Node
{
public:
    DragonBonesHandler(cocos2d::Scene* scene);

    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
    void animationEventHandler(dragonBones::EventObject*);
    void frameEventHandler(dragonBones::EventObject*);
    
private:
    void updateAnimation();
    void jump();
    void squat(bool);
    void updateMove(int);
    void move(int);
    void updatePosition();
    void updateAnim();
    void updateAttack();
    void enterFrameHandler(float);
    void switchWeaponL();
    void switchWeaponR();
    void fire(const cocos2d::Vec2& firePoint);
    void addBullet(const std::shared_ptr<DragonBoneBullet>& bullet);
    void aim(float, float);
    void attack(bool);
    
private:
    static std::string NORMAL_ANIMATION_GROUP;
    static std::string AIM_ANIMATION_GROUP;
    static std::string ATTACK_ANIMATION_GROUP;
    static float JUMP_SPEED;
    static float NORMALIZE_MOVE_SPEED;
    static float MAX_MOVE_SPEED_FRONT;
    static float MAX_MOVE_SPEED_BACK;
    static std::vector<std::string> WEAPON_R_LIST;
    static std::vector<std::string> WEAPON_L_LIST;
    static float GROUND;
    static float G;
    
    cocos2d::Scene *_scene;
    dragonBones::CCArmatureDisplay *_armatureDisplay;
    dragonBones::Armature *_armature;
    dragonBones::Armature *_weaponR;
    dragonBones::Armature *_weaponL;
    dragonBones::AnimationState *_animState;
    dragonBones::AnimationState *_walkState;
    dragonBones::AnimationState *_attackState;
    cocos2d::Vec2 _target;
    std::vector<std::shared_ptr<DragonBoneBullet>> _bullets;
    
    
    bool _left;
    bool _right;
    bool _isJumpingA;
    bool _isJumpingB;
    bool _isAttackingA;
    bool _isAttackingB;
    bool _isSquating;
    int _weaponRIndex;
    int _weaponLIndex;
    int _faceDir;
    int _aimDir;
    int _moveDir;
    float _animRadian;
    float _speedX;
    float _speedY;
};

class DragonBoneBullet
{
public:
    DragonBoneBullet(cocos2d::Node *parent, dragonBones::Armature *armature, dragonBones::Armature *effect,
                                    float radian, float speed, const cocos2d::Vec2& position);
    
    bool update();
private:
    void doClean();
    
private:
    float _speedX;
    float _speedY;
    
    dragonBones::Armature *_armature;
    dragonBones::CCArmatureDisplay *_armatureDisplay;
    dragonBones::Armature *_effect;
};
