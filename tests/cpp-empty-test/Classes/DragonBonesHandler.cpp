#include "DragonBonesHandler.h"

#include "ui/UIButton.h"

#include "dragonbones/DragonBonesHeaders.h"
#include "dragonbones/cocos2dx/CCDragonBonesHeaders.h"


std::string DragonBonesHandler::NORMAL_ANIMATION_GROUP = "normal";
std::string DragonBonesHandler::AIM_ANIMATION_GROUP = "aim";
std::string DragonBonesHandler::ATTACK_ANIMATION_GROUP = "attack";
float DragonBonesHandler::JUMP_SPEED = -20.f;
float DragonBonesHandler::NORMALIZE_MOVE_SPEED = 3.6f;
float DragonBonesHandler::MAX_MOVE_SPEED_FRONT = DragonBonesHandler::NORMALIZE_MOVE_SPEED * 1.4f;
float DragonBonesHandler::MAX_MOVE_SPEED_BACK = DragonBonesHandler::NORMALIZE_MOVE_SPEED * 1.f;
std::vector<std::string> DragonBonesHandler::WEAPON_R_LIST = {
    "weapon_1502b_r", "weapon_1005", "weapon_1005b", "weapon_1005c", "weapon_1005d", "weapon_1005e"
};
std::vector<std::string> DragonBonesHandler::WEAPON_L_LIST = {
    "weapon_1502b_l", "weapon_1005", "weapon_1005b", "weapon_1005c", "weapon_1005d"
};
float DragonBonesHandler::GROUND = 120;
float DragonBonesHandler::G = -0.6f;

using namespace dragonBones;

DragonBonesHandler::DragonBonesHandler(cocos2d::Scene* scene)
: _scene(scene)
, _left(false)
, _right(false)
, _isJumpingA(false)
, _isJumpingB(false)
, _isAttackingA(false)
, _isAttackingB(false)
, _isSquating(false)
, _weaponRIndex(0)
, _weaponLIndex(0)
, _faceDir(1)
, _aimDir(0)
, _moveDir(0)
, _animRadian(0.f)
, _speedX(0.f)
, _speedY(0.f)
, _animState(nullptr)
, _walkState(nullptr)
, _attackState(nullptr)
, _target(0, 0)
{
    _armatureDisplay = cocos2d::utils::findChild<CCArmatureDisplay*>(_scene, "DragonBoneNode");
    _armature = _armatureDisplay->_armature;
    
    
    _armatureDisplay->addEvent(EventObject::FADE_IN_COMPLETE, CC_CALLBACK_1(DragonBonesHandler::animationEventHandler, this));
    _armatureDisplay->addEvent(EventObject::FADE_OUT_COMPLETE, CC_CALLBACK_1(DragonBonesHandler::animationEventHandler, this));
    
    
    _armature->getSlot("effects_1")->displayController = DragonBonesHandler::NORMAL_ANIMATION_GROUP;
    _armature->getSlot("effects_2")->displayController = DragonBonesHandler::NORMAL_ANIMATION_GROUP;
    
    _weaponR = this->_armature->getSlot("weapon_r")->getChildArmature();
    _weaponL = this->_armature->getSlot("weapon_l")->getChildArmature();
    static_cast<CCArmatureDisplay*>(_weaponR->_display)->addEvent(EventObject::FRAME_EVENT, CC_CALLBACK_1(DragonBonesHandler::frameEventHandler, this));
    static_cast<CCArmatureDisplay*>(_weaponL->_display)->addEvent(EventObject::FRAME_EVENT, CC_CALLBACK_1(DragonBonesHandler::frameEventHandler, this));
    
    updateAnimation();
    
    // up
    auto button = cocos2d::utils::findChild<cocos2d::ui::Button*>(_scene, "up");
    button->addClickEventListener([=](cocos2d::Ref*){
        this->jump();
    });
    
    // down
    button = cocos2d::utils::findChild<cocos2d::ui::Button*>(_scene, "down");
    button->addTouchEventListener([=](cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
            this->squat(true);
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
            this->squat(false);
    });
    
    // left
    button = cocos2d::utils::findChild<cocos2d::ui::Button*>(_scene, "left");
    button->addTouchEventListener([=](cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
            this->_left = true;
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
            this->_left = false;
        
        this->updateMove(-1);
    });
    
    // right
    button = cocos2d::utils::findChild<cocos2d::ui::Button*>(_scene, "right");
    button->addTouchEventListener([=](cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
            this->_right = true;
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
            this->_right = false;
        
        this->updateMove(-1);
    });
    
    // change weapon L
    button = cocos2d::utils::findChild<cocos2d::ui::Button*>(_scene, "ChangeWeaponL");
    button->addClickEventListener([=](cocos2d::Ref*){
        this->switchWeaponL();
    });
    
    // change weapon R
    button = cocos2d::utils::findChild<cocos2d::ui::Button*>(_scene, "ChangeWeaponR");
    button->addClickEventListener([=](cocos2d::Ref*){
        this->switchWeaponR();
    });
    
    scheduleUpdate();
}

