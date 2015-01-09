
--------------------------------
-- @module PhysicsJoint
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#PhysicsJoint] getBodyA 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJoint] getBodyB 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
--  Get the max force setting 
-- @function [parent=#PhysicsJoint] getMaxForce 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the max force between two bodies 
-- @function [parent=#PhysicsJoint] setMaxForce 
-- @param self
-- @param #float force
        
--------------------------------
-- 
-- @function [parent=#PhysicsJoint] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Enable/Disable the joint 
-- @function [parent=#PhysicsJoint] setEnable 
-- @param self
-- @param #bool enable
        
--------------------------------
--  Enable/disable the collision between two bodies 
-- @function [parent=#PhysicsJoint] setCollisionEnable 
-- @param self
-- @param #bool enable
        
--------------------------------
-- 
-- @function [parent=#PhysicsJoint] getWorld 
-- @param self
-- @return PhysicsWorld#PhysicsWorld ret (return value: cc.PhysicsWorld)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJoint] setTag 
-- @param self
-- @param #int tag
        
--------------------------------
--  Remove the joint from the world 
-- @function [parent=#PhysicsJoint] removeFormWorld 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#PhysicsJoint] isCollisionEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PhysicsJoint] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
return nil
