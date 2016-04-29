/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#import "UserFacebook.h"
#import <FacebookSDK/FacebookSDK.h>
#import "UserWrapper.h"
#import "ParseUtils.h"
#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation UserFacebook


@synthesize mUserInfo;
@synthesize debug = __debug;
bool _isLogin = false;
NSString *_userId = @"";
NSString *_accessToken = @"";

- (void) configDeveloperInfo : (NSMutableDictionary*) cpInfo{
}
- (void) login{
    [self _loginWithPermission:@[@"public_profile"]];
}
-(void) loginWithPermission:(NSString *)permissions{
    NSArray *permission = [permissions componentsSeparatedByString:@","];
    [self _loginWithPermission:permission];
}
-(void)_loginWithPermission:(NSArray *) permission{
        [FBSession openActiveSessionWithReadPermissions:permission
                                           allowLoginUI:YES
                                      completionHandler:
         ^(FBSession *session, FBSessionState state, NSError *error) {
             [self sessionStateChanged:session state:state error:error];
             // Retrieve the app delegate
         }];
}
- (void) logout{
    if (FBSession.activeSession.state == FBSessionStateOpen
        || FBSession.activeSession.state == FBSessionStateOpenTokenExtended) {
        
        // Close the session and remove the access token from the cache
        // The session state handler (in the app delegate) will be called automatically
        [FBSession.activeSession closeAndClearTokenInformation];
        
        // If the session state is not any of the two "open" states when the button is clicked
    }
}
- (BOOL) isLogined{
    return _isLogin;
}
-(NSString *)getUserID{
    return _userId;
}
- (BOOL) isLoggedIn{
    return _isLogin;
}

-(NSString *) getPermissionList{
    NSString *msg;
    if(FBSession.activeSession.state != FBSessionStateOpen && FBSession.activeSession.state != FBSessionStateOpenTokenExtended){
        msg =[ParseUtils MakeJsonStringWithObject:@"session closed please login first" andKey:@"error_message"];
    }else{
        NSArray *permissionList =  [FBSession.activeSession permissions];
        msg = [ParseUtils MakeJsonStringWithObject:permissionList andKey:@"permissions"];
    }
    return msg;
}
-(NSString *)getAccessToken{
    return _accessToken;
}
- (NSString*) getSessionID{
    return @"";
}
- (void) setDebugMode: (BOOL) debug{
    __debug = debug;
}
- (NSString*) getSDKVersion{
    return [FBSettings sdkVersion];
}
- (void) setSDKVersion: (NSString *)sdkVersion{
    [FBSettings setSDKVersion:sdkVersion];
}
- (NSString*) getPluginVersion{
    return @"";
}
-(void)activateApp{
    [FBAppEvents activateApp];
}
-(void)logEventWithName:(NSString*) eventName{
    [FBAppEvents logEvent:eventName];
}
-(void)logEvent:(NSMutableDictionary*) logInfo{
    if(logInfo.count == 2){
        NSString *eventName = [logInfo objectForKey:@"Param1"];
        id  param2 = [logInfo objectForKey:@"Param2"];
        if([param2 isKindOfClass:[NSDictionary class]]){
            NSDictionary *dic = (NSDictionary *)param2;
            [FBAppEvents logEvent:eventName parameters:dic];
        }else{
            double floatval = [[logInfo objectForKey:@"Param2"] floatValue];
            [FBAppEvents logEvent:eventName valueToSum:floatval];
        }
    }else if(logInfo.count == 3){
        NSString *eventName = [logInfo objectForKey:@"Param1"];
        double floatval = [[logInfo objectForKey:@"Param2"] floatValue];
        NSDictionary *para = [logInfo objectForKey:@"Param3"];
        [FBAppEvents logEvent:eventName valueToSum:floatval parameters:para];
    }
}
-(void)sessionStateChanged:(FBSession *)session state:(FBSessionState) state error:(NSError *)error{
    // If the session was opened successfully
    if (!error && state == FBSessionStateOpen){
        _accessToken = session.accessTokenData.accessToken;
        OUTPUT_LOG(@"Session opened");
        
        [FBRequestConnection startForMeWithCompletionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
            if (!error) {
                NSDictionary *dic = (NSDictionary *)result;
                _userId = [dic objectForKey:@"id"];
                _isLogin = true;
                NSMutableDictionary *result = [NSMutableDictionary dictionaryWithObjectsAndKeys:[FBSession.activeSession permissions],@"permissions",session.accessTokenData.accessToken,@"accessToken", nil];
                NSString *msg = [ParseUtils NSDictionaryToNSString:result];
                [UserWrapper onActionResult:self withRet:kLoginSucceed withMsg:msg];
            } else {
                NSString *msg = [ParseUtils MakeJsonStringWithObject:@"loginFailed" andKey:@"error_message"];
                [UserWrapper onActionResult:self withRet:kLoginFailed withMsg:msg];
            }
        }];
        
    }
    if (state == FBSessionStateClosed || state == FBSessionStateClosedLoginFailed){
        NSString *msg = [ParseUtils MakeJsonStringWithObject:@"loginFail Session closed" andKey:@"error_message"];
        if(!_isLogin){
            [UserWrapper onActionResult:self withRet:kLoginFailed withMsg:msg];
        }
        _isLogin = false;
        OUTPUT_LOG(@"Session closed");
    }
    
    // Handle errors
    if (error){
        _isLogin = false;
        NSString *errorText = @"";
        if ([FBErrorUtility shouldNotifyUserForError:error] == YES){
            errorText = [FBErrorUtility userMessageForError:error];
        } else {
            if ([FBErrorUtility errorCategoryForError:error] == FBErrorCategoryUserCancelled) {
                OUTPUT_LOG(@"User cancelled login");
            } else if ([FBErrorUtility errorCategoryForError:error] == FBErrorCategoryAuthenticationReopenSession){
                errorText = @"Your current session is no longer valid. Please log in again.";
            } else {
                NSDictionary *errorInformation = [[[error.userInfo objectForKey:@"com.facebook.sdk:ParsedJSONResponseKey"] objectForKey:@"body"] objectForKey:@"error"];
                errorText = [NSString stringWithFormat:@"Please retry. \n\n If the problem persists contact us and mention this error code: %@", [errorInformation objectForKey:@"message"]];
            }
        }
        errorText = [ParseUtils MakeJsonStringWithObject:errorText andKey:@"error_message"];
        [UserWrapper onActionResult:self withRet:kLoginFailed withMsg:errorText];
        OUTPUT_LOG(errorText);
        [FBSession.activeSession closeAndClearTokenInformation];
    }
}
-(void)requestPermissions:(NSString *)permision{
    if(FBSession.activeSession.state != FBSessionStateOpen && FBSession.activeSession.state != FBSessionStateOpenTokenExtended){
        NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Session closed please login first" andKey:@"error_message"];
        [UserWrapper onPermissionsResult:self withRet:kPermissionFailed withMsg:msg];
        return;
    }
    NSArray *permission = [permision componentsSeparatedByString:@","];
    [FBSession.activeSession requestNewReadPermissions:permission
                                     completionHandler:^(FBSession *session, NSError *error) {
                                         if (!error) {
                                             // Permission granted
                                             OUTPUT_LOG(@"new permissions %@", [FBSession.activeSession permissions]);
                                             NSString *msg =[ParseUtils MakeJsonStringWithObject:[FBSession.activeSession permissions] andKey:@"permissions"];
                                             if(msg!=nil){
                                                 [UserWrapper onPermissionsResult:self withRet:kPermissionSucceed withMsg:msg];
                                             }else{
                                                 msg = [ParseUtils MakeJsonStringWithObject:@"parse permission data fail" andKey:@"error_message"];
                                                 [UserWrapper onPermissionsResult:self withRet:kPermissionFailed withMsg:msg];
                                             }
                                             // We can request the user information
                                         } else {
                                             // An error occurred, we need to handle the error
                                             // Check out our error handling guide: https://developers.facebook.com/docs/ios/errors/
                                              NSString *msg = [ParseUtils MakeJsonStringWithObject:error.description andKey:@"error_message"];
                                             [UserWrapper onPermissionsResult:self withRet:(int)error.code withMsg:msg];
                                             OUTPUT_LOG(@"error %@", msg);
                                         }
                                     }];
}