void DragonBonesHandler::update(float dt)
{
    Node::update(dt);
    updatePosition();
    updateAnim();
    updateAttack();
    enterFrameHandler(dt);
}

void DragonBonesHandler::onEnter()
{
    Node::onEnter();
    
    // touch events
    cocos2d::EventListenerTouchAllAtOnce* touchLisener = cocos2d::EventListenerTouchAllAtOnce::create();
    touchLisener->onTouchesBegan = [=](const std::vector<cocos2d::Touch*>&, cocos2d::Event*) -> bool{
        this->attack(true);
        return true;
    };
    touchLisener->onTouchesMoved = [=](const std::vector<cocos2d::Touch*>& touches, cocos2d::Event*){
        auto touchLoc = touches[0]->getLocation();
        this->aim(touchLoc.x, touchLoc.y);
    };
    touchLisener->onTouchesEnded = [=](const std::vector<cocos2d::Touch*>&, cocos2d::Event*){
        this->attack(false);
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchLisener, _armatureDisplay);
}

void DragonBonesHandler::onExit()
{
    Node::onExit();
    // since `CCArmatureDisplay` reset EventDispacher, so we should remove event listener manually
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(_armatureDisplay);
    
    dragonBones::CCFactory::destroyInstance();
}

void DragonBonesHandler::animationEventHandler(dragonBones::EventObject* event)
{
    if (event->type == dragonBones::EventObject::FADE_IN_COMPLETE)
    {
        if (event->animationState->getName() == "jump_1")
        {
            _isJumpingB = true;
            _speedY = -DragonBonesHandler::JUMP_SPEED;
            _armature->getAnimation().fadeIn("jump_2", -1, -1, 0, DragonBonesHandler::NORMAL_ANIMATION_GROUP);
        }
        else if (event->animationState->getName() == "jump_4")
            updateAnimation();
    }
    else if (event->type == dragonBones::EventObject::FADE_OUT_COMPLETE)
    {
        if (event->animationState->getName() == "attack_01")
        {
            _isAttackingB = false;
            _attackState = nullptr;
        }
    }
}

void DragonBonesHandler::frameEventHandler(dragonBones::EventObject* event)
{
    if (event->animationState->getName() == "fire_01")
    {
        auto firePointBone = event->armature->getBone("firePoint");
        auto localPoint = cocos2d::Vec2(firePointBone->global.x, -firePointBone->global.y);
        
        auto display = (dragonBones::CCArmatureDisplay*)event->armature->getDisplay();
        auto globalPoint = display->convertToWorldSpace(localPoint);
        
        fire(globalPoint);
    }
}

