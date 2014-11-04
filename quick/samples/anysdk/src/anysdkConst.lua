
function CreatEnumTable(tbl, index) 
    local enumtbl = {} 
    local enumindex = index or 0 
    for i, v in ipairs(tbl) do 
        enumtbl[v] = enumindex + i - 1
    end 
    return enumtbl 
end 

Plugin_type = {
    "kPluginAds",
    "kPluginAnalytics",
    "kPluginIAP",
    "kPluginShare",
    "kPluginUser",
    "kPluginSocial",
    "kPluginPush"
}
Plugin_type = CreatEnumTable(Plugin_type, 1)

-- for ads
AdsResultCode = {
    "kAdsReceived",           	--/**< enum the callback: the ad is received is at center. */
    "kAdsShown",                  --/**< enum the callback: the advertisement dismissed. */
    "kAdsDismissed",             --/**< enum the callback: the advertisement dismissed. */
    "kPointsSpendSucceed",       --/**< enum the callback: the points spend succeed. */
    "kPointsSpendFailed",        --/**< enum the callback: the points spend failed. */
    "kNetworkError",              --/**< enum the callback of Network error at center. */
    "kUnknownError",              --/**< enum the callback of Unknown error. */
    "kOfferWallOnPointsChanged",   --/**< enum the callback of Changing the point of offerwall. */
};	--ads result code
AdsResultCode = CreatEnumTable(AdsResultCode, 0)

AdsPos = {
    "kPosCenter",			--/**< enum the toolbar is at center. */
    "kPosTop",				--/**< enum the toolbar is at top. */
    "kPosTopLeft",			--/**< enum the toolbar is at topleft. */
    "kPosTopRight",			--/**< enum the toolbar is at topright. */
    "kPosBottom",				--/**< enum the toolbar is at bottom. */
    "kPosBottomLeft",			--/**< enum the toolbar is at bottomleft. */
    "kPosBottomRight" 		--/**< enum the toolbar is at bottomright. */
};	--ads pos
AdsPos = CreatEnumTable(AdsPos, 0)

AdsType = {
	"AD_TYPE_BANNER",		--/**< enum value is banner ads . */
	"AD_TYPE_FULLSCREEN",	--/**< enum value is fullscreen ads . */
	"AD_TYPE_MOREAPP",		--/**< enum value is moreapp ads . */
	"AD_TYPE_OFFERWALL"	--/**< enum value is offerwall ads . */
};	--ads type
AdsType = CreatEnumTable(AdsType, 0)

--for pay result code
PayResultCode = {
    "kPaySuccess",		--/**< enum value is callback of succeeding in paying . */
    "kPayFail",			--/**< enum value is callback of failing to pay . */
    "kPayCancel",		--/**< enum value is callback of canceling to pay . */
    "kPayNetworkError",	--/**< enum value is callback of network error . */
    "kPayProductionInforIncomplete",	--/**< enum value is callback of incompleting info . */
	"kPayInitSuccess",	--/**< enum value is callback of succeeding in initing sdk . */
	"kPayInitFail",		--/**< enum value is callback of failing to init sdk . */
	"kPayNowPaying" 	--/**< enum value is callback of paying now . */
};
PayResultCode = CreatEnumTable(PayResultCode, 0)

-- for push action result code
PushActionResultCode = {
	"kPushReceiveMessage"	--/**value is callback of Receiving Message . */
};
PushActionResultCode = CreatEnumTable(PushActionResultCode, 0)

-- for share result code
ShareResultCode = {
    "kShareSuccess",	--/**< enum value is callback of failing to sharing . */
    "kShareFail",		--/**< enum value is callback of failing to share . */
    "kShareCancel",		--/**< enum value is callback of canceling to share . */
    "kShareNetworkError"	--/**< enum value is callback of network error . */
};
ShareResultCode = CreatEnumTable(ShareResultCode, 0)

--for social ret code
SocialRetCode = {
	-- code for leaderboard feature
	"kScoreSubmitSucceed",		--/**< enum value is callback of succeeding in submiting. */
    "kScoreSubmitfail",			--/**< enum value is callback of failing to submit . */
    -- code for achievement feature
    "kAchUnlockSucceed",		--/**< enum value is callback of succeeding in unlocking. */
    "kAchUnlockFail",			--/**< enum value is callback of failing to  unlock. */
    "kSocialSignInSucceed",		--/**< enum value is callback of succeeding to login. */
    "kSocialSignInFail",		--/**< enum value is callback of failing to  login. */
    "kSocialSignOutSucceed",	--/**< enum value is callback of succeeding to login. */
    "kSocialSignOutFail"		--/**< enum value is callback of failing to  login. */
};
SocialRetCode = CreatEnumTable(SocialRetCode, 1)

-- for user action result code
UserActionResultCode = {
	"kInitSuccess",		--/**< enum value is callback of succeeding in initing sdk. */
	"kInitFail",     		--/**< enum  value is callback of failing to init sdk. */
    "kLoginSuccess",	    --/**< enum value is callback of succeeding in login.*/
    "kLoginNetworkError",	--/**< enum value is callback of network error*/
    "kLoginNoNeed",		--/**< enum value is callback of no need login.*/
    "kLoginFail",		--/**< enum value is callback of failing to login. */
    "kLoginCancel",		--/**< enum value is callback of canceling to login. */
    "kLogoutSuccess", 	--/**< enum value is callback of succeeding in logout. */
    "kLogoutFail",		--/**< enum value is callback of failing to logout. */
    "kPlatformEnter", 	--/**< enum value is callback after enter platform. */
    "kPlatformBack",  	--/**< enum value is callback after exit antiAddiction. */
    "kPausePage", 		--/**< enum value is callback after exit pause page. */
    "kExitPage",  		--/**< enum value is callback after exit exit page. */
    "kAntiAddictionQuery",	--/**< enum value is callback after querying antiAddiction. */
    "kRealNameRegister",	--/**< enum value is callback after registering realname. */
    "kAccountSwitchSuccess",	--/**< enum alue is callback of succeeding in switching account. */
    "kAccountSwitchFail"	--/**< enum value is callback of failing to switch account. */
};
UserActionResultCode = CreatEnumTable(UserActionResultCode, 0)

-- for toolBar place
ToolBarPlace = {
    "kToolBarTopLeft",		--/**< enum the toolbar is at topleft. */
    "kToolBarTopRight",		--/**< enum the toolbar is at topright. */
    "kToolBarMidLeft",		--/**< enum the toolbar is at midleft. */
    "kToolBarMidRight",		--/**< enum the toolbar is at midright. */
    "kToolBarBottomLeft", 	--/**< enum the toolbar is at bottomleft. */
    "kToolBarBottomRight" 	--/**< enum the toolbar is at bottomright. */
};
ToolBarPlace = CreatEnumTable(ToolBarPlace, 1)
