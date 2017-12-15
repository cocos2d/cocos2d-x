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

extern NSString *const FacebookAdsSDKErrorDomain;

/*!
 @class FBAdSettings

 @abstract AdSettings contains global settings for all ad controls.
 */
@interface FBAdSettings : NSObject

/*!
@method

@abstract
 Adds a test device.

@param deviceHash The id of the device to use test mode, can be obtained from debug log

@discussion
 Copy the current device Id from debug log and add it as a test device to get test ads. Apps
 running on emulator will automatically get test ads. Test devices should be added before loadAd is called.
*/
+ (void)addTestDevice:(NSString *)deviceHash;

/*!
 @method

 @abstract
 Add a collection of test devices. See `+addTestDevices:` for details.

 @param deviceHash The array of the device id to use test mode, can be obtained from debug log
 */
+ (void)addTestDevices:(NSArray *)devicesHash;

/*!
 @method

 @abstract
 Clear all the added test devices
 */
+ (void)clearTestDevices;

/*!
 @method

 @abstract
 Configures the ad control for treatment as child-directed.

 @param isChildDirected Indicates whether you would like your ad control to be treated as child-directed

 @discussion
 Note that you may have other legal obligations under the Children's Online Privacy Protection Act (COPPA).
 Please review the FTC's guidance and consult with your own legal counsel.
 */
+ (void)setIsChildDirected:(BOOL)isChildDirected;

/*!
 @method

 @abstract
 Sets the url prefix to use when making ad requests.

 @discussion
 This method should never be used in production.
 */
+ (void)setUrlPrefix:(NSString *) urlPrefix;

@end
