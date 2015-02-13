
--------------------------------
-- @module TextureCache
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Reload texture from the image file<br>
-- If the file image hasn't loaded before, load it.<br>
-- Otherwise the texture will be reloaded from the file image.<br>
-- The "filenName" parameter is the related/absolute path of the file image.<br>
-- Return true if the reloading is succeed, otherwise return false.
-- @function [parent=#TextureCache] reloadTexture 
-- @param self
-- @param #string fileName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextureCache] unbindAllImageAsync 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Deletes a texture from the cache given a its key name<br>
-- since v0.99.4
-- @function [parent=#TextureCache] removeTextureForKey 
-- @param self
-- @param #string key
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Purges the dictionary of loaded textures.<br>
-- Call this method if you receive the "Memory Warning"<br>
-- In the short term: it will free some resources preventing your app from being killed<br>
-- In the medium term: it will allocate more resources<br>
-- In the long term: it will be the same
-- @function [parent=#TextureCache] removeAllTextures 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#TextureCache] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Output to CCLOG the current contents of this TextureCache<br>
-- This will attempt to calculate the size of each texture, and the total texture memory in use<br>
-- since v1.0
-- @function [parent=#TextureCache] getCachedTextureInfo 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, cc.Image, string         
-- @overload self, string         
-- @function [parent=#TextureCache] addImage
-- @param self
-- @param #cc.Image image
-- @param #string key
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)

--------------------------------
-- 
-- @function [parent=#TextureCache] unbindImageAsync 
-- @param self
-- @param #string filename
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Returns an already created texture. Returns nil if the texture doesn't exist.<br>
-- since v0.99.5
-- @function [parent=#TextureCache] getTextureForKey 
-- @param self
-- @param #string key
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  Removes unused textures<br>
-- Textures that have a retain count of 1 will be deleted<br>
-- It is convenient to call this method after when starting a new Scene<br>
-- since v0.8
-- @function [parent=#TextureCache] removeUnusedTextures 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Deletes a texture from the cache given a texture
-- @function [parent=#TextureCache] removeTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
-- 
-- @function [parent=#TextureCache] waitForQuit 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
-- js ctor
-- @function [parent=#TextureCache] TextureCache 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
return nil
