/**
 * @module cocos2dx_spine
 */
var sp = sp || {};

/**
 * @class SkeletonRenderer
 */
sp.Skeleton = {

/**
 * @method setTimeScale
 * @param {float} arg0
 */
setTimeScale : function (
float 
)
{
},

/**
 * @method isOpacityModifyRGB
 * @return {bool}
 */
isOpacityModifyRGB : function (
)
{
    return false;
},

/**
 * @method drawSkeleton
 * @param {mat4_object} arg0
 * @param {unsigned int} arg1
 */
drawSkeleton : function (
mat4, 
int 
)
{
},

/**
 * @method setDebugSlotsEnabled
 * @param {bool} arg0
 */
setDebugSlotsEnabled : function (
bool 
)
{
},

/**
 * @method getDebugSlotsEnabled
 * @return {bool}
 */
getDebugSlotsEnabled : function (
)
{
    return false;
},

/**
 * @method setBonesToSetupPose
 */
setBonesToSetupPose : function (
)
{
},

/**
 * @method setSlotsToSetupPose
 */
setSlotsToSetupPose : function (
)
{
},

/**
 * @method setAttachment
 * @param {String} arg0
 * @param {String} arg1
 * @return {bool}
 */
setAttachment : function (
str, 
str 
)
{
    return false;
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
 * @method setSkin
 * @param {String} arg0
 * @return {bool}
 */
setSkin : function (
str 
)
{
    return false;
},

/**
 * @method setToSetupPose
 */
setToSetupPose : function (
)
{
},

/**
 * @method updateWorldTransform
 */
updateWorldTransform : function (
)
{
},

/**
 * @method setOpacityModifyRGB
 * @param {bool} arg0
 */
setOpacityModifyRGB : function (
bool 
)
{
},

/**
 * @method setDebugBonesEnabled
 * @param {bool} arg0
 */
setDebugBonesEnabled : function (
bool 
)
{
},

/**
 * @method getSkeleton
 * @return {spSkeleton}
 */
getSkeleton : function (
)
{
    return spSkeleton;
},

/**
 * @method getDebugBonesEnabled
 * @return {bool}
 */
getDebugBonesEnabled : function (
)
{
    return false;
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
 * @method getTimeScale
 * @return {float}
 */
getTimeScale : function (
)
{
    return 0;
},

/**
 * @method createWithFile
* @param {String|String} str
* @param {String|spAtlas} str
* @param {float|float} float
* @return {sp.SkeletonRenderer|sp.SkeletonRenderer}
*/
createWithFile : function(
str,
spatlas,
float 
)
{
    return sp.SkeletonRenderer;
},

};

/**
 * @class SkeletonAnimation
 */
sp.SkeletonAnimation = {

/**
 * @method setStartListener
 * @param {function} arg0
 */
setStartListener : function (
func 
)
{
},

/**
 * @method setTrackEventListener
 * @param {spTrackEntry} arg0
 * @param {function} arg1
 */
setTrackEventListener : function (
sptrackentry, 
func 
)
{
},

/**
 * @method getState
 * @return {spAnimationState}
 */
getState : function (
)
{
    return spAnimationState;
},

/**
 * @method setTrackCompleteListener
 * @param {spTrackEntry} arg0
 * @param {function} arg1
 */
setTrackCompleteListener : function (
sptrackentry, 
func 
)
{
},

/**
 * @method onTrackEntryEvent
 * @param {int} arg0
 * @param {spEventType} arg1
 * @param {spEvent} arg2
 * @param {int} arg3
 */
onTrackEntryEvent : function (
int, 
speventtype, 
spevent, 
int 
)
{
},

/**
 * @method setTrackStartListener
 * @param {spTrackEntry} arg0
 * @param {function} arg1
 */
setTrackStartListener : function (
sptrackentry, 
func 
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method setCompleteListener
 * @param {function} arg0
 */
setCompleteListener : function (
func 
)
{
},

/**
 * @method setTrackEndListener
 * @param {spTrackEntry} arg0
 * @param {function} arg1
 */
setTrackEndListener : function (
sptrackentry, 
func 
)
{
},

/**
 * @method setEventListener
 * @param {function} arg0
 */
setEventListener : function (
func 
)
{
},

/**
 * @method setMix
 * @param {String} arg0
 * @param {String} arg1
 * @param {float} arg2
 */
setMix : function (
str, 
str, 
float 
)
{
},

/**
 * @method setEndListener
 * @param {function} arg0
 */
setEndListener : function (
func 
)
{
},

/**
 * @method clearTracks
 */
clearTracks : function (
)
{
},

/**
 * @method clearTrack
 */
clearTrack : function (
)
{
},

/**
 * @method onAnimationStateEvent
 * @param {int} arg0
 * @param {spEventType} arg1
 * @param {spEvent} arg2
 * @param {int} arg3
 */
onAnimationStateEvent : function (
int, 
speventtype, 
spevent, 
int 
)
{
},

/**
 * @method createWithFile
* @param {String|String} str
* @param {String|spAtlas} str
* @param {float|float} float
* @return {sp.SkeletonAnimation|sp.SkeletonAnimation}
*/
createWithFile : function(
str,
spatlas,
float 
)
{
    return sp.SkeletonAnimation;
},

};
