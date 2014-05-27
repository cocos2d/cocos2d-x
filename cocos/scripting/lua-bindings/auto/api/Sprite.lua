
--------------------------------
-- @module Sprite
-- @extend Node,TextureProtocol

--------------------------------
-- overload function: setSpriteFrame(cc.SpriteFrame)
--          
-- overload function: setSpriteFrame(string)
--          
-- @function [parent=#Sprite] setSpriteFrame
-- @param self
-- @param #string str

--------------------------------
-- overload function: setTexture(cc.Texture2D)
--          
-- overload function: setTexture(string)
--          
-- @function [parent=#Sprite] setTexture
-- @param self
-- @param #string str

--------------------------------
-- @function [parent=#Sprite] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- @function [parent=#Sprite] setFlippedY 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] setFlippedX 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] getBatchNode 
-- @param self
-- @return SpriteBatchNode#SpriteBatchNode ret (return value: cc.SpriteBatchNode)
        
--------------------------------
-- @function [parent=#Sprite] getOffsetPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Sprite] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] updateTransform 
-- @param self
        
--------------------------------
-- overload function: setTextureRect(rect_table, bool, size_table)
--          
-- overload function: setTextureRect(rect_table)
--          
-- @function [parent=#Sprite] setTextureRect
-- @param self
-- @param #rect_table rect
-- @param #bool bool
-- @param #size_table size

--------------------------------
-- @function [parent=#Sprite] isFrameDisplayed 
-- @param self
-- @param #cc.SpriteFrame spriteframe
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Sprite] getAtlasIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#Sprite] setBatchNode 
-- @param self
-- @param #cc.SpriteBatchNode spritebatchnode
        
--------------------------------
-- @function [parent=#Sprite] setDisplayFrameWithAnimationName 
-- @param self
-- @param #string str
-- @param #long long
        
--------------------------------
-- @function [parent=#Sprite] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas textureatlas
        
--------------------------------
-- @function [parent=#Sprite] getSpriteFrame 
-- @param self
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
-- @function [parent=#Sprite] isDirty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Sprite] setAtlasIndex 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#Sprite] setDirty 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] isTextureRectRotated 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Sprite] getTextureRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#Sprite] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
-- @function [parent=#Sprite] isFlippedX 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Sprite] isFlippedY 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Sprite] setVertexRect 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- overload function: create(string)
--          
-- overload function: create()
--          
-- overload function: create(string, rect_table)
--          
-- @function [parent=#Sprite] create
-- @param self
-- @param #string str
-- @param #rect_table rect
-- @return Sprite#Sprite ret (retunr value: cc.Sprite)

--------------------------------
-- overload function: createWithTexture(cc.Texture2D, rect_table, bool)
--          
-- overload function: createWithTexture(cc.Texture2D)
--          
-- @function [parent=#Sprite] createWithTexture
-- @param self
-- @param #cc.Texture2D texture2d
-- @param #rect_table rect
-- @param #bool bool
-- @return Sprite#Sprite ret (retunr value: cc.Sprite)

--------------------------------
-- @function [parent=#Sprite] createWithSpriteFrameName 
-- @param self
-- @param #string str
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @function [parent=#Sprite] createWithSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteframe
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @function [parent=#Sprite] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] addChild 
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#Sprite] setScaleY 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Sprite] setScaleX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Sprite] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Sprite] setPositionZ 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Sprite] setAnchorPoint 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#Sprite] setRotationSkewX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Sprite] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Sprite] setRotationSkewY 
-- @param self
-- @param #float float
        
--------------------------------
-- overload function: setScale(float)
--          
-- overload function: setScale(float, float)
--          
-- @function [parent=#Sprite] setScale
-- @param self
-- @param #float float
-- @param #float float

--------------------------------
-- @function [parent=#Sprite] reorderChild 
-- @param self
-- @param #cc.Node node
-- @param #int int
        
--------------------------------
-- @function [parent=#Sprite] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] sortAllChildren 
-- @param self
        
--------------------------------
-- @function [parent=#Sprite] setOpacityModifyRGB 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] setRotation 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Sprite] setSkewY 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Sprite] setVisible 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Sprite] setSkewX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Sprite] ignoreAnchorPointForPosition 
-- @param self
-- @param #bool bool
        
return nil
