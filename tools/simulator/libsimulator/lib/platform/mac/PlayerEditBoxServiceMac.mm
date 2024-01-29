/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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


#include "PlayerEditBoxServiceMac.h"

#include "cocos2d.h"
#if (CC_LUA_ENGINE_ENABLED > 0)
#include "CCLuaEngine.h"
#endif
#include "glfw3native.h"

// internal

@implementation EditBoxServiceImplMac

@synthesize textField = textField_;
@synthesize placeholderAttributes = placeholderAttributes_;
@synthesize editState = editState_;
@synthesize editBox = editBox_;

- (id) getNSWindow
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    return glview->getCocoaWindow();
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [textField_ removeFromSuperview];
    [textField_ release];
    
    [placeholderAttributes_ release];
    [super dealloc];
}

-(id) initWithFrame: (NSRect) frameRect editBox: (void*) editBox
{
    self = [super init];
    
    if (self)
    {
        editState_ = NO;
        self.textField = [[[NSTextField alloc] initWithFrame:frameRect] autorelease];
        
        NSColor *newColor = [NSColor colorWithCalibratedRed:255 / 255.0f green:0 blue:0 alpha:1.0f];
        self.textField.textColor = newColor;
        
        NSFont *font = [NSFont systemFontOfSize:10]; //TODO need to delete hard code here.
        textField_.font = font;
        
        [self setupTextField:textField_];
        
        self.editBox = editBox;
        self.placeholderAttributes = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                      font, NSFontAttributeName,
                                      [NSColor grayColor], NSForegroundColorAttributeName,
                                      nil];
        
        [[[self getNSWindow] contentView] addSubview:textField_];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                selector:@selector(onTextDidChanged:)
                                                    name:NSControlTextDidEndEditingNotification
                                                  object:nil];
    }
    
    return self;
}

- (void)onTextDidChanged:(NSNotification *) notification
{
    // hide first
    [self.textField setHidden:YES];
    
#if (CC_LUA_ENGINE_ENABLED > 0)
    player::PlayerEditBoxServiceMac *macEditBox = static_cast<player::PlayerEditBoxServiceMac *>(self.editBox);
    auto luaStack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    luaStack->pushString([self.textField.stringValue UTF8String]);
    luaStack->executeFunctionByHandler(macEditBox->getHandler(), 1);
#endif
}

- (void)setupTextField:(NSTextField *)textField
{
    [textField setTextColor:[NSColor whiteColor]];
    [textField setBackgroundColor:[NSColor clearColor]];
    [textField setBordered:NO];
    [textField setHidden:NO];
    [textField setWantsLayer:YES];
    [textField setDelegate:self];
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    [[[self getNSWindow] contentView] doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

-(void) setPosition:(NSPoint) pos
{
    NSRect frame = [textField_ frame];
    frame.origin = pos;
    [textField_ setFrame:frame];
}

-(void) setContentSize:(NSSize) size
{
    [self.textField setFrameSize:size];
}

-(void) visit
{
    
}

-(void) openKeyboard
{
    if ([textField_ superview]) {
        [textField_ becomeFirstResponder];
    }
}

-(void) closeKeyboard
{
    if ([textField_ superview]) {
        [textField_ resignFirstResponder];
    }
}

- (BOOL)textFieldShouldReturn:(NSTextField *)sender
{
    if (sender == textField_) {
        [sender resignFirstResponder];
    }
    return NO;
}

-(void)animationSelector
{
}

- (BOOL) control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector
{
    return NO;
}

@end



PLAYER_NS_BEGIN;

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

PlayerEditBoxServiceMac::PlayerEditBoxServiceMac()
{
    _handler = 0;
    NSRect rect =  NSMakeRect(0, 0, 100, 20);
    _sysEdit = [[EditBoxServiceImplMac alloc] initWithFrame:rect editBox:this];
}

PlayerEditBoxServiceMac::~PlayerEditBoxServiceMac()
{
    [_sysEdit release];
}

void PlayerEditBoxServiceMac::showSingleLineEditBox(const cocos2d::Rect &rect)
{
    [[_sysEdit.textField cell] setLineBreakMode:NSLineBreakByTruncatingTail];
    [[_sysEdit.textField cell] setTruncatesLastVisibleLine:YES];
    
    [_sysEdit setPosition:NSMakePoint(rect.origin.x, rect.origin.y)];
    [_sysEdit setContentSize:NSMakeSize(rect.size.width, rect.size.height)];
    
    show();
}

void PlayerEditBoxServiceMac::showMultiLineEditBox(const cocos2d::Rect &rect)
{
    [[_sysEdit.textField cell] setLineBreakMode:NSLineBreakByCharWrapping];
    [[_sysEdit.textField cell] setTruncatesLastVisibleLine:NO];
    
    [_sysEdit setPosition:NSMakePoint(rect.origin.x, rect.origin.y)];
    [_sysEdit setContentSize:NSMakeSize(rect.size.width, rect.size.height)];
    
    show();
}

void PlayerEditBoxServiceMac::setText(const std::string &text)
{
    _sysEdit.textField.stringValue = [NSString stringWithUTF8String:text.c_str()];
}

void PlayerEditBoxServiceMac::setFont(const std::string &name, int size)
{
    NSString *fntName = [NSString stringWithUTF8String:name.c_str()];
	NSFont *textFont = [NSFont fontWithName:fntName size:size];
	if (textFont != nil)
    {
		[_sysEdit.textField setFont:textFont];
    }
}

void PlayerEditBoxServiceMac::setFontColor(const cocos2d::Color3B &color)
{
    NSColor *textColor = [NSColor colorWithCalibratedRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
    _sysEdit.textField.textColor = textColor;
}

// hide editbox
void PlayerEditBoxServiceMac::hide()
{
    [_sysEdit.textField setHidden:YES];
    [_sysEdit closeKeyboard];
}

void PlayerEditBoxServiceMac::show()
{
    [_sysEdit.textField setHidden:NO];
    [_sysEdit openKeyboard];
}

void PlayerEditBoxServiceMac::setFormator(int formator)
{
    CCLOG("Not support yet.");
}

PLAYER_NS_END;