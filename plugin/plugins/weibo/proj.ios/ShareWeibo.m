/****************************************************************************
 Copyright (c) 2012-2013 cocos2d-x.org
 
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

#import "ShareWeibo.h"
#import "ShareWrapper.h"
#import "SinaWeibo/SinaWeiboConstants.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation ShareWeibo

@synthesize mShareInfo;
@synthesize sinaweibo;
@synthesize debug = __debug;

- (void)dealloc
{
    if (sinaweibo) {
        [sinaweibo release];
        sinaweibo = nil;
    }

    [super dealloc];
}

#pragma mark - InterfaceShare 

- (void) configDeveloperInfo : (NSMutableDictionary*) cpInfo
{
    OUTPUT_LOG(@"configDeveloperInfo invoked (%@)", [cpInfo description]);
    
    if (! sinaweibo) {
        NSString* appKey = (NSString*) [cpInfo objectForKey:@"WeiboAppKey"];
        NSString* appSecret = (NSString*) [cpInfo objectForKey:@"WeiboAppSecret"];
        NSString* appUrl = (NSString*) [cpInfo objectForKey:@"WeiboRedirectUrl"];

        sinaweibo = [[SinaWeibo alloc] initWithAppKey:appKey appSecret:appSecret appRedirectURI:appUrl andDelegate: self];
    }
}

- (void) share: (NSMutableDictionary*) shareInfo
{
    OUTPUT_LOG(@"share invoked (%@)", [shareInfo description]);
    assert(sinaweibo != nil);

    self.mShareInfo = shareInfo;
    BOOL authValid = sinaweibo.isAuthValid;
    if (! authValid) {
        [sinaweibo logIn];
    } else {
        [self doShare];
    }
}

- (void) doShare
{
    NSString* strText = [mShareInfo objectForKey:@"SharedText"];
    NSString* strImgPath = [mShareInfo objectForKey:@"SharedImagePath"];

    if (nil == strImgPath) {
        [sinaweibo requestWithURL:@"statuses/update.json"
                           params:[NSMutableDictionary dictionaryWithObjectsAndKeys:strText, @"status", nil]
                       httpMethod:@"POST"
                         delegate:self];
    } else {
        [sinaweibo requestWithURL:@"statuses/upload.json"
                           params:[NSMutableDictionary dictionaryWithObjectsAndKeys:
                                   strText, @"status",
                                   [UIImage imageNamed:strImgPath], @"pic", nil]
                       httpMethod:@"POST"
                         delegate:self];
    }
}

- (void) setDebugMode: (BOOL) debug
{
    self.debug = debug;
}

- (NSString*) getSDKVersion
{
    return SinaWeiboSdkVersion;
}

- (NSString*) getPluginVersion
{
    return @"0.2.0";
}

#pragma mark - SinaWeibo Delegate

- (void)storeAuthData
{
    NSDictionary *authData = [NSDictionary dictionaryWithObjectsAndKeys:
                              sinaweibo.accessToken, @"AccessTokenKey",
                              sinaweibo.expirationDate, @"ExpirationDateKey",
                              sinaweibo.userID, @"UserIDKey",
                              sinaweibo.refreshToken, @"refresh_token", nil];
    [[NSUserDefaults standardUserDefaults] setObject:authData forKey:@"SinaWeiboAuthData"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)removeAuthData
{
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"SinaWeiboAuthData"];
}

- (void)sinaweiboDidLogIn:(SinaWeibo *)weibo
{
    OUTPUT_LOG(@"sinaweiboDidLogIn userID = %@ accesstoken = %@ expirationDate = %@ refresh_token = %@",
               weibo.userID, weibo.accessToken, weibo.expirationDate,weibo.refreshToken);

    [self storeAuthData];

    if (nil != mShareInfo) {
        [self doShare];
    }
}

- (void)sinaweiboDidLogOut:(SinaWeibo *)sinaweibo
{
    OUTPUT_LOG(@"sinaweiboDidLogOut");
    [self removeAuthData];
}

- (void)sinaweiboLogInDidCancel:(SinaWeibo *)sinaweibo
{
    OUTPUT_LOG(@"sinaweiboLogInDidCancel");
    [ShareWrapper onShareResult:self withRet:kShareCancel withMsg:@"User Canceled"];
}

- (void)sinaweibo:(SinaWeibo *)sinaweibo logInDidFailWithError:(NSError *)error
{
    OUTPUT_LOG(@"sinaweibo logInDidFailWithError %@", error);
    [ShareWrapper onShareResult:self withRet:kShareFail withMsg:[error description]];
}

- (void)sinaweibo:(SinaWeibo *)sinaweibo accessTokenInvalidOrExpired:(NSError *)error
{
    OUTPUT_LOG(@"sinaweiboAccessTokenInvalidOrExpired %@", error);
    [self removeAuthData];
    [ShareWrapper onShareResult:self withRet:kShareFail withMsg:[error description]];
}

#pragma mark - SinaWeiboRequest Delegate

- (void)request:(SinaWeiboRequest *)request didFailWithError:(NSError *)error
{
    if ([request.url hasSuffix:@"statuses/update.json"] ||
        [request.url hasSuffix:@"statuses/upload.json"])
    {
        [ShareWrapper onShareResult:self withRet:kShareFail withMsg:[error description]];
    }
}

- (void)request:(SinaWeiboRequest *)request didFinishLoadingWithResult:(id)result
{
    if ([request.url hasSuffix:@"statuses/update.json"] ||
        [request.url hasSuffix:@"statuses/upload.json"])
    {
        [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:@"Share Success"];
    }
}

@end
