/**
 * @module cocos2dx_other
 */
var cc = cc || {};

/**
 * @class CCApplicationProtocol
 */
cc.ApplicationProtocol = {

/**
 * @method getTargetPlatform
 * @return A value converted from C/C++ "cocos2d::TargetPlatform"
 */
getTargetPlatform : function () {},

/**
 * @method getCurrentLanguage
 * @return A value converted from C/C++ "cocos2d::ccLanguageType"
 */
getCurrentLanguage : function () {},

/**
 * @method setAnimationInterval
 * @param {double}
 */
setAnimationInterval : function () {},

};

/**
 * @class CCApplication
 */
cc.Application = {

/**
 * @method getTargetPlatform
 * @return A value converted from C/C++ "cocos2d::TargetPlatform"
 */
getTargetPlatform : function () {},

/**
 * @method setAnimationInterval
 * @param {double}
 */
setAnimationInterval : function () {},

/**
 * @method getCurrentLanguage
 * @return A value converted from C/C++ "cocos2d::ccLanguageType"
 */
getCurrentLanguage : function () {},

/**
 * @method sharedApplication
 * @return A value converted from C/C++ "cocos2d::CCApplication*"
 */
sharedApplication : function () {},

};
