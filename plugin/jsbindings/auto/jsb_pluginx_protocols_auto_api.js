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
 * @return A value converted from C/C++ "std::string"
 */
getPluginVersion : function () {},

/**
 * @method getSDKVersion
 * @return A value converted from C/C++ "std::string"
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
 * @param {TAdsInfo}
 * @param {cocos2d::plugin::ProtocolAds::AdsPos}
 */
showAds : function () {},

/**
 * @method hideAds
 * @param {TAdsInfo}
 */
hideAds : function () {},

/**
 * @method queryPoints
 */
queryPoints : function () {},

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
 * @method getAdsListener
 * @return A value converted from C/C++ "cocos2d::plugin::AdsListener*"
 */
getAdsListener : function () {},

};

/**
 * @class ProtocolShare
 */
plugin.ProtocolShare = {

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
 * @param {TShareDeveloperInfo}
 */
configDeveloperInfo : function () {},

};

/**
 * @class ProtocolSocial
 */
plugin.ProtocolSocial = {

/**
 * @method showLeaderboard
 * @param {const char*}
 */
showLeaderboard : function () {},

/**
 * @method showAchievements
 */
showAchievements : function () {},

/**
 * @method submitScore
 * @param {const char*}
 * @param {long}
 */
submitScore : function () {},

/**
 * @method configDeveloperInfo
 * @param {TSocialDeveloperInfo}
 */
configDeveloperInfo : function () {},

/**
 * @method unlockAchievement
 * @param {TAchievementInfo}
 */
unlockAchievement : function () {},

};

/**
 * @class ProtocolUser
 */
plugin.ProtocolUser = {

/**
 * @method isLogined
 * @return A value converted from C/C++ "bool"
 */
isLogined : function () {},

/**
 * @method logout
 */
logout : function () {},

/**
 * @method configDeveloperInfo
 * @param {TUserDeveloperInfo}
 */
configDeveloperInfo : function () {},

/**
 * @method login
 */
login : function () {},

/**
 * @method getSessionID
 * @return A value converted from C/C++ "std::string"
 */
getSessionID : function () {},

};
