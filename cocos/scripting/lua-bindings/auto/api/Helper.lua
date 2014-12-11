
--------------------------------
-- @module Helper
-- @parent_module ccui

--------------------------------
-- brief Get a UTF8 substring from a std::string with a given start position and length<br>
-- Sample:  std::string str = "中国中国中国";  substr = getSubStringOfUTF8String(str,0,2) will = "中国"<br>
-- param start The start position of the substring.<br>
-- param length The length of the substring in UTF8 count<br>
-- return a UTF8 substring
-- @function [parent=#Helper] getSubStringOfUTF8String 
-- @param self
-- @param #string str
-- @param #unsigned long start
-- @param #unsigned long length
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Helper] changeLayoutSystemActiveState 
-- @param self
-- @param #bool bActive
        
--------------------------------
-- 
-- @function [parent=#Helper] seekActionWidgetByActionTag 
-- @param self
-- @param #ccui.Widget root
-- @param #int tag
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Finds a widget whose name equals to param name from root widget.<br>
-- param root      widget which will be seeked.<br>
-- name             name value.<br>
-- return finded result.
-- @function [parent=#Helper] seekWidgetByName 
-- @param self
-- @param #ccui.Widget root
-- @param #string name
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Finds a widget whose tag equals to param tag from root widget.<br>
-- param root      widget which will be seeked.<br>
-- tag             tag value.<br>
-- return finded result.
-- @function [parent=#Helper] seekWidgetByTag 
-- @param self
-- @param #ccui.Widget root
-- @param #int tag
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#Helper] doLayout 
-- @param self
-- @param #cc.Node rootNode
        
return nil
