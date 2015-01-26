
--------------------------------
-- @module PhysicsJointLimit
-- @extend PhysicsJoint
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] setAnchr2 
-- @param self
-- @param #vec2_table anchr2
-- @return PhysicsJointLimit#PhysicsJointLimit self (return value: cc.PhysicsJointLimit)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] setAnchr1 
-- @param self
-- @param #vec2_table anchr1
-- @return PhysicsJointLimit#PhysicsJointLimit self (return value: cc.PhysicsJointLimit)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] setMax 
-- @param self
-- @param #float max
-- @return PhysicsJointLimit#PhysicsJointLimit self (return value: cc.PhysicsJointLimit)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] getAnchr2 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] getAnchr1 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] createConstraints 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] getMin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] getMax 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJointLimit] setMin 
-- @param self
-- @param #float min
-- @return PhysicsJointLimit#PhysicsJointLimit self (return value: cc.PhysicsJointLimit)
        
--------------------------------
-- @overload self, cc.PhysicsBody, cc.PhysicsBody, vec2_table, vec2_table, float, float         
-- @overload self, cc.PhysicsBody, cc.PhysicsBody, vec2_table, vec2_table         
-- @function [parent=#PhysicsJointLimit] construct
-- @param self
-- @param #cc.PhysicsBody a
-- @param #cc.PhysicsBody b
-- @param #vec2_table anchr1
-- @param #vec2_table anchr2
-- @param #float min
-- @param #float max
-- @return PhysicsJointLimit#PhysicsJointLimit ret (return value: cc.PhysicsJointLimit)

return nil
