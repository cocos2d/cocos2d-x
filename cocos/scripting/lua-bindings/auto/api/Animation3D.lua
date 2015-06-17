
--------------------------------
-- @module Animation3D
-- @extend Ref
-- @parent_module cc

--------------------------------
-- init Animation3D with file name and animation name
-- @function [parent=#Animation3D] initWithFile 
-- @param self
-- @param #string filename
-- @param #string animationName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- init Animation3D from bundle data
-- @function [parent=#Animation3D] init 
-- @param self
-- @param #cc.Animation3DData data
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- get duration
-- @function [parent=#Animation3D] getDuration 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- read all animation or only the animation with given animationName? animationName == "" read the first.
-- @function [parent=#Animation3D] create 
-- @param self
-- @param #string filename
-- @param #string animationName
-- @return Animation3D#Animation3D ret (return value: cc.Animation3D)
        
--------------------------------
-- 
-- @function [parent=#Animation3D] Animation3D 
-- @param self
-- @return Animation3D#Animation3D self (return value: cc.Animation3D)
        
return nil
