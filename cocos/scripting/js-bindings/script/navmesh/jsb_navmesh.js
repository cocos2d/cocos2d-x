
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