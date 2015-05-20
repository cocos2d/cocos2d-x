/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "navmesh/CCNavMeshObstacle.h"
#if CC_USE_NAVMESH

#include "navmesh/CCNavMesh.h"
#include "2d/CCNode.h"
#include "2d/CCScene.h"
#include "recast/DetourTileCache/DetourTileCache.h"

NS_CC_BEGIN

NavMeshObstacle* NavMeshObstacle::create(const Vec3 &position, float radius, float height)
{
    auto ref = new (std::nothrow) NavMeshObstacle();
    if (ref && ref->init(position, radius, height))
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}

std::string& NavMeshObstacle::getNavMeshObstacleComponentName()
{
    static std::string comName = "___NavMeshObstacleComponent___";
    return comName;
}

NavMeshObstacle::NavMeshObstacle()
: _radius(0.0f)
, _height(0.0f)
, _needUpdateObstacle(true)
, _tileCache(nullptr)
, _obstacleID(-1)
, _syncFlag(NODE_AND_NODE)
{

}

cocos2d::NavMeshObstacle::~NavMeshObstacle()
{

}

bool NavMeshObstacle::init(const Vec3 &position, float radius, float height)
{
    _position = position;
    _radius = radius;
    _height = height;
    setName(getNavMeshObstacleComponentName());
    return true;
}

void cocos2d::NavMeshObstacle::removeFrom(dtTileCache *tileCache)
{
    _tileCache->removeObstacle(_obstacleID);
    _tileCache = nullptr;
    _obstacleID = -1;
}

void cocos2d::NavMeshObstacle::addTo(dtTileCache *tileCache)
{
    _tileCache = tileCache;
    _tileCache->addObstacle(&_position.x, _radius, _height, &_obstacleID);
}

void cocos2d::NavMeshObstacle::onExit()
{
    if (_obstacleID == -1) return;
    Component::onExit();
    auto scene = _owner->getScene();
    if (scene && scene->getNavMesh()){
        scene->getNavMesh()->removeNavMeshObstacle(this);
    }
}

void cocos2d::NavMeshObstacle::onEnter()
{
    if (_obstacleID != -1) return;
    Component::onEnter();
    auto scene = _owner->getScene();
    if (scene && scene->getNavMesh()){
        scene->getNavMesh()->addNavMeshObstacle(this);
    }
    _owner->setPosition3D(_position);
}

void cocos2d::NavMeshObstacle::postUpdate(float delta)
{
    if ((_syncFlag & OBSTACLE_TO_NODE) != 0)
        syncToNode();
}

void cocos2d::NavMeshObstacle::preUpdate(float delta)
{
    if ((_syncFlag & NODE_TO_OBSTACLE) != 0)
        syncToObstacle();

    if (_needUpdateObstacle && _tileCache){
        _tileCache->removeObstacle(_obstacleID);
        Vec3 worldPos = _position;
        if (_owner->getParent())
            _owner->getParent()->getNodeToWorldTransform().transformPoint(_position, &worldPos);
        _tileCache->addObstacle(&worldPos.x, _radius, _height, &_obstacleID);
        _needUpdateObstacle = false;
    }
}

void NavMeshObstacle::syncToNode()
{
    if (_tileCache && _owner->getPosition3D() != _position){
        _owner->setPosition3D(_position);
    }
}

void NavMeshObstacle::syncToObstacle()
{
    setPosition(_owner->getPosition3D());
}

void NavMeshObstacle::setPosition(const Vec3 &position)
{
    if (_position == position) return;
    _position = position;
    _needUpdateObstacle = true;
}

NS_CC_END

#endif //CC_USE_NAVMESH
