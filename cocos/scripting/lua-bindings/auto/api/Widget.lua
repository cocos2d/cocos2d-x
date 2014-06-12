
--------------------------------
-- @module Widget
-- @extend ProtectedNode,LayoutParameterProtocol

--------------------------------
-- @function [parent=#Widget] setSizePercent 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#Widget] getCustomSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] getLeftBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] setFlippedX 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#Widget] getSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] setPositionPercent 
-- @param self
-- @param #vec2_table vec2
        
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
-- @function [parent=#Widget] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] isHighlighted 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getLayoutParameter 
-- @param self
-- @return LayoutParameter#LayoutParameter ret (return value: ccui.LayoutParameter)
        
--------------------------------
-- @function [parent=#Widget] findNextFocusedWidget 
-- @param self
-- @param #ccui.Widget::FocusDirection focusdirection
-- @param #ccui.Widget widget
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] getPositionType 
-- @param self
-- @return Widget::PositionType#Widget::PositionType ret (return value: ccui.Widget::PositionType)
        
--------------------------------
-- @function [parent=#Widget] getTopBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
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
-- @function [parent=#Widget] getTouchBeganPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
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
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Widget] setFocused 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] setActionTag 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Widget] setTouchEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] setFlippedY 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] setEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] getRightBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
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
-- @function [parent=#Widget] clone 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] setFocusEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] getBottomBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] isBright 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getCurrentFocusedWidget 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
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
-- @function [parent=#Widget] getSizePercent 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Widget] getTouchMovePosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
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
-- @function [parent=#Widget] getTouchEndPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Widget] getPositionPercent 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Widget] hitTest 
-- @param self
-- @param #vec2_table vec2
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
-- @function [parent=#Widget] isClippingParentContainsPoint 
-- @param self
-- @param #vec2_table vec2
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] setSizeType 
-- @param self
-- @param #ccui.Widget::SizeType sizetype
        
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
-- @function [parent=#Widget] enableDpadNavigation 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] create 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Widget] setPosition 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#Widget] Widget 
-- @param self
        
return nil
