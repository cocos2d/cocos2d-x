
--------------------------------
-- @module PhysicsManager
-- @parent_module cc

--------------------------------
-- Remove a physics component from `PhysiscsManager`. Will remove physics component's physics<br>
-- body from the physics world managed by this `PhysicsManager`.
-- @function [parent=#PhysicsManager] removePhysicsComponent 
-- @param self
-- @param #cc.ComponentPhysics2d componentPhsics2d
-- @return PhysicsManager#PhysicsManager self (return value: cc.PhysicsManager)
        
--------------------------------
-- Add a physics component to be managed by the `PhysicsManager`. Will register physics <br>
-- component's physics body to physics world managed by this `PhysicsManager`.<br>
-- param componentPhsics2d The physics component to be managed by this `PhysicsManager`.
-- @function [parent=#PhysicsManager] addPhysicsComponent 
-- @param self
-- @param #cc.ComponentPhysics2d componentPhsics2d
-- @return PhysicsManager#PhysicsManager self (return value: cc.PhysicsManager)
        
--------------------------------
-- Get the physics world.<br>
-- return Physics world managed by this `PhysicsManager`.
-- @function [parent=#PhysicsManager] getPhysicsWorld 
-- @param self
-- @return PhysicsWorld#PhysicsWorld ret (return value: cc.PhysicsWorld)
        
--------------------------------
-- Create a PhysicsManager with `Scene`. `Scene` will create it automatically,<br>
-- so don't create it yourself.<br>
-- scene The scene this `PhysicsManager` belongs to.
-- @function [parent=#PhysicsManager] PhysicsManager 
-- @param self
-- @param #cc.Scene scene
-- @return PhysicsManager#PhysicsManager self (return value: cc.PhysicsManager)
        
return nil
