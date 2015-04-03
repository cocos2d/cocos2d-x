
--------------------------------
-- @module PhysicsJointGroove
-- @extend PhysicsJoint
-- @parent_module cc

--------------------------------
--  Set the anchor point on body b.
-- @function [parent=#PhysicsJointGroove] setAnchr2 
-- @param self
-- @param #vec2_table anchr2
-- @return PhysicsJointGroove#PhysicsJointGroove self (return value: cc.PhysicsJointGroove)
        
--------------------------------
--  Set the line begin position
-- @function [parent=#PhysicsJointGroove] setGrooveA 
-- @param self
-- @param #vec2_table grooveA
-- @return PhysicsJointGroove#PhysicsJointGroove self (return value: cc.PhysicsJointGroove)
        
--------------------------------
--  Set the line end position
-- @function [parent=#PhysicsJointGroove] setGrooveB 
-- @param self
-- @param #vec2_table grooveB
-- @return PhysicsJointGroove#PhysicsJointGroove self (return value: cc.PhysicsJointGroove)
        
--------------------------------
--  Get the line begin position
-- @function [parent=#PhysicsJointGroove] getGrooveA 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get the line end position
-- @function [parent=#PhysicsJointGroove] getGrooveB 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get the anchor point on body b.
-- @function [parent=#PhysicsJointGroove] getAnchr2 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointGroove] createConstraints 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Create a groove joint.<br>
-- param a A is the body to connect.<br>
-- param b B is the body to connect.<br>
-- param grooveA The line begin position.<br>
-- param grooveB The line end position.<br>
-- param anchr2 Anchr2 is the anchor point on body b.<br>
-- return A object pointer.
-- @function [parent=#PhysicsJointGroove] construct 
-- @param self
-- @param #cc.PhysicsBody a
-- @param #cc.PhysicsBody b
-- @param #vec2_table grooveA
-- @param #vec2_table grooveB
-- @param #vec2_table anchr2
-- @return PhysicsJointGroove#PhysicsJointGroove ret (return value: cc.PhysicsJointGroove)
        
return nil
