
--------------------------------
-- @module Skeleton3D
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Skeleton3D] getBoneByName 
-- @param self
-- @param #string id
-- @return Bone3D#Bone3D ret (return value: cc.Bone3D)
        
--------------------------------
-- 
-- @function [parent=#Skeleton3D] getRootBone 
-- @param self
-- @param #int index
-- @return Bone3D#Bone3D ret (return value: cc.Bone3D)
        
--------------------------------
-- refresh bone world matrix
-- @function [parent=#Skeleton3D] updateBoneMatrix 
-- @param self
        
--------------------------------
-- get bone
-- @function [parent=#Skeleton3D] getBoneByIndex 
-- @param self
-- @param #unsigned int index
-- @return Bone3D#Bone3D ret (return value: cc.Bone3D)
        
--------------------------------
-- get & set root bone
-- @function [parent=#Skeleton3D] getRootCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- get bone index
-- @function [parent=#Skeleton3D] getBoneIndex 
-- @param self
-- @param #cc.Bone3D bone
-- @return int#int ret (return value: int)
        
--------------------------------
-- get total bone count
-- @function [parent=#Skeleton3D] getBoneCount 
-- @param self
-- @return long#long ret (return value: long)
        
return nil
