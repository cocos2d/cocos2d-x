
--------------------------------
-- @module PhysicsWorld
-- @parent_module cc

--------------------------------
-- set the gravity value of this physics world.<br>
-- param gravity A gravity value of this physics world.
-- @function [parent=#PhysicsWorld] setGravity 
-- @param self
-- @param #vec2_table gravity
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Get all the bodies that in this physics world.<br>
-- return A Vector<PhysicsBody*>& object contains all bodies in this physics world. 
-- @function [parent=#PhysicsWorld] getAllBodies 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- set the number of update of the physics world in a second.<br>
-- 0 - disable fixed step system<br>
-- default value is 0
-- @function [parent=#PhysicsWorld] setFixedUpdateRate 
-- @param self
-- @param #int updatesPerSecond
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- set the number of substeps in an update of the physics world.<br>
-- One physics update will be divided into several substeps to increase its accuracy.<br>
-- param steps An integer number, default value is 1.
-- @function [parent=#PhysicsWorld] setSubsteps 
-- @param self
-- @param #int steps
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- To control the step of physics.<br>
-- If you want control it by yourself( fixed-timestep for example ), you can set this to false and call step by yourself.<br>
-- attention If you set auto step to false, setSpeed setSubsteps and setUpdateRate won't work, you need to control the time step by yourself.<br>
-- param autoStep A bool object, default value is true.
-- @function [parent=#PhysicsWorld] setAutoStep 
-- @param self
-- @param #bool autoStep
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Adds a joint to this physics world.<br>
-- This joint will be added to this physics world at next frame.<br>
-- attention If this joint is already added to another physics world, it will be removed from that world first and then add to this world.<br>
-- param   joint   A pointer to an existing PhysicsJoint object.
-- @function [parent=#PhysicsWorld] addJoint 
-- @param self
-- @param #cc.PhysicsJoint joint
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Remove all joints from this physics world.<br>
-- attention This function is invoked in the destructor of this physics world, you do not use this api in common.<br>
-- param   destroy   true all joints will be destroyed after remove from this world, false otherwise.
-- @function [parent=#PhysicsWorld] removeAllJoints 
-- @param self
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Get the debug draw mask.<br>
-- return An integer number.
-- @function [parent=#PhysicsWorld] getDebugDrawMask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- set the callback which invoked before update of each object in physics world.
-- @function [parent=#PhysicsWorld] setPreUpdateCallback 
-- @param self
-- @param #function callback
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Get the auto step of this physics world.<br>
-- return A bool object.
-- @function [parent=#PhysicsWorld] isAutoStep 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set the callback which invoked after update of each object in physics world.
-- @function [parent=#PhysicsWorld] setPostUpdateCallback 
-- @param self
-- @param #function callback
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- @overload self, int         
-- @overload self, cc.PhysicsBody         
-- @function [parent=#PhysicsWorld] removeBody
-- @param self
-- @param #cc.PhysicsBody body
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)

--------------------------------
-- Remove a joint from this physics world.<br>
-- If this world is not locked, the joint is removed immediately, otherwise at next frame. <br>
-- If this joint is connected with a body, it will be removed from the body also.<br>
-- param   joint   A pointer to an existing PhysicsJoint object.<br>
-- param   destroy   true this joint will be destroyed after remove from this world, false otherwise.
-- @function [parent=#PhysicsWorld] removeJoint 
-- @param self
-- @param #cc.PhysicsJoint joint
-- @param #bool destroy
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Get physics shapes that contains the point. <br>
-- All shapes contains the point will be pushed in a Vector<PhysicsShape*> object.<br>
-- attention The point must lie inside a shape.<br>
-- param   point   A Vec2 object contains the position of the point.<br>
-- return A Vector<PhysicsShape*> object contains all found PhysicsShape pointer.
-- @function [parent=#PhysicsWorld] getShapes 
-- @param self
-- @param #vec2_table point
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- The step for physics world.<br>
-- The times passing for simulate the physics.<br>
-- attention You need to setAutoStep(false) first before it can work.<br>
-- param   delta   A float number.
-- @function [parent=#PhysicsWorld] step 
-- @param self
-- @param #float delta
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Set the debug draw mask of this physics world.<br>
-- This physics world will draw shapes and joints by DrawNode according to mask.<br>
-- param mask Mask has four value:DEBUGDRAW_NONE, DEBUGDRAW_SHAPE, DEBUGDRAW_JOINT, DEBUGDRAW_CONTACT and DEBUGDRAW_ALL, default is DEBUGDRAW_NONE
-- @function [parent=#PhysicsWorld] setDebugDrawMask 
-- @param self
-- @param #int mask
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Get the gravity value of this physics world.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsWorld] getGravity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Set the update rate of this physics world<br>
-- Update rate is the value of EngineUpdateTimes/PhysicsWorldUpdateTimes.<br>
-- Set it higher can improve performance, set it lower can improve accuracy of physics world simulation.<br>
-- attention if you setAutoStep(false), this won't work.<br>
-- param rate An integer number, default value is 1.0.
-- @function [parent=#PhysicsWorld] setUpdateRate 
-- @param self
-- @param #int rate
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
--  get the number of substeps 
-- @function [parent=#PhysicsWorld] getFixedUpdateRate 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get the number of substeps of this physics world.<br>
-- return An integer number.
-- @function [parent=#PhysicsWorld] getSubsteps 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get the speed of this physics world.<br>
-- return A float number.
-- @function [parent=#PhysicsWorld] getSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get the update rate of this physics world.<br>
-- return An integer number.
-- @function [parent=#PhysicsWorld] getUpdateRate 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Remove all bodies from physics world. <br>
-- If this world is not locked, those body are removed immediately, otherwise at next frame.
-- @function [parent=#PhysicsWorld] removeAllBodies 
-- @param self
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Set the speed of this physics world.<br>
-- attention if you setAutoStep(false), this won't work.<br>
-- param speed  A float number. Speed is the rate at which the simulation executes. default value is 1.0.
-- @function [parent=#PhysicsWorld] setSpeed 
-- @param self
-- @param #float speed
-- @return PhysicsWorld#PhysicsWorld self (return value: cc.PhysicsWorld)
        
--------------------------------
-- Get the nearest physics shape that contains the point. <br>
-- Query this physics world at point and return the closest shape.<br>
-- param   point   A Vec2 object contains the position of the point.<br>
-- return A PhysicsShape object pointer or nullptr if no shapes were found
-- @function [parent=#PhysicsWorld] getShape 
-- @param self
-- @param #vec2_table point
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
-- Get a body by tag. <br>
-- param   tag   An integer number that identifies a PhysicsBody object. <br>
-- return A PhysicsBody object pointer or nullptr if no shapes were found.
-- @function [parent=#PhysicsWorld] getBody 
-- @param self
-- @param #int tag
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
return nil
