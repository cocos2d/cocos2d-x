
--------------------------------
-- @module AtlasNode
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
--  updates the Atlas (indexed vertex array).<br>
-- Shall be overridden in subclasses.
-- @function [parent=#AtlasNode] updateAtlasValues 
-- @param self
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
--------------------------------
--  Initializes an AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render
-- @function [parent=#AtlasNode] initWithTileFile 
-- @param self
-- @param #string tile
-- @param #int tileWidth
-- @param #int tileHeight
-- @param #int itemsToRender
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  Set an buffer manager of the texture vertex. 
-- @function [parent=#AtlasNode] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas textureAtlas
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- endcode<br>
-- lua NA
-- @function [parent=#AtlasNode] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
--------------------------------
--  Return the buffer manager of the texture vertex. <br>
-- return Return A TextureAtlas.
-- @function [parent=#AtlasNode] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
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
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
--------------------------------
--  Initializes an AtlasNode  with a texture the width and height of each item measured in points and the quantity of items to render
-- @function [parent=#AtlasNode] initWithTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @param #int tileWidth
-- @param #int tileHeight
-- @param #int itemsToRender
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setQuadsToDraw 
-- @param self
-- @param #long quadsToDraw
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
--------------------------------
--  creates a AtlasNode  with an Atlas file the width and height of each item and the quantity of items to render.<br>
-- param filename The path of Atlas file.<br>
-- param tileWidth The width of the item.<br>
-- param tileHeight The height of the item.<br>
-- param itemsToRender The quantity of items to render.
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
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
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
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
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
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] setOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
--------------------------------
-- 
-- @function [parent=#AtlasNode] AtlasNode 
-- @param self
-- @return AtlasNode#AtlasNode self (return value: cc.AtlasNode)
        
return nil
