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

#define getEditBoxImplIOS() ((cocos2d::extension::CCEditBoxImplIOS*)editBox_)

static const int CC_EDIT_BOX_PADDING = 5;

@implementation CustomUITextField
- (CGRect)textRectForBounds:(CGRect)bounds {
    float padding = CC_EDIT_BOX_PADDING * cocos2d::CCEGLView::sharedOpenGLView()->getScaleX() / [[EAGLView sharedEGLView] contentScaleFactor ];
    return CGRectMake(bounds.origin.x + padding, bounds.origin.y + padding,
                      bounds.size.width - padding*2, bounds.size.height - padding*2);
}
- (CGRect)editingRectForBounds:(CGRect)bounds {
    return [self textRectForBounds:bounds];
}
@end


@implementation EditBoxImplIOS

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
        self.textField = [[[CustomUITextField alloc] initWithFrame: frameRect] autorelease];
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
    id eglView = [EAGLView sharedEGLView];
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
    [[EAGLView sharedEGLView] addSubview:textField_];
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
    id eglView = [EAGLView sharedEGLView];
    [eglView doAnimationWhenAnotherEditBeClicked];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)sender        // return NO to disallow editing.
{
    CCLOG("textFieldShouldBeginEditing...");
    editState_ = YES;
    id eglView = [EAGLView sharedEGLView];
    if ([eglView isKeyboardShown])
    {
        [self performSelector:@selector(animationSelector) withObject:nil afterDelay:0.0f];
    }
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidBegin(getEditBoxImplIOS()->getCCEditBox());
    }
    
    cocos2d::extension::CCEditBox*  pEditBox= getEditBoxImplIOS()->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
    }
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)sender
{
    CCLOG("textFieldShouldEndEditing...");
    editState_ = NO;
    getEditBoxImplIOS()->setText(getEditBoxImplIOS()->getText());
    
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxEditingDidEnd(getEditBoxImplIOS()->getCCEditBox());
        pDelegate->editBoxReturn(getEditBoxImplIOS()->getCCEditBox());
    }
    
    cocos2d::extension::CCEditBox*  pEditBox= getEditBoxImplIOS()->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
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
    cocos2d::extension::CCEditBoxDelegate* pDelegate = getEditBoxImplIOS()->getDelegate();
    if (pDelegate != NULL)
    {
        pDelegate->editBoxTextChanged(getEditBoxImplIOS()->getCCEditBox(), getEditBoxImplIOS()->getText());
    }
    
    cocos2d::extension::CCEditBox*  pEditBox= getEditBoxImplIOS()->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
    }

}

@end


NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplIOS(pEditBox);
}

