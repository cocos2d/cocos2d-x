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


#import "FBDialog.h"

@protocol FBLoginDialogDelegate;

/**
 * Do not use this interface directly, instead, use authorize in Facebook.h
 *
 * Facebook Login Dialog interface for start the facebook webView login dialog.
 * It start pop-ups prompting for credentials and permissions.
 */

@interface FBLoginDialog : FBDialog

- (instancetype)initWithURL:(NSString *)loginURL
                loginParams:(NSMutableDictionary *)params
                   delegate:(id<FBLoginDialogDelegate>)loginDelegate;

@property (nonatomic, assign) id<FBLoginDialogDelegate> loginDelegate;

@end

///////////////////////////////////////////////////////////////////////////////////////////////////

@protocol FBLoginDialogDelegate <NSObject>

- (void)fbDialogLogin:(NSString *)token expirationDate:(NSDate *)expirationDate params:(NSDictionary *)params;

- (void)fbDialogNotLogin:(BOOL)cancelled;

@end


