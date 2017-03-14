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

#import "ui/UIEditBox/Mac/CCUIPasswordTextField.h"
#include "ui/UIEditBox/Mac/CCUITextFieldFormatter.h"

@interface RSVerticallyCenteredSecureTextFieldCell : NSSecureTextFieldCell
{
    BOOL mIsEditingOrSelecting;
}

@end

@implementation RSVerticallyCenteredSecureTextFieldCell

- (NSRect)drawingRectForBounds:(NSRect)theRect
{
    // Get the parent's idea of where we should draw
    NSRect newRect = [super drawingRectForBounds:theRect];

    // When the text field is being
    // edited or selected, we have to turn off the magic because it screws up
    // the configuration of the field editor.  We sneak around this by
    // intercepting selectWithFrame and editWithFrame and sneaking a
    // reduced, centered rect in at the last minute.
    if (mIsEditingOrSelecting == NO)
    {
        // Get our ideal size for current text
        NSSize textSize = [self cellSizeForBounds:theRect];

        // Center that in the proposed rect
        float heightDelta = newRect.size.height - textSize.height;
        if (heightDelta > 0)
        {
            newRect.size.height -= heightDelta;
            newRect.origin.y += (heightDelta / 2);
        }
    }

    return newRect;
}

- (void)selectWithFrame:(NSRect)aRect
                 inView:(NSView *)controlView
                 editor:(NSText *)textObj
               delegate:(id)anObject
                  start:(long)selStart
                 length:(long)selLength
{
    aRect = [self drawingRectForBounds:aRect];
    mIsEditingOrSelecting = YES;
    [super selectWithFrame:aRect
                    inView:controlView
                    editor:textObj
                  delegate:anObject
                     start:selStart
                    length:selLength];
    mIsEditingOrSelecting = NO;
}

- (void)editWithFrame:(NSRect)aRect
               inView:(NSView *)controlView
               editor:(NSText *)textObj
             delegate:(id)anObject
                event:(NSEvent *)theEvent
{
    aRect = [self drawingRectForBounds:aRect];
    mIsEditingOrSelecting = YES;
    [super editWithFrame:aRect
                  inView:controlView
                  editor:textObj
                delegate:anObject
                   event:theEvent];
    mIsEditingOrSelecting = NO;
}

@end

@interface CCUIPasswordTextField()
{

}

@end

@implementation CCUIPasswordTextField

-(id) initWithFrame:(NSRect)frameRect
{
    if (self = [super initWithFrame:frameRect]) {
        [self setLineBreakMode:NSLineBreakByTruncatingTail];
    }
    
    return self;
}

-(void)dealloc
{
    [super dealloc];
}

+(void)load
{
    [self setCellClass:[RSVerticallyCenteredSecureTextFieldCell class]];
}


-(void)ccui_setPlaceholderFont:(NSFont *)font
{
    //TODO:
}

-(NSString*)ccui_placeholder
{
    return self.placeholderString;
}

-(NSFont*)ccui_placeholderFont
{
    return [NSFont systemFontOfSize:self.bounds.size.height * 3.0 / 2.0];
}

-(NSColor*)ccui_placeholderColor
{
    return [NSColor whiteColor];
}

-(void)ccui_setPlaceholder:(NSString *)text
{
    //TODO:
}

-(void)ccui_setPlaceholderColor:(NSColor *)color
{
    //TODO;
}

#pragma mark - CCUITextInput
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

- (NSTextAlignment)ccui_alignment
{
  return self.alignment;
}

- (void)ccui_setTextHorizontalAlignment:(NSTextAlignment)ccui_alignment
{
  self.alignment = ccui_alignment;
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
