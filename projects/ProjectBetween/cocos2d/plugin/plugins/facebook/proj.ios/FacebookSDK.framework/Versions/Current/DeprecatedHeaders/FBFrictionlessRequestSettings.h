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

@class FBRequest;
@class Facebook;

/**
 * Do not use this interface directly, instead, use methods in Facebook.h
 *
 * Handles frictionless interaction and recipient-caching by the SDK,
 * see https://developers.facebook.com/docs/reference/dialogs/requests/
 */
@interface FBFrictionlessRequestSettings : NSObject {
@private
    NSArray *_allowedRecipients;
    FBRequest *_activeRequest;
    BOOL _enabled;
}

/**
 * BOOL indicating whether frictionless request sending has been enabled
 */
@property (nonatomic, readonly) BOOL enabled;

/**
 * NSArray of recipients
 */
@property (nonatomic, readonly) NSArray *recipientIDs;

/**
 * Enable frictionless request sending by the sdk; this means:
 *   1. query and cache the current set of frictionless recipients
 *   2. flag other facets of the sdk to behave in a frictionless way
 */
- (void)enableWithFacebook:(Facebook *)facebook;

/**
 * Reload recipient cache; called by the sdk to keep the cache fresh;
 * method makes graph request: me/apprequestformerrecipients
 */
- (void)reloadRecipientCacheWithFacebook:(Facebook *)facebook;

/**
 * Update the recipient cache; called by the sdk to keep the cache fresh;
 */
- (void)updateRecipientCacheWithRecipients:(NSArray *)ids;

/**
 * Update the recipient cache, using a request result
 */
- (void)updateRecipientCacheWithRequestResult:(id)result;

/**
 * Given an fbID for a user, indicates whether user is enabled for
 * frictionless calls
 */
- (BOOL)isFrictionlessEnabledForRecipient:(id)fbid;

/**
 * Given an array of user fbIDs, indicates whether they are enabled for
 * frictionless calls
 */
- (BOOL)isFrictionlessEnabledForRecipients:(NSArray *)fbids;

@end
