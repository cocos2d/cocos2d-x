
--------------------------------
-- @module Widget
--------------------------------
-- @function [parent=#Widget] setSizePercent 
-- @param self
-- @param #point_table point
        
--------------------------------
-- @function [parent=#Widget] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
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
-- @function [parent=#Widget] getNodeByTag 
-- @param self
-- @param #int int
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#Widget] getTouchEndPos 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#Widget] setPositionPercent 
-- @param self
-- @param #point_table point
        
--------------------------------
-- @function [parent=#Widget] getNodes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#Widget] getLayoutSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] setPositionType 
-- @param self
-- @param #ccui.PositionType positiontype
        
--------------------------------
-- @function [parent=#Widget] getName 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- @function [parent=#Widget] isIgnoreContentAdaptWithSize 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- overload function: updateSizeAndPosition(size_table)
--          
-- overload function: updateSizeAndPosition()
--          
-- @function [parent=#Widget] updateSizeAndPosition
-- @param self
-- @param #size_table size

--------------------------------
-- @function [parent=#Widget] getBottomInParent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] getActionTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Widget] getLayoutParameter 
-- @param self
-- @param #ccui.LayoutParameterType layoutparametertype
-- @return LayoutParameter#LayoutParameter ret (return value: ccui.LayoutParameter)
        
--------------------------------
-- @function [parent=#Widget] getPositionType 
-- @param self
-- @return PositionType#PositionType ret (return value: ccui.PositionType)
        
--------------------------------
-- @function [parent=#Widget] setName 
-- @param self
-- @param #char char
        
--------------------------------
-- @function [parent=#Widget] getChildByName 
-- @param self
-- @param #char char
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] removeNodeByTag 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Widget] isTouchEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Widget] getWorldPosition 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#Widget] didNotSelectSelf 
-- @param self
        
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
-- @return point_table#point_table ret (return value: point_table)
        
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
-- @param #ccui.BrightStyle brightstyle
        
--------------------------------
-- overload function: addNode(cc.Node, int)
--          
-- overload function: addNode(cc.Node)
--          
-- overload function: addNode(cc.Node, int, int)
--          
-- @function [parent=#Widget] addNode
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int

--------------------------------
-- @function [parent=#Widget] setLayoutParameter 
-- @param self
-- @param #ccui.LayoutParameter layoutparameter
        
--------------------------------
-- @function [parent=#Widget] getSizePercent 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#Widget] getTouchStartPos 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#Widget] getLeftInParent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] setActionTag 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#Widget] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] isBright 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] clippingParentAreaContainPoint 
-- @param self
-- @param #point_table point
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] getTopInParent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Widget] getWidgetType 
-- @param self
-- @return WidgetType#WidgetType ret (return value: ccui.WidgetType)
        
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
-- @return SizeType#SizeType ret (return value: ccui.SizeType)
        
--------------------------------
-- @function [parent=#Widget] removeNode 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#Widget] removeAllNodes 
-- @param self
        
--------------------------------
-- @function [parent=#Widget] getPositionPercent 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#Widget] hitTest 
-- @param self
-- @param #point_table point
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] isFocused 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] isFlippedY 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Widget] setSizeType 
-- @param self
-- @param #ccui.SizeType sizetype
        
--------------------------------
-- @function [parent=#Widget] checkChildInfo 
-- @param self
-- @param #int int
-- @param #ccui.Widget widget
-- @param #point_table point
        
--------------------------------
-- @function [parent=#Widget] setSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#Widget] setBright 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Widget] create 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Widget] Widget 
-- @param self
        
return nil
