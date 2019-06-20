/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "chipmunk/chipmunk.h"

#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsWorld.h"
#include "physics/CCPhysicsHelper.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

template<typename T>
class Optional {

public:
    Optional() {}
    Optional(T d) :_isSet(true), _data(d) {}
    Optional(const Optional &t) : _isSet(t._isSet), _data(t._data) {}

    //bool isNull()       const { return !_isSet; }
    //bool isDefineded()  const { return _isSet; }
    //bool isEmpty()      const { return !_isSet; }

    T    get()          const { CCASSERT(_isSet, "data should be set!"); return _data; }
    void set(T d)             { _isSet = true; _data = d; }

private:
    bool _isSet = false;
    T _data;
};

class WriteCache {
public:
    Optional<Vec2>  _grooveA;
    Optional<Vec2>  _grooveB;
    Optional<Vec2>  _anchr1;
    Optional<Vec2>  _anchr2;
    Optional<float> _min;
    Optional<float> _max;
    Optional<float> _distance;
    Optional<float> _restLength;
    Optional<float> _restAngle;
    Optional<float> _stiffness;
    Optional<float> _damping;
    Optional<float> _angle;
    Optional<float> _phase;
    Optional<float> _ratchet;
    Optional<float> _ratio;
    Optional<float> _rate;
};

#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
#define LIKELY(x)   (__builtin_expect((x), 1))
#define UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define LIKELY(x)   (x)
#define UNLIKELY(x) (x)
#endif


#define CC_PJOINT_CACHE_READ(field)         \
    do {                                    \
    if(UNLIKELY(_initDirty))                \
    {                                       \
        return _writeCache->field.get();    \
    }                                       \
    }while(0)



#define CC_PJOINT_CACHE_WRITE2(field, method, arg, convertedArg)    \
    do {                                                            \
    if(UNLIKELY(_initDirty))                                        \
    {                                                               \
        _writeCache->field.set(arg);                                \
        delay([this, arg]() {                                       \
            method(_cpConstraints.front(), convertedArg);           \
        });                                                         \
    }                                                               \
    else                                                            \
    {                                                               \
        method(_cpConstraints.front(), convertedArg);               \
    }                                                               \
    }while(0)

#define CC_PJOINT_CACHE_WRITE(field, method, arg)   \
    CC_PJOINT_CACHE_WRITE2(field, method, arg, arg)

PhysicsJoint::PhysicsJoint()
: _bodyA(nullptr)
, _bodyB(nullptr)
, _world(nullptr)
, _enable(false)
, _collisionEnable(true)
, _destroyMark(false)
, _tag(0)
, _maxForce(PHYSICS_INFINITY)
, _initDirty(true)
{
    _writeCache = new WriteCache();
}

PhysicsJoint::~PhysicsJoint()
{
    // reset the shapes collision group
    setCollisionEnable(true);

    for (cpConstraint* joint : _cpConstraints)
    {
        cpConstraintFree(joint);
    }
    _cpConstraints.clear();

    delete _writeCache;
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
        ret = createConstraints();
        CC_BREAK_IF(!ret);

        for (auto subjoint : _cpConstraints)
        {
            cpConstraintSetMaxForce(subjoint, _maxForce);
            cpConstraintSetErrorBias(subjoint, cpfpow(1.0f - 0.15f, 60.0f));
            cpSpaceAddConstraint(_world->_cpSpace, subjoint);
        }
        _initDirty = false;
        ret = true;
    }

    return ret;
}

