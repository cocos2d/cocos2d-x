
--------------------------------
-- @module OrbitCamera
-- @extend ActionCamera
-- @parent_module cc

--------------------------------
--  Creates a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX. <br>
-- param t Duration in seconds.<br>
-- param radius The start radius.<br>
-- param deltaRadius The delta radius.<br>
-- param angelZ The start Angel in Z.<br>
-- param deltaAngleZ The delta angle in Z.<br>
-- param angelX The start Angel in X.<br>
-- param deltaAngleX The delta angle in X.<br>
-- return An OrbitCamera.
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
        
return nil
