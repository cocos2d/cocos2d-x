/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "physics/CCPhysicsJoint.h"
#if CC_USE_PHYSICS
#include "chipmunk.h"

#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsWorld.h"
#include "chipmunk/CCPhysicsHelper_chipmunk.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

PhysicsJoint::PhysicsJoint()
: _bodyA(nullptr)
, _bodyB(nullptr)
, _world(nullptr)
, _enable(false)
, _collisionEnable(true)
, _destoryMark(false)
, _initDirty(true)
, _tag(0)
, _maxForce(PHYSICS_INFINITY)
{
    
}

PhysicsJoint::~PhysicsJoint()
{
    // reset the shapes collision group
    setCollisionEnable(true);
    
    for (cpConstraint* joint : _joints)
    {
        cpConstraintFree(joint);
    }
    _joints.clear();
}

bool PhysicsJoint::init(cocos2d::PhysicsBody *a, cocos2d::PhysicsBody *b)
{
    do
    {
        CCASSERT(a != nullptr && b != nullptr, "the body passed in is nil");
        CCASSERT(a != b, "the two bodies are equal");
        
        _bodyA = a;
        _bodyB = b;
        _bodyA->_joints.push_back(this);
        _bodyB->_joints.push_back(this);

        return true;
    } while (false);
    
    return false;
}

bool PhysicsJoint::initJoint()
{
    bool ret = !_initDirty;
    while (_initDirty)
    {
        ret = _initJoint();
        CC_BREAK_IF(!ret);

        for (auto subjoint : _joints)
        {
            subjoint->maxForce = _maxForce;
            subjoint->errorBias = cpfpow(1.0f - 0.15f, 60.0f);
            cpSpaceAddConstraint(_world->_space, subjoint);
        }
        _initDirty = false;
        ret = true;
    }

    return ret;
}

void PhysicsJoint::setEnable(bool enable)
{
    if (_enable != enable)
    {
        _enable = enable;
        
        if (_world)
        {
            if (enable)
            {
                _world->addJoint(this);
            }else
            {
                _world->removeJoint(this, false);
            }
        }
    }
}

void PhysicsJoint::setCollisionEnable(bool enable)
{
    if (_collisionEnable != enable)
    {
        _collisionEnable = enable;
    }
}

void PhysicsJoint::removeFormWorld()
{
    if (_world)
    {
        _world->removeJoint(this, false);
    }
}

void PhysicsJoint::setMaxForce(float force)
{
    _maxForce = force;
    for (auto joint : _joints)
    {
        joint->maxForce = PhysicsHelper::float2cpfloat(force);
    }
}

PhysicsJointFixed* PhysicsJointFixed::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr)
{
    auto joint = new (std::nothrow) PhysicsJointFixed();
    
    if (joint && joint->init(a, b))
    {
        joint->_anchr = anchr;
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointFixed::_initJoint()
{
    do
    {
        _bodyA->getNode()->setPosition(_anchr);
        _bodyB->getNode()->setPosition(_anchr);

        // add a pivot joint to fixed two body together
        auto joint = cpPivotJointNew(_bodyA->getBody(), _bodyB->getBody(),
            PhysicsHelper::point2cpv(_anchr));
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);

        // add a gear joint to make two body have the same rotation.
        joint = cpGearJointNew(_bodyA->getBody(), _bodyB->getBody(), 0, 1);
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);

        _collisionEnable = false;

        return true;
    } while (false);
    
    return false;
}

