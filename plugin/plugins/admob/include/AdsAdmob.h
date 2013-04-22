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
		eSizeBanner = 0,
		eSizeIABMRect,
		eSizeIABBanner,
		eSizeIABLeaderboard,
	} ESizeAdmobBanner;

    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
	@brief initialize the application info
	@param appInfo This parameter is the info of application, must contains:
					AdmobID		The publisher ID of admob.
	@warning Must invoke this interface before other interfaces.
			 And invoked only once.
	*/
    virtual void initAppInfo(TAppInfo appInfo);

	/**
	@brief show banner ads at specified position
	@param pos The position where the banner view be shown
	@param sizeEnum The size of the banner view. Use the value in ESizeAdmobBanner
	*/
	virtual void showBannerAd(EBannerPos pos, int sizeEnum);

	/**
	@brief hide the banner ads view
	*/
	virtual void hideBannerAd();

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
