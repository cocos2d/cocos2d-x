
--------------------------------
-- @module LayerGradient
-- @extend LayerColor

--------------------------------
-- @function [parent=#LayerGradient] getStartColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
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
-- @param #cc.Vec2 vec2
        
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
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#LayerGradient] setEndColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#LayerGradient] getEndColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- @function [parent=#LayerGradient] getEndOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @function [parent=#LayerGradient] setStartColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- overload function: create(color4b_table, color4b_table)
--          
-- overload function: create()
--          
-- overload function: create(color4b_table, color4b_table, cc.Vec2)
--          
-- @function [parent=#LayerGradient] create
-- @param self
-- @param #color4b_table color4b
-- @param #color4b_table color4b
-- @param #cc.Vec2 vec2
-- @return LayerGradient#LayerGradient ret (retunr value: cc.LayerGradient)

--------------------------------
-- @function [parent=#LayerGradient] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
