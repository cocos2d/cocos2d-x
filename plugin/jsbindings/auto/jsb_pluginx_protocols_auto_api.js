/**
 * @module pluginx_protocols
 */
var plugin = plugin || {};

/**
 * @class PluginProtocol
 */
plugin.PluginProtocol = {

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
 * @method setSessionContinueMillis
 * @param {long}
 */
setSessionContinueMillis : function () {},

/**
 * @method logEvent
 * @param {const char*}
 * @param {LogEventParamMap*}
 */
logEvent : function () {},

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

};

/**
 * @class ProtocolIAP
 */
plugin.ProtocolIAP = {

/**
 * @method payForProduct
 * @param {TProductInfo}
 */
payForProduct : function () {},

/**
 * @method onPayResult
 * @param {cocos2d::plugin::PayResultCode}
 * @param {const char*}
 */
onPayResult : function () {},

/**
 * @method configDeveloperInfo
 * @param {TIAPDeveloperInfo}
 */
configDeveloperInfo : function () {},

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
 * @method configDeveloperInfo
 * @param {TAdsDeveloperInfo}
 */
configDeveloperInfo : function () {},

/**
 * @method spendPoints
 * @param {int}
 */
spendPoints : function () {},

/**
 * @method onAdsResult
 * @param {cocos2d::plugin::AdsResultCode}
 * @param {const char*}
 */
onAdsResult : function () {},

/**
 * @method onPlayerGetPoints
 * @param {int}
 */
onPlayerGetPoints : function () {},

};

/**
 * @class ProtocolSocial
 */
plugin.ProtocolSocial = {

/**
 * @method onShareResult
 * @param {cocos2d::plugin::ShareResultCode}
 * @param {const char*}
 */
onShareResult : function () {},

/**
 * @method share
 * @param {TShareInfo}
 */
share : function () {},

/**
 * @method configDeveloperInfo
 * @param {TSocialDeveloperInfo}
 */
configDeveloperInfo : function () {},

};
