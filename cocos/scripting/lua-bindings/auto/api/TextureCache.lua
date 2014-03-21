
--------------------------------
-- @module TextureCache
-- @extend Ref

--------------------------------
-- @function [parent=#TextureCache] reloadTexture 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#TextureCache] removeTextureForKey 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#TextureCache] removeAllTextures 
-- @param self
        
--------------------------------
-- @function [parent=#TextureCache] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#TextureCache] getCachedTextureInfo 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- overload function: addImage(cc.Image, string)
--          
-- overload function: addImage(string)
--          
-- @function [parent=#TextureCache] addImage
-- @param self
-- @param #cc.Image image
-- @param #string str
-- @return Texture2D#Texture2D ret (retunr value: cc.Texture2D)

--------------------------------
-- @function [parent=#TextureCache] getTextureForKey 
-- @param self
-- @param #string str
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- @function [parent=#TextureCache] removeUnusedTextures 
-- @param self
        
--------------------------------
-- @function [parent=#TextureCache] removeTexture 
-- @param self
-- @param #cc.Texture2D texture2d
        
--------------------------------
-- @function [parent=#TextureCache] waitForQuit 
-- @param self
        
--------------------------------
-- @function [parent=#TextureCache] TextureCache 
-- @param self
        
return nil
