
--------------------------------
-- @module Helper
-- @parent_module ccui

--------------------------------
-- brief Get a UTF8 substring from a std::string with a given start position and length<br>
-- Sample:  std::string str = "中国中国中国";  substr = getSubStringOfUTF8String(str,0,2) will = "中国"<br>
-- param str The source string.<br>
-- param start The start position of the substring.<br>
-- param length The length of the substring in UTF8 count<br>
-- return a UTF8 substring<br>
-- js NA
-- @function [parent=#Helper] getSubStringOfUTF8String 
-- @param self
-- @param #string str
-- @param #unsigned int start
-- @param #unsigned int length
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief Convert a node's boundingBox rect into screen coordinates.<br>
-- param node Any node pointer.<br>
-- return A Rect in screen coordinates.
-- @function [parent=#Helper] convertBoundingBoxToScreen 
-- @param self
-- @param #cc.Node node
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Change the active property of Layout's @see `LayoutComponent`<br>
-- param active A boolean value.
-- @function [parent=#Helper] changeLayoutSystemActiveState 
-- @param self
-- @param #bool active
-- @return Helper#Helper self (return value: ccui.Helper)
        
--------------------------------
-- Find a widget with a specific action tag from root widget<br>
-- This search will be recursive through all child widgets.<br>
-- param root The be searched root widget.<br>
-- param tag The widget action's tag.<br>
-- return Widget instance pointer.
-- @function [parent=#Helper] seekActionWidgetByActionTag 
-- @param self
-- @param #ccui.Widget root
-- @param #int tag
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Find a widget with a specific name from root widget.<br>
-- This search will be recursive through all child widgets.<br>
-- param root      The be searched root widget.<br>
-- param name      The widget name.<br>
-- return Widget instance pointer.
-- @function [parent=#Helper] seekWidgetByName 
-- @param self
-- @param #ccui.Widget root
-- @param #string name
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Find a widget with a specific tag from root widget.<br>
-- This search will be recursive through all child widgets.<br>
-- param root      The be searched root widget.<br>
-- param tag       The widget tag.<br>
-- return Widget instance pointer.
-- @function [parent=#Helper] seekWidgetByTag 
-- @param self
-- @param #ccui.Widget root
-- @param #int tag
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- brief  restrict capInsetSize, when the capInsets's width is larger than the textureSize, it will restrict to 0,<br>
-- the height goes the same way as width.<br>
-- param  capInsets A user defined capInsets.<br>
-- param  textureSize  The size of a scale9enabled texture<br>
-- return a restricted capInset.
-- @function [parent=#Helper] restrictCapInsetRect 
-- @param self
-- @param #rect_table capInsets
-- @param #size_table textureSize
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Refresh object and it's children layout state<br>
-- param rootNode   A Node* or Node* descendant instance pointer.
-- @function [parent=#Helper] doLayout 
-- @param self
-- @param #cc.Node rootNode
-- @return Helper#Helper self (return value: ccui.Helper)
        
return nil
