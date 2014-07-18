//
//  EditBoxServiceMac.mm
//  quick-x-player
//

#include "EditBoxServiceMac.h"

#include "cocos2d.h"
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
    return glfwGetCocoaWindow(glview->getWindow());
}

- (void)dealloc
{
    [textField_ resignFirstResponder];
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
    }
    
    return self;
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
        [textField_ removeFromSuperview];
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
    if( commandSelector == @selector(insertTab:) ){
        cocos2d::EventCustom event("APP.EVENT");
        std::string data = "{\"name\":\"keyPress\", \"key\":\"tab\"}";
        event.setDataString(data);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    if( commandSelector == @selector(insertNewline:) ){
        
        cocos2d::EventCustom event("APP.EVENT");
        std::string data = "{\"name\":\"keyPress\", \"key\":\"return\"}";
        event.setDataString(data);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    
    return NO;
}

- (BOOL)textFieldShouldBeginEditing:(NSTextField *)sender        // return NO to disallow editing.
{
    editState_ = YES;
    //    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    //    if (pDelegate != NULL)
    //    {
    //        pDelegate->editBoxEditingDidBegin(getEditBoxImplMac()->getEditBox());
    //    }
    //
    //#if CC_ENABLE_SCRIPT_BINDING
    //    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    //    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    //    {
    //        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
    //        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
    //        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    //    }
    //#endif
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(NSTextField *)sender
{
    editState_ = NO;
    //    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    //    if (pDelegate != NULL)
    //    {
    //        pDelegate->editBoxEditingDidEnd(getEditBoxImplMac()->getEditBox());
    //        pDelegate->editBoxReturn(getEditBoxImplMac()->getEditBox());
    //    }
    //
    //#if CC_ENABLE_SCRIPT_BINDING
    //    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    //    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    //    {
    //        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
    //        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
    //        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    //        memset(data.eventName, 0, sizeof(data.eventName));
    //        strncpy(data.eventName, "return", sizeof(data.eventName));
    //        event.data = (void*)&data;
    //        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    //    }
    //#endif
    return YES;
}

/**
 * Delegate method called before the text has been changed.
 * @param textField The text field containing the text.
 * @param range The range of characters to be replaced.
 * @param string The replacement string.
 * @return YES if the specified text range should be replaced; otherwise, NO to keep the old text.
 */
- (BOOL)textField:(NSTextField *) textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    //    if (getEditBoxImplMac()->getMaxLength() < 0)
    //    {
    //        return YES;
    //    }
    
    NSUInteger oldLength = [[textField stringValue] length];
    NSUInteger replacementLength = [string length];
    NSUInteger rangeLength = range.length;
    
    NSUInteger newLength = oldLength - rangeLength + replacementLength;
    
    return YES;
    //    return newLength <= getEditBoxImplMac()->getMaxLength();
}

/**
 * Called each time when the text field's text has changed.
 */
- (void)controlTextDidChange:(NSNotification *)notification
{
    //    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplMac()->getDelegate();
    //    if (pDelegate != NULL)
    //    {
    //        pDelegate->editBoxTextChanged(getEditBoxImplMac()->getEditBox(), getEditBoxImplMac()->getText());
    //    }
    //
    //#if CC_ENABLE_SCRIPT_BINDING
    //    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplMac()->getEditBox();
    //    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    //    {
    //        cocos2d::CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
    //        cocos2d::ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
    //        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    //    }
    //#endif
}

@end



PLAYER_NS_BEGIN;

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

EditBoxServiceMac::EditBoxServiceMac()
{
    NSRect rect =  NSMakeRect(0, 0, 100, 20);
    _sysEdit = [[EditBoxServiceImplMac alloc] initWithFrame:rect editBox:this];
}

EditBoxServiceMac::~EditBoxServiceMac()
{
    [_sysEdit release];
}

void EditBoxServiceMac::setPosition(int x, int y)
{
    [_sysEdit setPosition:NSMakePoint(x, y)];
}

void EditBoxServiceMac::setSize(int width, int height)
{
    [_sysEdit setContentSize:NSMakeSize(width, height)];
}

void EditBoxServiceMac::setRect(int x, int y, int width, int height)
{
    setPosition(x, y);
    setSize(width, height);
}

void EditBoxServiceMac::setText(std::string text)
{
    _sysEdit.textField.stringValue = [NSString stringWithUTF8String:text.c_str()];
}

void EditBoxServiceMac::setFont(const char* pFontName, int fontSize)
{
    NSString *fntName = [NSString stringWithUTF8String:pFontName];
	NSFont *textFont = [NSFont fontWithName:fntName size:fontSize];
	if (textFont != nil)
    {
		[_sysEdit.textField setFont:textFont];
    }
}

void EditBoxServiceMac::setFontColor(int r, int g, int b)
{
    NSColor *color = [NSColor colorWithCalibratedRed:r / 255.0f green:g / 255.0f blue:b / 255.0f alpha:1.0f];
    _sysEdit.textField.textColor = color;
}

// hide editbox
void EditBoxServiceMac::hide()
{
    [_sysEdit.textField setHidden:YES];
    [_sysEdit closeKeyboard];
}

void EditBoxServiceMac::show()
{
    [_sysEdit.textField setHidden:NO];
    [_sysEdit openKeyboard];
    
    printf("show edit box service herer\n");
}

PLAYER_NS_END;