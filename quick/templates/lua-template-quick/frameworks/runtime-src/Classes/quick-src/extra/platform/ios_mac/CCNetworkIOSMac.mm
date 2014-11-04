
#import "ReachabilityIOSMac.h"
#include "network/CCNetwork.h"

NS_CC_EXTRA_BEGIN

bool Network::isLocalWiFiAvailable(void)
{
    return [[ReachabilityIOSMac reachabilityForLocalWiFi] currentReachabilityStatus] != NotReachable;
}

bool Network::isInternetConnectionAvailable(void)
{
    return [[ReachabilityIOSMac reachabilityForInternetConnection] currentReachabilityStatus] != NotReachable;
}

bool Network::isHostNameReachable(const char* hostName)
{
    NSString *hostName_ = [NSString stringWithUTF8String:hostName];
    return [[ReachabilityIOSMac reachabilityWithHostname:hostName_] currentReachabilityStatus] != NotReachable;
}

int Network::getInternetConnectionStatus(void)
{
    NetworkStatus status = [[ReachabilityIOSMac reachabilityForInternetConnection] currentReachabilityStatus];
    if (status == ReachableViaWiFi) return kCCNetworkStatusReachableViaWiFi;
    if (status == ReachableViaWWAN) return kCCNetworkStatusReachableViaWWAN;
    return kCCNetworkStatusNotReachable;
}

NS_CC_EXTRA_END
