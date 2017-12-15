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

#import "FBCacheDescriptor.h"
#import "FBGraphUser.h"
#import "FBPeoplePickerViewController.h"

@protocol FBFriendPickerDelegate;


/*!
 @class

 @abstract
 The `FBFriendPickerViewController` class creates a controller object that manages
 the user interface for displaying and selecting Facebook friends.

 @discussion
 When the `FBFriendPickerViewController` view loads it creates a `UITableView` object
 where the friends will be displayed. You can access this view through the `tableView`
 property. The friend display can be sorted by first name or last name. Friends'
 names can be displayed with the first name first or the last name first.

 The friend data can be pre-fetched and cached prior to using the view controller. The
 cache is setup using an <FBCacheDescriptor> object that can trigger the
 data fetch. Any friend data requests will first check the cache and use that data.
 If the friend picker is being displayed cached data will initially be shown before
 a fresh copy is retrieved.

 The `delegate` property may be set to an object that conforms to the <FBFriendPickerDelegate>
 protocol. The `delegate` object will receive updates related to friend selection and
 data changes. The delegate can also be used to filter the friends to display in the
 picker.
 */
@interface FBFriendPickerViewController : FBPeoplePickerViewController

/*!
 @abstract
 The list of friends that are currently selected in the veiw.
 The items in the array are <FBGraphUser> objects.

 @discussion
 You can set this this array to pre-select items in the picker. The objects in the array
 must be complete id<FBGraphUser> objects (i.e., fetched from a Graph query or from a
 previous picker's selection, with id and appropriate name fields).
 */
@property (nonatomic, copy, readwrite) NSArray *selection;

/*!
 @abstract
 Configures the properties used in the caching data queries.

 @discussion
 Cache descriptors are used to fetch and cache the data used by the view controller.
 If the view controller finds a cached copy of the data, it will
 first display the cached content then fetch a fresh copy from the server.

 @param cacheDescriptor     The <FBCacheDescriptor> containing the cache query properties.
 */
- (void)configureUsingCachedDescriptor:(FBCacheDescriptor *)cacheDescriptor;

/*!
 @method

 @abstract
 Creates a cache descriptor based on default settings of the `FBFriendPickerViewController` object.

 @discussion
 An `FBCacheDescriptor` object may be used to pre-fetch data before it is used by
 the view controller. It may also be used to configure the `FBFriendPickerViewController`
 object.
 */
+ (FBCacheDescriptor *)cacheDescriptor;

/*!
 @method

 @abstract
 Creates a cache descriptor with additional fields and a profile ID for use with the `FBFriendPickerViewController` object.

 @discussion
 An `FBCacheDescriptor` object may be used to pre-fetch data before it is used by
 the view controller. It may also be used to configure the `FBFriendPickerViewController`
 object.

 @param userID              The profile ID of the user whose friends will be displayed. A nil value implies a "me" alias.
 @param fieldsForRequest    The set of additional fields to include in the request for friend data.
 */
+ (FBCacheDescriptor *)cacheDescriptorWithUserID:(NSString *)userID fieldsForRequest:(NSSet *)fieldsForRequest;

@end

/*!
 @protocol

 @abstract
 The `FBFriendPickerDelegate` protocol defines the methods used to receive event
 notifications and allow for deeper control of the <FBFriendPickerViewController>
 view.

 The methods of <FBFriendPickerDelegate> correspond to <FBGraphObjectPickerDelegate>.
 If a pair of corresponding methods are implemented, the <FBGraphObjectPickerDelegate>
 method is called first.
 */
@protocol FBFriendPickerDelegate <FBGraphObjectPickerDelegate>
@optional

/*!
 @abstract
 Tells the delegate that data has been loaded.

 @discussion
 The <FBFriendPickerViewController> object's `tableView` property is automatically
 reloaded when this happens. However, if another table view, for example the
 `UISearchBar` is showing data, then it may also need to be reloaded.

 @param friendPicker        The friend picker view controller whose data changed.
 */
- (void)friendPickerViewControllerDataDidChange:(FBFriendPickerViewController *)friendPicker;

/*!
 @abstract
 Tells the delegate that the selection has changed.

 @param friendPicker        The friend picker view controller whose selection changed.
 */
- (void)friendPickerViewControllerSelectionDidChange:(FBFriendPickerViewController *)friendPicker;

/*!
 @abstract
 Asks the delegate whether to include a friend in the list.

 @discussion
 This can be used to implement a search bar that filters the friend list.

 If -[<FBGraphObjectPickerDelegate> graphObjectPickerViewController:shouldIncludeGraphObject:]
 is implemented and returns NO, this method is not called.

 @param friendPicker        The friend picker view controller that is requesting this information.
 @param user                An <FBGraphUser> object representing the friend.
 */
- (BOOL)friendPickerViewController:(FBFriendPickerViewController *)friendPicker
                 shouldIncludeUser:(id<FBGraphUser>)user;

/*!
 @abstract
 Tells the delegate that there is a communication error.

 @param friendPicker        The friend picker view controller that encountered the error.
 @param error               An error object containing details of the error.
 */
- (void)friendPickerViewController:(FBFriendPickerViewController *)friendPicker
                       handleError:(NSError *)error;

@end
