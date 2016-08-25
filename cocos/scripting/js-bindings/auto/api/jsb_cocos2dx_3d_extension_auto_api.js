/**
 * @module cocos2dx_3d_extension
 */
var jsb = jsb || {};

/**
 * @class ParticleSystem3D
 */
jsb.ParticleSystem3D = {

/**
 * @method resumeParticleSystem
 */
resumeParticleSystem : function (
)
{
},

/**
 * @method startParticleSystem
 */
startParticleSystem : function (
)
{
},

/**
 * @method isEnabled
 * @return {bool}
 */
isEnabled : function (
)
{
    return false;
},

/**
 * @method getRender
 * @return {cc.Particle3DRender}
 */
getRender : function (
)
{
    return cc.Particle3DRender;
},

/**
 * @method isKeepLocal
 * @return {bool}
 */
isKeepLocal : function (
)
{
    return false;
},

/**
 * @method setEnabled
 * @param {bool} arg0
 */
setEnabled : function (
bool 
)
{
},

/**
 * @method getParticleQuota
 * @return {unsigned int}
 */
getParticleQuota : function (
)
{
    return 0;
},

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method pauseParticleSystem
 */
pauseParticleSystem : function (
)
{
},

/**
 * @method getState
 * @return {cc.ParticleSystem3D::State}
 */
getState : function (
)
{
    return 0;
},

/**
 * @method getAliveParticleCount
 * @return {int}
 */
getAliveParticleCount : function (
)
{
    return 0;
},

/**
 * @method setParticleQuota
 * @param {unsigned int} arg0
 */
setParticleQuota : function (
int 
)
{
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method stopParticleSystem
 */
stopParticleSystem : function (
)
{
},

/**
 * @method setKeepLocal
 * @param {bool} arg0
 */
setKeepLocal : function (
bool 
)
{
},

/**
 * @method ParticleSystem3D
 * @constructor
 */
ParticleSystem3D : function (
)
{
},

};

/**
 * @class PUParticleSystem3D
 */
jsb.PUParticleSystem3D = {

/**
 * @method initWithFilePath
 * @param {String} arg0
 * @return {bool}
 */
initWithFilePath : function (
str 
)
{
    return false;
},

/**
 * @method getParticleSystemScaleVelocity
 * @return {float}
 */
getParticleSystemScaleVelocity : function (
)
{
    return 0;
},

/**
 * @method setEmittedSystemQuota
 * @param {unsigned int} arg0
 */
setEmittedSystemQuota : function (
int 
)
{
},

/**
 * @method getDefaultDepth
 * @return {float}
 */
getDefaultDepth : function (
)
{
    return 0;
},

/**
 * @method getEmittedSystemQuota
 * @return {unsigned int}
 */
getEmittedSystemQuota : function (
)
{
    return 0;
},

/**
 * @method initWithFilePathAndMaterialPath
 * @param {String} arg0
 * @param {String} arg1
 * @return {bool}
 */
initWithFilePathAndMaterialPath : function (
str, 
str 
)
{
    return false;
},

/**
 * @method clearAllParticles
 */
clearAllParticles : function (
)
{
},

/**
 * @method getMaterialName
 * @return {String}
 */
getMaterialName : function (
)
{
    return ;
},

/**
 * @method calulateRotationOffset
 */
calulateRotationOffset : function (
)
{
},

/**
 * @method getMaxVelocity
 * @return {float}
 */
getMaxVelocity : function (
)
{
    return 0;
},

/**
 * @method forceUpdate
 * @param {float} arg0
 */
forceUpdate : function (
float 
)
{
},

/**
 * @method getTimeElapsedSinceStart
 * @return {float}
 */
getTimeElapsedSinceStart : function (
)
{
    return 0;
},

/**
 * @method getEmittedEmitterQuota
 * @return {unsigned int}
 */
getEmittedEmitterQuota : function (
)
{
    return 0;
},

/**
 * @method isMarkedForEmission
 * @return {bool}
 */
isMarkedForEmission : function (
)
{
    return false;
},

/**
 * @method getDefaultWidth
 * @return {float}
 */
getDefaultWidth : function (
)
{
    return 0;
},

/**
 * @method setEmittedEmitterQuota
 * @param {unsigned int} arg0
 */
setEmittedEmitterQuota : function (
int 
)
{
},

/**
 * @method setMarkedForEmission
 * @param {bool} arg0
 */
setMarkedForEmission : function (
bool 
)
{
},

/**
 * @method clone
 * @return {cc.PUParticleSystem3D}
 */
clone : function (
)
{
    return cc.PUParticleSystem3D;
},

/**
 * @method setDefaultWidth
 * @param {float} arg0
 */
setDefaultWidth : function (
float 
)
{
},

/**
 * @method copyAttributesTo
 * @param {cc.PUParticleSystem3D} arg0
 */
copyAttributesTo : function (
puparticlesystem3d 
)
{
},

/**
 * @method setMaterialName
 * @param {String} arg0
 */
setMaterialName : function (
str 
)
{
},

/**
 * @method getParentParticleSystem
 * @return {cc.PUParticleSystem3D}
 */
getParentParticleSystem : function (
)
{
    return cc.PUParticleSystem3D;
},

/**
 * @method setMaxVelocity
 * @param {float} arg0
 */
setMaxVelocity : function (
float 
)
{
},

/**
 * @method getDefaultHeight
 * @return {float}
 */
getDefaultHeight : function (
)
{
    return 0;
},

/**
 * @method getDerivedPosition
 * @return {vec3_object}
 */
getDerivedPosition : function (
)
{
    return cc.Vec3;
},

/**
 * @method rotationOffset
 * @param {vec3_object} arg0
 */
rotationOffset : function (
vec3 
)
{
},

/**
 * @method getDerivedOrientation
 * @return {cc.Quaternion}
 */
getDerivedOrientation : function (
)
{
    return cc.Quaternion;
},

/**
 * @method removeAllEmitter
 */
removeAllEmitter : function (
)
{
},

/**
 * @method setParticleSystemScaleVelocity
 * @param {float} arg0
 */
setParticleSystemScaleVelocity : function (
float 
)
{
},

/**
 * @method getDerivedScale
 * @return {vec3_object}
 */
getDerivedScale : function (
)
{
    return cc.Vec3;
},

/**
 * @method setDefaultHeight
 * @param {float} arg0
 */
setDefaultHeight : function (
float 
)
{
},

/**
 * @method removeAllListener
 */
removeAllListener : function (
)
{
},

/**
 * @method initSystem
 * @param {String} arg0
 * @return {bool}
 */
initSystem : function (
str 
)
{
    return false;
},

/**
 * @method setDefaultDepth
 * @param {float} arg0
 */
setDefaultDepth : function (
float 
)
{
},

/**
 * @method create
* @param {String|String} str
* @param {String} str
* @return {cc.PUParticleSystem3D|cc.PUParticleSystem3D|cc.PUParticleSystem3D}
*/
create : function(
str,
str 
)
{
    return cc.PUParticleSystem3D;
},

/**
 * @method PUParticleSystem3D
 * @constructor
 */
PUParticleSystem3D : function (
)
{
},

};
