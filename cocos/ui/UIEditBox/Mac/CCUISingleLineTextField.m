/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 zilongshanren
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "ui/UIEditBox/Mac/CCUISingleLineTextField.h"
#include "ui/UIEditBox/Mac/CCUITextFieldFormatter.h"

@interface CCUISingleLineTextField()
@property (nonatomic, retain) NSMutableDictionary *placeholderAttributes;

@end

@implementation CCUISingleLineTextField
{
}

@synthesize placeholderAttributes = _placeholderAttributes;

-(id) initWithFrame:(NSRect)frameRect
{
    if ([super initWithFrame:frameRect]) {
        NSFont* font = [NSFont systemFontOfSize:frameRect.size.height * 3 /2];
        self.placeholderAttributes = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                      font, NSFontAttributeName,
                                      [NSColor grayColor], NSForegroundColorAttributeName,
                                      nil];
        [self setLineBreakMode:NSLineBreakByTruncatingTail];
    }
    
    return self;
}

- (void)dealloc
{
    self.placeholderAttributes = nil;
    
    [super dealloc];
}

-(void)ccui_setPlaceholderFont:(NSFont *)font
{
    [self.placeholderAttributes setObject:font forKey:NSFontAttributeName];
}



-(void)ccui_setPlaceholder:(NSString *)text
{
    NSAttributedString *as = [[NSAttributedString alloc] initWithString:text
                                                             attributes:self.placeholderAttributes];
    
    [[self cell] setPlaceholderAttributedString:as];
    
    [as release];
}

-(NSString*)ccui_placeholder
{
    return self.placeholderString;
}

-(NSFont*)ccui_placeholderFont
{
    return [self.placeholderAttributes objectForKey:NSFontAttributeName];
}

-(NSColor*)ccui_placeholderColor
{
    return [self.placeholderAttributes objectForKey:NSForegroundColorAttributeName];
}

-(void)ccui_setPlaceholderColor:(NSColor *)color
{
    [self.placeholderAttributes setObject:color forKey:NSForegroundColorAttributeName];
}

- (NSString *)ccui_text
{
    return self.stringValue;
}

- (void)ccui_setText:(NSString *)ccui_text
{
    self.stringValue = ccui_text;
}

- (NSColor *)ccui_textColor
{
    return self.textColor;
}

- (void)ccui_setTextColor:(NSColor *)ccui_textColor
{
    self.textColor = ccui_textColor;
}

- (NSFont *)ccui_font
{
    return self.font;
}

- (void)ccui_setFont:(NSFont *)ccui_font
{
    self.font = ccui_font;
}


- (void)ccui_setDelegate:(id<NSTextFieldDelegate,NSTextViewDelegate>)delegate
{
    self.delegate = delegate;
}

- (void)ccui_setMaxLength:(int)length
{
    id formater =  [[[CCUITextFieldFormatter alloc]init] autorelease];
    [formater setMaximumLength:length];
    [self setFormatter:formater];
}

- (int)ccui_maxLength
{
    return [self.formatter maximumLength];
}

@end
