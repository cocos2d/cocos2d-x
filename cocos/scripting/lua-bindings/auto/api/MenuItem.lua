
--------------------------------
-- @module MenuItem
-- @extend Node
-- @parent_module cc

--------------------------------
--  Enables or disables the item. 
-- @function [parent=#MenuItem] setEnabled 
-- @param self
-- @param #bool value
-- @return MenuItem#MenuItem self (return value: cc.MenuItem)
        
--------------------------------
--  Activate the item. 
-- @function [parent=#MenuItem] activate 
-- @param self
-- @return MenuItem#MenuItem self (return value: cc.MenuItem)
        
--------------------------------
--  Returns whether or not the item is enabled. 
-- @function [parent=#MenuItem] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  The item was selected (not activated), similar to "mouse-over". 
-- @function [parent=#MenuItem] selected 
-- @param self
-- @return MenuItem#MenuItem self (return value: cc.MenuItem)
        
--------------------------------
--  Returns whether or not the item is selected. 
-- @function [parent=#MenuItem] isSelected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  The item was unselected. 
-- @function [parent=#MenuItem] unselected 
-- @param self
-- @return MenuItem#MenuItem self (return value: cc.MenuItem)
        
--------------------------------
--  Returns the outside box. 
-- @function [parent=#MenuItem] rect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#MenuItem] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
