
--------------------------------
-- @module Layout
-- @extend Widget,LayoutProtocol
-- @parent_module ccui

--------------------------------
-- Sets background color vector for layout.<br>
-- This setting only take effect when layout's color type is BackGroundColorType::GRADIENT<br>
-- param vector The color vector in `Vec2`.
-- @function [parent=#Layout] setBackGroundColorVector 
-- @param self
-- @param #vec2_table vector
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Change the clipping type of layout.<br>
-- On default, the clipping type is `ClippingType::STENCIL`.<br>
-- see `ClippingType`<br>
-- param type The clipping type of layout.
-- @function [parent=#Layout] setClippingType 
-- @param self
-- @param #int type
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Sets Color Type for layout's background<br>
-- param type   @see `BackGroundColorType`
-- @function [parent=#Layout] setBackGroundColorType 
-- @param self
-- @param #int type
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- If a layout is loop focused which means that the focus movement will be inside the layout<br>
-- param loop  pass true to let the focus movement loop inside the layout
-- @function [parent=#Layout] setLoopFocus 
-- @param self
-- @param #bool loop
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Set layout's background image color.<br>
-- param color Background color value in `Color3B`.
-- @function [parent=#Layout] setBackGroundImageColor 
-- @param self
-- @param #color3b_table color
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Get the layout's background color vector.<br>
-- return Background color vector.
-- @function [parent=#Layout] getBackGroundColorVector 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- see `setClippingType(ClippingType)`
-- @function [parent=#Layout] getClippingType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- return If focus loop is enabled, then it will return true, otherwise it returns false. The default value is false.
-- @function [parent=#Layout] isLoopFocus 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Remove the background image of layout.
-- @function [parent=#Layout] removeBackGroundImage 
-- @param self
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Get the layout's background color opacity.<br>
-- return Background color opacity value.
-- @function [parent=#Layout] getBackGroundColorOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- Gets if layout is clipping enabled.<br>
-- return if layout is clipping enabled.
-- @function [parent=#Layout] isClippingEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Set opacity of background image.<br>
-- param opacity Background image opacity in GLubyte.
-- @function [parent=#Layout] setBackGroundImageOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Sets a background image for layout.<br>
-- param fileName image file path.<br>
-- param texType @see TextureResType. 
-- @function [parent=#Layout] setBackGroundImage 
-- @param self
-- @param #string fileName
-- @param #int texType
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- @overload self, color3b_table, color3b_table         
-- @overload self, color3b_table         
-- @function [parent=#Layout] setBackGroundColor
-- @param self
-- @param #color3b_table startColor
-- @param #color3b_table endColor
-- @return Layout#Layout self (return value: ccui.Layout)

--------------------------------
-- request to refresh widget layout
-- @function [parent=#Layout] requestDoLayout 
-- @param self
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Query background image's capInsets size.<br>
-- return The background image capInsets.
-- @function [parent=#Layout] getBackGroundImageCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Query the layout's background color.<br>
-- return Background color in Color3B.
-- @function [parent=#Layout] getBackGroundColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Toggle layout clipping.<br>
-- If you do need clipping, you pass true to this function.<br>
-- param enabled Pass true to enable clipping, false otherwise.
-- @function [parent=#Layout] setClippingEnabled 
-- @param self
-- @param #bool enabled
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Get color of layout's background image.<br>
-- return Layout's background image color.
-- @function [parent=#Layout] getBackGroundImageColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Query background image scale9 enable status.<br>
-- return Whehter background image is scale9 enabled or not.
-- @function [parent=#Layout] isBackGroundImageScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Query the layout's background color type.<br>
-- return The layout's background color type.
-- @function [parent=#Layout] getBackGroundColorType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get the gradient background end color.<br>
-- return Gradient background end color value.
-- @function [parent=#Layout] getBackGroundEndColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Sets background color opacity of layout.<br>
-- param opacity The opacity in `GLubyte`.
-- @function [parent=#Layout] setBackGroundColorOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Get the opacity of layout's background image.<br>
-- return The opacity of layout's background image.
-- @function [parent=#Layout] getBackGroundImageOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- return To query whether the layout will pass the focus to its children or not. The default value is true
-- @function [parent=#Layout] isPassFocusToChild 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets a background image capinsets for layout, it only affects the scale9 enabled background image<br>
-- param capInsets  The capInsets in Rect.
-- @function [parent=#Layout] setBackGroundImageCapInsets 
-- @param self
-- @param #rect_table capInsets
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Gets background image texture size.<br>
-- return background image texture size.
-- @function [parent=#Layout] getBackGroundImageTextureSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- force refresh widget layout
-- @function [parent=#Layout] forceDoLayout 
-- @param self
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Query layout type.<br>
-- return Get the layout type.
-- @function [parent=#Layout] getLayoutType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- param pass To specify whether the layout pass its focus to its child
-- @function [parent=#Layout] setPassFocusToChild 
-- @param self
-- @param #bool pass
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Get the gradient background start color.<br>
-- return  Gradient background start color value.
-- @function [parent=#Layout] getBackGroundStartColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Enable background image scale9 rendering.<br>
-- param enabled  True means enable scale9 rendering for background image, false otherwise.
-- @function [parent=#Layout] setBackGroundImageScale9Enabled 
-- @param self
-- @param #bool enabled
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Change the layout type.<br>
-- param type Layout type.
-- @function [parent=#Layout] setLayoutType 
-- @param self
-- @param #int type
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Create a empty layout.
-- @function [parent=#Layout] create 
-- @param self
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- 
-- @function [parent=#Layout] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- @overload self, cc.Node, int         
-- @overload self, cc.Node         
-- @overload self, cc.Node, int, int         
-- @overload self, cc.Node, int, string         
-- @function [parent=#Layout] addChild
-- @param self
-- @param #cc.Node child
-- @param #int localZOrder
-- @param #string name
-- @return Layout#Layout self (return value: ccui.Layout)

--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#Layout] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.<br>
-- param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.<br>
-- js removeAllChildren<br>
-- lua removeAllChildren
-- @function [parent=#Layout] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Removes all children from the container with a cleanup.<br>
-- see `removeAllChildrenWithCleanup(bool)`
-- @function [parent=#Layout] removeAllChildren 
-- @param self
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.<br>
-- If the widget is not in a layout, it will return itself<br>
-- param direction the direction to look for the next focused widget in a layout<br>
-- param current  the current focused widget<br>
-- return the next focused widget in a layout
-- @function [parent=#Layout] findNextFocusedWidget 
-- @param self
-- @param #int direction
-- @param #ccui.Widget current
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Layout] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return Layout#Layout self (return value: ccui.Layout)
        
--------------------------------
-- Default constructor<br>
-- js ctor<br>
-- lua new
-- @function [parent=#Layout] Layout 
-- @param self
-- @return Layout#Layout self (return value: ccui.Layout)
        
return nil
