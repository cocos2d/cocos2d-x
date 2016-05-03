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

#import <Bolts/BFAppLinkResolving.h>

/*!
 @class FBAppLinkResolver

 @abstract
 Provides an implementation of the BFAppLinkResolving protocol that uses the Facebook app link
 index to resolve App Links given a URL. It also provides an additional helper method that can resolve
 multiple App Links in a single call.

 @discussion
 Usage of this type requires a client token. See `[FBSettings setClientToken:]`.
 */
@interface FBAppLinkResolver : NSObject<BFAppLinkResolving>

/*!
 @abstract Asynchronously resolves App Link data for multiple URLs.

 @param urls An array of NSURLs to resolve into App Links.
 @returns A BFTask that will return dictionary mapping input NSURLs to their
  corresponding BFAppLink.

 @discussion
 You should set the client token before making this call. See `[FBSettings setClientToken:]`
 */
- (BFTask *)appLinksFromURLsInBackground:(NSArray *)urls;

/*!
 @abstract Allocates and initializes a new instance of FBAppLinkResolver.
 */
+ (instancetype)resolver;

@end
