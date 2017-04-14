/**
 * @module cocos2dx_network
 */
var jsb = jsb || {};

/**
 * @class Downloader
 */
jsb.Downloader = {

/**
 * @method setOnTaskError
 * @param {function} arg0
 */
setOnTaskError : function (
func 
)
{
},

/**
 * @method setOnTaskProgress
 * @param {function} arg0
 */
setOnTaskProgress : function (
func 
)
{
},

/**
 * @method createDownloadFileTask
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @return {std::shared_ptr<cc.network::DownloadTask>}
 */
createDownloadFileTask : function (
str, 
str, 
str 
)
{
    return std::shared_ptr<cocos2d::network::DownloadTask>;
},

/**
 * @method setOnFileTaskSuccess
 * @param {function} arg0
 */
setOnFileTaskSuccess : function (
func 
)
{
},

/**
 * @method Downloader
 * @constructor
* @param {cc.network::DownloaderHints} downloaderhints
*/
Downloader : function(
downloaderhints 
)
{
},

};
