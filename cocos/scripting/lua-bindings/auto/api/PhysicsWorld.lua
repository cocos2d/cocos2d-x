
--------------------------------
-- @module PhysicsWorld
-- @parent_module cc

--------------------------------
--  set the gravity value 
-- @function [parent=#PhysicsWorld] setGravity 
-- @param self
-- @param #vec2_table gravity
        
--------------------------------
--  Get all the bodys that in the physics world. 
-- @function [parent=#PhysicsWorld] getAllBodies 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
--  get the bebug draw mask 
-- @function [parent=#PhysicsWorld] getDebugDrawMask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- To control the step of physics, if you want control it by yourself( fixed-timestep for example ), you can set this to false and call step by yourself.<br>
-- Defaut value is true.<br>
-- Note: if you set auto step to false, setSpeed and setUpdateRate won't work, you need to control the time step by yourself.
-- @function [parent=#PhysicsWorld] setAutoStep 
-- @param self
-- @param #bool autoStep
        
--------------------------------
--  Adds a joint to the physics world.
-- @function [parent=#PhysicsWorld] addJoint 
-- @param self
-- @param #cc.PhysicsJoint joint
        
--------------------------------
--  Remove all joints from physics world.
-- @function [parent=#PhysicsWorld] removeAllJoints 
-- @param self
        
--------------------------------
--  Get the auto step 
-- @function [parent=#PhysicsWorld] isAutoStep 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, int         
-- @overload self, cc.PhysicsBody         
-- @function [parent=#PhysicsWorld] removeBody
-- @param self
-- @param #cc.PhysicsBody body

--------------------------------
--  Remove a joint from physics world.
-- @function [parent=#PhysicsWorld] removeJoint 
-- @param self
-- @param #cc.PhysicsJoint joint
-- @param #bool destroy
        
--------------------------------
--  Get phsyics shapes that contains the point. 
-- @function [parent=#PhysicsWorld] getShapes 
-- @param self
-- @param #vec2_table point
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- The step for physics world, The times passing for simulate the physics.<br>
-- Note: you need to setAutoStep(false) first before it can work.
-- @function [parent=#PhysicsWorld] step 
-- @param self
-- @param #float delta
        
--------------------------------
--  set the debug draw mask 
-- @function [parent=#PhysicsWorld] setDebugDrawMask 
-- @param self
-- @param #int mask
        
--------------------------------
--  get the gravity value 
-- @function [parent=#PhysicsWorld] getGravity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- set the update rate of physics world, update rate is the value of EngineUpdateTimes/PhysicsWorldUpdateTimes.<br>
-- set it higher can improve performance, set it lower can improve accuracy of physics world simulation.<br>
-- default value is 1.0<br>
-- Note: if you setAutoStep(false), this won't work.
-- @function [parent=#PhysicsWorld] setUpdateRate 
-- @param self
-- @param #int rate
        
--------------------------------
--  get the speed of physics world 
-- @function [parent=#PhysicsWorld] getSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  get the update rate 
-- @function [parent=#PhysicsWorld] getUpdateRate 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Remove all bodies from physics world. 
-- @function [parent=#PhysicsWorld] removeAllBodies 
-- @param self
        
--------------------------------
-- Set the speed of physics world, speed is the rate at which the simulation executes. default value is 1.0<br>
-- Note: if you setAutoStep(false), this won't work.
-- @function [parent=#PhysicsWorld] setSpeed 
-- @param self
-- @param #float speed
        
--------------------------------
--  return physics shape that contains the point. 
-- @function [parent=#PhysicsWorld] getShape 
-- @param self
-- @param #vec2_table point
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
--  Get body by tag 
-- @function [parent=#PhysicsWorld] getBody 
-- @param self
-- @param #int tag
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
return nil
