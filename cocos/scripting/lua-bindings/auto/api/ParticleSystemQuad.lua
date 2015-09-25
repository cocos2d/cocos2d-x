
--------------------------------
-- @module ParticleSystemQuad
-- @extend ParticleSystem
-- @parent_module cc

--------------------------------
--  Sets a new SpriteFrame as particle.<br>
-- WARNING: this method is experimental. Use setTextureWithRect instead.<br>
-- param spriteFrame A given sprite frame as particle texture.<br>
-- since v0.99.4
-- @function [parent=#ParticleSystemQuad] setDisplayFrame 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @return ParticleSystemQuad#ParticleSystemQuad self (return value: cc.ParticleSystemQuad)
        
--------------------------------
--  Sets a new texture with a rect. The rect is in Points.<br>
-- since v0.99.4<br>
-- js NA<br>
-- lua NA<br>
-- param texture A given texture.<br>
-- 8 @param rect A given rect, in points.
-- @function [parent=#ParticleSystemQuad] setTextureWithRect 
-- @param self
-- @param #cc.Texture2D texture
-- @param #rect_table rect
-- @return ParticleSystemQuad#ParticleSystemQuad self (return value: cc.ParticleSystemQuad)
        
--------------------------------
--  Listen the event that renderer was recreated on Android/WP8.<br>
-- js NA<br>
-- lua NA<br>
-- param event the event that renderer was recreated on Android/WP8.
-- @function [parent=#ParticleSystemQuad] listenRendererRecreated 
-- @param self
-- @param #cc.EventCustom event
-- @return ParticleSystemQuad#ParticleSystemQuad self (return value: cc.ParticleSystemQuad)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @overload self, map_table         
-- @function [parent=#ParticleSystemQuad] create
-- @param self
-- @param #map_table dictionary
-- @return ParticleSystemQuad#ParticleSystemQuad ret (return value: cc.ParticleSystemQuad)

--------------------------------
--  Creates a Particle Emitter with a number of particles.<br>
-- param numberOfParticles A given number of particles.<br>
-- return An autoreleased ParticleSystemQuad object.
-- @function [parent=#ParticleSystemQuad] createWithTotalParticles 
-- @param self
-- @param #int numberOfParticles
-- @return ParticleSystemQuad#ParticleSystemQuad ret (return value: cc.ParticleSystemQuad)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemQuad] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#ParticleSystemQuad] updateParticleQuads 
-- @param self
-- @return ParticleSystemQuad#ParticleSystemQuad self (return value: cc.ParticleSystemQuad)
        
--------------------------------
-- js ctor
-- @function [parent=#ParticleSystemQuad] ParticleSystemQuad 
-- @param self
-- @return ParticleSystemQuad#ParticleSystemQuad self (return value: cc.ParticleSystemQuad)
        
return nil
