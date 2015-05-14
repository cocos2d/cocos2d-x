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
#include "navmesh/CCNavMeshAgent.h"
#include "navmesh/CCNavMesh.h"
#include "recast/DetourCrowd/DetourCrowd.h"
#include "2d/CCNode.h"
#include "2d/CCScene.h"
#include <algorithm>

NS_CC_BEGIN

NavMeshAgent* NavMeshAgent::create(const NavMeshAgentParam &param)
{
    auto ref = new (std::nothrow) NavMeshAgent();
    if (ref && ref->init(param))
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}

cocos2d::NavMeshAgent::NavMeshAgent()
    : _agentID(-1)
    , _needAutoOrientation(false)
    , _crowd(nullptr)
    , _needUpdateAgent(true)
    , _needMove(false)
    , _navMeshQuery(nullptr)
{

}

cocos2d::NavMeshAgent::~NavMeshAgent()
{

}

bool NavMeshAgent::init(const NavMeshAgentParam &param)
{
    _param = param;
    setName("___NavMeshAgentComponent___");
    return true;
}

void cocos2d::NavMeshAgent::setNavMeshQuery(dtNavMeshQuery *query)
{
    _navMeshQuery = query;
}

void cocos2d::NavMeshAgent::removeFrom(dtCrowd *crowed)
{
    crowed->removeAgent(_agentID);
    _crowd = nullptr;
}

void cocos2d::NavMeshAgent::addTo(dtCrowd *crowed)
{
    _crowd = crowed;
    dtCrowdAgentParams ap;
    convertTodtAgentParam(_param, ap);
    _agentID = _crowd->addAgent(&_param.position.x, &ap);
}

void cocos2d::NavMeshAgent::convertTodtAgentParam(const NavMeshAgentParam &inParam, dtCrowdAgentParams &outParam)
{
    memset(&outParam, 0, sizeof(outParam));
    outParam.collisionQueryRange = inParam.collisionQueryRange;
    outParam.height = inParam.height;
    outParam.maxAcceleration = inParam.maxAcceleration;
    outParam.maxSpeed = inParam.maxSpeed;
    outParam.obstacleAvoidanceType = inParam.obstacleAvoidanceType;
    outParam.pathOptimizationRange = inParam.pathOptimizationRange;
    outParam.queryFilterType = inParam.queryFilterType;
    outParam.radius = inParam.radius;
    outParam.separationWeight = inParam.separationWeight;
    outParam.updateFlags = inParam.updateFlags;
}

void cocos2d::NavMeshAgent::onExit()
{
    Component::onExit();

//    auto navMesh = _owner->getScene()->getNavMesh();
//    if (navMesh){
//        navMesh->removeNavMeshAgent(this);
//    }		
}

void cocos2d::NavMeshAgent::onEnter()
{
    Component::onEnter();

//    auto navMesh = _owner->getScene()->getNavMesh();
//    if (navMesh){
//        navMesh->addNavMeshAgent(this);
//    }
}

cocos2d::Vec3 NavMeshAgent::getPosition() const
{
    return _param.position;
}

float NavMeshAgent::getMaxSpeed() const
{
    return _param.maxSpeed;
}

void NavMeshAgent::setMaxSpeed(float maxSpeed)
{
    _param.maxSpeed;
    _needUpdateAgent = true;
}

float NavMeshAgent::getMaxAcceleration() const
{
    return _param.maxAcceleration;
}

void NavMeshAgent::setMaxAcceleration(float maxAcceleration)
{
    _param.maxAcceleration = maxAcceleration;
    _needUpdateAgent = true;
}

float NavMeshAgent::getHeight() const
{
    return _param.height;
}

void NavMeshAgent::setHeight(float height)
{
    _param.height = height;
    _needUpdateAgent = true;
}

float NavMeshAgent::getRadius() const
{
    return _param.radius;
}

void NavMeshAgent::setRadius(float radius)
{
    _param.radius = radius;
    _needUpdateAgent = true;
}

void NavMeshAgent::move(const Vec3 &destination, const Vec3 &rotRefAxes, bool needAutoOrientation)
{
    _destination = destination;
    _needMove = true;
}

void cocos2d::NavMeshAgent::preUpdate(float delta)
{
    syncToAgent();

    if (_needUpdateAgent && _crowd){
        dtCrowdAgentParams ap;
        convertTodtAgentParam(_param, ap);
        _crowd->updateAgentParameters(_agentID, &ap);
        _needUpdateAgent = false;
    }

    if (_needMove && _crowd && _navMeshQuery){
        dtPolyRef pRef = 0;
        float nearestPos[3];
        _navMeshQuery->findNearestPoly(&_destination.x, _crowd->getQueryExtents(), _crowd->getFilter(0), &pRef, nearestPos);
        _crowd->requestMoveTarget(_agentID, pRef, nearestPos);
        _needMove = false;
    }
}

void cocos2d::NavMeshAgent::postUpdate(float delta)
{
    syncToNode();
}

void cocos2d::NavMeshAgent::syncToNode()
{
    const dtCrowdAgent *agent = nullptr;
    if (_crowd){
        agent = _crowd->getAgent(_agentID);
    }

    if (agent){
        _owner->setPosition3D(Vec3(agent->npos[0], agent->npos[1], agent->npos[2]));
        if (_needAutoOrientation){
            if (agent->vel[0] != 0.0f || agent->vel[1] != 0.0f || agent->vel[2] != 0.0f){
                Vec3 axes(_rotRefAxes);
                axes.normalize();
                Vec3 dir(agent->vel[0], agent->vel[1], agent->vel[2]);
                dir.normalize();
                float cosTheta = Vec3::dot(axes, dir);
                _owner->setRotationQuat(Quaternion(_rotRefAxes, acosf(cosTheta)));
            }
        }
    }
}

void cocos2d::NavMeshAgent::syncToAgent()
{
    setPosition(_owner->getPosition3D());
}

void NavMeshAgent::setPosition(const Vec3 & pos)
{
    if (pos == _param.position) return;
    _param.position = pos;
    _needUpdateAgent = true;
}

NS_CC_END
