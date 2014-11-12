
#include "network/CCNetwork.h"

NS_CC_EXTRA_BEGIN

bool Network::isLocalWiFiAvailable(void)
{
    CCLOG("Network::isLocalWiFiAvailable() - not support this platform.");
    return true;
}

bool Network::isInternetConnectionAvailable(void)
{
    CCLOG("Network::isInternetConnectionAvailable() - not support this platform.");
    return true;
}

bool Network::isHostNameReachable(const char* hostName)
{
    CCLOG("Network::isHostNameReachable() - not support this platform.");
    return true;
}

int Network::getInternetConnectionStatus(void)
{
    CCLOG("Network::getInternetConnectionStatus() - not support this platform.");
    return kCCNetworkStatusNotReachable;
}

NS_CC_EXTRA_END
