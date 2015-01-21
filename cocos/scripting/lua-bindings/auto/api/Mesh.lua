
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
-- name getter 
-- @function [parent=#Mesh] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Mesh] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
--------------------------------
-- 
-- @function [parent=#Mesh] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#Mesh] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- visible getter and setter
-- @function [parent=#Mesh] setVisible 
-- @param self
-- @param #bool visible
-- @return Mesh#Mesh self (return value: cc.Mesh)
        
return nil
