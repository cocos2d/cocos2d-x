
--------------------------------
-- @module Mesh
-- @extend Ref
-- @parent_module cc

--------------------------------
-- get mesh vertex attribute count
-- @function [parent=#Mesh] getMeshVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#Mesh] setTexture
-- @param self
-- @param #string texPath

--------------------------------
-- mesh index data getter 
-- @function [parent=#Mesh] getMeshIndexData 
-- @param self
-- @return MeshIndexData#MeshIndexData ret (return value: cc.MeshIndexData)
        
--------------------------------
-- 
-- @function [parent=#Mesh] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- skin getter 
-- @function [parent=#Mesh] getSkin 
-- @param self
-- @return MeshSkin#MeshSkin ret (return value: cc.MeshSkin)
        
--------------------------------
-- name getter 
-- @function [parent=#Mesh] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Mesh] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
        
--------------------------------
-- get index format
-- @function [parent=#Mesh] getIndexFormat 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- get per vertex size in bytes
-- @function [parent=#Mesh] getVertexSizeInBytes 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Mesh] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- get GLProgramState
-- @function [parent=#Mesh] getGLProgramState 
-- @param self
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
-- get index count
-- @function [parent=#Mesh] getIndexCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- get vertex buffer
-- @function [parent=#Mesh] getVertexBuffer 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- get MeshVertexAttribute by index
-- @function [parent=#Mesh] getMeshVertexAttribute 
-- @param self
-- @param #int idx
-- @return MeshVertexAttrib#MeshVertexAttrib ret (return value: cc.MeshVertexAttrib)
        
--------------------------------
-- 
-- @function [parent=#Mesh] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- get index buffer
-- @function [parent=#Mesh] getIndexBuffer 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- has vertex attribute?
-- @function [parent=#Mesh] hasVertexAttrib 
-- @param self
-- @param #int attrib
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  get primitive type
-- @function [parent=#Mesh] getPrimitiveType 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- visible getter and setter
-- @function [parent=#Mesh] setVisible 
-- @param self
-- @param #bool visible
        
return nil
