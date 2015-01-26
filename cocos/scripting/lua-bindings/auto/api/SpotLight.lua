
--------------------------------
-- @module SpotLight
-- @extend BaseLight
-- @parent_module cc

--------------------------------
-- Returns the range of point or spot light.<br>
-- return The range of the point or spot light.
-- @function [parent=#SpotLight] getRange 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Sets the Direction in parent.<br>
-- param dir The Direction in parent.
-- @function [parent=#SpotLight] setDirection 
-- @param self
-- @param #vec3_table dir
-- @return SpotLight#SpotLight self (return value: cc.SpotLight)
        
--------------------------------
--  get cos innerAngle 
-- @function [parent=#SpotLight] getCosInnerAngle 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the outer angle of the spot light (in radians).
-- @function [parent=#SpotLight] getOuterAngle 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the inner angle the spot light (in radians).
-- @function [parent=#SpotLight] getInnerAngle 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the Direction in parent.
-- @function [parent=#SpotLight] getDirection 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  get cos outAngle 
-- @function [parent=#SpotLight] getCosOuterAngle 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Sets the outer angle of a spot light (in radians).<br>
-- param outerAngle The angle of spot light (in radians).
-- @function [parent=#SpotLight] setOuterAngle 
-- @param self
-- @param #float angle
-- @return SpotLight#SpotLight self (return value: cc.SpotLight)
        
--------------------------------
-- Sets the inner angle of a spot light (in radians).<br>
-- param angle The angle of spot light (in radians).
-- @function [parent=#SpotLight] setInnerAngle 
-- @param self
-- @param #float angle
-- @return SpotLight#SpotLight self (return value: cc.SpotLight)
        
--------------------------------
-- Returns direction in world.
-- @function [parent=#SpotLight] getDirectionInWorld 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- Sets the range of point or spot light.<br>
-- param range The range of point or spot light.
-- @function [parent=#SpotLight] setRange 
-- @param self
-- @param #float range
-- @return SpotLight#SpotLight self (return value: cc.SpotLight)
        
--------------------------------
-- Creates a spot light.<br>
-- param direction The light's direction<br>
-- param position The light's position<br>
-- param color The light's color.<br>
-- param innerAngle The light's inner angle (in radians).<br>
-- param outerAngle The light's outer angle (in radians).<br>
-- param range The light's range.<br>
-- return The new spot light.
-- @function [parent=#SpotLight] create 
-- @param self
-- @param #vec3_table direction
-- @param #vec3_table position
-- @param #color3b_table color
-- @param #float innerAngle
-- @param #float outerAngle
-- @param #float range
-- @return SpotLight#SpotLight ret (return value: cc.SpotLight)
        
--------------------------------
-- 
-- @function [parent=#SpotLight] getLightType 
-- @param self
-- @return int#int ret (return value: int)
        
return nil
