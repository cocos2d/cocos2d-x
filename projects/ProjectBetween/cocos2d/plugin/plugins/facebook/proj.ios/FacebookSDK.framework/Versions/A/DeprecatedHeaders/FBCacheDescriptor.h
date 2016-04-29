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
 @class

 @abstract
 Base class from which CacheDescriptors derive, provides a method to fetch data for later use

 @discussion
 Cache descriptors allow your application to specify the arguments that will be
 later used with another object, such as the FBFriendPickerViewController. By using a cache descriptor
 instance, an application can choose to fetch data ahead of the point in time where the data is needed.
 */
@interface FBCacheDescriptor : NSObject

/*!
 @method
 @abstract
 Fetches and caches the data described by the cache descriptor instance, for the given session.

 @param session     the <FBSession> to use for fetching data
 */
- (void)prefetchAndCacheForSession:(FBSession *)session;

@end
