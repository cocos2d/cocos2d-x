
--------------------------------
-- @module Sprite3D
-- @extend Node,BlendProtocol
-- @parent_module cc

--------------------------------
-- @function [parent=#Sprite3D] setCullFaceEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#Sprite3D] setTexture
-- @param self
-- @param #string str

--------------------------------
-- @function [parent=#Sprite3D] removeAllAttachNode 
-- @param self
        
--------------------------------
-- @function [parent=#Sprite3D] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendfunc
        
--------------------------------
-- @function [parent=#Sprite3D] getMesh 
-- @param self
-- @return Mesh#Mesh ret (return value: cc.Mesh)
        
--------------------------------
-- @function [parent=#Sprite3D] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- @function [parent=#Sprite3D] setCullFace 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Sprite3D] removeAttachNode 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#Sprite3D] getAttachNode 
-- @param self
-- @param #string str
-- @return AttachNode#AttachNode ret (return value: cc.AttachNode)
        
--------------------------------
-- @overload self, string, string         
-- @overload self, string         
-- @function [parent=#Sprite3D] create
-- @param self
-- @param #string str
-- @param #string str
-- @return Sprite3D#Sprite3D ret (retunr value: cc.Sprite3D)

return nil
