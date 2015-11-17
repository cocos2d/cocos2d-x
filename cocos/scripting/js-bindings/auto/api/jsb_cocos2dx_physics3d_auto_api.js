/**
 * @module cocos2dx_physics3d
 */
var jsb = jsb || {};

/**
 * @class Physics3DShape
 */
jsb.Physics3DShape = {

/**
 * @method initConvexHull
 * @param {vec3_object} arg0
 * @param {int} arg1
 * @return {bool}
 */
initConvexHull : function (
vec3, 
int 
)
{
    return false;
},

/**
 * @method getbtShape
 * @return {btCollisionShape}
 */
getbtShape : function (
)
{
    return btCollisionShape;
},

/**
 * @method initSphere
 * @param {float} arg0
 * @return {bool}
 */
initSphere : function (
float 
)
{
    return false;
},

/**
 * @method initBox
 * @param {vec3_object} arg0
 * @return {bool}
 */
initBox : function (
vec3 
)
{
    return false;
},

/**
 * @method initCapsule
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initCapsule : function (
float, 
float 
)
{
    return false;
},

/**
 * @method initCylinder
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initCylinder : function (
float, 
float 
)
{
    return false;
},

/**
 * @method getShapeType
 * @return {cc.Physics3DShape::ShapeType}
 */
getShapeType : function (
)
{
    return 0;
},

/**
 * @method createBox
 * @param {vec3_object} arg0
 * @return {cc.Physics3DShape}
 */
createBox : function (
vec3 
)
{
    return cc.Physics3DShape;
},

/**
 * @method createCylinder
 * @param {float} arg0
 * @param {float} arg1
 * @return {cc.Physics3DShape}
 */
createCylinder : function (
float, 
float 
)
{
    return cc.Physics3DShape;
},

/**
 * @method createConvexHull
 * @param {vec3_object} arg0
 * @param {int} arg1
 * @return {cc.Physics3DShape}
 */
createConvexHull : function (
vec3, 
int 
)
{
    return cc.Physics3DShape;
},

/**
 * @method createCapsule
 * @param {float} arg0
 * @param {float} arg1
 * @return {cc.Physics3DShape}
 */
createCapsule : function (
float, 
float 
)
{
    return cc.Physics3DShape;
},

/**
 * @method createSphere
 * @param {float} arg0
 * @return {cc.Physics3DShape}
 */
createSphere : function (
float 
)
{
    return cc.Physics3DShape;
},

/**
 * @method Physics3DShape
 * @constructor
 */
Physics3DShape : function (
)
{
},

};

/**
 * @class Physics3DObject
 */
jsb.Physics3DObject = {

/**
 * @method setUserData
 * @param {void} arg0
 */
setUserData : function (
void 
)
{
},

/**
 * @method getUserData
 * @return {void}
 */
getUserData : function (
)
{
    return void;
},

/**
 * @method getObjType
 * @return {cc.Physics3DObject::PhysicsObjType}
 */
getObjType : function (
)
{
    return 0;
},

/**
 * @method setPhysicsWorld
 * @param {cc.Physics3DWorld} arg0
 */
setPhysicsWorld : function (
physics3dworld 
)
{
},

/**
 * @method getWorldTransform
 * @return {mat4_object}
 */
getWorldTransform : function (
)
{
    return cc.Mat4;
},

/**
 * @method getPhysicsWorld
 * @return {cc.Physics3DWorld}
 */
getPhysicsWorld : function (
)
{
    return cc.Physics3DWorld;
},

/**
 * @method setMask
 * @param {unsigned int} arg0
 */
setMask : function (
int 
)
{
},

/**
 * @method getCollisionCallback
 * @return {function}
 */
getCollisionCallback : function (
)
{
    return std::function<void (cocos2d::Physics3DCollisionInfo &)>;
},

/**
 * @method getMask
 * @return {unsigned int}
 */
getMask : function (
)
{
    return 0;
},

/**
 * @method needCollisionCallback
 * @return {bool}
 */
needCollisionCallback : function (
)
{
    return false;
},

};

/**
 * @class Physics3DRigidBody
 */
