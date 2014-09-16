
--------------------------------
-- @module Layout
-- @extend Widget,LayoutProtocol
-- @parent_module ccui

--------------------------------
-- Sets background color vector for layout, if color type is BackGroundColorType::GRADIENT<br>
-- param vector
-- @function [parent=#Layout] setBackGroundColorVector 
-- @param self
-- @param #vec2_table vector
        
--------------------------------
-- 
-- @function [parent=#Layout] setClippingType 
-- @param self
-- @param #int type
        
--------------------------------
-- Sets Color Type for layout.<br>
-- param type   @see LayoutBackGroundColorType.
-- @function [parent=#Layout] setBackGroundColorType 
-- @param self
-- @param #int type
        
--------------------------------
-- If a layout is loop focused which means that the focus movement will be inside the layout<br>
-- param loop  pass true to let the focus movement loop inside the layout
-- @function [parent=#Layout] setLoopFocus 
-- @param self
-- @param #bool loop
        
--------------------------------
-- 
-- @function [parent=#Layout] setBackGroundImageColor 
-- @param self
-- @param #color3b_table color
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundColorVector 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
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
        
--------------------------------
-- 
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
-- 
-- @function [parent=#Layout] setBackGroundImageOpacity 
-- @param self
-- @param #unsigned char opacity
        
--------------------------------
-- Sets a background image for layout<br>
-- param fileName image file path.<br>
-- param texType @see TextureResType. TextureResType::LOCAL means local file, TextureResType::PLIST means sprite frame.
-- @function [parent=#Layout] setBackGroundImage 
-- @param self
-- @param #string fileName
-- @param #int texType
        
--------------------------------
-- @overload self, color3b_table, color3b_table         
-- @overload self, color3b_table         
-- @function [parent=#Layout] setBackGroundColor
-- @param self
-- @param #color3b_table startColor
-- @param #color3b_table endColor

--------------------------------
-- request to refresh widget layout
-- @function [parent=#Layout] requestDoLayout 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundImageCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Changes if layout can clip it's content and child.<br>
-- If you really need this, please enable it. But it would reduce the rendering efficiency. <br>
-- param clipping enabled.
-- @function [parent=#Layout] setClippingEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundImageColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#Layout] isBackGroundImageScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundColorType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundEndColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Sets background opacity layout.<br>
-- param opacity
-- @function [parent=#Layout] setBackGroundColorOpacity 
-- @param self
-- @param #unsigned char opacity
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundImageOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- return To query whether the layout will pass the focus to its children or not. The default value is true
-- @function [parent=#Layout] isPassFocusToChild 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets a background image capinsets for layout, if the background image is a scale9 render.<br>
-- param capinsets of background image.
-- @function [parent=#Layout] setBackGroundImageCapInsets 
-- @param self
-- @param #rect_table capInsets
        
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
        
--------------------------------
-- 
-- @function [parent=#Layout] getLayoutType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- param pass To specify whether the layout pass its focus to its child
-- @function [parent=#Layout] setPassFocusToChild 
-- @param self
-- @param #bool pass
        
--------------------------------
-- 
-- @function [parent=#Layout] getBackGroundStartColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Sets background iamge use scale9 renderer.<br>
-- param enabled   true that use scale9 renderer, false otherwise.
-- @function [parent=#Layout] setBackGroundImageScale9Enabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- 
-- @function [parent=#Layout] setLayoutType 
-- @param self
-- @param #int type
        
--------------------------------
-- Allocates and initializes a layout.
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
-- @param #int zOrder
-- @param #string name

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
        
--------------------------------
-- Removes all children from the container with a cleanup.<br>
-- see `removeAllChildrenWithCleanup(bool)`
-- @function [parent=#Layout] removeAllChildren 
-- @param self
        
--------------------------------
-- When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.<br>
-- If the widget is not in a layout, it will return itself<br>
-- param dir the direction to look for the next focused widget in a layout<br>
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
        
--------------------------------
-- Default constructor
-- @function [parent=#Layout] Layout 
-- @param self
        
return nil