-(void)api:(NSMutableDictionary *)params{
    NSString *graphPath = [params objectForKey:@"Param1"];
    int methodID = [[params objectForKey:@"Param2"] intValue];
    NSString * method = methodID == 0? @"GET":methodID == 1?@"POST":@"DELETE";
    NSDictionary *param = [params objectForKey:@"Param3"];
    int cbId = [[params objectForKey:@"Param4"] intValue];
    [FBRequestConnection startWithGraphPath:graphPath
                                 parameters:param HTTPMethod:method
                          completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
                              if(!error){
                                  NSString *msg = [ParseUtils NSDictionaryToNSString:(NSDictionary *)result];
                                  if(nil == msg){
                                       NSString *msg = [ParseUtils MakeJsonStringWithObject:@"parse result failed" andKey:@"error_message"];
                                      [UserWrapper onGraphResult:self withRet:kGraphResultFail withMsg:msg withCallback:cbId];
                                  }else{
                                      OUTPUT_LOG(@"success");
                                      [UserWrapper onGraphResult:self withRet:kGraphResultSuccess withMsg:msg withCallback:cbId];
                                  }
                              }else{
                                   NSString *msg = [ParseUtils MakeJsonStringWithObject:error.description andKey:@"error_message"];
                                  [UserWrapper onGraphResult:self withRet:(int)error.code withMsg:msg withCallback:cbId];
                                  OUTPUT_LOG(@"error %@", error.description);
                              }
                              
                          }];
}
-(void)logPurchase:(NSMutableDictionary *)purchaseInfo{
    if(purchaseInfo.count == 2){
        NSNumber *count = [purchaseInfo objectForKey:@"Param1"];
        NSString *currency = [purchaseInfo objectForKey:@"Param2"];
        [FBAppEvents logPurchase:[count floatValue] currency:currency];
    }else if(purchaseInfo.count == 3){
        NSNumber *count = [purchaseInfo objectForKey:@"Param1"];
        NSString *currency = [purchaseInfo objectForKey:@"Param2"];
        NSDictionary *dict = [purchaseInfo objectForKey:@"Param3"];
        [FBAppEvents logPurchase:[count floatValue] currency:currency parameters:dict];
    }
}
@end
