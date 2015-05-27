
--------------------------------
-- @module Physics3D6DofConstraint
-- @extend Physics3DConstraint
-- @parent_module cc

--------------------------------
-- set linear lower limit
-- @function [parent=#Physics3D6DofConstraint] setLinearLowerLimit 
-- @param self
-- @param #vec3_table linearLower
-- @return Physics3D6DofConstraint#Physics3D6DofConstraint self (return value: cc.Physics3D6DofConstraint)
        
--------------------------------
-- get linear lower limit
-- @function [parent=#Physics3D6DofConstraint] getLinearLowerLimit 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- get angular upper limit
-- @function [parent=#Physics3D6DofConstraint] getAngularUpperLimit 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  access for UseFrameOffset
-- @function [parent=#Physics3D6DofConstraint] getUseFrameOffset 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- get linear upper limit
-- @function [parent=#Physics3D6DofConstraint] getLinearUpperLimit 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- set angular lower limit
-- @function [parent=#Physics3D6DofConstraint] setAngularLowerLimit 
-- @param self
-- @param #vec3_table angularLower
-- @return Physics3D6DofConstraint#Physics3D6DofConstraint self (return value: cc.Physics3D6DofConstraint)
        
--------------------------------
-- is limited?<br>
-- param limitIndex first 3 are linear, next 3 are angular
-- @function [parent=#Physics3D6DofConstraint] isLimited 
-- @param self
-- @param #int limitIndex
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set use frame offset
-- @function [parent=#Physics3D6DofConstraint] setUseFrameOffset 
-- @param self
-- @param #bool frameOffsetOnOff
-- @return Physics3D6DofConstraint#Physics3D6DofConstraint self (return value: cc.Physics3D6DofConstraint)
        
--------------------------------
-- set linear upper limit
-- @function [parent=#Physics3D6DofConstraint] setLinearUpperLimit 
-- @param self
-- @param #vec3_table linearUpper
-- @return Physics3D6DofConstraint#Physics3D6DofConstraint self (return value: cc.Physics3D6DofConstraint)
        
--------------------------------
-- get angular lower limit
-- @function [parent=#Physics3D6DofConstraint] getAngularLowerLimit 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- set angular upper limit
-- @function [parent=#Physics3D6DofConstraint] setAngularUpperLimit 
-- @param self
-- @param #vec3_table angularUpper
-- @return Physics3D6DofConstraint#Physics3D6DofConstraint self (return value: cc.Physics3D6DofConstraint)
        
--------------------------------
-- @overload self, cc.Physics3DRigidBody, mat4_table, bool         
-- @overload self, cc.Physics3DRigidBody, cc.Physics3DRigidBody, mat4_table, mat4_table, bool         
-- @function [parent=#Physics3D6DofConstraint] create
-- @param self
-- @param #cc.Physics3DRigidBody rbA
-- @param #cc.Physics3DRigidBody rbB
-- @param #mat4_table frameInA
-- @param #mat4_table frameInB
-- @param #bool useLinearReferenceFrameA
-- @return Physics3D6DofConstraint#Physics3D6DofConstraint ret (return value: cc.Physics3D6DofConstraint)

--------------------------------
-- 
-- @function [parent=#Physics3D6DofConstraint] Physics3D6DofConstraint 
-- @param self
-- @return Physics3D6DofConstraint#Physics3D6DofConstraint self (return value: cc.Physics3D6DofConstraint)
        
return nil
