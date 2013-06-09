//
//  PluginTwitter.m
//  PluginTwitter
//
//  Created by zhangbin on 13-6-8.
//  Copyright (c) 2013年 zhangbin. All rights reserved.
//

#import "SocialTwitter.h"
#import "FHSTwitterEngine.h"
#import "SocialWrapper.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation SocialTwitter

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
                [SocialWrapper onShareResult:self withRet:kShareFail withMsg:@"Login Failed"];
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
        [SocialWrapper onShareResult:self withRet:kShareFail withMsg:@"Shared info error"];
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
        [SocialWrapper onShareResult:self withRet:kShareFail withMsg:strErrorCode];
    } else {
        [SocialWrapper onShareResult:self withRet:kShareSuccess withMsg:@"Share Succeed"];
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
