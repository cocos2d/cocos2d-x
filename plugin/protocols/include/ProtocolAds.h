#ifndef __CCX_PROTOCOL_ADS_H__
#define __CCX_PROTOCOL_ADS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TAppInfo;

class AdListener
{
public:
    typedef enum
    {
        eUnknownError = 0,
        eNetworkError,
    } EAdErrorCode;

    virtual void onReceiveAd() {}
    virtual void onPresentScreen() {}
    virtual void onFailedToReceiveAd(EAdErrorCode code, const char* msg) {}
    virtual void onDismissScreen() {}
};

class ProtocolAds : public PluginProtocol
{
public:

    typedef enum {
        ePosTop = 0,
        ePosTopLeft,
        ePosTopRight,
        ePosBottom,
        ePosBottomLeft,
        ePosBottomRight,
    } EBannerPos;

    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
    @brief initialize the application info
    @param appInfo This parameter is the info of aplication,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void initAppInfo(TAppInfo appInfo);

    /**
    @brief show banner ads at specified position
    @param pos The position where the banner view be shown
    @param sizeEnum The size of the banner view.
    	   In different plugin, it's have different mean.
    	   Pay attention to the subclass definition
    */
    virtual void showBannerAd(EBannerPos pos, int sizeEnum);

    /**
    @brief hide the banner ads view
    */
    virtual void hideBannerAd();

    /**
     @brief Set whether needs to output logs to console.
     @param debug If true debug mode enabled, or debug mode disabled.
     */
    virtual void setDebugMode(bool debug);

    /**
     @brief set the Ads listener
    */
    static void setAdListener(AdListener* pListener)
    {
        m_pListener = pListener;
    }

    // For the callbak methods
    static void receiveAd();
    static void presentScreen();
    static void failedToReceiveAd(AdListener::EAdErrorCode code, const char* msg);
    static void dismissScreen();

    virtual const char* getPluginVersion() { return "ProtocolAds, v0.1.01 , subclass should override this interface!"; };
    virtual const char* getSDKVersion();
    virtual const char* getPluginName() = 0;

protected:
    ProtocolAds();
public:
    virtual ~ProtocolAds();

protected:
    static AdListener* m_pListener;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_ADS_H__ */
