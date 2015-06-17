
--------------------------------
-- @module PhysicsJointMotor
-- @extend PhysicsJoint
-- @parent_module cc

--------------------------------
--  Set the relative angular velocity.
-- @function [parent=#PhysicsJointMotor] setRate 
-- @param self
-- @param #float rate
-- @return PhysicsJointMotor#PhysicsJointMotor self (return value: cc.PhysicsJointMotor)
        
--------------------------------
--  Get the relative angular velocity.
-- @function [parent=#PhysicsJointMotor] getRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointMotor] createConstraints 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Create a motor joint.<br>
-- param a A is the body to connect.<br>
-- param b B is the body to connect.<br>
-- param rate Rate is the desired relative angular velocity.<br>
-- return A object pointer.
-- @function [parent=#PhysicsJointMotor] construct 
-- @param self
-- @param #cc.PhysicsBody a
-- @param #cc.PhysicsBody b
-- @param #float rate
-- @return PhysicsJointMotor#PhysicsJointMotor ret (return value: cc.PhysicsJointMotor)
        
return nil
