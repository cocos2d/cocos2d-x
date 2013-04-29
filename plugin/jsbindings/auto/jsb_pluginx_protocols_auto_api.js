/**
 * @module pluginx_protocols
 */
var plugin = plugin || {};

/**
 * @class PluginProtocol
 */
plugin.PluginProtocol = {

/**
 * @method setUserData
 * @param {void*}
 */
setUserData : function () {},

/**
 * @method getUserData
 * @return A value converted from C/C++ "void*"
 */
getUserData : function () {},

/**
 * @method getPluginName
 * @return A value converted from C/C++ "const char*"
 */
getPluginName : function () {},

/**
 * @method getPluginVersion
 * @return A value converted from C/C++ "const char*"
 */
getPluginVersion : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setDebugMode
 * @param {bool}
 */
setDebugMode : function () {},

};

/**
 * @class PluginManager
 */
plugin.PluginManager = {

/**
 * @method unloadPlugin
 * @param {const char*}
 */
unloadPlugin : function () {},

/**
 * @method loadPlugin
 * @return A value converted from C/C++ "cocos2d::plugin::PluginProtocol*"
 * @param {const char*}
 */
loadPlugin : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocos2d::plugin::PluginManager*"
 */
getInstance : function () {},

};

/**
 * @class ProtocolAnalytics
 */
plugin.ProtocolAnalytics = {

/**
 * @method logTimedEventBegin
 * @param {const char*}
 */
logTimedEventBegin : function () {},

/**
 * @method logError
 * @param {const char*}
 * @param {const char*}
 */
logError : function () {},

/**
 * @method setCaptureUncaughtException
 * @param {bool}
 */
setCaptureUncaughtException : function () {},

/**
 * @method getPluginName
 * @return A value converted from C/C++ "const char*"
 */
getPluginName : function () {},

/**
 * @method getPluginVersion
 * @return A value converted from C/C++ "const char*"
 */
getPluginVersion : function () {},

/**
 * @method logEvent
 * @param {const char*}
 * @param {LogEventParamMap*}
 */
logEvent : function () {},

/**
 * @method setSessionContinueMillis
 * @param {long}
 */
setSessionContinueMillis : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method startSession
 * @param {const char*}
 */
startSession : function () {},

/**
 * @method stopSession
 */
stopSession : function () {},

/**
 * @method logTimedEventEnd
 * @param {const char*}
 */
logTimedEventEnd : function () {},

/**
 * @method getSDKVersion
 * @return A value converted from C/C++ "const char*"
 */
getSDKVersion : function () {},

/**
 * @method setDebugMode
 * @param {bool}
 */
setDebugMode : function () {},

};

/**
 * @class ProtocolIAP
 */
plugin.ProtocolIAP = {

/**
 * @method getPluginVersion
 * @return A value converted from C/C++ "const char*"
 */
getPluginVersion : function () {},

/**
 * @method payForProduct
 * @param {TProductInfo}
 */
payForProduct : function () {},

/**
 * @method configDeveloperInfo
 * @param {TIAPDeveloperInfo}
 */
configDeveloperInfo : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method getPluginName
 * @return A value converted from C/C++ "const char*"
 */
getPluginName : function () {},

/**
 * @method onPayResult
 * @param {cocos2d::plugin::PayResultCode}
 * @param {const char*}
 */
onPayResult : function () {},

/**
 * @method getSDKVersion
 * @return A value converted from C/C++ "const char*"
 */
getSDKVersion : function () {},

/**
 * @method setDebugMode
 * @param {bool}
 */
setDebugMode : function () {},

};

/**
 * @class ProtocolAds
 */
plugin.ProtocolAds = {

/**
 * @method showAds
 * @param {cocos2d::plugin::ProtocolAds::AdsType}
 * @param {int}
 * @param {cocos2d::plugin::ProtocolAds::AdsPos}
 */
showAds : function () {},

/**
 * @method hideAds
 * @param {cocos2d::plugin::ProtocolAds::AdsType}
 */
hideAds : function () {},

/**
 * @method getPluginVersion
 * @return A value converted from C/C++ "const char*"
 */
getPluginVersion : function () {},

/**
 * @method getPluginName
 * @return A value converted from C/C++ "const char*"
 */
getPluginName : function () {},

/**
 * @method onAdsResult
 * @param {cocos2d::plugin::AdsResultCode}
 * @param {const char*}
 */
onAdsResult : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method spendPoints
 * @param {int}
 */
spendPoints : function () {},

/**
 * @method configDeveloperInfo
 * @param {TAdsDeveloperInfo}
 */
configDeveloperInfo : function () {},

/**
 * @method onPlayerGetPoints
 * @param {int}
 */
onPlayerGetPoints : function () {},

/**
 * @method getSDKVersion
 * @return A value converted from C/C++ "const char*"
 */
getSDKVersion : function () {},

/**
 * @method setDebugMode
 * @param {bool}
 */
setDebugMode : function () {},

};

/**
 * @class ProtocolSocial
 */
plugin.ProtocolSocial = {

/**
 * @method getPluginName
 * @return A value converted from C/C++ "const char*"
 */
getPluginName : function () {},

/**
 * @method onShareResult
 * @param {cocos2d::plugin::ShareResultCode}
 * @param {const char*}
 */
onShareResult : function () {},

/**
 * @method getPluginVersion
 * @return A value converted from C/C++ "const char*"
 */
getPluginVersion : function () {},

/**
 * @method share
 * @param {TShareInfo}
 */
share : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method configDeveloperInfo
 * @param {TSocialDeveloperInfo}
 */
configDeveloperInfo : function () {},

/**
 * @method getSDKVersion
 * @return A value converted from C/C++ "const char*"
 */
getSDKVersion : function () {},

/**
 * @method setDebugMode
 * @param {bool}
 */
setDebugMode : function () {},

/**
 * @method setResultListener
 * @param {cocos2d::plugin::ShareResultListener*}
 */
setResultListener : function () {},

};
