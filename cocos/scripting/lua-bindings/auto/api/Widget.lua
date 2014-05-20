
--------------------------------
-- @module Widget
-- @extend ProtectedNode

--------------------------------
-- @function [parent=#Widget] setSizePercent 
-- @param self
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#Widget] getCustomSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] setFlippedY 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] setFlippedX 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] getLeftInParent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] getTouchEndPos 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#Widget] setPositionPercent 
-- @param self
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#Widget] getLayoutSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] setHighlighted 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] setPositionType 
-- @param self
-- @param #ccui.Widget::PositionType positiontype
        
--------------------------------
-- @function [parent=#Widget] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Widget] isIgnoreContentAdaptWithSize 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getBottomInParent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] isHighlighted 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getLayoutParameter 
-- @param self
-- @param #ccui.LayoutParameter::Type type
-- @return LayoutParameter#LayoutParameter ret (return value: ccui.LayoutParameter)
        
--------------------------------
-- @function [parent=#Widget] getPositionType 
-- @param self
-- @return Widget::PositionType#Widget::PositionType ret (return value: ccui.Widget::PositionType)
        
--------------------------------
-- @function [parent=#Widget] getChildByName 
-- @param self
-- @param #string str
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] isFocused 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] findNextFocusedWidget 
-- @param self
-- @param #ccui.Widget::FocusDirection focusdirection
-- @param #ccui.Widget widget
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] isTouchEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getActionTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Widget] getWorldPosition 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#Widget] setFocused 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] setTouchEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] clone 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] getTouchMovePos 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#Widget] setEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#Widget] setBrightStyle 
-- @param self
-- @param #ccui.Widget::BrightStyle brightstyle
        
--------------------------------
-- @function [parent=#Widget] setName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#Widget] setLayoutParameter 
-- @param self
-- @param #ccui.LayoutParameter layoutparameter
        
--------------------------------
-- @function [parent=#Widget] getSizePercent 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#Widget] getTouchStartPos 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#Widget] setFocusEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] setActionTag 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Widget] isBright 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] clippingParentAreaContainPoint 
-- @param self
-- @param #cc.Vec2 vec2
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getCurrentFocusedWidget 
-- @param self
-- @param #bool bool
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] getTopInParent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] requestFocus 
-- @param self
        
--------------------------------
-- overload function: updateSizeAndPosition(size_table)
--          
-- overload function: updateSizeAndPosition()
--          
-- @function [parent=#Widget] updateSizeAndPosition
-- @param self
-- @param #size_table size

--------------------------------
-- @function [parent=#Widget] getSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] getRightInParent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] getSizeType 
-- @param self
-- @return Widget::SizeType#Widget::SizeType ret (return value: ccui.Widget::SizeType)
        
--------------------------------
-- @function [parent=#Widget] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] addTouchEventListener 
-- @param self
-- @param #function func
        
--------------------------------
-- @function [parent=#Widget] getPositionPercent 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#Widget] hitTest 
-- @param self
-- @param #cc.Vec2 vec2
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] isFlippedY 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] setSizeType 
-- @param self
-- @param #ccui.Widget::SizeType sizetype
        
--------------------------------
-- @function [parent=#Widget] checkChildInfo 
-- @param self
-- @param #int int
-- @param #ccui.Widget widget
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#Widget] setSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#Widget] setBright 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] isFocusEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] create 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] setColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#Widget] getColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#Widget] setOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#Widget] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#Widget] setPosition 
-- @param self
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#Widget] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Widget] Widget 
-- @param self
        
return nil
