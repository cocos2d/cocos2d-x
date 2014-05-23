
--------------------------------
-- @module SpriteFrame
-- @extend Ref

--------------------------------
-- @function [parent=#SpriteFrame] clone 
-- @param self
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
-- @function [parent=#SpriteFrame] setRotated 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteFrame] setTexture 
-- @param self
-- @param #cc.Texture2D texture2d
        
--------------------------------
-- overload function: initWithTexture(cc.Texture2D, rect_table, bool, cc.Vec2, size_table)
--          
-- overload function: initWithTexture(cc.Texture2D, rect_table)
--          
-- @function [parent=#SpriteFrame] initWithTexture
-- @param self
-- @param #cc.Texture2D texture2d
-- @param #rect_table rect
-- @param #bool bool
-- @param #cc.Vec2 vec2
-- @param #size_table size
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#SpriteFrame] setRectInPixels 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#SpriteFrame] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- @function [parent=#SpriteFrame] getRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#SpriteFrame] setOffsetInPixels 
-- @param self
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#SpriteFrame] getRectInPixels 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#SpriteFrame] setOriginalSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#SpriteFrame] getOriginalSizeInPixels 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#SpriteFrame] setOriginalSizeInPixels 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#SpriteFrame] setOffset 
-- @param self
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#SpriteFrame] getOffset 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#SpriteFrame] isRotated 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- overload function: initWithTextureFilename(string, rect_table, bool, cc.Vec2, size_table)
--          
-- overload function: initWithTextureFilename(string, rect_table)
--          
-- @function [parent=#SpriteFrame] initWithTextureFilename
-- @param self
-- @param #string str
-- @param #rect_table rect
-- @param #bool bool
-- @param #cc.Vec2 vec2
-- @param #size_table size
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#SpriteFrame] setRect 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#SpriteFrame] getOffsetInPixels 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#SpriteFrame] getOriginalSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- overload function: create(string, rect_table, bool, cc.Vec2, size_table)
--          
-- overload function: create(string, rect_table)
--          
-- @function [parent=#SpriteFrame] create
-- @param self
-- @param #string str
-- @param #rect_table rect
-- @param #bool bool
-- @param #cc.Vec2 vec2
-- @param #size_table size
-- @return SpriteFrame#SpriteFrame ret (retunr value: cc.SpriteFrame)

--------------------------------
-- overload function: createWithTexture(cc.Texture2D, rect_table, bool, cc.Vec2, size_table)
--          
-- overload function: createWithTexture(cc.Texture2D, rect_table)
--          
-- @function [parent=#SpriteFrame] createWithTexture
-- @param self
-- @param #cc.Texture2D texture2d
-- @param #rect_table rect
-- @param #bool bool
-- @param #cc.Vec2 vec2
-- @param #size_table size
-- @return SpriteFrame#SpriteFrame ret (retunr value: cc.SpriteFrame)

return nil
