
--------------------------------
-- @module MenuItemToggle
-- @extend MenuItem
-- @parent_module cc

--------------------------------
--  Sets the array that contains the subitems. 
-- @function [parent=#MenuItemToggle] setSubItems 
-- @param self
-- @param #array_table items
-- @return MenuItemToggle#MenuItemToggle self (return value: cc.MenuItemToggle)
        
--------------------------------
--  Gets the index of the selected item. 
-- @function [parent=#MenuItemToggle] getSelectedIndex 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  Add more menu item. 
-- @function [parent=#MenuItemToggle] addSubItem 
-- @param self
-- @param #cc.MenuItem item
-- @return MenuItemToggle#MenuItemToggle self (return value: cc.MenuItemToggle)
        
--------------------------------
--  Return the selected item. 
-- @function [parent=#MenuItemToggle] getSelectedItem 
-- @param self
-- @return MenuItem#MenuItem ret (return value: cc.MenuItem)
        
--------------------------------
--  Sets the index of the selected item. 
-- @function [parent=#MenuItemToggle] setSelectedIndex 
-- @param self
-- @param #unsigned int index
-- @return MenuItemToggle#MenuItemToggle self (return value: cc.MenuItemToggle)
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] setEnabled 
-- @param self
-- @param #bool var
-- @return MenuItemToggle#MenuItemToggle self (return value: cc.MenuItemToggle)
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] activate 
-- @param self
-- @return MenuItemToggle#MenuItemToggle self (return value: cc.MenuItemToggle)
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] unselected 
-- @param self
-- @return MenuItemToggle#MenuItemToggle self (return value: cc.MenuItemToggle)
        
--------------------------------
-- 
-- @function [parent=#MenuItemToggle] selected 
-- @param self
-- @return MenuItemToggle#MenuItemToggle self (return value: cc.MenuItemToggle)
        
return nil
