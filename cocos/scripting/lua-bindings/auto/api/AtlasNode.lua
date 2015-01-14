
--------------------------------
-- @module AtlasNode
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
--  updates the Atlas (indexed vertex array).<br>
-- Shall be overridden in subclasses
-- @function [parent=#AtlasNode] updateAtlasValues 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas textureAtlas
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- endcode<br>
-- lua NA
-- @function [parent=#AtlasNode] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#AtlasNode] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] getQuadsToDraw 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setTexture 
-- @param self
-- @param #cc.Texture2D texture
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setQuadsToDraw 
-- @param self
-- @param #long quadsToDraw
        
--------------------------------
--  creates a AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render
-- @function [parent=#AtlasNode] create 
-- @param self
-- @param #string filename
-- @param #int tileWidth
-- @param #int tileHeight
-- @param #int itemsToRender
-- @return AtlasNode#AtlasNode ret (return value: cc.AtlasNode)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setColor 
-- @param self
-- @param #color3b_table color
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] getColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setOpacityModifyRGB 
-- @param self
-- @param #bool isOpacityModifyRGB
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setOpacity 
-- @param self
-- @param #unsigned char opacity
        
return nil
