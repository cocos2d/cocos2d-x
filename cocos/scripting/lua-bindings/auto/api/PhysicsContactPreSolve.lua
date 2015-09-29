
--------------------------------
-- @module PhysicsContactPreSolve
-- @parent_module cc

--------------------------------
--  Get friction between two bodies.
-- @function [parent=#PhysicsContactPreSolve] getFriction 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get restitution between two bodies.
-- @function [parent=#PhysicsContactPreSolve] getRestitution 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the friction.
-- @function [parent=#PhysicsContactPreSolve] setFriction 
-- @param self
-- @param #float friction
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
--------------------------------
--  Ignore the rest of the contact presolve and postsolve callbacks. 
-- @function [parent=#PhysicsContactPreSolve] ignore 
-- @param self
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
--------------------------------
--  Get surface velocity between two bodies.
-- @function [parent=#PhysicsContactPreSolve] getSurfaceVelocity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Set the surface velocity.
-- @function [parent=#PhysicsContactPreSolve] setSurfaceVelocity 
-- @param self
-- @param #vec2_table velocity
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
--------------------------------
--  Set the restitution.
-- @function [parent=#PhysicsContactPreSolve] setRestitution 
-- @param self
-- @param #float restitution
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
return nil