PhysicsJointPin* PhysicsJointPin::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& pivot)
{
    auto joint = new (std::nothrow) PhysicsJointPin();
    
    if (joint && joint->init(a, b))
    {
        joint->_anchr1 = pivot;
        joint->_useSpecificAnchr = false;
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

PhysicsJointPin* PhysicsJointPin::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2)
{
    auto joint = new (std::nothrow) PhysicsJointPin();

    if (joint && joint->init(a, b))
    {
        joint->_anchr1 = anchr1;
        joint->_anchr2 = anchr2;
        joint->_useSpecificAnchr = true;

        return joint;
    }

    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointPin::_initJoint()
{
    do
    {
        cpConstraint* joint = nullptr;
        if (_useSpecificAnchr)
        {
            joint = cpPivotJointNew2(_bodyA->getBody(), _bodyB->getBody(),
                PhysicsHelper::point2cpv(_anchr1), PhysicsHelper::point2cpv(_anchr2));
        } 
        else
        {
            joint = cpPivotJointNew(_bodyA->getBody(), _bodyB->getBody(),
                PhysicsHelper::point2cpv(_anchr1));
        }

        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);

        return true;
    } while (false);
    
    return false;
}

PhysicsJointLimit* PhysicsJointLimit::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float min, float max)
{
    auto joint = new (std::nothrow) PhysicsJointLimit();
    
    if (joint && joint->init(a, b))
    {
        joint->_anchr1 = anchr1;
        joint->_anchr2 = anchr2;
        joint->_min = min;
        joint->_max = max;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

PhysicsJointLimit* PhysicsJointLimit::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2)
{
    return construct(a, b, anchr1, anchr2, 0, b->local2World(anchr1).getDistance(a->local2World(anchr2)));
}

bool PhysicsJointLimit::_initJoint()
{
    do
    {
        auto joint = cpSlideJointNew(_bodyA->getBody(), _bodyB->getBody(),
            PhysicsHelper::point2cpv(_anchr1),
            PhysicsHelper::point2cpv(_anchr2),
            PhysicsHelper::float2cpfloat(_min),
            PhysicsHelper::float2cpfloat(_max));

        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);

        return true;
    } while (false);
    
    return false;
}

float PhysicsJointLimit::getMin() const
{
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMin(_joints.front()));
}

void PhysicsJointLimit::setMin(float min)
{
    cpSlideJointSetMin(_joints.front(), PhysicsHelper::float2cpfloat(min));
}

float PhysicsJointLimit::getMax() const
{
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMax(_joints.front()));
}

void PhysicsJointLimit::setMax(float max)
{
    cpSlideJointSetMax(_joints.front(), PhysicsHelper::float2cpfloat(max));
}

Vec2 PhysicsJointLimit::getAnchr1() const
{
    return PhysicsHelper::cpv2point(cpSlideJointGetAnchr1(_joints.front()));
}

void PhysicsJointLimit::setAnchr1(const Vec2& anchr)
{
    cpSlideJointSetAnchr1(_joints.front(), PhysicsHelper::point2cpv(anchr));
}

Vec2 PhysicsJointLimit::getAnchr2() const
{
    return PhysicsHelper::cpv2point(cpSlideJointGetAnchr2(_joints.front()));
}

void PhysicsJointLimit::setAnchr2(const Vec2& anchr)
{
    cpSlideJointSetAnchr1(_joints.front(), PhysicsHelper::point2cpv(anchr));
}

