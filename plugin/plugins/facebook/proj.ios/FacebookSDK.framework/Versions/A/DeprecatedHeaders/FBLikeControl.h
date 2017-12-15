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

#import <UIKit/UIKit.h>

#import "FBSDKMacros.h"

/*!
 @typedef NS_ENUM (NSUInteger, FBLikeControlAuxiliaryPosition)

 @abstract Specifies the position of the auxiliary view relative to the like button.
 */
typedef NS_ENUM(NSUInteger, FBLikeControlAuxiliaryPosition)
{
    /*! The auxiliary view is inline with the like button. */
    FBLikeControlAuxiliaryPositionInline,
    /*! The auxiliary view is above the like button. */
    FBLikeControlAuxiliaryPositionTop,
    /*! The auxiliary view is below the like button. */
    FBLikeControlAuxiliaryPositionBottom,
};

/*!
 @abstract Converts an FBLikeControlAuxiliaryPosition to an NSString.
 */
FBSDK_EXTERN NSString *NSStringFromFBLikeControlAuxiliaryPosition(FBLikeControlAuxiliaryPosition auxiliaryPosition);

/*!
 @typedef NS_ENUM(NSUInteger, FBLikeControlHorizontalAlignment)

 @abstract Specifies the horizontal alignment for FBLikeControlStyleStandard with
 FBLikeControlAuxiliaryPositionTop or FBLikeControlAuxiliaryPositionBottom.
 */
typedef NS_ENUM(NSUInteger, FBLikeControlHorizontalAlignment)
{
    /*! The subviews are left aligned. */
    FBLikeControlHorizontalAlignmentLeft,
    /*! The subviews are center aligned. */
    FBLikeControlHorizontalAlignmentCenter,
    /*! The subviews are right aligned. */
    FBLikeControlHorizontalAlignmentRight,
};

/*!
 @abstract Converts an FBLikeControlHorizontalAlignment to an NSString.
 */
FBSDK_EXTERN NSString *NSStringFromFBLikeControlHorizontalAlignment(FBLikeControlHorizontalAlignment horizontalAlignment);

/*!
 @typedef NS_ENUM (NSUInteger, FBLikeControlStyle)

 @abstract Specifies the style of a like control.
 */
typedef NS_ENUM(NSUInteger, FBLikeControlStyle)
{
    /*! Displays the button and the social sentence. */
    FBLikeControlStyleStandard = 0,
    /*! Displays the button and a box that contains the like count. */
    FBLikeControlStyleBoxCount,
    /*! Displays the button only. */
    FBLikeControlStyleButton,
};

/*!
 @abstract Converts an FBLikeControlStyle to an NSString.
 */
FBSDK_EXTERN NSString *NSStringFromFBLikeControlStyle(FBLikeControlStyle style);

/*!
 @class FBLikeControl

 @abstract UI control to like an object in the Facebook graph.

 @discussion Taps on the like button within this control will invoke an API call to the Facebook app through a
 fast-app-switch that allows the user to like the object.  Upon return to the calling app, the view will update
 with the new state and send actions for the UIControlEventValueChanged event.
 */
@interface FBLikeControl : UIControl

/*!
 @abstract If YES, FBLikeControl is available for use with through the Like Dialog.

 @discussion If NO, the control requires publish_action permissions on the active session for in-place liking.  It is
 the responsibility of the consumer to ensure that the control is not presented without this permission.
 */
+ (BOOL)dialogIsAvailable;

/*!
 @abstract The foreground color to use for the content of the receiver.
 */
@property (nonatomic, strong) UIColor *foregroundColor;

/*!
 @abstract The position for the auxiliary view for the receiver.

 @see FBLikeControlAuxiliaryPosition
 */
@property (nonatomic, assign) FBLikeControlAuxiliaryPosition likeControlAuxiliaryPosition;

/*!
 @abstract The text alignment of the social sentence.

 @discussion This value is only valid for FBLikeControlStyleStandard with FBLikeControlAuxiliaryPositionTop|Bottom.
 */
@property (nonatomic, assign) FBLikeControlHorizontalAlignment likeControlHorizontalAlignment;

/*!
 @abstract The style to use for the receiver.

 @see FBLikeControlStyle
 */
@property (nonatomic, assign) FBLikeControlStyle likeControlStyle;

/*!
 @abstract The objectID for the object to like.

 @discussion This value may be an Open Graph object ID or a string representation of an URL that describes an
 Open Graph object.  The objects may be public objects, like pages, or objects that are defined by your application.
 */
@property (nonatomic, copy) NSString *objectID;

/*!
 @abstract The preferred maximum width (in points) for autolayout.

 @discussion This property affects the size of the receiver when layout constraints are applied to it. During layout,
 if the text extends beyond the width specified by this property, the additional text is flowed to one or more new
 lines, thereby increasing the height of the receiver.
 */
@property (nonatomic, assign) CGFloat preferredMaxLayoutWidth;

/*!
 @abstract If YES, a sound is played when the receiver is toggled.

 @default YES
 */
@property (nonatomic, assign, getter = isSoundEnabled) BOOL soundEnabled;

@end
