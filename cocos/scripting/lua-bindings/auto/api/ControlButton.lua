
--------------------------------
-- @module ControlButton
-- @extend Control
-- @parent_module cc

--------------------------------
-- @function [parent=#ControlButton] isPushed 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ControlButton] setSelected 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ControlButton] setTitleLabelForState 
-- @param self
-- @param #cc.Node node
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] setAdjustBackgroundImage 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ControlButton] setHighlighted 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ControlButton] setZoomOnTouchDown 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ControlButton] setTitleForState 
-- @param self
-- @param #string str
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] setLabelAnchorPoint 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#ControlButton] getLabelAnchorPoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleTTFSizeForState 
-- @param self
-- @param #int state
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ControlButton] setTitleTTFForState 
-- @param self
-- @param #string str
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] setTitleTTFSizeForState 
-- @param self
-- @param #float float
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] setTitleLabel 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ControlButton] setPreferredSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#ControlButton] getCurrentTitleColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#ControlButton] setEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ControlButton] getBackgroundSpriteForState 
-- @param self
-- @param #int state
-- @return Scale9Sprite#Scale9Sprite ret (return value: cc.Scale9Sprite)
        
--------------------------------
-- @function [parent=#ControlButton] getHorizontalOrigin 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#ControlButton] needsLayout 
-- @param self
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#ControlButton] getCurrentTitle
-- @param self
-- @return string#string ret (retunr value: string)

--------------------------------
-- @function [parent=#ControlButton] getScaleRatio 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleTTFForState 
-- @param self
-- @param #int state
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#ControlButton] getBackgroundSprite 
-- @param self
-- @return Scale9Sprite#Scale9Sprite ret (return value: cc.Scale9Sprite)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleColorForState 
-- @param self
-- @param #int state
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#ControlButton] setTitleColorForState 
-- @param self
-- @param #color3b_table color3b
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] doesAdjustBackgroundImage 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ControlButton] setBackgroundSpriteFrameForState 
-- @param self
-- @param #cc.SpriteFrame spriteframe
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] setBackgroundSpriteForState 
-- @param self
-- @param #cc.Scale9Sprite scale9sprite
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] setScaleRatio 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ControlButton] setBackgroundSprite 
-- @param self
-- @param #cc.Scale9Sprite scale9sprite
        
--------------------------------
-- @function [parent=#ControlButton] getTitleLabel 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#ControlButton] getPreferredSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#ControlButton] getVerticalMargin 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleLabelForState 
-- @param self
-- @param #int state
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#ControlButton] setMargins 
-- @param self
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#ControlButton] setTitleBMFontForState 
-- @param self
-- @param #string str
-- @param #int state
        
--------------------------------
-- @function [parent=#ControlButton] getTitleBMFontForState 
-- @param self
-- @param #int state
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#ControlButton] getZoomOnTouchDown 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleForState 
-- @param self
-- @param #int state
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, cc.Scale9Sprite         
-- @overload self         
-- @overload self, cc.Node, cc.Scale9Sprite         
-- @overload self, string, string, float         
-- @function [parent=#ControlButton] create
-- @param self
-- @param #string str
-- @param #string str
-- @param #float float
-- @return ControlButton#ControlButton ret (retunr value: cc.ControlButton)

--------------------------------
-- @function [parent=#ControlButton] onTouchMoved 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ControlButton] onTouchEnded 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ControlButton] setColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#ControlButton] onTouchCancelled 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ControlButton] setOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#ControlButton] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#ControlButton] updateDisplayedColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#ControlButton] onTouchBegan 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return bool#bool ret (return value: bool)
        
return nil
