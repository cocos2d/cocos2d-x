
--------------------------------
-- @module SpriteBatchNode
--------------------------------
-- @function [parent=#SpriteBatchNode] appendChild 
-- @param self
-- @param #cc.Sprite sprite
        
--------------------------------
-- @function [parent=#SpriteBatchNode] reorderBatch 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteBatchNode] initWithTexture 
-- @param self
-- @param #cc.Texture2D texture2d
-- @param #long long
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] lowestAtlasIndexInChild 
-- @param self
-- @param #cc.Sprite sprite
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] atlasIndexForChild 
-- @param self
-- @param #cc.Sprite sprite
-- @param #int int
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas textureatlas
        
--------------------------------
-- @function [parent=#SpriteBatchNode] rebuildIndexInOrder 
-- @param self
-- @param #cc.Sprite sprite
-- @param #long long
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] increaseAtlasCapacity 
-- @param self
        
--------------------------------
-- @function [parent=#SpriteBatchNode] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] insertQuadFromSprite 
-- @param self
-- @param #cc.Sprite sprite
-- @param #long long
        
--------------------------------
-- overload function: init()
--          
-- overload function: init(string, long)
--          
-- @function [parent=#SpriteBatchNode] init
-- @param self
-- @param #string str
-- @param #long long
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#SpriteBatchNode] setTexture 
-- @param self
-- @param #cc.Texture2D texture2d
        
--------------------------------
-- @function [parent=#SpriteBatchNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] highestAtlasIndexInChild 
-- @param self
-- @param #cc.Sprite sprite
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] removeChildAtIndex 
-- @param self
-- @param #long long
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteBatchNode] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteBatchNode] removeSpriteFromAtlas 
-- @param self
-- @param #cc.Sprite sprite
        
--------------------------------
-- @function [parent=#SpriteBatchNode] create 
-- @param self
-- @param #string str
-- @param #long long
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] createWithTexture 
-- @param self
-- @param #cc.Texture2D texture2d
-- @param #long long
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] SpriteBatchNode 
-- @param self
        
return nil