void PhysicsJoint::flushDelayTasks()
{
    for (const auto& tsk : _delayTasks)
    {
        tsk();
    }
    _delayTasks.clear();
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
            }
            else
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
    if(_initDirty)
    {
        delay([this, force]() {
            _maxForce = force;
            for (auto joint : _cpConstraints)
            {
                cpConstraintSetMaxForce(joint, force);
            }
        });
    }
    else
    {
        _maxForce = force;
        for (auto joint : _cpConstraints)
        {
            cpConstraintSetMaxForce(joint, force);
        }
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

bool PhysicsJointFixed::createConstraints()
{
    do
    {
        _bodyA->getNode()->setPosition(_anchr);
        _bodyB->getNode()->setPosition(_anchr);

        // add a pivot joint to fixed two body together
        auto joint = cpPivotJointNew(_bodyA->getCPBody(), _bodyB->getCPBody(),
            PhysicsHelper::point2cpv(_anchr));
        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        // add a gear joint to make two body have the same rotation.
        joint = cpGearJointNew(_bodyA->getCPBody(), _bodyB->getCPBody(), 0, 1);
        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

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

bool PhysicsJointPin::createConstraints()
{
    do
    {
        cpConstraint* joint = nullptr;
        if (_useSpecificAnchr)
        {
            joint = cpPivotJointNew2(_bodyA->getCPBody(), _bodyB->getCPBody(),
                PhysicsHelper::point2cpv(_anchr1), PhysicsHelper::point2cpv(_anchr2));
        }
        else
        {
            joint = cpPivotJointNew(_bodyA->getCPBody(), _bodyB->getCPBody(),
                PhysicsHelper::point2cpv(_anchr1));
        }

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

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

bool PhysicsJointLimit::createConstraints()
{
    do
    {
        auto joint = cpSlideJointNew(_bodyA->getCPBody(), _bodyB->getCPBody(),
            PhysicsHelper::point2cpv(_anchr1),
            PhysicsHelper::point2cpv(_anchr2),
            _min,
            _max);

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

float PhysicsJointLimit::getMin() const
{
    CC_PJOINT_CACHE_READ(_min);
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMin(_cpConstraints.front()));
}

void PhysicsJointLimit::setMin(float min)
{
    CC_PJOINT_CACHE_WRITE(_min, cpSlideJointSetMin, min);
}

float PhysicsJointLimit::getMax() const
{
    CC_PJOINT_CACHE_READ(_max);
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMax(_cpConstraints.front()));
}

void PhysicsJointLimit::setMax(float max)
{
    CC_PJOINT_CACHE_WRITE(_max, cpSlideJointSetMax, max);
}

Vec2 PhysicsJointLimit::getAnchr1() const
{
    CC_PJOINT_CACHE_READ(_anchr1);
    return PhysicsHelper::cpv2point(cpSlideJointGetAnchorA(_cpConstraints.front()));
}

void PhysicsJointLimit::setAnchr1(const Vec2& anchr)
{
    CC_PJOINT_CACHE_WRITE2(_anchr1, cpSlideJointSetAnchorA, anchr, PhysicsHelper::point2cpv(anchr));
}

Vec2 PhysicsJointLimit::getAnchr2() const
{
    CC_PJOINT_CACHE_READ(_anchr2);
    return PhysicsHelper::cpv2point(cpSlideJointGetAnchorB(_cpConstraints.front()));
}

void PhysicsJointLimit::setAnchr2(const Vec2& anchr)
{
    CC_PJOINT_CACHE_WRITE2(_anchr2, cpSlideJointSetAnchorB, anchr, PhysicsHelper::point2cpv(anchr));
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

bool PhysicsJointDistance::createConstraints()
{
    do
    {
        auto joint = cpPinJointNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            PhysicsHelper::point2cpv(_anchr1),
            PhysicsHelper::point2cpv(_anchr2));
        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

float PhysicsJointDistance::getDistance() const
{
    CC_PJOINT_CACHE_READ(_distance);
    return PhysicsHelper::cpfloat2float(cpPinJointGetDist(_cpConstraints.front()));
}

void PhysicsJointDistance::setDistance(float distance)
{
    CC_PJOINT_CACHE_WRITE(_distance, cpPinJointSetDist, distance);
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

bool PhysicsJointSpring::createConstraints()
{
    do {
        auto joint = cpDampedSpringNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            PhysicsHelper::point2cpv(_anchr1),
            PhysicsHelper::point2cpv(_anchr2),
            _bodyB->local2World(_anchr1).getDistance(_bodyA->local2World(_anchr2)),
            _stiffness,
            _damping);

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

Vec2 PhysicsJointSpring::getAnchr1() const
{
    CC_PJOINT_CACHE_READ(_anchr1);
    return PhysicsHelper::cpv2point(cpDampedSpringGetAnchorA(_cpConstraints.front()));
}

void PhysicsJointSpring::setAnchr1(const Vec2& anchr)
{
    CC_PJOINT_CACHE_WRITE2(_anchr1, cpDampedSpringSetAnchorA, anchr, PhysicsHelper::point2cpv(anchr));
}

Vec2 PhysicsJointSpring::getAnchr2() const
{
    CC_PJOINT_CACHE_READ(_anchr2);
    return PhysicsHelper::cpv2point(cpDampedSpringGetAnchorB(_cpConstraints.front()));
}

void PhysicsJointSpring::setAnchr2(const Vec2& anchr)
{
    CC_PJOINT_CACHE_WRITE2(_anchr2, cpDampedSpringSetAnchorB, anchr, PhysicsHelper::point2cpv(anchr));
}

float PhysicsJointSpring::getRestLength() const
{
    CC_PJOINT_CACHE_READ(_restLength);
    return PhysicsHelper::cpfloat2float(cpDampedSpringGetRestLength(_cpConstraints.front()));
}

void PhysicsJointSpring::setRestLength(float restLength)
{
    CC_PJOINT_CACHE_WRITE(_restLength, cpDampedSpringSetRestLength, restLength);
}

float PhysicsJointSpring::getStiffness() const
{
    CC_PJOINT_CACHE_READ(_stiffness);
    return PhysicsHelper::cpfloat2float(cpDampedSpringGetStiffness(_cpConstraints.front()));
}

void PhysicsJointSpring::setStiffness(float stiffness)
{
    CC_PJOINT_CACHE_WRITE(_stiffness, cpDampedSpringSetStiffness, stiffness);
}

float PhysicsJointSpring::getDamping() const
{
    CC_PJOINT_CACHE_READ(_damping);
    return PhysicsHelper::cpfloat2float(cpDampedSpringGetDamping(_cpConstraints.front()));
}

void PhysicsJointSpring::setDamping(float damping)
{
    CC_PJOINT_CACHE_WRITE(_damping, cpDampedSpringSetDamping, damping);
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

bool PhysicsJointGroove::createConstraints()
{
    do {
        auto joint = cpGrooveJointNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            PhysicsHelper::point2cpv(_grooveA),
            PhysicsHelper::point2cpv(_grooveB),
            PhysicsHelper::point2cpv(_anchr2));

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

Vec2 PhysicsJointGroove::getGrooveA() const
{
    CC_PJOINT_CACHE_READ(_grooveA);
    return PhysicsHelper::cpv2point(cpGrooveJointGetGrooveA(_cpConstraints.front()));
}

void PhysicsJointGroove::setGrooveA(const Vec2& grooveA)
{
    CC_PJOINT_CACHE_WRITE2(_grooveA, cpGrooveJointSetGrooveA, grooveA, PhysicsHelper::point2cpv(grooveA));
}

Vec2 PhysicsJointGroove::getGrooveB() const
{
    CC_PJOINT_CACHE_READ(_grooveB);
    return PhysicsHelper::cpv2point(cpGrooveJointGetGrooveB(_cpConstraints.front()));
}

void PhysicsJointGroove::setGrooveB(const Vec2& grooveB)
{
    CC_PJOINT_CACHE_WRITE2(_grooveB, cpGrooveJointSetGrooveB, grooveB, PhysicsHelper::point2cpv(grooveB));
}

Vec2 PhysicsJointGroove::getAnchr2() const
{
    CC_PJOINT_CACHE_READ(_anchr2);
    return PhysicsHelper::cpv2point(cpGrooveJointGetAnchorB(_cpConstraints.front()));
}

void PhysicsJointGroove::setAnchr2(const Vec2& anchr2)
{
    CC_PJOINT_CACHE_WRITE2(_anchr2, cpGrooveJointSetAnchorB, anchr2, PhysicsHelper::point2cpv(anchr2));
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

bool PhysicsJointRotarySpring::createConstraints()
{
    do {
        auto joint = cpDampedRotarySpringNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            _bodyB->getRotation() - _bodyA->getRotation(),
            _stiffness,
            _damping);

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

float PhysicsJointRotarySpring::getRestAngle() const
{
    CC_PJOINT_CACHE_READ(_restAngle);
    return PhysicsHelper::cpfloat2float(cpDampedRotarySpringGetRestAngle(_cpConstraints.front()));
}

void PhysicsJointRotarySpring::setRestAngle(float restAngle)
{
    CC_PJOINT_CACHE_WRITE(_restAngle, cpDampedRotarySpringSetRestAngle, restAngle);
}

float PhysicsJointRotarySpring::getStiffness() const
{
    CC_PJOINT_CACHE_READ(_stiffness);
    return PhysicsHelper::cpfloat2float(cpDampedRotarySpringGetStiffness(_cpConstraints.front()));
}

void PhysicsJointRotarySpring::setStiffness(float stiffness)
{
    CC_PJOINT_CACHE_WRITE(_stiffness, cpDampedRotarySpringSetStiffness, stiffness);
}

float PhysicsJointRotarySpring::getDamping() const
{
    CC_PJOINT_CACHE_READ(_damping);
    return PhysicsHelper::cpfloat2float(cpDampedRotarySpringGetDamping(_cpConstraints.front()));
}

void PhysicsJointRotarySpring::setDamping(float damping)
{
    CC_PJOINT_CACHE_WRITE(_damping, cpDampedRotarySpringSetDamping, damping);
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

bool PhysicsJointRotaryLimit::createConstraints()
{
    do
    {
        auto joint = cpRotaryLimitJointNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            _min,
            _max);

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

float PhysicsJointRotaryLimit::getMin() const
{
    CC_PJOINT_CACHE_READ(_min);
    return PhysicsHelper::cpfloat2float(cpRotaryLimitJointGetMin(_cpConstraints.front()));
}

void PhysicsJointRotaryLimit::setMin(float min)
{
    CC_PJOINT_CACHE_WRITE(_min, cpRotaryLimitJointSetMin, min);
}

float PhysicsJointRotaryLimit::getMax() const
{
    CC_PJOINT_CACHE_READ(_max);
    return PhysicsHelper::cpfloat2float(cpRotaryLimitJointGetMax(_cpConstraints.front()));
}

void PhysicsJointRotaryLimit::setMax(float max)
{
    CC_PJOINT_CACHE_WRITE(_max, cpRotaryLimitJointSetMax, max);
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

bool PhysicsJointRatchet::createConstraints()
{
    do
    {
        auto joint = cpRatchetJointNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            _phase,
            PhysicsHelper::cpfloat2float(_ratchet));

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

float PhysicsJointRatchet::getAngle() const
{
    CC_PJOINT_CACHE_READ(_angle);
    return PhysicsHelper::cpfloat2float(cpRatchetJointGetAngle(_cpConstraints.front()));
}

void PhysicsJointRatchet::setAngle(float angle)
{
    CC_PJOINT_CACHE_WRITE(_angle, cpRatchetJointSetAngle, angle);
}

float PhysicsJointRatchet::getPhase() const
{
    CC_PJOINT_CACHE_READ(_phase);
    return PhysicsHelper::cpfloat2float(cpRatchetJointGetPhase(_cpConstraints.front()));
}

void PhysicsJointRatchet::setPhase(float phase)
{
    CC_PJOINT_CACHE_WRITE(_phase, cpRatchetJointSetPhase, phase);
}

float PhysicsJointRatchet::getRatchet() const
{
    CC_PJOINT_CACHE_READ(_ratchet);
    return PhysicsHelper::cpfloat2float(cpRatchetJointGetRatchet(_cpConstraints.front()));
}

void PhysicsJointRatchet::setRatchet(float ratchet)
{
    CC_PJOINT_CACHE_WRITE(_ratchet, cpRatchetJointSetRatchet, ratchet);
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

bool PhysicsJointGear::createConstraints()
{
    do
    {
        auto joint = cpGearJointNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            _phase,
            _ratio);

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

float PhysicsJointGear::getPhase() const
{
    CC_PJOINT_CACHE_READ(_phase);
    return PhysicsHelper::cpfloat2float(cpGearJointGetPhase(_cpConstraints.front()));
}

void PhysicsJointGear::setPhase(float phase)
{
    CC_PJOINT_CACHE_WRITE(_phase, cpGearJointSetPhase, phase);
}

float PhysicsJointGear::getRatio() const
{
    CC_PJOINT_CACHE_READ(_ratio);
    return PhysicsHelper::cpfloat2float(cpGearJointGetRatio(_cpConstraints.front()));
}

void PhysicsJointGear::setRatio(float ratio)
{
    CC_PJOINT_CACHE_WRITE(_ratio, cpGearJointSetRatio, ratio);
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

bool PhysicsJointMotor::createConstraints()
{
    do
    {
        auto joint = cpSimpleMotorNew(_bodyA->getCPBody(),
            _bodyB->getCPBody(),
            _rate);

        CC_BREAK_IF(joint == nullptr);
        _cpConstraints.push_back(joint);

        return true;
    } while (false);

    return false;
}

float PhysicsJointMotor::getRate() const
{
    CC_PJOINT_CACHE_READ(_rate);
    return PhysicsHelper::cpfloat2float(cpSimpleMotorGetRate(_cpConstraints.front()));
}

void PhysicsJointMotor::setRate(float rate)
{
    CC_PJOINT_CACHE_WRITE(_rate, cpSimpleMotorSetRate, rate);
}

NS_CC_END
#endif // CC_USE_PHYSICS
