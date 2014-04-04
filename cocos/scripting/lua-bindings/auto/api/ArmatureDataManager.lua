
--------------------------------
-- @module ArmatureDataManager
-- @extend Ref

--------------------------------
-- @function [parent=#ArmatureDataManager] getAnimationDatas 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] removeAnimationData 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#ArmatureDataManager] addArmatureData 
-- @param self
-- @param #string str
-- @param #ccs.ArmatureData armaturedata
-- @param #string str
        
--------------------------------
-- overload function: addArmatureFileInfo(string, string, string)
--          
-- overload function: addArmatureFileInfo(string)
--          
-- @function [parent=#ArmatureDataManager] addArmatureFileInfo
-- @param self
-- @param #string str
-- @param #string str
-- @param #string str

--------------------------------
-- @function [parent=#ArmatureDataManager] removeArmatureFileInfo 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#ArmatureDataManager] getTextureDatas 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] getTextureData 
-- @param self
-- @param #string str
-- @return TextureData#TextureData ret (return value: ccs.TextureData)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] getArmatureData 
-- @param self
-- @param #string str
-- @return ArmatureData#ArmatureData ret (return value: ccs.ArmatureData)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] getAnimationData 
-- @param self
-- @param #string str
-- @return AnimationData#AnimationData ret (return value: ccs.AnimationData)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] addAnimationData 
-- @param self
-- @param #string str
-- @param #ccs.AnimationData animationdata
-- @param #string str
        
--------------------------------
-- @function [parent=#ArmatureDataManager] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] removeArmatureData 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#ArmatureDataManager] getArmatureDatas 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] removeTextureData 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#ArmatureDataManager] addTextureData 
-- @param self
-- @param #string str
-- @param #ccs.TextureData texturedata
-- @param #string str
        
--------------------------------
-- @function [parent=#ArmatureDataManager] isAutoLoadSpriteFile 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ArmatureDataManager] addSpriteFrameFromFile 
-- @param self
-- @param #string str
-- @param #string str
-- @param #string str
        
--------------------------------
-- @function [parent=#ArmatureDataManager] destroyInstance 
-- @param self
        
--------------------------------
-- @function [parent=#ArmatureDataManager] getInstance 
-- @param self
-- @return ArmatureDataManager#ArmatureDataManager ret (return value: ccs.ArmatureDataManager)
        
return nil
