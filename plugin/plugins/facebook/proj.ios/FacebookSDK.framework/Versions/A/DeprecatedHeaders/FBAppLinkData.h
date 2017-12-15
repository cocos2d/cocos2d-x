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

/*!
 @abstract This class contains information that represents an App Link from Facebook.
 */
@interface FBAppLinkData : NSObject

/*! @abstract The target */
@property (readonly) NSURL *targetURL;

/*! @abstract List of the types of actions for this target */
@property (readonly) NSArray *actionTypes;

/*! @abstract List of the ids of the actions for this target */
@property (readonly) NSArray *actionIDs;

/*! @abstract Reference breadcrumb provided during creation of story */
@property (readonly) NSString *ref;

/*! @abstract User Agent string set by the referer */
@property (readonly) NSString *userAgent;

/*! @abstract Referer data is a JSON object set by the referer with referer-specific content */
@property (readonly) NSDictionary *refererData;

/*! @abstract Full set of query parameters for this app link */
@property (readonly) NSDictionary *originalQueryParameters;

/*! @abstract Original url from which applinkData was extracted */
@property (readonly) NSURL *originalURL;

/*! @abstract Addtional arguments supplied with the App Link data. */
@property (readonly) NSDictionary *arguments;

@end
