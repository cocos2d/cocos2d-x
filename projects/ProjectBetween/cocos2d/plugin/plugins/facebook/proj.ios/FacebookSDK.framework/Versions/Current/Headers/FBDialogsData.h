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

/*!
 @abstract
 This class encapsulates state and data related to the presentation and completion
 of a dialog.
 */
@interface FBDialogsData : NSObject

/*! @abstract The method being performed */
@property (nonatomic, readonly) NSString *method;
/*! @abstract The arguments being passed to the entity that will show the dialog */
@property (nonatomic, readonly) NSDictionary *arguments;
/*! @abstract Client JSON state that is passed through to the completion handler for context */
@property (nonatomic, readonly) NSDictionary *clientState;
/*! @abstract Results of this FBAppCall that are only set before calling an FBAppCallHandler */
@property (nonatomic, readonly) NSDictionary *results;

@end
