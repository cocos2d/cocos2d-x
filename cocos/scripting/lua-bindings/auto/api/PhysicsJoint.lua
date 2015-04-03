
--------------------------------
-- @module PhysicsJoint
-- @parent_module cc

--------------------------------
-- Get physics body a connected to this joint.
-- @function [parent=#PhysicsJoint] getBodyA 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- Get physics body b connected to this joint.
-- @function [parent=#PhysicsJoint] getBodyB 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
--  Get the max force setting. 
-- @function [parent=#PhysicsJoint] getMaxForce 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the max force between two bodies. 
-- @function [parent=#PhysicsJoint] setMaxForce 
-- @param self
-- @param #float force
-- @return PhysicsJoint#PhysicsJoint self (return value: cc.PhysicsJoint)
        
--------------------------------
--  Determines if the joint is enable. 
-- @function [parent=#PhysicsJoint] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Enable/Disable the joint. 
-- @function [parent=#PhysicsJoint] setEnable 
-- @param self
-- @param #bool enable
-- @return PhysicsJoint#PhysicsJoint self (return value: cc.PhysicsJoint)
        
--------------------------------
--  Enable/disable the collision between two bodies. 
-- @function [parent=#PhysicsJoint] setCollisionEnable 
-- @param self
-- @param #bool enable
-- @return PhysicsJoint#PhysicsJoint self (return value: cc.PhysicsJoint)
        
--------------------------------
-- Get the physics world.
-- @function [parent=#PhysicsJoint] getWorld 
-- @param self
-- @return PhysicsWorld#PhysicsWorld ret (return value: cc.PhysicsWorld)
        
--------------------------------
-- Set this joint's tag.<br>
-- param tag An interger number that identifies a PhysicsJoint.
-- @function [parent=#PhysicsJoint] setTag 
-- @param self
-- @param #int tag
-- @return PhysicsJoint#PhysicsJoint self (return value: cc.PhysicsJoint)
        
--------------------------------
--  Remove the joint from the world. 
-- @function [parent=#PhysicsJoint] removeFormWorld 
-- @param self
-- @return PhysicsJoint#PhysicsJoint self (return value: cc.PhysicsJoint)
        
--------------------------------
--  Determines if the collsion is enable. 
-- @function [parent=#PhysicsJoint] isCollisionEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get this joint's tag.<br>
-- return An interger number.
-- @function [parent=#PhysicsJoint] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
return nil
