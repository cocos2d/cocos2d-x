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

#import "FBGraphObject.h"
#import "FBSession.h"
#import "FBViewController.h"

@protocol FBGraphObjectPickerDelegate;

/*!
 @class FBGraphObjectPickerViewController

 @abstract
 The `FBGraphObjectPickerViewController` class is an abstract controller object that
 manages the user interface for displaying and selecting a collection of graph objects.

 @discussion
 When the `FBGraphObjectPickerViewController` view loads it creates a `UITableView`
 object where the graph objects defined by a concrete subclass will be displayed. You
 can access this view through the `tableView` property.

 The `delegate` property may be set to an object that conforms to the <FBGraphObjectPickerDelegate>
 protocol. The `delegate` object will receive updates related to object selection and
 data changes. The delegate can also be used to filter the objects to display in the
 picker.
 */
@interface FBGraphObjectPickerViewController : FBViewController

/*!
 @abstract
 Returns an outlet for the spinner used in the view controller.
 */
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *spinner;

/*!
 @abstract
 Returns an outlet for the table view managed by the view controller.
 */
@property (nonatomic, retain) IBOutlet UITableView *tableView;

/*!
 @abstract
 Addtional fields to fetch when making the Graph API call to get graph object data.
 */
@property (nonatomic, copy) NSSet *fieldsForRequest;

/*!
 @abstract
 A Boolean value that indicates whether pictures representing the graph object are displayed.
 Defaults to YES.
 */
@property (nonatomic) BOOL itemPicturesEnabled;

/*!
 @abstract
 The session that is used in the request for the graph object data.
 */
@property (nonatomic, retain) FBSession *session;

/*!
 @abstract
 Clears the current selection, so the picker is ready for a fresh use.
 */
- (void)clearSelection;

/*!
 @abstract
 Initiates a query to get the graph object data.


 @discussion
 A cached copy will be returned if available. The cached view is temporary until a fresh copy is
 retrieved from the server. It is legal to call this more than once.
 */
- (void)loadData;

/*!
 @abstract
 Updates the view locally without fetching data from the server or from cache.

 @discussion
 Use this if the filter or sort (if applicable) properties change. This may affect the
 order or display of information.
 */
- (void)updateView;

@end

/*!
 @protocol

 @abstract
 The `FBGraphObjectPickerDelegate` protocol defines the methods used to receive event
 notifications and allow for deeper control of the <FBGraphObjectPickerViewController>
 view.
 */
@protocol FBGraphObjectPickerDelegate <FBViewControllerDelegate>
@optional

/*!
 @abstract
 Tells the delegate that data has been loaded.

 @discussion
 The <FBGraphObjectPickerViewController> object's `tableView` property is automatically
 reloaded when this happens. However, if another table view, for example the
 `UISearchBar` is showing data, then it may also need to be reloaded.

 @param graphObjectPicker   The graph object picker view controller whose data changed.
 */
- (void)graphObjectPickerViewControllerDataDidChange:(FBGraphObjectPickerViewController *)graphObjectPicker;

/*!
 @abstract
 Tells the delegate that the selection has changed.

 @param graphObjectPicker   The graph object picker view controller whose selection changed.
 */
- (void)graphObjectPickerViewControllerSelectionDidChange:(FBGraphObjectPickerViewController *)graphObjectPicker;

/*!
 @abstract
 Asks the delegate whether to include a graph object in the list.

 @discussion
 This can be used to implement a search bar that filters the graph object list.

 @param graphObjectPicker   The graph object picker view controller that is requesting this information.
 @param object              An <FBGraphObject> object
 */
- (BOOL)graphObjectPickerViewController:(FBGraphObjectPickerViewController *)graphObjectPicker
               shouldIncludeGraphObject:(id<FBGraphObject>)object;

/*!
 @abstract
 Called if there is a communication error.

 @param graphObjectPicker   The graph object picker view controller that encountered the error.
 @param error               An error object containing details of the error.
 */
- (void)graphObjectPickerViewController:(FBGraphObjectPickerViewController *)graphObjectPicker
                            handleError:(NSError *)error;

@end
