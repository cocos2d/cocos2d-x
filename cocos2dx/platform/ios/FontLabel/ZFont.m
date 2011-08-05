//
//  ZFont.m
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

#import "ZFont.h"

@interface ZFont ()
@property (nonatomic, readonly) CGFloat ratio;
- (NSString *)copyNameTableEntryForID:(UInt16)nameID;
@end

@implementation ZFont
@synthesize cgFont=_cgFont, pointSize=_pointSize, ratio=_ratio;

+ (ZFont *)fontWithCGFont:(CGFontRef)cgFont size:(CGFloat)fontSize {
	return [[[self alloc] initWithCGFont:cgFont size:fontSize] autorelease];
}

+ (ZFont *)fontWithUIFont:(UIFont *)uiFont {
	NSParameterAssert(uiFont != nil);
	CGFontRef cgFont = CGFontCreateWithFontName((CFStringRef)uiFont.fontName);
	ZFont *zFont = [[self alloc] initWithCGFont:cgFont size:uiFont.pointSize];
	CGFontRelease(cgFont);
	return [zFont autorelease];
}

- (id)initWithCGFont:(CGFontRef)cgFont size:(CGFloat)fontSize {
	if ((self = [super init])) {
		_cgFont = CGFontRetain(cgFont);
		_pointSize = fontSize;
		_ratio = fontSize/CGFontGetUnitsPerEm(cgFont);
	}
	return self;
}

- (id)init {
	NSAssert(NO, @"-init is not valid for ZFont");
	return nil;
}

- (CGFloat)ascender {
	return ceilf(self.ratio * CGFontGetAscent(self.cgFont));
}

- (CGFloat)descender {
	return floorf(self.ratio * CGFontGetDescent(self.cgFont));
}

- (CGFloat)leading {
	return (self.ascender - self.descender);
}

- (CGFloat)capHeight {
	return ceilf(self.ratio * CGFontGetCapHeight(self.cgFont));
}

- (CGFloat)xHeight {
	return ceilf(self.ratio * CGFontGetXHeight(self.cgFont));
}

- (NSString *)familyName {
	if (_familyName == nil) {
		_familyName = [self copyNameTableEntryForID:1];
	}
	return _familyName;
}

- (NSString *)fontName {
	if (_fontName == nil) {
		_fontName = [self copyNameTableEntryForID:4];
	}
	return _fontName;
}

- (NSString *)postScriptName {
	if (_postScriptName == nil) {
		_postScriptName = [self copyNameTableEntryForID:6];
	}
	return _postScriptName;
}

- (ZFont *)fontWithSize:(CGFloat)fontSize {
	if (fontSize == self.pointSize) return self;
	NSParameterAssert(fontSize > 0.0);
	return [[[ZFont alloc] initWithCGFont:self.cgFont size:fontSize] autorelease];
}

- (BOOL)isEqual:(id)object {
	if (![object isKindOfClass:[ZFont class]]) return NO;
	ZFont *font = (ZFont *)object;
	return (font.cgFont == self.cgFont && font.pointSize == self.pointSize);
}

- (NSString *)copyNameTableEntryForID:(UInt16)aNameID {
	CFDataRef nameTable = CGFontCopyTableForTag(self.cgFont, 'name');
	NSAssert1(nameTable != NULL, @"CGFontCopyTableForTag returned NULL for 'name' tag in font %@",
			   [(id)CFCopyDescription(self.cgFont) autorelease]);
	const UInt8 * const bytes = CFDataGetBytePtr(nameTable);
	NSAssert1(OSReadBigInt16(bytes, 0) == 0, @"name table for font %@ has bad version number",
			   [(id)CFCopyDescription(self.cgFont) autorelease]);
	const UInt16 count = OSReadBigInt16(bytes, 2);
	const UInt16 stringOffset = OSReadBigInt16(bytes, 4);
	const UInt8 * const nameRecords = &bytes[6];
	UInt16 nameLength = 0;
	UInt16 nameOffset = 0;
	NSStringEncoding encoding = 0;
	for (UInt16 idx = 0; idx < count; idx++) {
		const uintptr_t recordOffset = 12 * idx;
		const UInt16 nameID = OSReadBigInt16(nameRecords, recordOffset + 6);
		if (nameID != aNameID) continue;
		const UInt16 platformID = OSReadBigInt16(nameRecords, recordOffset + 0);
		const UInt16 platformSpecificID = OSReadBigInt16(nameRecords, recordOffset + 2);
		encoding = 0;
		// for now, we only support a subset of encodings
		switch (platformID) {
			case 0: // Unicode
				encoding = NSUTF16StringEncoding;
				break;
			case 1: // Macintosh
				switch (platformSpecificID) {
					case 0:
						encoding = NSMacOSRomanStringEncoding;
						break;
				}
			case 3: // Microsoft
				switch (platformSpecificID) {
					case 1:
						encoding = NSUTF16StringEncoding;
						break;
				}
		}
		if (encoding == 0) continue;
		nameLength = OSReadBigInt16(nameRecords, recordOffset + 8);
		nameOffset = OSReadBigInt16(nameRecords, recordOffset + 10);
		break;
	}
	NSString *result = nil;
	if (nameOffset > 0) {
		const UInt8 *nameBytes = &bytes[stringOffset + nameOffset];
		result = [[NSString alloc] initWithBytes:nameBytes length:nameLength encoding:encoding];
	}
	CFRelease(nameTable);
	return result;
}

- (void)dealloc {
	CGFontRelease(_cgFont);
	[_familyName release];
	[_fontName release];
	[_postScriptName release];
	[super dealloc];
}
@end
