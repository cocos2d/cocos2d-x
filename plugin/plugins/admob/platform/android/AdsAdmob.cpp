/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
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

void AdsAdmob::configDeveloperInfo(TAdsDeveloperInfo appInfo)
{
	ProtocolAds::configDeveloperInfo(appInfo);
}

void AdsAdmob::showAds(AdsType type, int sizeEnum, AdsPos pos)
{
	ProtocolAds::showAds(type, sizeEnum, pos);
}

void AdsAdmob::hideAds(AdsType type)
{
	ProtocolAds::hideAds(type);
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
