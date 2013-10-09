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

#ifndef __CC_KEYBOARDCONFIG_H__
#define __CC_KEYBOARDCONFIG_H__

#include "ccMacros.h"

NS_CC_BEGIN

class CCKeyboardConfig
{
public:
	
	enum CCTextAutocapitalizationType
	{
		kCCTextAutocapitalizationTypeNone,
		kCCTextAutocapitalizationTypeWords,
		kCCTextAutocapitalizationTypeSentences,
		kCCTextAutocapitalizationTypeAllCharacters,
	};
	
	enum CCKeyboardType
	{
		kCCKeyboardTypeDefault,
		kCCKeyboardTypeASCIICapable,
		kCCKeyboardTypeNumbersAndPunctuation,
		kCCKeyboardTypeURL,
		kCCKeyboardTypeNumberPad,
		kCCKeyboardTypePhonePad,
		kCCKeyboardTypeNamePhonePad,
		kCCKeyboardTypeEmailAddress,
		kCCKeyboardTypeDecimalPad,
		kCCKeyboardTypeTwitter,
		kCCKeyboardTypeWebSearch,
	};
	
	enum CCKeyboardAppearance
	{
		kCCKeyboardAppearanceDefault,
		kCCKeyboardAppearanceDark,
		kCCKeyboardAppearanceLight,
		kCCKeyboardAppearanceAlert,
	};
	
	enum CCReturnKeyType
	{
		kCCReturnKeyDefault,
		kCCReturnKeyGo,
		kCCReturnKeyGoogle,
		kCCReturnKeyJoin,
		kCCReturnKeyNext,
		kCCReturnKeyRoute,
		kCCReturnKeySearch,
		kCCReturnKeySend,
		kCCReturnKeyYahoo,
		kCCReturnKeyDone,
		kCCReturnKeyEmergencyCall,
	};

	
	CC_SYNTHESIZE(CCReturnKeyType, _returnKeyType, ReturnKeyType);
	CC_SYNTHESIZE(CCKeyboardAppearance, _keyboardAppearance, KeyboardAppearance);
	CC_SYNTHESIZE(CCTextAutocapitalizationType, _textAutocapitalizationType, TextAutocapitalizationType);
	CC_SYNTHESIZE(CCKeyboardType, _keyboatdType, KeyboardType);
	CC_SYNTHESIZE(bool, _spellChecking, SpellChecking);
	CC_SYNTHESIZE(bool, _autocorrection, Autocorrection);
	CC_SYNTHESIZE(bool, _enablesReturnKeyAutomatically, EnablesReturnKeyAutomatically);
	CC_SYNTHESIZE(bool, _secureTextEntry, SecureTextEntry);
	
public:
	
	static CCKeyboardConfig defaultConfig(void);
	
public:
	
	void setToDefault(void);
	CCKeyboardConfig(void);
};


NS_CC_END

#endif    // __CC_KEYBOARDCONFIG_H__
