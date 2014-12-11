
--------------------------------
-- @module Scale9Sprite
-- @extend Node
-- @parent_module ccui

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] disableCascadeColor 
-- @param self
        
--------------------------------
-- @overload self, cc.Sprite, rect_table, bool, vec2_table, size_table, rect_table         
-- @overload self, cc.Sprite, rect_table, bool, rect_table         
-- @function [parent=#Scale9Sprite] updateWithSprite
-- @param self
-- @param #cc.Sprite sprite
-- @param #rect_table rect
-- @param #bool rotated
-- @param #vec2_table offset
-- @param #size_table originalSize
-- @param #rect_table capInsets
-- @return bool#bool ret (return value: bool)

--------------------------------
-- Returns the flag which indicates whether the widget is flipped horizontally or not.<br>
-- It only flips the texture of the widget, and not the texture of the widget's children.<br>
-- Also, flipping the texture doesn't alter the anchorPoint.<br>
-- If you want to flip the anchorPoint too, and/or to flip the children too use:<br>
-- widget->setScaleX(sprite->getScaleX() * -1);<br>
-- return true if the widget is flipped horizaontally, false otherwise.
-- @function [parent=#Scale9Sprite] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets whether the widget should be flipped vertically or not.<br>
-- param bFlippedY true if the widget should be flipped vertically, flase otherwise.
-- @function [parent=#Scale9Sprite] setFlippedY 
-- @param self
-- @param #bool flippedY
        
--------------------------------
-- Sets whether the widget should be flipped horizontally or not.<br>
-- param bFlippedX true if the widget should be flipped horizaontally, false otherwise.
-- @function [parent=#Scale9Sprite] setFlippedX 
-- @param self
-- @param #bool flippedX
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setScale9Enabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] disableCascadeOpacity 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setInsetBottom 
-- @param self
-- @param #float bottomInset
        
--------------------------------
-- @overload self, string         
-- @overload self, string, rect_table         
-- @function [parent=#Scale9Sprite] initWithSpriteFrameName
-- @param self
-- @param #string spriteFrameName
-- @param #rect_table capInsets
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setInsetTop 
-- @param self
-- @param #float topInset
        
--------------------------------
-- @overload self, cc.Sprite, rect_table, bool, rect_table         
-- @overload self         
-- @overload self, cc.Sprite, rect_table, rect_table         
-- @overload self, cc.Sprite, rect_table, bool, vec2_table, size_table, rect_table         
-- @function [parent=#Scale9Sprite] init
-- @param self
-- @param #cc.Sprite sprite
-- @param #rect_table rect
-- @param #bool rotated
-- @param #vec2_table offset
-- @param #size_table originalSize
-- @param #rect_table capInsets
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setPreferredSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getInsetRight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #rect_table capInsets
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getInsetBottom 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Creates and returns a new sprite object with the specified cap insets.<br>
-- You use this method to add cap insets to a sprite or to change the existing<br>
-- cap insets of a sprite. In both cases, you get back a new image and the<br>
-- original sprite remains untouched.<br>
-- param capInsets The values to use for the cap insets.
-- @function [parent=#Scale9Sprite] resizableSpriteWithCapInsets 
-- @param self
-- @param #rect_table capInsets
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getOriginalSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @overload self, string, rect_table         
-- @overload self, string, rect_table, rect_table         
-- @overload self, rect_table, string         
-- @overload self, string         
-- @function [parent=#Scale9Sprite] initWithFile
-- @param self
-- @param #string file
-- @param #rect_table rect
-- @param #rect_table capInsets
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getInsetTop 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setInsetLeft 
-- @param self
-- @param #float leftInset
        
--------------------------------
-- @overload self, cc.SpriteFrame         
-- @overload self, cc.SpriteFrame, rect_table         
-- @function [parent=#Scale9Sprite] initWithSpriteFrame
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #rect_table capInsets
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getPreferredSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setCapInsets 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- Return the flag which indicates whether the widget is flipped vertically or not.<br>
-- It only flips the texture of the widget, and not the texture of the widget's children.<br>
-- Also, flipping the texture doesn't alter the anchorPoint.<br>
-- If you want to flip the anchorPoint too, and/or to flip the children too use:<br>
-- widget->setScaleY(widget->getScaleY() * -1);<br>
-- return true if the widget is flipped vertically, flase otherwise.
-- @function [parent=#Scale9Sprite] isFlippedY 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getInsetLeft 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setInsetRight 
-- @param self
-- @param #float rightInset
        
--------------------------------
-- @overload self, string, rect_table, rect_table         
-- @overload self         
-- @overload self, rect_table, string         
-- @overload self, string, rect_table         
-- @overload self, string         
-- @function [parent=#Scale9Sprite] create
-- @param self
-- @param #string file
-- @param #rect_table rect
-- @param #rect_table capInsets
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)

--------------------------------
-- @overload self, string, rect_table         
-- @overload self, string         
-- @function [parent=#Scale9Sprite] createWithSpriteFrameName
-- @param self
-- @param #string spriteFrameName
-- @param #rect_table capInsets
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)

--------------------------------
-- @overload self, cc.SpriteFrame, rect_table         
-- @overload self, cc.SpriteFrame         
-- @function [parent=#Scale9Sprite] createWithSpriteFrame
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #rect_table capInsets
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setAnchorPoint 
-- @param self
-- @param #vec2_table anchorPoint
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setScaleY 
-- @param self
-- @param #float scaleY
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setScaleX 
-- @param self
-- @param #float scaleX
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char parentOpacity
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] cleanup 
-- @param self
        
--------------------------------
-- @overload self, float, float         
-- @overload self, float         
-- @function [parent=#Scale9Sprite] setScale
-- @param self
-- @param #float scalex
-- @param #float scaley

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] updateDisplayedColor 
-- @param self
-- @param #color3b_table parentColor
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setContentSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- js ctor
-- @function [parent=#Scale9Sprite] Scale9Sprite 
-- @param self
        
return nil
