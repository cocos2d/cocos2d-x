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

#import "FBTooltipView.h"

@protocol FBLoginTooltipViewDelegate;

/*!
 @class FBLoginTooltipView

 @abstract Represents a tooltip to be displayed next to a Facebook login button
  to highlight features for new users.

 @discussion The `FBLoginView` may display this view automatically. If you do
  not use the `FBLoginView`, you can manually call one of the `present*` methods
  as appropriate and customize behavior via `FBLoginTooltipViewDelegate` delegate.

  By default, the `FBLoginTooltipView` is not added to the superview until it is
  determined the app has migrated to the new login experience. You can override this
  (e.g., to test the UI layout) by implementing the delegate or setting `forceDisplay` to YES.

 */
@interface FBLoginTooltipView : FBTooltipView

/*! @abstract the delegate */
@property (nonatomic, assign) id<FBLoginTooltipViewDelegate> delegate;

/*! @abstract if set to YES, the view will always be displayed and the delegate's
  `loginTooltipView:shouldAppear:` will NOT be called. */
@property (nonatomic, assign) BOOL forceDisplay;

@end

/*!
 @protocol

 @abstract
 The `FBLoginTooltipViewDelegate` protocol defines the methods used to receive event
 notifications from `FBLoginTooltipView` objects.
 */
@protocol FBLoginTooltipViewDelegate <NSObject>

@optional

/*!
 @abstract
 Asks the delegate if the tooltip view should appear

 @param view The tooltip view.
 @param appIsEligible The value fetched from the server identifying if the app
 is eligible for the new login experience.

 @discussion Use this method to customize display behavior.
 */
- (BOOL)loginTooltipView:(FBLoginTooltipView *)view shouldAppear:(BOOL)appIsEligible;

/*!
 @abstract
 Tells the delegate the tooltip view will appear, specifically after it's been
 added to the super view but before the fade in animation.

 @param view The tooltip view.
 */
- (void)loginTooltipViewWillAppear:(FBLoginTooltipView *)view;

/*!
 @abstract
 Tells the delegate the tooltip view will not appear (i.e., was not
 added to the super view).

 @param view The tooltip view.
 */
- (void)loginTooltipViewWillNotAppear:(FBLoginTooltipView *)view;


@end

