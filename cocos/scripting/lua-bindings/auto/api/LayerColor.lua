
--------------------------------
-- @module LayerColor
-- @extend Layer,BlendProtocol

--------------------------------
-- @function [parent=#LayerColor] changeWidthAndHeight 
-- @param self
-- @param #float float
-- @param #float float
        
--------------------------------
-- @function [parent=#LayerColor] changeHeight 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#LayerColor] changeWidth 
-- @param self
-- @param #float float
        
--------------------------------
-- overload function: create(color4b_table, float, float)
--          
-- overload function: create()
--          
-- overload function: create(color4b_table)
--          
-- @function [parent=#LayerColor] create
-- @param self
-- @param #color4b_table color4b
-- @param #float float
-- @param #float float
-- @return LayerColor#LayerColor ret (retunr value: cc.LayerColor)

--------------------------------
-- @function [parent=#LayerColor] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#LayerColor] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#LayerColor] setContentSize 
-- @param self
-- @param #size_table size
        
return nil
