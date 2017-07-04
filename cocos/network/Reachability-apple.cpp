/****************************************************************************
 Copyright (c) 2016-2017 Chukong Technologies Inc.

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
#include "network/Reachability-apple.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <netinet/in.h>
#include <SystemConfiguration/CaptiveNetwork.h>
#include <notify_keys.h>

NS_CC_BEGIN

#define NSAssert(cond, ...) assert(cond)

#pragma mark - Supporting functions

#define kShouldPrintReachabilityFlags 1

static void printReachabilityFlags(SCNetworkReachabilityFlags flags, const char* comment)
{
#if kShouldPrintReachabilityFlags

    printf("Reachability Flag Status: %c%c %c%c%c%c%c%c%c %s\n",
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
          (flags & kSCNetworkReachabilityFlagsIsWWAN)				? 'W' : '-',
#else
          '-',
#endif
          (flags & kSCNetworkReachabilityFlagsReachable)            ? 'R' : '-',

          (flags & kSCNetworkReachabilityFlagsTransientConnection)  ? 't' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionRequired)   ? 'c' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic)  ? 'C' : '-',
          (flags & kSCNetworkReachabilityFlagsInterventionRequired) ? 'i' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionOnDemand)   ? 'D' : '-',
          (flags & kSCNetworkReachabilityFlagsIsLocalAddress)       ? 'l' : '-',
          (flags & kSCNetworkReachabilityFlagsIsDirect)             ? 'd' : '-',
          comment
          );
#endif
}

static Reachability::NetworkStatus getNetworkStatusForFlags(SCNetworkReachabilityFlags flags)
{
    printReachabilityFlags(flags, "networkStatusForFlags");
    if ((flags & kSCNetworkReachabilityFlagsReachable) == 0)
    {
        // The target host is not reachable.
        return Reachability::NetworkStatus::NOT_REACHABLE;
    }

    Reachability::NetworkStatus returnValue = Reachability::NetworkStatus::NOT_REACHABLE;

    if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0)
    {
        /*
         If the target host is reachable and no connection is required then we'll assume (for now) that you're on Wi-Fi...
         */
        returnValue = Reachability::NetworkStatus::REACHABLE_VIA_ETHERNET_OR_WIFI;
    }

    if ((((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) ||
         (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0))
    {
        /*
         ... and the connection is on-demand (or on-traffic) if the calling application is using the CFSocketStream or higher APIs...
         */

        if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0)
        {
            /*
             ... and no [user] intervention is needed...
             */
            returnValue = Reachability::NetworkStatus::REACHABLE_VIA_ETHERNET_OR_WIFI;
        }
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN)
    {
        /*
         ... but WWAN connections are OK if the calling application is using the CFNetwork APIs.
         */
        returnValue = Reachability::NetworkStatus::REACHABLE_VIA_WWAN;
    }
#endif
    
    return returnValue;
}

// static
void Reachability::onReachabilityChanged(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void* info)
{
    Reachability* thiz = (Reachability*) info;
    // Notify the client that the network reachability changed.
    if (!thiz->_isOwnerDestroyed)
    {
        if (thiz->_reachabilityChangedCallback != nullptr)
        {
            printf("Reachability (%p) was changed by SCNetworkReachabilityRef\n", thiz);
            NetworkStatus netStatus = getNetworkStatusForFlags(flags);
            thiz->_reachabilityChangedCallback(thiz, netStatus);
        }
    }
    else
    {
        printf("Reachability's owner is destroyed, skip callback!\n");
    }
}


#pragma mark - Reachability implementation

Reachability* Reachability::createWithHostName(const char* hostName)
{
	Reachability* returnValue = nullptr;
	SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithName(nullptr, hostName);
	if (reachability != nullptr)
	{
        returnValue = new (std::nothrow) Reachability();
		if (returnValue != nullptr)
		{
			returnValue->_reachabilityRef = reachability;
		}
        else {
            CFRelease(reachability);
        }
	}
	return returnValue;
}


Reachability* Reachability::createWithAddress(const struct sockaddr *hostAddress)
{
	SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, hostAddress);

	Reachability* returnValue = nullptr;

	if (reachability != nullptr)
	{
		returnValue = new (std::nothrow) Reachability();
		if (returnValue != nullptr)
		{
			returnValue->_reachabilityRef = reachability;
		}
        else {
            CFRelease(reachability);
        }
	}
	return returnValue;
}


Reachability* Reachability::createForInternetConnection()
{
#if (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 90000) || (defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)
    struct sockaddr_in6 zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin6_len = sizeof(zeroAddress);
    zeroAddress.sin6_family = AF_INET6;
#else
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
#endif
    
    return createWithAddress((const struct sockaddr *) &zeroAddress);
}

