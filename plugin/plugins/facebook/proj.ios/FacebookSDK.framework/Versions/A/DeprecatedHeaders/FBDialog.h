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
#import <UIKit/UIKit.h>

@protocol FBDialogDelegate;
@class FBFrictionlessRequestSettings;

/**
 * Do not use this interface directly, instead, use dialog in Facebook.h
 *
 * Facebook dialog interface for start the facebook webView UIServer Dialog.
 */

@interface FBDialog : UIView <UIWebViewDelegate> {
    id<FBDialogDelegate> _delegate;
    NSMutableDictionary *_params;
    NSString *_serverURL;
    NSURL *_loadingURL;
    UIWebView *_webView;
    UIActivityIndicatorView *_spinner;
    UIButton *_closeButton;
    UIInterfaceOrientation _orientation;
    BOOL _showingKeyboard;
    BOOL _isViewInvisible;
    FBFrictionlessRequestSettings *_frictionlessSettings;

    // Ensures that UI elements behind the dialog are disabled.
    UIView *_modalBackgroundView;
}

/**
 * The delegate.
 */
@property (nonatomic, assign) id<FBDialogDelegate> delegate;

/**
 * The parameters.
 */
@property (nonatomic, retain) NSMutableDictionary *params;

- (NSString *)getStringFromUrl:(NSString *)url needle:(NSString *)needle;

- (id)      initWithURL:(NSString *)loadingURL
                 params:(NSMutableDictionary *)params
        isViewInvisible:(BOOL)isViewInvisible
   frictionlessSettings:(FBFrictionlessRequestSettings *)frictionlessSettings
               delegate:(id<FBDialogDelegate>)delegate;

/**
 * Displays the view with an animation.
 *
 * The view will be added to the top of the current key window.
 */
- (void)show;

/**
 * Displays the first page of the dialog.
 *
 * Do not ever call this directly.  It is intended to be overriden by subclasses.
 */
- (void)load;

/**
 * Displays a URL in the dialog.
 */
- (void)loadURL:(NSString *)url
            get:(NSDictionary *)getParams;

/**
 * Hides the view and notifies delegates of success or cancellation.
 */
- (void)dismissWithSuccess:(BOOL)success animated:(BOOL)animated;

/**
 * Hides the view and notifies delegates of an error.
 */
- (void)dismissWithError:(NSError *)error animated:(BOOL)animated;

/**
 * Subclasses may override to perform actions just prior to showing the dialog.
 */
- (void)dialogWillAppear;

/**
 * Subclasses may override to perform actions just after the dialog is hidden.
 */
- (void)dialogWillDisappear;

/**
 * Subclasses should override to process data returned from the server in a 'fbconnect' url.
 *
 * Implementations must call dismissWithSuccess:YES at some point to hide the dialog.
 */
- (void)dialogDidSucceed:(NSURL *)url;

/**
 * Subclasses should override to process data returned from the server in a 'fbconnect' url.
 *
 * Implementations must call dismissWithSuccess:YES at some point to hide the dialog.
 */
- (void)dialogDidCancel:(NSURL *)url;
@end

///////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *Your application should implement this delegate
 */
@protocol FBDialogDelegate <NSObject>

@optional

/**
 * Called when the dialog succeeds and is about to be dismissed.
 */
- (void)dialogDidComplete:(FBDialog *)dialog;

/**
 * Called when the dialog succeeds with a returning url.
 */
- (void)dialogCompleteWithUrl:(NSURL *)url;

/**
 * Called when the dialog get canceled by the user.
 */
- (void)dialogDidNotCompleteWithUrl:(NSURL *)url;

/**
 * Called when the dialog is cancelled and is about to be dismissed.
 */
- (void)dialogDidNotComplete:(FBDialog *)dialog;

/**
 * Called when dialog failed to load due to an error.
 */
- (void)dialog:(FBDialog *)dialog didFailWithError:(NSError *)error;

/**
 * Asks if a link touched by a user should be opened in an external browser.
 *
 * If a user touches a link, the default behavior is to open the link in the Safari browser,
 * which will cause your app to quit.  You may want to prevent this from happening, open the link
 * in your own internal browser, or perhaps warn the user that they are about to leave your app.
 * If so, implement this method on your delegate and return NO.  If you warn the user, you
 * should hold onto the URL and once you have received their acknowledgement open the URL yourself
 * using [[UIApplication sharedApplication] openURL:].
 */
- (BOOL)dialog:(FBDialog *)dialog shouldOpenURLInExternalBrowser:(NSURL *)url;

@end
