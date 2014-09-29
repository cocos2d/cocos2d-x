
--------------------------------
-- @module AABB
-- @parent_module cc

--------------------------------
-- reset min and max value.
-- @function [parent=#AABB] reset 
-- @param self
        
--------------------------------
-- Sets this bounding box to the specified values.
-- @function [parent=#AABB] set 
-- @param self
-- @param #vec3_table min
-- @param #vec3_table max
        
--------------------------------
-- Transforms the bounding box by the given transformation matrix.
-- @function [parent=#AABB] transform 
-- @param self
-- @param #mat4_table mat
        
--------------------------------
-- Gets the center point of the bounding box.
-- @function [parent=#AABB] getCenter 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- 
-- @function [parent=#AABB] isEmpty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#AABB] getCorners 
-- @param self
-- @param #vec3_table dst
        
--------------------------------
-- update the _min and _max from the given point.
-- @function [parent=#AABB] updateMinMax 
-- @param self
-- @param #vec3_table point
-- @param #long num
        
--------------------------------
-- check whether the point is in.
-- @function [parent=#AABB] containPoint 
-- @param self
-- @param #vec3_table point
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, vec3_table, vec3_table         
-- @overload self         
-- @function [parent=#AABB] AABB
-- @param self
-- @param #vec3_table min
-- @param #vec3_table max

return nil
