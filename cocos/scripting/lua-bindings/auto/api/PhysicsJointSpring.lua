
--------------------------------
-- @module PhysicsJointSpring
-- @extend PhysicsJoint
-- @parent_module cc

--------------------------------
--  Set the anchor point on body b.
-- @function [parent=#PhysicsJointSpring] setAnchr2 
-- @param self
-- @param #vec2_table anchr2
-- @return PhysicsJointSpring#PhysicsJointSpring self (return value: cc.PhysicsJointSpring)
        
--------------------------------
--  Set the anchor point on body a.
-- @function [parent=#PhysicsJointSpring] setAnchr1 
-- @param self
-- @param #vec2_table anchr1
-- @return PhysicsJointSpring#PhysicsJointSpring self (return value: cc.PhysicsJointSpring)
        
--------------------------------
--  Get the spring soft constant.
-- @function [parent=#PhysicsJointSpring] getDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the spring constant.
-- @function [parent=#PhysicsJointSpring] setStiffness 
-- @param self
-- @param #float stiffness
-- @return PhysicsJointSpring#PhysicsJointSpring self (return value: cc.PhysicsJointSpring)
        
--------------------------------
--  Get the distance of the anchor points.
-- @function [parent=#PhysicsJointSpring] getRestLength 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get the anchor point on body b.
-- @function [parent=#PhysicsJointSpring] getAnchr2 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get the anchor point on body a.
-- @function [parent=#PhysicsJointSpring] getAnchr1 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get the spring constant.
-- @function [parent=#PhysicsJointSpring] getStiffness 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointSpring] createConstraints 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Set the distance of the anchor points.
-- @function [parent=#PhysicsJointSpring] setRestLength 
-- @param self
-- @param #float restLength
-- @return PhysicsJointSpring#PhysicsJointSpring self (return value: cc.PhysicsJointSpring)
        
--------------------------------
--  Set the spring soft constant.
-- @function [parent=#PhysicsJointSpring] setDamping 
-- @param self
-- @param #float damping
-- @return PhysicsJointSpring#PhysicsJointSpring self (return value: cc.PhysicsJointSpring)
        
--------------------------------
--  Create a fixed distance joint.<br>
-- param a A is the body to connect.<br>
-- param b B is the body to connect.<br>
-- param anchr1 Anchr1 is the anchor point on body a.<br>
-- param anchr2 Anchr2 is the anchor point on body b.<br>
-- param stiffness It's the spring constant.<br>
-- param damping It's how soft to make the damping of the spring.<br>
-- return A object pointer.
-- @function [parent=#PhysicsJointSpring] construct 
-- @param self
-- @param #cc.PhysicsBody a
-- @param #cc.PhysicsBody b
-- @param #vec2_table anchr1
-- @param #vec2_table anchr2
-- @param #float stiffness
-- @param #float damping
-- @return PhysicsJointSpring#PhysicsJointSpring ret (return value: cc.PhysicsJointSpring)
        
return nil
