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

#include "base/CCRef.h"
#include "recast/DetourCrowd/DetourCrowd.h"


NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */

struct CC_DLL NavMeshAgentParam
{
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

class CC_DLL NavMeshAgent : public Ref
{
public:

	static NavMeshAgent* create(const NavMeshAgentParam &param);


CC_CONSTRUCTOR_ACCESS:
	NavMeshAgent();
	virtual ~NavMeshAgent();

private:

	bool init(const NavMeshAgentParam &param);

private:

	NavMeshAgentParam _param;
	int _agentID;
	dtCrowd *_crowd;
};

/** @} */

NS_CC_END

#endif // __CCNAV_MESH_AGENT_H__
