/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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
#include "CCEditBoxImplIOS.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#define kLabelZOrder  9999

#include "CCEditBox.h"
#import "EAGLView.h"

#define getEditBoxImplIOS() ((cocos2d::extension::EditBoxImplIOS*)editBox_)

static const int CC_EDIT_BOX_PADDING = 5;

@implementation CCCustomUITextField
- (CGRect)textRectForBounds:(CGRect)bounds {
    float padding = CC_EDIT_BOX_PADDING * cocos2d::EGLView::sharedOpenGLView()->getScaleX() / [[CCEAGLView sharedEGLView] contentScaleFactor ];
    return CGRectMake(bounds.origin.x + padding, bounds.origin.y + padding,
                      bounds.size.width - padding*2, bounds.size.height - padding*2);
}
- (CGRect)editingRectForBounds:(CGRect)bounds {
    return [self textRectForBounds:bounds];
}
@end


@implementation CCEditBoxImplIOS_objc

@synthesize textField = textField_;
@synthesize editState = editState_;
@synthesize editBox = editBox_;

- (void)dealloc
{
    [textField_ resignFirstResponder];
    [textField_ removeFromSuperview];
    self.textField = NULL;
    [super dealloc];
}

-(id) initWithFrame: (CGRect) frameRect editBox: (void*) editBox
{
    self = [super init];
    
    do
    {
        if (self == nil) break;
        editState_ = NO;
        self.textField = [[[CCCustomUITextField alloc] initWithFrame: frameRect] autorelease];
        if (!textField_) break;
        [textField_ setTextColor:[UIColor whiteColor]];
        textField_.font = [UIFont systemFontOfSize:frameRect.size.height*2/3]; //TODO need to delete hard code here.
		textField_.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
        textField_.backgroundColor = [UIColor clearColor];
        textField_.borderStyle = UITextBorderStyleNone;
        textField_.delegate = self;
        textField_.hidden = true;
		textField_.returnKeyType = UIReturnKeyDefault;
        [textField_ addTarget:self action:@selector(textChanged) forControlEvents:UIControlEventEditingChanged];
        self.editBox = editBox;
        
		
        
        return self;
    }while(0);
    
    return nil;
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)distance
{
    id eglView = [CCEAGLView sharedEGLView];
    [eglView doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
}

-(void) setPosition:(CGPoint) pos
{
    CGRect frame = [textField_ frame];
    frame.origin = pos;
    [textField_ setFrame:frame];
}

-(void) setContentSize:(CGSize) size
{
    CGRect frame = [textField_ frame];
    frame.size = size;
    [textField_ setFrame:frame];
}

-(void) visit
{
    
}

-(void) openKeyboard
{
    [[CCEAGLView sharedEGLView] addSubview:textField_];
    [textField_ becomeFirstResponder];
}

-(void) closeKeyboard
{
    [textField_ resignFirstResponder];
    [textField_ removeFromSuperview];
}

- (BOOL)textFieldShouldReturn:(UITextField *)sender
{
    if (sender == textField_) {
        [sender resignFirstResponder];
    }
    return NO;
}

-(void)animationSelector
{
    id eglView = [CCEAGLView sharedEGLView];
    [eglView doAnimationWhenAnotherEditBeClicked];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)sender        // return NO to disallow editing.
{
    CCLOG("textFieldShouldBeginEditing...");
    editState_ = YES;
    id eglView = [CCEAGLView sharedEGLView];
    if ([eglView isKeyboardShown])
    {
        [self performSelector:@selector(animationSelector) withObject:nil afterDelay:0.0f];
    }
    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidBegin(getEditBoxImplIOS()->getEditBox());
    }
    
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplIOS()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::ScriptEngineProtocol* pEngine = cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
    }
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)sender
{
    CCLOG("textFieldShouldEndEditing...");
    editState_ = NO;
    getEditBoxImplIOS()->setText(getEditBoxImplIOS()->getText());
    
    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidEnd(getEditBoxImplIOS()->getEditBox());
        pDelegate->editBoxReturn(getEditBoxImplIOS()->getEditBox());
    }
    
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplIOS()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::ScriptEngineProtocol* pEngine = cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "return",pEditBox);
    }
	
	if(editBox_ != nil)
	{
		getEditBoxImplIOS()->onEndEditing();
	}
    return YES;
}

