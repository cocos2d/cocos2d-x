
--------------------------------
-- @module SpriteFrame
-- @extend Ref
-- @parent_module cc

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
-- @function [parent=#SpriteFrame] getOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
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
-- @param #vec2_table vec2
        
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
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#SpriteFrame] isRotated 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SpriteFrame] setRect 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#SpriteFrame] getOffsetInPixels 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#SpriteFrame] getOriginalSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @overload self, string, rect_table, bool, vec2_table, size_table         
-- @overload self, string, rect_table         
-- @function [parent=#SpriteFrame] create
-- @param self
-- @param #string str
-- @param #rect_table rect
-- @param #bool bool
-- @param #vec2_table vec2
-- @param #size_table size
-- @return SpriteFrame#SpriteFrame ret (retunr value: cc.SpriteFrame)

--------------------------------
-- @overload self, cc.Texture2D, rect_table, bool, vec2_table, size_table         
-- @overload self, cc.Texture2D, rect_table         
-- @function [parent=#SpriteFrame] createWithTexture
-- @param self
-- @param #cc.Texture2D texture2d
-- @param #rect_table rect
-- @param #bool bool
-- @param #vec2_table vec2
-- @param #size_table size
-- @return SpriteFrame#SpriteFrame ret (retunr value: cc.SpriteFrame)

return nil
