
--------------------------------
-- @module Physics3DHingeConstraint
-- @extend Physics3DConstraint
-- @parent_module cc

--------------------------------
-- @overload self, mat4_table, mat4_table         
-- @overload self         
-- @function [parent=#Physics3DHingeConstraint] getHingeAngle
-- @param self
-- @param #mat4_table transA
-- @param #mat4_table transB
-- @return float#float ret (return value: float)

--------------------------------
-- get motor target velocity
-- @function [parent=#Physics3DHingeConstraint] getMotorTargetVelosity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get rigid body A's frame offset
-- @function [parent=#Physics3DHingeConstraint] getFrameOffsetA 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- get rigid body B's frame offset
-- @function [parent=#Physics3DHingeConstraint] getFrameOffsetB 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
--  set max motor impulse 
-- @function [parent=#Physics3DHingeConstraint] setMaxMotorImpulse 
-- @param self
-- @param #float maxMotorImpulse
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
--  enable angular motor 
-- @function [parent=#Physics3DHingeConstraint] enableAngularMotor 
-- @param self
-- @param #bool enableMotor
-- @param #float targetVelocity
-- @param #float maxMotorImpulse
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
-- get upper limit
-- @function [parent=#Physics3DHingeConstraint] getUpperLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get max motor impulse
-- @function [parent=#Physics3DHingeConstraint] getMaxMotorImpulse 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get lower limit
-- @function [parent=#Physics3DHingeConstraint] getLowerLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- set use frame offset
-- @function [parent=#Physics3DHingeConstraint] setUseFrameOffset 
-- @param self
-- @param #bool frameOffsetOnOff
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
-- get enable angular motor
-- @function [parent=#Physics3DHingeConstraint] getEnableAngularMotor 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DHingeConstraint] enableMotor 
-- @param self
-- @param #bool enableMotor
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
-- get B's frame
-- @function [parent=#Physics3DHingeConstraint] getBFrame 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- set frames for rigid body A and B
-- @function [parent=#Physics3DHingeConstraint] setFrames 
-- @param self
-- @param #mat4_table frameA
-- @param #mat4_table frameB
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
--  access for UseFrameOffset
-- @function [parent=#Physics3DHingeConstraint] getUseFrameOffset 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set angular only
-- @function [parent=#Physics3DHingeConstraint] setAngularOnly 
-- @param self
-- @param #bool angularOnly
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
--  set limit 
-- @function [parent=#Physics3DHingeConstraint] setLimit 
-- @param self
-- @param #float low
-- @param #float high
-- @param #float _softness
-- @param #float _biasFactor
-- @param #float _relaxationFactor
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
-- get angular only
-- @function [parent=#Physics3DHingeConstraint] getAngularOnly 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set axis
-- @function [parent=#Physics3DHingeConstraint] setAxis 
-- @param self
-- @param #vec3_table axisInA
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
--------------------------------
-- get A's frame 
-- @function [parent=#Physics3DHingeConstraint] getAFrame 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @overload self, cc.Physics3DRigidBody, vec3_table, vec3_table, bool         
-- @overload self, cc.Physics3DRigidBody, mat4_table, bool         
-- @overload self, cc.Physics3DRigidBody, cc.Physics3DRigidBody, vec3_table, vec3_table, vec3_table, vec3_table, bool         
-- @overload self, cc.Physics3DRigidBody, cc.Physics3DRigidBody, mat4_table, mat4_table, bool         
-- @function [parent=#Physics3DHingeConstraint] create
-- @param self
-- @param #cc.Physics3DRigidBody rbA
-- @param #cc.Physics3DRigidBody rbB
-- @param #vec3_table pivotInA
-- @param #vec3_table pivotInB
-- @param #vec3_table axisInA
-- @param #vec3_table axisInB
-- @param #bool useReferenceFrameA
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint ret (return value: cc.Physics3DHingeConstraint)

--------------------------------
-- 
-- @function [parent=#Physics3DHingeConstraint] Physics3DHingeConstraint 
-- @param self
-- @return Physics3DHingeConstraint#Physics3DHingeConstraint self (return value: cc.Physics3DHingeConstraint)
        
return nil
