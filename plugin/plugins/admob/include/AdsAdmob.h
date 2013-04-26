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
#ifndef __CCX_ADS_ADMOB_H__
#define __CCX_ADS_ADMOB_H__

#include "ProtocolAds.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

class AdsAdmob : public ProtocolAds
{
	PLUGIN_REGISTER_DECL(AdsAdmob)
public:

	typedef enum {
		kSizeBanner = 0,
		kSizeIABMRect,
		kSizeIABBanner,
		kSizeIABLeaderboard,
	} AdmobBannerSize;

    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
	@brief config the application info
	@param devInfo This parameter is the info of application, must contains:
					AdmobID		The publisher ID of admob.
	@warning Must invoke this interface before other interfaces.
			 And invoked only once.
	*/
    virtual void configDeveloperInfo(TAdsDeveloperInfo devInfo);

    /**
	@brief show adview
	@param type The adview type need to show.
	@param sizeEnum The size of the banner view.
				(only used when type is kBannerAd)
				Use the enum number in AdmobBannerSize.
	@param pos The position where the adview be shown.
			   (only used when type is kBannerAd)
	*/
	virtual void showAds(AdsType type, int sizeEnum = 0, AdsPos pos = kPosCenter);

	/**
	@brief Hide the adview
	@param type The adview type need to hide.
	*/
	virtual void hideAds(AdsType type);

    /**
	 @brief Set whether needs to output logs to console.
	 @param debug if true debug mode enabled, or debug mode disabled.
	 */
	virtual void setDebugMode(bool debug);

	/**
	@brief Add the test device ID
	@param deviceID  The device ID
	 */
	void addTestDevice(const char* deviceID);

    virtual const char* getPluginVersion() { return "v0.1.01"; };
    virtual const char* getSDKVersion();

    virtual ~AdsAdmob();
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ADS_ADMOB_H__ */
