/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 Jozef Pridavok
 
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

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#include "ui/UIEditBox/UIEditBoxImpl-mac.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "ui/UIEditBox/Mac/CCUIEditBoxMac.h"

NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplMac(pEditBox);
}

EditBoxImplMac::EditBoxImplMac(EditBox* pEditText)
: EditBoxImplCommon(pEditText)
, _sysEdit(nullptr)
{
    //! TODO: Retina on Mac
    //! _inRetinaMode = [[CCEAGLView sharedEGLView] contentScaleFactor] == 2.0f ? true : false;
    _inRetinaMode = false;
}

EditBoxImplMac::~EditBoxImplMac()
{
    [_sysEdit release];
}

void EditBoxImplMac::createNativeControl(const cocos2d::Rect &frame)
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    Size size = frame.size;
    NSRect rect = NSMakeRect(0, 0,
                             size.width * glview->getScaleX(),
                             size.height * glview->getScaleY());
    
    float factor = cocos2d::Director::getInstance()->getContentScaleFactor();
    
    rect.size.width /= factor;
    rect.size.height /= factor;
    
    _sysEdit = [[UIEditBoxImplMac alloc] initWithFrame:rect editBox:this];
    this->setNativeVisible(false);
}
    
NSFont* EditBoxImplMac::constructFont(const char *fontName, int fontSize)
{
    NSString * fntName = [NSString stringWithUTF8String:fontName];
    fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
    float retinaFactor = _inRetinaMode ? 2.0f : 1.0f;
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float scaleFactor = glview->getScaleX();
    
    if (fontSize == -1)
    {
        NSRect frameRect = [_sysEdit.textInput frame];
        fontSize = frameRect.size.height*2/3;
    }
    else
    {
        fontSize = fontSize * scaleFactor / retinaFactor;
    }
    
    NSFont *textFont = nil;
    if (strlen(fontName) == 0)
    {
        textFont = [NSFont systemFontOfSize:fontSize];
    }
    else
    {
        textFont = [NSFont fontWithName:fntName size:fontSize];
        if (textFont == nil) {
            textFont = [NSFont systemFontOfSize:fontSize];
        }
    }
    
    return textFont;
}

void EditBoxImplMac::setNativeFont(const char *pFontName, int fontSize)
{
    NSFont* textFont = constructFont(pFontName, fontSize);
    [_sysEdit setFont:textFont];
}

void EditBoxImplMac::setNativePlaceholderFont(const char *pFontName, int fontSize)
{
    NSFont *textFont = constructFont(pFontName, fontSize);
    
    if (!textFont) {
        CCLOGWARN("Font not found: %s", pFontName);
        return;
    }
    [_sysEdit setPlaceholderFont:textFont];
}

void EditBoxImplMac::setNativeFontColor(const cocos2d::Color4B &color)
{
    NSColor *newColor = [NSColor colorWithCalibratedRed:color.r / 255.0f
                                                  green:color.g / 255.0f
                                                   blue:color.b / 255.0f
                                                  alpha:color.a / 255.f];

    [_sysEdit setTextColor:newColor];
}
    
void EditBoxImplMac::setNativePlaceholderFontColor(const cocos2d::Color4B &color)
{
    NSColor *newColor = [NSColor colorWithCalibratedRed:color.r/255.f
                                                 green:color.g / 255.f
                                                  blue:color.b / 255.f
                                                 alpha:color.a / 255.f];
    [_sysEdit setPlaceholderFontColor:newColor];
}

void EditBoxImplMac::setNativeInputMode(EditBox::InputMode inputMode)
{
    [_sysEdit setInputMode:inputMode];
    auto oldPosition = _editBox->getPosition();
    _editBox->setPosition(_editBox->getPosition() + Vec2(10,10));
    _editBox->setPosition(oldPosition);
}

void EditBoxImplMac::setNativeMaxLength(int maxLength)
{
    [_sysEdit setMaxLength:maxLength];
}


void EditBoxImplMac::setNativeInputFlag(EditBox::InputFlag inputFlag)
{
    [_sysEdit setInputFlag:inputFlag];
}

void EditBoxImplMac::setNativeReturnType(EditBox::KeyboardReturnType returnType)
{
    [_sysEdit setReturnType:returnType];
}

void EditBoxImplMac::setNativeTextHorizontalAlignment(cocos2d::TextHAlignment alignment)
{
    [_sysEdit setTextHorizontalAlignment:alignment];
}

bool EditBoxImplMac::isEditing()
{
    return [_sysEdit isEditState] ? true : false;
}

void EditBoxImplMac::setNativeText(const char *pText)
{
    NSString *text = [NSString stringWithUTF8String:pText];
    [_sysEdit setText:text];
}
    
void EditBoxImplMac::setNativePlaceHolder(const char* pText)
{
    [_sysEdit setPlaceHolder:pText];
}

void EditBoxImplMac::setNativeVisible(bool visible)
{
    [_sysEdit setVisible:visible];
}

void EditBoxImplMac::updateNativeFrame(const cocos2d::Rect &rect)
{
    GLView* eglView = Director::getInstance()->getOpenGLView();
    auto viewPortRect = eglView->getViewPortRect();
    // Coordinate System on OSX has its origin at the lower left corner.
//    https://developer.apple.com/library/ios/documentation/General/Conceptual/Devpedia-CocoaApp/CoordinateSystem.html
    auto screenPosY = viewPortRect.size.height - rect.origin.y - rect.size.height;
    [_sysEdit updateFrame:CGRectMake(rect.origin.x,
                                     screenPosY,
                                     rect.size.width, rect.size.height)];
}
    
const char* EditBoxImplMac::getNativeDefaultFontName()
{
    return [[_sysEdit getDefaultFontName] UTF8String];
}


void EditBoxImplMac::nativeOpenKeyboard()
{
    [_sysEdit setVisible:YES];
    [_sysEdit openKeyboard];
}

void EditBoxImplMac::nativeCloseKeyboard()
{
    [_sysEdit closeKeyboard];
}

}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)


