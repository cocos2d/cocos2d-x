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

#include "CCPhysicsShapeInfo.h"
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include <algorithm>
NS_CC_BEGIN

std::map<cpShape*, PhysicsShapeInfo*> PhysicsShapeInfo::map;

PhysicsShapeInfo::PhysicsShapeInfo(PhysicsShape* shape)
: shape(shape)
{
}

PhysicsShapeInfo::~PhysicsShapeInfo()
{
    for (auto it = shapes.begin(); it != shapes.end(); it++)
    {
        cpShapeFree(*it);
        
        auto mit = map.find(*it);
        if (mit != map.end()) map.erase(*it);
    }
}

void PhysicsShapeInfo::add(cpShape* shape)
{
    if (shape == nullptr) return;
    
    shapes.push_back(shape);
    map.insert(std::pair<cpShape*, PhysicsShapeInfo*>(shape, this));
}

void PhysicsShapeInfo::remove(cpShape* shape)
{
    if (shape == nullptr) return;
    
    auto it = std::find(shapes.begin(), shapes.end(), shape);
    if (it != shapes.end())
    {
        shapes.erase(it);
        
        auto mit = map.find(shape);
        if (mit != map.end()) map.erase(mit);
    }
}

NS_CC_END
#endif // CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK
