/**
 * @module cocos2dx_navmesh
 */
var jsb = jsb || {};

/**
 * @class NavMeshAgent
 */
jsb.NavMeshAgent = {

/**
 * @method setMaxSpeed
 * @param {float} arg0
 */
setMaxSpeed : function (
float 
)
{
},

/**
 * @method syncToNode
 */
syncToNode : function (
)
{
},

/**
 * @method completeOffMeshLink
 */
completeOffMeshLink : function (
)
{
},

/**
 * @method getSeparationWeight
 * @return {float}
 */
getSeparationWeight : function (
)
{
    return 0;
},

/**
 * @method setAutoTraverseOffMeshLink
 * @param {bool} arg0
 */
setAutoTraverseOffMeshLink : function (
bool 
)
{
},

/**
 * @method getCurrentVelocity
 * @return {vec3_object}
 */
getCurrentVelocity : function (
)
{
    return cc.Vec3;
},

/**
 * @method syncToAgent
 */
syncToAgent : function (
)
{
},

/**
 * @method isOnOffMeshLink
 * @return {bool}
 */
isOnOffMeshLink : function (
)
{
    return false;
},

/**
 * @method setSeparationWeight
 * @param {float} arg0
 */
setSeparationWeight : function (
float 
)
{
},

/**
 * @method pause
 */
pause : function (
)
{
},

/**
 * @method setAutoOrientation
 * @param {bool} arg0
 */
setAutoOrientation : function (
bool 
)
{
},

/**
 * @method getHeight
 * @return {float}
 */
getHeight : function (
)
{
    return 0;
},

/**
 * @method getMaxSpeed
 * @return {float}
 */
getMaxSpeed : function (
)
{
    return 0;
},

/**
 * @method getCurrentOffMeshLinkData
 * @return {cc.OffMeshLinkData}
 */
getCurrentOffMeshLinkData : function (
)
{
    return cc.OffMeshLinkData;
},

/**
 * @method getRadius
 * @return {float}
 */
getRadius : function (
)
{
    return 0;
},

/**
 * @method setSyncFlag
 * @param {cc.NavMeshAgent::NavMeshAgentSyncFlag} arg0
 */
setSyncFlag : function (
navmeshagentsyncflag 
)
{
},

/**
 * @method getSyncFlag
 * @return {cc.NavMeshAgent::NavMeshAgentSyncFlag}
 */
getSyncFlag : function (
)
{
    return 0;
},

/**
 * @method resume
 */
resume : function (
)
{
},

/**
 * @method stop
 */
stop : function (
)
{
},

/**
 * @method setMaxAcceleration
 * @param {float} arg0
 */
setMaxAcceleration : function (
float 
)
{
},

/**
 * @method setOrientationRefAxes
 * @param {vec3_object} arg0
 */
setOrientationRefAxes : function (
vec3 
)
{
},

/**
 * @method getMaxAcceleration
 * @return {float}
 */
getMaxAcceleration : function (
)
{
    return 0;
},

/**
 * @method setHeight
 * @param {float} arg0
 */
setHeight : function (
float 
)
{
},

/**
 * @method getObstacleAvoidanceType
 * @return {unsigned char}
 */
getObstacleAvoidanceType : function (
)
{
    return 0;
},

/**
 * @method getVelocity
 * @return {vec3_object}
 */
getVelocity : function (
)
{
    return cc.Vec3;
},

/**
 * @method setRadius
 * @param {float} arg0
 */
setRadius : function (
float 
)
{
},

/**
 * @method setObstacleAvoidanceType
 * @param {unsigned char} arg0
 */
setObstacleAvoidanceType : function (
char 
)
{
},

/**
 * @method getNavMeshAgentComponentName
 * @return {String}
 */
getNavMeshAgentComponentName : function (
)
{
    return ;
},

/**
 * @method create
 * @param {cc.NavMeshAgentParam} arg0
 * @return {cc.NavMeshAgent}
 */
create : function (
navmeshagentparam 
)
{
    return cc.NavMeshAgent;
},

/**
 * @method NavMeshAgent
 * @constructor
 */
NavMeshAgent : function (
)
{
},

};

/**
 * @class NavMeshObstacle
 */
jsb.NavMeshObstacle = {

/**
 * @method getSyncFlag
 * @return {cc.NavMeshObstacle::NavMeshObstacleSyncFlag}
 */
getSyncFlag : function (
)
{
    return 0;
},

/**
 * @method initWith
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWith : function (
float, 
float 
)
{
    return false;
},

/**
 * @method syncToObstacle
 */
syncToObstacle : function (
)
{
},

/**
 * @method syncToNode
 */
syncToNode : function (
)
{
},

/**
 * @method getHeight
 * @return {float}
 */
getHeight : function (
)
{
    return 0;
},

/**
 * @method setSyncFlag
 * @param {cc.NavMeshObstacle::NavMeshObstacleSyncFlag} arg0
 */
setSyncFlag : function (
navmeshobstaclesyncflag 
)
{
},

/**
 * @method getRadius
 * @return {float}
 */
getRadius : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @return {cc.NavMeshObstacle}
 */
create : function (
float, 
float 
)
{
    return cc.NavMeshObstacle;
},

/**
 * @method getNavMeshObstacleComponentName
 * @return {String}
 */
getNavMeshObstacleComponentName : function (
)
{
    return ;
},

/**
 * @method NavMeshObstacle
 * @constructor
 */
NavMeshObstacle : function (
)
{
},

};

/**
 * @class NavMesh
 */
jsb.NavMesh = {

/**
 * @method removeNavMeshObstacle
 * @param {cc.NavMeshObstacle} arg0
 */
removeNavMeshObstacle : function (
navmeshobstacle 
)
{
},

/**
 * @method removeNavMeshAgent
 * @param {cc.NavMeshAgent} arg0
 */
removeNavMeshAgent : function (
navmeshagent 
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method isDebugDrawEnabled
 * @return {bool}
 */
isDebugDrawEnabled : function (
)
{
    return false;
},

/**
 * @method addNavMeshAgent
 * @param {cc.NavMeshAgent} arg0
 */
addNavMeshAgent : function (
navmeshagent 
)
{
},

/**
 * @method addNavMeshObstacle
 * @param {cc.NavMeshObstacle} arg0
 */
addNavMeshObstacle : function (
navmeshobstacle 
)
{
},

/**
 * @method setDebugDrawEnable
 * @param {bool} arg0
 */
setDebugDrawEnable : function (
bool 
)
{
},

/**
 * @method debugDraw
 * @param {cc.Renderer} arg0
 */
debugDraw : function (
renderer 
)
{
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @return {cc.NavMesh}
 */
create : function (
str, 
str 
)
{
    return cc.NavMesh;
},

/**
 * @method NavMesh
 * @constructor
 */
NavMesh : function (
)
{
},

};
