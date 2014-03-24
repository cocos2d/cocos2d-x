
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
-- @param #point_table point
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
-- @param #point_table point
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] getOffset 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#PhysicsShapeBox] calculateDefaultMoment 
-- @param self
-- @return float#float ret (return value: float)
        
return nil
