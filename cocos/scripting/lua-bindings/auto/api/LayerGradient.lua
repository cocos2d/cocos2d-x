
--------------------------------
-- @module LayerGradient
-- @extend LayerColor

--------------------------------
-- @function [parent=#LayerGradient] getStartColor 
-- @param self
-- @return color3B_table#color3B_table ret (return value: color3B_table)
        
--------------------------------
-- @function [parent=#LayerGradient] isCompressedInterpolation 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#LayerGradient] getStartOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#LayerGradient] setVector 
-- @param self
-- @param #cc.math::Vector2 array
        
--------------------------------
-- @function [parent=#LayerGradient] setStartOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#LayerGradient] setCompressedInterpolation 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#LayerGradient] setEndOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#LayerGradient] getVector 
-- @param self
-- @return math::Vector2#math::Vector2 ret (return value: cc.math::Vector2)
        
--------------------------------
-- @function [parent=#LayerGradient] setEndColor 
-- @param self
-- @param #color3B_table color3b
        
--------------------------------
-- @function [parent=#LayerGradient] getEndColor 
-- @param self
-- @return color3B_table#color3B_table ret (return value: color3B_table)
        
--------------------------------
-- @function [parent=#LayerGradient] getEndOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#LayerGradient] setStartColor 
-- @param self
-- @param #color3B_table color3b
        
--------------------------------
-- overload function: create(color4B_table, color4B_table)
--          
-- overload function: create()
--          
-- overload function: create(color4B_table, color4B_table, cc.math::Vector2)
--          
-- @function [parent=#LayerGradient] create
-- @param self
-- @param #color4B_table color4b
-- @param #color4B_table color4b
-- @param #cc.math::Vector2 array
-- @return LayerGradient#LayerGradient ret (retunr value: cc.LayerGradient)

--------------------------------
-- @function [parent=#LayerGradient] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
