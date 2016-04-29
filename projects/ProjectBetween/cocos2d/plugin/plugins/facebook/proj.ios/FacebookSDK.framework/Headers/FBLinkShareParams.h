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
 @class FBLinkShareParams

 @abstract
 This object is used to encapsulate state for parameters to a share a link,
 typically with the Facebook Native Share Dialog or the Message Dialog.
 */
@interface FBLinkShareParams : FBDialogsParams

/*! @abstract The URL link to be attached to the post. Only "http" or "https"
 schemes are supported. */
@property (nonatomic, copy) NSURL *link;

/*! @abstract The name, or title associated with the link. Is only used if the
 link is non-nil. */
@property (nonatomic, copy) NSString *name;

/*! @abstract The caption to be used with the link. Is only used if the link is
 non-nil. */
@property (nonatomic, copy) NSString *caption;

/*! @abstract The description associated with the link. Is only used if the
 link is non-nil. */
@property (nonatomic, copy) NSString *linkDescription;

/*! @abstract The link to a thumbnail to associate with the post. Is only used
 if the link is non-nil. Only "http" or "https" schemes are supported. Note that this
 property should not be used to share photos; see the photos property. */
@property (nonatomic, copy) NSURL *picture;

/*! @abstract An array of NSStrings or FBGraphUsers to tag in the post.
 If using NSStrings, the values must represent the IDs of the users to tag. */
@property (nonatomic, copy) NSArray *friends;

/*! @abstract An NSString or FBGraphPlace to tag in the status update. If
 NSString, the value must be the ID of the place to tag. */
@property (nonatomic, copy) id place;

/*! @abstract A text reference for the category of the post, used on Facebook
 Insights. */
@property (nonatomic, copy) NSString *ref;

/*! @abstract If YES, treats any data failures (e.g. failures when getting
 data for IDs passed through "friends" or "place") as a fatal error, and will not
 continue with the status update. */
@property (nonatomic, assign) BOOL dataFailuresFatal;

/*!
 @abstract Designated initializer
 @param link the required link to share
 @param name the optional name to describe the share
 @param caption the optional caption to describe the share
 @param description the optional description to describe the share
 @param picture the optional url to use as the share's image
*/
- (instancetype)initWithLink:(NSURL *)link
                        name:(NSString *)name
                     caption:(NSString *)caption
                 description:(NSString *)description
                     picture:(NSURL *)picture;
@end
