/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 Copyright (c) 2013-2015 zilongshanren
 
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
#include "UIEditBoxImpl-ios.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#define kLabelZOrder  9999

#include "UIEditBox.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"
#import "platform/ios/CCEAGLView-ios.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "iOS/CCUIEditBoxIOS.h"

#define getEditBoxImplIOS() ((cocos2d::ui::EditBoxImplIOS *)_editBox)


NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplIOS(pEditBox);
}

EditBoxImplIOS::EditBoxImplIOS(EditBox* pEditText)
: EditBoxImplCommon(pEditText)
, _systemControl(nullptr)
, _anchorPoint(Vec2(0.5f, 0.5f))
{
    
}

EditBoxImplIOS::~EditBoxImplIOS()
{
    [_systemControl release];
    _systemControl = nil;
}
    
void EditBoxImplIOS::createNativeControl(const Rect& frame)
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    Rect rect(0, 0, frame.size.width * glview->getScaleX(), frame.size.height * glview->getScaleY());

    float factor = cocos2d::Director::getInstance()->getContentScaleFactor();

    rect.size.width /= factor;
    rect.size.height /= factor;
    
    _systemControl = [[UIEditBoxImplIOS_objc alloc] initWithFrame:CGRectMake(rect.origin.x,
                                                                             rect.origin.y,
                                                                             rect.size.width,
                                                                             rect.size.height)
                                                          editBox:this];

}

bool EditBoxImplIOS::isEditing()
{
    return [_systemControl isEditState] ? true : false;
}

void EditBoxImplIOS::doAnimationWhenKeyboardMove(float duration, float distance)
{
    if ([_systemControl isEditState] || distance < 0.0f) {
        [_systemControl doAnimationWhenKeyboardMoveWithDuration:duration distance:distance];
    }
}
    
void EditBoxImplIOS::setNativeFont(const char* pFontName, int fontSize)
{
    UIFont* textFont = constructFont(pFontName, fontSize);
    if (textFont != nil) {
        [_systemControl setFont:textFont];
    }
}
    
void EditBoxImplIOS::setNativeFontColor(const Color4B& color)
{
    _systemControl.textColor = [UIColor colorWithRed:color.r / 255.0f
                                                         green:color.g / 255.0f
                                                          blue:color.b / 255.0f
                                                         alpha:color.a / 255.f];

}

void EditBoxImplIOS::setNativePlaceholderFont(const char* pFontName, int fontSize)
{
    //TODO::
}

void EditBoxImplIOS::setNativePlaceholderFontColor(const Color4B& color)
{
    //TODO::
}

void EditBoxImplIOS::setNativeInputMode(EditBox::InputMode inputMode)
{
    [_systemControl setInputMode:inputMode];
}

void EditBoxImplIOS::setNativeInputFlag(EditBox::InputFlag inputFlag)
{
    [_systemControl setInputFlag:inputFlag];
}
    
NSString* removeSiriString(NSString* str)
{
    NSString* siriString = @"\xef\xbf\xbc";
    return [str stringByReplacingOccurrencesOfString:siriString withString:@""];
}

const char* EditBoxImplIOS::getText(void)
{
    return [removeSiriString(_systemControl.text) UTF8String];
}


void EditBoxImplIOS::setNativeReturnType(EditBox::KeyboardReturnType returnType)
{
    [_systemControl setReturnType:returnType];
}

void EditBoxImplIOS::setNativeText(const char* pText)
{
    NSString* nsText =[NSString stringWithUTF8String:pText];
    if ([nsText compare:_systemControl.text] != NSOrderedSame) {
        _systemControl.text = nsText;
    }
}

void EditBoxImplIOS::setNativePlaceHolder(const char* pText)
{
    [_systemControl setPlaceHolder:[NSString stringWithUTF8String:pText]];
}

void EditBoxImplIOS::setNativeVisible(bool visible)
{
    [_systemControl setVisible:visible];
}

void EditBoxImplIOS::updateNativeFrame(const Rect& rect)
{
    //no-op
}

void EditBoxImplIOS::setNativeContentSize(const Size& size)
{
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    CCEAGLView *eaglview = static_cast<CCEAGLView *>(glview->getEAGLView());
    float factor = eaglview.contentScaleFactor;
    
    [_systemControl setContentSize:CGSizeMake(size.width / factor, size.height / factor)];
}

const char* EditBoxImplIOS::getNativeDefaultFontName()
{
    const char* pDefaultFontName = [[_systemControl getDefaultFontName] UTF8String];
    return pDefaultFontName;
}

void EditBoxImplIOS::nativeOpenKeyboard()
{
    [_systemControl setVisible:YES];
    [_systemControl openKeyboard];
}

void EditBoxImplIOS::nativeCloseKeyboard()
{
    [_systemControl closeKeyboard];
}
    
UIFont* EditBoxImplIOS::constructFont(const char *fontName, int fontSize)
{
    CCASSERT(fontName != nullptr, "fontName can't be nullptr");
    CCEAGLView *eaglview = static_cast<CCEAGLView *>(cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView());
    float retinaFactor = eaglview.contentScaleFactor;
    NSString * fntName = [NSString stringWithUTF8String:fontName];
    
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float scaleFactor = glview->getScaleX();
    
    if (fontSize == -1)
    {
        fontSize = _systemControl.frameRect.size.height*2/3;
    }
    else
    {
        fontSize = fontSize * scaleFactor / retinaFactor;
    }
    
    UIFont *textFont = nil;
    if (strlen(fontName) > 0)
    {
        textFont = [UIFont fontWithName:fntName size:fontSize];
    }
    else
    {
        textFont = [UIFont systemFontOfSize:fontSize];
    }
    return textFont;
}
    
void EditBoxImplIOS::setPosition(const Vec2& pos)
{
    _position = pos;
    adjustTextFieldPosition();
}

void EditBoxImplIOS::setAnchorPoint(const Vec2& anchorPoint)
{
    CCLOG("[Edit text] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
    _anchorPoint = anchorPoint;
    setPosition(_position);
}

void EditBoxImplIOS::updatePosition(float dt)
{
    if (nullptr != _systemControl) {
        this->adjustTextFieldPosition();
    }
}

static CGPoint convertDesignCoordToScreenCoord(const Vec2& designCoord)
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    CCEAGLView *eaglview = (CCEAGLView *) glview->getEAGLView();
    
    float viewH = (float)[eaglview getHeight];
    
    Vec2 visiblePos = Vec2(designCoord.x * glview->getScaleX(), designCoord.y * glview->getScaleY());
    Vec2 screenGLPos = visiblePos + glview->getViewPortRect().origin;
    
    CGPoint screenPos = CGPointMake(screenGLPos.x, viewH - screenGLPos.y);
    
    float factor = eaglview.contentScaleFactor;
    screenPos.x = screenPos.x / factor;
    screenPos.y = screenPos.y / factor;
    
    CCLOGINFO("[EditBox] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}


void EditBoxImplIOS::adjustTextFieldPosition()
{
    Size contentSize = _editBox->getContentSize();
    Rect rect = Rect(0, 0, contentSize.width, contentSize.height);
    rect = RectApplyAffineTransform(rect, _editBox->nodeToWorldTransform());
    
    Vec2 designCoord = Vec2(rect.origin.x, rect.origin.y + rect.size.height);
    [_systemControl setPosition:convertDesignCoordToScreenCoord(designCoord)];
}

}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


