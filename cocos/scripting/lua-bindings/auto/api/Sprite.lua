
--------------------------------
-- @module Sprite
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
-- @overload self, cc.SpriteFrame         
-- @overload self, string         
-- @function [parent=#Sprite] setSpriteFrame
-- @param self
-- @param #string spriteFrameName
-- @return Sprite#Sprite self (return value: cc.Sprite)

--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#Sprite] setTexture
-- @param self
-- @param #string filename
-- @return Sprite#Sprite self (return value: cc.Sprite)

--------------------------------
--  Returns the Texture2D object used by the sprite. 
-- @function [parent=#Sprite] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- Sets whether the sprite should be flipped vertically or not.<br>
-- param flippedY true if the sprite should be flipped vertically, false otherwise.
-- @function [parent=#Sprite] setFlippedY 
-- @param self
-- @param #bool flippedY
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Sets whether the sprite should be flipped horizontally or not.<br>
-- param flippedX true if the sprite should be flipped horizontally, false otherwise.
-- @function [parent=#Sprite] setFlippedX 
-- @param self
-- @param #bool flippedX
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- / @}
-- @function [parent=#Sprite] getResourceType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- / @{/ @name Animation methods<br>
-- Changes the display frame with animation name and index.<br>
-- The animation name will be get from the AnimationCache.
-- @function [parent=#Sprite] setDisplayFrameWithAnimationName 
-- @param self
-- @param #string animationName
-- @param #int frameIndex
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Returns the batch node object if this sprite is rendered by SpriteBatchNode.<br>
-- return The SpriteBatchNode object if this sprite is rendered by SpriteBatchNode,<br>
-- nullptr if the sprite isn't used batch node.
-- @function [parent=#Sprite] getBatchNode 
-- @param self
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
-- Gets the offset position of the sprite. Calculated automatically by editors like Zwoptex.
-- @function [parent=#Sprite] getOffsetPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- brief Returns the Cap Insets rect<br>
-- return Scale9Sprite's cap inset.
-- @function [parent=#Sprite] getCenterRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#Sprite] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- setCenterRectNormalized<br>
-- Useful to implement "9 sliced" sprites.<br>
-- The default value is (0,0) - (1,1), which means that only one "slice" will be used: From top-left (0,0) to bottom-right (1,1).<br>
-- If the value is different than (0,0), (1,1), then the sprite will be sliced into a 3 x 3 grid. The four corners of this grid are applied without<br>
-- performing any scaling. The upper- and lower-middle parts are scaled horizontally, and the left- and right-middle parts are scaled vertically.<br>
-- The center is scaled in both directions.<br>
-- Important: The scaling is based the Sprite's trimmed size.<br>
-- Limitations: Does not work when the sprite is part of `SpriteBatchNode`.
-- @function [parent=#Sprite] setCenterRectNormalized 
-- @param self
-- @param #rect_table rect
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
--  returns whether or not contentSize stretches the sprite's texture 
-- @function [parent=#Sprite] isStretchEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, rect_table, bool, size_table         
-- @overload self, rect_table         
-- @function [parent=#Sprite] setTextureRect
-- @param self
-- @param #rect_table rect
-- @param #bool rotated
-- @param #size_table untrimmedSize
-- @return Sprite#Sprite self (return value: cc.Sprite)

--------------------------------
-- Initializes a sprite with an sprite frame name.<br>
-- A SpriteFrame will be fetched from the SpriteFrameCache by name.<br>
-- If the SpriteFrame doesn't exist it will raise an exception.<br>
-- param   spriteFrameName  A key string that can fetched a valid SpriteFrame from SpriteFrameCache.<br>
-- return  True if the sprite is initialized properly, false otherwise.
-- @function [parent=#Sprite] initWithSpriteFrameName 
-- @param self
-- @param #string spriteFrameName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  whether or not contentSize stretches the sprite's texture 
-- @function [parent=#Sprite] setStretchEnabled 
-- @param self
-- @param #bool enabled
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Returns whether or not a SpriteFrame is being displayed.
-- @function [parent=#Sprite] isFrameDisplayed 
-- @param self
-- @param #cc.SpriteFrame frame
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns the index used on the TextureAtlas.
-- @function [parent=#Sprite] getAtlasIndex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Sets the batch node to sprite.<br>
-- warning This method is not recommended for game developers. Sample code for using batch node<br>
-- code<br>
-- SpriteBatchNode *batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 15);<br>
-- Sprite *sprite = Sprite::createWithTexture(batch->getTexture(), Rect(0, 0, 57, 57));<br>
-- batch->addChild(sprite);<br>
-- layer->addChild(batch);<br>
-- endcode
-- @function [parent=#Sprite] setBatchNode 
-- @param self
-- @param #cc.SpriteBatchNode spriteBatchNode
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- js  NA<br>
-- lua NA
-- @function [parent=#Sprite] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setCenterRect 
-- @param self
-- @param #rect_table rect
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Sets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
-- @function [parent=#Sprite] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas textureAtlas
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Returns the current displayed frame.
-- @function [parent=#Sprite] getSpriteFrame 
-- @param self
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
-- 
-- @function [parent=#Sprite] getResourceName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Whether or not the Sprite needs to be updated in the Atlas.<br>
-- return True if the sprite needs to be updated in the Atlas, false otherwise.
-- @function [parent=#Sprite] isDirty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- getCenterRectNormalized<br>
-- Returns the CenterRect in normalized coordinates
-- @function [parent=#Sprite] getCenterRectNormalized 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Sets the index used on the TextureAtlas.<br>
-- warning Don't modify this value unless you know what you are doing.
-- @function [parent=#Sprite] setAtlasIndex 
-- @param self
-- @param #int atlasIndex
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- @overload self, cc.Texture2D, rect_table         
-- @overload self, cc.Texture2D         
-- @overload self, cc.Texture2D, rect_table, bool         
-- @function [parent=#Sprite] initWithTexture
-- @param self
-- @param #cc.Texture2D texture
-- @param #rect_table rect
-- @param #bool rotated
-- @return bool#bool ret (return value: bool)

--------------------------------
-- Makes the Sprite to be updated in the Atlas.
-- @function [parent=#Sprite] setDirty 
-- @param self
-- @param #bool dirty
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Returns whether or not the texture rectangle is rotated.
-- @function [parent=#Sprite] isTextureRectRotated 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns the rect of the Sprite in points.
-- @function [parent=#Sprite] getTextureRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @overload self, string, rect_table         
-- @overload self, string         
-- @function [parent=#Sprite] initWithFile
-- @param self
-- @param #string filename
-- @param #rect_table rect
-- @return bool#bool ret (return value: bool)

--------------------------------
-- / @{/ @name Functions inherited from TextureProtocol.<br>
-- code<br>
-- When this function bound into js or lua,the parameter will be changed.<br>
-- In js: var setBlendFunc(var src, var dst).<br>
-- In lua: local setBlendFunc(local src, local dst).<br>
-- endcode
-- @function [parent=#Sprite] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Gets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
-- @function [parent=#Sprite] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
-- Initializes a sprite with an SpriteFrame. The texture and rect in SpriteFrame will be applied on this sprite.<br>
-- param   spriteFrame  A SpriteFrame object. It should includes a valid texture and a rect.<br>
-- return  True if the sprite is initialized properly, false otherwise.
-- @function [parent=#Sprite] initWithSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns the flag which indicates whether the sprite is flipped horizontally or not.<br>
-- It only flips the texture of the sprite, and not the texture of the sprite's children.<br>
-- Also, flipping the texture doesn't alter the anchorPoint.<br>
-- If you want to flip the anchorPoint too, and/or to flip the children too use:<br>
-- sprite->setScaleX(sprite->getScaleX() * -1);<br>
-- return true if the sprite is flipped horizontally, false otherwise.
-- @function [parent=#Sprite] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Return the flag which indicates whether the sprite is flipped vertically or not.<br>
-- It only flips the texture of the sprite, and not the texture of the sprite's children.<br>
-- Also, flipping the texture doesn't alter the anchorPoint.<br>
-- If you want to flip the anchorPoint too, and/or to flip the children too use:<br>
-- sprite->setScaleY(sprite->getScaleY() * -1);<br>
-- return true if the sprite is flipped vertically, false otherwise.
-- @function [parent=#Sprite] isFlippedY 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets the vertex rect.<br>
-- It will be called internally by setTextureRect.<br>
-- Useful if you want to create 2x images from SD images in Retina Display.<br>
-- Do not call it manually. Use setTextureRect instead.
-- @function [parent=#Sprite] setVertexRect 
-- @param self
-- @param #rect_table rect
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- @overload self, cc.Texture2D, rect_table, bool         
-- @overload self, cc.Texture2D         
-- @function [parent=#Sprite] createWithTexture
-- @param self
-- @param #cc.Texture2D texture
-- @param #rect_table rect
-- @param #bool rotated
-- @return Sprite#Sprite ret (return value: cc.Sprite)

--------------------------------
-- Creates a sprite with an sprite frame name.<br>
-- A SpriteFrame will be fetched from the SpriteFrameCache by spriteFrameName param.<br>
-- If the SpriteFrame doesn't exist it will raise an exception.<br>
-- param   spriteFrameName A null terminated string which indicates the sprite frame name.<br>
-- return  An autoreleased sprite object.
-- @function [parent=#Sprite] createWithSpriteFrameName 
-- @param self
-- @param #string spriteFrameName
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- Creates a sprite with an sprite frame.<br>
-- param   spriteFrame    A sprite frame which involves a texture and a rect.<br>
-- return  An autoreleased sprite object.
-- @function [parent=#Sprite] createWithSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @overload self, cc.Node, int, string         
-- @overload self, cc.Node, int, int         
-- @function [parent=#Sprite] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
-- @return Sprite#Sprite self (return value: cc.Sprite)

--------------------------------
-- 
-- @function [parent=#Sprite] setAnchorPoint 
-- @param self
-- @param #vec2_table anchor
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setRotationSkewX 
-- @param self
-- @param #float rotationX
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setScaleY 
-- @param self
-- @param #float scaleY
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- @overload self, float         
-- @overload self, float, float         
-- @function [parent=#Sprite] setScale
-- @param self
-- @param #float scaleX
-- @param #float scaleY
-- @return Sprite#Sprite self (return value: cc.Sprite)

--------------------------------
-- 
-- @function [parent=#Sprite] setContentSize 
-- @param self
-- @param #size_table size
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setOpacityModifyRGB 
-- @param self
-- @param #bool modify
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setRotation 
-- @param self
-- @param #float rotation
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setIgnoreAnchorPointForPosition 
-- @param self
-- @param #bool value
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- / @{/ @name Functions inherited from Node.
-- @function [parent=#Sprite] setScaleX 
-- @param self
-- @param #float scaleX
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- js NA
-- @function [parent=#Sprite] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setRotationSkewY 
-- @param self
-- @param #float rotationY
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] sortAllChildren 
-- @param self
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] reorderChild 
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setPositionZ 
-- @param self
-- @param #float positionZ
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- Updates the quad according the rotation, position, scale values.
-- @function [parent=#Sprite] updateTransform 
-- @param self
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setSkewX 
-- @param self
-- @param #float sx
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setSkewY 
-- @param self
-- @param #float sy
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#Sprite] setVisible 
-- @param self
-- @param #bool bVisible
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
--------------------------------
-- js ctor
-- @function [parent=#Sprite] Sprite 
-- @param self
-- @return Sprite#Sprite self (return value: cc.Sprite)
        
return nil
