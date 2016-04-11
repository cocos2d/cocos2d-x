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

#import "ui/UIEditBox/Mac/CCUIMultilineTextField.h"

@interface CCUIMultilineTextField()
@property(nonatomic, copy)NSString* placeHolder;
@end

@implementation CCUIMultilineTextField
{
}

@synthesize placeHolder = _placeHolder;

-(void)dealloc
{
    self.placeHolder = nil;
    
    [super dealloc];
}

-(void)ccui_setPlaceholderFont:(NSFont *)font
{
    //TODO
}

-(NSFont*)ccui_placeholderFont
{
    return NULL;
}

-(void)ccui_setPlaceholder:(NSString *)text
{
    self.placeHolder = text;
}

-(NSString*)ccui_placeholder
{
    return self.placeHolder;
}

-(void)ccui_setPlaceholderColor:(NSColor *)color
{
    //TODO
}

-(NSColor*)ccui_placeholderColor
{
    return NULL;
}


#pragma mark - CCUITextInput
- (NSString *)ccui_text
{
    return self.string;
}

- (void)ccui_setText:(NSString *)ccui_text
{
    self.string = ccui_text;
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

- (void)ccui_setMaxLength:(int)ccui_maxLength
{
    //noop
}
-(int)ccui_maxLength
{
    return 0;
}
@end
