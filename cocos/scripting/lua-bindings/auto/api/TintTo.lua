
--------------------------------
-- @module TintTo
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- @overload self, float, color3b_table         
-- @overload self, float, unsigned char, unsigned char, unsigned char         
-- @function [parent=#TintTo] create
-- @param self
-- @param #float duration
-- @param #unsigned char red
-- @param #unsigned char green
-- @param #unsigned char blue
-- @return TintTo#TintTo ret (return value: cc.TintTo)

--------------------------------
-- 
-- @function [parent=#TintTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return TintTo#TintTo self (return value: cc.TintTo)
        
--------------------------------
-- 
-- @function [parent=#TintTo] clone 
-- @param self
-- @return TintTo#TintTo ret (return value: cc.TintTo)
        
--------------------------------
-- 
-- @function [parent=#TintTo] reverse 
-- @param self
-- @return TintTo#TintTo ret (return value: cc.TintTo)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#TintTo] update 
-- @param self
-- @param #float time
-- @return TintTo#TintTo self (return value: cc.TintTo)
        
return nil
