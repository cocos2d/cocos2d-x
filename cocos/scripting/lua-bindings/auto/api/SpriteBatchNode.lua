
--------------------------------
-- @module SpriteBatchNode
-- @extend Node,TextureProtocol

--------------------------------
-- @function [parent=#SpriteBatchNode] appendChild 
-- @param self
-- @param #cc.Sprite sprite
        
--------------------------------
-- @function [parent=#SpriteBatchNode] addSpriteWithoutQuad 
-- @param self
-- @param #cc.Sprite sprite
-- @param #int int
-- @param #int int
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] reorderBatch 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteBatchNode] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool bool
        
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
-- @function [parent=#SpriteBatchNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
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
-- @function [parent=#SpriteBatchNode] setTexture 
-- @param self
-- @param #cc.Texture2D texture2d
        
--------------------------------
-- @function [parent=#SpriteBatchNode] rebuildIndexInOrder 
-- @param self
-- @param #cc.Sprite sprite
-- @param #long long
-- @return long#long ret (return value: long)
        
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
-- @function [parent=#SpriteBatchNode] addChild 
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#SpriteBatchNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #kmMat4 kmmat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteBatchNode] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#SpriteBatchNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #kmMat4 kmmat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteBatchNode] sortAllChildren 
-- @param self
        
--------------------------------
-- @function [parent=#SpriteBatchNode] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#SpriteBatchNode] reorderChild 
-- @param self
-- @param #cc.Node node
-- @param #int int
        
return nil