void DragonBonesHandler::updateAnimation()
{
    if (_isJumpingA)
        return;
    
    if (_isSquating)
    {
        _speedX = 0.f;
        _armature->getAnimation().fadeIn("squat", -1, -1, 0, DragonBonesHandler::NORMAL_ANIMATION_GROUP);
        _walkState = nullptr;
        return;
    }
    
    if (_moveDir == 0)
    {
        _speedX = 0.f;
        _armature->getAnimation().fadeIn("idle", -1, -1, 0, DragonBonesHandler::NORMAL_ANIMATION_GROUP);
        _walkState = nullptr;
    }
    else
    {
        if (!_walkState)
            _walkState = _armature->getAnimation().fadeIn("walk", -1, -1, 0, DragonBonesHandler::NORMAL_ANIMATION_GROUP);
        
        if (_moveDir * _faceDir > 0)
        {
            _walkState->timeScale = DragonBonesHandler::MAX_MOVE_SPEED_FRONT / DragonBonesHandler::NORMALIZE_MOVE_SPEED;
            _speedX = DragonBonesHandler::MAX_MOVE_SPEED_FRONT * _faceDir;
        }
        else
        {
            _walkState->timeScale = -DragonBonesHandler::MAX_MOVE_SPEED_BACK / DragonBonesHandler::NORMALIZE_MOVE_SPEED;
            _speedX = -DragonBonesHandler::MAX_MOVE_SPEED_BACK * _faceDir;
        }
    }
}

void DragonBonesHandler::jump()
{
    if (_isJumpingA)
        return;
    
    _isJumpingA = true;
    _armature->getAnimation().fadeIn("jump_1", -1, -1, 0, DragonBonesHandler::NORMAL_ANIMATION_GROUP);
    _walkState = nullptr;
}

void DragonBonesHandler::squat(bool isSquating)
{
    if (_isSquating == isSquating)
        return;
    
    _isSquating = isSquating;
    updateAnimation();
}

void DragonBonesHandler::updateMove(int dir)
{
    if (_left && _right)
        move(dir);
    else if (_left)
        move(-1);
    else if (_right)
        move(1);
    else
        move(0);
}

void DragonBonesHandler::move(int dir)
{
    if (_moveDir == dir)
        return;
    
    _moveDir = dir;
    updateAnimation();
}

void DragonBonesHandler::aim(float x, float y)
{
    if (_aimDir == 0)
        _aimDir = 10;
    
    _target = _armatureDisplay->getParent()->convertToNodeSpace(cocos2d::Vec2(x, y));
}

void DragonBonesHandler::attack(bool isAttacking)
{
    if (_isAttackingA == isAttacking)
        return;
    
    _isAttackingA = isAttacking;
}

void DragonBonesHandler::updatePosition()
{
    if (_speedX != 0.f)
    {
        auto armatureDisplayPos = _armatureDisplay->getPosition();
        _armatureDisplay->setPositionX(armatureDisplayPos.x + _speedX);
        auto visibleRect = cocos2d::Director::getInstance()->getVisibleSize();
        auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
        auto minX = visibleOrigin.x + 10;
        auto maxX = visibleRect.width + visibleOrigin.x;
        if (armatureDisplayPos.x < minX)
            _armatureDisplay->setPositionX(minX);
        else if (armatureDisplayPos.x > maxX)
            _armatureDisplay->setPositionX(maxX);
    }
    
    if (_speedY != 0)
    {
        if (_speedY > 5 && (_speedY + DragonBonesHandler::G) <= 5)
            _armature->getAnimation().fadeIn("jump_3", -1, -1, 0, DragonBonesHandler::NORMAL_ANIMATION_GROUP);
        
        _speedY += DragonBonesHandler::G;
        
        auto armatureDisplayPos = _armatureDisplay->getPosition();
        _armatureDisplay->setPositionY(armatureDisplayPos.y + _speedY);
        if (armatureDisplayPos.y < DragonBonesHandler::GROUND)
        {
            _armatureDisplay->setPositionY(DragonBonesHandler::GROUND);
            _isJumpingA = false;
            _isJumpingB = false;
            _speedX = 0.f;
            _speedY = 0.f;
            _armature->getAnimation().fadeIn("jump_4", -1, -1, 0, DragonBonesHandler::NORMAL_ANIMATION_GROUP);
            if (_isSquating || _moveDir)
                updateAnimation();
        }
    }
}

