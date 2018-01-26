/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#ifndef __HTTPASYNCONNECTION_H__
#define __HTTPASYNCONNECTION_H__
/// @cond DO_NOT_SHOW

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import <Foundation/Foundation.h>
#import <Security/Security.h>
/// @cond
@interface HttpAsynConnection : NSObject <NSURLConnectionDelegate, NSURLConnectionDataDelegate>
{
}

// The original URL to download.  Due to redirects the actual content may come from another URL
@property (strong) NSString *srcURL;

@property (strong) NSString *sslFile;

@property (copy) NSDictionary *responseHeader;

@property (strong) NSMutableData *responseData;

@property (readonly) NSInteger getDataTime;

@property (readonly) NSInteger responseCode;
@property (readonly) NSString *statusString;

@property (strong) NSError *responseError;
@property (strong) NSError *connError;

@property (strong) NSURLConnection *conn;

@property bool finish;

@property (strong) NSRunLoop *runLoop;

// instructs the class to start the request.
-(void) startRequest:(NSURLRequest*)request;

@end

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

/// @endcond
#endif //__HTTPASYNCONNECTION_H__

