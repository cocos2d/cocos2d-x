
--------------------------------
-- @module Physics3DWorld
-- @extend Ref
-- @parent_module cc

--------------------------------
--  set gravity for the physics world 
-- @function [parent=#Physics3DWorld] setGravity 
-- @param self
-- @param #vec3_table gravity
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Simulate one frame. 
-- @function [parent=#Physics3DWorld] stepSimulate 
-- @param self
-- @param #float dt
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
-- 
-- @function [parent=#Physics3DWorld] needCollisionChecking 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DWorld] collisionChecking 
-- @param self
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Remove all Physics3DObjects. 
-- @function [parent=#Physics3DWorld] removeAllPhysics3DObjects 
-- @param self
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Check debug drawing is enabled. 
-- @function [parent=#Physics3DWorld] isDebugDrawEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Remove all Physics3DConstraint. 
-- @function [parent=#Physics3DWorld] removeAllPhysics3DConstraints 
-- @param self
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  get current gravity 
-- @function [parent=#Physics3DWorld] getGravity 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  Remove a Physics3DConstraint. 
-- @function [parent=#Physics3DWorld] removePhysics3DConstraint 
-- @param self
-- @param #cc.Physics3DConstraint constraint
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Add a Physics3DObject. 
-- @function [parent=#Physics3DWorld] addPhysics3DObject 
-- @param self
-- @param #cc.Physics3DObject physicsObj
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Enable or disable debug drawing. 
-- @function [parent=#Physics3DWorld] setDebugDrawEnable 
-- @param self
-- @param #bool enableDebugDraw
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Remove a Physics3DObject. 
-- @function [parent=#Physics3DWorld] removePhysics3DObject 
-- @param self
-- @param #cc.Physics3DObject physicsObj
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Add a Physics3DConstraint. 
-- @function [parent=#Physics3DWorld] addPhysics3DConstraint 
-- @param self
-- @param #cc.Physics3DConstraint constraint
-- @param #bool disableCollisionsBetweenLinkedObjs
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
--  Internal method, the updater of debug drawing, need called each frame. 
-- @function [parent=#Physics3DWorld] debugDraw 
-- @param self
-- @param #cc.Renderer renderer
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
--------------------------------
-- 
-- @function [parent=#Physics3DWorld] Physics3DWorld 
-- @param self
-- @return Physics3DWorld#Physics3DWorld self (return value: cc.Physics3DWorld)
        
return nil
