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

#ifndef __CCPHYSICS_HELPER_BOX2D_H__
#define __CCPHYSICS_HELPER_BOX2D_H__

#include "../CCPhysicsSetting.h"
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)
#include "Box2D.h"
#include "CCPlatformMacros.h"
#include "CCGeometry.h"

NS_CC_BEGIN

class PhysicsHelper
{
public:
    static b2Vec2 point2Vec2(const Point& point) { return b2Vec2(point.x, point.y); }
    static Point vec22Point(const b2Vec2& vec) { return Point(vec.x, vec.y); }
};

NS_CC_END

#endif // CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D
#endif // __CCPHYSICS_HELPER_BOX2D_H__
