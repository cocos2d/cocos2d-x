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

#ifndef __CCNAV_MESH_AGENT_H__
#define __CCNAV_MESH_AGENT_H__

#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#include "2d/CCComponent.h"

#include "base/CCRef.h"
#include "math/Vec3.h"
#include "recast/DetourCrowd/DetourCrowd.h"

class dtNavMeshQuery;
NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */
struct CC_DLL NavMeshAgentParam
{
    NavMeshAgentParam();

    float radius;						///< Agent radius. [Limit: >= 0]
    float height;						///< Agent height. [Limit: > 0]
    float maxAcceleration;				///< Maximum allowed acceleration. [Limit: >= 0]
    float maxSpeed;						///< Maximum allowed speed. [Limit: >= 0]

    /// Defines how close a collision element must be before it is considered for steering behaviors. [Limits: > 0]
    float collisionQueryRange;

    float pathOptimizationRange;		///< The path visibility optimization range. [Limit: > 0]

    /// How aggresive the agent manager should be at avoiding collisions with this agent. [Limit: >= 0]
    float separationWeight;

    /// Flags that impact steering behavior. (See: #UpdateFlags)
    unsigned char updateFlags;

    /// The index of the avoidance configuration to use for the agent. 
    /// [Limits: 0 <= value <= #DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS]
    unsigned char obstacleAvoidanceType;

    /// The index of the query filter used by this agent.
    unsigned char queryFilterType;
};

struct CC_DLL OffMeshLinkData
{
    Vec3 startPosition;//position in local coordinate system.
    Vec3 endPosition;//position in local coordinate system.
};

/** @brief NavMeshAgent: The code wrapping of dtCrowdAgent, use component mode. */
class CC_DLL NavMeshAgent : public Component
{
    friend class NavMesh;
public:

    enum NavMeshAgentSyncFlag
    {
        NONE = 0,
        NODE_TO_AGENT = 1,
        AGENT_TO_NODE = 2,
        NODE_AND_NODE = NODE_TO_AGENT | AGENT_TO_NODE,
    };

    typedef std::function<void(NavMeshAgent *agent, float totalTimeAfterMove)> MoveCallback;

    /**
    Create agent

    @param param The parameters of agent.
    */
    static NavMeshAgent* create(const NavMeshAgentParam &param);
    static const std::string& getNavMeshAgentComponentName();

    virtual void onEnter() override;
    virtual void onExit() override;

    /** set agent radius */
    void setRadius(float radius);

    /** get agent radius */
    float getRadius() const;

    /** set agent height */
    void setHeight(float height);

    /** get agent height */
    float getHeight() const;

    /** set maximal acceleration of agent*/
    void setMaxAcceleration(float maxAcceleration);

    /** get maximal acceleration of agent*/
    float getMaxAcceleration() const;

    /** set maximal speed of agent */
    void setMaxSpeed(float maxSpeed);

    /** get maximal speed of agent */
    float getMaxSpeed() const;

    /** set separation weight */
    void setSeparationWeight(float weight);

    /** get separation weight */
    float getSeparationWeight() const;

    /** set obstacle avoidance type */
    void setObstacleAvoidanceType(unsigned char type);

    /** get obstacle avoidance type */
    unsigned char getObstacleAvoidanceType() const;

    /** get current velocity */
    Vec3 getCurrentVelocity() const;

    /**
    Move agent to a destination

    @param destination The position in world coordinate system.
    @param callback Use this function can catch movement state.
    */
    void move(const Vec3 &destination, const MoveCallback &callback = nullptr);

    /** puase movement */
    void pause();

    /** resume movement */
    void resume();

    /** stop movement */
    void stop();

    /**
    Set the reference axes of agent's orientation

    @param rotRefAxes The value of reference axes in local coordinate system.
    */
    void setOrientationRefAxes(const Vec3 &rotRefAxes);

    /**Set automatic Orientation */
    void setAutoOrientation(bool isAuto);

    /**Set automatic Traverse OffMeshLink */
    void setAutoTraverseOffMeshLink(bool isAuto);

    /**Check agent arrived OffMeshLink */
    bool isOnOffMeshLink();

    /**Traverse OffMeshLink manually*/
    void completeOffMeshLink();

    /**Get current OffMeshLink information*/
    OffMeshLinkData getCurrentOffMeshLinkData();

    void setUserData(void *data) { _userData = data; };
    void* getUserData() const { return _userData; };

    /**
    * synchronization between node and agent is time consuming, you can skip some synchronization using this function
    */
    void setSyncFlag(const NavMeshAgentSyncFlag &flag) { _syncFlag = flag;  }
    NavMeshAgentSyncFlag getSyncFlag() const { return _syncFlag; }

    /** synchronize parameter to agent. */
    void syncToAgent();

    /** synchronize parameter to node. */
    void syncToNode();
    
    /** get current velocity */
    Vec3 getVelocity() const;

CC_CONSTRUCTOR_ACCESS:
    NavMeshAgent();
    virtual ~NavMeshAgent();

private:

    bool initWith(const NavMeshAgentParam &param);
    void addTo(dtCrowd *crowed);
    void removeFrom(dtCrowd *crowed);
    void setNavMeshQuery(dtNavMeshQuery *query);
    void preUpdate(float delta);
    void postUpdate(float delta);
    static void convertTodtAgentParam(const NavMeshAgentParam &inParam, dtCrowdAgentParams &outParam);

private:

    MoveCallback _moveCallback;
    NavMeshAgentParam _param;
    NavMeshAgentSyncFlag _syncFlag;
    Vec3 _origination;
    Vec3 _destination;
    Vec3 _rotRefAxes;
    unsigned char _state;
    bool _needAutoOrientation;
    int _agentID;
    bool _needUpdateAgent;
    bool _needMove;
    float _totalTimeAfterMove;
    void *_userData;
    dtCrowd *_crowd;
    dtNavMeshQuery *_navMeshQuery;
};

/** @} */

NS_CC_END

#endif //CC_USE_NAVMESH

#endif // __CCNAV_MESH_AGENT_H__
