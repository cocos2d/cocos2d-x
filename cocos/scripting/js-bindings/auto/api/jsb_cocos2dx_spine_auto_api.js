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
 * @method getDebugSlotsEnabled
 * @return {bool}
 */
getDebugSlotsEnabled : function (
)
{
    return false;
},

/**
 * @method setAttachment
* @param {String|String} str
* @param {char|String} char
* @return {bool|bool}
*/
setAttachment : function(
str,
str 
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
 * @method initWithData
 * @param {spSkeletonData} arg0
 * @param {bool} arg1
 */
initWithData : function (
spskeletondata, 
bool 
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
 * @method setSlotsToSetupPose
 */
setSlotsToSetupPose : function (
)
{
},

/**
 * @method setToSetupPose
 */
setToSetupPose : function (
)
{
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
 * @method updateWorldTransform
 */
updateWorldTransform : function (
)
{
},

/**
 * @method initialize
 */
initialize : function (
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
 * @method getDebugBonesEnabled
 * @return {bool}
 */
getDebugBonesEnabled : function (
)
{
    return false;
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
 * @method initWithFile
* @param {String|String} str
* @param {String|spAtlas} str
* @param {float|float} float
*/
initWithFile : function(
str,
spatlas,
float 
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
 * @method setSkin
* @param {char|String} char
* @return {bool|bool}
*/
setSkin : function(
str 
)
{
    return false;
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
 * @method drawDebug
 * @param {cc.Renderer} arg0
 * @param {mat4_object} arg1
 * @param {unsigned int} arg2
 */
drawDebug : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method createWithFile
* @param {String|String} str
* @param {spAtlas|String} spatlas
* @param {float|float} float
* @return {sp.SkeletonRenderer|sp.SkeletonRenderer|sp.SkeletonRenderer}
*/
createWithFile : function(
str,
str,
float 
)
{
    return sp.SkeletonRenderer;
},

/**
 * @method SkeletonRenderer
 * @constructor
* @param {spSkeletonData|String|String} spskeletondata
* @param {bool|spAtlas|String} bool
* @param {float|float} float
*/
SkeletonRenderer : function(
str,
str,
float 
)
{
},

};

/**
 * @class SkeletonAnimation
 */
sp.SkeletonAnimation = {

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
 * @method findAnimation
 * @param {String} arg0
 * @return {spAnimation}
 */
findAnimation : function (
str 
)
{
    return spAnimation;
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
 * @method setEndListener
 * @param {function} arg0
 */
setEndListener : function (
func 
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
 * @method getState
 * @return {spAnimationState}
 */
getState : function (
)
{
    return spAnimationState;
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
 * @method setEventListener
 * @param {function} arg0
 */
setEventListener : function (
func 
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
 * @method clearTrack
 */
clearTrack : function (
)
{
},

/**
 * @method initialize
 */
initialize : function (
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
 * @method clearTracks
 */
clearTracks : function (
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
 * @method setStartListener
 * @param {function} arg0
 */
setStartListener : function (
func 
)
{
},

/**
 * @method createWithFile
* @param {String|String} str
* @param {spAtlas|String} spatlas
* @param {float|float} float
* @return {sp.SkeletonAnimation|sp.SkeletonAnimation|sp.SkeletonAnimation}
*/
createWithFile : function(
str,
str,
float 
)
{
    return sp.SkeletonAnimation;
},

/**
 * @method SkeletonAnimation
 * @constructor
* @param {spSkeletonData|String|String} spskeletondata
* @param {bool|spAtlas|String} bool
* @param {float|float} float
*/
SkeletonAnimation : function(
str,
str,
float 
)
{
},

};
