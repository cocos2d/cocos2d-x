/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "CCPhysicsJointInfo.h"
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include <algorithm>
NS_CC_BEGIN

std::map<cpConstraint*, PhysicsJointInfo*> PhysicsJointInfo::map;

PhysicsJointInfo::PhysicsJointInfo(PhysicsJoint* joint)
: joint(joint)
{
}

PhysicsJointInfo::~PhysicsJointInfo()
{
    for (cpConstraint* joint : joints)
    {
        cpConstraintFree(joint);
    }
}

void PhysicsJointInfo::add(cpConstraint* joint)
{
    if (joint == nullptr) return;

    joints.push_back(joint);
    map.insert(std::pair<cpConstraint*, PhysicsJointInfo*>(joint, this));
}

void PhysicsJointInfo::remove(cpConstraint* joint)
{
    if (joint == nullptr) return;
    
    auto it = std::find(joints.begin(), joints.end(), joint);
    if (it != joints.end())
    {
        joints.erase(it);
        
        auto mit = map.find(joint);
        if (mit != map.end()) map.erase(mit);
        
        cpConstraintFree(joint);
    }
}

void PhysicsJointInfo::removeAll()
{
    for (cpConstraint* joint : joints)
    {
        auto mit = map.find(joint);
        if (mit != map.end()) map.erase(mit);
        cpConstraintFree(joint);
    }
    
    joints.clear();
}

NS_CC_END
#endif // CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK
