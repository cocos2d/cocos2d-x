
--------------------------------
-- @module PhysicsWorld
-- @parent_module cc

--------------------------------
-- @function [parent=#PhysicsWorld] getGravity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsWorld] getAllBodies 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#PhysicsWorld] setGravity 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#PhysicsWorld] getSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, int         
-- @overload self, cc.PhysicsBody         
-- @function [parent=#PhysicsWorld] removeBody
-- @param self
-- @param #cc.PhysicsBody physicsbody

--------------------------------
-- @function [parent=#PhysicsWorld] removeJoint 
-- @param self
-- @param #cc.PhysicsJoint physicsjoint
-- @param #bool bool
        
--------------------------------
-- @function [parent=#PhysicsWorld] getUpdateRate 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsWorld] setSpeed 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsWorld] getShapes 
-- @param self
-- @param #vec2_table vec2
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#PhysicsWorld] removeAllJoints 
-- @param self
        
--------------------------------
-- @function [parent=#PhysicsWorld] getShape 
-- @param self
-- @param #vec2_table vec2
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
-- @function [parent=#PhysicsWorld] removeAllBodies 
-- @param self
        
--------------------------------
-- @function [parent=#PhysicsWorld] getDebugDrawMask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsWorld] setDebugDrawMask 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#PhysicsWorld] getBody 
-- @param self
-- @param #int int
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- @function [parent=#PhysicsWorld] setUpdateRate 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#PhysicsWorld] addJoint 
-- @param self
-- @param #cc.PhysicsJoint physicsjoint
        
return nil
