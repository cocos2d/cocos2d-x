
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
-- 
-- @function [parent=#Mesh] calcuateAABB 
-- @param self
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- get per vertex size in bytes
-- @function [parent=#Mesh] getVertexSizeInBytes 
-- @param self
-- @return long#long ret (return value: long)
        
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
-- 
-- @function [parent=#Mesh] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Mesh] bindMeshCommand 
-- @param self
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
-- skin setter
-- @function [parent=#Mesh] setSkin 
-- @param self
-- @param #cc.MeshSkin skin
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- 
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
