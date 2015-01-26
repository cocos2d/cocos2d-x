
--------------------------------
-- @module RelativeLayoutParameter
-- @extend LayoutParameter
-- @parent_module ccui

--------------------------------
-- Sets RelativeAlign parameter for LayoutParameter.<br>
-- see RelativeAlign<br>
-- param RelativeAlign
-- @function [parent=#RelativeLayoutParameter] setAlign 
-- @param self
-- @param #int align
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- Sets a key for LayoutParameter. Witch widget named this is relative to.<br>
-- param name
-- @function [parent=#RelativeLayoutParameter] setRelativeToWidgetName 
-- @param self
-- @param #string name
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- Gets a name in Relative Layout of LayoutParameter.<br>
-- return name
-- @function [parent=#RelativeLayoutParameter] getRelativeName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Gets the key of LayoutParameter. Witch widget named this is relative to.<br>
-- return name
-- @function [parent=#RelativeLayoutParameter] getRelativeToWidgetName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Sets a name in Relative Layout for LayoutParameter.<br>
-- param name
-- @function [parent=#RelativeLayoutParameter] setRelativeName 
-- @param self
-- @param #string name
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- Gets RelativeAlign parameter for LayoutParameter.<br>
-- see RelativeAlign<br>
-- return RelativeAlign
-- @function [parent=#RelativeLayoutParameter] getAlign 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Allocates and initializes.<br>
-- return A initialized LayoutParameter which is marked as "autorelease".
-- @function [parent=#RelativeLayoutParameter] create 
-- @param self
-- @return RelativeLayoutParameter#RelativeLayoutParameter ret (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- 
-- @function [parent=#RelativeLayoutParameter] createCloneInstance 
-- @param self
-- @return LayoutParameter#LayoutParameter ret (return value: ccui.LayoutParameter)
        
--------------------------------
-- 
-- @function [parent=#RelativeLayoutParameter] copyProperties 
-- @param self
-- @param #ccui.LayoutParameter model
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- Default constructor
-- @function [parent=#RelativeLayoutParameter] RelativeLayoutParameter 
-- @param self
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
return nil
