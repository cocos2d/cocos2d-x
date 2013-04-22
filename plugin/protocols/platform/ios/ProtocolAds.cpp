#include "ProtocolAds.h"

namespace cocos2d { namespace plugin {

AdListener* ProtocolAds::m_pListener = NULL;

ProtocolAds::ProtocolAds()
{
}

ProtocolAds::~ProtocolAds()
{
}

/**
 @brief plugin initialization
 */
bool ProtocolAds::init()
{
    return true;
}

/**
 @brief initialize the application info
 @param appInfo This parameter is the info of aplication,
 different plugin have different format
 @warning Must invoke this interface before other interfaces.
 And invoked only once.
 */
void ProtocolAds::initAppInfo(TAppInfo appInfo)
{
}

/**
 @brief show banner ads at specified position
 @param pos The position where the banner view be shown
 @param sizeEnum The size of the banner view.
 In different plugin, it's have different mean.
 Pay attention to the subclass definition
 */
void ProtocolAds::showBannerAd(EBannerPos pos, int sizeEnum)
{
}

/**
 @brief hide the banner ads view
 */
void ProtocolAds::hideBannerAd()
{
}

/**
 @brief Set whether needs to output logs to console.
 @param debug If true debug mode enabled, or debug mode disabled.
 */
void ProtocolAds::setDebugMode(bool debug)
{
}

// For the callbak methods
void ProtocolAds::receiveAd()
{
    if (m_pListener != NULL)
    {
        m_pListener->onReceiveAd();
    }
}

void ProtocolAds::presentScreen()
{
    if (m_pListener != NULL)
    {
        m_pListener->onPresentScreen();
    }
}

void ProtocolAds::failedToReceiveAd(AdListener::EAdErrorCode code, const char* msg)
{
    if (m_pListener != NULL)
    {
        m_pListener->onFailedToReceiveAd(code, msg);
    }
}

void ProtocolAds::dismissScreen()
{
    if (m_pListener != NULL)
    {
        m_pListener->onDismissScreen();
    }
}

const char* ProtocolAds::getSDKVersion()
{
    return "Subclass should override this interface";
}

}} //namespace cocos2d { namespace plugin {
