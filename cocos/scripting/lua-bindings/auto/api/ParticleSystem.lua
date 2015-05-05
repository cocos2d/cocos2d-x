
--------------------------------
-- @module ParticleSystem
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
--  Gets the start size variance in pixels of each particle.<br>
-- return The start size variance in pixels of each particle.
-- @function [parent=#ParticleSystem] getStartSizeVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  Whether or not the system is full.<br>
-- return True if the system is full.
-- @function [parent=#ParticleSystem] isFull 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the batch node.<br>
-- return The batch node.
-- @function [parent=#ParticleSystem] getBatchNode 
-- @param self
-- @return ParticleBatchNode#ParticleBatchNode ret (return value: cc.ParticleBatchNode)
        
--------------------------------
--  Gets the start color of each particle.<br>
-- return The start color of each particle.
-- @function [parent=#ParticleSystem] getStartColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  Gets the particles movement type: Free or Grouped.<br>
-- since v0.8<br>
-- return The particles movement type.
-- @function [parent=#ParticleSystem] getPositionType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Sets the position variance of the emitter.<br>
-- param pos The position variance of the emitter.
-- @function [parent=#ParticleSystem] setPosVar 
-- @param self
-- @param #vec2_table pos
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the end spin of each particle.<br>
-- return The end spin of each particle.
-- @function [parent=#ParticleSystem] getEndSpin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the rotate per second variance.<br>
-- param degrees The rotate per second variance.
-- @function [parent=#ParticleSystem] setRotatePerSecondVar 
-- @param self
-- @param #float degrees
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the start spin variance of each particle.<br>
-- return The start spin variance of each particle.
-- @function [parent=#ParticleSystem] getStartSpinVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the radial acceleration variance.<br>
-- return The radial acceleration variance.
-- @function [parent=#ParticleSystem] getRadialAccelVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the end size variance in pixels of each particle.<br>
-- return The end size variance in pixels of each particle.
-- @function [parent=#ParticleSystem] getEndSizeVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the tangential acceleration.<br>
-- param t The tangential acceleration.
-- @function [parent=#ParticleSystem] setTangentialAccel 
-- @param self
-- @param #float t
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the radial acceleration.<br>
-- return The radial acceleration.
-- @function [parent=#ParticleSystem] getRadialAccel 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the start radius.<br>
-- param startRadius The start radius.
-- @function [parent=#ParticleSystem] setStartRadius 
-- @param self
-- @param #float startRadius
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the number of degrees to rotate a particle around the source pos per second.<br>
-- param degrees The number of degrees to rotate a particle around the source pos per second.
-- @function [parent=#ParticleSystem] setRotatePerSecond 
-- @param self
-- @param #float degrees
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the end size in pixels of each particle.<br>
-- param endSize The end size in pixels of each particle.
-- @function [parent=#ParticleSystem] setEndSize 
-- @param self
-- @param #float endSize
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the garvity.<br>
-- return The gravity.
-- @function [parent=#ParticleSystem] getGravity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Gets the tangential acceleration.<br>
-- return The tangential acceleration.
-- @function [parent=#ParticleSystem] getTangentialAccel 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the end radius.<br>
-- param endRadius The end radius.
-- @function [parent=#ParticleSystem] setEndRadius 
-- @param self
-- @param #float endRadius
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the speed.<br>
-- return The speed.
-- @function [parent=#ParticleSystem] getSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the angle of each particle. <br>
-- return The angle of each particle.
-- @function [parent=#ParticleSystem] getAngle 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the end color and end color variation of each particle.<br>
-- param color The end color and end color variation of each particle.
-- @function [parent=#ParticleSystem] setEndColor 
-- @param self
-- @param #color4f_table color
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the start spin of each particle.<br>
-- param spin The start spin of each particle.
-- @function [parent=#ParticleSystem] setStartSpin 
-- @param self
-- @param #float spin
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets how many seconds the emitter will run. -1 means 'forever'.<br>
-- param duration The seconds that the emitter will run. -1 means 'forever'.
-- @function [parent=#ParticleSystem] setDuration 
-- @param self
-- @param #float duration
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Initializes a system with a fixed number of particles
-- @function [parent=#ParticleSystem] initWithTotalParticles 
-- @param self
-- @param #int numberOfParticles
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the position variance of the emitter.<br>
-- return The position variance of the emitter.
-- @function [parent=#ParticleSystem] getPosVar 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Call the update mathod with no time..
-- @function [parent=#ParticleSystem] updateWithNoTime 
-- @param self
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Whether or not the particle system is blend additive.<br>
-- return True if the particle system is blend additive.
-- @function [parent=#ParticleSystem] isBlendAdditive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the speed variance.<br>
-- return The speed variance.
-- @function [parent=#ParticleSystem] getSpeedVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the particles movement type: Free or Grouped.<br>
-- since v0.8<br>
-- param type The particles movement type.
-- @function [parent=#ParticleSystem] setPositionType 
-- @param self
-- @param #int type
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Stop emitting particles. Running particles will continue to run until they die.
-- @function [parent=#ParticleSystem] stopSystem 
-- @param self
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the source position of the emitter.<br>
-- return The source position of the emitter.
-- @function [parent=#ParticleSystem] getSourcePosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Sets the life variance of each particle.<br>
-- param lifeVar The life variance of each particle.
-- @function [parent=#ParticleSystem] setLifeVar 
-- @param self
-- @param #float lifeVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the maximum particles of the system.<br>
-- param totalParticles The maximum particles of the system.
-- @function [parent=#ParticleSystem] setTotalParticles 
-- @param self
-- @param #int totalParticles
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the end color variance of each particle.<br>
-- param color The end color variance of each particle.
-- @function [parent=#ParticleSystem] setEndColorVar 
-- @param self
-- @param #color4f_table color
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the index of system in batch node array.<br>
-- return The index of system in batch node array.
-- @function [parent=#ParticleSystem] getAtlasIndex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Gets the start size in pixels of each particle.<br>
-- return The start size in pixels of each particle.
-- @function [parent=#ParticleSystem] getStartSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the start spin variance of each particle.<br>
-- param pinVar The start spin variance of each particle.
-- @function [parent=#ParticleSystem] setStartSpinVar 
-- @param self
-- @param #float pinVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Kill all living particles.
-- @function [parent=#ParticleSystem] resetSystem 
-- @param self
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the index of system in batch node array.<br>
-- param index The index of system in batch node array.
-- @function [parent=#ParticleSystem] setAtlasIndex 
-- @param self
-- @param #int index
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the tangential acceleration variance.<br>
-- param t The tangential acceleration variance.
-- @function [parent=#ParticleSystem] setTangentialAccelVar 
-- @param self
-- @param #float t
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the end radius variance.<br>
-- param endRadiusVar The end radius variance.
-- @function [parent=#ParticleSystem] setEndRadiusVar 
-- @param self
-- @param #float endRadiusVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the end radius.<br>
-- return The end radius.
-- @function [parent=#ParticleSystem] getEndRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Whether or not the particle system is active.<br>
-- return True if the particle system is active.
-- @function [parent=#ParticleSystem] isActive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the radial acceleration variance.<br>
-- param t The radial acceleration variance.
-- @function [parent=#ParticleSystem] setRadialAccelVar 
-- @param self
-- @param #float t
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the start size in pixels of each particle.<br>
-- param startSize The start size in pixels of each particle.
-- @function [parent=#ParticleSystem] setStartSize 
-- @param self
-- @param #float startSize
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the speed.<br>
-- param speed The speed.
-- @function [parent=#ParticleSystem] setSpeed 
-- @param self
-- @param #float speed
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the start spin of each particle.<br>
-- return The start spin of each particle.
-- @function [parent=#ParticleSystem] getStartSpin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the number of degrees to rotate a particle around the source pos per second.<br>
-- return The number of degrees to rotate a particle around the source pos per second.
-- @function [parent=#ParticleSystem] getRotatePerSecond 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the mode of the emitter.<br>
-- param mode The mode of the emitter.
-- @function [parent=#ParticleSystem] setEmitterMode 
-- @param self
-- @param #int mode
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets how many seconds the emitter will run. -1 means 'forever'.<br>
-- return The seconds that the emitter will run. -1 means 'forever'.
-- @function [parent=#ParticleSystem] getDuration 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the source position of the emitter.<br>
-- param pos The source position of the emitter.
-- @function [parent=#ParticleSystem] setSourcePosition 
-- @param self
-- @param #vec2_table pos
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the end spin variance of each particle.<br>
-- return The end spin variance of each particle.
-- @function [parent=#ParticleSystem] getEndSpinVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the particle system blend additive.<br>
-- param value True if the particle system is blend additive.
-- @function [parent=#ParticleSystem] setBlendAdditive 
-- @param self
-- @param #bool value
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the life of each particle.<br>
-- param life The life of each particle.
-- @function [parent=#ParticleSystem] setLife 
-- @param self
-- @param #float life
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the angle variance of each particle.<br>
-- param angleVar The angle variance of each particle.
-- @function [parent=#ParticleSystem] setAngleVar 
-- @param self
-- @param #float angleVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the rotation of each particle to its direction.<br>
-- param t True if the rotation is the direction.
-- @function [parent=#ParticleSystem] setRotationIsDir 
-- @param self
-- @param #bool t
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the end size variance in pixels of each particle.<br>
-- param sizeVar The end size variance in pixels of each particle.
-- @function [parent=#ParticleSystem] setEndSizeVar 
-- @param self
-- @param #float sizeVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the angle of each particle.<br>
-- param angle The angle of each particle.
-- @function [parent=#ParticleSystem] setAngle 
-- @param self
-- @param #float angle
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the batch node.<br>
-- param batchNode The batch node.
-- @function [parent=#ParticleSystem] setBatchNode 
-- @param self
-- @param #cc.ParticleBatchNode batchNode
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the tangential acceleration variance.<br>
-- return The tangential acceleration variance.
-- @function [parent=#ParticleSystem] getTangentialAccelVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Switch between different kind of emitter modes:<br>
-- - kParticleModeGravity: uses gravity, speed, radial and tangential acceleration.<br>
-- - kParticleModeRadius: uses radius movement + rotation.<br>
-- return The mode of the emitter.
-- @function [parent=#ParticleSystem] getEmitterMode 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Sets the end spin variance of each particle.<br>
-- param endSpinVar The end spin variance of each particle.
-- @function [parent=#ParticleSystem] setEndSpinVar 
-- @param self
-- @param #float endSpinVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  initializes a ParticleSystem from a plist file.<br>
-- This plist files can be created manually or with Particle Designer:<br>
-- http:particledesigner.71squared.com/<br>
-- since v0.99.3
-- @function [parent=#ParticleSystem] initWithFile 
-- @param self
-- @param #string plistFile
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the angle variance of each particle.<br>
-- return The angle variance of each particle.
-- @function [parent=#ParticleSystem] getAngleVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the start color of each particle.<br>
-- param color The start color of each particle.
-- @function [parent=#ParticleSystem] setStartColor 
-- @param self
-- @param #color4f_table color
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the rotate per second variance.<br>
-- return The rotate per second variance.
-- @function [parent=#ParticleSystem] getRotatePerSecondVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the end size in pixels of each particle.<br>
-- return The end size in pixels of each particle.
-- @function [parent=#ParticleSystem] getEndSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the life of each particle.<br>
-- return The life of each particle.
-- @function [parent=#ParticleSystem] getLife 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the speed variance.<br>
-- param speed The speed variance.
-- @function [parent=#ParticleSystem] setSpeedVar 
-- @param self
-- @param #float speed
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Set the particle system auto removed it self on finish.<br>
-- param var True if the particle system removed self on finish.
-- @function [parent=#ParticleSystem] setAutoRemoveOnFinish 
-- @param self
-- @param #bool var
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the gravity.<br>
-- param g The gravity.
-- @function [parent=#ParticleSystem] setGravity 
-- @param self
-- @param #vec2_table g
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Update the VBO verts buffer which does not use batch node,<br>
-- should be overridden by subclasses. 
-- @function [parent=#ParticleSystem] postStep 
-- @param self
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the emission rate of the particles.<br>
-- param rate The emission rate of the particles.
-- @function [parent=#ParticleSystem] setEmissionRate 
-- @param self
-- @param #float rate
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the end color variance of each particle.<br>
-- return The end color variance of each particle.
-- @function [parent=#ParticleSystem] getEndColorVar 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  Whether or not the rotation of each particle to its direction.<br>
-- return True if the rotation is the direction.
-- @function [parent=#ParticleSystem] getRotationIsDir 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the emission rate of the particles.<br>
-- return The emission rate of the particles.
-- @function [parent=#ParticleSystem] getEmissionRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the end color and end color variation of each particle.<br>
-- return The end color and end color variation of each particle.
-- @function [parent=#ParticleSystem] getEndColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  Gets the life variance of each particle.<br>
-- return The life variance of each particle.
-- @function [parent=#ParticleSystem] getLifeVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the start size variance in pixels of each particle.<br>
-- param sizeVar The start size variance in pixels of each particle.
-- @function [parent=#ParticleSystem] setStartSizeVar 
-- @param self
-- @param #float sizeVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Add a particle to the emitter.<br>
-- return True if add success.<br>
-- js ctor
-- @function [parent=#ParticleSystem] addParticle 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the start radius.<br>
-- return The start radius.
-- @function [parent=#ParticleSystem] getStartRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the Quantity of particles that are being simulated at the moment.<br>
-- return The Quantity of particles that are being simulated at the moment.
-- @function [parent=#ParticleSystem] getParticleCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  Gets the start radius variance.<br>
-- return The start radius variance.
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
--  Sets the start color variance of each particle.<br>
-- param color The start color variance of each particle.
-- @function [parent=#ParticleSystem] setStartColorVar 
-- @param self
-- @param #color4f_table color
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the end spin of each particle.<br>
-- param endSpin The end spin of each particle.
-- @function [parent=#ParticleSystem] setEndSpin 
-- @param self
-- @param #float endSpin
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Sets the radial acceleration.<br>
-- param t The radial acceleration.
-- @function [parent=#ParticleSystem] setRadialAccel 
-- @param self
-- @param #float t
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
-- @overload self, map_table, string         
-- @overload self, map_table         
-- @function [parent=#ParticleSystem] initWithDictionary
-- @param self
-- @param #map_table dictionary
-- @param #string dirname
-- @return bool#bool ret (return value: bool)

--------------------------------
--  Whether or not the particle system removed self on finish.<br>
-- return True if the particle system removed self on finish.
-- @function [parent=#ParticleSystem] isAutoRemoveOnFinish 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the maximum particles of the system.<br>
-- return The maximum particles of the system.
-- @function [parent=#ParticleSystem] getTotalParticles 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Sets the start radius variance.<br>
-- param startRadiusVar The start radius variance.
-- @function [parent=#ParticleSystem] setStartRadiusVar 
-- @param self
-- @param #float startRadiusVar
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- In lua: local setBlendFunc(local src, local dst)<br>
-- endcode
-- @function [parent=#ParticleSystem] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  Gets the end radius variance.<br>
-- return The end radius variance.
-- @function [parent=#ParticleSystem] getEndRadiusVar 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the start color variance of each particle.<br>
-- return The start color variance of each particle.
-- @function [parent=#ParticleSystem] getStartColorVar 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  Creates an initializes a ParticleSystem from a plist file.<br>
-- This plist files can be created manually or with Particle Designer:<br>
-- http:particledesigner.71squared.com/<br>
-- since v2.0<br>
-- param plistFile Particle plist file name.<br>
-- return An autoreleased ParticleSystem object.
-- @function [parent=#ParticleSystem] create 
-- @param self
-- @param #string plistFile
-- @return ParticleSystem#ParticleSystem ret (return value: cc.ParticleSystem)
        
--------------------------------
--  Create a system with a fixed number of particles.<br>
-- param numberOfParticles A given number of particles.<br>
-- return An autoreleased ParticleSystemQuad object.<br>
-- js NA
-- @function [parent=#ParticleSystem] createWithTotalParticles 
-- @param self
-- @param #int numberOfParticles
-- @return ParticleSystem#ParticleSystem ret (return value: cc.ParticleSystem)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setScaleY 
-- @param self
-- @param #float newScaleY
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setScaleX 
-- @param self
-- @param #float newScaleX
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  does the alpha value modify color 
-- @function [parent=#ParticleSystem] setOpacityModifyRGB 
-- @param self
-- @param #bool opacityModifyRGB
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setScale 
-- @param self
-- @param #float s
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] update 
-- @param self
-- @param #float dt
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
--  initializes a ParticleSystem
-- @function [parent=#ParticleSystem] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystem] setRotation 
-- @param self
-- @param #float newRotation
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
--------------------------------
-- js ctor
-- @function [parent=#ParticleSystem] ParticleSystem 
-- @param self
-- @return ParticleSystem#ParticleSystem self (return value: cc.ParticleSystem)
        
return nil
