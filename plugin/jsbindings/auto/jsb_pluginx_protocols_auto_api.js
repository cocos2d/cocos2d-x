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
 * @method initDeveloperInfo
 * @param {TDeveloperInfo}
 */
initDeveloperInfo : function () {},

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
 * @method payForProduct
 * @param {TProductInfo}
 */
payForProduct : function () {},

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
 * @method getPluginName
 * @return A value converted from C/C++ "const char*"
 */
getPluginName : function () {},

/**
 * @method payResult
 * @param {cocos2d::plugin::EPayResult}
 * @param {const char*}
 */
payResult : function () {},

};

/**
 * @class ProtocolIAPOnLine
 */
plugin.ProtocolIAPOnLine = {

/**
 * @method initDeveloperInfo
 * @param {TDeveloperInfo}
 */
initDeveloperInfo : function () {},

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
 * @method payForProduct
 * @param {TProductInfo}
 */
payForProduct : function () {},

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
 * @method getPluginName
 * @return A value converted from C/C++ "const char*"
 */
getPluginName : function () {},

/**
 * @method payFailedLocally
 * @param {cocos2d::plugin::EPayResult}
 * @param {const char*}
 */
payFailedLocally : function () {},

};
