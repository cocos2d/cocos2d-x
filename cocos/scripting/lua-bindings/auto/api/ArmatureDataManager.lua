
--------------------------------
-- @module ArmatureDataManager
-- @extend Ref
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#ArmatureDataManager] getAnimationDatas 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- brief    remove animation data<br>
-- param     id the id of the animation data
-- @function [parent=#ArmatureDataManager] removeAnimationData 
-- @param self
-- @param #string id
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- Add armature data<br>
-- param id The id of the armature data<br>
-- param armatureData ArmatureData *
-- @function [parent=#ArmatureDataManager] addArmatureData 
-- @param self
-- @param #string id
-- @param #ccs.ArmatureData armatureData
-- @param #string configFilePath
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- @overload self, string, string, string         
-- @overload self, string         
-- @function [parent=#ArmatureDataManager] addArmatureFileInfo
-- @param self
-- @param #string imagePath
-- @param #string plistPath
-- @param #string configFilePath
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)

--------------------------------
-- 
-- @function [parent=#ArmatureDataManager] removeArmatureFileInfo 
-- @param self
-- @param #string configFilePath
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- 
-- @function [parent=#ArmatureDataManager] getTextureDatas 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- brief    get texture data<br>
-- param     id the id of the texture data you want to get<br>
-- return TextureData *
-- @function [parent=#ArmatureDataManager] getTextureData 
-- @param self
-- @param #string id
-- @return TextureData#TextureData ret (return value: ccs.TextureData)
        
--------------------------------
-- brief    get armature data<br>
-- param    id the id of the armature data you want to get<br>
-- return    ArmatureData *
-- @function [parent=#ArmatureDataManager] getArmatureData 
-- @param self
-- @param #string id
-- @return ArmatureData#ArmatureData ret (return value: ccs.ArmatureData)
        
--------------------------------
-- brief    get animation data from _animationDatas(Dictionary)<br>
-- param     id the id of the animation data you want to get<br>
-- return AnimationData *
-- @function [parent=#ArmatureDataManager] getAnimationData 
-- @param self
-- @param #string id
-- @return AnimationData#AnimationData ret (return value: ccs.AnimationData)
        
--------------------------------
-- brief    add animation data<br>
-- param     id the id of the animation data<br>
-- return AnimationData *
-- @function [parent=#ArmatureDataManager] addAnimationData 
-- @param self
-- @param #string id
-- @param #ccs.AnimationData animationData
-- @param #string configFilePath
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- Init ArmatureDataManager
-- @function [parent=#ArmatureDataManager] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief    remove armature data<br>
-- param    id the id of the armature data you want to get
-- @function [parent=#ArmatureDataManager] removeArmatureData 
-- @param self
-- @param #string id
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- 
-- @function [parent=#ArmatureDataManager] getArmatureDatas 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- brief    remove texture data<br>
-- param     id the id of the texture data you want to get
-- @function [parent=#ArmatureDataManager] removeTextureData 
-- @param self
-- @param #string id
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- brief    add texture data<br>
-- param     id the id of the texture data<br>
-- return TextureData *
-- @function [parent=#ArmatureDataManager] addTextureData 
-- @param self
-- @param #string id
-- @param #ccs.TextureData textureData
-- @param #string configFilePath
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- brief    Judge whether or not need auto load sprite file
-- @function [parent=#ArmatureDataManager] isAutoLoadSpriteFile 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief    Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
-- @function [parent=#ArmatureDataManager] addSpriteFrameFromFile 
-- @param self
-- @param #string plistPath
-- @param #string imagePath
-- @param #string configFilePath
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- 
-- @function [parent=#ArmatureDataManager] destroyInstance 
-- @param self
-- @return ArmatureDataManager#ArmatureDataManager self (return value: ccs.ArmatureDataManager)
        
--------------------------------
-- 
-- @function [parent=#ArmatureDataManager] getInstance 
-- @param self
-- @return ArmatureDataManager#ArmatureDataManager ret (return value: ccs.ArmatureDataManager)
        
return nil
