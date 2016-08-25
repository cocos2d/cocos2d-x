
--------------------------------
-- @module PhysicsJointDistance
-- @extend PhysicsJoint
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#PhysicsJointDistance] createConstraints 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Set the distance of the anchor points.
-- @function [parent=#PhysicsJointDistance] setDistance 
-- @param self
-- @param #float distance
-- @return PhysicsJointDistance#PhysicsJointDistance self (return value: cc.PhysicsJointDistance)
        
--------------------------------
--  Get the distance of the anchor points.
-- @function [parent=#PhysicsJointDistance] getDistance 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Create a fixed distance joint.<br>
-- param a A is the body to connect.<br>
-- param b B is the body to connect.<br>
-- param anchr1 Anchr1 is the anchor point on body a.<br>
-- param anchr2 Anchr2 is the anchor point on body b.<br>
-- return A object pointer.
-- @function [parent=#PhysicsJointDistance] construct 
-- @param self
-- @param #cc.PhysicsBody a
-- @param #cc.PhysicsBody b
-- @param #vec2_table anchr1
-- @param #vec2_table anchr2
-- @return PhysicsJointDistance#PhysicsJointDistance ret (return value: cc.PhysicsJointDistance)
        
return nil
