
--------------------------------
-- @module ControlButton
-- @extend Control
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ControlButton] isPushed 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets the title label to use for the specified state.<br>
-- If a property is not specified for a state, the default is to use<br>
-- the ButtonStateNormal value.<br>
-- param label The title label to use for the specified state.<br>
-- param state The state that uses the specified title. The values are described<br>
-- in "CCControlState".
-- @function [parent=#ControlButton] setTitleLabelForState 
-- @param self
-- @param #cc.Node label
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setAdjustBackgroundImage 
-- @param self
-- @param #bool adjustBackgroundImage
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- Sets the title string to use for the specified state.<br>
-- If a property is not specified for a state, the default is to use<br>
-- the ButtonStateNormal value.<br>
-- param title The title string to use for the specified state.<br>
-- param state The state that uses the specified title. The values are described<br>
-- in "CCControlState".
-- @function [parent=#ControlButton] setTitleForState 
-- @param self
-- @param #string title
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setLabelAnchorPoint 
-- @param self
-- @param #vec2_table var
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getLabelAnchorPoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] initWithBackgroundSprite 
-- @param self
-- @param #ccui.Scale9Sprite sprite
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getTitleTTFSizeForState 
-- @param self
-- @param #int state
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setTitleTTFForState 
-- @param self
-- @param #string fntFile
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setTitleTTFSizeForState 
-- @param self
-- @param #float size
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setTitleLabel 
-- @param self
-- @param #cc.Node var
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setPreferredSize 
-- @param self
-- @param #size_table var
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getCurrentTitleColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setZoomOnTouchDown 
-- @param self
-- @param #bool var
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setBackgroundSprite 
-- @param self
-- @param #ccui.Scale9Sprite var
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- Returns the background sprite used for a state.<br>
-- param state The state that uses the background sprite. Possible values are<br>
-- described in "CCControlState".
-- @function [parent=#ControlButton] getBackgroundSpriteForState 
-- @param self
-- @param #int state
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getHorizontalOrigin 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] initWithTitleAndFontNameAndFontSize 
-- @param self
-- @param #string title
-- @param #string fontName
-- @param #float fontSize
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets the font of the label, changes the label to a BMFont if neccessary.<br>
-- param fntFile The name of the font to change to<br>
-- param state The state that uses the specified fntFile. The values are described<br>
-- in "CCControlState".
-- @function [parent=#ControlButton] setTitleBMFontForState 
-- @param self
-- @param #string fntFile
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getScaleRatio 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getTitleTTFForState 
-- @param self
-- @param #int state
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getBackgroundSprite 
-- @param self
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Returns the title color used for a state.<br>
-- param state The state that uses the specified color. The values are described<br>
-- in "CCControlState".<br>
-- return The color of the title for the specified state.
-- @function [parent=#ControlButton] getTitleColorForState 
-- @param self
-- @param #int state
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Sets the color of the title to use for the specified state.<br>
-- param color The color of the title to use for the specified state.<br>
-- param state The state that uses the specified color. The values are described<br>
-- in "CCControlState".
-- @function [parent=#ControlButton] setTitleColorForState 
-- @param self
-- @param #color3b_table color
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
--  Adjust the background image. YES by default. If the property is set to NO, the<br>
-- background will use the prefered size of the background image. 
-- @function [parent=#ControlButton] doesAdjustBackgroundImage 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets the background spriteFrame to use for the specified button state.<br>
-- param spriteFrame The background spriteFrame to use for the specified state.<br>
-- param state The state that uses the specified image. The values are described<br>
-- in "CCControlState".
-- @function [parent=#ControlButton] setBackgroundSpriteFrameForState 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- Sets the background sprite to use for the specified button state.<br>
-- param sprite The background sprite to use for the specified state.<br>
-- param state The state that uses the specified image. The values are described<br>
-- in "CCControlState".
-- @function [parent=#ControlButton] setBackgroundSpriteForState 
-- @param self
-- @param #ccui.Scale9Sprite sprite
-- @param #int state
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setScaleRatio 
-- @param self
-- @param #float var
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getTitleBMFontForState 
-- @param self
-- @param #int state
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getTitleLabel 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getPreferredSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getVerticalMargin 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Returns the title label used for a state.<br>
-- param state The state that uses the title label. Possible values are described<br>
-- in "CCControlState".
-- @function [parent=#ControlButton] getTitleLabelForState 
-- @param self
-- @param #int state
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setMargins 
-- @param self
-- @param #int marginH
-- @param #int marginV
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#ControlButton] getCurrentTitle
-- @param self
-- @return string#string ret (return value: string)

--------------------------------
-- 
-- @function [parent=#ControlButton] initWithLabelAndBackgroundSprite 
-- @param self
-- @param #cc.Node label
-- @param #ccui.Scale9Sprite backgroundSprite
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] getZoomOnTouchDown 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns the title used for a state.<br>
-- param state The state that uses the title. Possible values are described in<br>
-- "CCControlState".<br>
-- return The title for the specified state.
-- @function [parent=#ControlButton] getTitleForState 
-- @param self
-- @param #int state
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, ccui.Scale9Sprite         
-- @overload self         
-- @overload self, cc.Node, ccui.Scale9Sprite         
-- @overload self, string, string, float         
-- @function [parent=#ControlButton] create
-- @param self
-- @param #string title
-- @param #string fontName
-- @param #float fontSize
-- @return ControlButton#ControlButton ret (return value: cc.ControlButton)

--------------------------------
-- 
-- @function [parent=#ControlButton] setEnabled 
-- @param self
-- @param #bool enabled
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] onTouchEnded 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setColor 
-- @param self
-- @param #color3b_table 
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] onTouchMoved 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setSelected 
-- @param self
-- @param #bool enabled
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] onTouchCancelled 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] needsLayout 
-- @param self
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] onTouchBegan 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char parentOpacity
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setHighlighted 
-- @param self
-- @param #bool enabled
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] updateDisplayedColor 
-- @param self
-- @param #color3b_table parentColor
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- 
-- @function [parent=#ControlButton] setOpacity 
-- @param self
-- @param #unsigned char var
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
--------------------------------
-- js ctor
-- @function [parent=#ControlButton] ControlButton 
-- @param self
-- @return ControlButton#ControlButton self (return value: cc.ControlButton)
        
return nil