#pragma mark - Start and stop notifier

static std::string convertCFStringRefToStdString(CFTypeRef str)
{
    std::string ret;

    if (str != nullptr && CFGetTypeID(str) == CFStringGetTypeID())
    {
        char buffer[256] = {0};
        if (CFStringGetCString((CFStringRef)str, buffer, sizeof(buffer), kCFStringEncodingUTF8))
        {
            ret = buffer;
        }
    }

    return ret;
}

bool Reachability::startNotifier(const std::function<void(Reachability*, NetworkStatus)>& reachabilityChangedCallback)
{
	bool returnValue = false;

    auto retainCb = [](const void* info) -> const void*{
        Reachability* reachability = (Reachability*)info;
        reachability->retain();
        return reachability;
    };

    auto releaseCb = [](const void* info) -> void {
        Reachability* reachability = (Reachability*)info;
        reachability->release();
    };

    SCNetworkReachabilityContext context = {0, this, retainCb, releaseCb, nullptr};

	if (SCNetworkReachabilitySetCallback(_reachabilityRef, onReachabilityChanged, &context))
	{
		if (SCNetworkReachabilityScheduleWithRunLoop(_reachabilityRef, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode))
		{
            _reachabilityChangedCallback = reachabilityChangedCallback;
			returnValue = true;
		}
	}

    CFNotificationCenterAddObserver(CFNotificationCenterGetDarwinNotifyCenter(), //center
                                    this, // observer
                                    [](CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo){
                                        std::string notifyName = convertCFStringRefToStdString(name);
                                        if (notifyName == kNotifySCNetworkChange)
                                        {
                                            Reachability* thiz = (Reachability*)observer;
//                                            printf("Reachability (%p) was changed by %s!\n", thiz, kNotifySCNetworkChange);

                                            if (thiz->_reachabilityChangedCallback != nullptr)
                                            {
                                                thiz->_reachabilityChangedCallback(thiz, NetworkStatus::REACHABLE_VIA_ETHERNET_OR_WIFI);
                                            }
                                        }
                                        else
                                        {
                                            printf("Unknown notifcation: %s\n", notifyName.c_str());
                                        }
                                    },
                                    CFSTR(kNotifySCNetworkChange), // event name
                                    nullptr, // object
                                    CFNotificationSuspensionBehaviorDeliverImmediately);
    _toObserveNetworkChanged = true;
    
	return returnValue;
}


void Reachability::stopNotifier()
{
    if (_toObserveNetworkChanged)
    {
        CFNotificationCenterRemoveObserver(CFNotificationCenterGetDarwinNotifyCenter(), this, CFSTR(kNotifySCNetworkChange), nullptr);
        _toObserveNetworkChanged = false;
    }

	if (_reachabilityRef != nullptr)
	{
        SCNetworkReachabilitySetCallback(_reachabilityRef, nullptr, nullptr);
		SCNetworkReachabilityUnscheduleFromRunLoop(_reachabilityRef, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
	}

    _reachabilityChangedCallback = nullptr;
}

Reachability::Reachability()
: _reachabilityRef(nullptr)
, _reachabilityChangedCallback(nullptr)
, _isOwnerDestroyed(false)
, _toObserveNetworkChanged(false)
{
}

Reachability::~Reachability()
{
    stopNotifier();

    CFRelease(_reachabilityRef);
    _reachabilityRef = nullptr;
}


#pragma mark - Network Flag Handling


bool Reachability::isConnectionRequired() const
{
	NSAssert(_reachabilityRef != nullptr, "connectionRequired called with nullptr reachabilityRef");
	SCNetworkReachabilityFlags flags;

	if (SCNetworkReachabilityGetFlags(_reachabilityRef, &flags))
	{
		return (flags & kSCNetworkReachabilityFlagsConnectionRequired);
	}

    return false;
}

Reachability::NetworkStatus Reachability::getCurrentReachabilityStatus() const
{
	NSAssert(_reachabilityRef != nullptr, "currentNetworkStatus called with nullptr SCNetworkReachabilityRef");
    NetworkStatus returnValue = NetworkStatus::NOT_REACHABLE;
	SCNetworkReachabilityFlags flags;
    
	if (SCNetworkReachabilityGetFlags(_reachabilityRef, &flags))
	{
        returnValue = getNetworkStatusForFlags(flags);
	}
    
	return returnValue;
}

void Reachability::setOwnerDestroyed(bool isOwnerDestroyed)
{
    _isOwnerDestroyed = isOwnerDestroyed;
}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
