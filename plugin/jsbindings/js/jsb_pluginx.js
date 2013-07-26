plugin = plugin || {};

plugin.PluginParam.ParamType = {};
plugin.PluginParam.ParamType.TypeInt = 1;
plugin.PluginParam.ParamType.TypeFloat = 2;
plugin.PluginParam.ParamType.TypeBool = 3;
plugin.PluginParam.ParamType.TypeString = 4;
plugin.PluginParam.ParamType.TypeStringMap = 5;

plugin.ProtocolAds.AdsResultCode = {};
plugin.ProtocolAds.AdsResultCode.AdsReceived = 0;
plugin.ProtocolAds.AdsResultCode.FullScreenViewShown = 1;
plugin.ProtocolAds.AdsResultCode.FullScreenViewDismissed = 2;
plugin.ProtocolAds.AdsResultCode.PointsSpendSucceed = 3;
plugin.ProtocolAds.AdsResultCode.PointsSpendFailed = 4;
plugin.ProtocolAds.AdsResultCode.NetworkError = 5;
plugin.ProtocolAds.AdsResultCode.UnknownError = 6;

plugin.ProtocolAds.AdsPos = {};
plugin.ProtocolAds.AdsPos.PosCenter = 0;
plugin.ProtocolAds.AdsPos.PosTop = 1;
plugin.ProtocolAds.AdsPos.PosTopLeft = 2;
plugin.ProtocolAds.AdsPos.PosTopRight = 3;
plugin.ProtocolAds.AdsPos.PosBottom = 4;
plugin.ProtocolAds.AdsPos.PosBottomLeft = 5;
plugin.ProtocolAds.AdsPos.PosBottomRight = 6;

plugin.ProtocolIAP.PayResultCode = {};
plugin.ProtocolIAP.PayResultCode.PaySuccess = 0;
plugin.ProtocolIAP.PayResultCode.PayFail = 1;
plugin.ProtocolIAP.PayResultCode.PayCancel = 2;
plugin.ProtocolIAP.PayResultCode.PayTimeOut = 3;

plugin.ProtocolShare.ShareResultCode = {};
plugin.ProtocolShare.ShareResultCode.ShareSuccess = 0;
plugin.ProtocolShare.ShareResultCode.ShareFail = 1;
plugin.ProtocolShare.ShareResultCode.ShareCancel = 2;
plugin.ProtocolShare.ShareResultCode.ShareTimeOut = 3;

plugin.ProtocolSocial.SocialRetCode = {};
plugin.ProtocolSocial.SocialRetCode.ScoreSubmitSuccess = 1;
plugin.ProtocolSocial.SocialRetCode.ScoreSubmitFailed = 2;
plugin.ProtocolSocial.SocialRetCode.AchUnlockSuccess = 3;
plugin.ProtocolSocial.SocialRetCode.AchUnlockFailed = 4;

plugin.ProtocolUser.UserActionResultCode = {};
plugin.ProtocolUser.UserActionResultCode.LoginSucceed = 0;
plugin.ProtocolUser.UserActionResultCode.LoginFailed = 1;
plugin.ProtocolUser.UserActionResultCode.LogoutSucceed = 2;

