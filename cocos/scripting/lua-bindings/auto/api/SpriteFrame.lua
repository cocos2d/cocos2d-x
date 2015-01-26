
--------------------------------
-- @module SpriteFrame
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#SpriteFrame] clone 
-- @param self
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
-- 
-- @function [parent=#SpriteFrame] setRotated 
-- @param self
-- @param #bool rotated
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
--  set texture of the frame, the texture is retained 
-- @function [parent=#SpriteFrame] setTexture 
-- @param self
-- @param #cc.Texture2D pobTexture
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
-- 
-- @function [parent=#SpriteFrame] getOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#SpriteFrame] setRectInPixels 
-- @param self
-- @param #rect_table rectInPixels
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
--  get texture of the frame 
-- @function [parent=#SpriteFrame] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  get rect of the frame 
-- @function [parent=#SpriteFrame] getRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  set offset of the frame 
-- @function [parent=#SpriteFrame] setOffsetInPixels 
-- @param self
-- @param #vec2_table offsetInPixels
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
-- 
-- @function [parent=#SpriteFrame] getRectInPixels 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  set original size of the trimmed image 
-- @function [parent=#SpriteFrame] setOriginalSize 
-- @param self
-- @param #size_table sizeInPixels
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
--  get original size of the trimmed image 
-- @function [parent=#SpriteFrame] getOriginalSizeInPixels 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  set original size of the trimmed image 
-- @function [parent=#SpriteFrame] setOriginalSizeInPixels 
-- @param self
-- @param #size_table sizeInPixels
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
-- 
-- @function [parent=#SpriteFrame] setOffset 
-- @param self
-- @param #vec2_table offsets
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
-- 
-- @function [parent=#SpriteFrame] isRotated 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  set rect of the frame 
-- @function [parent=#SpriteFrame] setRect 
-- @param self
-- @param #rect_table rect
-- @return SpriteFrame#SpriteFrame self (return value: cc.SpriteFrame)
        
--------------------------------
--  get offset of the frame 
-- @function [parent=#SpriteFrame] getOffsetInPixels 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  get original size of the trimmed image 
-- @function [parent=#SpriteFrame] getOriginalSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @overload self, string, rect_table, bool, vec2_table, size_table         
-- @overload self, string, rect_table         
-- @function [parent=#SpriteFrame] create
-- @param self
-- @param #string filename
-- @param #rect_table rect
-- @param #bool rotated
-- @param #vec2_table offset
-- @param #size_table originalSize
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)

--------------------------------
-- @overload self, cc.Texture2D, rect_table, bool, vec2_table, size_table         
-- @overload self, cc.Texture2D, rect_table         
-- @function [parent=#SpriteFrame] createWithTexture
-- @param self
-- @param #cc.Texture2D pobTexture
-- @param #rect_table rect
-- @param #bool rotated
-- @param #vec2_table offset
-- @param #size_table originalSize
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)

return nil