PhysicsJointDistance* PhysicsJointDistance::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2)
{
    auto joint = new (std::nothrow) PhysicsJointDistance();
    
    if (joint && joint->init(a, b))
    {
        joint->_anchr1 = anchr1;
        joint->_anchr2 = anchr2;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointDistance::_initJoint()
{
    do
    {
        auto joint = cpPinJointNew(_bodyA->getBody(),
                                   _bodyB->getBody(),
                                   PhysicsHelper::point2cpv(_anchr1),
                                   PhysicsHelper::point2cpv(_anchr2));
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointDistance::getDistance() const
{
    return PhysicsHelper::cpfloat2float(cpPinJointGetDist(_joints.front()));
}

void PhysicsJointDistance::setDistance(float distance)
{
    cpPinJointSetDist(_joints.front(), PhysicsHelper::float2cpfloat(distance));
}

PhysicsJointSpring* PhysicsJointSpring::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float stiffness, float damping)
{
    auto joint = new (std::nothrow) PhysicsJointSpring();
    
    if (joint && joint->init(a, b))
    {
        joint->_anchr1 = anchr1;
        joint->_anchr2 = anchr2;
        joint->_stiffness = stiffness;
        joint->_damping = damping;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointSpring::_initJoint()
{
    do {
        auto joint = cpDampedSpringNew(_bodyA->getBody(),
                                                _bodyB->getBody(),
                                                PhysicsHelper::point2cpv(_anchr1),
                                                PhysicsHelper::point2cpv(_anchr2),
                                                PhysicsHelper::float2cpfloat(_bodyB->local2World(_anchr1).getDistance(_bodyA->local2World(_anchr2))),
                                                PhysicsHelper::float2cpfloat(_stiffness),
                                                PhysicsHelper::float2cpfloat(_damping));
        
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

Vec2 PhysicsJointSpring::getAnchr1() const
{
    return PhysicsHelper::cpv2point(cpDampedSpringGetAnchr1(_joints.front()));
}

void PhysicsJointSpring::setAnchr1(const Vec2& anchr)
{
    cpDampedSpringSetAnchr1(_joints.front(), PhysicsHelper::point2cpv(anchr));
}

Vec2 PhysicsJointSpring::getAnchr2() const
{
    return PhysicsHelper::cpv2point(cpDampedSpringGetAnchr2(_joints.front()));
}

void PhysicsJointSpring::setAnchr2(const Vec2& anchr)
{
    cpDampedSpringSetAnchr1(_joints.front(), PhysicsHelper::point2cpv(anchr));
}

float PhysicsJointSpring::getRestLength() const
{
    return PhysicsHelper::cpfloat2float(cpDampedSpringGetRestLength(_joints.front()));
}

void PhysicsJointSpring::setRestLength(float restLength)
{
    cpDampedSpringSetRestLength(_joints.front(), PhysicsHelper::float2cpfloat(restLength));
}

float PhysicsJointSpring::getStiffness() const
{
    return PhysicsHelper::cpfloat2float(cpDampedSpringGetStiffness(_joints.front()));
}

void PhysicsJointSpring::setStiffness(float stiffness)
{
    cpDampedSpringSetStiffness(_joints.front(), PhysicsHelper::float2cpfloat(stiffness));
}

float PhysicsJointSpring::getDamping() const
{
    return PhysicsHelper::cpfloat2float(cpDampedSpringGetDamping(_joints.front()));
}

void PhysicsJointSpring::setDamping(float damping)
{
    cpDampedSpringSetDamping(_joints.front(), PhysicsHelper::float2cpfloat(damping));
}

PhysicsJointGroove* PhysicsJointGroove::construct(PhysicsBody* a, PhysicsBody* b, const Vec2& grooveA, const Vec2& grooveB, const Vec2& anchr2)
{
    auto joint = new (std::nothrow) PhysicsJointGroove();
    
    if (joint && joint->init(a, b))
    {
        joint->_grooveA = grooveA;
        joint->_grooveB = grooveB;
        joint->_anchr2 = anchr2;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointGroove::_initJoint()
{
    do {
        auto joint = cpGrooveJointNew(_bodyA->getBody(),
                                               _bodyB->getBody(),
                                               PhysicsHelper::point2cpv(_grooveA),
                                               PhysicsHelper::point2cpv(_grooveB),
                                               PhysicsHelper::point2cpv(_anchr2));
        
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

Vec2 PhysicsJointGroove::getGrooveA() const
{
    return PhysicsHelper::cpv2point(cpGrooveJointGetGrooveA(_joints.front()));
}

void PhysicsJointGroove::setGrooveA(const Vec2& grooveA)
{
    cpGrooveJointSetGrooveA(_joints.front(), PhysicsHelper::point2cpv(grooveA));
}

Vec2 PhysicsJointGroove::getGrooveB() const
{
    return PhysicsHelper::cpv2point(cpGrooveJointGetGrooveB(_joints.front()));
}

void PhysicsJointGroove::setGrooveB(const Vec2& grooveB)
{
    cpGrooveJointSetGrooveB(_joints.front(), PhysicsHelper::point2cpv(grooveB));
}

Vec2 PhysicsJointGroove::getAnchr2() const
{
    return PhysicsHelper::cpv2point(cpGrooveJointGetAnchr2(_joints.front()));
}

void PhysicsJointGroove::setAnchr2(const Vec2& anchr2)
{
    cpGrooveJointSetAnchr2(_joints.front(), PhysicsHelper::point2cpv(anchr2));
}

PhysicsJointRotarySpring* PhysicsJointRotarySpring::construct(PhysicsBody* a, PhysicsBody* b, float stiffness, float damping)
{
    auto joint = new (std::nothrow) PhysicsJointRotarySpring();
    
    if (joint && joint->init(a, b))
    {
        joint->_stiffness = stiffness;
        joint->_damping = damping;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointRotarySpring::_initJoint()
{
    do {
        auto joint = cpDampedRotarySpringNew(_bodyA->getBody(),
                                                      _bodyB->getBody(),
                                                      PhysicsHelper::float2cpfloat(_bodyB->getRotation() - _bodyA->getRotation()),
                                                      PhysicsHelper::float2cpfloat(_stiffness),
                                                      PhysicsHelper::float2cpfloat(_damping));
        
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointRotarySpring::getRestAngle() const
{
    return PhysicsHelper::cpfloat2float(cpDampedRotarySpringGetRestAngle(_joints.front()));
}

void PhysicsJointRotarySpring::setRestAngle(float restAngle)
{
    cpDampedRotarySpringSetRestAngle(_joints.front(), PhysicsHelper::float2cpfloat(restAngle));
}

float PhysicsJointRotarySpring::getStiffness() const
{
    return PhysicsHelper::cpfloat2float(cpDampedRotarySpringGetStiffness(_joints.front()));
}

void PhysicsJointRotarySpring::setStiffness(float stiffness)
{
    cpDampedRotarySpringSetStiffness(_joints.front(), PhysicsHelper::float2cpfloat(stiffness));
}

float PhysicsJointRotarySpring::getDamping() const
{
    return PhysicsHelper::cpfloat2float(cpDampedRotarySpringGetDamping(_joints.front()));
}

void PhysicsJointRotarySpring::setDamping(float damping)
{
    cpDampedRotarySpringSetDamping(_joints.front(), PhysicsHelper::float2cpfloat(damping));
}

PhysicsJointRotaryLimit* PhysicsJointRotaryLimit::construct(PhysicsBody* a, PhysicsBody* b, float min, float max)
{
    auto joint = new (std::nothrow) PhysicsJointRotaryLimit();
    
    if (joint && joint->init(a, b))
    {
        joint->_min = min;
        joint->_max = max;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

PhysicsJointRotaryLimit* PhysicsJointRotaryLimit::construct(PhysicsBody* a, PhysicsBody* b)
{
    return construct(a, b, 0.0f, 0.0f);
}

bool PhysicsJointRotaryLimit::_initJoint()
{
    do
    {
        auto joint = cpRotaryLimitJointNew(_bodyA->getBody(),
                                                    _bodyB->getBody(),
                                                    PhysicsHelper::float2cpfloat(_min),
                                                    PhysicsHelper::float2cpfloat(_max));
        
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointRotaryLimit::getMin() const
{
    return PhysicsHelper::cpfloat2float(cpRotaryLimitJointGetMin(_joints.front()));
}

void PhysicsJointRotaryLimit::setMin(float min)
{
    cpRotaryLimitJointSetMin(_joints.front(), PhysicsHelper::float2cpfloat(min));
}

float PhysicsJointRotaryLimit::getMax() const
{
    return PhysicsHelper::cpfloat2float(cpRotaryLimitJointGetMax(_joints.front()));
}

void PhysicsJointRotaryLimit::setMax(float max)
{
    cpRotaryLimitJointSetMax(_joints.front(), PhysicsHelper::float2cpfloat(max));
}

PhysicsJointRatchet* PhysicsJointRatchet::construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratchet)
{
    auto joint = new (std::nothrow) PhysicsJointRatchet();
    
    if (joint && joint->init(a, b))
    {
        joint->_phase = phase;
        joint->_ratchet = ratchet;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointRatchet::_initJoint()
{
    do
    {
        auto joint = cpRatchetJointNew(_bodyA->getBody(),
                                                _bodyB->getBody(),
                                                PhysicsHelper::float2cpfloat(_phase),
                                                PhysicsHelper::cpfloat2float(_ratchet));
        
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointRatchet::getAngle() const
{
    return PhysicsHelper::cpfloat2float(cpRatchetJointGetAngle(_joints.front()));
}

void PhysicsJointRatchet::setAngle(float angle)
{
    cpRatchetJointSetAngle(_joints.front(), PhysicsHelper::float2cpfloat(angle));
}

float PhysicsJointRatchet::getPhase() const
{
    return PhysicsHelper::cpfloat2float(cpRatchetJointGetPhase(_joints.front()));
}

void PhysicsJointRatchet::setPhase(float phase)
{
    cpRatchetJointSetPhase(_joints.front(), PhysicsHelper::float2cpfloat(phase));
}

float PhysicsJointRatchet::getRatchet() const
{
    return PhysicsHelper::cpfloat2float(cpRatchetJointGetRatchet(_joints.front()));
}

void PhysicsJointRatchet::setRatchet(float ratchet)
{
    cpRatchetJointSetRatchet(_joints.front(), PhysicsHelper::float2cpfloat(ratchet));
}

PhysicsJointGear* PhysicsJointGear::construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratio)
{
    auto joint = new (std::nothrow) PhysicsJointGear();
    
    if (joint && joint->init(a, b))
    {
        joint->_phase = phase;
        joint->_ratio = ratio;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointGear::_initJoint()
{
    do
    {
        auto joint = cpGearJointNew(_bodyA->getBody(),
                                             _bodyB->getBody(),
                                             PhysicsHelper::float2cpfloat(_phase),
                                             PhysicsHelper::float2cpfloat(_ratio));
        
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointGear::getPhase() const
{
    return PhysicsHelper::cpfloat2float(cpGearJointGetPhase(_joints.front()));
}

void PhysicsJointGear::setPhase(float phase)
{
    cpGearJointSetPhase(_joints.front(), PhysicsHelper::float2cpfloat(phase));
}

float PhysicsJointGear::getRatio() const
{
    return PhysicsHelper::cpfloat2float(cpGearJointGetRatio(_joints.front()));
}

void PhysicsJointGear::setRatio(float ratio)
{
    cpGearJointSetRatio(_joints.front(), PhysicsHelper::float2cpfloat(ratio));
}

PhysicsJointMotor* PhysicsJointMotor::construct(PhysicsBody* a, PhysicsBody* b, float rate)
{
    auto joint = new (std::nothrow) PhysicsJointMotor();
    
    if (joint && joint->init(a, b))
    {
        joint->_rate = rate;
        
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointMotor::_initJoint()
{
    do
    {
        auto joint = cpSimpleMotorNew(_bodyA->getBody(),
                                             _bodyB->getBody(),
                                             PhysicsHelper::float2cpfloat(_rate));
        
        CC_BREAK_IF(joint == nullptr);
        _joints.push_back(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointMotor::getRate() const
{
    return PhysicsHelper::cpfloat2float(cpSimpleMotorGetRate(_joints.front()));
}

void PhysicsJointMotor::setRate(float rate)
{
    cpSimpleMotorSetRate(_joints.front(), PhysicsHelper::float2cpfloat(rate));
}

NS_CC_END
#endif // CC_USE_PHYSICS
