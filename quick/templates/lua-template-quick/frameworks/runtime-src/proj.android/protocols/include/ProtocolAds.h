/** @file ProtocolAds.h
 */
#ifndef __CCX_PROTOCOL_ADS_H__
#define __CCX_PROTOCOL_ADS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {
/// \typedef std::map<std::string, std::string> TAdsDeveloperInfo
/// typedef TAdsDeveloperInfo.
typedef std::map<std::string, std::string> TAdsDeveloperInfo;
/// \typedef std::map<std::string, std::string> TAdsInfo
/// typedef TAdsInfo.
typedef std::map<std::string, std::string> TAdsInfo;
/** @brief AdsResultCode enum, with inline docs */
typedef enum
{
    kAdsReceived = 0,           /**< enum the callback: the ad is received is at center. */

    kAdsShown,                  /**< enum the callback: the advertisement dismissed. */
    kAdsDismissed,             /**< enum the callback: the advertisement dismissed. */

    kPointsSpendSucceed,       /**< enum the callback: the points spend succeed. */
    kPointsSpendFailed,        /**< enum the callback: the points spend failed. */



    kNetworkError,              /**< enum the callback of Network error at center. */
    kUnknownError,              /**< enum the callback of Unknown error. */
    kOfferWallOnPointsChanged,   /**< enum the callback of Changing the point of offerwall. */
} AdsResultCode;
/** @brief AdsPos enum, with inline docs */
typedef enum {
    kPosCenter = 0,/**< enum the toolbar is at center. */
    kPosTop,/**< enum the toolbar is at top. */
    kPosTopLeft,/**< enum the toolbar is at topleft. */
    kPosTopRight,/**< enum the toolbar is at topright. */
    kPosBottom,/**< enum the toolbar is at bottom. */
    kPosBottomLeft,/**< enum the toolbar is at bottomleft. */
    kPosBottomRight,/**< enum the toolbar is at bottomright. */
} AdsPos;
/** @brief AdsType enum, with inline docs */
typedef enum {
	AD_TYPE_BANNER = 0,/**< enum value is banner ads . */
	AD_TYPE_FULLSCREEN,/**< enum value is fullscreen ads . */
	AD_TYPE_MOREAPP,/**< enum value is moreapp ads . */
	AD_TYPE_OFFERWALL,/**< enum value is offerwall ads . */
} AdsType;

class ProtocolAds;
class AdsListener
{
public:
    /**
     *@brief The advertisement request result
     *@param the id of callback
	 *@param the information of callback
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



    /**
    @brief show adview
    @param the type of ads
    @param the idx of ads
    */
    virtual void showAds(AdsType adsType, int idx = 1) = 0;

    /**
    @brief Hide the adview
    @param the type of ads
    @param the idx of ads
    */
    virtual void hideAds(AdsType adsType, int idx = 1) = 0;

    /**
    @brief preload the adview
    @param the type of ads
    @param the idx of ads
    */
    virtual void preloadAds(AdsType adsType, int idx = 1)= 0;

    /**
     *@brief Query the points of player
     *@return the point
    */
    virtual float queryPoints() = 0;

    /**
     *@brief Spend the points.
           Use this method to notify server spend points.
     *@param points Need spend number of points
     */
    virtual void spendPoints(int points) = 0;

    /**
     @brief set the Ads listener
     @param pListener The callback object for Ads result
     */
    virtual void setAdsListener(AdsListener* listener) = 0;

    /**
     @brief get pListener The callback object for Ads result
     @return the listener
     */
    virtual AdsListener* getAdsListener() = 0;

    /**
     @brief Is it supportive of this type of ads
     @param the type of ads
     @return if it is supportive ,return true
     	 	 else retur false
     */
    virtual bool isAdTypeSupported(AdsType adType) = 0;

};

}} // namespace anysdk { namespace framework {

#endif /* __CCX_PROTOCOL_ADS_H__ */
