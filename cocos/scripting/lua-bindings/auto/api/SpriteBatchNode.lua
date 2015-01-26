
--------------------------------
-- @module SpriteBatchNode
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] appendChild 
-- @param self
-- @param #cc.Sprite sprite
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] addSpriteWithoutQuad 
-- @param self
-- @param #cc.Sprite child
-- @param #int z
-- @param #int aTag
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] reorderBatch 
-- @param self
-- @param #bool reorder
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#SpriteBatchNode] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] lowestAtlasIndexInChild 
-- @param self
-- @param #cc.Sprite sprite
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] atlasIndexForChild 
-- @param self
-- @param #cc.Sprite sprite
-- @param #int z
-- @return long#long ret (return value: long)
        
--------------------------------
--  sets the TextureAtlas object 
-- @function [parent=#SpriteBatchNode] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas textureAtlas
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] increaseAtlasCapacity 
-- @param self
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
--  returns the TextureAtlas object 
-- @function [parent=#SpriteBatchNode] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
--  Inserts a quad at a certain index into the texture atlas. The Sprite won't be added into the children array.<br>
-- This method should be called only when you are dealing with very big AtlasSrite and when most of the Sprite won't be updated.<br>
-- For example: a tile map (TMXMap) or a label with lots of characters (LabelBMFont)
-- @function [parent=#SpriteBatchNode] insertQuadFromSprite 
-- @param self
-- @param #cc.Sprite sprite
-- @param #long index
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] setTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] rebuildIndexInOrder 
-- @param self
-- @param #cc.Sprite parent
-- @param #long index
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] highestAtlasIndexInChild 
-- @param self
-- @param #cc.Sprite sprite
-- @return long#long ret (return value: long)
        
--------------------------------
--  removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.<br>
-- warning Removing a child from a SpriteBatchNode is very slow
-- @function [parent=#SpriteBatchNode] removeChildAtIndex 
-- @param self
-- @param #long index
-- @param #bool doCleanup
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] removeSpriteFromAtlas 
-- @param self
-- @param #cc.Sprite sprite
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- endcode<br>
-- lua NA 
-- @function [parent=#SpriteBatchNode] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
--  creates a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.<br>
-- The capacity will be increased in 33% in runtime if it run out of space.<br>
-- The file will be loaded using the TextureMgr.
-- @function [parent=#SpriteBatchNode] create 
-- @param self
-- @param #string fileImage
-- @param #long capacity
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
--  creates a SpriteBatchNode with a texture2d and capacity of children.<br>
-- The capacity will be increased in 33% in runtime if it run out of space.
-- @function [parent=#SpriteBatchNode] createWithTexture 
-- @param self
-- @param #cc.Texture2D tex
-- @param #long capacity
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
-- @overload self, cc.Node, int, string         
-- @overload self, cc.Node, int, int         
-- @function [parent=#SpriteBatchNode] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)

--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] sortAllChildren 
-- @param self
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
--------------------------------
-- 
-- @function [parent=#SpriteBatchNode] reorderChild 
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @return SpriteBatchNode#SpriteBatchNode self (return value: cc.SpriteBatchNode)
        
return nil
