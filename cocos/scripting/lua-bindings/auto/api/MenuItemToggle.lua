
--------------------------------
-- @module MenuItemToggle
-- @extend MenuItem
-- @parent_module cc

--------------------------------
--  Sets the array that contains the subitems. 
-- @function [parent=#MenuItemToggle] setSubItems 
-- @param self
-- @param #array_table items
        
--------------------------------
--  Gets the index of the selected item 
-- @function [parent=#MenuItemToggle] getSelectedIndex 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  add more menu item 
-- @function [parent=#MenuItemToggle] addSubItem 
-- @param self
-- @param #cc.MenuItem item
        
--------------------------------
--  return the selected item 
-- @function [parent=#MenuItemToggle] getSelectedItem 
-- @param self
-- @return MenuItem#MenuItem ret (return value: cc.MenuItem)
        
--------------------------------
--  Sets the index of the selected item 
-- @function [parent=#MenuItemToggle] setSelectedIndex 
-- @param self
-- @param #unsigned int index
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] setEnabled 
-- @param self
-- @param #bool var
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] activate 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] unselected 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] selected 
-- @param self
        
return nil