jsb.Physics3DRigidBody = {

/**
 * @method setGravity
 * @param {vec3_object} arg0
 */
setGravity : function (
vec3 
)
{
},

/**
 * @method getFriction
 * @return {float}
 */
getFriction : function (
)
{
    return 0;
},

/**
 * @method setAngularFactor
* @param {float|vec3_object} float
*/
setAngularFactor : function(
vec3 
)
{
},

/**
 * @method addConstraint
 * @param {cc.Physics3DConstraint} arg0
 */
addConstraint : function (
physics3dconstraint 
)
{
},

/**
 * @method getRigidBody
 * @return {btRigidBody}
 */
getRigidBody : function (
)
{
    return btRigidBody;
},

/**
 * @method getTotalForce
 * @return {vec3_object}
 */
getTotalForce : function (
)
{
    return cc.Vec3;
},

/**
 * @method getConstraintCount
 * @return {unsigned int}
 */
getConstraintCount : function (
)
{
    return 0;
},

/**
 * @method applyCentralForce
 * @param {vec3_object} arg0
 */
applyCentralForce : function (
vec3 
)
{
},

/**
 * @method setMassProps
 * @param {float} arg0
 * @param {vec3_object} arg1
 */
setMassProps : function (
float, 
vec3 
)
{
},

/**
 * @method setFriction
 * @param {float} arg0
 */
setFriction : function (
float 
)
{
},

/**
 * @method setKinematic
 * @param {bool} arg0
 */
setKinematic : function (
bool 
)
{
},

/**
 * @method setDamping
 * @param {float} arg0
 * @param {float} arg1
 */
setDamping : function (
float, 
float 
)
{
},

/**
 * @method applyImpulse
 * @param {vec3_object} arg0
 * @param {vec3_object} arg1
 */
applyImpulse : function (
vec3, 
vec3 
)
{
},

/**
 * @method isKinematic
 * @return {bool}
 */
isKinematic : function (
)
{
    return false;
},

/**
 * @method applyTorque
 * @param {vec3_object} arg0
 */
applyTorque : function (
vec3 
)
{
},

/**
 * @method setCcdMotionThreshold
 * @param {float} arg0
 */
setCcdMotionThreshold : function (
float 
)
{
},

/**
 * @method setRollingFriction
 * @param {float} arg0
 */
setRollingFriction : function (
float 
)
{
},

/**
 * @method getCcdMotionThreshold
 * @return {float}
 */
getCcdMotionThreshold : function (
)
{
    return 0;
},

/**
 * @method getLinearFactor
 * @return {vec3_object}
 */
getLinearFactor : function (
)
{
    return cc.Vec3;
},

/**
 * @method applyDamping
 * @param {float} arg0
 */
applyDamping : function (
float 
)
{
},

/**
 * @method getAngularVelocity
 * @return {vec3_object}
 */
getAngularVelocity : function (
)
{
    return cc.Vec3;
},

/**
 * @method init
 * @param {cc.Physics3DRigidBodyDes} arg0
 * @return {bool}
 */
init : function (
physics3drigidbodydes 
)
{
    return false;
},

/**
 * @method applyTorqueImpulse
 * @param {vec3_object} arg0
 */
applyTorqueImpulse : function (
vec3 
)
{
},

/**
 * @method setActive
 * @param {bool} arg0
 */
setActive : function (
bool 
)
{
},

/**
 * @method setLinearFactor
 * @param {vec3_object} arg0
 */
setLinearFactor : function (
vec3 
)
{
},

/**
 * @method setLinearVelocity
 * @param {vec3_object} arg0
 */
setLinearVelocity : function (
vec3 
)
{
},

/**
 * @method getLinearVelocity
 * @return {vec3_object}
 */
getLinearVelocity : function (
)
{
    return cc.Vec3;
},

/**
 * @method setCcdSweptSphereRadius
 * @param {float} arg0
 */
setCcdSweptSphereRadius : function (
float 
)
{
},

/**
 * @method applyForce
 * @param {vec3_object} arg0
 * @param {vec3_object} arg1
 */
applyForce : function (
vec3, 
vec3 
)
{
},

/**
 * @method setAngularVelocity
 * @param {vec3_object} arg0
 */
setAngularVelocity : function (
vec3 
)
{
},

/**
 * @method applyCentralImpulse
 * @param {vec3_object} arg0
 */
applyCentralImpulse : function (
vec3 
)
{
},

/**
 * @method getGravity
 * @return {vec3_object}
 */
getGravity : function (
)
{
    return cc.Vec3;
},

/**
 * @method getRollingFriction
 * @return {float}
 */
getRollingFriction : function (
)
{
    return 0;
},

/**
 * @method setCenterOfMassTransform
 * @param {mat4_object} arg0
 */
setCenterOfMassTransform : function (
mat4 
)
{
},

/**
 * @method setInvInertiaDiagLocal
 * @param {vec3_object} arg0
 */
setInvInertiaDiagLocal : function (
vec3 
)
{
},

/**
 * @method removeConstraint
* @param {unsigned int|cc.Physics3DConstraint} int
*/
removeConstraint : function(
physics3dconstraint 
)
{
},

/**
 * @method getTotalTorque
 * @return {vec3_object}
 */
getTotalTorque : function (
)
{
    return cc.Vec3;
},

/**
 * @method getInvMass
 * @return {float}
 */
getInvMass : function (
)
{
    return 0;
},

/**
 * @method getConstraint
 * @param {unsigned int} arg0
 * @return {cc.Physics3DConstraint}
 */
getConstraint : function (
int 
)
{
    return cc.Physics3DConstraint;
},

/**
 * @method getRestitution
 * @return {float}
 */
getRestitution : function (
)
{
    return 0;
},

/**
 * @method getCcdSweptSphereRadius
 * @return {float}
 */
getCcdSweptSphereRadius : function (
)
{
    return 0;
},

/**
 * @method getHitFraction
 * @return {float}
 */
getHitFraction : function (
)
{
    return 0;
},

/**
 * @method getAngularDamping
 * @return {float}
 */
getAngularDamping : function (
)
{
    return 0;
},

/**
 * @method getInvInertiaDiagLocal
 * @return {vec3_object}
 */
getInvInertiaDiagLocal : function (
)
{
    return cc.Vec3;
},

/**
 * @method getCenterOfMassTransform
 * @return {mat4_object}
 */
getCenterOfMassTransform : function (
)
{
    return cc.Mat4;
},

/**
 * @method getAngularFactor
 * @return {vec3_object}
 */
getAngularFactor : function (
)
{
    return cc.Vec3;
},

/**
 * @method setRestitution
 * @param {float} arg0
 */
setRestitution : function (
float 
)
{
},

/**
 * @method setHitFraction
 * @param {float} arg0
 */
setHitFraction : function (
float 
)
{
},

/**
 * @method getLinearDamping
 * @return {float}
 */
getLinearDamping : function (
)
{
    return 0;
},

/**
 * @method Physics3DRigidBody
 * @constructor
 */
Physics3DRigidBody : function (
)
{
},

};

