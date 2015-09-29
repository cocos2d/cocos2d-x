
--------------------------------
-- @module Widget
-- @extend ProtectedNode,LayoutParameterProtocol
-- @parent_module ccui

--------------------------------
-- Toggle layout component enable.<br>
-- param enable Layout Component of a widget<br>
-- return void
-- @function [parent=#Widget] setLayoutComponentEnabled 
-- @param self
-- @param #bool enable
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Changes the percent that is widget's percent size<br>
-- param percent that is widget's percent size
-- @function [parent=#Widget] setSizePercent 
-- @param self
-- @param #vec2_table percent
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Get the user defined widget size.<br>
-- return User defined size.
-- @function [parent=#Widget] getCustomSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Gets the left boundary position of this widget in parent's coordination system.<br>
-- return The left boundary position of this widget.
-- @function [parent=#Widget] getLeftBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Sets whether the widget should be flipped horizontally or not.<br>
-- param flippedX true if the widget should be flipped horizaontally, false otherwise.
-- @function [parent=#Widget] setFlippedX 
-- @param self
-- @param #bool flippedX
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Set callback name.<br>
-- param callbackName A string representation of callback name.
-- @function [parent=#Widget] setCallbackName 
-- @param self
-- @param #string callbackName
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Gets the inner Renderer node of widget.<br>
-- For example, a button's Virtual Renderer is it's texture renderer.<br>
-- return Node pointer.
-- @function [parent=#Widget] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- brief Allow widget touch events to propagate to its parents. Set false will disable propagation<br>
-- param isPropagate  True to allow propagation, false otherwise.<br>
-- since v3.3
-- @function [parent=#Widget] setPropagateTouchEvents 
-- @param self
-- @param #bool isPropagate
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Query whether unify size enable state. <br>
-- return true represent the widget use Unify Size, false represent the widget couldn't use Unify Size
-- @function [parent=#Widget] isUnifySizeEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get size percent of widget.<br>
-- return Percent size.
-- @function [parent=#Widget] getSizePercent 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Set the percent(x,y) of the widget in OpenGL coordinates<br>
-- param percent  The percent (x,y) of the widget in OpenGL coordinates
-- @function [parent=#Widget] setPositionPercent 
-- @param self
-- @param #vec2_table percent
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Toggle widget swallow touch option.<br>
-- brief Specify widget to swallow touches or not<br>
-- param swallow True to swallow touch, false otherwise.<br>
-- since v3.3
-- @function [parent=#Widget] setSwallowTouches 
-- @param self
-- @param #bool swallow
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Get the content size of widget.<br>
-- warning This API exists mainly for keeping back compatibility.<br>
-- return 
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
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Changes the position type of the widget<br>
-- see `PositionType`<br>
-- param type  the position type of widget
-- @function [parent=#Widget] setPositionType 
-- @param self
-- @param #int type
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Query whether the widget ignores user deinfed content size or not<br>
-- return True means ignore user defined content size, false otherwise.
-- @function [parent=#Widget] isIgnoreContentAdaptWithSize 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get the virtual renderer's size<br>
-- return Widget virtual renderer size.
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
-- return LayoutParameter
-- @function [parent=#Widget] getLayoutParameter 
-- @param self
-- @return LayoutParameter#LayoutParameter ret (return value: ccui.LayoutParameter)
        
--------------------------------
-- Gets the position type of the widget<br>
-- see `PositionType`<br>
-- return type  the position type of widget
-- @function [parent=#Widget] getPositionType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Gets the top boundary position of this widget in parent's coordination system.<br>
-- return The top boundary position of this widget.
-- @function [parent=#Widget] getTopBoundary 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Toggle whether ignore user defined content size for widget.<br>
-- Set true will ignore user defined content size which means <br>
-- the widget size is always equal to the return value of `getVirtualRendererSize`.<br>
-- param ignore set member variabl _ignoreSize to ignore
-- @function [parent=#Widget] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- When a widget is in a layout, you could call this method to get the next focused widget within a specified direction. <br>
-- If the widget is not in a layout, it will return itself<br>
-- param direction the direction to look for the next focused widget in a layout<br>
-- param current  the current focused widget<br>
-- return the next focused widget in a layout
-- @function [parent=#Widget] findNextFocusedWidget 
-- @param self
-- @param #int direction
-- @param #ccui.Widget current
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Determines if the widget is enabled or not.<br>
-- return true if the widget is enabled, false if the widget is disabled.
-- @function [parent=#Widget] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Query whether widget is focused or not.<br>
-- return  whether the widget is focused or not
-- @function [parent=#Widget] isFocused 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Gets the touch began point of widget when widget is selected.<br>
-- return the touch began point.
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
-- Query callback name.<br>
-- return The callback name.
-- @function [parent=#Widget] getCallbackName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Get the action tag.<br>
-- return Action tag.
-- @function [parent=#Widget] getActionTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Gets position of widget in world space.<br>
-- return Position of widget in world space.
-- @function [parent=#Widget] getWorldPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Query widget's focus enable state.<br>
-- return true represent the widget could accept focus, false represent the widget couldn't accept focus
-- @function [parent=#Widget] isFocusEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Toggle widget focus status.<br>
-- param focus  pass true to let the widget get focus or pass false to let the widget lose focus<br>
-- return void
-- @function [parent=#Widget] setFocused 
-- @param self
-- @param #bool focus
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Set the tag of action.<br>
-- param tag  A integer tag value.
-- @function [parent=#Widget] setActionTag 
-- @param self
-- @param #int tag
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Sets whether the widget is touch enabled.<br>
-- The default value is false, a widget is default to touch disabled.<br>
-- param enabled   True if the widget is touch enabled, false if the widget is touch disabled.
-- @function [parent=#Widget] setTouchEnabled 
-- @param self
-- @param #bool enabled
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Sets whether the widget should be flipped vertically or not.<br>
-- param flippedY true if the widget should be flipped vertically, flase otherwise.
-- @function [parent=#Widget] setFlippedY 
-- @param self
-- @param #bool flippedY
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Sets whether the widget is enabled<br>
-- true if the widget is enabled, widget may be touched , false if the widget is disabled, widget cannot be touched.<br>
-- Note: If you want to change the widget's appearance  to disabled state, you should also call  `setBright(false)`.<br>
-- The default value is true, a widget is default to enable touch.<br>
-- param enabled Set to true to enable touch, false otherwise.
-- @function [parent=#Widget] setEnabled 
-- @param self
-- @param #bool enabled
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Gets the right boundary position of this widget in parent's coordination system.<br>
-- return The right boundary position of this widget.
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
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Sets a LayoutParameter to widget.<br>
-- see LayoutParameter<br>
-- param parameter LayoutParameter pointer
-- @function [parent=#Widget] setLayoutParameter 
-- @param self
-- @param #ccui.LayoutParameter parameter
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Create a new widget copy of the original one.<br>
-- return A cloned widget copy of original.
-- @function [parent=#Widget] clone 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Allow widget to accept focus.<br>
-- param enable pass true/false to enable/disable the focus ability of a widget<br>
-- return void
-- @function [parent=#Widget] setFocusEnabled 
-- @param self
-- @param #bool enable
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Gets the bottom boundary position of this widget in parent's coordination system.<br>
-- return The bottom boundary position of this widget.
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
-- Dispatch a EventFocus through a EventDispatcher<br>
-- param widgetLoseFocus  The widget which lose its focus<br>
-- param widgetGetFocus he widget whihc get its focus<br>
-- return void
-- @function [parent=#Widget] dispatchFocusEvent 
-- @param self
-- @param #ccui.Widget widgetLoseFocus
-- @param #ccui.Widget widgetGetFocus
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Toggle use unify size.<br>
-- param enable True to use unify size, false otherwise.<br>
-- return void
-- @function [parent=#Widget] setUnifySizeEnabled 
-- @param self
-- @param #bool enable
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Return whether the widget is propagate touch events to its parents or not<br>
-- return whether touch event propagation is allowed or not.<br>
-- since v3.3
-- @function [parent=#Widget] isPropagateTouchEvents 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Return a current focused widget in your UI scene.<br>
-- No matter what widget object you call this method on , it will return you the exact one focused widget.
-- @function [parent=#Widget] getCurrentFocusedWidget 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Checks a point is in widget's content space.<br>
-- This function is used for determining touch area of widget.<br>
-- param pt        The point in `Vec2`.<br>
-- param camera    The camera look at widget, used to convert GL screen point to near/far plane.<br>
-- param p         Point to a Vec3 for store the intersect point, if don't need them set to nullptr.<br>
-- return true if the point is in widget's content space, flase otherwise.
-- @function [parent=#Widget] hitTest 
-- @param self
-- @param #vec2_table pt
-- @param #cc.Camera camera
-- @param #vec3_table p
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Query whether layout component is enabled or not. <br>
-- return true represent the widget use Layout Component, false represent the widget couldn't use Layout Component.
-- @function [parent=#Widget] isLayoutComponentEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- when a widget calls this method, it will get focus immediately.
-- @function [parent=#Widget] requestFocus 
-- @param self
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- @overload self, size_table         
-- @overload self         
-- @function [parent=#Widget] updateSizeAndPosition
-- @param self
-- @param #size_table parentSize
-- @return Widget#Widget self (return value: ccui.Widget)

--------------------------------
-- This method is called when a focus change event happens<br>
-- param widgetLostFocus  The widget which lose its focus<br>
-- param widgetGetFocus  The widget whihc get its focus<br>
-- return void
-- @function [parent=#Widget] onFocusChange 
-- @param self
-- @param #ccui.Widget widgetLostFocus
-- @param #ccui.Widget widgetGetFocus
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Widget] getTouchMovePosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Gets the size type of widget.<br>
-- see `SizeType`
-- @function [parent=#Widget] getSizeType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Query callback type.<br>
-- return Callback type string.
-- @function [parent=#Widget] getCallbackType 
-- @param self
-- @return string#string ret (return value: string)
        
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
-- brief Propagate touch events to its parents
-- @function [parent=#Widget] propagateTouchEvent 
-- @param self
-- @param #int event
-- @param #ccui.Widget sender
-- @param #cc.Touch touch
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Returns the flag which indicates whether the widget is flipped horizontally or not.<br>
-- It not only flips the texture of the widget, but also the texture of the widget's children.<br>
-- Also, flipping relies on widget's anchor point.<br>
-- Internally, it just use setScaleX(-1) to flip the widget.<br>
-- return true if the widget is flipped horizaontally, false otherwise.
-- @function [parent=#Widget] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Return the flag which indicates whether the widget is flipped vertically or not.<br>
-- It not only flips the texture of the widget, but also the texture of the widget's children.<br>
-- Also, flipping relies on widget's anchor point.<br>
-- Internally, it just use setScaleY(-1) to flip the widget.<br>
-- return true if the widget is flipped vertically, flase otherwise.
-- @function [parent=#Widget] isFlippedY 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Checks a point if in parent's area.<br>
-- param pt A point in `Vec2`.<br>
-- return true if the point is in parent's area, flase otherwise.
-- @function [parent=#Widget] isClippingParentContainsPoint 
-- @param self
-- @param #vec2_table pt
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Changes the size type of widget.<br>
-- see `SizeType`<br>
-- param type that is widget's size type
-- @function [parent=#Widget] setSizeType 
-- @param self
-- @param #int type
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Widget] interceptTouchEvent 
-- @param self
-- @param #int event
-- @param #ccui.Widget sender
-- @param #cc.Touch touch
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Sets whether the widget is bright<br>
-- The default value is true, a widget is default to bright<br>
-- param bright   true if the widget is bright, false if the widget is dark.
-- @function [parent=#Widget] setBright 
-- @param self
-- @param #bool bright
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Set callback type.<br>
-- param callbackType A string representation of callback type.
-- @function [parent=#Widget] setCallbackType 
-- @param self
-- @param #string callbackType
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Return whether the widget is swallowing touch or not<br>
-- return Whether touch is swallowed.<br>
-- since v3.3
-- @function [parent=#Widget] isSwallowTouches 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Widget] enableDpadNavigation 
-- @param self
-- @param #bool enable
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Create and return a empty Widget instance pointer.
-- @function [parent=#Widget] create 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Widget] setScaleY 
-- @param self
-- @param #float scaleY
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Widget] setScaleX 
-- @param self
-- @param #float scaleX
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Widget] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Widget] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the string representation of widget class name<br>
-- return get the class description.
-- @function [parent=#Widget] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, float, float         
-- @overload self, float         
-- @function [parent=#Widget] setScale
-- @param self
-- @param #float scalex
-- @param #float scaley
-- @return Widget#Widget self (return value: ccui.Widget)

--------------------------------
-- 
-- @function [parent=#Widget] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Changes the position (x,y) of the widget in OpenGL coordinates<br>
-- Usually we use p(x,y) to compose a Vec2 object.<br>
-- The original point (0,0) is at the left-bottom corner of screen.<br>
-- param pos  The position (x,y) of the widget in OpenGL coordinates
-- @function [parent=#Widget] setPosition 
-- @param self
-- @param #vec2_table pos
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- Changes the size that is widget's size<br>
-- param contentSize A content size in `Size`.
-- @function [parent=#Widget] setContentSize 
-- @param self
-- @param #size_table contentSize
-- @return Widget#Widget self (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Widget] getScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Default constructor<br>
-- js ctor<br>
-- lua new
-- @function [parent=#Widget] Widget 
-- @param self
-- @return Widget#Widget self (return value: ccui.Widget)
        
return nil
