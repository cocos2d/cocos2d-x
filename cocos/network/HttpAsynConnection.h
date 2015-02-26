/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#import <Foundation/Foundation.h>
#import <Security/Security.h>

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

@property (strong) NSURLConnection *conn;

@property bool finish;

@property (strong) NSRunLoop *runLoop;

// instructs the class to start the request.
-(void) startRequest:(NSURLRequest*)request;

@end

#endif //__HTTPASYNCONNECTION_H__
