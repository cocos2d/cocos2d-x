
--------------------------------
-- @module Scale9Sprite
-- @extend Node,BlendProtocol
-- @parent_module ccui

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] disableCascadeColor 
-- @param self
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
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
-- return true if the widget is flipped horizontally, false otherwise.
-- @function [parent=#Scale9Sprite] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Toggle 9-slice feature.<br>
-- If Scale9Sprite is 9-slice disabled, the Scale9Sprite will rendered as a normal sprite.<br>
-- param enabled True to enable 9-slice, false otherwise.<br>
-- js NA
-- @function [parent=#Scale9Sprite] setScale9Enabled 
-- @param self
-- @param #bool enabled
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Sets whether the widget should be flipped vertically or not.<br>
-- param flippedY true if the widget should be flipped vertically, false otherwise.
-- @function [parent=#Scale9Sprite] setFlippedY 
-- @param self
-- @param #bool flippedY
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Sets whether the widget should be flipped horizontally or not.<br>
-- param flippedX true if the widget should be flipped horizontally, false otherwise.
-- @function [parent=#Scale9Sprite] setFlippedX 
-- @param self
-- @param #bool flippedX
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Creates and returns a new sprite object with the specified cap insets.<br>
-- You use this method to add cap insets to a sprite or to change the existing<br>
-- cap insets of a sprite. In both cases, you get back a new image and the<br>
-- original sprite remains untouched.<br>
-- param capInsets The values to use for the cap insets.<br>
-- return A Scale9Sprite instance.
-- @function [parent=#Scale9Sprite] resizableSpriteWithCapInsets 
-- @param self
-- @param #rect_table capInsets
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] disableCascadeOpacity 
-- @param self
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Query the current bright state.<br>
-- return @see `State`<br>
-- since v3.7
-- @function [parent=#Scale9Sprite] getState 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Change the state of 9-slice sprite.<br>
-- see `State`<br>
-- param state A enum value in State.<br>
-- since v3.4
-- @function [parent=#Scale9Sprite] setState 
-- @param self
-- @param #int state
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- brief Change the bottom sprite's cap inset.<br>
-- param bottomInset The values to use for the cap inset.
-- @function [parent=#Scale9Sprite] setInsetBottom 
-- @param self
-- @param #float bottomInset
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- @overload self, string         
-- @overload self, string, rect_table         
-- @function [parent=#Scale9Sprite] initWithSpriteFrameName
-- @param self
-- @param #string spriteFrameName
-- @param #rect_table capInsets
-- @return bool#bool ret (return value: bool)

--------------------------------
-- brief Get the original no 9-sliced sprite<br>
-- return A sprite instance.
-- @function [parent=#Scale9Sprite] getSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- brief Change the top sprite's cap inset.<br>
-- param topInset The values to use for the cap inset.
-- @function [parent=#Scale9Sprite] setInsetTop 
-- @param self
-- @param #float topInset
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- @overload self, cc.Sprite, rect_table, rect_table         
-- @overload self, cc.Sprite, rect_table, bool, rect_table         
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
-- brief Change the prefered size of Scale9Sprite.<br>
-- param size A delimitation zone.
-- @function [parent=#Scale9Sprite] setPreferredSize 
-- @param self
-- @param #size_table size
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- brief Change inner sprite's sprite frame.<br>
-- param spriteFrame A sprite frame pointer.<br>
-- param capInsets The values to use for the cap insets.
-- @function [parent=#Scale9Sprite] setSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #rect_table capInsets
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Returns the blending function that is currently being used.<br>
-- return A BlendFunc structure with source and destination factor which specified pixel arithmetic.<br>
-- js NA<br>
-- lua NA
-- @function [parent=#Scale9Sprite] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- brief Query the bottom sprite's cap inset.<br>
-- return The bottom sprite's cap inset.
-- @function [parent=#Scale9Sprite] getInsetBottom 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Query the Scale9Sprite's prefered size.<br>
-- return Scale9Sprite's cap inset.
-- @function [parent=#Scale9Sprite] getCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- brief Query whether the Scale9Sprite is enable 9-slice or not.<br>
-- return True if 9-slice is enabled, false otherwise.<br>
-- js NA
-- @function [parent=#Scale9Sprite] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Query the right sprite's cap inset.<br>
-- return The right sprite's cap inset.
-- @function [parent=#Scale9Sprite] getInsetRight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Query the sprite's original size.<br>
-- return Sprite size.
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
-- Sets the source blending function.<br>
-- param blendFunc A structure with source and destination factor to specify pixel arithmetic. e.g. {GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.<br>
-- js NA<br>
-- lua NA
-- @function [parent=#Scale9Sprite] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- brief Query the top sprite's cap inset.<br>
-- return The top sprite's cap inset.
-- @function [parent=#Scale9Sprite] getInsetTop 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Change the left sprite's cap inset.<br>
-- param leftInset The values to use for the cap inset.
-- @function [parent=#Scale9Sprite] setInsetLeft 
-- @param self
-- @param #float leftInset
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- @overload self, cc.SpriteFrame         
-- @overload self, cc.SpriteFrame, rect_table         
-- @function [parent=#Scale9Sprite] initWithSpriteFrame
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #rect_table capInsets
-- @return bool#bool ret (return value: bool)

--------------------------------
-- brief Query the  Scale9Sprite's prefered size.<br>
-- return Scale9Sprite's prefered size.
-- @function [parent=#Scale9Sprite] getPreferredSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- brief Change the cap inset size.<br>
-- param rect A delimitation zone.
-- @function [parent=#Scale9Sprite] setCapInsets 
-- @param self
-- @param #rect_table rect
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
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
-- brief Query the left sprite's cap inset.<br>
-- return The left sprite's cap inset.
-- @function [parent=#Scale9Sprite] getInsetLeft 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Change the right sprite's cap inset.<br>
-- param rightInset The values to use for the cap inset.
-- @function [parent=#Scale9Sprite] setInsetRight 
-- @param self
-- @param #float rightInset
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
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
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setScaleY 
-- @param self
-- @param #float scaleY
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setScaleX 
-- @param self
-- @param #float scaleX
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
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
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] cleanup 
-- @param self
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- @overload self, float, float         
-- @overload self, float         
-- @function [parent=#Scale9Sprite] setScale
-- @param self
-- @param #float scaleX
-- @param #float scaleY
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)

--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setCameraMask 
-- @param self
-- @param #unsigned short mask
-- @param #bool applyChildren
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] updateDisplayedColor 
-- @param self
-- @param #color3b_table parentColor
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] setContentSize 
-- @param self
-- @param #size_table size
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Scale9Sprite] getScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Default constructor.<br>
-- js ctor<br>
-- lua new
-- @function [parent=#Scale9Sprite] Scale9Sprite 
-- @param self
-- @return Scale9Sprite#Scale9Sprite self (return value: ccui.Scale9Sprite)
        
return nil
