
--------------------------------
-- @module ParticleSystem3D
-- @extend Node,BlendProtocol
-- @parent_module cc

--------------------------------
-- remove affector by index
-- @function [parent=#ParticleSystem3D] removeAffector 
-- @param self
-- @param #int index
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- resume particle
-- @function [parent=#ParticleSystem3D] resumeParticleSystem 
-- @param self
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- remove all particle affector
-- @function [parent=#ParticleSystem3D] removeAllAffector 
-- @param self
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- add particle affector
-- @function [parent=#ParticleSystem3D] addAffector 
-- @param self
-- @param #cc.Particle3DAffector affector
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- particle system play control
-- @function [parent=#ParticleSystem3D] startParticleSystem 
-- @param self
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- is enabled
-- @function [parent=#ParticleSystem3D] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set emitter for particle system, can set your own particle emitter
-- @function [parent=#ParticleSystem3D] setEmitter 
-- @param self
-- @param #cc.Particle3DEmitter emitter
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem3D] isKeepLocal 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Enables or disables the system.
-- @function [parent=#ParticleSystem3D] setEnabled 
-- @param self
-- @param #bool enabled
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- get particle quota
-- @function [parent=#ParticleSystem3D] getParticleQuota 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- override function
-- @function [parent=#ParticleSystem3D] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- pause particle
-- @function [parent=#ParticleSystem3D] pauseParticleSystem 
-- @param self
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- get particle playing state
-- @function [parent=#ParticleSystem3D] getState 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- get alive particles count
-- @function [parent=#ParticleSystem3D] getAliveParticleCount 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- set particle quota
-- @function [parent=#ParticleSystem3D] setParticleQuota 
-- @param self
-- @param #unsigned int quota
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- override function
-- @function [parent=#ParticleSystem3D] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- set particle render, can set your own particle render
-- @function [parent=#ParticleSystem3D] setRender 
-- @param self
-- @param #cc.Particle3DRender render
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- stop particle
-- @function [parent=#ParticleSystem3D] stopParticleSystem 
-- @param self
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem3D] setKeepLocal 
-- @param self
-- @param #bool keepLocal
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- override function
-- @function [parent=#ParticleSystem3D] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- override function
-- @function [parent=#ParticleSystem3D] update 
-- @param self
-- @param #float delta
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem3D] ParticleSystem3D 
-- @param self
-- @return ParticleSystem3D#ParticleSystem3D self (return value: cc.ParticleSystem3D)
        
return nil
