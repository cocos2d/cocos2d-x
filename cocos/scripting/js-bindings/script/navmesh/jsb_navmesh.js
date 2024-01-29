/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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


jsb.NavMesh.UpdateFlags = 
{
    DT_CROWD_ANTICIPATE_TURNS:1,
    DT_CROWD_OBSTACLE_AVOIDANCE:2,
    DT_CROWD_SEPARATION:4,
    DT_CROWD_OPTIMIZE_VIS:8,          ///< Use #dtPathCorridor::optimizePathVisibility() to optimize the agent path.
    DT_CROWD_OPTIMIZE_TOPO:16,        ///< Use dtPathCorridor::optimizePathTopology() to optimize the agent path.
};


jsb.NavMeshAgentParam = function(){
    this.radius = 0.6;
    this.height = 2;
    this.maxAcceleration = 8;
    this.maxSpeed = 3.5;
    this.collisionQueryRange = this.radius * 12;
    this.pathOptimizationRange = this.radius * 30;
    this.updateFlags = jsb.NavMesh.UpdateFlags.DT_CROWD_ANTICIPATE_TURNS | 
                       jsb.NavMesh.UpdateFlags.DT_CROWD_OPTIMIZE_VIS | 
                       jsb.NavMesh.UpdateFlags.DT_CROWD_OPTIMIZE_TOPO | 
                       jsb.NavMesh.UpdateFlags.DT_CROWD_OBSTACLE_AVOIDANCE;
    this.obstacleAvoidanceType = 3;
    this.separationWeight = 2;
    this.queryFilterType = 0;
}

jsb.navMeshAgentParam = function(){
    return new jsb.NavMeshAgentParam();
};

jsb.AgentUserData = function(){
    this.time = 0;
};

jsb.agentUserData = function(){
    return new jsb.AgentUserData();
};

jsb.NavMeshAgent.prototype.setUserData = cc.Node.prototype.setUserData;
jsb.NavMeshAgent.prototype.getUserData = cc.Node.prototype.getUserData;