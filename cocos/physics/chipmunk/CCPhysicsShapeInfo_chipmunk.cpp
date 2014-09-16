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

#include "CCPhysicsShapeInfo_chipmunk.h"
#if CC_USE_PHYSICS
#include <algorithm>
#include <unordered_map>
#include "chipmunk.h"

NS_CC_BEGIN

std::unordered_map<cpShape*, PhysicsShapeInfo*> PhysicsShapeInfo::_map;
cpBody* PhysicsShapeInfo::_sharedBody = nullptr;

PhysicsShapeInfo::PhysicsShapeInfo(PhysicsShape* shape)
: _shape(shape)
, _group(CP_NO_GROUP)
{
    if (_sharedBody == nullptr)
    {
        _sharedBody = cpBodyNewStatic();
    }
    
    _body = _sharedBody;
}

PhysicsShapeInfo::~PhysicsShapeInfo()
{
    for (auto shape : _shapes)
    {
        auto it = _map.find(shape);
        if (it != _map.end()) _map.erase(shape);
        
        cpShapeFree(shape);
    }
}

void PhysicsShapeInfo::setGroup(cpGroup group)
{
    this->_group = group;
    
    for (cpShape* shape : _shapes)
    {
        cpShapeSetGroup(shape, group);
    }
}

void PhysicsShapeInfo::setBody(cpBody* body)
{
    if (this->_body != body)
    {
        this->_body = body;
        for (cpShape* shape : _shapes)
        {
            cpShapeSetBody(shape, body == nullptr ? _sharedBody : body);
        }
    }
}

void PhysicsShapeInfo::add(cpShape* shape)
{
    if (shape == nullptr) return;
    
    cpShapeSetGroup(shape, _group);
    _shapes.push_back(shape);
    _map.insert(std::pair<cpShape*, PhysicsShapeInfo*>(shape, this));
}

void PhysicsShapeInfo::remove(cpShape* shape)
{
    if (shape == nullptr) return;
    
    auto it = std::find(_shapes.begin(), _shapes.end(), shape);
    if (it != _shapes.end())
    {
        _shapes.erase(it);
        
        auto mit = _map.find(shape);
        if (mit != _map.end()) _map.erase(mit);
        
        cpShapeFree(shape);
    }
}

void PhysicsShapeInfo::removeAll()
{
    for (cpShape* shape : _shapes)
    {
        auto mit = _map.find(shape);
        if (mit != _map.end()) _map.erase(mit);
        cpShapeFree(shape);
    }
    
    _shapes.clear();
}

NS_CC_END
#endif // CC_USE_PHYSICS
