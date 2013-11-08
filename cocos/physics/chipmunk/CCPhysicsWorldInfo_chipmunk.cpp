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
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
NS_CC_BEGIN

#define PHYSICS_WORLD_INFO_FUNCTION_IMPLEMENTS(name, type) \
void PhysicsWorldInfo::add##name(cp##type* data) \
{ \
    if (!cpSpaceContains##type(_space, data)) cpSpaceAdd##type(_space, data); \
} \
\
void PhysicsWorldInfo::remove##name(cp##type* data) \
{ \
    if (cpSpaceContains##type(_space, data)) cpSpaceRemove##type(_space, data); \
} \

PHYSICS_WORLD_INFO_FUNCTION_IMPLEMENTS(Shape, Shape)
PHYSICS_WORLD_INFO_FUNCTION_IMPLEMENTS(Body, Body)
PHYSICS_WORLD_INFO_FUNCTION_IMPLEMENTS(Joint, Constraint)

PhysicsWorldInfo::PhysicsWorldInfo()
{
    _space = cpSpaceNew();
}

PhysicsWorldInfo::~PhysicsWorldInfo()
{
    cpSpaceFree(_space);
}

NS_CC_END
#endif // CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK
