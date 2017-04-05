
--------------------------------
-- @module DirectionLight
-- @extend BaseLight
-- @parent_module cc

--------------------------------
-- Returns the Direction in parent.
-- @function [parent=#DirectionLight] getDirection 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- Returns direction in world.
-- @function [parent=#DirectionLight] getDirectionInWorld 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- Sets the Direction in parent.<br>
-- param dir The Direction in parent.
-- @function [parent=#DirectionLight] setDirection 
-- @param self
-- @param #vec3_table dir
-- @return DirectionLight#DirectionLight self (return value: cc.DirectionLight)
        
--------------------------------
-- Creates a direction light.<br>
-- param direction The light's direction<br>
-- param color The light's color.<br>
-- return The new direction light.
-- @function [parent=#DirectionLight] create 
-- @param self
-- @param #vec3_table direction
-- @param #color3b_table color
-- @return DirectionLight#DirectionLight ret (return value: cc.DirectionLight)
        
--------------------------------
-- 
-- @function [parent=#DirectionLight] getLightType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#DirectionLight] DirectionLight 
-- @param self
-- @return DirectionLight#DirectionLight self (return value: cc.DirectionLight)
        
return nil
