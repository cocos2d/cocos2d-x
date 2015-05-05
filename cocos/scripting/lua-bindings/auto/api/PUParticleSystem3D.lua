
--------------------------------
-- @module PUParticleSystem3D
-- @extend ParticleSystem3D
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] initWithFilePath 
-- @param self
-- @param #string filePath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns the velocity scale, defined in the particle system, but passed to the technique for convenience.
-- @function [parent=#PUParticleSystem3D] getParticleSystemScaleVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setEmittedSystemQuota 
-- @param self
-- @param #unsigned int quota
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- default particle depth
-- @function [parent=#PUParticleSystem3D] getDefaultDepth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getEmittedSystemQuota 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] initWithFilePathAndMaterialPath 
-- @param self
-- @param #string filePath
-- @param #string materialPath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] clearAllParticles 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getMaterialName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] calulateRotationOffset 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- Return the maximum velocity a particle can have, even if the velocity of the particle has been set higher (either by initialisation of the particle or by means of an affector).
-- @function [parent=#PUParticleSystem3D] getMaxVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] forceUpdate 
-- @param self
-- @param #float delta
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getTimeElapsedSinceStart 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] removeAllBehaviourTemplate 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getEmittedEmitterQuota 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  Forces emission of particles.<br>
-- remarks The number of requested particles are the exact number that are emitted. No down-scalling is applied.
-- @function [parent=#PUParticleSystem3D] forceEmission 
-- @param self
-- @param #cc.PUEmitter emitter
-- @param #unsigned int requested
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] addListener 
-- @param self
-- @param #cc.PUListener listener
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] isMarkedForEmission 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- default particle width
-- @function [parent=#PUParticleSystem3D] getDefaultWidth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setEmittedEmitterQuota 
-- @param self
-- @param #unsigned int quota
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setMarkedForEmission 
-- @param self
-- @param #bool isMarked
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] clone 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D ret (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- add particle affector
-- @function [parent=#PUParticleSystem3D] addEmitter 
-- @param self
-- @param #cc.PUEmitter emitter
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] addBehaviourTemplate 
-- @param self
-- @param #cc.PUBehaviour behaviour
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setDefaultWidth 
-- @param self
-- @param #float width
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] copyAttributesTo 
-- @param self
-- @param #cc.PUParticleSystem3D system
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setMaterialName 
-- @param self
-- @param #string name
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getParentParticleSystem 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D ret (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] removeListener 
-- @param self
-- @param #cc.PUListener listener
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- Set the maximum velocity a particle can have.
-- @function [parent=#PUParticleSystem3D] setMaxVelocity 
-- @param self
-- @param #float maxVelocity
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- default particle height
-- @function [parent=#PUParticleSystem3D] getDefaultHeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getDerivedPosition 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- If the orientation of the particle system has been changed since the last update, the passed vector is rotated accordingly.
-- @function [parent=#PUParticleSystem3D] rotationOffset 
-- @param self
-- @param #vec3_table pos
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] removeAllEmitter 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setParticleSystemScaleVelocity 
-- @param self
-- @param #float scaleVelocity
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] getDerivedScale 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setDefaultHeight 
-- @param self
-- @param #float height
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] removeAllListener 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] makeParticleLocal 
-- @param self
-- @param #cc.PUParticle3D particle
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] removerAllObserver 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] setDefaultDepth 
-- @param self
-- @param #float depth
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] addObserver 
-- @param self
-- @param #cc.PUObserver observer
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
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
-- 
-- @function [parent=#PUParticleSystem3D] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
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
        
--------------------------------
-- 
-- @function [parent=#PUParticleSystem3D] PUParticleSystem3D 
-- @param self
-- @return PUParticleSystem3D#PUParticleSystem3D self (return value: cc.PUParticleSystem3D)
        
return nil
