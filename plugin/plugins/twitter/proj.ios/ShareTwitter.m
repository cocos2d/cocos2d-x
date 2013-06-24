/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#import "ShareTwitter.h"
#import "FHSTwitterEngine.h"
#import "ShareWrapper.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation ShareTwitter

@synthesize mShareInfo;
@synthesize debug = __debug;

- (void) configDeveloperInfo : (NSMutableDictionary*) cpInfo
{
    NSString* appKey = [cpInfo objectForKey:@"TwitterKey"];
    NSString* appSecret = [cpInfo objectForKey:@"TwitterSecret"];

    if (nil == appKey || nil == appSecret) {
        return;
    }

    [[FHSTwitterEngine sharedEngine]permanentlySetConsumerKey:appKey andSecret:appSecret];
}

- (void) share: (NSMutableDictionary*) shareInfo
{
    self.mShareInfo = shareInfo;
    if ([[FHSTwitterEngine sharedEngine]isAuthorized])
    {
        [self doShare];
    } else {
        UIViewController* controller = [self getCurrentRootViewController];
        [[FHSTwitterEngine sharedEngine]showOAuthLoginControllerFromViewController:controller withCompletion:^(BOOL success) {
            if (success) {
                [self doShare];
            } else {
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:@"Login Failed"];
            }
        }];
    }
}

- (void) setDebugMode: (BOOL) debug
{
    self.debug = debug;
}

- (NSString*) getSDKVersion
{
    return @"20130607";
}

- (NSString*) getPluginVersion
{
    return @"0.2.0";
}

- (void) doShare
{
    if (nil == mShareInfo) {
        [ShareWrapper onShareResult:self withRet:kShareFail withMsg:@"Shared info error"];
        return;
    }

    NSString* strText = [mShareInfo objectForKey:@"SharedText"];
    NSString* strImagePath = [mShareInfo objectForKey:@"SharedImagePath"];

    BOOL oldConfig = [UIApplication sharedApplication].networkActivityIndicatorVisible;
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
    NSError* returnCode = nil;
    if (nil != strImagePath) {
        NSData* data = [NSData dataWithContentsOfFile:strImagePath];
        returnCode = [[FHSTwitterEngine sharedEngine] postTweet:strText withImageData:data];
    } else {
        returnCode = [[FHSTwitterEngine sharedEngine]postTweet:strText];
    }
    [UIApplication sharedApplication].networkActivityIndicatorVisible = oldConfig;

    if (returnCode) {
        NSString* strErrorCode = [NSString stringWithFormat:@"ErrorCode %d", returnCode.code];
        [ShareWrapper onShareResult:self withRet:kShareFail withMsg:strErrorCode];
    } else {
        [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:@"Share Succeed"];
    }
}

- (UIViewController *)getCurrentRootViewController {

    UIViewController *result = nil;

    // Try to find the root view controller programmically

    // Find the top window (that is not an alert view or other window)
    UIWindow *topWindow = [[UIApplication sharedApplication] keyWindow];
    if (topWindow.windowLevel != UIWindowLevelNormal)
    {
        NSArray *windows = [[UIApplication sharedApplication] windows];
        for(topWindow in windows)
        {
            if (topWindow.windowLevel == UIWindowLevelNormal)
                break;
        }
    }

    UIView *rootView = [[topWindow subviews] objectAtIndex:0];
    id nextResponder = [rootView nextResponder];

    if ([nextResponder isKindOfClass:[UIViewController class]])
        result = nextResponder;
    else if ([topWindow respondsToSelector:@selector(rootViewController)] && topWindow.rootViewController != nil)
        result = topWindow.rootViewController;
    else
        NSAssert(NO, @"Could not find a root view controller.");

    return result;
}

@end
