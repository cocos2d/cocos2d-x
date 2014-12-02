/*
 *
 * Copyright (c) 2014 Nguyen Thai Duong
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __cocos2d_libs__CCBPhysicsJoints__
#define __cocos2d_libs__CCBPhysicsJoints__

#include <iostream>
#include "chipmunk.h"
#include "CCPhysicsHelper_chipmunk.h"
#include "CCPhysicsJointInfo_chipmunk.h"
#include "CCPhysicsBodyInfo_chipmunk.h"
#include "CCBPhysicsBody.h"

namespace spritebuilder {
    
    //because _info field is a protected field in PhysicsJoint class
    class HackPhysicsJoint : public cocos2d::PhysicsJoint {
    public:
        cocos2d::PhysicsJointInfo* getPhysicsJointInfo() {
            return _info;
        }

    };
    
    class ExternalJointsInfo {
    public:
        virtual ~ExternalJointsInfo() {}
        virtual float getBreakingForce() {return m_nBreakingForce;}
        virtual void  setBreakingForce(float breakingForce) {m_nBreakingForce = breakingForce;}
    protected:
        float m_nBreakingForce;
    };
    
    class CCBPhysicsJointMotor : public cocos2d::PhysicsJointMotor, public virtual ExternalJointsInfo {
    public:
        static CCBPhysicsJointMotor* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, float rate) {
            CCBPhysicsJointMotor* joint = new CCBPhysicsJointMotor();
            
            if (joint && joint->init(a, b, rate))
            {
                return joint;
            }
            
            CC_SAFE_DELETE(joint);
            return nullptr;
        }
    };
    
    class CCBPhysicsJointRotarySpring : public cocos2d::PhysicsJointRotarySpring, public virtual ExternalJointsInfo {
    public:
        static CCBPhysicsJointRotarySpring* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, float stiffness, float damping) {
            CCBPhysicsJointRotarySpring* joint = new CCBPhysicsJointRotarySpring();
            
            if (joint && joint->init(a, b, stiffness, damping))
            {
                return joint;
            }
            
            CC_SAFE_DELETE(joint);
            return nullptr;
        }
        
    };
    
    class CCBPhysicsJointRotaryLimit : public cocos2d::PhysicsJointRotaryLimit, public virtual ExternalJointsInfo {
    public:
        static CCBPhysicsJointRotaryLimit* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, float min, float max) {
            CCBPhysicsJointRotaryLimit* joint = new CCBPhysicsJointRotaryLimit();
            
            if (joint && joint->init(a, b, min, max))
            {
                return joint;
            }
            
            CC_SAFE_DELETE(joint);
            return nullptr;

        }
        static CCBPhysicsJointRotaryLimit* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b) {
             return construct(a, b, 0.0f, 0.0f);
        }
    };
    
    class CCBPhysicsJointSpring : public cocos2d::PhysicsJointSpring, public virtual ExternalJointsInfo {
    public:
        static CCBPhysicsJointSpring* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, const cocos2d::Point& anchr1, const cocos2d::Point& anchr2, float stiffness, float damping) {
            
            CCBPhysicsJointSpring* joint = new CCBPhysicsJointSpring();
            
            if (joint && joint->init(a, b, anchr1, anchr2, stiffness, damping))
            {
                return joint;
            }
            
            CC_SAFE_DELETE(joint);
            return nullptr;

        }
    };
    
    class CCBPhysicsJointRatchet : public cocos2d::PhysicsJointRatchet, public virtual ExternalJointsInfo {
    public:
        static CCBPhysicsJointRatchet* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, float phase, float ratchet) {
            CCBPhysicsJointRatchet* joint = new CCBPhysicsJointRatchet();
            
            if (joint && joint->init(a, b, phase, ratchet))
            {
                return joint;
            }
            
            CC_SAFE_DELETE(joint);
            return nullptr;
        }
    };
    
    class CCBPhysicsJointLimit : public cocos2d::PhysicsJointLimit, public virtual ExternalJointsInfo {
    public:
        static CCBPhysicsJointLimit* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, const cocos2d::Point& anchr1, const cocos2d::Point& anchr2) {
             return construct(a, b, anchr1, anchr2, 0, b->local2World(anchr1).getDistance(a->local2World(anchr2)));
        }
        static CCBPhysicsJointLimit* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, const cocos2d::Point& anchr1, const cocos2d::Point& anchr2, float min, float max) {
            CCBPhysicsJointLimit* joint = new CCBPhysicsJointLimit();
            
            if (joint && joint->init(a, b, anchr1, anchr2, min, max))
            {
                return joint;
            }
            
            CC_SAFE_DELETE(joint);
            return nullptr;
        }
    };
    
    class CCBPhysicsJointDistance : public cocos2d::PhysicsJointDistance, public virtual ExternalJointsInfo {
    public:
        static CCBPhysicsJointDistance* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, const cocos2d::Point& anchr1, const cocos2d::Point& anchr2, float min, float max) {
            CCBPhysicsJointDistance* joint = new CCBPhysicsJointDistance();
        
            if (joint && joint->init(a, b, anchr1, anchr2, min, max))
            {
                return joint;
            }
        
            CC_SAFE_DELETE(joint);
            return nullptr;
        }
        static CCBPhysicsJointDistance* construct(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, const cocos2d::Point& anchr1, const cocos2d::Point& anchr2) {
            CCBPhysicsJointDistance* joint = new CCBPhysicsJointDistance();
            
            if (joint && joint->init(a, b, anchr1, anchr2))
            {
                return joint;
            }
            
            CC_SAFE_DELETE(joint);
            return nullptr;
        }
        /*
        float getDistance() const {
            if (m_bHasMinMax) {
                
            } else
                return cocos2d::PhysicsJointDistance::getDistance();
        }
        void setDistance(float distance) {
            if (m_bHasMinMax) {
                
            } else
                return cocos2d::PhysicsJointDistance::setDistance(distance);
        }*/
    protected:
        bool init(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, const cocos2d::Point& anchr1, const cocos2d::Point& anchr2)
        {
            do
            {
                CC_BREAK_IF(!PhysicsJoint::init(a, b));
                
                cpConstraint* joint = cpPinJointNew(getBodyInfo(a)->getBody(),
                                                    getBodyInfo(b)->getBody(),
                                                    cocos2d::PhysicsHelper::point2cpv(anchr1),
                                                    cocos2d::PhysicsHelper::point2cpv(anchr2));
                
                CC_BREAK_IF(joint == nullptr);
                
                _info->add(joint);
                m_bHasMinMax = false;
                return true;
            } while (false);
            
            return false;
        }
        bool init(cocos2d::PhysicsBody* a, cocos2d::PhysicsBody* b, const cocos2d::Point& anchr1, const cocos2d::Point& anchr2, float min, float max) {
            do
            {
                CC_BREAK_IF(!PhysicsJoint::init(a, b));


                cpConstraint* joint = cpSlideJointNew(getBodyInfo(a)->getBody(),
                                                      getBodyInfo(b)->getBody(),
                                                      cocos2d::PhysicsHelper::point2cpv(anchr1),
                                                      cocos2d::PhysicsHelper::point2cpv(anchr2),
                                                      min,
                                                      max
                                                      );
                
                
                CC_BREAK_IF(joint == nullptr);
                
                _info->add(joint);
                m_bHasMinMax = true;
                return true;
            } while (false);
            
            return false;

        }
    protected:
        bool    m_bHasMinMax;
    };
}

#endif /* defined(__cocos2d_libs__CCBPhysicsJoints__) */