void DragonBonesHandler::updateAnim()
{
    if (_aimDir == 0)
        return;
    
    auto position = _armatureDisplay->getPosition();
    _faceDir = _target.x > position.x ? 1 : -1;
    if (_armatureDisplay->getScaleX() * _faceDir < 0)
    {
        _armatureDisplay->setScaleX(_armatureDisplay->getScaleX() * -1);
        if (_moveDir)
            updateAnimation();
    }
    
    auto animOffsetY = _armature->getBone("chest")->global.y * _armatureDisplay->getScaleY();
    if (_faceDir > 0)
        _animRadian = std::atan2(-(_target.y - position.y + animOffsetY), _target.x - position.x);
    else
    {
        _animRadian = M_PI - std::atan2(-(_target.y - position.y + animOffsetY), _target.x - position.x);
        if (_animRadian > M_PI)
            _animRadian -= M_PI * 2;
    }
    
    int aimDir = 0;
    if (_animRadian > 0)
        aimDir = -1;
    else
        aimDir = 1;
    
    if (_aimDir != aimDir)
    {
        _aimDir = aimDir;
        
        if (_aimDir >=0)
            _animState = _armature->getAnimation().fadeIn("aimUp", 0, 1, 0,
                                                          DragonBonesHandler::AIM_ANIMATION_GROUP,
                                                          dragonBones::AnimationFadeOutMode::SameGroup);
        else
            _animState = _armature->getAnimation().fadeIn("aimDown", 0, 1, 0,
                                                          DragonBonesHandler::AIM_ANIMATION_GROUP,
                                                          dragonBones::AnimationFadeOutMode::SameGroup);
    }
    
    _animState->weight = std::fabs(_animRadian / M_PI * 2);
    _armature->invalidUpdate();
}

void DragonBonesHandler::updateAttack()
{
    if (!_isAttackingA || _isAttackingB)
        return;
    
    _isAttackingB = true;
    
    _attackState = _armature->getAnimation().fadeIn("attack_01", -1, -1, 0,
                                                    DragonBonesHandler::ATTACK_ANIMATION_GROUP,
                                                    dragonBones::AnimationFadeOutMode::SameGroup);
    
    _attackState->autoFadeOutTime = _attackState->fadeTotalTime;
    _attackState->addBoneMask("pelvis");
}

void DragonBonesHandler::enterFrameHandler(float dt)
{
    auto iter = _bullets.begin();
    while (iter != _bullets.end())
    {
        if ((*iter)->update())
            iter = _bullets.erase(iter);
        else
            ++iter;
    }
        
    dragonBones::WorldClock::clock.advanceTime(dt);
}

void DragonBonesHandler::switchWeaponL()
{
    static_cast<CCArmatureDisplay*>(_weaponL->_display)->removeEvent(dragonBones::EventObject::FRAME_EVENT);
    
    _weaponLIndex = (_weaponLIndex + 1) % DragonBonesHandler::WEAPON_L_LIST.size();
    auto newWeaponName = DragonBonesHandler::WEAPON_L_LIST[_weaponLIndex];
    _weaponL = dragonBones::CCFactory::getInstance()->buildArmature(newWeaponName);
    _armature->getSlot("weapon_l")->setChildArmature(_weaponL);
    
    static_cast<CCArmatureDisplay*>(_weaponL->_display)->addEvent(dragonBones::EventObject::FRAME_EVENT, CC_CALLBACK_1(DragonBonesHandler::frameEventHandler, this));
}

void DragonBonesHandler::switchWeaponR()
{
    static_cast<CCArmatureDisplay*>(_weaponR->_display)->removeEvent(dragonBones::EventObject::FRAME_EVENT);
    
    _weaponRIndex = (_weaponRIndex + 1) % DragonBonesHandler::WEAPON_R_LIST.size();
    auto newWeaponName = DragonBonesHandler::WEAPON_R_LIST[_weaponRIndex];
    _weaponR = dragonBones::CCFactory::getInstance()->buildArmature(newWeaponName);
    _armature->getSlot("weapon_r")->setChildArmature(_weaponR);
    
    static_cast<CCArmatureDisplay*>(_weaponR->_display)->addEvent(dragonBones::EventObject::FRAME_EVENT, CC_CALLBACK_1(DragonBonesHandler::frameEventHandler, this));
}

