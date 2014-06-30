
#ifndef __CC_EXTENSION_CCNETWORK_H_
#define __CC_EXTENSION_CCNETWORK_H_

#include "cocos2dx_extra.h"
#include "network/CCHTTPRequest.h"
#include "network/CCHTTPRequestDelegate.h"

using namespace cocos2d;
NS_CC_EXTRA_BEGIN

#define kCCNetworkStatusNotReachable     0
#define kCCNetworkStatusReachableViaWiFi 1
#define kCCNetworkStatusReachableViaWWAN 2

class Network
{
public:
#pragma mark -
#pragma mark reachability
    
    /** @brief Checks whether a local wifi connection is available */
    static bool isLocalWiFiAvailable(void);
    
    /** @brief Checks whether the default route is available */
    static bool isInternetConnectionAvailable(void);
    
    /** @brief Checks the reachability of a particular host name */
    static bool isHostNameReachable(const char* hostName);
    
    /** @brief Checks Internet connection reachability status */
    static int getInternetConnectionStatus(void);
    
#pragma mark -
#pragma mark HTTP
    
    static HTTPRequest* createHTTPRequest(HTTPRequestDelegate* delegate,
                                            const char* url,
                                            int method = kCCHTTPRequestMethodGET);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static HTTPRequest* createHTTPRequestLua(cocos2d::LUA_FUNCTION listener,
                                               const char* url,
                                               int method = kCCHTTPRequestMethodGET);
#endif
    
private:
    Network(void) {}
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCNETWORK_H_
