#include "AdsAdmob.h"
#include "PluginUtils.h"

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AdsAdmob)

AdsAdmob::~AdsAdmob()
{
}

bool AdsAdmob::init()
{
	return PluginUtils::initJavaPlugin(this, "org.cocos2dx.plugin.AdsAdmob");
}

void AdsAdmob::initAppInfo(TAppInfo appInfo)
{
	ProtocolAds::initAppInfo(appInfo);
}

void AdsAdmob::showBannerAd(EBannerPos pos, int sizeEnum)
{
	ProtocolAds::showBannerAd(pos, sizeEnum);
}

void AdsAdmob::hideBannerAd()
{
	ProtocolAds::hideBannerAd();
}

const char* AdsAdmob::getSDKVersion()
{
	return ProtocolAds::getSDKVersion();
}

void AdsAdmob::setDebugMode(bool debug)
{
	ProtocolAds::setDebugMode(debug);
}

void AdsAdmob::addTestDevice(const char* deviceID)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "addTestDevice"
		, "(Ljava/lang/String;)V"))
	{
		jstring strDeviceID = t.env->NewStringUTF(deviceID);
		t.env->CallVoidMethod(pData->jobj, t.methodID, strDeviceID);
		t.env->DeleteLocalRef(strDeviceID);
		t.env->DeleteLocalRef(t.classID);
	}
}

}} // namespace cocos2d { namespace plugin {
