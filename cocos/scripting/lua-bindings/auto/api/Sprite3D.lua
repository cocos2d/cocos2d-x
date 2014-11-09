
--------------------------------
-- @module Sprite3D
-- @extend Node,BlendProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Sprite3D] setCullFaceEnabled 
-- @param self
-- @param #bool enable
        
--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#Sprite3D] setTexture
-- @param self
-- @param #string texFile

--------------------------------
-- 
-- @function [parent=#Sprite3D] getLightMask 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- remove all attach nodes
-- @function [parent=#Sprite3D] removeAllAttachNode 
-- @param self
        
--------------------------------
-- get mesh
-- @function [parent=#Sprite3D] getMesh 
-- @param self
-- @return Mesh#Mesh ret (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] setCullFace 
-- @param self
-- @param #unsigned int cullFace
        
--------------------------------
--  light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff 
-- @function [parent=#Sprite3D] setLightMask 
-- @param self
-- @param #unsigned int mask
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
--  get mesh count 
-- @function [parent=#Sprite3D] getMeshCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- remove attach node
-- @function [parent=#Sprite3D] removeAttachNode 
-- @param self
-- @param #string boneName
        
--------------------------------
-- 
-- @function [parent=#Sprite3D] getSkeleton 
-- @param self
-- @return Skeleton3D#Skeleton3D ret (return value: cc.Skeleton3D)
        
--------------------------------
-- get Mesh by index
-- @function [parent=#Sprite3D] getMeshByIndex 
-- @param self
-- @param #int index
-- @return Mesh#Mesh ret (return value: cc.Mesh)
        
--------------------------------
-- get Mesh by Name, it returns the first one if there are more than one mesh with the same name 
-- @function [parent=#Sprite3D] getMeshByName 
-- @param self
-- @param #string name
-- @return Mesh#Mesh ret (return value: cc.Mesh)
        
--------------------------------
-- get AttachNode by bone name, return nullptr if not exist
-- @function [parent=#Sprite3D] getAttachNode 
-- @param self
-- @param #string boneName
-- @return AttachNode#AttachNode ret (return value: cc.AttachNode)
        
--------------------------------
-- @overload self, string, string         
-- @overload self, string         
-- @function [parent=#Sprite3D] create
-- @param self
-- @param #string modelPath
-- @param #string texturePath
-- @return Sprite3D#Sprite3D ret (return value: cc.Sprite3D)

--------------------------------
-- Returns 2d bounding-box<br>
-- Note: the bouding-box is just get from the AABB which as Z=0, so that is not very accurate.
-- @function [parent=#Sprite3D] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  set GLProgramState, you should bind attributes by yourself 
-- @function [parent=#Sprite3D] setGLProgramState 
-- @param self
-- @param #cc.GLProgramState glProgramState
        
--------------------------------
--  just rember bind attributes 
-- @function [parent=#Sprite3D] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
        
return nil
