
--------------------------------
-- @module Menu
-- @extend Layer
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Menu] setEnabled 
-- @param self
-- @param #bool value
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
--  align items vertically 
-- @function [parent=#Menu] alignItemsVertically 
-- @param self
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
-- 
-- @function [parent=#Menu] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  align items horizontally with padding<br>
-- since v0.7.2
-- @function [parent=#Menu] alignItemsHorizontallyWithPadding 
-- @param self
-- @param #float padding
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
--  align items vertically with padding<br>
-- since v0.7.2
-- @function [parent=#Menu] alignItemsVerticallyWithPadding 
-- @param self
-- @param #float padding
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
--  align items horizontally 
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
-- @function [parent=#Menu] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Menu] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Menu] setOpacityModifyRGB 
-- @param self
-- @param #bool bValue
-- @return Menu#Menu self (return value: cc.Menu)
        
--------------------------------
-- 
-- @function [parent=#Menu] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return Menu#Menu self (return value: cc.Menu)
        
return nil
