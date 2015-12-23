
--------------------------------
-- @module PhysicsShapeCircle
-- @extend PhysicsShape
-- @parent_module cc

--------------------------------
-- Get the circle's radius.<br>
-- return A float number.
-- @function [parent=#PhysicsShapeCircle] getRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Creates a PhysicsShapeCircle with specified value.<br>
-- param   radius A float number, it is the circle's radius.<br>
-- param   material A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.<br>
-- param   offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.<br>
-- return  An autoreleased PhysicsShapeCircle object pointer.
-- @function [parent=#PhysicsShapeCircle] create 
-- @param self
-- @param #float radius
-- @param #cc.PhysicsMaterial material
-- @param #vec2_table offset
-- @return PhysicsShapeCircle#PhysicsShapeCircle ret (return value: cc.PhysicsShapeCircle)
        
--------------------------------
-- Calculate the area of a circle with specified radius.<br>
-- param radius A float number<br>
-- return A float number
-- @function [parent=#PhysicsShapeCircle] calculateArea 
-- @param self
-- @param #float radius
-- @return float#float ret (return value: float)
        
--------------------------------
-- Calculate the moment of a circle with specified value.<br>
-- param mass A float number<br>
-- param radius A float number<br>
-- param offset A Vec2 object, it is the offset from the body's center of gravity in body local coordinates.<br>
-- return A float number
-- @function [parent=#PhysicsShapeCircle] calculateMoment 
-- @param self
-- @param #float mass
-- @param #float radius
-- @param #vec2_table offset
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get this circle's position offset.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShapeCircle] getOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Calculate the moment for a circle.<br>
-- return A float number.
-- @function [parent=#PhysicsShapeCircle] calculateDefaultMoment 
-- @param self
-- @return float#float ret (return value: float)
        
return nil
