
--------------------------------
-- @module Menu
-- @extend Layer
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Menu] setEnabled 
-- @param self
-- @param #bool value
        
--------------------------------
--  align items vertically 
-- @function [parent=#Menu] alignItemsVertically 
-- @param self
        
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
        
--------------------------------
--  align items vertically with padding<br>
-- since v0.7.2
-- @function [parent=#Menu] alignItemsVerticallyWithPadding 
-- @param self
-- @param #float padding
        
--------------------------------
--  align items horizontally 
-- @function [parent=#Menu] alignItemsHorizontally 
-- @param self
        
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
        
--------------------------------
-- 
-- @function [parent=#Menu] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
        
return nil
