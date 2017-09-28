
--------------------------------
-- @module CreatorReader
-- @extend Ref
-- @parent_module creator

--------------------------------
-- Return the CollisionManager. It is added as a child of the Scene to simplify the codes.<br>
-- return The `AnimationManager` of the scene
-- @function [parent=#CreatorReader] getAnimationManager 
-- @param self
-- @return AnimationManager#AnimationManager ret (return value: creator.AnimationManager)
        
--------------------------------
-- Setup the needed spritesheets and change the design resolution if needed.<br>
-- Call it before getting the Scene graph
-- @function [parent=#CreatorReader] setup 
-- @param self
-- @return CreatorReader#CreatorReader self (return value: creator.CreatorReader)
        
--------------------------------
-- Returns the FlatBuffers Schema version.<br>
-- return a string containing the flatbuffer's schema version
-- @function [parent=#CreatorReader] getVersion 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Returns the scenegraph contained in the .ccreator file<br>
-- return A `Scene*`
-- @function [parent=#CreatorReader] getSceneGraph 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
-- Return the CollisionManager. It is added as a child of the Scene to make collision take effect.<br>
-- return The `CollisionManager` of the scene
-- @function [parent=#CreatorReader] getColliderManager 
-- @param self
-- @return ColliderManager#ColliderManager ret (return value: creator.ColliderManager)
        
--------------------------------
-- 
-- @function [parent=#CreatorReader] createWithFilename 
-- @param self
-- @param #string filename
-- @return CreatorReader#CreatorReader ret (return value: creator.CreatorReader)
        
return nil
