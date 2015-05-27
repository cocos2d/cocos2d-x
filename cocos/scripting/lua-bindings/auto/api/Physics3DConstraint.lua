
--------------------------------
-- @module Physics3DConstraint
-- @extend Ref
-- @parent_module cc

--------------------------------
-- set enable or not
-- @function [parent=#Physics3DConstraint] setEnabled 
-- @param self
-- @param #bool enabled
-- @return Physics3DConstraint#Physics3DConstraint self (return value: cc.Physics3DConstraint)
        
--------------------------------
-- set the impulse that break the constraint
-- @function [parent=#Physics3DConstraint] setBreakingImpulse 
-- @param self
-- @param #float impulse
-- @return Physics3DConstraint#Physics3DConstraint self (return value: cc.Physics3DConstraint)
        
--------------------------------
-- get user data
-- @function [parent=#Physics3DConstraint] getUserData 
-- @param self
-- @return void#void ret (return value: void)
        
--------------------------------
-- get the impulse that break the constraint
-- @function [parent=#Physics3DConstraint] getBreakingImpulse 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get rigid body a
-- @function [parent=#Physics3DConstraint] getBodyA 
-- @param self
-- @return Physics3DRigidBody#Physics3DRigidBody ret (return value: cc.Physics3DRigidBody)
        
--------------------------------
-- is it enabled
-- @function [parent=#Physics3DConstraint] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- get override number of solver iterations
-- @function [parent=#Physics3DConstraint] getOverrideNumSolverIterations 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- get rigid body b
-- @function [parent=#Physics3DConstraint] getBodyB 
-- @param self
-- @return Physics3DRigidBody#Physics3DRigidBody ret (return value: cc.Physics3DRigidBody)
        
--------------------------------
-- override the number of constraint solver iterations used to solve this constraint, -1 will use the default number of iterations, as specified in SolverInfo.m_numIterations
-- @function [parent=#Physics3DConstraint] setOverrideNumSolverIterations 
-- @param self
-- @param #int overideNumIterations
-- @return Physics3DConstraint#Physics3DConstraint self (return value: cc.Physics3DConstraint)
        
--------------------------------
-- get constraint type
-- @function [parent=#Physics3DConstraint] getConstraintType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- get user data
-- @function [parent=#Physics3DConstraint] setUserData 
-- @param self
-- @param #void userData
-- @return Physics3DConstraint#Physics3DConstraint self (return value: cc.Physics3DConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DConstraint] getbtContraint 
-- @param self
-- @return btTypedConstraint#btTypedConstraint ret (return value: btTypedConstraint)
        
return nil
