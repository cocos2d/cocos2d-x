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
#include <functional>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TAdsDeveloperInfo;
typedef std::map<std::string, std::string> TAdsInfo;

typedef enum
{
    kAdsReceived = 0,            // The ad is received

    kAdsShown,                  // The advertisement shown
    kAdsDismissed,              // The advertisement dismissed

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
	ProtocolAds();
	virtual ~ProtocolAds();

    typedef enum {
        kPosCenter = 0,
        kPosTop,
        kPosTopLeft,
        kPosTopRight,
        kPosBottom,
        kPosBottomLeft,
        kPosBottomRight,
    } AdsPos;

    typedef std::function<void(int, std::string&)> ProtocolAdsCallback;

    /**
    @brief config the application info
    @param devInfo This parameter is the info of aplication,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TAdsDeveloperInfo devInfo);

    /**
    @brief show adview
    @param info The information of adview will be shown
                Pay attention to the subclass definition
    @param pos The position where the adview be shown.
    */
    void showAds(TAdsInfo info, AdsPos pos = kPosCenter);

    /**
    @brief Hide the adview
    @param info The information of adview will be hided
    */
    void hideAds(TAdsInfo info);

    /**
    @brief Query the points of player
    */
    void queryPoints();

    /**
    @brief Spend the points.
           Use this method to notify server spend points.
    @param points Need spend number of points
    */
    void spendPoints(int points);

    /**
     @deprecated
     @brief set the Ads listener
    */
    CC_DEPRECATED_ATTRIBUTE inline void setAdsListener(AdsListener* listener)
    {
        _listener = listener;
    }

    /**
     @deprecated
     @brief set the Ads listener
    */
    CC_DEPRECATED_ATTRIBUTE inline AdsListener* getAdsListener()
    {
        return _listener;
    }

    /**
     @brief set the Ads callback function
    */
    inline void setCallback(ProtocolAdsCallback& cb)
    {
    	_callback = cb;
    }

    /**
     @brief get the Ads callback function
    */
    inline ProtocolAdsCallback getCallback()
    {
    	return _callback;
    }
protected:
    AdsListener* _listener;
    ProtocolAdsCallback _callback;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_ADS_H__ */
