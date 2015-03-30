
--------------------------------
-- @module PhysicsJointRotarySpring
-- @extend PhysicsJoint
-- @parent_module cc

--------------------------------
--  Get the spring soft constant.
-- @function [parent=#PhysicsJointRotarySpring] getDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the relative angle in radians from the body a to b.
-- @function [parent=#PhysicsJointRotarySpring] setRestAngle 
-- @param self
-- @param #float restAngle
-- @return PhysicsJointRotarySpring#PhysicsJointRotarySpring self (return value: cc.PhysicsJointRotarySpring)
        
--------------------------------
--  Get the spring constant.
-- @function [parent=#PhysicsJointRotarySpring] getStiffness 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointRotarySpring] createConstraints 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Set the spring constant.
-- @function [parent=#PhysicsJointRotarySpring] setStiffness 
-- @param self
-- @param #float stiffness
-- @return PhysicsJointRotarySpring#PhysicsJointRotarySpring self (return value: cc.PhysicsJointRotarySpring)
        
--------------------------------
--  Set the spring soft constant.
-- @function [parent=#PhysicsJointRotarySpring] setDamping 
-- @param self
-- @param #float damping
-- @return PhysicsJointRotarySpring#PhysicsJointRotarySpring self (return value: cc.PhysicsJointRotarySpring)
        
--------------------------------
--  Get the relative angle in radians from the body a to b.
-- @function [parent=#PhysicsJointRotarySpring] getRestAngle 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Create a damped rotary spring joint.<br>
-- param a A is the body to connect.<br>
-- param b B is the body to connect.<br>
-- param stiffness It's the spring constant.<br>
-- param damping It's how soft to make the damping of the spring.<br>
-- return A object pointer.
-- @function [parent=#PhysicsJointRotarySpring] construct 
-- @param self
-- @param #cc.PhysicsBody a
-- @param #cc.PhysicsBody b
-- @param #float stiffness
-- @param #float damping
-- @return PhysicsJointRotarySpring#PhysicsJointRotarySpring ret (return value: cc.PhysicsJointRotarySpring)
        
return nil
