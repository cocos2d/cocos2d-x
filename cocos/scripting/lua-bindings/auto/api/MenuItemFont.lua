
--------------------------------
-- @module MenuItemFont
-- @extend MenuItemLabel
-- @parent_module cc

--------------------------------
--  get font size .<br>
-- js getFontSize
-- @function [parent=#MenuItemFont] getFontSizeObj 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Returns the name of the Font.<br>
-- js getFontNameObj
-- @function [parent=#MenuItemFont] getFontNameObj 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Set font size.<br>
-- c++ can not overload static and non-static member functions with the same parameter types.<br>
-- so change the name to setFontSizeObj.<br>
-- js setFontSize
-- @function [parent=#MenuItemFont] setFontSizeObj 
-- @param self
-- @param #int size
-- @return MenuItemFont#MenuItemFont self (return value: cc.MenuItemFont)
        
--------------------------------
-- Set the font name .<br>
-- c++ can not overload static and non-static member functions with the same parameter types.<br>
-- so change the name to setFontNameObj.<br>
-- js setFontName
-- @function [parent=#MenuItemFont] setFontNameObj 
-- @param self
-- @param #string name
-- @return MenuItemFont#MenuItemFont self (return value: cc.MenuItemFont)
        
--------------------------------
--  Set the default font name. 
-- @function [parent=#MenuItemFont] setFontName 
-- @param self
-- @param #string name
-- @return MenuItemFont#MenuItemFont self (return value: cc.MenuItemFont)
        
--------------------------------
--  Get default font size. 
-- @function [parent=#MenuItemFont] getFontSize 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Get the default font name. 
-- @function [parent=#MenuItemFont] getFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Set default font size. 
-- @function [parent=#MenuItemFont] setFontSize 
-- @param self
-- @param #int size
-- @return MenuItemFont#MenuItemFont self (return value: cc.MenuItemFont)
        
return nil
