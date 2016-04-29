var plugin = plugin || {PluginParam: {}, ProtocolAds: {}, ProtocolIAP: {}, ProtocolShare: {}, ProtocolSocial: {}, ProtocolUser: {}};
plugin.PluginParam = plugin.PluginParam || {};

plugin.PluginParam.ParamType = {};
plugin.PluginParam.ParamType.TypeInt = 1;
plugin.PluginParam.ParamType.TypeFloat = 2;
plugin.PluginParam.ParamType.TypeBool = 3;
plugin.PluginParam.ParamType.TypeString = 4;
plugin.PluginParam.ParamType.TypeStringMap = 5;

plugin.PluginParam.ParamType.TYPE_INT = 1;
plugin.PluginParam.ParamType.TYPE_FLOAT = 2;
plugin.PluginParam.ParamType.TYPE_BOOL = 3;
plugin.PluginParam.ParamType.TYPE_STRING = 4;
plugin.PluginParam.ParamType.TYPE_STRINGMAP = 5;

plugin.ProtocolAds.AdsResultCode = {};
plugin.ProtocolAds.AdsResultCode.AdsReceived = 0;
plugin.ProtocolAds.AdsResultCode.FullScreenViewShown = 1;
plugin.ProtocolAds.AdsResultCode.FullScreenViewDismissed = 2;
plugin.ProtocolAds.AdsResultCode.PointsSpendSucceed = 3;
plugin.ProtocolAds.AdsResultCode.PointsSpendFailed = 4;
plugin.ProtocolAds.AdsResultCode.NetworkError = 5;
plugin.ProtocolAds.AdsResultCode.UnknownError = 6;

plugin.ProtocolAds.AdsResultCode.ADSRECEIVED = 0;
plugin.ProtocolAds.AdsResultCode.FULLSCREENVIEW_SHOWN = 1;
plugin.ProtocolAds.AdsResultCode.FULLSCREENVIEW_DISMISSED = 2;
plugin.ProtocolAds.AdsResultCode.POINTS_SPEND_SUCCEED = 3;
plugin.ProtocolAds.AdsResultCode.POINTS_SPEND_FAILED = 4;
plugin.ProtocolAds.AdsResultCode.NETWORK_ERROR = 5;
plugin.ProtocolAds.AdsResultCode.UNKOWN_ERROR = 6;

plugin.ProtocolAds.AdsPos = {};
plugin.ProtocolAds.AdsPos.PosCenter = 0;
plugin.ProtocolAds.AdsPos.PosTop = 1;
plugin.ProtocolAds.AdsPos.PosTopLeft = 2;
plugin.ProtocolAds.AdsPos.PosTopRight = 3;
plugin.ProtocolAds.AdsPos.PosBottom = 4;
plugin.ProtocolAds.AdsPos.PosBottomLeft = 5;
plugin.ProtocolAds.AdsPos.PosBottomRight = 6;

plugin.ProtocolAds.AdsPos.POS_CENTER = 0;
plugin.ProtocolAds.AdsPos.POS_TOP = 1;
plugin.ProtocolAds.AdsPos.POS_TOP_LEFT = 2;
plugin.ProtocolAds.AdsPos.POS_TOP_RIGHT = 3;
plugin.ProtocolAds.AdsPos.POS_BOTTOM = 4;
plugin.ProtocolAds.AdsPos.POS_BOTTOM_LEFT = 5;
plugin.ProtocolAds.AdsPos.POS_BOTTOM_RIGHT = 6;

plugin.ProtocolIAP.PayResultCode = {};
plugin.ProtocolIAP.PayResultCode.PaySuccess = 0;
plugin.ProtocolIAP.PayResultCode.PayFail = 1;
plugin.ProtocolIAP.PayResultCode.PayCancel = 2;
plugin.ProtocolIAP.PayResultCode.PayTimeOut = 3;

plugin.ProtocolIAP.PayResultCode.PAY_SUCCESS = 0;
plugin.ProtocolIAP.PayResultCode.PAY_FAIL = 1;
plugin.ProtocolIAP.PayResultCode.PAY_CANCEL = 2;
plugin.ProtocolIAP.PayResultCode.PAY_TIMEOUT = 3;

plugin.ProtocolIAP.RequestProductCode = {};
plugin.ProtocolIAP.RequestProductCode.RequestSuccess = 0;
plugin.ProtocolIAP.RequestProductCode.RequestFail = 1;
plugin.ProtocolIAP.RequestProductCode.Requestimeout = 2;

plugin.ProtocolIAP.RequestProductCode.REQUEST_SUCCESS = 0;
plugin.ProtocolIAP.RequestProductCode.REQUEST_FAIL = 1;
plugin.ProtocolIAP.RequestProductCode.REQUEST_TIMEOUT = 2;

plugin.ProtocolShare.ShareResultCode = {};
plugin.ProtocolShare.ShareResultCode.ShareSuccess = 0;
plugin.ProtocolShare.ShareResultCode.ShareFail = 1;
plugin.ProtocolShare.ShareResultCode.ShareCancel = 2;
plugin.ProtocolShare.ShareResultCode.ShareTimeOut = 3;

plugin.ProtocolShare.ShareResultCode.SHARE_SUCCESS = 0;
plugin.ProtocolShare.ShareResultCode.SHARE_FAIL = 1;
plugin.ProtocolShare.ShareResultCode.SHARE_CANCEL = 2;
plugin.ProtocolShare.ShareResultCode.SHARE_TIMEOUT = 3;

