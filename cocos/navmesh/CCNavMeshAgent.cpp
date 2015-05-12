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
{

}

cocos2d::NavMeshAgent::~NavMeshAgent()
{

}

bool NavMeshAgent::init(const NavMeshAgentParam &param)
{
	_param = param;
	//dtCrowdAgentParams ap;
	//memset(&ap, 0, sizeof(ap));
	//ap.collisionQueryRange = param.collisionQueryRange;
	//ap.height = param.height;
	//ap.maxAcceleration = param.maxAcceleration;
	//ap.maxSpeed = param.maxSpeed;
	//ap.obstacleAvoidanceType = param.obstacleAvoidanceType;
	//ap.pathOptimizationRange = param.pathOptimizationRange;
	//ap.queryFilterType = param.queryFilterType;
	//ap.radius = param.radius;
	//ap.separationWeight = param.separationWeight;
	//ap.updateFlags = param.updateFlags;
	return true;
}

NS_CC_END