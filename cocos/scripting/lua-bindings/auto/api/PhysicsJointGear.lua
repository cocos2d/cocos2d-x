
--------------------------------
-- @module PhysicsJointGear
-- @extend PhysicsJoint
-- @parent_module cc

--------------------------------
--  Set the ratio.
-- @function [parent=#PhysicsJointGear] setRatio 
-- @param self
-- @param #float ratchet
-- @return PhysicsJointGear#PhysicsJointGear self (return value: cc.PhysicsJointGear)
        
--------------------------------
--  Get the angular offset of the two bodies.
-- @function [parent=#PhysicsJointGear] getPhase 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the angular offset of the two bodies.
-- @function [parent=#PhysicsJointGear] setPhase 
-- @param self
-- @param #float phase
-- @return PhysicsJointGear#PhysicsJointGear self (return value: cc.PhysicsJointGear)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointGear] createConstraints 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Get the ratio.
-- @function [parent=#PhysicsJointGear] getRatio 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Create a gear joint.<br>
-- param a A is the body to connect.<br>
-- param b B is the body to connect.<br>
-- param phase Phase is the initial angular offset of the two bodies.<br>
-- param ratio Ratio is always measured in absolute terms.<br>
-- return A object pointer.
-- @function [parent=#PhysicsJointGear] construct 
-- @param self
-- @param #cc.PhysicsBody a
-- @param #cc.PhysicsBody b
-- @param #float phase
-- @param #float ratio
-- @return PhysicsJointGear#PhysicsJointGear ret (return value: cc.PhysicsJointGear)
        
return nil
