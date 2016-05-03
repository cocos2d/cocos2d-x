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

#import "FBAccessTokenData.h"
#import "FBSDKMacros.h"

/*!
 @class

 @abstract
 The `FBSessionTokenCachingStrategy` class is responsible for persisting and retrieving cached data related to
 an <FBSession> object, including the user's Facebook access token.

 @discussion
 `FBSessionTokenCachingStrategy` is designed to be instantiated directly or used as a base class. Usually default
 token caching behavior is sufficient, and you do not need to interface directly with `FBSessionTokenCachingStrategy` objects.
 However, if you need to control where or how `FBSession` information is cached, then you may take one of two approaches.

 The first and simplest approach is to instantiate an instance of `FBSessionTokenCachingStrategy`, and then pass
 the instance to `FBSession` class' `init` method. This enables your application to control the key name used in
 the iOS Keychain to store session information. You may consider this approach if you plan to cache session information
 for multiple users.

 The second and more advanced approached is to derive a custom class from `FBSessionTokenCachingStrategy`, which will
 be responsible for caching behavior of your application. This approach is useful if you need to change where the
 information is cached, for example if you prefer to use the filesystem or make a network connection to fetch and
 persist cached tokens.  Inheritors should override the cacheTokenInformation, fetchTokenInformation, and clearToken methods.
 Doing this enables your application to implement any token caching scheme, including no caching at all (see
 `[FBSessionTokenCachingStrategy nullCacheInstance]`.

 Direct use of `FBSessionTokenCachingStrategy`is an advanced technique. Most applications use <FBSession> objects without
 passing an `FBSessionTokenCachingStrategy`, which yields default caching to the iOS Keychain.
 */
@interface FBSessionTokenCachingStrategy : NSObject

/*!
 @abstract Initializes and returns an instance
 */
- (instancetype)init;

/*!
 @abstract
 Initializes and returns an instance

 @param tokenInformationKeyName     Specifies a key name to use for cached token information in the iOS Keychain, nil
 indicates a default value of @"FBAccessTokenInformationKey"
 */
- (instancetype)initWithUserDefaultTokenInformationKeyName:(NSString *)tokenInformationKeyName;

/*!
 @abstract
 Called by <FBSession> (and overridden by inheritors), in order to cache token information.

 @param tokenInformation            Dictionary containing token information to be cached by the method
 @discussion You should favor overriding this instead of `cacheFBAccessTokenData` only if you intend
 to cache additional data not captured by the FBAccessTokenData type.
 */
- (void)cacheTokenInformation:(NSDictionary *)tokenInformation;

/*!
 @abstract Cache the supplied token.
 @param accessToken The token instance.
 @discussion This essentially wraps a call to `cacheTokenInformation` so you should
 override this when providing a custom token caching strategy.
 */
- (void)cacheFBAccessTokenData:(FBAccessTokenData *)accessToken;

/*!
 @abstract
 Called by <FBSession> (and overridden by inheritors), in order to fetch cached token information

 @discussion
 An overriding implementation should only return a token if it
 can also return an expiration date, otherwise return nil.
 You should favor overriding this instead of `fetchFBAccessTokenData` only if you intend
 to cache additional data not captured by the FBAccessTokenData type.

 */
- (NSDictionary *)fetchTokenInformation;

/*!
 @abstract
 Fetches the cached token instance.

 @discussion
 This essentially wraps a call to `fetchTokenInformation` so you should
 override this when providing a custom token caching strategy.

 In order for an `FBSession` instance to be able to use a cached token,
 the token must be not be expired (see `+isValidTokenInformation:`) and
 must also contain all permissions in the initialized session instance.
 */
- (FBAccessTokenData *)fetchFBAccessTokenData;

/*!
 @abstract
 Called by <FBSession> (and overridden by inheritors), in order delete any cached information for the current token
 */
- (void)clearToken;

/*!
 @abstract
 Helper function called by the SDK as well as apps, in order to fetch the default strategy instance.
 */
+ (FBSessionTokenCachingStrategy *)defaultInstance;

/*!
 @abstract
 Helper function to return a FBSessionTokenCachingStrategy instance that does not perform any caching.
 */
+ (FBSessionTokenCachingStrategy *)nullCacheInstance;

/*!
 @abstract
 Helper function called by the SDK as well as application code, used to determine whether a given dictionary
 contains the minimum token information usable by the <FBSession>.

 @param tokenInformation            Dictionary containing token information to be validated
 */
+ (BOOL)isValidTokenInformation:(NSDictionary *)tokenInformation;

@end

// The key to use with token information dictionaries to get and set the token value
FBSDK_EXTERN NSString *const FBTokenInformationTokenKey;

// The to use with token information dictionaries to get and set the expiration date
FBSDK_EXTERN NSString *const FBTokenInformationExpirationDateKey;

// The to use with token information dictionaries to get and set the refresh date
FBSDK_EXTERN NSString *const FBTokenInformationRefreshDateKey;

// The key to use with token information dictionaries to get the related user's fbid
FBSDK_EXTERN NSString *const FBTokenInformationUserFBIDKey;

// The key to use with token information dictionaries to determine whether the token was fetched via Facebook Login
FBSDK_EXTERN NSString *const FBTokenInformationIsFacebookLoginKey;

// The key to use with token information dictionaries to determine whether the token was fetched via the OS
FBSDK_EXTERN NSString *const FBTokenInformationLoginTypeLoginKey;

// The key to use with token information dictionaries to get the latest known permissions
FBSDK_EXTERN NSString *const FBTokenInformationPermissionsKey;

// The key to use with token information dictionaries to get the latest known declined permissions
FBSDK_EXTERN NSString *const FBTokenInformationDeclinedPermissionsKey;

// The key to use with token information dictionaries to get the date the permissions were last refreshed.
FBSDK_EXTERN NSString *const FBTokenInformationPermissionsRefreshDateKey;

// The key to use with token information dictionaries to get the id of the creator app
FBSDK_EXTERN NSString *const FBTokenInformationAppIDKey;
