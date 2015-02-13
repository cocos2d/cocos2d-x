
--------------------------------
-- @module PhysicsContactPreSolve
-- @parent_module cc

--------------------------------
--  get friction between two bodies
-- @function [parent=#PhysicsContactPreSolve] getFriction 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  get restitution between two bodies
-- @function [parent=#PhysicsContactPreSolve] getRestitution 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  set the friction
-- @function [parent=#PhysicsContactPreSolve] setFriction 
-- @param self
-- @param #float friction
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
--------------------------------
--  ignore the rest of the contact presolve and postsolve callbacks 
-- @function [parent=#PhysicsContactPreSolve] ignore 
-- @param self
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
--------------------------------
--  get surface velocity between two bodies
-- @function [parent=#PhysicsContactPreSolve] getSurfaceVelocity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  set the surface velocity
-- @function [parent=#PhysicsContactPreSolve] setSurfaceVelocity 
-- @param self
-- @param #vec2_table velocity
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
--------------------------------
--  set the restitution
-- @function [parent=#PhysicsContactPreSolve] setRestitution 
-- @param self
-- @param #float restitution
-- @return PhysicsContactPreSolve#PhysicsContactPreSolve self (return value: cc.PhysicsContactPreSolve)
        
return nil
