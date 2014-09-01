
--------------------------------
-- @module Camera
-- @extend Node
-- @parent_module cc

--------------------------------
-- @function [parent=#Camera] getProjectionMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Camera] getViewProjectionMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Camera] getViewMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Camera] getCameraFlag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Camera] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Camera] lookAt 
-- @param self
-- @param #vec3_table vec3
-- @param #vec3_table vec3
        
--------------------------------
-- @function [parent=#Camera] setCameraFlag 
-- @param self
-- @param #int cameraflag
        
--------------------------------
-- @function [parent=#Camera] unproject 
-- @param self
-- @param #size_table size
-- @param #vec3_table vec3
-- @param #vec3_table vec3
        
--------------------------------
-- @function [parent=#Camera] create 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- @function [parent=#Camera] createPerspective 
-- @param self
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #float float
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- @function [parent=#Camera] createOrthographic 
-- @param self
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #float float
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- @function [parent=#Camera] getVisitingCamera 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- @function [parent=#Camera] setPosition3D 
-- @param self
-- @param #vec3_table vec3
        
return nil
