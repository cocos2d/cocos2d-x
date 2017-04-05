
--------------------------------
-- @module PhysicsSprite3D
-- @extend Sprite3D
-- @parent_module cc

--------------------------------
--  synchronize node transformation to physics. 
-- @function [parent=#PhysicsSprite3D] syncNodeToPhysics 
-- @param self
-- @return PhysicsSprite3D#PhysicsSprite3D self (return value: cc.PhysicsSprite3D)
        
--------------------------------
--  synchronize physics transformation to node. 
-- @function [parent=#PhysicsSprite3D] syncPhysicsToNode 
-- @param self
-- @return PhysicsSprite3D#PhysicsSprite3D self (return value: cc.PhysicsSprite3D)
        
--------------------------------
--  Get the Physics3DObject. 
-- @function [parent=#PhysicsSprite3D] getPhysicsObj 
-- @param self
-- @return Physics3DObject#Physics3DObject ret (return value: cc.Physics3DObject)
        
--------------------------------
--  Set synchronization flag, see Physics3DComponent. 
-- @function [parent=#PhysicsSprite3D] setSyncFlag 
-- @param self
-- @param #int syncFlag
-- @return PhysicsSprite3D#PhysicsSprite3D self (return value: cc.PhysicsSprite3D)
        
--------------------------------
-- 
-- @function [parent=#PhysicsSprite3D] PhysicsSprite3D 
-- @param self
-- @return PhysicsSprite3D#PhysicsSprite3D self (return value: cc.PhysicsSprite3D)
        
return nil
