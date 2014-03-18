
--------------------------------
-- @module ControlButton
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
-- @param #cc.Control::State state
        
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
-- @param #cc.Control::State state
        
--------------------------------
-- @function [parent=#ControlButton] setLabelAnchorPoint 
-- @param self
-- @param #point_table point
        
--------------------------------
-- @function [parent=#ControlButton] getLabelAnchorPoint 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleTTFSizeForState 
-- @param self
-- @param #cc.Control::State state
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ControlButton] setTitleTTFForState 
-- @param self
-- @param #string str
-- @param #cc.Control::State state
        
--------------------------------
-- @function [parent=#ControlButton] setTitleTTFSizeForState 
-- @param self
-- @param #float float
-- @param #cc.Control::State state
        
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
-- @return color3B_table#color3B_table ret (return value: color3B_table)
        
--------------------------------
-- @function [parent=#ControlButton] setEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ControlButton] getBackgroundSpriteForState 
-- @param self
-- @param #cc.Control::State state
-- @return Scale9Sprite#Scale9Sprite ret (return value: cc.Scale9Sprite)
        
--------------------------------
-- @function [parent=#ControlButton] getHorizontalOrigin 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#ControlButton] needsLayout 
-- @param self
        
--------------------------------
-- overload function: getCurrentTitle()
--          
-- overload function: getCurrentTitle()
--          
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
-- @param #cc.Control::State state
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#ControlButton] getBackgroundSprite 
-- @param self
-- @return Scale9Sprite#Scale9Sprite ret (return value: cc.Scale9Sprite)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleColorForState 
-- @param self
-- @param #cc.Control::State state
-- @return color3B_table#color3B_table ret (return value: color3B_table)
        
--------------------------------
-- @function [parent=#ControlButton] setTitleColorForState 
-- @param self
-- @param #color3B_table color3b
-- @param #cc.Control::State state
        
--------------------------------
-- @function [parent=#ControlButton] doesAdjustBackgroundImage 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ControlButton] setBackgroundSpriteFrameForState 
-- @param self
-- @param #cc.SpriteFrame spriteframe
-- @param #cc.Control::State state
        
--------------------------------
-- @function [parent=#ControlButton] setBackgroundSpriteForState 
-- @param self
-- @param #cc.Scale9Sprite scale9sprite
-- @param #cc.Control::State state
        
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
-- @param #cc.Control::State state
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
-- @param #cc.Control::State state
        
--------------------------------
-- @function [parent=#ControlButton] getTitleBMFontForState 
-- @param self
-- @param #cc.Control::State state
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#ControlButton] getZoomOnTouchDown 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ControlButton] getTitleForState 
-- @param self
-- @param #cc.Control::State state
-- @return string#string ret (return value: string)
        
--------------------------------
-- overload function: create(cc.Scale9Sprite)
--          
-- overload function: create()
--          
-- overload function: create(cc.Node, cc.Scale9Sprite)
--          
-- overload function: create(string, string, float)
--          
-- @function [parent=#ControlButton] create
-- @param self
-- @param #string str
-- @param #string str
-- @param #float float
-- @return ControlButton#ControlButton ret (retunr value: cc.ControlButton)

return nil