CCEditBoxImplIOS::CCEditBoxImplIOS(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_pLabel(NULL)
, m_pLabelPlaceHolder(NULL)
, m_systemControl(NULL)
, m_obAnchorPoint(ccp(0.5f, 0.5f))
, m_nMaxTextLength(-1)
{
    m_bInRetinaMode = [[EAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
}

CCEditBoxImplIOS::~CCEditBoxImplIOS()
{
    [m_systemControl release];
}

void CCEditBoxImplIOS::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([m_systemControl isEditState] || distance < 0.0f)
    {
        [m_systemControl doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
    }
}

bool CCEditBoxImplIOS::initWithSize(const CCSize& size)
{
    do 
    {
        CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();

        CGRect rect = CGRectMake(0, 0, size.width * eglView->getScaleX(),size.height * eglView->getScaleY());

        if (m_bInRetinaMode)
        {
            rect.size.width /= 2.0f;
            rect.size.height /= 2.0f;
        }
        
        m_systemControl = [[EditBoxImplIOS alloc] initWithFrame:rect editBox:this];
        if (!m_systemControl) break;
        
		initInactiveLabels(size);
        setContentSize(size);
		
        return true;
    }while (0);
    
    return false;
}

void CCEditBoxImplIOS::initInactiveLabels(const CCSize& size)
{
	const char* pDefaultFontName = [[m_systemControl.textField.font fontName] UTF8String];

	m_pLabel = CCLabelTTF::create("", "", 0.0f);
    m_pLabel->setAnchorPoint(ccp(0, 0.5f));
    m_pLabel->setColor(ccWHITE);
    m_pLabel->setVisible(false);
    m_pEditBox->addChild(m_pLabel, kLabelZOrder);
	
    m_pLabelPlaceHolder = CCLabelTTF::create("", "", 0.0f);
	// align the text vertically center
    m_pLabelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
    m_pLabelPlaceHolder->setColor(ccGRAY);
    m_pEditBox->addChild(m_pLabelPlaceHolder, kLabelZOrder);
    
    setFont(pDefaultFontName, size.height*2/3);
    setPlaceholderFont(pDefaultFontName, size.height*2/3);
}

void CCEditBoxImplIOS::placeInactiveLabels() {
    m_pLabel->setPosition(ccp(CC_EDIT_BOX_PADDING, m_tContentSize.height / 2.0f));
    m_pLabelPlaceHolder->setPosition(ccp(CC_EDIT_BOX_PADDING, m_tContentSize.height / 2.0f));
}

void CCEditBoxImplIOS::setInactiveText(const char* pText)
{
	if(m_systemControl.textField.secureTextEntry == YES)
	{
		std::string passwordString;
		for(int i = 0; i < strlen(pText); ++i)
			passwordString.append("\u25CF");
		m_pLabel->setString(passwordString.c_str());
	}
	else
		m_pLabel->setString(getText());
	
	// Clip the text width to fit to the text box
	float fMaxWidth = m_pEditBox->getContentSize().width - CC_EDIT_BOX_PADDING * 2;
	CCRect clippingRect = m_pLabel->getTextureRect();
	if(clippingRect.size.width > fMaxWidth) {
		clippingRect.size.width = fMaxWidth;
		m_pLabel->setTextureRect(clippingRect);
	}
}

void CCEditBoxImplIOS::setFont(const char* pFontName, int fontSize)
{
    bool isValidFontName = true;
	if(pFontName == NULL || strlen(pFontName) == 0) {
        isValidFontName = false;
    }

    float retinaFactor = m_bInRetinaMode ? 2.0f : 1.0f;
	NSString * fntName = [NSString stringWithUTF8String:pFontName];
    float scaleFactor = CCEGLView::sharedOpenGLView()->getScaleX();
    UIFont *textFont = nil;
    if (isValidFontName) {
        textFont = [UIFont fontWithName:fntName size:fontSize * scaleFactor / retinaFactor];
    }
    
    if (!isValidFontName || textFont == nil){
        textFont = [UIFont systemFontOfSize:fontSize * scaleFactor / retinaFactor];
    }

	if(textFont != nil) {
		[m_systemControl.textField setFont:textFont];
    }

	m_pLabel->setFontName(pFontName);
	m_pLabel->setFontSize(fontSize);
	m_pLabelPlaceHolder->setFontName(pFontName);
	m_pLabelPlaceHolder->setFontSize(fontSize);
}

void CCEditBoxImplIOS::setFontColor(const ccColor3B& color)
{
    m_systemControl.textField.textColor = [UIColor colorWithRed:color.r / 255.0f green:color.g / 255.0f blue:color.b / 255.0f alpha:1.0f];
	m_pLabel->setColor(color);
}

void CCEditBoxImplIOS::setPlaceholderFont(const char* pFontName, int fontSize)
{
	// TODO need to be implemented.
}

void CCEditBoxImplIOS::setPlaceholderFontColor(const ccColor3B& color)
{
	m_pLabelPlaceHolder->setColor(color);
}

void CCEditBoxImplIOS::setInputMode(EditBoxInputMode inputMode)
{
    switch (inputMode)
    {
        case kEditBoxInputModeEmailAddr:
            m_systemControl.textField.keyboardType = UIKeyboardTypeEmailAddress;
            break;
        case kEditBoxInputModeNumeric:
            m_systemControl.textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            break;
        case kEditBoxInputModePhoneNumber:
            m_systemControl.textField.keyboardType = UIKeyboardTypePhonePad;
            break;
        case kEditBoxInputModeUrl:
            m_systemControl.textField.keyboardType = UIKeyboardTypeURL;
            break;
        case kEditBoxInputModeDecimal:
            m_systemControl.textField.keyboardType = UIKeyboardTypeDecimalPad;
            break;
        case kEditBoxInputModeSingleLine:
            m_systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
        default:
            m_systemControl.textField.keyboardType = UIKeyboardTypeDefault;
            break;
    }
}

void CCEditBoxImplIOS::setMaxLength(int maxLength)
{
    m_nMaxTextLength = maxLength;
}

int CCEditBoxImplIOS::getMaxLength()
{
    return m_nMaxTextLength;
}

void CCEditBoxImplIOS::setInputFlag(EditBoxInputFlag inputFlag)
{
    switch (inputFlag)
    {
        case kEditBoxInputFlagPassword:
            m_systemControl.textField.secureTextEntry = YES;
            break;
        case kEditBoxInputFlagInitialCapsWord:
            m_systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeWords;
            break;
        case kEditBoxInputFlagInitialCapsSentence:
            m_systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeSentences;
            break;
        case kEditBoxInputFlagInitialCapsAllCharacters:
            m_systemControl.textField.autocapitalizationType = UITextAutocapitalizationTypeAllCharacters;
            break;
        case kEditBoxInputFlagSensitive:
            m_systemControl.textField.autocorrectionType = UITextAutocorrectionTypeNo;
            break;
        default:
            break;
    }
}

void CCEditBoxImplIOS::setReturnType(KeyboardReturnType returnType)
{
    switch (returnType) {
        case kKeyboardReturnTypeDefault:
            m_systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
        case kKeyboardReturnTypeDone:
            m_systemControl.textField.returnKeyType = UIReturnKeyDone;
            break;
        case kKeyboardReturnTypeSend:
            m_systemControl.textField.returnKeyType = UIReturnKeySend;
            break;
        case kKeyboardReturnTypeSearch:
            m_systemControl.textField.returnKeyType = UIReturnKeySearch;
            break;
        case kKeyboardReturnTypeGo:
            m_systemControl.textField.returnKeyType = UIReturnKeyGo;
            break;
        default:
            m_systemControl.textField.returnKeyType = UIReturnKeyDefault;
            break;
    }
}

bool CCEditBoxImplIOS::isEditing()
{
    return [m_systemControl isEditState] ? true : false;
}

void CCEditBoxImplIOS::setText(const char* pText)
{
    m_systemControl.textField.text = [NSString stringWithUTF8String:pText];
	if(m_systemControl.textField.hidden == YES) {
		setInactiveText(pText);
		if(strlen(pText) == 0)
		{
			m_pLabel->setVisible(false);
			m_pLabelPlaceHolder->setVisible(true);
		}
		else
		{
			m_pLabel->setVisible(true);
			m_pLabelPlaceHolder->setVisible(false);
		}
	}
}

const char*  CCEditBoxImplIOS::getText(void)
{
    return [m_systemControl.textField.text UTF8String];
}

void CCEditBoxImplIOS::setPlaceHolder(const char* pText)
{
    m_systemControl.textField.placeholder = [NSString stringWithUTF8String:pText];
	m_pLabelPlaceHolder->setString(pText);
}

static CGPoint convertDesignCoordToScreenCoord(const CCPoint& designCoord, bool bInRetinaMode)
{
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
    float viewH = (float)[[EAGLView sharedEGLView] getHeight];
    
    CCPoint visiblePos = ccp(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    CCPoint screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    
    CGPoint screenPos = CGPointMake(screenGLPos.x, viewH - screenGLPos.y);
    
    if (bInRetinaMode)
    {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    CCLOG("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void CCEditBoxImplIOS::setPosition(const CCPoint& pos)
{
	m_obPosition = pos;
	adjustTextFieldPosition();
}

void CCEditBoxImplIOS::setVisible(bool visible)
{
//    m_systemControl.textField.hidden = !visible;
}

void CCEditBoxImplIOS::setContentSize(const CCSize& size)
{
    m_tContentSize = size;
    CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
    placeInactiveLabels();
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
    CGSize controlSize = CGSizeMake(size.width * eglView->getScaleX(),size.height * eglView->getScaleY());
    
    if (m_bInRetinaMode)
    {
        controlSize.width /= 2.0f;
        controlSize.height /= 2.0f;
    }
    [m_systemControl setContentSize:controlSize];
}

void CCEditBoxImplIOS::setAnchorPoint(const CCPoint& anchorPoint)
{
    CCLOG("[Edit text] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
	m_obAnchorPoint = anchorPoint;
	setPosition(m_obPosition);
}

void CCEditBoxImplIOS::visit(void)
{
    
}

void CCEditBoxImplIOS::onEnter(void)
{
    adjustTextFieldPosition();
    const char* pText = getText();
    if (pText) {
        setInactiveText(pText);
    }
}

void CCEditBoxImplIOS::adjustTextFieldPosition()
{
	CCSize contentSize = m_pEditBox->getContentSize();
	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
    rect = CCRectApplyAffineTransform(rect, m_pEditBox->nodeToWorldTransform());
	
	CCPoint designCoord = ccp(rect.origin.x, rect.origin.y + rect.size.height);
    [m_systemControl setPosition:convertDesignCoordToScreenCoord(designCoord, m_bInRetinaMode)];
}

void CCEditBoxImplIOS::openKeyboard()
{
	m_pLabel->setVisible(false);
	m_pLabelPlaceHolder->setVisible(false);

	m_systemControl.textField.hidden = NO;
    [m_systemControl openKeyboard];
}

void CCEditBoxImplIOS::closeKeyboard()
{
    [m_systemControl closeKeyboard];
}

void CCEditBoxImplIOS::onEndEditing()
{
	m_systemControl.textField.hidden = YES;
	if(strlen(getText()) == 0)
	{
		m_pLabel->setVisible(false);
		m_pLabelPlaceHolder->setVisible(true);
	}
	else
	{
		m_pLabel->setVisible(true);
		m_pLabelPlaceHolder->setVisible(false);
		setInactiveText(getText());
	}
}

NS_CC_EXT_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


