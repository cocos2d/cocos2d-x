
--------------------------------
-- @module Widget
-- @extend ProtectedNode,LayoutParameterProtocol
-- @parent_module ccui

--------------------------------
-- Changes the percent that is widget's percent size<br>
-- param percent that is widget's percent size
-- @function [parent=#Widget] setSizePercent 
-- @param self
-- @param #vec2_table percent
        
--------------------------------
-- 
-- @function [parent=#Widget] getCustomSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#Widget] getLeftBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Sets whether the widget should be flipped horizontally or not.<br>
-- param bFlippedX true if the widget should be flipped horizaontally, false otherwise.
-- @function [parent=#Widget] setFlippedX 
-- @param self
-- @param #bool flippedX
        
--------------------------------
-- Gets the Virtual Renderer of widget.<br>
-- For example, a button's Virtual Renderer is it's texture renderer.<br>
-- return Node pointer.
-- @function [parent=#Widget] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- brief Allow widget touch events to propagate to its parents. Set false will disable propagation
-- @function [parent=#Widget] setPropagateTouchEvents 
-- @param self
-- @param #bool isPropagate
        
--------------------------------
-- Returns size percent of widget<br>
-- return size percent
-- @function [parent=#Widget] getSizePercent 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Set the percent(x,y) of the widget in OpenGL coordinates<br>
-- param percent  The percent (x,y) of the widget in OpenGL coordinates
-- @function [parent=#Widget] setPositionPercent 
-- @param self
-- @param #vec2_table percent
        
--------------------------------
-- brief Specify widget to swallow touches or not
-- @function [parent=#Widget] setSwallowTouches 
-- @param self
-- @param #bool swallow
        
--------------------------------
-- 
-- @function [parent=#Widget] getLayoutSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Sets whether the widget is hilighted<br>
-- The default value is false, a widget is default to not hilighted<br>
-- param hilight   true if the widget is hilighted, false if the widget is not hilighted.
-- @function [parent=#Widget] setHighlighted 
-- @param self
-- @param #bool hilight
        
--------------------------------
-- Changes the position type of the widget<br>
-- see PositionType<br>
-- param type  the position type of widget
-- @function [parent=#Widget] setPositionType 
-- @param self
-- @param #int type
        
--------------------------------
-- Query whether the widget ignores user deinfed content size or not<br>
-- return bool
-- @function [parent=#Widget] isIgnoreContentAdaptWithSize 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Determines if the widget is highlighted<br>
-- return true if the widget is highlighted, false if the widget is not hignlighted .
-- @function [parent=#Widget] isHighlighted 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Gets LayoutParameter of widget.<br>
-- see LayoutParameter<br>
-- param type  Relative or Linear<br>
-- return LayoutParameter
-- @function [parent=#Widget] getLayoutParameter 
-- @param self
-- @return LayoutParameter#LayoutParameter ret (return value: ccui.LayoutParameter)
        
--------------------------------
-- Checks a point if is in widget's space<br>
-- param point<br>
-- return true if the point is in widget's space, flase otherwise.
-- @function [parent=#Widget] hitTest 
-- @param self
-- @param #vec2_table pt
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Gets the position type of the widget<br>
-- see PositionType<br>
-- return type  the position type of widget
-- @function [parent=#Widget] getPositionType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Widget] getTopBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Note: when you set _ignoreSize to true, no matther you call setContentSize or not, <br>
-- the widget size is always equal to the return value of the member function getVirtualRendererSize.<br>
-- param ignore, set member variabl _ignoreSize to ignore
-- @function [parent=#Widget] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
        
--------------------------------
-- When a widget is in a layout, you could call this method to get the next focused widget within a specified direction. <br>
-- If the widget is not in a layout, it will return itself<br>
-- param dir the direction to look for the next focused widget in a layout<br>
-- param current  the current focused widget<br>
-- return the next focused widget in a layout
-- @function [parent=#Widget] findNextFocusedWidget 
-- @param self
-- @param #int direction
-- @param #ccui.Widget current
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Determines if the widget is enabled<br>
-- return true if the widget is enabled, false if the widget is disabled.
-- @function [parent=#Widget] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- return  whether the widget is focused or not
-- @function [parent=#Widget] isFocused 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] getTouchBeganPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Determines if the widget is touch enabled<br>
-- return true if the widget is touch enabled, false if the widget is touch disabled.
-- @function [parent=#Widget] isTouchEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] getActionTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Gets world position of widget.<br>
-- return world position of widget.
-- @function [parent=#Widget] getWorldPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- return true represent the widget could accept focus, false represent the widget couldn't accept focus
-- @function [parent=#Widget] isFocusEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- param focus  pass true to let the widget get focus or pass false to let the widget lose focus<br>
-- return void
-- @function [parent=#Widget] setFocused 
-- @param self
-- @param #bool focus
        
--------------------------------
-- 
-- @function [parent=#Widget] setActionTag 
-- @param self
-- @param #int tag
        
--------------------------------
-- Sets whether the widget is touch enabled<br>
-- The default value is false, a widget is default to touch disabled<br>
-- param visible   true if the widget is touch enabled, false if the widget is touch disabled.
-- @function [parent=#Widget] setTouchEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- Sets whether the widget should be flipped vertically or not.<br>
-- param bFlippedY true if the widget should be flipped vertically, flase otherwise.
-- @function [parent=#Widget] setFlippedY 
-- @param self
-- @param #bool flippedY
        
--------------------------------
-- Sets whether the widget is enabled<br>
-- true if the widget is enabled, widget may be touched , false if the widget is disabled, widget cannot be touched.<br>
-- The default value is true, a widget is default to enabled<br>
-- param enabled
-- @function [parent=#Widget] setEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- 
-- @function [parent=#Widget] getRightBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- To set the bright style of widget.<br>
-- see BrightStyle<br>
-- param style   BrightStyle::NORMAL means the widget is in normal state, BrightStyle::HIGHLIGHT means the widget is in highlight state.
-- @function [parent=#Widget] setBrightStyle 
-- @param self
-- @param #int style
        
--------------------------------
-- Sets a LayoutParameter to widget.<br>
-- see LayoutParameter<br>
-- param LayoutParameter pointer<br>
-- param type  Relative or Linear
-- @function [parent=#Widget] setLayoutParameter 
-- @param self
-- @param #ccui.LayoutParameter parameter
        
--------------------------------
-- 
-- @function [parent=#Widget] clone 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- param enable pass true/false to enable/disable the focus ability of a widget<br>
-- return void
-- @function [parent=#Widget] setFocusEnabled 
-- @param self
-- @param #bool enable
        
--------------------------------
-- 
-- @function [parent=#Widget] getBottomBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Determines if the widget is bright<br>
-- return true if the widget is bright, false if the widget is dark.
-- @function [parent=#Widget] isBright 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] isPropagateTouchEvents 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] getCurrentFocusedWidget 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- when a widget calls this method, it will get focus immediately.
-- @function [parent=#Widget] requestFocus 
-- @param self
        
--------------------------------
-- @overload self, size_table         
-- @overload self         
-- @function [parent=#Widget] updateSizeAndPosition
-- @param self
-- @param #size_table parentSize

--------------------------------
-- 
-- @function [parent=#Widget] getTouchMovePosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Gets the size type of widget.<br>
-- see SizeType<br>
-- param type that is widget's size type
-- @function [parent=#Widget] getSizeType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Widget] addTouchEventListener 
-- @param self
-- @param #function callback
        
--------------------------------
-- 
-- @function [parent=#Widget] getTouchEndPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Gets the percent (x,y) of the widget in OpenGL coordinates<br>
-- see setPosition(const Vec2&)<br>
-- return The percent (x,y) of the widget in OpenGL coordinates
-- @function [parent=#Widget] getPositionPercent 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Set a click event handler to the widget
-- @function [parent=#Widget] addClickEventListener 
-- @param self
-- @param #function callback
        
--------------------------------
-- Returns the flag which indicates whether the widget is flipped horizontally or not.<br>
-- It only flips the texture of the widget, and not the texture of the widget's children.<br>
-- Also, flipping the texture doesn't alter the anchorPoint.<br>
-- If you want to flip the anchorPoint too, and/or to flip the children too use:<br>
-- widget->setScaleX(sprite->getScaleX() * -1);<br>
-- return true if the widget is flipped horizaontally, false otherwise.
-- @function [parent=#Widget] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Return the flag which indicates whether the widget is flipped vertically or not.<br>
-- It only flips the texture of the widget, and not the texture of the widget's children.<br>
-- Also, flipping the texture doesn't alter the anchorPoint.<br>
-- If you want to flip the anchorPoint too, and/or to flip the children too use:<br>
-- widget->setScaleY(widget->getScaleY() * -1);<br>
-- return true if the widget is flipped vertically, flase otherwise.
-- @function [parent=#Widget] isFlippedY 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] isClippingParentContainsPoint 
-- @param self
-- @param #vec2_table pt
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Changes the size type of widget.<br>
-- see SizeType<br>
-- param type that is widget's size type
-- @function [parent=#Widget] setSizeType 
-- @param self
-- @param #int type
        
--------------------------------
-- Sets whether the widget is bright<br>
-- The default value is true, a widget is default to bright<br>
-- param visible   true if the widget is bright, false if the widget is dark.
-- @function [parent=#Widget] setBright 
-- @param self
-- @param #bool bright
        
--------------------------------
-- 
-- @function [parent=#Widget] isSwallowTouches 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] enableDpadNavigation 
-- @param self
-- @param #bool enable
        
--------------------------------
-- Allocates and initializes a widget.
-- @function [parent=#Widget] create 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#Widget] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Changes the position (x,y) of the widget in OpenGL coordinates<br>
-- Usually we use p(x,y) to compose Vec2 object.<br>
-- The original point (0,0) is at the left-bottom corner of screen.<br>
-- param position  The position (x,y) of the widget in OpenGL coordinates
-- @function [parent=#Widget] setPosition 
-- @param self
-- @param #vec2_table pos
        
--------------------------------
-- 
-- @function [parent=#Widget] setContentSize 
-- @param self
-- @param #size_table contentSize
        
--------------------------------
-- Default constructor
-- @function [parent=#Widget] Widget 
-- @param self
        
return nil
