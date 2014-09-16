
--------------------------------
-- @module ParticleBatchNode
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] setTexture 
-- @param self
-- @param #cc.Texture2D texture
        
--------------------------------
--  disables a particle by inserting a 0'd quad into the texture atlas 
-- @function [parent=#ParticleBatchNode] disableParticle 
-- @param self
-- @param #int particleIndex
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  Sets the texture atlas used for drawing the quads 
-- @function [parent=#ParticleBatchNode] setTextureAtlas 
-- @param self
-- @param #cc.TextureAtlas atlas
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool doCleanup
        
--------------------------------
--  Gets the texture atlas used for drawing the quads 
-- @function [parent=#ParticleBatchNode] getTextureAtlas 
-- @param self
-- @return TextureAtlas#TextureAtlas ret (return value: cc.TextureAtlas)
        
--------------------------------
--  Inserts a child into the ParticleBatchNode 
-- @function [parent=#ParticleBatchNode] insertChild 
-- @param self
-- @param #cc.ParticleSystem system
-- @param #int index
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] removeChildAtIndex 
-- @param self
-- @param #int index
-- @param #bool doCleanup
        
--------------------------------
--  initializes the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles 
-- @function [parent=#ParticleBatchNode] create 
-- @param self
-- @param #string fileImage
-- @param #int capacity
-- @return ParticleBatchNode#ParticleBatchNode ret (return value: cc.ParticleBatchNode)
        
--------------------------------
--  initializes the particle system with Texture2D, a capacity of particles, which particle system to use 
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

--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] reorderChild 
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
        
--------------------------------
-- 
-- @function [parent=#ParticleBatchNode] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
        
return nil
