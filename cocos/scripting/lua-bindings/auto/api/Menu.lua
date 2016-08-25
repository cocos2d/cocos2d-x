
--------------------------------
-- @module Menu
-- @extend Layer
-- @parent_module cc

--------------------------------
--  initializes a Menu with a NSArray of MenuItem objects 
-- @function [parent=#Menu] initWithArray 
-- @param self
-- @param #array_table arrayOfItems
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Set whether the menu is visible. If set false, interacting with the menu<br>
-- will have no effect.<br>
-- The default value is true, a menu is default to visible.<br>
-- param value true if menu is to be enabled, false if menu is to be disabled.
-- @function [parent=#Menu] setEnabled 
-- @param self
-- @param #bool value
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
--  Align items vertically. 
-- @function [parent=#Menu] alignItemsVertically 
-- @param self
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
-- Determines if the menu is enabled.<br>
-- see `setEnabled(bool)`.<br>
-- return whether the menu is enabled or not.
-- @function [parent=#Menu] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Align items horizontally with padding.<br>
-- since v0.7.2
-- @function [parent=#Menu] alignItemsHorizontallyWithPadding 
-- @param self
-- @param #float padding
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
--  Align items vertically with padding.<br>
-- since v0.7.2
-- @function [parent=#Menu] alignItemsVerticallyWithPadding 
-- @param self
-- @param #float padding
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
--  Align items horizontally. 
-- @function [parent=#Menu] alignItemsHorizontally 
-- @param self
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
-- @overload self, cc.Node, int         
-- @overload self, cc.Node         
-- @overload self, cc.Node, int, int         
-- @overload self, cc.Node, int, string         
-- @function [parent=#Menu] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #string name
-- @return Menu#Menu self (return value: cc.Menu)

--------------------------------
-- 
-- @function [parent=#Menu] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Menu] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
--  initializes an empty Menu 
-- @function [parent=#Menu] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Menu] setOpacityModifyRGB 
-- @param self
-- @param #bool bValue
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
-- 
-- @function [parent=#Menu] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- js ctor
-- @function [parent=#Menu] Menu 
-- @param self
-- @return Menu#Menu self (return value: cc.Menu)
        
return nil
