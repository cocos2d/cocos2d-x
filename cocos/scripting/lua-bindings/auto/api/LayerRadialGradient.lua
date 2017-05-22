
--------------------------------
-- @module LayerRadialGradient
-- @extend Layer
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getStartColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getStartColor3B 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getStartOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] setCenter 
-- @param self
-- @param #vec2_table center
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getEndColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] setStartOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getCenter 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] setEndOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] setExpand 
-- @param self
-- @param #float expand
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getEndOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] initWithColor 
-- @param self
-- @param #color4b_table startColor
-- @param #color4b_table endColor
-- @param #float radius
-- @param #vec2_table center
-- @param #float expand
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, color4b_table         
-- @overload self, color3b_table         
-- @function [parent=#LayerRadialGradient] setEndColor
-- @param self
-- @param #color3b_table color
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)

--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getEndColor3B 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] setRadius 
-- @param self
-- @param #float radius
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- @overload self, color4b_table         
-- @overload self, color3b_table         
-- @function [parent=#LayerRadialGradient] setStartColor
-- @param self
-- @param #color3b_table color
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)

--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getExpand 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] getRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self         
-- @overload self, color4b_table, color4b_table, float, vec2_table, float         
-- @function [parent=#LayerRadialGradient] create
-- @param self
-- @param #color4b_table startColor
-- @param #color4b_table endColor
-- @param #float radius
-- @param #vec2_table center
-- @param #float expand
-- @return LayerRadialGradient#LayerRadialGradient ret (return value: cc.LayerRadialGradient)

--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] setContentSize 
-- @param self
-- @param #size_table size
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
--------------------------------
-- 
-- @function [parent=#LayerRadialGradient] LayerRadialGradient 
-- @param self
-- @return LayerRadialGradient#LayerRadialGradient self (return value: cc.LayerRadialGradient)
        
return nil
