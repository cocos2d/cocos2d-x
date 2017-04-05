
--------------------------------
-- @module MenuItemLabel
-- @extend MenuItem
-- @parent_module cc

--------------------------------
--  Sets the label that is rendered. 
-- @function [parent=#MenuItemLabel] setLabel 
-- @param self
-- @param #cc.Node node
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
--------------------------------
--  Get the inner string of the inner label. 
-- @function [parent=#MenuItemLabel] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Gets the color that will be used when the item is disabled. 
-- @function [parent=#MenuItemLabel] getDisabledColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
--  Sets a new string to the inner label. 
-- @function [parent=#MenuItemLabel] setString 
-- @param self
-- @param #string label
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
--------------------------------
--  Initializes a MenuItemLabel with a Label, target and selector. 
-- @function [parent=#MenuItemLabel] initWithLabel 
-- @param self
-- @param #cc.Node label
-- @param #function callback
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the color that will be used when the item is disabled. 
-- @function [parent=#MenuItemLabel] setDisabledColor 
-- @param self
-- @param #color3b_table color
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
--------------------------------
--  Gets the label that is rendered. 
-- @function [parent=#MenuItemLabel] getLabel 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#MenuItemLabel] setEnabled 
-- @param self
-- @param #bool enabled
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
--------------------------------
-- 
-- @function [parent=#MenuItemLabel] activate 
-- @param self
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
--------------------------------
-- 
-- @function [parent=#MenuItemLabel] unselected 
-- @param self
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
--------------------------------
-- 
-- @function [parent=#MenuItemLabel] selected 
-- @param self
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
--------------------------------
-- js ctor
-- @function [parent=#MenuItemLabel] MenuItemLabel 
-- @param self
-- @return MenuItemLabel#MenuItemLabel self (return value: cc.MenuItemLabel)
        
return nil
