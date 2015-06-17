
--------------------------------
-- @module PhysicsShapeEdgeSegment
-- @extend PhysicsShape
-- @parent_module cc

--------------------------------
-- Get this edge's end position.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShapeEdgeSegment] getPointB 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Get this edge's begin position.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShapeEdgeSegment] getPointA 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Creates a PhysicsShapeEdgeSegment with specified value.<br>
-- param   a It's the edge's begin position.<br>
-- param   b It's the edge's end position.<br>
-- param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.<br>
-- param   border It's a edge's border width.<br>
-- return  An autoreleased PhysicsShapeEdgeSegment object pointer.
-- @function [parent=#PhysicsShapeEdgeSegment] create 
-- @param self
-- @param #vec2_table a
-- @param #vec2_table b
-- @param #cc.PhysicsMaterial material
-- @param #float border
-- @return PhysicsShapeEdgeSegment#PhysicsShapeEdgeSegment ret (return value: cc.PhysicsShapeEdgeSegment)
        
--------------------------------
-- Get this edge's center position.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShapeEdgeSegment] getCenter 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
return nil
