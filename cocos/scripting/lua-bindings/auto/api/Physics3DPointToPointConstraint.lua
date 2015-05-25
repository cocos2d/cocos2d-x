
--------------------------------
-- @module Physics3DPointToPointConstraint
-- @extend Physics3DConstraint
-- @parent_module cc

--------------------------------
-- get pivot point in A's local space
-- @function [parent=#Physics3DPointToPointConstraint] getPivotPointInA 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- get pivot point in B's local space
-- @function [parent=#Physics3DPointToPointConstraint] getPivotPointInB 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- set pivot point in A's local space
-- @function [parent=#Physics3DPointToPointConstraint] setPivotPointInA 
-- @param self
-- @param #vec3_table pivotA
-- @return Physics3DPointToPointConstraint#Physics3DPointToPointConstraint self (return value: cc.Physics3DPointToPointConstraint)
        
--------------------------------
-- set pivot point in B's local space
-- @function [parent=#Physics3DPointToPointConstraint] setPivotPointInB 
-- @param self
-- @param #vec3_table pivotB
-- @return Physics3DPointToPointConstraint#Physics3DPointToPointConstraint self (return value: cc.Physics3DPointToPointConstraint)
        
--------------------------------
-- @overload self, cc.Physics3DRigidBody, cc.Physics3DRigidBody, vec3_table, vec3_table         
-- @overload self, cc.Physics3DRigidBody, vec3_table         
-- @function [parent=#Physics3DPointToPointConstraint] create
-- @param self
-- @param #cc.Physics3DRigidBody rbA
-- @param #cc.Physics3DRigidBody rbB
-- @param #vec3_table pivotPointInA
-- @param #vec3_table pivotPointInB
-- @return Physics3DPointToPointConstraint#Physics3DPointToPointConstraint ret (return value: cc.Physics3DPointToPointConstraint)

--------------------------------
-- 
-- @function [parent=#Physics3DPointToPointConstraint] Physics3DPointToPointConstraint 
-- @param self
-- @return Physics3DPointToPointConstraint#Physics3DPointToPointConstraint self (return value: cc.Physics3DPointToPointConstraint)
        
return nil