/**
 * @class Physics3DComponent
 */
jsb.Physics3DComponent = {

/**
 * @method syncNodeToPhysics
 */
syncNodeToPhysics : function (
)
{
},

/**
 * @method addToPhysicsWorld
 * @param {cc.Physics3DWorld} arg0
 */
addToPhysicsWorld : function (
physics3dworld 
)
{
},

/**
 * @method syncPhysicsToNode
 */
syncPhysicsToNode : function (
)
{
},

/**
 * @method getPhysics3DObject
 * @return {cc.Physics3DObject}
 */
getPhysics3DObject : function (
)
{
    return cc.Physics3DObject;
},

/**
 * @method setPhysics3DObject
 * @param {cc.Physics3DObject} arg0
 */
setPhysics3DObject : function (
physics3dobject 
)
{
},

/**
 * @method setSyncFlag
 * @param {cc.Physics3DComponent::PhysicsSyncFlag} arg0
 */
setSyncFlag : function (
physicssyncflag 
)
{
},

/**
 * @method setTransformInPhysics
 * @param {vec3_object} arg0
 * @param {cc.Quaternion} arg1
 */
setTransformInPhysics : function (
vec3, 
quaternion 
)
{
},

/**
 * @method create
* @param {cc.Physics3DObject} physics3dobject
* @param {vec3_object} vec3
* @param {cc.Quaternion} quaternion
* @return {cc.Physics3DComponent|cc.Physics3DComponent}
*/
create : function(
physics3dobject,
vec3,
quaternion 
)
{
    return cc.Physics3DComponent;
},

/**
 * @method getPhysics3DComponentName
 * @return {String}
 */
getPhysics3DComponentName : function (
)
{
    return ;
},

/**
 * @method Physics3DComponent
 * @constructor
 */
Physics3DComponent : function (
)
{
},

};

/**
 * @class PhysicsSprite3D
 */
jsb.PhysicsSprite3D = {

/**
 * @method syncNodeToPhysics
 */
syncNodeToPhysics : function (
)
{
},

/**
 * @method syncPhysicsToNode
 */
syncPhysicsToNode : function (
)
{
},

/**
 * @method getPhysicsObj
 * @return {cc.Physics3DObject}
 */
getPhysicsObj : function (
)
{
    return cc.Physics3DObject;
},

/**
 * @method setSyncFlag
 * @param {cc.Physics3DComponent::PhysicsSyncFlag} arg0
 */
setSyncFlag : function (
physicssyncflag 
)
{
},

/**
 * @method PhysicsSprite3D
 * @constructor
 */
PhysicsSprite3D : function (
)
{
},

};

/**
 * @class Physics3DWorld
 */
