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

#import "FBPeoplePickerViewController.h"

/*!
 @class

 @abstract
 The `FBTaggableFriendPickerViewController` class creates a controller object that
 manages the user interface for displaying and selecting taggable Facebook friends.

 @discussion
 When the `FBTaggableFriendPickerViewController` view loads it creates a `UITableView`
 object where the taggable friends will be displayed. You can access this view through
 the `tableView` property. The taggalb e friend display can be sorted by first name or
 last name. Taggable friends' names can be displayed with the first name first or the
 last name first.

 The `FBTaggableFriendPickerViewController` does not support the `fieldsForRequest`
 property, as there are no other fields that may be requested from the Graph API.

 The `delegate` property may be set to an object that conforms to the <FBGraphObjectPickerDelegate>
 protocol. The graph object passed to the delegate conforms to the <FBGraphPerson> protocol.
 */
@interface FBTaggableFriendPickerViewController : FBPeoplePickerViewController

@end
