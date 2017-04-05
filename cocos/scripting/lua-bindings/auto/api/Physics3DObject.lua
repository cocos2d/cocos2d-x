
--------------------------------
-- @module Physics3DObject
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Set the user data. 
-- @function [parent=#Physics3DObject] setUserData 
-- @param self
-- @param #void userData
-- @return Physics3DObject#Physics3DObject self (return value: cc.Physics3DObject)
        
--------------------------------
--  Get the user data. 
-- @function [parent=#Physics3DObject] getUserData 
-- @param self
-- @return void#void ret (return value: void)
        
--------------------------------
--  Get the Physics3DObject Type. 
-- @function [parent=#Physics3DObject] getObjType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Internal method. Set the pointer of Physics3DWorld. 
-- @function [parent=#Physics3DObject] setPhysicsWorld 
-- @param self
-- @param #cc.Physics3DWorld world
-- @return Physics3DObject#Physics3DObject self (return value: cc.Physics3DObject)
        
--------------------------------
--  Get the world matrix of Physics3DObject. 
-- @function [parent=#Physics3DObject] getWorldTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
--  Get the pointer of Physics3DWorld. 
-- @function [parent=#Physics3DObject] getPhysicsWorld 
-- @param self
-- @return Physics3DWorld#Physics3DWorld ret (return value: cc.Physics3DWorld)
        
--------------------------------
--  Set the mask of Physics3DObject. 
-- @function [parent=#Physics3DObject] setMask 
-- @param self
-- @param #unsigned int mask
-- @return Physics3DObject#Physics3DObject self (return value: cc.Physics3DObject)
        
--------------------------------
--  Get the collision callback function. 
-- @function [parent=#Physics3DObject] getCollisionCallback 
-- @param self
-- @return function#function ret (return value: function)
        
--------------------------------
--  Get the mask of Physics3DObject. 
-- @function [parent=#Physics3DObject] getMask 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  Check has collision callback function. 
-- @function [parent=#Physics3DObject] needCollisionCallback 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
