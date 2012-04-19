//
//  ZFont.h
//  FontLabel
//
//  Created by Kevin Ballard on 7/2/09.
//  Copyright © 2009 Zynga Game Networks
//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ZFont : NSObject {
    CGFontRef _cgFont;
    CGFloat _pointSize;
    CGFloat _ratio;
    NSString *_familyName;
    NSString *_fontName;
    NSString *_postScriptName;
}
@property (nonatomic, readonly) CGFontRef cgFont;
@property (nonatomic, readonly) CGFloat pointSize;
@property (nonatomic, readonly) CGFloat ascender;
@property (nonatomic, readonly) CGFloat descender;
@property (nonatomic, readonly) CGFloat leading;
@property (nonatomic, readonly) CGFloat xHeight;
@property (nonatomic, readonly) CGFloat capHeight;
@property (nonatomic, readonly) NSString *familyName;
@property (nonatomic, readonly) NSString *fontName;
@property (nonatomic, readonly) NSString *postScriptName;
+ (ZFont *)fontWithCGFont:(CGFontRef)cgFont size:(CGFloat)fontSize;
+ (ZFont *)fontWithUIFont:(UIFont *)uiFont;
- (id)initWithCGFont:(CGFontRef)cgFont size:(CGFloat)fontSize;
- (ZFont *)fontWithSize:(CGFloat)fontSize;
@end
