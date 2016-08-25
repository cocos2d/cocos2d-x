
--------------------------------
-- @module ParticleBatchNode
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] setTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
--  initializes the particle system with Texture2D, a capacity of particles 
-- @function [parent=#ParticleBatchNode] initWithTexture 
-- @param self
-- @param #cc.Texture2D tex
-- @param #int capacity
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Disables a particle by inserting a 0'd quad into the texture atlas.<br>
-- param particleIndex The index of the particle.
-- @function [parent=#ParticleBatchNode] disableParticle 
-- @param self
-- @param #int particleIndex
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  Sets the texture atlas used for drawing the quads.<br>
-- param atlas The texture atlas used for drawing the quads.
-- @function [parent=#ParticleBatchNode] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas atlas
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
--  initializes the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles 
-- @function [parent=#ParticleBatchNode] initWithFile 
-- @param self
-- @param #string fileImage
-- @param #int capacity
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- endcode<br>
-- lua NA
-- @function [parent=#ParticleBatchNode] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool doCleanup
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
--  Gets the texture atlas used for drawing the quads.<br>
-- return The texture atlas used for drawing the quads.
-- @function [parent=#ParticleBatchNode] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#ParticleBatchNode] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
--  Inserts a child into the ParticleBatchNode.<br>
-- param system A given particle system.<br>
-- param index The insert index.
-- @function [parent=#ParticleBatchNode] insertChild 
-- @param self
-- @param #cc.ParticleSystem system
-- @param #int index
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
--  Remove a child of the ParticleBatchNode.<br>
-- param index The index of the child.<br>
-- param doCleanup True if all actions and callbacks on this node should be removed, false otherwise.
-- @function [parent=#ParticleBatchNode] removeChildAtIndex 
-- @param self
-- @param #int index
-- @param #bool doCleanup
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
--  Create the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles.<br>
-- param fileImage A given file name.<br>
-- param capacity A capacity of particles.<br>
-- return An autoreleased ParticleBatchNode object.
-- @function [parent=#ParticleBatchNode] create 
-- @param self
-- @param #string fileImage
-- @param #int capacity
-- @return ParticleBatchNode#ParticleBatchNode ret (return value: cc.ParticleBatchNode)
        
--------------------------------
--  Create the particle system with Texture2D, a capacity of particles, which particle system to use.<br>
-- param tex A given texture.<br>
-- param capacity A capacity of particles.<br>
-- return An autoreleased ParticleBatchNode object.<br>
-- js NA
-- @function [parent=#ParticleBatchNode] createWithTexture 
-- @param self
-- @param #cc.Texture2D tex
-- @param #int capacity
-- @return ParticleBatchNode#ParticleBatchNode ret (return value: cc.ParticleBatchNode)
        
--------------------------------
-- @overload self, cc.Node, int, string         
-- @overload self, cc.Node, int, int         
-- @function [parent=#ParticleBatchNode] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)

--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] reorderChild 
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
--------------------------------
-- js ctor
-- @function [parent=#ParticleBatchNode] ParticleBatchNode 
-- @param self
-- @return ParticleBatchNode#ParticleBatchNode self (return value: cc.ParticleBatchNode)
        
return nil
