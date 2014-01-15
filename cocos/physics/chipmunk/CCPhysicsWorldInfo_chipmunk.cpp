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

#include "CCPhysicsWorldInfo_chipmunk.h"
#if CC_USE_PHYSICS
#include "CCPhysicsHelper_chipmunk.h"
#include "CCPhysicsBodyInfo_chipmunk.h"
#include "CCPhysicsShapeInfo_chipmunk.h"
#include "CCPhysicsJointInfo_chipmunk.h"
NS_CC_BEGIN

PhysicsWorldInfo::PhysicsWorldInfo()
{
    _space = cpSpaceNew();
}

PhysicsWorldInfo::~PhysicsWorldInfo()
{
    cpSpaceFree(_space);
}

void PhysicsWorldInfo::setGravity(const Vect& gravity)
{
    cpSpaceSetGravity(_space, PhysicsHelper::point2cpv(gravity));
}

void PhysicsWorldInfo::addBody(PhysicsBodyInfo& body)
{
    if (!cpSpaceContainsBody(_space, body.getBody()))
    {
        cpSpaceAddBody(_space, body.getBody());
    }
}

void PhysicsWorldInfo::removeBody(PhysicsBodyInfo& body)
{
    if (cpSpaceContainsBody(_space, body.getBody()))
    {
        cpSpaceRemoveBody(_space, body.getBody());
    }
}

void PhysicsWorldInfo::addShape(PhysicsShapeInfo& shape)
{
    for (auto cps : shape.getShapes())
    {
        cpSpaceAddShape(_space, cps);
    }
}

void PhysicsWorldInfo::removeShape(PhysicsShapeInfo& shape)
{
    for (auto cps : shape.getShapes())
    {
        if (cpSpaceContainsShape(_space, cps))
        {
            cpSpaceRemoveShape(_space, cps);
        }
    }
}

void PhysicsWorldInfo::addJoint(PhysicsJointInfo& joint)
{
    for (auto subjoint : joint.getJoints())
    {
        cpSpaceAddConstraint(_space, subjoint);
    }
}

void PhysicsWorldInfo::removeJoint(PhysicsJointInfo& joint)
{
    for (auto subjoint : joint.getJoints())
    {
        cpSpaceRemoveConstraint(_space, subjoint);
    }
}

NS_CC_END
#endif // CC_USE_PHYSICS
