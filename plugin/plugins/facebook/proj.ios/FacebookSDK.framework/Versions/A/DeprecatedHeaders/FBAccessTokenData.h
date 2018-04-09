/*
 * Copyright 2010-present Facebook.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>

#import "FBSession.h"

/*!
 @class FBAccessTokenData

 @abstract Represents an access token used for the Facebook login flow
 and includes associated metadata such as expiration date and permissions.
 You should use factory methods (createToken...) to construct instances
 and should be treated as immutable.

 @discussion For more information, see
 https://developers.facebook.com/docs/concepts/login/access-tokens-and-types/.
 */
@interface FBAccessTokenData : NSObject <NSCopying>

/*!
 @method

 @abstract Creates an FBAccessTokenData from an App Link provided by the Facebook application
 or nil if the url is not valid.

 @param url The url provided.
 @param appID needed in order to verify URL format.
 @param urlSchemeSuffix needed in order to verify URL format.

 */
+ (FBAccessTokenData *)createTokenFromFacebookURL:(NSURL *)url appID:(NSString *)appID urlSchemeSuffix:(NSString *)urlSchemeSuffix;

/*!
 @method

 @abstract Creates an FBAccessTokenData from a dictionary or returns nil if required data is missing.
 @param dictionary the dictionary with FBSessionTokenCachingStrategy keys.
 */
+ (FBAccessTokenData *)createTokenFromDictionary:(NSDictionary *)dictionary;

/*!
 @method

 @abstract Creates an FBAccessTokenData from existing information or returns nil if required data is missing.

 @param accessToken The token string. If nil or empty, this method will return nil.
 @param permissions The permissions set. A value of nil indicates basic permissions.
 @param expirationDate The expiration date. A value of nil defaults to `[NSDate distantFuture]`.
 @param loginType The login source of the token.
 @param refreshDate The date that token was last refreshed. A value of nil defaults to `[NSDate date]`.
 */
+ (FBAccessTokenData *)createTokenFromString:(NSString *)accessToken
                                 permissions:(NSArray *)permissions
                              expirationDate:(NSDate *)expirationDate
                                   loginType:(FBSessionLoginType)loginType
                                 refreshDate:(NSDate *)refreshDate;

/*!
 @method

 @abstract Creates an FBAccessTokenData from existing information or returns nil if required data is missing.

 @param accessToken The token string. If nil or empty, this method will return nil.
 @param permissions The permissions set. A value of nil indicates basic permissions.
 @param expirationDate The expiration date. A value of nil defaults to `[NSDate distantFuture]`.
 @param loginType The login source of the token.
 @param refreshDate The date that token was last refreshed. A value of nil defaults to `[NSDate date]`.
 @param permissionsRefreshDate The date the permissions were last refreshed. A value of nil defaults to `[NSDate distantPast]`.
 */
+ (FBAccessTokenData *)createTokenFromString:(NSString *)accessToken
                                 permissions:(NSArray *)permissions
                              expirationDate:(NSDate *)expirationDate
                                   loginType:(FBSessionLoginType)loginType
                                 refreshDate:(NSDate *)refreshDate
                      permissionsRefreshDate:(NSDate *)permissionsRefreshDate;

/*!
 @method

 @abstract Creates an FBAccessTokenData from existing information or returns nil if required data is missing.

 @param accessToken The token string. If nil or empty, this method will return nil.
 @param permissions The permissions set. A value of nil indicates basic permissions.
 @param expirationDate The expiration date. A value of nil defaults to `[NSDate distantFuture]`.
 @param loginType The login source of the token.
 @param refreshDate The date that token was last refreshed. A value of nil defaults to `[NSDate date]`.
 @param permissionsRefreshDate The date the permissions were last refreshed. A value of nil defaults to `[NSDate distantPast]`.
 @param appID The ID string of the calling app. A value of nil defaults to `[FBSettings defaultAppID]`.
 */
+ (FBAccessTokenData *)createTokenFromString:(NSString *)accessToken
                                 permissions:(NSArray *)permissions
                              expirationDate:(NSDate *)expirationDate
                                   loginType:(FBSessionLoginType)loginType
                                 refreshDate:(NSDate *)refreshDate
                      permissionsRefreshDate:(NSDate *)permissionsRefreshDate
                                       appID:(NSString *)appID;

/*!
 @method

 @abstract Designated factory method.
 Creates an FBAccessTokenData from existing information or returns nil if required data is missing.

 @param accessToken The token string. If nil or empty, this method will return nil.
 @param permissions The permissions set. A value of nil indicates basic permissions.
 @param declinedPermissions The declined permissions set. A value of nil indicates empty array.
 @param expirationDate The expiration date. A value of nil defaults to `[NSDate distantFuture]`.
 @param loginType The login source of the token.
 @param refreshDate The date that token was last refreshed. A value of nil defaults to `[NSDate date]`.
 @param permissionsRefreshDate The date the permissions were last refreshed. A value of nil defaults to `[NSDate distantPast]`.
 @param appID The ID string of the calling app. A value of nil defaults to `[FBSettings defaultAppID]`.
 */
+ (FBAccessTokenData *)createTokenFromString:(NSString *)accessToken
                                 permissions:(NSArray *)permissions
                         declinedPermissions:(NSArray *)declinedPermissions
                              expirationDate:(NSDate *)expirationDate
                                   loginType:(FBSessionLoginType)loginType
                                 refreshDate:(NSDate *)refreshDate
                      permissionsRefreshDate:(NSDate *)permissionsRefreshDate
                                       appID:(NSString *)appID
                                      userID:(NSString *)userID;

/*!
 @method

 @abstract Returns a dictionary representation of this instance.

 @discussion This is provided for backwards compatibility with previous
 access token related APIs that used a NSDictionary (see `FBSessionTokenCachingStrategy`).
 */
- (NSMutableDictionary *)dictionary;

/*!
 @method

 @abstract Returns a Boolean value that indicates whether a given object is an FBAccessTokenData object and exactly equal the receiver.

 @param accessTokenData the data to compare to the receiver.
 */
- (BOOL)isEqualToAccessTokenData:(FBAccessTokenData *)accessTokenData;

/*!
 @abstract returns the access token NSString.
 */
@property (readonly, nonatomic, copy) NSString *accessToken;

/*!
 @abstract returns the app ID NSString.
 */
@property (readonly, nonatomic, copy) NSString *appID;

/*!
 @abstract returns the user ID NSString that is associated with the token,if available.
 @discussion This may not be populated for login behaviours such as the iOS system account.
 */
@property (readonly, nonatomic, copy) NSString *userID;

/*!
 @abstract returns the permissions associated with the access token.
 */
@property (readonly, nonatomic, copy) NSArray *permissions;

/*!
 @abstract returns the declined permissions associated with the access token.
 */
@property (readonly, nonatomic, copy) NSArray *declinedPermissions;

/*!
 @abstract returns the expiration date of the access token.
 */
@property (readonly, nonatomic, copy) NSDate *expirationDate;

/*!
 @abstract returns the login type associated with the token.
 */
@property (readonly, nonatomic) FBSessionLoginType loginType;

/*!
 @abstract returns the date the token was last refreshed.
 */
@property (readonly, nonatomic, copy) NSDate *refreshDate;

/*!
 @abstract returns the date the permissions were last refreshed.
 */
@property (readonly, nonatomic, copy) NSDate *permissionsRefreshDate;

@end
