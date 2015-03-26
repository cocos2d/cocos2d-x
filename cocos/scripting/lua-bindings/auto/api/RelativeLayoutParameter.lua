
--------------------------------
-- @module RelativeLayoutParameter
-- @extend LayoutParameter
-- @parent_module ccui

--------------------------------
-- Sets RelativeAlign parameter for LayoutParameter.<br>
-- see RelativeAlign<br>
-- param RelativeAlign Relative align in @see `RelativeAlign`.
-- @function [parent=#RelativeLayoutParameter] setAlign 
-- @param self
-- @param #int align
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- Set widget name your widget want to relative to.<br>
-- param name Relative widget name.
-- @function [parent=#RelativeLayoutParameter] setRelativeToWidgetName 
-- @param self
-- @param #string name
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- Get a name of LayoutParameter in Relative Layout.<br>
-- return name Relative name in string.
-- @function [parent=#RelativeLayoutParameter] getRelativeName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Get the relative widget name.<br>
-- return name A relative widget name in string.
-- @function [parent=#RelativeLayoutParameter] getRelativeToWidgetName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Set a name for LayoutParameter in Relative Layout.<br>
-- param name A string name.
-- @function [parent=#RelativeLayoutParameter] setRelativeName 
-- @param self
-- @param #string name
-- @return RelativeLayoutParameter#RelativeLayoutParameter self (return value: ccui.RelativeLayoutParameter)
        
--------------------------------
-- Get RelativeAlign parameter for LayoutParameter.<br>
-- see RelativeAlign<br>
-- return RelativeAlign A RelativeAlign variable.
-- @function [parent=#RelativeLayoutParameter] getAlign 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Create a RelativeLayoutParameter instance.<br>
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
