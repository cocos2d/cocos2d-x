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

#include "CCPhysicsJointInfo_chipmunk.h"
#if CC_USE_PHYSICS
#include <algorithm>
#include <unordered_map>
#include "chipmunk.h"

NS_CC_BEGIN

std::unordered_map<cpConstraint*, PhysicsJointInfo*> PhysicsJointInfo::_map;

PhysicsJointInfo::PhysicsJointInfo(PhysicsJoint* joint)
: _joint(joint)
{
}

PhysicsJointInfo::~PhysicsJointInfo()
{
    for (cpConstraint* joint : _joints)
    {
        cpConstraintFree(joint);
    }
}

void PhysicsJointInfo::add(cpConstraint* joint)
{
    if (joint == nullptr) return;

    _joints.push_back(joint);
    _map.insert(std::pair<cpConstraint*, PhysicsJointInfo*>(joint, this));
}

void PhysicsJointInfo::remove(cpConstraint* joint)
{
    if (joint == nullptr) return;
    
    auto it = std::find(_joints.begin(), _joints.end(), joint);
    if (it != _joints.end())
    {
        _joints.erase(it);
        
        auto mit = _map.find(joint);
        if (mit != _map.end()) _map.erase(mit);
        
        cpConstraintFree(joint);
    }
}

void PhysicsJointInfo::removeAll()
{
    for (cpConstraint* joint : _joints)
    {
        auto mit = _map.find(joint);
        if (mit != _map.end()) _map.erase(mit);
        cpConstraintFree(joint);
    }
    
    _joints.clear();
}

NS_CC_END
#endif // CC_USE_PHYSICS
