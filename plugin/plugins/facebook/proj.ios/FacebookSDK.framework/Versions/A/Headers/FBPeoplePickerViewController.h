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

#import "FBGraphObjectPickerViewController.h"

/*!
 @typedef NS_ENUM (NSUInteger, FBFriendSortOrdering)

 @abstract Indicates the order in which friends should be listed in the friend picker.

 @discussion
 */
typedef NS_ENUM(NSUInteger, FBFriendSortOrdering) {
    /*! Sort friends by first, middle, last names. */
    FBFriendSortByFirstName = 0,
    /*! Sort friends by last, first, middle names. */
    FBFriendSortByLastName
};

/*!
 @typedef NS_ENUM (NSUInteger, FBFriendDisplayOrdering)

 @abstract Indicates whether friends should be displayed first-name-first or last-name-first.

 @discussion
 */
typedef NS_ENUM(NSUInteger, FBFriendDisplayOrdering) {
    /*! Display friends as First Middle Last. */
    FBFriendDisplayByFirstName = 0,
    /*! Display friends as Last First Middle. */
    FBFriendDisplayByLastName,
};


/*!
 @class

 @abstract
 The `FBPeoplePickerViewController` class is an abstract controller object that manages
 the user interface for displaying and selecting people.

 @discussion
 When the `FBPeoplePickerViewController` view loads it creates a `UITableView` object
 where the people will be displayed. You can access this view through the `tableView`
 property. The people display can be sorted by first name or last name. People's
 names can be displayed with the first name first or the last name first.

 The `delegate` property may be set to an object that conforms to the <FBGraphObjectPickerDelegate>
 protocol, as defined by <FBGraphObjectPickerViewController>. The graph object passed to
 the delegate conforms to the <FBGraphPerson> protocol.
 */
@interface FBPeoplePickerViewController : FBGraphObjectPickerViewController

/*!
 @abstract
 A Boolean value that specifies whether multi-select is enabled.
 */
@property (nonatomic) BOOL allowsMultipleSelection;

/*!
 @abstract
 The profile ID of the user whose 'user_friends' permission is being used.
 */
@property (nonatomic, copy) NSString *userID;

/*!
 @abstract
 The list of people that are currently selected in the veiw.
 The items in the array are <FBGraphPerson> objects.
 */
@property (nonatomic, copy, readonly) NSArray *selection;

/*!
 @abstract
 The order in which people are sorted in the display.
 */
@property (nonatomic) FBFriendSortOrdering sortOrdering;

/*!
 @abstract
 The order in which people's names are displayed.
 */
@property (nonatomic) FBFriendDisplayOrdering displayOrdering;

@end
