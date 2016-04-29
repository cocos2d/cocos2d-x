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

/*!
 @class FBAdStarRating

 @abstract
 Represents the Facebook ad star rating, which contains the rating value and rating scale.
 */
extern const struct FBAdStarRating {
  float value;
  int scale;
} FBAdStarRating;

/*!
 @class FBAdImage

 @abstract Represents an image creative.
 */
@interface FBAdImage : NSObject

/*!
 @property
 @abstract Typed access to the image url.
 */
@property (nonatomic, copy, readonly) NSURL *url;
/*!
 @property
 @abstract Typed access to the image width.
 */
@property (nonatomic, assign, readonly) int width;
/*!
 @property
 @abstract Typed access to the image height.
 */
@property (nonatomic, assign, readonly) int height;

/*!
 @method

 @abstract
 This is a method to initialize an FBAdImage.

 @param url the image url.
 @param width the image width.
 @param height the image height.
 */
- (id)initWithURL:(NSURL *)url width:(int)width height:(int)height;

@end


