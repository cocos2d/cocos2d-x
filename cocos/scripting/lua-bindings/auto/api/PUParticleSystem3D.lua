
--------------------------------
-- @module PUParticleSystem3D
-- @extend ParticleSystem3D
-- @parent_module cc

--------------------------------
--  Set the maximum velocity a particle can have.
-- @function [parent=#PUParticleSystem3D] setMaxVelocity 
-- @param self
-- @param #float maxVelocity
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
--  Returns the velocity scale, defined in the particle system, but passed to the technique for convenience.
-- @function [parent=#PUParticleSystem3D] getParticleSystemScaleVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getDerivedPosition 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  If the orientation of the particle system has been changed since the last update, the passed vector<br>
-- is rotated accordingly.
-- @function [parent=#PUParticleSystem3D] rotationOffset 
-- @param self
-- @param #vec3_table pos
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getDefaultWidth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setParticleSystemScaleVelocity 
-- @param self
-- @param #float scaleVelocity
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- add particle affector
-- @function [parent=#PUParticleSystem3D] addEmitter 
-- @param self
-- @param #cc.PUParticle3DEmitter emitter
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getDerivedScale 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getDefaultHeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setDefaultHeight 
-- @param self
-- @param #float height
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getDefaultDepth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getMaterialName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setDefaultWidth 
-- @param self
-- @param #float width
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getTimeElapsedSinceStart 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setMaterialName 
-- @param self
-- @param #string name
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setDefaultDepth 
-- @param self
-- @param #float depth
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
--  Return the maximum velocity a particle can have, even if the velocity of the particle has been set higher (either by <br>
-- initialisation of the particle or by means of an affector).
-- @function [parent=#PUParticleSystem3D] getMaxVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @overload self, string, string         
-- @function [parent=#PUParticleSystem3D] create
-- @param self
-- @param #string filePath
-- @param #string materialPath
-- @return PUParticleSystem3D#PUParticleSystem3D ret (return value: cc.PUParticleSystem3D)

--------------------------------
-- particle system play control
-- @function [parent=#PUParticleSystem3D] startParticleSystem 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- stop particle
-- @function [parent=#PUParticleSystem3D] stopParticleSystem 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] update 
-- @param self
-- @param #float delta
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- pause particle
-- @function [parent=#PUParticleSystem3D] pauseParticleSystem 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- resume particle
-- @function [parent=#PUParticleSystem3D] resumeParticleSystem 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getAliveParticleCount 
-- @param self
-- @return int#int ret (return value: int)
        
return nil
