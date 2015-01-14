
--------------------------------
-- @module ParticleSystem
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
--  size variance in pixels of each particle 
-- @function [parent=#ParticleSystem] getStartSizeVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  whether or not the system is full
-- @function [parent=#ParticleSystem] isFull 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getBatchNode 
-- @param self
-- @return ParticleBatchNode#ParticleBatchNode ret (return value: cc.ParticleBatchNode)
        
--------------------------------
--  start color of each particle 
-- @function [parent=#ParticleSystem] getStartColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  particles movement type: Free or Grouped<br>
-- since v0.8
-- @function [parent=#ParticleSystem] getPositionType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setPosVar 
-- @param self
-- @param #vec2_table pos
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getEndSpin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setRotatePerSecondVar 
-- @param self
-- @param #float degrees
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getStartSpinVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getRadialAccelVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  end size variance in pixels of each particle 
-- @function [parent=#ParticleSystem] getEndSizeVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setRotation 
-- @param self
-- @param #float newRotation
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setTangentialAccel 
-- @param self
-- @param #float t
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setScaleY 
-- @param self
-- @param #float newScaleY
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setScaleX 
-- @param self
-- @param #float newScaleX
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getRadialAccel 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartRadius 
-- @param self
-- @param #float startRadius
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setRotatePerSecond 
-- @param self
-- @param #float degrees
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndSize 
-- @param self
-- @param #float endSize
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getGravity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getTangentialAccel 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndRadius 
-- @param self
-- @param #float endRadius
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  angle and angle variation of each particle 
-- @function [parent=#ParticleSystem] getAngle 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndColor 
-- @param self
-- @param #color4f_table color
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartSpin 
-- @param self
-- @param #float spin
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setDuration 
-- @param self
-- @param #float duration
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setTexture 
-- @param self
-- @param #cc.Texture2D texture
        
--------------------------------
--  Position variance of the emitter 
-- @function [parent=#ParticleSystem] getPosVar 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] updateWithNoTime 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] isBlendAdditive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getSpeedVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setPositionType 
-- @param self
-- @param #int type
        
--------------------------------
--  stop emitting particles. Running particles will continue to run until they die
-- @function [parent=#ParticleSystem] stopSystem 
-- @param self
        
--------------------------------
--  sourcePosition of the emitter 
-- @function [parent=#ParticleSystem] getSourcePosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setLifeVar 
-- @param self
-- @param #float lifeVar
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setTotalParticles 
-- @param self
-- @param #int totalParticles
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndColorVar 
-- @param self
-- @param #color4f_table color
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getAtlasIndex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  start size in pixels of each particle 
-- @function [parent=#ParticleSystem] getStartSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartSpinVar 
-- @param self
-- @param #float pinVar
        
--------------------------------
--  Kill all living particles.
-- @function [parent=#ParticleSystem] resetSystem 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setAtlasIndex 
-- @param self
-- @param #int index
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setTangentialAccelVar 
-- @param self
-- @param #float t
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndRadiusVar 
-- @param self
-- @param #float endRadiusVar
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getEndRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] isActive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setRadialAccelVar 
-- @param self
-- @param #float t
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartSize 
-- @param self
-- @param #float startSize
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setSpeed 
-- @param self
-- @param #float speed
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getStartSpin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getRotatePerSecond 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEmitterMode 
-- @param self
-- @param #int mode
        
--------------------------------
--  How many seconds the emitter will run. -1 means 'forever' 
-- @function [parent=#ParticleSystem] getDuration 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setSourcePosition 
-- @param self
-- @param #vec2_table pos
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getEndSpinVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setBlendAdditive 
-- @param self
-- @param #bool value
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setLife 
-- @param self
-- @param #float life
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setAngleVar 
-- @param self
-- @param #float angleVar
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setRotationIsDir 
-- @param self
-- @param #bool t
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndSizeVar 
-- @param self
-- @param #float sizeVar
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setAngle 
-- @param self
-- @param #float angle
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setBatchNode 
-- @param self
-- @param #cc.ParticleBatchNode batchNode
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getTangentialAccelVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Switch between different kind of emitter modes:<br>
-- - kParticleModeGravity: uses gravity, speed, radial and tangential acceleration<br>
-- - kParticleModeRadius: uses radius movement + rotation
-- @function [parent=#ParticleSystem] getEmitterMode 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndSpinVar 
-- @param self
-- @param #float endSpinVar
        
--------------------------------
--  angle variance of each particle 
-- @function [parent=#ParticleSystem] getAngleVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartColor 
-- @param self
-- @param #color4f_table color
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getRotatePerSecondVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  end size in pixels of each particle 
-- @function [parent=#ParticleSystem] getEndSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  life, and life variation of each particle 
-- @function [parent=#ParticleSystem] getLife 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setSpeedVar 
-- @param self
-- @param #float speed
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setAutoRemoveOnFinish 
-- @param self
-- @param #bool var
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setGravity 
-- @param self
-- @param #vec2_table g
        
--------------------------------
--  should be overridden by subclasses
-- @function [parent=#ParticleSystem] postStep 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEmissionRate 
-- @param self
-- @param #float rate
        
--------------------------------
--  end color variance of each particle 
-- @function [parent=#ParticleSystem] getEndColorVar 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getRotationIsDir 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setScale 
-- @param self
-- @param #float s
        
--------------------------------
--  emission rate of the particles 
-- @function [parent=#ParticleSystem] getEmissionRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  end color and end color variation of each particle 
-- @function [parent=#ParticleSystem] getEndColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  life variance of each particle 
-- @function [parent=#ParticleSystem] getLifeVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartSizeVar 
-- @param self
-- @param #float sizeVar
        
--------------------------------
--  does the alpha value modify color 
-- @function [parent=#ParticleSystem] setOpacityModifyRGB 
-- @param self
-- @param #bool opacityModifyRGB
        
--------------------------------
--  Add a particle to the emitter
-- @function [parent=#ParticleSystem] addParticle 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getStartRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Quantity of particles that are being simulated at the moment 
-- @function [parent=#ParticleSystem] getParticleCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getStartRadiusVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#ParticleSystem] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartColorVar 
-- @param self
-- @param #color4f_table color
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setEndSpin 
-- @param self
-- @param #float endSpin
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setRadialAccel 
-- @param self
-- @param #float t
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] isAutoRemoveOnFinish 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  maximum particles of the system 
-- @function [parent=#ParticleSystem] getTotalParticles 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setStartRadiusVar 
-- @param self
-- @param #float startRadiusVar
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- In lua: local setBlendFunc(local src, local dst)<br>
-- endcode
-- @function [parent=#ParticleSystem] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getEndRadiusVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  start color variance of each particle 
-- @function [parent=#ParticleSystem] getStartColorVar 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  creates an initializes a ParticleSystem from a plist file.<br>
-- This plist files can be created manually or with Particle Designer:<br>
-- http:particledesigner.71squared.com/<br>
-- since v2.0
-- @function [parent=#ParticleSystem] create 
-- @param self
-- @param #string plistFile
-- @return ParticleSystem#ParticleSystem ret (return value: cc.ParticleSystem)
        
--------------------------------
--  create a system with a fixed number of particles
-- @function [parent=#ParticleSystem] createWithTotalParticles 
-- @param self
-- @param #int numberOfParticles
-- @return ParticleSystem#ParticleSystem ret (return value: cc.ParticleSystem)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] update 
-- @param self
-- @param #float dt
        
return nil
