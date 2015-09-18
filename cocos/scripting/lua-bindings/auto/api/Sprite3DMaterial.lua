
--------------------------------
-- @module Sprite3DMaterial
-- @extend Material
-- @parent_module cc

--------------------------------
-- Get material type<br>
-- return Material type
-- @function [parent=#Sprite3DMaterial] getMaterialType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Create material with file name, it creates material from cache if it is previously loaded<br>
-- param path Path of material file<br>
-- return Created material
-- @function [parent=#Sprite3DMaterial] createWithFilename 
-- @param self
-- @param #string path
-- @return Sprite3DMaterial#Sprite3DMaterial ret (return value: cc.Sprite3DMaterial)
        
--------------------------------
-- Release all cached materials
-- @function [parent=#Sprite3DMaterial] releaseCachedMaterial 
-- @param self
-- @return Sprite3DMaterial#Sprite3DMaterial self (return value: cc.Sprite3DMaterial)
        
--------------------------------
-- @overload self         
-- @overload self, int, bool         
-- @function [parent=#Sprite3DMaterial] createBuiltInMaterial
-- @param self
-- @param #int type
-- @param #bool skinned
-- @return Sprite3DMaterial#Sprite3DMaterial ret (return value: cc.Sprite3DMaterial)

--------------------------------
-- Create material with GLProgramState<br>
-- param programState GLProgramState instance<br>
-- return Created material
-- @function [parent=#Sprite3DMaterial] createWithGLStateProgram 
-- @param self
-- @param #cc.GLProgramState programState
-- @return Sprite3DMaterial#Sprite3DMaterial ret (return value: cc.Sprite3DMaterial)
        
--------------------------------
-- Release all built in materials
-- @function [parent=#Sprite3DMaterial] releaseBuiltInMaterial 
-- @param self
-- @return Sprite3DMaterial#Sprite3DMaterial self (return value: cc.Sprite3DMaterial)
        
--------------------------------
-- Clone material
-- @function [parent=#Sprite3DMaterial] clone 
-- @param self
-- @return Material#Material ret (return value: cc.Material)
        
return nil
