
--------------------------------
-- @module OrbitCamera
-- @extend ActionCamera
-- @parent_module cc

--------------------------------
--  initializes a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX 
-- @function [parent=#OrbitCamera] initWithDuration 
-- @param self
-- @param #float t
-- @param #float radius
-- @param #float deltaRadius
-- @param #float angleZ
-- @param #float deltaAngleZ
-- @param #float angleX
-- @param #float deltaAngleX
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  creates a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX 
-- @function [parent=#OrbitCamera] create 
-- @param self
-- @param #float t
-- @param #float radius
-- @param #float deltaRadius
-- @param #float angleZ
-- @param #float deltaAngleZ
-- @param #float angleX
-- @param #float deltaAngleX
-- @return OrbitCamera#OrbitCamera ret (return value: cc.OrbitCamera)
        
--------------------------------
-- 
-- @function [parent=#OrbitCamera] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return OrbitCamera#OrbitCamera self (return value: cc.OrbitCamera)
        
--------------------------------
-- 
-- @function [parent=#OrbitCamera] clone 
-- @param self
-- @return OrbitCamera#OrbitCamera ret (return value: cc.OrbitCamera)
        
--------------------------------
-- 
-- @function [parent=#OrbitCamera] update 
-- @param self
-- @param #float time
-- @return OrbitCamera#OrbitCamera self (return value: cc.OrbitCamera)
        
--------------------------------
-- js ctor
-- @function [parent=#OrbitCamera] OrbitCamera 
-- @param self
-- @return OrbitCamera#OrbitCamera self (return value: cc.OrbitCamera)
        
return nil
