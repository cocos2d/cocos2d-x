
--------------------------------
-- @module Mesh
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#Mesh] setTexture
-- @param self
-- @param #string texPath
-- @return Mesh#Mesh self (return value: cc.Mesh)

--------------------------------
-- 
-- @function [parent=#Mesh] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  Returns the Material being used by the Mesh 
-- @function [parent=#Mesh] getMaterial 
-- @param self
-- @return Material#Material ret (return value: cc.Material)
        
--------------------------------
-- get per vertex size in bytes
-- @function [parent=#Mesh] getVertexSizeInBytes 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Sets a new Material to the Mesh 
-- @function [parent=#Mesh] setMaterial 
-- @param self
-- @param #cc.Material material
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- name getter 
-- @function [parent=#Mesh] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- get MeshVertexAttribute by index
-- @function [parent=#Mesh] getMeshVertexAttribute 
-- @param self
-- @param #int idx
-- @return MeshVertexAttrib#MeshVertexAttrib ret (return value: cc.MeshVertexAttrib)
        
--------------------------------
-- calculate the AABB of the mesh<br>
-- note the AABB is in the local space, not the world space
-- @function [parent=#Mesh] calculateAABB 
-- @param self
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Mesh] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #float globalZ
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @param #unsigned int lightMask
-- @param #vec4_table color
-- @param #bool forceDepthWrite
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Mesh] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- name setter
-- @function [parent=#Mesh] setName 
-- @param self
-- @param #string name
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- Mesh index data setter
-- @function [parent=#Mesh] setMeshIndexData 
-- @param self
-- @param #cc.MeshIndexData indexdata
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- get mesh vertex attribute count
-- @function [parent=#Mesh] getMeshVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#Mesh] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- force set this Sprite3D to 2D render queue
-- @function [parent=#Mesh] setForce2DQueue 
-- @param self
-- @param #bool force2D
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- skin setter
-- @function [parent=#Mesh] setSkin 
-- @param self
-- @param #cc.MeshSkin skin
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Mesh] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--   Sets a new GLProgramState for the Mesh<br>
-- A new Material will be created for it
-- @function [parent=#Mesh] setGLProgramState 
-- @param self
-- @param #cc.GLProgramState glProgramState
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- visible getter and setter
-- @function [parent=#Mesh] setVisible 
-- @param self
-- @param #bool visible
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Mesh] Mesh 
-- @param self
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
return nil
