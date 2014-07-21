
--------------------------------
-- @module SpriteFrameCache
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @overload self, string, string         
-- @overload self, string         
-- @overload self, string, cc.Texture2D         
-- @function [parent=#SpriteFrameCache] addSpriteFramesWithFile
-- @param self
-- @param #string str
-- @param #cc.Texture2D texture2d

--------------------------------
-- @function [parent=#SpriteFrameCache] addSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteframe
-- @param #string str
        
--------------------------------
-- @function [parent=#SpriteFrameCache] removeUnusedSpriteFrames 
-- @param self
        
--------------------------------
-- @function [parent=#SpriteFrameCache] getSpriteFrameByName 
-- @param self
-- @param #string str
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
-- @function [parent=#SpriteFrameCache] removeSpriteFramesFromFile 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#SpriteFrameCache] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SpriteFrameCache] removeSpriteFrames 
-- @param self
        
--------------------------------
-- @function [parent=#SpriteFrameCache] removeSpriteFramesFromTexture 
-- @param self
-- @param #cc.Texture2D texture2d
        
--------------------------------
-- @function [parent=#SpriteFrameCache] removeSpriteFrameByName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#SpriteFrameCache] destroyInstance 
-- @param self
        
--------------------------------
-- @function [parent=#SpriteFrameCache] getInstance 
-- @param self
-- @return SpriteFrameCache#SpriteFrameCache ret (return value: cc.SpriteFrameCache)
        
return nil
