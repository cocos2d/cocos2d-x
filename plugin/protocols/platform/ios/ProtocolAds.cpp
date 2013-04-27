#include "ProtocolAds.h"

namespace cocos2d { namespace plugin {

ProtocolAds::ProtocolAds()
: m_pListener(NULL)
{
}

ProtocolAds::~ProtocolAds()
{
}

bool ProtocolAds::init()
{
    return true;
}

void ProtocolAds::configDeveloperInfo(TAdsDeveloperInfo devInfo)
{
}

void ProtocolAds::showAds(AdsType type, int sizeEnum, AdsPos pos)
{
}

void ProtocolAds::hideAds(AdsType type)
{
}

void ProtocolAds::spendPoints(int points)
{
}

void ProtocolAds::setDebugMode(bool debug)
{
}

// For the callbak methods
void ProtocolAds::setAdsListener(AdsListener* pListener)
{
    m_pListener = pListener;
}

void ProtocolAds::onAdsResult(AdsResultCode code, const char* msg)
{
    if (m_pListener != NULL)
    {
        m_pListener->onAdsResult(code, msg);
    }
}

void ProtocolAds::onPlayerGetPoints(int points)
{
    if (m_pListener != NULL)
    {
        m_pListener->onPlayerGetPoints(this, points);
    }
}

const char* ProtocolAds::getSDKVersion()
{
    return "Subclass should override this interface";
}

}} //namespace cocos2d { namespace plugin {