/**
 * Delegate method called before the text has been changed.
 * @param textField The text field containing the text.
 * @param range The range of characters to be replaced.
 * @param string The replacement string.
 * @return YES if the specified text range should be replaced; otherwise, NO to keep the old text.
 */
- (BOOL)textField:(UITextField *) textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if (getEditBoxImplIOS()->getMaxLength() < 0)
    {
        return YES;
    }
    
    NSUInteger oldLength = [textField.text length];
    NSUInteger replacementLength = [string length];
    NSUInteger rangeLength = range.length;
    
    NSUInteger newLength = oldLength - rangeLength + replacementLength;
    
    return newLength <= getEditBoxImplIOS()->getMaxLength();
}

/**
 * Called each time when the text field's text has changed.
 */
- (void) textChanged
{
    // NSLog(@"text is %@", self.textField.text);
    cocos2d::extension::EditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxTextChanged(getEditBoxImplIOS()->getEditBox(), getEditBoxImplIOS()->getText());
    }
    
    cocos2d::extension::EditBox*  pEditBox= getEditBoxImplIOS()->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::ScriptEngineProtocol* pEngine = cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
    }

}

@end


NS_CC_EXT_BEGIN

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplIOS(pEditBox);
}

EditBoxImplIOS::EditBoxImplIOS(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(NULL)
, _labelPlaceHolder(NULL)
, _systemControl(NULL)
, _anchorPoint(ccp(0.5f, 0.5f))
, _maxTextLength(-1)
{
    _inRetinaMode = [[CCEAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
}

EditBoxImplIOS::~EditBoxImplIOS()
{
    [_systemControl release];
}

void EditBoxImplIOS::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([_systemControl isEditState] || distance < 0.0f)
    {
        [_systemControl doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
    }
}

bool EditBoxImplIOS::initWithSize(const Size& size)
{
    do 
    {
        EGLViewProtocol* eglView = EGLView::sharedOpenGLView();

        CGRect rect = CGRectMake(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());

        if (_inRetinaMode)
        {
            rect.size.width /= 2.0f;
            rect.size.height /= 2.0f;
        }
        
        _systemControl = [[CCEditBoxImplIOS_objc alloc] initWithFrame:rect editBox:this];
        if (!_systemControl) break;
        
		initInactiveLabels(size);
        setContentSize(size);
		
        return true;
    }while (0);
    
    return false;
}

void EditBoxImplIOS::initInactiveLabels(const Size& size)
{
	const char* pDefaultFontName = [[_systemControl.textField.font fontName] UTF8String];

	_label = LabelTTF::create("", "", 0.0f);
    _label->setAnchorPoint(ccp(0, 0.5f));
    _label->setColor(ccWHITE);
    _label->setVisible(false);
    _editBox->addChild(_label, kLabelZOrder);
	
    _labelPlaceHolder = LabelTTF::create("", "", 0.0f);
	// align the text vertically center
    _labelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
    _labelPlaceHolder->setColor(ccGRAY);
    _editBox->addChild(_labelPlaceHolder, kLabelZOrder);
    
    setFont(pDefaultFontName, size.height*2/3);
    setPlaceholderFont(pDefaultFontName, size.height*2/3);
}

void EditBoxImplIOS::placeInactiveLabels() {
    _label->setPosition(ccp(CC_EDIT_BOX_PADDING, _contentSize.height / 2.0f));
    _labelPlaceHolder->setPosition(ccp(CC_EDIT_BOX_PADDING, _contentSize.height / 2.0f));
}

void EditBoxImplIOS::setInactiveText(const char* pText)
{
	if(_systemControl.textField.secureTextEntry == YES)
	{
		std::string passwordString;
		for(int i = 0; i < strlen(pText); ++i)
			passwordString.append("\u25CF");
		_label->setString(passwordString.c_str());
	}
	else
		_label->setString(getText());
	
	// Clip the text width to fit to the text box
	float fMaxWidth = _editBox->getContentSize().width - CC_EDIT_BOX_PADDING * 2;
	Rect clippingRect = _label->getTextureRect();
	if(clippingRect.size.width > fMaxWidth) {
		clippingRect.size.width = fMaxWidth;
		_label->setTextureRect(clippingRect);
	}
}

void EditBoxImplIOS::setFont(const char* pFontName, int fontSize)
{
    bool isValidFontName = true;
	if(pFontName == NULL || strlen(pFontName) == 0) {
        isValidFontName = false;
    }

    float retinaFactor = _inRetinaMode ? 2.0f : 1.0f;
	NSString * fntName = [NSString stringWithUTF8String:pFontName];
    float scaleFactor = EGLView::sharedOpenGLView()->getScaleX();
    UIFont *textFont = nil;
    if (isValidFontName) {
        textFont = [UIFont fontWithName:fntName size:fontSize * scaleFactor / retinaFactor];
    }
    
    if (!isValidFontName || textFont == nil){
        textFont = [UIFont systemFontOfSize:fontSize * scaleFactor / retinaFactor];
    }

	if(textFont != nil) {
		[_systemControl.textField setFont:textFont];
    }

	_label->setFontName(pFontName);
	_label->setFontSize(fontSize);
	_labelPlaceHolder->setFontName(pFontName);
	_labelPlaceHolder->setFontSize(fontSize);
}

void EditBoxImplIOS::setFontColor(const ccColor3B& color)
{
    _systemControl.textField.textColor = [UIColor colorWithRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
	_label->setColor(color);
}

void EditBoxImplIOS::setPlaceholderFont(const char* pFontName, int fontSize)
{
	// TODO need to be implemented.
}

void EditBoxImplIOS::setPlaceholderFontColor(const ccColor3B& color)
{
	_labelPlaceHolder->setColor(color);
}

void EditBoxImplIOS::setInputMode(EditBoxInputMode inputMode)
{
    switch (inputMode)
    {
        case kEditBoxInputModeEmailAddr:
            _systemControl.textField.keyboardType = UIKeyboardTypeEmailAddress;
            break;
        case kEditBoxInputModeNumeric:
            _systemControl.textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            break;
        case kEditBoxInputModePhoneNumber:
            _systemControl.textField.keyboardType = UIKeyboardTypePhonePad;
            break;
        case kEditBoxInputModeUrl:
            _systemControl.textField.keyboardType = UIKeyboardTypeURL;
            break;
        case kEditBoxInputModeDecimal:
            _systemControl.textField.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case kEditBoxInputModeSingleLine:
            _systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
        default:
            _systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
    }
}

void EditBoxImplIOS::setMaxLength(int maxLength)
{
    _maxTextLength = maxLength;
}

int EditBoxImplIOS::getMaxLength()
{
    return _maxTextLength;
}

void EditBoxImplIOS::setInputFlag(EditBoxInputFlag inputFlag)
{
    switch (inputFlag)
    {
        case kEditBoxInputFlagPassword:
            _systemControl.textField.secureTextEntry = YES;
            break;
        case kEditBoxInputFlagInitialCapsWord:
            _systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeWords;
            break;
        case kEditBoxInputFlagInitialCapsSentence:
            _systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            break;
        case kEditBoxInputFlagInitialCapsAllCharacters:
            _systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            break;
        case kEditBoxInputFlagSensitive:
            _systemControl.textField.autocorrectionType = UITextAutocorrectionTypeNo;
            break;
        default:
            break;
    }
}

void EditBoxImplIOS::setReturnType(KeyboardReturnType returnType)
{
    switch (returnType) {
        case kKeyboardReturnTypeDefault:
            _systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
        case kKeyboardReturnTypeDone:
            _systemControl.textField.returnKeyType = UIReturnKeyDone;
            break;
        case kKeyboardReturnTypeSend:
            _systemControl.textField.returnKeyType = UIReturnKeySend;
            break;
        case kKeyboardReturnTypeSearch:
            _systemControl.textField.returnKeyType = UIReturnKeySearch;
            break;
        case kKeyboardReturnTypeGo:
            _systemControl.textField.returnKeyType = UIReturnKeyGo;
            break;
        default:
            _systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
    }
}

bool EditBoxImplIOS::isEditing()
{
    return [_systemControl isEditState] ? true : false;
}

void EditBoxImplIOS::setText(const char* pText)
{
    _systemControl.textField.text = [NSString stringWithUTF8String:pText];
	if(_systemControl.textField.hidden == YES) {
		setInactiveText(pText);
		if(strlen(pText) == 0)
		{
			_label->setVisible(false);
			_labelPlaceHolder->setVisible(true);
		}
		else
		{
			_label->setVisible(true);
			_labelPlaceHolder->setVisible(false);
		}
	}
}

const char*  EditBoxImplIOS::getText(void)
{
    return [_systemControl.textField.text UTF8String];
}

void EditBoxImplIOS::setPlaceHolder(const char* pText)
{
    _systemControl.textField.placeholder = [NSString stringWithUTF8String:pText];
	_labelPlaceHolder->setString(pText);
}

static CGPoint convertDesignCoordToScreenCoord(const Point& designCoord, bool bInRetinaMode)
{
    EGLViewProtocol* eglView = EGLView::sharedOpenGLView();
    float viewH = (float)[[CCEAGLView sharedEGLView] getHeight];
    
    Point visiblePos = ccp(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    Point screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    
    CGPoint screenPos = CGPointMake(screenGLPos.x, viewH - screenGLPos.y);
    
    if (bInRetinaMode)
    {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    CCLOG("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void EditBoxImplIOS::setPosition(const Point& pos)
{
	_position = pos;
	adjustTextFieldPosition();
}

void EditBoxImplIOS::setVisible(bool visible)
{
//    _systemControl.textField.hidden = !visible;
}

void EditBoxImplIOS::setContentSize(const Size& size)
{
    _contentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
    placeInactiveLabels();
    EGLViewProtocol* eglView = EGLView::sharedOpenGLView();
    CGSize controlSize = CGSizeMake(size.width * eglView->getScaleX(),size.height * eglView->getScaleY());
    
    if (_inRetinaMode)
    {
        controlSize.width /= 2.0f;
        controlSize.height /= 2.0f;
    }
    [_systemControl setContentSize:controlSize];
}

void EditBoxImplIOS::setAnchorPoint(const Point& anchorPoint)
{
    CCLOG("[Edit text] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
	_anchorPoint = anchorPoint;
	setPosition(_position);
}

void EditBoxImplIOS::visit(void)
{
    
}

void EditBoxImplIOS::onEnter(void)
{
    adjustTextFieldPosition();
    const char* pText = getText();
    if (pText) {
        setInactiveText(pText);
    }
}

void EditBoxImplIOS::adjustTextFieldPosition()
{
	Size contentSize = _editBox->getContentSize();
	Rect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
    rect = RectApplyAffineTransform(rect, _editBox->nodeToWorldTransform());
	
	Point designCoord = ccp(rect.origin.x, rect.origin.y + rect.size.height);
    [_systemControl setPosition:convertDesignCoordToScreenCoord(designCoord, _inRetinaMode)];
}

void EditBoxImplIOS::openKeyboard()
{
	_label->setVisible(false);
	_labelPlaceHolder->setVisible(false);

	_systemControl.textField.hidden = NO;
    [_systemControl openKeyboard];
}

void EditBoxImplIOS::closeKeyboard()
{
    [_systemControl closeKeyboard];
}

void EditBoxImplIOS::onEndEditing()
{
	_systemControl.textField.hidden = YES;
	if(strlen(getText()) == 0)
	{
		_label->setVisible(false);
		_labelPlaceHolder->setVisible(true);
	}
	else
	{
		_label->setVisible(true);
		_labelPlaceHolder->setVisible(false);
		setInactiveText(getText());
	}
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


