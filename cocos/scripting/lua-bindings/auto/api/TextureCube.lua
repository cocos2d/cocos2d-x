
--------------------------------
-- @module TextureCube
-- @extend Texture2D
-- @parent_module cc

--------------------------------
--  reload texture cube after GLESContext reconstructed.
-- @function [parent=#TextureCube] reloadTexture 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the min filter, mag filter, wrap s and wrap t texture parameters.<br>
-- If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.
-- @function [parent=#TextureCube] setTexParameters 
-- @param self
-- @param #cc.Texture2D::_TexParams 
-- @return TextureCube#TextureCube self (return value: cc.TextureCube)
        
--------------------------------
--  create cube texture from 6 textures.<br>
-- param positive_x texture for the right side of the texture cube face.<br>
-- param negative_x texture for the up side of the texture cube face.<br>
-- param positive_y texture for the top side of the texture cube face<br>
-- param negative_y texture for the bottom side of the texture cube face<br>
-- param positive_z texture for the forward side of the texture cube face.<br>
-- param negative_z texture for the rear side of the texture cube face.<br>
-- return  A new texture cube inited with given parameters.
-- @function [parent=#TextureCube] create 
-- @param self
-- @param #string positive_x
-- @param #string negative_x
-- @param #string positive_y
-- @param #string negative_y
-- @param #string positive_z
-- @param #string negative_z
-- @return TextureCube#TextureCube ret (return value: cc.TextureCube)
        
return nil
