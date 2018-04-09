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
 The `FBGraphLocation` protocol enables typed access to the `location` property
 of a Facebook place object.


 @discussion
 The `FBGraphLocation` protocol represents the most commonly used properties of a
 location object. It may be used to access an `NSDictionary` object that has
 been wrapped with an <FBGraphObject> facade.
 */
@protocol FBGraphLocation<FBGraphObject>

/*!
 @property
 @abstract Typed access to a location's street.
 */
@property (retain, nonatomic) NSString *street;

/*!
 @property
 @abstract Typed access to a location's city.
 */
@property (retain, nonatomic) NSString *city;

/*!
 @property
 @abstract Typed access to a location's state.
 */
@property (retain, nonatomic) NSString *state;

/*!
 @property
 @abstract Typed access to a location's country.
 */
@property (retain, nonatomic) NSString *country;

/*!
 @property
 @abstract Typed access to a location's zip code.
 */
@property (retain, nonatomic) NSString *zip;

/*!
 @property
 @abstract Typed access to a location's latitude.
 */
@property (retain, nonatomic) NSNumber *latitude;

/*!
 @property
 @abstract Typed access to a location's longitude.
 */
@property (retain, nonatomic) NSNumber *longitude;

@end
