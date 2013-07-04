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

plugin.ProtocolIAP.PayResultCode = {};
plugin.ProtocolIAP.PayResultCode.PaySuccess = 0;
plugin.ProtocolIAP.PayResultCode.PayFail = 1;
plugin.ProtocolIAP.PayResultCode.PayCancel = 2;
plugin.ProtocolIAP.PayResultCode.PayTimeOut = 3;

plugin.ProtocolSocial.ShareResultCode = {};
plugin.ProtocolSocial.ShareResultCode.ShareSuccess = 0;
plugin.ProtocolSocial.ShareResultCode.ShareFail = 1;
plugin.ProtocolSocial.ShareResultCode.ShareCancel = 2;
plugin.ProtocolSocial.ShareResultCode.ShareTimeOut = 3;

