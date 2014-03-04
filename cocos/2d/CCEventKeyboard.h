/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_libs__CCKeyboardEvent__
#define __cocos2d_libs__CCKeyboardEvent__

#include "CCEvent.h"

NS_CC_BEGIN

class EventKeyboard : public Event
{
public:
    /**
     * The key (code).
     */
    enum class KeyCode
    {
        KEY_NONE              = 0,
        KEY_PAUSE             = 0x0013,
        KEY_SCROLL_LOCK       = 0x1014,
        KEY_PRINT             = 0x1061,
        KEY_SYSREQ            = 0x106A,
        KEY_BREAK             = 0x106B,
        KEY_ESCAPE            = 0x001B,
        KEY_BACKSPACE         = 0x0008,
        KEY_TAB               = 0x0009,
        KEY_BACK_TAB          = 0x0089,
        KEY_RETURN            = 0x000D,
        KEY_CAPS_LOCK         = 0x00E5,
        KEY_SHIFT             = 0x00E1,
        KEY_CTRL              = 0x00E3,
        KEY_ALT               = 0x00E9,
        KEY_MENU              = 0x1067,
        KEY_HYPER             = 0x10ED,
        KEY_INSERT            = 0x1063,
        KEY_HOME              = 0x1050,
        KEY_PG_UP             = 0x1055,
        KEY_DELETE            = 0x10FF,
        KEY_END               = 0x1057,
        KEY_PG_DOWN           = 0x1056,
        KEY_LEFT_ARROW        = 0x1051,
        KEY_RIGHT_ARROW       = 0x1053,
        KEY_UP_ARROW          = 0x1052,
        KEY_DOWN_ARROW        = 0x1054,
        KEY_NUM_LOCK          = 0x107F,
        KEY_KP_PLUS           = 0x10AB,
        KEY_KP_MINUS          = 0x10AD,
        KEY_KP_MULTIPLY       = 0x10AA,
        KEY_KP_DIVIDE         = 0x10AF,
        KEY_KP_ENTER          = 0x108D,
        KEY_KP_HOME           = 0x10B7,
        KEY_KP_UP             = 0x10B8,
        KEY_KP_PG_UP          = 0x10B9,
        KEY_KP_LEFT           = 0x10B4,
        KEY_KP_FIVE           = 0x10B5,
        KEY_KP_RIGHT          = 0x10B6,
        KEY_KP_END            = 0x10B1,
        KEY_KP_DOWN           = 0x10B2,
        KEY_KP_PG_DOWN        = 0x10B3,
        KEY_KP_INSERT         = 0x10B0,
        KEY_KP_DELETE         = 0x10AE,
        KEY_F1                = 0x00BE,
        KEY_F2                = 0x00BF,
        KEY_F3                = 0x00C0,
        KEY_F4                = 0x00C1,
        KEY_F5                = 0x00C2,
        KEY_F6                = 0x00C3,
        KEY_F7                = 0x00C4,
        KEY_F8                = 0x00C5,
        KEY_F9                = 0x00C6,
        KEY_F10               = 0x00C7,
        KEY_F11               = 0x00C8,
        KEY_F12               = 0x00C9,
        KEY_SPACE             = ' ',
        KEY_EXCLAM            = '!',
        KEY_QUOTE             = '"',
        KEY_NUMBER            = '#',
        KEY_DOLLAR            = '$',
        KEY_PERCENT           = '%',
        KEY_CIRCUMFLEX        = '^',
        KEY_AMPERSAND         = '&',
        KEY_APOSTROPHE        = '\'',
        KEY_LEFT_PARENTHESIS  = '(',
        KEY_RIGHT_PARENTHESIS = ')',
        KEY_ASTERISK          = '*',
        KEY_PLUS              = '+',
        KEY_COMMA             = ',',
        KEY_MINUS             = '-',
        KEY_PERIOD            = '.',
        KEY_SLASH             = '/',
        KEY_0                 = '0',
        KEY_1                 = '1',
        KEY_2                 = '2',
        KEY_3                 = '3',
        KEY_4                 = '4',
        KEY_5                 = '5',
        KEY_6                 = '6',
        KEY_7                 = '7',
        KEY_8                 = '8',
        KEY_9                 = '9',
        KEY_COLON             = ':',
        KEY_SEMICOLON         = ';',
        KEY_LESS_THAN         = '<',
        KEY_EQUAL             = '=',
        KEY_GREATER_THAN      = '>',
        KEY_QUESTION          = '?',
        KEY_AT                = '@',
        KEY_CAPITAL_A         = 'A',
        KEY_CAPITAL_B         = 'B',
        KEY_CAPITAL_C         = 'C',
        KEY_CAPITAL_D         = 'D',
        KEY_CAPITAL_E         = 'E',
        KEY_CAPITAL_F         = 'F',
        KEY_CAPITAL_G         = 'G',
        KEY_CAPITAL_H         = 'H',
        KEY_CAPITAL_I         = 'I',
        KEY_CAPITAL_J         = 'J',
        KEY_CAPITAL_K         = 'K',
        KEY_CAPITAL_L         = 'L',
        KEY_CAPITAL_M         = 'M',
        KEY_CAPITAL_N         = 'N',
        KEY_CAPITAL_O         = 'O',
        KEY_CAPITAL_P         = 'P',
        KEY_CAPITAL_Q         = 'Q',
        KEY_CAPITAL_R         = 'R',
        KEY_CAPITAL_S         = 'S',
        KEY_CAPITAL_T         = 'T',
        KEY_CAPITAL_U         = 'U',
        KEY_CAPITAL_V         = 'V',
        KEY_CAPITAL_W         = 'W',
        KEY_CAPITAL_X         = 'X',
        KEY_CAPITAL_Y         = 'Y',
        KEY_CAPITAL_Z         = 'Z',
        KEY_LEFT_BRACKET      = '[',
        KEY_BACK_SLASH        = '\\',
        KEY_RIGHT_BRACKET     = ']',
        KEY_UNDERSCORE        = '_',
        KEY_GRAVE             = '`',
        KEY_A                 = 'a',
        KEY_B                 = 'b',
        KEY_C                 = 'c',
        KEY_D                 = 'd',
        KEY_E                 = 'e',
        KEY_F                 = 'f',
        KEY_G                 = 'g',
        KEY_H                 = 'h',
        KEY_I                 = 'i',
        KEY_J                 = 'j',
        KEY_K                 = 'k',
        KEY_L                 = 'l',
        KEY_M                 = 'm',
        KEY_N                 = 'n',
        KEY_O                 = 'o',
        KEY_P                 = 'p',
        KEY_Q                 = 'q',
        KEY_R                 = 'r',
        KEY_S                 = 's',
        KEY_T                 = 't',
        KEY_U                 = 'u',
        KEY_V                 = 'v',
        KEY_W                 = 'w',
        KEY_X                 = 'x',
        KEY_Y                 = 'y',
        KEY_Z                 = 'z',
        KEY_LEFT_BRACE        = '{',
        KEY_BAR               = '|',
        KEY_RIGHT_BRACE       = '}',
        KEY_TILDE             = '~',
        KEY_EURO              = 0x20AC,
        KEY_POUND             = 0x00A3,
        KEY_YEN               = 0x00A5,
        KEY_MIDDLE_DOT        = 0x0095,
        KEY_SEARCH            = 0xFFAA
    };
    
    EventKeyboard(KeyCode keyCode, bool isPressed);
    
private:
    KeyCode _keyCode;
    bool _isPressed;
    
    friend class EventListenerKeyboard;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCKeyboardEvent__) */
