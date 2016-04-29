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

#import "FBGraphObject.h"

/*!
 @protocol

 @abstract
 The `FBGraphPerson` protocol enables typed access to a person's name, photo
 and context-specific identifier as represented in the Graph API.


 @discussion
 The `FBGraphPerson` protocol provides access to the name, picture and context-specific
 ID of a person represented by a graph object. It may be used to access an `NSDictionary`
 object that has been wrapped with an <FBGraphObject> facade.
 */
@protocol FBGraphPerson<FBGraphObject>

/*!
 @property
 @abstract Typed access to the user ID.
 @discussion Note this typically refers to the "id" field of the graph object (i.e., equivalent
 to `[self objectForKey:@"id"]`) but is differently named to avoid conflicting with Apple's
 non-public selectors.
 */
@property (retain, nonatomic) NSString *objectID;

/*!
 @property
 @abstract Typed access to the user's name.
 */
@property (retain, nonatomic) NSString *name;

/*!
 @property
 @abstract Typed access to the user's first name.
 */
@property (retain, nonatomic) NSString *first_name;

/*!
 @property
 @abstract Typed access to the user's middle name.
 */
@property (retain, nonatomic) NSString *middle_name;

/*!
 @property
 @abstract Typed access to the user's last name.
 */
@property (retain, nonatomic) NSString *last_name;

@end
