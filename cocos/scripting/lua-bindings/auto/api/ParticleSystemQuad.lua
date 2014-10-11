
--------------------------------
-- @module ParticleSystemQuad
-- @extend ParticleSystem
-- @parent_module cc

--------------------------------
--  Sets a new SpriteFrame as particle.<br>
-- WARNING: this method is experimental. Use setTextureWithRect instead.<br>
-- since v0.99.4
-- @function [parent=#ParticleSystemQuad] setDisplayFrame 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
        
--------------------------------
--  Sets a new texture with a rect. The rect is in Points.<br>
-- since v0.99.4<br>
-- js NA<br>
-- lua NA
-- @function [parent=#ParticleSystemQuad] setTextureWithRect 
-- @param self
-- @param #cc.Texture2D texture
-- @param #rect_table rect
        
--------------------------------
--  listen the event that renderer was recreated on Android/WP8<br>
-- js NA<br>
-- lua NA
-- @function [parent=#ParticleSystemQuad] listenRendererRecreated 
-- @param self
-- @param #cc.EventCustom event
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @overload self, map_table         
-- @function [parent=#ParticleSystemQuad] create
-- @param self
-- @param #map_table dictionary
-- @return ParticleSystemQuad#ParticleSystemQuad ret (retunr value: cc.ParticleSystemQuad)

--------------------------------
--  creates a Particle Emitter with a number of particles 
-- @function [parent=#ParticleSystemQuad] createWithTotalParticles 
-- @param self
-- @param #int numberOfParticles
-- @return ParticleSystemQuad#ParticleSystemQuad ret (return value: cc.ParticleSystemQuad)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemQuad] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
