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

#import "FBDialogsParams.h"

/*!
 @class FBPhotoParams

 @abstract
 This object is used to encapsulate state for parameters to share photos,
 typically with the Facebook Native Share Dialog or Message Dialog
 */
@interface FBPhotoParams : FBDialogsParams

/*! @abstract An array of NSStrings or FBGraphUsers to tag in the post.
 If using NSStrings, the values must represent the IDs of the users to tag. */
@property (nonatomic, copy) NSArray *friends;

/*! @abstract An NSString or FBGraphPlace to tag in the status update. If
 NSString, the value must be the ID of the place to tag. */
@property (nonatomic, copy) id place;

/*! @abstract If YES, treats any data failures (e.g. failures when getting
 data for IDs passed through "friends" or "place") as a fatal error, and will not
 continue with the status update. */
@property (nonatomic, assign) BOOL dataFailuresFatal;

/*! @abstract An array of UIImages representing photos to be shared. Only
 six or fewer images are supported. */
@property (nonatomic, copy) NSArray *photos;

/*! @abstract Designated initializer.
 @param photos the array of UIImages
*/
- (instancetype)initWithPhotos:(NSArray *)photos;
@end
