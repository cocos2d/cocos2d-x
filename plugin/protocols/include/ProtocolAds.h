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
#ifndef __CCX_PROTOCOL_ADS_H__
#define __CCX_PROTOCOL_ADS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TAdsDeveloperInfo;

typedef enum
{
    kAdsReceived = 0,            // The ad is received

    kFullScreenViewShown,       // The full screen advertisement shown
    kFullScreenViewDismissed,   // The full screen advertisement dismissed

    kPointsSpendSucceed,        // The points spend succeed
    kPointsSpendFailed,         // The points spend failed

    kNetworkError,              // Network error
    kUnknownError,              // Unknown error
} AdsResultCode;

class ProtocolAds;
class AdsListener
{
public:
    /**
    @brief The advertisement request result
    */
    virtual void onAdsResult(AdsResultCode code, const char* msg) = 0;
    
    /**
    @brief Player get points from advertisement(For example: Tapjoy)
    @param points The point number player has got.
    @param pAdsPlugin  The plugin which the player get points. Used to spend the points.
    */
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points) {}
};

class ProtocolAds : public PluginProtocol
{
public:

    typedef enum {
        kBannerAd = 0,
        kFullScreenAd,
    } AdsType;

    typedef enum {
        kPosCenter = 0,
        kPosTop,
        kPosTopLeft,
        kPosTopRight,
        kPosBottom,
        kPosBottomLeft,
        kPosBottomRight,
    } AdsPos;

    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
    @brief config the application info
    @param devInfo This parameter is the info of aplication,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void configDeveloperInfo(TAdsDeveloperInfo devInfo);

    /**
    @brief show adview
    @param type The adview type need to show.
    @param sizeEnum The size of the banner view.
                (only used when type is kBannerAd)
                In different plugin, it's have different mean.
                Pay attention to the subclass definition
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
    @brief Spend the points.
           Use this method to notify server spend points.
    @param points Need spend number of points
    */
    virtual void spendPoints(int points);

    /**
     @brief Set whether needs to output logs to console.
     @param debug If true debug mode enabled, or debug mode disabled.
     */
    virtual void setDebugMode(bool debug);

    /**
     @brief set the Ads listener
    */
    void setAdsListener(AdsListener* pListener);

    // For the callbak methods
    void onAdsResult(AdsResultCode code, const char* msg);
    void onPlayerGetPoints(int points);

    virtual const char* getPluginVersion() { return "ProtocolAds, v0.1.01 , subclass should override this interface!"; };
    virtual const char* getSDKVersion();
    virtual const char* getPluginName() = 0;

protected:
    ProtocolAds();
public:
    virtual ~ProtocolAds();

protected:
    AdsListener* m_pListener;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_ADS_H__ */