void DragonBonesHandler::fire(const cocos2d::Vec2& pos)
{
    auto firePoint = pos;
    firePoint.x += cocos2d::random(0, 1) * 2 - 1;
    firePoint.y += cocos2d::random(0, 1) * 2 - 1;
    
    auto armature = dragonBones::CCFactory::getInstance()->buildArmature("bullet_01");
    auto effect = dragonBones::CCFactory::getInstance()->buildArmature("fireEffect_01");
    auto radian = _faceDir < 0 ? M_PI - _animRadian : _animRadian;
    auto bullet = std::make_shared<DragonBoneBullet>(_parent, armature, effect, radian + cocos2d::random(0, 1) * 0.02f - 0.01f, 40, firePoint);
    addBullet(bullet);
}

void DragonBonesHandler::addBullet(const std::shared_ptr<DragonBoneBullet>& bullet)
{
    _bullets.push_back(bullet);
}

/***************************************
 DragonBoneBullet
 **************************************/
DragonBoneBullet::DragonBoneBullet(cocos2d::Node *parent, dragonBones::Armature *armature, dragonBones::Armature *effect,
                 float radian, float speed, const cocos2d::Vec2& position)
{
    _speedX = std::cos(radian) * speed;
    _speedY = -std::sin(radian) * speed;
    auto thePos = parent->convertToNodeSpace(position);
    
    _armature = armature;
    _armatureDisplay = static_cast<dragonBones::CCArmatureDisplay*>(_armature->_display);
    _armatureDisplay->setPosition(thePos);
    _armatureDisplay->setRotation(radian * dragonBones::RADIAN_TO_ANGLE);
    _armature->getAnimation().play("idle");
    
    if (effect)
    {
        _effect = effect;
        auto effectDisplay = static_cast<dragonBones::CCArmatureDisplay*>(_effect->_display);
        effectDisplay->setRotation(radian * dragonBones::RADIAN_TO_ANGLE);
        effectDisplay->setPosition(thePos);
        effectDisplay->setScaleX(1 + cocos2d::random(0, 1));
        effectDisplay->setScaleY(1 + cocos2d::random(0, 1) * 0.5f);
        if (cocos2d::random() < 0.5f)
            effectDisplay->setScaleY(effectDisplay->getScaleY() * -1);
        
        _effect->getAnimation().play("idle");
        dragonBones::WorldClock::clock.add(_effect);
        parent->addChild(effectDisplay);
    }
    
    dragonBones::WorldClock::clock.add(_armature);
    parent->addChild(_armatureDisplay);
}

bool DragonBoneBullet::update()
{
    _armatureDisplay->setPosition(_armatureDisplay->getPosition() + cocos2d::Vec2(_speedX, _speedY));
    
    auto worldPos = _armatureDisplay->getParent()->convertToWorldSpace(_armatureDisplay->getPosition());
    auto visibleRect = cocos2d::Director::getInstance()->getVisibleSize();
    auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
    if (worldPos.x < visibleOrigin.x || worldPos.x >= visibleOrigin.x + visibleRect.width ||
        worldPos.y < visibleOrigin.y || worldPos.y >= visibleOrigin.y + visibleRect.height)
    {
        doClean();
        return true;
    }
    
    return false;
}

void DragonBoneBullet::doClean()
{
    dragonBones::WorldClock::clock.remove(_armature);
    _armatureDisplay->removeFromParent();
    _armature->dispose();
    
    if (_effect)
    {
        dragonBones::WorldClock::clock.remove(_effect);
        static_cast<CCArmatureDisplay*>(_effect->_display)->removeFromParent();
        _effect->dispose();
    }
}
