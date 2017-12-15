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

@class FBViewController;

/*!
 @typedef FBModalCompletionHandler

 @abstract
 A block that is passed to [FBViewController presentModallyInViewController:animated:handler:]
 and called when the view controller is dismissed via either Done or Cancel.

 @param sender          The <FBViewController> that is being dismissed.

 @param donePressed     If YES, Done was pressed. If NO, Cancel was pressed.
 */
typedef void (^FBModalCompletionHandler)(FBViewController *sender, BOOL donePressed);

/*!
 @protocol

 @abstract
 The `FBViewControllerDelegate` protocol defines the methods called when the Cancel or Done
 buttons are pressed in a <FBViewController>.
 */
@protocol FBViewControllerDelegate <NSObject>

@optional

/*!
 @abstract
 Called when the Cancel button is pressed on a modally-presented <FBViewController>.

 @param sender          The view controller sending the message.
 */
- (void)facebookViewControllerCancelWasPressed:(id)sender;

/*!
 @abstract
 Called when the Done button is pressed on a modally-presented <FBViewController>.

 @param sender          The view controller sending the message.
 */
- (void)facebookViewControllerDoneWasPressed:(id)sender;

@end


/*!
 @class FBViewController

 @abstract
 The `FBViewController` class is a base class encapsulating functionality common to several
 other view controller classes. Specifically, it provides UI when a view controller is presented
 modally, in the form of optional Cancel and Done buttons.
 */
@interface FBViewController : UIViewController

/*!
 @abstract
 The Cancel button to display when presented modally. If nil, no Cancel button is displayed.
 If this button is provided, its target and action will be redirected to internal handlers, replacing
 any previous target that may have been set.
 */
@property (nonatomic, retain) IBOutlet UIBarButtonItem *cancelButton;

/*!
 @abstract
 The Done button to display when presented modally. If nil, no Done button is displayed.
 If this button is provided, its target and action will be redirected to internal handlers, replacing
 any previous target that may have been set.
 */
@property (nonatomic, retain) IBOutlet UIBarButtonItem *doneButton;

/*!
 @abstract
 The delegate that will be called when Cancel or Done is pressed. Derived classes may specify
 derived types for their delegates that provide additional functionality.
 */
@property (nonatomic, assign) IBOutlet id<FBViewControllerDelegate> delegate;

/*!
 @abstract
 The view into which derived classes should put their subviews. This view will be resized correctly
 depending on whether or not a toolbar is displayed.
 */
@property (nonatomic, readonly, retain) UIView *canvasView;

/*!
 @abstract
 Provides a wrapper that presents the view controller modally and automatically dismisses it
 when either the Done or Cancel button is pressed.

 @param viewController  The view controller that is presenting this view controller.
 @param animated        If YES, presenting and dismissing the view controller is animated.
 @param handler         The block called when the Done or Cancel button is pressed.
 */
- (void)presentModallyFromViewController:(UIViewController *)viewController
                                animated:(BOOL)animated
                                 handler:(FBModalCompletionHandler)handler;

@end

