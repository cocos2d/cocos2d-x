
--------------------------------
-- @module Layout
-- @extend Widget

--------------------------------
-- @function [parent=#Layout] setBackGroundColorVector 
-- @param self
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#Layout] setClippingType 
-- @param self
-- @param #ccui.Layout::ClippingType clippingtype
        
--------------------------------
-- @function [parent=#Layout] setBackGroundColorType 
-- @param self
-- @param #ccui.Layout::BackGroundColorType backgroundcolortype
        
--------------------------------
-- @function [parent=#Layout] setLoopFocus 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Layout] setBackGroundImageColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#Layout] getBackGroundColorVector 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#Layout] getClippingType 
-- @param self
-- @return Layout::ClippingType#Layout::ClippingType ret (return value: ccui.Layout::ClippingType)
        
--------------------------------
-- @function [parent=#Layout] isLoopFocus 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Layout] removeBackGroundImage 
-- @param self
        
--------------------------------
-- @function [parent=#Layout] getBackGroundColorOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#Layout] isClippingEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Layout] setBackGroundImageOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#Layout] setBackGroundImage 
-- @param self
-- @param #string str
-- @param #ccui.Widget::TextureResType texturerestype
        
--------------------------------
-- overload function: setBackGroundColor(color3b_table, color3b_table)
--          
-- overload function: setBackGroundColor(color3b_table)
--          
-- @function [parent=#Layout] setBackGroundColor
-- @param self
-- @param #color3b_table color3b
-- @param #color3b_table color3b

--------------------------------
-- @function [parent=#Layout] requestDoLayout 
-- @param self
        
--------------------------------
-- @function [parent=#Layout] getBackGroundImageCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#Layout] getBackGroundColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#Layout] setClippingEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Layout] getBackGroundImageColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#Layout] isBackGroundImageScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Layout] getBackGroundColorType 
-- @param self
-- @return Layout::BackGroundColorType#Layout::BackGroundColorType ret (return value: ccui.Layout::BackGroundColorType)
        
--------------------------------
-- @function [parent=#Layout] getBackGroundEndColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#Layout] setBackGroundColorOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#Layout] getBackGroundImageOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#Layout] isPassFocusToChild 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Layout] setBackGroundImageCapInsets 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#Layout] getBackGroundImageTextureSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Layout] getLayoutType 
-- @param self
-- @return Layout::Type#Layout::Type ret (return value: ccui.Layout::Type)
        
--------------------------------
-- @function [parent=#Layout] setPassFocusToChild 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Layout] getBackGroundStartColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#Layout] setBackGroundImageScale9Enabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Layout] setLayoutType 
-- @param self
-- @param #ccui.Layout::Type type
        
--------------------------------
-- @function [parent=#Layout] create 
-- @param self
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- @function [parent=#Layout] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- overload function: addChild(cc.Node, int)
--          
-- overload function: addChild(cc.Node)
--          
-- overload function: addChild(cc.Node, int, int)
--          
-- @function [parent=#Layout] addChild
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int

--------------------------------
-- @function [parent=#Layout] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Layout] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Layout] removeAllChildren 
-- @param self
        
--------------------------------
-- @function [parent=#Layout] sortAllChildren 
-- @param self
        
--------------------------------
-- @function [parent=#Layout] findNextFocusedWidget 
-- @param self
-- @param #ccui.Widget::FocusDirection focusdirection
-- @param #ccui.Widget widget
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#Layout] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Layout] Layout 
-- @param self
        
return nil
