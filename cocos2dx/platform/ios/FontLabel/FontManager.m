//
//  FontManager.m
//  FontLabel
//
//  Created by Kevin Ballard on 5/5/09.
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

#import "FontManager.h"
#import "ZFont.h"

static FontManager *sharedFontManager = nil;

@implementation FontManager
+ (FontManager *)sharedManager {
	@synchronized(self) {
		if (sharedFontManager == nil) {
			sharedFontManager = [[self alloc] init];
		}
	}
	return sharedFontManager;
}

- (id)init {
	if ((self = [super init])) {
		fonts = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
		urls = [[NSMutableDictionary alloc] init];
	}
	return self;
}

- (BOOL)loadFont:(NSString *)filename {
	NSString *fontPath = [[NSBundle mainBundle] pathForResource:filename ofType:@"ttf"];
	if (fontPath == nil) {
		fontPath = [[NSBundle mainBundle] pathForResource:filename ofType:nil];
	}
	if (fontPath == nil) return NO;
	
	NSURL *url = [NSURL fileURLWithPath:fontPath];
	if ([self loadFontURL:url]) {
		[urls setObject:url forKey:filename];
		return YES;
	}
	return NO;
}

- (BOOL)loadFontURL:(NSURL *)url {
	CGDataProviderRef fontDataProvider = CGDataProviderCreateWithURL((CFURLRef)url);
	if (fontDataProvider == NULL) return NO;
	CGFontRef newFont = CGFontCreateWithDataProvider(fontDataProvider); 
	CGDataProviderRelease(fontDataProvider); 
	if (newFont == NULL) return NO;
	
	CFDictionarySetValue(fonts, url, newFont);
	CGFontRelease(newFont);
	return YES;
}

- (CGFontRef)fontWithName:(NSString *)filename {
	CGFontRef font = NULL;
	NSURL *url = [urls objectForKey:filename];
	if (url == nil && [self loadFont:filename]) {
		url = [urls objectForKey:filename];
	}
	if (url != nil) {
		font = (CGFontRef)CFDictionaryGetValue(fonts, url);
	}
	return font;
}

- (ZFont *)zFontWithName:(NSString *)filename pointSize:(CGFloat)pointSize {
	NSURL *url = [urls objectForKey:filename];
	if (url == nil && [self loadFont:filename]) {
		url = [urls objectForKey:filename];
	}
	if (url != nil) {
		CGFontRef cgFont = (CGFontRef)CFDictionaryGetValue(fonts, url);
		if (cgFont != NULL) {
			return [ZFont fontWithCGFont:cgFont size:pointSize];
		}
	}
	return nil;
}

- (ZFont *)zFontWithURL:(NSURL *)url pointSize:(CGFloat)pointSize {
	CGFontRef cgFont = (CGFontRef)CFDictionaryGetValue(fonts, url);
	if (cgFont == NULL && [self loadFontURL:url]) {
		cgFont = (CGFontRef)CFDictionaryGetValue(fonts, url);
	}
	if (cgFont != NULL) {
		return [ZFont fontWithCGFont:cgFont size:pointSize];
	}
	return nil;
}

- (CFArrayRef)copyAllFonts {
	CFIndex count = CFDictionaryGetCount(fonts);
	CGFontRef *values = (CGFontRef *)malloc(sizeof(CGFontRef) * count);
	CFDictionaryGetKeysAndValues(fonts, NULL, (const void **)values);
	CFArrayRef array = CFArrayCreate(NULL, (const void **)values, count, &kCFTypeArrayCallBacks);
	free(values);
	return array;
}

- (void)dealloc {
	CFRelease(fonts);
	[urls release];
	[super dealloc];
}
@end
