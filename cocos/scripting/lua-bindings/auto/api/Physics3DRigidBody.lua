
--------------------------------
-- @module Physics3DRigidBody
-- @extend Physics3DObject
-- @parent_module cc

--------------------------------
--  Set the acceleration. 
-- @function [parent=#Physics3DRigidBody] setGravity 
-- @param self
-- @param #vec3_table acceleration
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Get friction. 
-- @function [parent=#Physics3DRigidBody] getFriction 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, float         
-- @overload self, vec3_table         
-- @function [parent=#Physics3DRigidBody] setAngularFactor
-- @param self
-- @param #vec3_table angFac
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)

--------------------------------
-- 
-- @function [parent=#Physics3DRigidBody] addConstraint 
-- @param self
-- @param #cc.Physics3DConstraint constraint
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Get the pointer of btRigidBody. 
-- @function [parent=#Physics3DRigidBody] getRigidBody 
-- @param self
-- @return btRigidBody#btRigidBody ret (return value: btRigidBody)
        
--------------------------------
--  Get total force. 
-- @function [parent=#Physics3DRigidBody] getTotalForce 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Get the total number of constraints. 
-- @function [parent=#Physics3DRigidBody] getConstraintCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Apply a central force.<br>
-- param   force the value of the force
-- @function [parent=#Physics3DRigidBody] applyCentralForce 
-- @param self
-- @param #vec3_table force
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set mass and inertia. 
-- @function [parent=#Physics3DRigidBody] setMassProps 
-- @param self
-- @param #float mass
-- @param #vec3_table inertia
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set friction. 
-- @function [parent=#Physics3DRigidBody] setFriction 
-- @param self
-- @param #float frict
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set kinematic object. 
-- @function [parent=#Physics3DRigidBody] setKinematic 
-- @param self
-- @param #bool kinematic
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set linear damping and angular damping. 
-- @function [parent=#Physics3DRigidBody] setDamping 
-- @param self
-- @param #float lin_damping
-- @param #float ang_damping
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
-- Apply a impulse.<br>
-- param   impulse the value of the impulse<br>
-- param   rel_pos the position of the impulse
-- @function [parent=#Physics3DRigidBody] applyImpulse 
-- @param self
-- @param #vec3_table impulse
-- @param #vec3_table rel_pos
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Check rigid body is kinematic object. 
-- @function [parent=#Physics3DRigidBody] isKinematic 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Apply a torque.<br>
-- param   torque the value of the torque
-- @function [parent=#Physics3DRigidBody] applyTorque 
-- @param self
-- @param #vec3_table torque
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set motion threshold, don't do continuous collision detection if the motion (in one step) is less then ccdMotionThreshold 
-- @function [parent=#Physics3DRigidBody] setCcdMotionThreshold 
-- @param self
-- @param #float ccdMotionThreshold
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set rolling friction. 
-- @function [parent=#Physics3DRigidBody] setRollingFriction 
-- @param self
-- @param #float frict
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Get motion threshold. 
-- @function [parent=#Physics3DRigidBody] getCcdMotionThreshold 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get the linear factor. 
-- @function [parent=#Physics3DRigidBody] getLinearFactor 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Damps the velocity, using the given linearDamping and angularDamping. 
-- @function [parent=#Physics3DRigidBody] applyDamping 
-- @param self
-- @param #float timeStep
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Get the angular velocity. 
-- @function [parent=#Physics3DRigidBody] getAngularVelocity 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- 
-- @function [parent=#Physics3DRigidBody] init 
-- @param self
-- @param #cc.Physics3DRigidBodyDes info
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Apply a torque impulse.<br>
-- param   torque the value of the torque
-- @function [parent=#Physics3DRigidBody] applyTorqueImpulse 
-- @param self
-- @param #vec3_table torque
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Active or inactive. 
-- @function [parent=#Physics3DRigidBody] setActive 
-- @param self
-- @param #bool active
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set the linear factor. 
-- @function [parent=#Physics3DRigidBody] setLinearFactor 
-- @param self
-- @param #vec3_table linearFactor
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set the linear velocity. 
-- @function [parent=#Physics3DRigidBody] setLinearVelocity 
-- @param self
-- @param #vec3_table lin_vel
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Get the linear velocity. 
-- @function [parent=#Physics3DRigidBody] getLinearVelocity 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Set swept sphere radius. 
-- @function [parent=#Physics3DRigidBody] setCcdSweptSphereRadius 
-- @param self
-- @param #float radius
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
-- Apply a force.<br>
-- param   force the value of the force<br>
-- param   rel_pos the position of the force
-- @function [parent=#Physics3DRigidBody] applyForce 
-- @param self
-- @param #vec3_table force
-- @param #vec3_table rel_pos
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set the angular velocity. 
-- @function [parent=#Physics3DRigidBody] setAngularVelocity 
-- @param self
-- @param #vec3_table ang_vel
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
-- Apply a central impulse.<br>
-- param   impulse the value of the impulse
-- @function [parent=#Physics3DRigidBody] applyCentralImpulse 
-- @param self
-- @param #vec3_table impulse
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Get the acceleration. 
-- @function [parent=#Physics3DRigidBody] getGravity 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Get rolling friction. 
-- @function [parent=#Physics3DRigidBody] getRollingFriction 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the center of mass. 
-- @function [parent=#Physics3DRigidBody] setCenterOfMassTransform 
-- @param self
-- @param #mat4_table xform
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set the inverse of local inertia. 
-- @function [parent=#Physics3DRigidBody] setInvInertiaDiagLocal 
-- @param self
-- @param #vec3_table diagInvInertia
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
-- @overload self, unsigned int         
-- @overload self, cc.Physics3DConstraint         
-- @function [parent=#Physics3DRigidBody] removeConstraint
-- @param self
-- @param #cc.Physics3DConstraint constraint
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)

--------------------------------
--  Get total torque. 
-- @function [parent=#Physics3DRigidBody] getTotalTorque 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Get inverse of mass. 
-- @function [parent=#Physics3DRigidBody] getInvMass 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get constraint by index. 
-- @function [parent=#Physics3DRigidBody] getConstraint 
-- @param self
-- @param #unsigned int idx
-- @return Physics3DConstraint#Physics3DConstraint ret (return value: cc.Physics3DConstraint)
        
--------------------------------
--  Get restitution. 
-- @function [parent=#Physics3DRigidBody] getRestitution 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get swept sphere radius. 
-- @function [parent=#Physics3DRigidBody] getCcdSweptSphereRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get hit friction. 
-- @function [parent=#Physics3DRigidBody] getHitFraction 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get angular damping. 
-- @function [parent=#Physics3DRigidBody] getAngularDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get the inverse of local inertia. 
-- @function [parent=#Physics3DRigidBody] getInvInertiaDiagLocal 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Get the center of mass. 
-- @function [parent=#Physics3DRigidBody] getCenterOfMassTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
--  Get the angular factor. 
-- @function [parent=#Physics3DRigidBody] getAngularFactor 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Set restitution. 
-- @function [parent=#Physics3DRigidBody] setRestitution 
-- @param self
-- @param #float rest
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Set hit friction. 
-- @function [parent=#Physics3DRigidBody] setHitFraction 
-- @param self
-- @param #float hitFraction
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
--------------------------------
--  Get linear damping. 
-- @function [parent=#Physics3DRigidBody] getLinearDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  override. 
-- @function [parent=#Physics3DRigidBody] getWorldTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- 
-- @function [parent=#Physics3DRigidBody] Physics3DRigidBody 
-- @param self
-- @return Physics3DRigidBody#Physics3DRigidBody self (return value: cc.Physics3DRigidBody)
        
return nil
