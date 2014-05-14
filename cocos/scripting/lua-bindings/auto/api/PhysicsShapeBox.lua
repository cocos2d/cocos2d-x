
--------------------------------
-- @module PhysicsShapeBox
-- @extend PhysicsShape

--------------------------------
-- @function [parent=#PhysicsShapeBox] getPointsCount 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] getSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] create 
-- @param self
-- @param #size_table size
-- @param #cc.PhysicsMaterial physicsmaterial
-- @param #cc.Vec2 vec2
-- @return PhysicsShapeBox#PhysicsShapeBox ret (return value: cc.PhysicsShapeBox)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] calculateArea 
-- @param self
-- @param #size_table size
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] calculateMoment 
-- @param self
-- @param #float float
-- @param #size_table size
-- @param #cc.Vec2 vec2
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] getOffset 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] calculateDefaultMoment 
-- @param self
-- @return float#float ret (return value: float)
        
return nil
