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
#if CC_USE_NAVMESH

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
    , _state(DT_CROWDAGENT_STATE_INVALID)
    , _syncFlag(NODE_AND_NODE)
    , _isOnOffMesh(false)
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

    auto navMesh = _owner->getScene()->getNavMesh();
    if (navMesh){
        navMesh->removeNavMeshAgent(this);
    }		
}

void cocos2d::NavMeshAgent::onEnter()
{
    Component::onEnter();

    auto navMesh = _owner->getScene()->getNavMesh();
    if (navMesh){
        navMesh->addNavMeshAgent(this);
    }
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
    _param.maxSpeed = maxSpeed;
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

void NavMeshAgent::move(const Vec3 &destination, const MoveCallback &callback, const Vec3 &rotRefAxes, bool needAutoOrientation)
{
    if (_state != DT_CROWDAGENT_STATE_INVALID) return;
    _origination = _param.position;
    _destination = destination;
    _moveCallback = callback;
    _state = DT_CROWDAGENT_STATE_WALKING;
    _needMove = true;
    _needUpdateAgent = true;
}

OffMeshLinkData NavMeshAgent::getCurrentOffMeshLinkData()
{
    OffMeshLinkData data;
    if (_crowd && isOnOffMeshLink()){
        auto agent = _crowd->getAgent(_agentID);
        if (agent){
            dtPathCorridor pc = agent->corridor;
            dtPolyRef refs[2];
            pc.moveOverOffmeshConnection(agent->cornerPolys[agent->ncorners - 1], refs,
                &data.startPosition.x, &data.endPosition.x, _navMeshQuery);
        }
    }
    return data;
}

bool NavMeshAgent::isOnOffMeshLink()
{
    if (_state == DT_CROWDAGENT_STATE_OFFMESH){
        _isOnOffMesh = true;
    }

    return _isOnOffMesh;
}

void cocos2d::NavMeshAgent::completeOffMeshLink()
{
    _isOnOffMesh = false;
}

void NavMeshAgent::stop()
{
    if (_state != DT_CROWDAGENT_STATE_INVALID) return;
    _param.position = _origination;
    _state = DT_CROWDAGENT_STATE_INVALID;
    _needUpdateAgent = true;
}

void NavMeshAgent::resume()
{
    if (_state != DT_CROWDAGENT_STATE_INVALID) return;
    _state = DT_CROWDAGENT_STATE_WALKING;
    _needUpdateAgent = true;
}

void NavMeshAgent::pause()
{
    if (_state == DT_CROWDAGENT_STATE_INVALID) return;
    _state = DT_CROWDAGENT_STATE_INVALID;
    _needUpdateAgent = true;
}

void NavMeshAgent::preUpdate(float delta)
{
    if ((_syncFlag & NODE_TO_AGENT) != 0)
        syncToAgent();

    if (_needUpdateAgent && _crowd){
        auto agent = _crowd->getEditableAgent(_agentID);
        dtCrowdAgentParams ap;
        convertTodtAgentParam(_param, ap);
        agent->params = ap;
        agent->state = _state;
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

void NavMeshAgent::postUpdate(float delta)
{
    if ((_syncFlag & AGENT_TO_NODE) != 0)
        syncToNode();
}

void NavMeshAgent::syncToNode()
{
    const dtCrowdAgent *agent = nullptr;
    if (_crowd){
        agent = _crowd->getAgent(_agentID);
    }

    if (agent){
        _state = agent->state;
        _param.position = Vec3(agent->npos[0], agent->npos[1], agent->npos[2]);
        bool autoMove = true;
        if (_moveCallback){
            _moveCallback(this, autoMove);
        }
        if (autoMove){
            _owner->setPosition3D(_param.position);
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
}

void NavMeshAgent::syncToAgent()
{
    setPosition(_owner->getPosition3D());
}

void NavMeshAgent::setPosition(const Vec3 & pos)
{
    if (pos == _param.position) return;
    _param.position = pos;
    _needUpdateAgent = true;
}

Vec3 NavMeshAgent::getVelocity() const
{
    const dtCrowdAgent *agent = nullptr;
    if (_crowd){
        agent = _crowd->getAgent(_agentID);
    }
    if (agent)
    {
        return Vec3(agent->vel[0], agent->vel[1], agent->vel[2]);
    }
    return Vec3::ZERO;
}

NS_CC_END

#endif //CC_USE_NAVMESH
