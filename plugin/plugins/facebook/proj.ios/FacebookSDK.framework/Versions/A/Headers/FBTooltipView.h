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

/*!
 @typedef FBTooltipViewArrowDirection enum

 @abstract
 Passed on construction to determine arrow orientation.
 */
typedef NS_ENUM(NSUInteger, FBTooltipViewArrowDirection) {
    /*! View is located above given point, arrow is pointing down. */
    FBTooltipViewArrowDirectionDown = 0,
    /*! View is located below given point, arrow is pointing up. */
    FBTooltipViewArrowDirectionUp = 1,
};

/*!
 @typedef FBTooltipColorStyle enum

 @abstract
 Passed on construction to determine color styling.
 */
typedef NS_ENUM(NSUInteger, FBTooltipColorStyle) {
    /*! Light blue background, white text, faded blue close button. */
    FBTooltipColorStyleFriendlyBlue = 0,
    /*! Dark gray background, white text, light gray close button. */
    FBTooltipColorStyleNeutralGray = 1,
};

/*!
 @class FBTooltipView

 @abstract
 Tooltip bubble with text in it used to display tips for UI elements,
 with a pointed arrow (to refer to the UI element).

 @discussion
 The tooltip fades in and will automatically fade out. See `displayDuration`.
 */
@interface FBTooltipView : UIView

/*!
 @abstract Gets or sets the amount of time in seconds the tooltip should be displayed.
 @discussion Set this to zero to make the display permanent until explicitly dismissed.
 Defaults to six seconds.
*/
@property (nonatomic, assign) CFTimeInterval displayDuration;

/*!
 @abstract Gets or sets the color style after initialization.
 @discussion Defaults to value passed to -initWithTagline:message:colorStyle:.
 */
@property (nonatomic, assign) FBTooltipColorStyle colorStyle;

/*!
 @abstract Gets or sets the message.
*/
@property (nonatomic, copy) NSString *message;

/*!
 @abstract Gets or sets the optional phrase that comprises the first part of the label (and is highlighted differently).
*/
@property (nonatomic, copy) NSString *tagline;

/*!
 @abstract
 Designated initializer.

 @param tagline First part of the label, that will be highlighted with different color. Can be nil.

 @param message Main message to display.

 @param colorStyle Color style to use for tooltip.

 @discussion
 If you need to show a tooltip for login, consider using the `FBLoginTooltipView` view.

 @see FBLoginTooltipView
 */
- (id)initWithTagline:(NSString *)tagline message:(NSString *)message colorStyle:(FBTooltipColorStyle)colorStyle;

/*!
 @abstract
 Show tooltip at the top or at the bottom of given view.
 Tooltip will be added to anchorView.window.rootViewController.view

 @param anchorView view to show at, must be already added to window view hierarchy, in order to decide
 where tooltip will be shown. (If there's not enough space at the top of the anchorView in window bounds -
 tooltip will be shown at the bottom of it)

 @discussion
 Use this method to present the tooltip with automatic positioning or
 use -presentInView:withArrowPosition:direction: for manual positioning
 If anchorView is nil or has no window - this method does nothing.
 */
- (void)presentFromView:(UIView *)anchorView;

/*!
 @abstract
 Adds tooltip to given view, with given position and arrow direction.

 @param view View to be used as superview.

 @param arrowPosition Point in view's cordinates, where arrow will be pointing

 @param arrowDirection whenever arrow should be pointing up (message bubble is below the arrow) or
 down (message bubble is above the arrow).
 */
- (void)presentInView:(UIView *)view withArrowPosition:(CGPoint)arrowPosition direction:(FBTooltipViewArrowDirection)arrowDirection;

/*!
 @abstract
 Remove tooltip manually.

 @discussion
 Calling this method isn't necessary - tooltip will dismiss itself automatically after the `displayDuration`.
 */
- (void)dismiss;

@end
