
--------------------------------
-- @module PhysicsShapeBox
-- @extend PhysicsShapePolygon
-- @parent_module cc

--------------------------------
-- Get this box's width and height.<br>
-- return An Size object.
-- @function [parent=#PhysicsShapeBox] getSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Creates a PhysicsShapeBox with specified value.<br>
-- param   size Size contains this box's width and height.<br>
-- param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.<br>
-- param   offset A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.<br>
-- return  An autoreleased PhysicsShapeBox object pointer.
-- @function [parent=#PhysicsShapeBox] create 
-- @param self
-- @param #size_table size
-- @param #cc.PhysicsMaterial material
-- @param #vec2_table offset
-- @return PhysicsShapeBox#PhysicsShapeBox ret (return value: cc.PhysicsShapeBox)
        
--------------------------------
-- Get this box's position offset.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShapeBox] getOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
return nil
