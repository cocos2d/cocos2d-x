/**
 * @module cocos2dx_audioengine
 */
var jsb = jsb || {};

/**
 * @class AudioProfile
 */
jsb.AudioProfile = {

/**
 * @method AudioProfile
 * @constructor
 */
AudioProfile : function (
)
{
},

};

/**
 * @class AudioEngine
 */
jsb.AudioEngine = {

/**
 * @method lazyInit
 * @return {bool}
 */
lazyInit : function (
)
{
    return false;
},

/**
 * @method setCurrentTime
 * @param {int} arg0
 * @param {float} arg1
 * @return {bool}
 */
setCurrentTime : function (
int, 
float 
)
{
    return false;
},

/**
 * @method getVolume
 * @param {int} arg0
 * @return {float}
 */
getVolume : function (
int 
)
{
    return 0;
},

/**
 * @method uncache
 * @param {String} arg0
 */
uncache : function (
str 
)
{
},

/**
 * @method resumeAll
 */
resumeAll : function (
)
{
},

/**
 * @method stopAll
 */
stopAll : function (
)
{
},

/**
 * @method pause
 * @param {int} arg0
 */
pause : function (
int 
)
{
},

/**
 * @method end
 */
end : function (
)
{
},

/**
 * @method getMaxAudioInstance
 * @return {int}
 */
getMaxAudioInstance : function (
)
{
    return 0;
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
 * @method getCurrentTime
 * @param {int} arg0
 * @return {float}
 */
getCurrentTime : function (
int 
)
{
    return 0;
},

/**
 * @method setMaxAudioInstance
 * @param {int} arg0
 * @return {bool}
 */
setMaxAudioInstance : function (
int 
)
{
    return false;
},

/**
 * @method isLoop
 * @param {int} arg0
 * @return {bool}
 */
isLoop : function (
int 
)
{
    return false;
},

/**
 * @method pauseAll
 */
pauseAll : function (
)
{
},

/**
 * @method uncacheAll
 */
uncacheAll : function (
)
{
},

/**
 * @method setVolume
 * @param {int} arg0
 * @param {float} arg1
 */
setVolume : function (
int, 
float 
)
{
},

/**
 * @method preload
* @param {String|String} str
* @param {function} func
*/
preload : function(
str,
func 
)
{
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
 * @method play2d
 * @param {String} arg0
 * @param {bool} arg1
 * @param {float} arg2
 * @param {cc.experimental::AudioProfile} arg3
 * @return {int}
 */
play2d : function (
str, 
bool, 
float, 
audioprofile 
)
{
    return 0;
},

/**
 * @method getState
 * @param {int} arg0
 * @return {cc.experimental::AudioEngine::AudioState}
 */
getState : function (
int 
)
{
    return 0;
},

/**
 * @method resume
 * @param {int} arg0
 */
resume : function (
int 
)
{
},

/**
 * @method stop
 * @param {int} arg0
 */
stop : function (
int 
)
{
},

/**
 * @method getDuration
 * @param {int} arg0
 * @return {float}
 */
getDuration : function (
int 
)
{
    return 0;
},

/**
 * @method setLoop
 * @param {int} arg0
 * @param {bool} arg1
 */
setLoop : function (
int, 
bool 
)
{
},

/**
 * @method getDefaultProfile
 * @return {cc.experimental::AudioProfile}
 */
getDefaultProfile : function (
)
{
    return cc.experimental::AudioProfile;
},

/**
 * @method setFinishCallback
 * @param {int} arg0
 * @param {function} arg1
 */
setFinishCallback : function (
int, 
func 
)
{
},

/**
 * @method getProfile
* @param {String|int} str
* @return {cc.experimental::AudioProfile|cc.experimental::AudioProfile}
*/
getProfile : function(
int 
)
{
    return cc.experimental::AudioProfile;
},

/**
 * @method getPlayingAudioCount
 * @return {int}
 */
getPlayingAudioCount : function (
)
{
    return 0;
},

};
