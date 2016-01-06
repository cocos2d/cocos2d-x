
--------------------------------
-- @module Scene
-- @extend Node
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Scene] initWithPhysics 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Scene] setCameraOrderDirty 
-- @param self
-- @return Scene#Scene self (return value: cc.Scene)
        
--------------------------------
--  Render the scene.<br>
-- param renderer The renderer use to render the scene.<br>
-- js NA
-- @function [parent=#Scene] render 
-- @param self
-- @param #cc.Renderer renderer
-- @return Scene#Scene self (return value: cc.Scene)
        
--------------------------------
-- 
-- @function [parent=#Scene] stepPhysicsAndNavigation 
-- @param self
-- @param #float deltaTime
-- @return Scene#Scene self (return value: cc.Scene)
        
--------------------------------
-- 
-- @function [parent=#Scene] onProjectionChanged 
-- @param self
-- @param #cc.EventCustom event
-- @return Scene#Scene self (return value: cc.Scene)
        
--------------------------------
--  Get the physics world of the scene.<br>
-- return The physics world of the scene.<br>
-- js NA
-- @function [parent=#Scene] getPhysicsWorld 
-- @param self
-- @return PhysicsWorld#PhysicsWorld ret (return value: cc.PhysicsWorld)
        
--------------------------------
-- 
-- @function [parent=#Scene] initWithSize 
-- @param self
-- @param #size_table size
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Get the default camera.<br>
-- js NA<br>
-- return The default camera of scene.
-- @function [parent=#Scene] getDefaultCamera 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
--  Creates a new Scene object with a predefined Size. <br>
-- param size The predefined size of scene.<br>
-- return An autoreleased Scene object.<br>
-- js NA
-- @function [parent=#Scene] createWithSize 
-- @param self
-- @param #size_table size
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
--  Creates a new Scene object. <br>
-- return An autoreleased Scene object.
-- @function [parent=#Scene] create 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
--  Create a scene with physics.<br>
-- return An autoreleased Scene object with physics.<br>
-- js NA
-- @function [parent=#Scene] createWithPhysics 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
-- 
-- @function [parent=#Scene] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Scene] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  override function 
-- @function [parent=#Scene] removeAllChildren 
-- @param self
-- @return Scene#Scene self (return value: cc.Scene)
        
--------------------------------
-- 
-- @function [parent=#Scene] Scene 
-- @param self
-- @return Scene#Scene self (return value: cc.Scene)
        
return nil
