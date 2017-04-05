
--------------------------------
-- @module Bundle3D
-- @parent_module cc

--------------------------------
-- load a file. You must load a file first, then call loadMeshData, loadSkinData, and so on<br>
-- param path File to be loaded<br>
-- return result of load
-- @function [parent=#Bundle3D] load 
-- @param self
-- @param #string path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- load skin data from bundle<br>
-- param id The ID of the skin, load the first Skin in the bundle if it is empty
-- @function [parent=#Bundle3D] loadSkinData 
-- @param self
-- @param #string id
-- @param #cc.SkinData skindata
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Bundle3D] clear 
-- @param self
-- @return Bundle3D#Bundle3D self (return value: cc.Bundle3D)
        
--------------------------------
-- 
-- @function [parent=#Bundle3D] loadMaterials 
-- @param self
-- @param #cc.MaterialDatas materialdatas
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Bundle3D] loadNodes 
-- @param self
-- @param #cc.NodeDatas nodedatas
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- load material data from bundle<br>
-- param id The ID of the animation, load the first animation in the bundle if it is empty
-- @function [parent=#Bundle3D] loadAnimationData 
-- @param self
-- @param #string id
-- @param #cc.Animation3DData animationdata
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- create a new bundle, destroy it when finish using it
-- @function [parent=#Bundle3D] createBundle 
-- @param self
-- @return Bundle3D#Bundle3D ret (return value: cc.Bundle3D)
        
--------------------------------
-- 
-- @function [parent=#Bundle3D] destroyBundle 
-- @param self
-- @param #cc.Bundle3D bundle
-- @return Bundle3D#Bundle3D self (return value: cc.Bundle3D)
        
--------------------------------
-- 
-- @function [parent=#Bundle3D] Bundle3D 
-- @param self
-- @return Bundle3D#Bundle3D self (return value: cc.Bundle3D)
        
return nil