plugin.ProtocolSocial.SocialRetCode = {};
plugin.ProtocolSocial.SocialRetCode.ScoreSubmitSuccess = 1;
plugin.ProtocolSocial.SocialRetCode.ScoreSubmitFailed = 2;
plugin.ProtocolSocial.SocialRetCode.AchUnlockSuccess = 3;
plugin.ProtocolSocial.SocialRetCode.AchUnlockFailed = 4;

plugin.ProtocolSocial.SocialRetCode.SCORE_SUBMIT_SUCCESS = 1;
plugin.ProtocolSocial.SocialRetCode.SCORE_SUBMIT_FAILED = 2;
plugin.ProtocolSocial.SocialRetCode.ACH_UNLOCK_SUCCESS = 3;
plugin.ProtocolSocial.SocialRetCode.ACH_UNLOCK_FAILED = 4;

plugin.ProtocolUser.UserActionResultCode = {};
plugin.ProtocolUser.UserActionResultCode.LoginSucceed = 0;
plugin.ProtocolUser.UserActionResultCode.LoginFailed = 1;
plugin.ProtocolUser.UserActionResultCode.LogoutSucceed = 2;

plugin.ProtocolUser.UserActionResultCode.LOGIN_SUCCEED = 0;
plugin.ProtocolUser.UserActionResultCode.LOGIN_FAILED = 1;
plugin.ProtocolUser.UserActionResultCode.LOGOUT_SUCCEED = 2;

plugin.FacebookAgent.HttpMethod = {};
plugin.FacebookAgent.HttpMethod.GET = 0;
plugin.FacebookAgent.HttpMethod.POST = 1;
plugin.FacebookAgent.HttpMethod.DELETE = 2;

plugin.FacebookAgent.AppEvent = {};
plugin.FacebookAgent.AppEvent.ACTIVATED_APP = "fb_mobile_activate_app";
plugin.FacebookAgent.AppEvent.COMPLETED_REGISTRATION = "fb_mobile_complete_registration";
plugin.FacebookAgent.AppEvent.VIEWED_CONTENT = "fb_mobile_content_view";
plugin.FacebookAgent.AppEvent.SEARCHED = "fb_mobile_search";
plugin.FacebookAgent.AppEvent.RATED = "fb_mobile_rate";
plugin.FacebookAgent.AppEvent.COMPLETED_TUTORIAL = "fb_mobile_tutorial_completion";
plugin.FacebookAgent.AppEvent.ADDED_TO_CART = "fb_mobile_add_to_cart";
plugin.FacebookAgent.AppEvent.ADDED_TO_WISHLIST = "fb_mobile_add_to_wishlist";
plugin.FacebookAgent.AppEvent.INITIATED_CHECKOUT = "fb_mobile_initiated_checkout";
plugin.FacebookAgent.AppEvent.ADDED_PAYMENT_INFO = "fb_mobile_add_payment_info";
plugin.FacebookAgent.AppEvent.PURCHASED = "fb_mobile_purchase";
plugin.FacebookAgent.AppEvent.ACHIEVED_LEVEL = "fb_mobile_level_achieved";
plugin.FacebookAgent.AppEvent.UNLOCKED_ACHIEVEMENT = "fb_mobile_achievement_unlocked";
plugin.FacebookAgent.AppEvent.SPENT_CREDITS = "fb_mobile_spent_credits";

plugin.FacebookAgent.AppEventParam = {};
plugin.FacebookAgent.AppEventParam.CURRENCY = "fb_currency";
plugin.FacebookAgent.AppEventParam.REGISTRATION_METHOD = "fb_registration_method";
plugin.FacebookAgent.AppEventParam.CONTENT_TYPE = "fb_content_type";
plugin.FacebookAgent.AppEventParam.CONTENT_ID = "fb_content_id";
plugin.FacebookAgent.AppEventParam.SEARCH_STRING = "fb_search_string";
plugin.FacebookAgent.AppEventParam.SUCCESS = "fb_success";
plugin.FacebookAgent.AppEventParam.MAX_RATING_VALUE = "fb_max_rating_value";
plugin.FacebookAgent.AppEventParam.PAYMENT_INFO_AVAILABLE = "fb_payment_info_available";
plugin.FacebookAgent.AppEventParam.NUM_ITEMS = "fb_num_items";
plugin.FacebookAgent.AppEventParam.LEVEL = "fb_level";
plugin.FacebookAgent.AppEventParam.DESCRIPTION = "fb_description";

plugin.FacebookAgent.AppEventParamValue = {};
plugin.FacebookAgent.AppEventParamValue.VALUE_YES = "1";
plugin.FacebookAgent.AppEventParamValue.VALUE_NO = "0";

plugin.FacebookAgent.CODE_SUCCEED = 0;

plugin.FacebookAgent.getInstance = plugin.FacebookAgent.getInstanceJs;

plugin.FacebookAgent.prototype.logout = function(callback){
    this._logout();
    callback(0, {"isLoggedIn" : false});
};

//plugin.FacebookAgent.prototype.getPermissionList = function(callback){
//    var list = this._getPermissionList();
//    callback( list ? plugin.FacebookAgent.CODE_SUCCEED : -1, JSON.parse(list));
//};

//plugin.FacebookAgent.prototype.requestAccessToken = function(callback){
//    var at = this.getAccessToken();
//    callback( at ? plugin.FacebookAgent.CODE_SUCCEED : -1, {"accessToken" : at});
//};

plugin.FacebookAgent.prototype.api = function(path, HttpMethod, params, callback){
    if(callback == undefined){
       callback = params;
       params = {};
    }

    this._api(path, HttpMethod, params, function(code, msg){
        callback(code, JSON.parse(msg));
    });
}