jsb.Physics3DWorld = {

/**
 * @method setGravity
 * @param {vec3_object} arg0
 */
setGravity : function (
vec3 
)
{
},

/**
 * @method stepSimulate
 * @param {float} arg0
 */
stepSimulate : function (
float 
)
{
},

/**
 * @method needCollisionChecking
 * @return {bool}
 */
needCollisionChecking : function (
)
{
    return false;
},

/**
 * @method collisionChecking
 */
collisionChecking : function (
)
{
},

/**
 * @method setGhostPairCallback
 */
setGhostPairCallback : function (
)
{
},

/**
 * @method init
 * @param {cc.Physics3DWorldDes} arg0
 * @return {bool}
 */
init : function (
physics3dworlddes 
)
{
    return false;
},

/**
 * @method removeAllPhysics3DObjects
 */
removeAllPhysics3DObjects : function (
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
 * @method removeAllPhysics3DConstraints
 */
removeAllPhysics3DConstraints : function (
)
{
},

/**
 * @method getGravity
 * @return {vec3_object}
 */
getGravity : function (
)
{
    return cc.Vec3;
},

/**
 * @method removePhysics3DConstraint
 * @param {cc.Physics3DConstraint} arg0
 */
removePhysics3DConstraint : function (
physics3dconstraint 
)
{
},

/**
 * @method addPhysics3DObject
 * @param {cc.Physics3DObject} arg0
 */
addPhysics3DObject : function (
physics3dobject 
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
 * @method removePhysics3DObject
 * @param {cc.Physics3DObject} arg0
 */
removePhysics3DObject : function (
physics3dobject 
)
{
},

/**
 * @method getPhysicsObject
 * @param {btCollisionObject} arg0
 * @return {cc.Physics3DObject}
 */
getPhysicsObject : function (
btcollisionobject 
)
{
    return cc.Physics3DObject;
},

/**
 * @method addPhysics3DConstraint
 * @param {cc.Physics3DConstraint} arg0
 * @param {bool} arg1
 */
addPhysics3DConstraint : function (
physics3dconstraint, 
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
 * @method sweepShape
 * @param {cc.Physics3DShape} arg0
 * @param {mat4_object} arg1
 * @param {mat4_object} arg2
 * @param {cc.Physics3DWorld::HitResult} arg3
 * @return {bool}
 */
sweepShape : function (
physics3dshape, 
mat4, 
mat4, 
hitresult 
)
{
    return false;
},

/**
 * @method create
 * @param {cc.Physics3DWorldDes} arg0
 * @return {cc.Physics3DWorld}
 */
create : function (
physics3dworlddes 
)
{
    return cc.Physics3DWorld;
},

/**
 * @method Physics3DWorld
 * @constructor
 */
Physics3DWorld : function (
)
{
},

};

/**
 * @class Physics3DConstraint
 */
jsb.Physics3DConstraint = {

/**
 * @method setEnabled
 * @param {bool} arg0
 */
setEnabled : function (
bool 
)
{
},

/**
 * @method setBreakingImpulse
 * @param {float} arg0
 */
setBreakingImpulse : function (
float 
)
{
},

/**
 * @method getUserData
 * @return {void}
 */
getUserData : function (
)
{
    return void;
},

/**
 * @method getBreakingImpulse
 * @return {float}
 */
getBreakingImpulse : function (
)
{
    return 0;
},

/**
 * @method getBodyA
 * @return {cc.Physics3DRigidBody}
 */
getBodyA : function (
)
{
    return cc.Physics3DRigidBody;
},

/**
 * @method isEnabled
 * @return {bool}
 */
isEnabled : function (
)
{
    return false;
},

/**
 * @method getOverrideNumSolverIterations
 * @return {int}
 */
getOverrideNumSolverIterations : function (
)
{
    return 0;
},

/**
 * @method getBodyB
 * @return {cc.Physics3DRigidBody}
 */
getBodyB : function (
)
{
    return cc.Physics3DRigidBody;
},

/**
 * @method setOverrideNumSolverIterations
 * @param {int} arg0
 */
setOverrideNumSolverIterations : function (
int 
)
{
},

/**
 * @method getConstraintType
 * @return {cc.Physics3DConstraint::ConstraintType}
 */
getConstraintType : function (
)
{
    return 0;
},

/**
 * @method setUserData
 * @param {void} arg0
 */
setUserData : function (
void 
)
{
},

/**
 * @method getbtContraint
 * @return {btTypedConstraint}
 */
getbtContraint : function (
)
{
    return btTypedConstraint;
},

};

/**
 * @class Physics3DPointToPointConstraint
 */
jsb.Physics3DPointToPointConstraint = {

/**
 * @method getPivotPointInA
 * @return {vec3_object}
 */
getPivotPointInA : function (
)
{
    return cc.Vec3;
},

/**
 * @method getPivotPointInB
 * @return {vec3_object}
 */
getPivotPointInB : function (
)
{
    return cc.Vec3;
},

/**
 * @method init
* @param {cc.Physics3DRigidBody|cc.Physics3DRigidBody} physics3drigidbody
* @param {cc.Physics3DRigidBody|vec3_object} physics3drigidbody
* @param {vec3_object} vec3
* @param {vec3_object} vec3
* @return {bool|bool}
*/
init : function(
physics3drigidbody,
physics3drigidbody,
vec3,
vec3 
)
{
    return false;
},

/**
 * @method setPivotPointInA
 * @param {vec3_object} arg0
 */
setPivotPointInA : function (
vec3 
)
{
},

/**
 * @method setPivotPointInB
 * @param {vec3_object} arg0
 */
setPivotPointInB : function (
vec3 
)
{
},

/**
 * @method create
* @param {cc.Physics3DRigidBody|cc.Physics3DRigidBody} physics3drigidbody
* @param {cc.Physics3DRigidBody|vec3_object} physics3drigidbody
* @param {vec3_object} vec3
* @param {vec3_object} vec3
* @return {cc.Physics3DPointToPointConstraint|cc.Physics3DPointToPointConstraint}
*/
create : function(
physics3drigidbody,
physics3drigidbody,
vec3,
vec3 
)
{
    return cc.Physics3DPointToPointConstraint;
},

/**
 * @method Physics3DPointToPointConstraint
 * @constructor
 */
Physics3DPointToPointConstraint : function (
)
{
},

};

/**
 * @class Physics3DHingeConstraint
 */
jsb.Physics3DHingeConstraint = {

/**
 * @method getHingeAngle
* @param {mat4_object} mat4
* @param {mat4_object} mat4
* @return {float|float}
*/
getHingeAngle : function(
mat4,
mat4 
)
{
    return 0;
},

/**
 * @method getMotorTargetVelosity
 * @return {float}
 */
getMotorTargetVelosity : function (
)
{
    return 0;
},

/**
 * @method getFrameOffsetA
 * @return {mat4_object}
 */
getFrameOffsetA : function (
)
{
    return cc.Mat4;
},

/**
 * @method getFrameOffsetB
 * @return {mat4_object}
 */
getFrameOffsetB : function (
)
{
    return cc.Mat4;
},

/**
 * @method setMaxMotorImpulse
 * @param {float} arg0
 */
setMaxMotorImpulse : function (
float 
)
{
},

/**
 * @method enableAngularMotor
 * @param {bool} arg0
 * @param {float} arg1
 * @param {float} arg2
 */
enableAngularMotor : function (
bool, 
float, 
float 
)
{
},

/**
 * @method getUpperLimit
 * @return {float}
 */
getUpperLimit : function (
)
{
    return 0;
},

/**
 * @method getMaxMotorImpulse
 * @return {float}
 */
getMaxMotorImpulse : function (
)
{
    return 0;
},

/**
 * @method getLowerLimit
 * @return {float}
 */
getLowerLimit : function (
)
{
    return 0;
},

/**
 * @method setUseFrameOffset
 * @param {bool} arg0
 */
setUseFrameOffset : function (
bool 
)
{
},

/**
 * @method getEnableAngularMotor
 * @return {bool}
 */
getEnableAngularMotor : function (
)
{
    return false;
},

/**
 * @method enableMotor
 * @param {bool} arg0
 */
enableMotor : function (
bool 
)
{
},

/**
 * @method getBFrame
 * @return {mat4_object}
 */
getBFrame : function (
)
{
    return cc.Mat4;
},

/**
 * @method setFrames
 * @param {mat4_object} arg0
 * @param {mat4_object} arg1
 */
setFrames : function (
mat4, 
mat4 
)
{
},

/**
 * @method getUseFrameOffset
 * @return {bool}
 */
getUseFrameOffset : function (
)
{
    return false;
},

/**
 * @method setAngularOnly
 * @param {bool} arg0
 */
setAngularOnly : function (
bool 
)
{
},

/**
 * @method setLimit
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {float} arg3
 * @param {float} arg4
 */
setLimit : function (
float, 
float, 
float, 
float, 
float 
)
{
},

/**
 * @method setMotorTarget
* @param {float|cc.Quaternion} float
* @param {float|float} float
*/
setMotorTarget : function(
quaternion,
float 
)
{
},

/**
 * @method getAngularOnly
 * @return {bool}
 */
getAngularOnly : function (
)
{
    return false;
},

/**
 * @method setAxis
 * @param {vec3_object} arg0
 */
setAxis : function (
vec3 
)
{
},

/**
 * @method getAFrame
 * @return {mat4_object}
 */
getAFrame : function (
)
{
    return cc.Mat4;
},

/**
 * @method create
* @param {cc.Physics3DRigidBody|cc.Physics3DRigidBody|cc.Physics3DRigidBody|cc.Physics3DRigidBody} physics3drigidbody
* @param {vec3_object|mat4_object|cc.Physics3DRigidBody|cc.Physics3DRigidBody} vec3
* @param {vec3_object|bool|vec3_object|mat4_object} vec3
* @param {bool|vec3_object|mat4_object} bool
* @param {vec3_object|bool} vec3
* @param {vec3_object} vec3
* @param {bool} bool
* @return {cc.Physics3DHingeConstraint|cc.Physics3DHingeConstraint|cc.Physics3DHingeConstraint|cc.Physics3DHingeConstraint}
*/
create : function(
physics3drigidbody,
physics3drigidbody,
vec3,
vec3,
vec3,
vec3,
bool 
)
{
    return cc.Physics3DHingeConstraint;
},

/**
 * @method Physics3DHingeConstraint
 * @constructor
 */
Physics3DHingeConstraint : function (
)
{
},

};

/**
 * @class Physics3DSliderConstraint
 */
jsb.Physics3DSliderConstraint = {

/**
 * @method setPoweredAngMotor
 * @param {bool} arg0
 */
setPoweredAngMotor : function (
bool 
)
{
},

/**
 * @method getDampingLimAng
 * @return {float}
 */
getDampingLimAng : function (
)
{
    return 0;
},

/**
 * @method setRestitutionOrthoLin
 * @param {float} arg0
 */
setRestitutionOrthoLin : function (
float 
)
{
},

/**
 * @method setRestitutionDirLin
 * @param {float} arg0
 */
setRestitutionDirLin : function (
float 
)
{
},

/**
 * @method getLinearPos
 * @return {float}
 */
getLinearPos : function (
)
{
    return 0;
},

/**
 * @method getFrameOffsetA
 * @return {mat4_object}
 */
getFrameOffsetA : function (
)
{
    return cc.Mat4;
},

/**
 * @method getFrameOffsetB
 * @return {mat4_object}
 */
getFrameOffsetB : function (
)
{
    return cc.Mat4;
},

/**
 * @method setPoweredLinMotor
 * @param {bool} arg0
 */
setPoweredLinMotor : function (
bool 
)
{
},

/**
 * @method getDampingDirAng
 * @return {float}
 */
getDampingDirAng : function (
)
{
    return 0;
},

/**
 * @method getRestitutionLimLin
 * @return {float}
 */
getRestitutionLimLin : function (
)
{
    return 0;
},

/**
 * @method getSoftnessOrthoAng
 * @return {float}
 */
getSoftnessOrthoAng : function (
)
{
    return 0;
},

/**
 * @method setSoftnessOrthoLin
 * @param {float} arg0
 */
setSoftnessOrthoLin : function (
float 
)
{
},

/**
 * @method setSoftnessLimLin
 * @param {float} arg0
 */
setSoftnessLimLin : function (
float 
)
{
},

/**
 * @method getAngularPos
 * @return {float}
 */
getAngularPos : function (
)
{
    return 0;
},

/**
 * @method setRestitutionLimAng
 * @param {float} arg0
 */
setRestitutionLimAng : function (
float 
)
{
},

/**
 * @method setUpperLinLimit
 * @param {float} arg0
 */
setUpperLinLimit : function (
float 
)
{
},

/**
 * @method setDampingDirLin
 * @param {float} arg0
 */
setDampingDirLin : function (
float 
)
{
},

/**
 * @method getUpperAngLimit
 * @return {float}
 */
getUpperAngLimit : function (
)
{
    return 0;
},

/**
 * @method getDampingDirLin
 * @return {float}
 */
getDampingDirLin : function (
)
{
    return 0;
},

/**
 * @method getSoftnessDirAng
 * @return {float}
 */
getSoftnessDirAng : function (
)
{
    return 0;
},

/**
 * @method getPoweredAngMotor
 * @return {bool}
 */
getPoweredAngMotor : function (
)
{
    return false;
},

/**
 * @method setLowerAngLimit
 * @param {float} arg0
 */
setLowerAngLimit : function (
float 
)
{
},

/**
 * @method setUpperAngLimit
 * @param {float} arg0
 */
setUpperAngLimit : function (
float 
)
{
},

/**
 * @method setTargetLinMotorVelocity
 * @param {float} arg0
 */
setTargetLinMotorVelocity : function (
float 
)
{
},

/**
 * @method setDampingLimAng
 * @param {float} arg0
 */
setDampingLimAng : function (
float 
)
{
},

/**
 * @method getRestitutionLimAng
 * @return {float}
 */
getRestitutionLimAng : function (
)
{
    return 0;
},

/**
 * @method getUseFrameOffset
 * @return {bool}
 */
getUseFrameOffset : function (
)
{
    return false;
},

/**
 * @method getSoftnessOrthoLin
 * @return {float}
 */
getSoftnessOrthoLin : function (
)
{
    return 0;
},

/**
 * @method getDampingOrthoAng
 * @return {float}
 */
getDampingOrthoAng : function (
)
{
    return 0;
},

/**
 * @method setUseFrameOffset
 * @param {bool} arg0
 */
setUseFrameOffset : function (
bool 
)
{
},

/**
 * @method setLowerLinLimit
 * @param {float} arg0
 */
setLowerLinLimit : function (
float 
)
{
},

/**
 * @method getRestitutionDirLin
 * @return {float}
 */
getRestitutionDirLin : function (
)
{
    return 0;
},

/**
 * @method getTargetLinMotorVelocity
 * @return {float}
 */
getTargetLinMotorVelocity : function (
)
{
    return 0;
},

/**
 * @method getLowerLinLimit
 * @return {float}
 */
getLowerLinLimit : function (
)
{
    return 0;
},

/**
 * @method getSoftnessLimLin
 * @return {float}
 */
getSoftnessLimLin : function (
)
{
    return 0;
},

/**
 * @method setDampingOrthoAng
 * @param {float} arg0
 */
setDampingOrthoAng : function (
float 
)
{
},

/**
 * @method setSoftnessDirAng
 * @param {float} arg0
 */
setSoftnessDirAng : function (
float 
)
{
},

/**
 * @method getPoweredLinMotor
 * @return {bool}
 */
getPoweredLinMotor : function (
)
{
    return false;
},

/**
 * @method setRestitutionOrthoAng
 * @param {float} arg0
 */
setRestitutionOrthoAng : function (
float 
)
{
},

/**
 * @method setDampingDirAng
 * @param {float} arg0
 */
setDampingDirAng : function (
float 
)
{
},

/**
 * @method setFrames
 * @param {mat4_object} arg0
 * @param {mat4_object} arg1
 */
setFrames : function (
mat4, 
mat4 
)
{
},

/**
 * @method getRestitutionOrthoAng
 * @return {float}
 */
getRestitutionOrthoAng : function (
)
{
    return 0;
},

/**
 * @method getMaxAngMotorForce
 * @return {float}
 */
getMaxAngMotorForce : function (
)
{
    return 0;
},

/**
 * @method getDampingOrthoLin
 * @return {float}
 */
getDampingOrthoLin : function (
)
{
    return 0;
},

/**
 * @method getUpperLinLimit
 * @return {float}
 */
getUpperLinLimit : function (
)
{
    return 0;
},

/**
 * @method setMaxLinMotorForce
 * @param {float} arg0
 */
setMaxLinMotorForce : function (
float 
)
{
},

/**
 * @method getRestitutionOrthoLin
 * @return {float}
 */
getRestitutionOrthoLin : function (
)
{
    return 0;
},

/**
 * @method setTargetAngMotorVelocity
 * @param {float} arg0
 */
setTargetAngMotorVelocity : function (
float 
)
{
},

/**
 * @method getSoftnessLimAng
 * @return {float}
 */
getSoftnessLimAng : function (
)
{
    return 0;
},

/**
 * @method setRestitutionDirAng
 * @param {float} arg0
 */
setRestitutionDirAng : function (
float 
)
{
},

/**
 * @method getDampingLimLin
 * @return {float}
 */
getDampingLimLin : function (
)
{
    return 0;
},

/**
 * @method getLowerAngLimit
 * @return {float}
 */
getLowerAngLimit : function (
)
{
    return 0;
},

/**
 * @method getRestitutionDirAng
 * @return {float}
 */
getRestitutionDirAng : function (
)
{
    return 0;
},

/**
 * @method getTargetAngMotorVelocity
 * @return {float}
 */
getTargetAngMotorVelocity : function (
)
{
    return 0;
},

/**
 * @method setRestitutionLimLin
 * @param {float} arg0
 */
setRestitutionLimLin : function (
float 
)
{
},

/**
 * @method getMaxLinMotorForce
 * @return {float}
 */
getMaxLinMotorForce : function (
)
{
    return 0;
},

/**
 * @method setDampingOrthoLin
 * @param {float} arg0
 */
setDampingOrthoLin : function (
float 
)
{
},

/**
 * @method setSoftnessOrthoAng
 * @param {float} arg0
 */
setSoftnessOrthoAng : function (
float 
)
{
},

/**
 * @method setDampingLimLin
 * @param {float} arg0
 */
setDampingLimLin : function (
float 
)
{
},

/**
 * @method setSoftnessDirLin
 * @param {float} arg0
 */
setSoftnessDirLin : function (
float 
)
{
},

/**
 * @method setMaxAngMotorForce
 * @param {float} arg0
 */
setMaxAngMotorForce : function (
float 
)
{
},

/**
 * @method getSoftnessDirLin
 * @return {float}
 */
getSoftnessDirLin : function (
)
{
    return 0;
},

/**
 * @method setSoftnessLimAng
 * @param {float} arg0
 */
setSoftnessLimAng : function (
float 
)
{
},

/**
 * @method getUseLinearReferenceFrameA
 * @return {bool}
 */
getUseLinearReferenceFrameA : function (
)
{
    return false;
},

/**
 * @method create
 * @param {cc.Physics3DRigidBody} arg0
 * @param {cc.Physics3DRigidBody} arg1
 * @param {mat4_object} arg2
 * @param {mat4_object} arg3
 * @param {bool} arg4
 * @return {cc.Physics3DSliderConstraint}
 */
create : function (
physics3drigidbody, 
physics3drigidbody, 
mat4, 
mat4, 
bool 
)
{
    return cc.Physics3DSliderConstraint;
},

/**
 * @method Physics3DSliderConstraint
 * @constructor
 */
Physics3DSliderConstraint : function (
)
{
},

};

/**
 * @class Physics3DConeTwistConstraint
 */
jsb.Physics3DConeTwistConstraint = {

/**
 * @method getBFrame
 * @return {mat4_object}
 */
getBFrame : function (
)
{
    return cc.Mat4;
},

/**
 * @method setFixThresh
 * @param {float} arg0
 */
setFixThresh : function (
float 
)
{
},

/**
 * @method getFrameOffsetB
 * @return {mat4_object}
 */
getFrameOffsetB : function (
)
{
    return cc.Mat4;
},

/**
 * @method getFrameOffsetA
 * @return {mat4_object}
 */
getFrameOffsetA : function (
)
{
    return cc.Mat4;
},

/**
 * @method getFixThresh
 * @return {float}
 */
getFixThresh : function (
)
{
    return 0;
},

/**
 * @method getSwingSpan2
 * @return {float}
 */
getSwingSpan2 : function (
)
{
    return 0;
},

/**
 * @method getSwingSpan1
 * @return {float}
 */
getSwingSpan1 : function (
)
{
    return 0;
},

/**
 * @method setMaxMotorImpulse
 * @param {float} arg0
 */
setMaxMotorImpulse : function (
float 
)
{
},

/**
 * @method setFrames
 * @param {mat4_object} arg0
 * @param {mat4_object} arg1
 */
setFrames : function (
mat4, 
mat4 
)
{
},

/**
 * @method getTwistAngle
 * @return {float}
 */
getTwistAngle : function (
)
{
    return 0;
},

/**
 * @method GetPointForAngle
 * @param {float} arg0
 * @param {float} arg1
 * @return {vec3_object}
 */
GetPointForAngle : function (
float, 
float 
)
{
    return cc.Vec3;
},

/**
 * @method setMaxMotorImpulseNormalized
 * @param {float} arg0
 */
setMaxMotorImpulseNormalized : function (
float 
)
{
},

/**
 * @method getTwistSpan
 * @return {float}
 */
getTwistSpan : function (
)
{
    return 0;
},

/**
 * @method setDamping
 * @param {float} arg0
 */
setDamping : function (
float 
)
{
},

/**
 * @method setLimit
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {float} arg3
 * @param {float} arg4
 * @param {float} arg5
 */
setLimit : function (
float, 
float, 
float, 
float, 
float, 
float 
)
{
},

/**
 * @method getAFrame
 * @return {mat4_object}
 */
getAFrame : function (
)
{
    return cc.Mat4;
},

/**
 * @method enableMotor
 * @param {bool} arg0
 */
enableMotor : function (
bool 
)
{
},

/**
 * @method create
* @param {cc.Physics3DRigidBody|cc.Physics3DRigidBody} physics3drigidbody
* @param {cc.Physics3DRigidBody|mat4_object} physics3drigidbody
* @param {mat4_object} mat4
* @param {mat4_object} mat4
* @return {cc.Physics3DConeTwistConstraint|cc.Physics3DConeTwistConstraint}
*/
create : function(
physics3drigidbody,
physics3drigidbody,
mat4,
mat4 
)
{
    return cc.Physics3DConeTwistConstraint;
},

/**
 * @method Physics3DConeTwistConstraint
 * @constructor
 */
Physics3DConeTwistConstraint : function (
)
{
},

};

/**
 * @class Physics3D6DofConstraint
 */
jsb.Physics3D6DofConstraint = {

/**
 * @method setLinearLowerLimit
 * @param {vec3_object} arg0
 */
setLinearLowerLimit : function (
vec3 
)
{
},

/**
 * @method getLinearLowerLimit
 * @return {vec3_object}
 */
getLinearLowerLimit : function (
)
{
    return cc.Vec3;
},

/**
 * @method getAngularUpperLimit
 * @return {vec3_object}
 */
getAngularUpperLimit : function (
)
{
    return cc.Vec3;
},

/**
 * @method getUseFrameOffset
 * @return {bool}
 */
getUseFrameOffset : function (
)
{
    return false;
},

/**
 * @method getLinearUpperLimit
 * @return {vec3_object}
 */
getLinearUpperLimit : function (
)
{
    return cc.Vec3;
},

/**
 * @method setAngularLowerLimit
 * @param {vec3_object} arg0
 */
setAngularLowerLimit : function (
vec3 
)
{
},

/**
 * @method isLimited
 * @param {int} arg0
 * @return {bool}
 */
isLimited : function (
int 
)
{
    return false;
},

/**
 * @method setUseFrameOffset
 * @param {bool} arg0
 */
setUseFrameOffset : function (
bool 
)
{
},

/**
 * @method setLinearUpperLimit
 * @param {vec3_object} arg0
 */
setLinearUpperLimit : function (
vec3 
)
{
},

/**
 * @method getAngularLowerLimit
 * @return {vec3_object}
 */
getAngularLowerLimit : function (
)
{
    return cc.Vec3;
},

/**
 * @method setAngularUpperLimit
 * @param {vec3_object} arg0
 */
setAngularUpperLimit : function (
vec3 
)
{
},

/**
 * @method create
* @param {cc.Physics3DRigidBody|cc.Physics3DRigidBody} physics3drigidbody
* @param {mat4_object|cc.Physics3DRigidBody} mat4
* @param {bool|mat4_object} bool
* @param {mat4_object} mat4
* @param {bool} bool
* @return {cc.Physics3D6DofConstraint|cc.Physics3D6DofConstraint}
*/
create : function(
physics3drigidbody,
physics3drigidbody,
mat4,
mat4,
bool 
)
{
    return cc.Physics3D6DofConstraint;
},

/**
 * @method Physics3D6DofConstraint
 * @constructor
 */
Physics3D6DofConstraint : function (
)
{
},

};
