/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
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

#ifndef __CC_Keyboard_H__
#define __CC_Keyboard_H__

#include "cocoa/CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */

class CC_DLL CCKeyboard : public CCObject
{
public:
    CCKeyboard()
    : m_nId(0), m_ccCharSequence(NULL), m_bShiftKeyPressed(false), m_bControlKeyPressed(false), m_bAltKeyPressed(false), m_bCommandKeyPressed(false)
    {}
    
    void setKeyboardInfo(unsigned int keyCode, const char* charSequence, unsigned int modifiers, bool shiftKeyPressed, bool controlKeyPressed, bool altKeyPressed, bool commandKeyPressed);
    
    /** Returns key without any modifiers. */
    unsigned int getKey();
    
    /** Some keys are actually sequences. This gets the first key in that sequence. */
    const char getFirstKey() const;

    const char* getKeySequence() const;

    unsigned int getModifiers();
    
    bool isShiftKeyPressed();
    bool isControlKeyPressed();
    bool isAltKeyPressed();
    bool isCommandKeyPressed();
    
    int getID() const
    {
        return m_nId;
    }
    
private:
    int m_nId;
    unsigned int m_unKeyCode;
    const char* m_ccCharSequence;
    unsigned int m_unModifiers;
    bool m_bShiftKeyPressed;
    bool m_bControlKeyPressed;
    bool m_bAltKeyPressed;
    bool m_bCommandKeyPressed;
};

// end of input group
/// @}

NS_CC_END

#endif  // __PLATFORM_Keyboard_H__
