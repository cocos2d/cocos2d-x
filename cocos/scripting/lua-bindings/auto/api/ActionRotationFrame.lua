
--------------------------------
-- @module ActionRotationFrame
-- @extend ActionFrame
-- @parent_module ccs

--------------------------------
-- Changes rotate action rotation.<br>
-- param rotation rotate action rotation.
-- @function [parent=#ActionRotationFrame] setRotation 
-- @param self
-- @param #float rotation
        
--------------------------------
-- @overload self, float, ccs.ActionFrame         
-- @overload self, float         
-- @function [parent=#ActionRotationFrame] getAction
-- @param self
-- @param #float duration
-- @param #ccs.ActionFrame srcFrame
-- @return ActionInterval#ActionInterval ret (retunr value: cc.ActionInterval)

--------------------------------
-- Gets the rotate action rotation.<br>
-- return the rotate action rotation.
-- @function [parent=#ActionRotationFrame] getRotation 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Default constructor
-- @function [parent=#ActionRotationFrame] ActionRotationFrame 
-- @param self
        
return nil
