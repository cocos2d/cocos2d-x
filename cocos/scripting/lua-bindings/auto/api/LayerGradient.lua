
--------------------------------
-- @module LayerGradient
-- @extend LayerColor
-- @parent_module cc

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
-- @param #vec2_table vec2
        
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
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
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
-- @overload self, color4b_table, color4b_table         
-- @overload self         
-- @overload self, color4b_table, color4b_table, vec2_table         
-- @function [parent=#LayerGradient] create
-- @param self
-- @param #color4b_table color4b
-- @param #color4b_table color4b
-- @param #vec2_table vec2
-- @return LayerGradient#LayerGradient ret (retunr value: cc.LayerGradient)

--------------------------------
-- @function [parent=#LayerGradient] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
