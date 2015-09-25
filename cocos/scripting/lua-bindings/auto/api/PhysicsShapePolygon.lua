
--------------------------------
-- @module PhysicsShapePolygon
-- @extend PhysicsShape
-- @parent_module cc

--------------------------------
-- Get this polygon's points array count.<br>
-- return An integer number.
-- @function [parent=#PhysicsShapePolygon] getPointsCount 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get a point of this polygon's points array.<br>
-- param i A index of this polygon's points array.<br>
-- return A point value.
-- @function [parent=#PhysicsShapePolygon] getPoint 
-- @param self
-- @param #int i
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Calculate the moment for a polygon.<br>
-- return A float number.
-- @function [parent=#PhysicsShapePolygon] calculateDefaultMoment 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get this polygon's center position.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShapePolygon] getCenter 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
return nil
