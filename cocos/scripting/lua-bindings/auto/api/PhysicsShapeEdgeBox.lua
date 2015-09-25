
--------------------------------
-- @module PhysicsShapeEdgeBox
-- @extend PhysicsShapeEdgePolygon
-- @parent_module cc

--------------------------------
-- Creates a PhysicsShapeEdgeBox with specified value.<br>
-- param   size Size contains this box's width and height.<br>
-- param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.<br>
-- param   border It's a edge's border width.<br>
-- param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.<br>
-- return  An autoreleased PhysicsShapeEdgeBox object pointer.
-- @function [parent=#PhysicsShapeEdgeBox] create 
-- @param self
-- @param #size_table size
-- @param #cc.PhysicsMaterial material
-- @param #float border
-- @param #vec2_table offset
-- @return PhysicsShapeEdgeBox#PhysicsShapeEdgeBox ret (return value: cc.PhysicsShapeEdgeBox)
        
--------------------------------
-- Get this box's position offset.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShapeEdgeBox] getOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
return nil
