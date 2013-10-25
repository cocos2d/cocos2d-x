#ifndef ENUMDEF_H_
#define ENUMDEF_H_

namespace cocos3d
{

/**
* The touch event type.
*/
enum TouchEvent
{
    TouchEvent_PRESS,
    TouchEvent_RELEASE,
    TouchEvent_MOVE
};

/**
    * The mouse event type.
*/
enum MouseEvent
{
    MouseEvent_PRESS_LEFT_BUTTON,
    MouseEvent_RELEASE_LEFT_BUTTON,
    MouseEvent_PRESS_MIDDLE_BUTTON,
    MouseEvent_RELEASE_MIDDLE_BUTTON,
    MouseEvent_PRESS_RIGHT_BUTTON,
    MouseEvent_RELEASE_RIGHT_BUTTON,
    MouseEvent_MOVE,
    MouseEvent_WHEEL
};

/**
* The keyboard event.
*/
enum KeyEvent
{
    KeyEvent_PRESS,
    KeyEvent_RELEASE,
    KeyEvent_CHAR
};

/**
* The key (code).
*/
enum Keyboard_Key
{
    Keyboard_KEY_NONE              = 0,
    Keyboard_KEY_PAUSE             = 0x0013,
    Keyboard_KEY_SCROLL_LOCK       = 0x1014,
    Keyboard_KEY_PRINT             = 0x1061,
    Keyboard_KEY_SYSREQ            = 0x106A,
    Keyboard_KEY_BREAK             = 0x106B,
    Keyboard_KEY_ESCAPE            = 0x001B,
    Keyboard_KEY_BACKSPACE         = 0x0008,
    Keyboard_KEY_TAB               = 0x0009,
    Keyboard_KEY_BACK_TAB          = 0x0089,
    Keyboard_KEY_RETURN            = 0x000D,
    Keyboard_KEY_CAPS_LOCK         = 0x00E5,
    Keyboard_KEY_SHIFT             = 0x00E1,
    Keyboard_KEY_CTRL              = 0x00E3,
    Keyboard_KEY_ALT               = 0x00E9,
    Keyboard_KEY_MENU              = 0x1067,
    Keyboard_KEY_HYPER             = 0x10ED,
    Keyboard_KEY_INSERT            = 0x1063,
    Keyboard_KEY_HOME              = 0x1050,
    Keyboard_KEY_PG_UP             = 0x1055,
    Keyboard_KEY_DELETE            = 0x10FF,
    Keyboard_KEY_END               = 0x1057,
    Keyboard_KEY_PG_DOWN           = 0x1056,
    Keyboard_KEY_LEFT_ARROW        = 0x1051,
    Keyboard_KEY_RIGHT_ARROW       = 0x1053,
    Keyboard_KEY_UP_ARROW          = 0x1052,
    Keyboard_KEY_DOWN_ARROW        = 0x1054,
    Keyboard_KEY_NUM_LOCK          = 0x107F,
    Keyboard_KEY_KP_PLUS           = 0x10AB,
    Keyboard_KEY_KP_MINUS          = 0x10AD,
    Keyboard_KEY_KP_MULTIPLY       = 0x10AA,
    Keyboard_KEY_KP_DIVIDE         = 0x10AF,
    Keyboard_KEY_KP_ENTER          = 0x108D,
    Keyboard_KEY_KP_HOME           = 0x10B7,
    Keyboard_KEY_KP_UP             = 0x10B8,
    Keyboard_KEY_KP_PG_UP          = 0x10B9,
    Keyboard_KEY_KP_LEFT           = 0x10B4,
    Keyboard_KEY_KP_FIVE           = 0x10B5,
    Keyboard_KEY_KP_RIGHT          = 0x10B6,
    Keyboard_KEY_KP_END            = 0x10B1,
    Keyboard_KEY_KP_DOWN           = 0x10B2,
    Keyboard_KEY_KP_PG_DOWN        = 0x10B3,
    Keyboard_KEY_KP_INSERT         = 0x10B0,
    Keyboard_KEY_KP_DELETE         = 0x10AE,
    Keyboard_KEY_F1                = 0x00BE,
    Keyboard_KEY_F2                = 0x00BF,
    Keyboard_KEY_F3                = 0x00C0,
    Keyboard_KEY_F4                = 0x00C1,
    Keyboard_KEY_F5                = 0x00C2,
    Keyboard_KEY_F6                = 0x00C3,
    Keyboard_KEY_F7                = 0x00C4,
    Keyboard_KEY_F8                = 0x00C5,
    Keyboard_KEY_F9                = 0x00C6,
    Keyboard_KEY_F10               = 0x00C7,
    Keyboard_KEY_F11               = 0x00C8,
    Keyboard_KEY_F12               = 0x00C9,
    Keyboard_KEY_SPACE             = ' ',
    Keyboard_KEY_EXCLAM            = '!',
    Keyboard_KEY_QUOTE             = '"',
    Keyboard_KEY_NUMBER            = '#',
    Keyboard_KEY_DOLLAR            = '$',
    Keyboard_KEY_PERCENT           = '%',
    Keyboard_KEY_CIRCUMFLEX        = '^',
    Keyboard_KEY_AMPERSAND         = '&',
    Keyboard_KEY_APOSTROPHE        = '\'',
    Keyboard_KEY_LEFT_PARENTHESIS  = '(',
    Keyboard_KEY_RIGHT_PARENTHESIS = ')',
    Keyboard_KEY_ASTERISK          = '*',
    Keyboard_KEY_PLUS              = '+',
    Keyboard_KEY_COMMA             = ',',
    Keyboard_KEY_MINUS             = '-',
    Keyboard_KEY_PERIOD            = '.',
    Keyboard_KEY_SLASH             = '/',
    Keyboard_KEY_ZERO              = '0',
    Keyboard_KEY_ONE               = '1',
    Keyboard_KEY_TWO               = '2',
    Keyboard_KEY_THREE             = '3',
    Keyboard_KEY_FOUR              = '4',
    Keyboard_KEY_FIVE              = '5',
    Keyboard_KEY_SIX               = '6',
    Keyboard_KEY_SEVEN             = '7',
    Keyboard_KEY_EIGHT             = '8',
    Keyboard_KEY_NINE              = '9',
    Keyboard_KEY_COLON             = ':',
    Keyboard_KEY_SEMICOLON         = ';',
    Keyboard_KEY_LESS_THAN         = '<',
    Keyboard_KEY_EQUAL             = '=',
    Keyboard_KEY_GREATER_THAN      = '>',
    Keyboard_KEY_QUESTION          = '?',
    Keyboard_KEY_AT                = '@',
    Keyboard_KEY_CAPITAL_A         = 'A',
    Keyboard_KEY_CAPITAL_B         = 'B',
    Keyboard_KEY_CAPITAL_C         = 'C',
    Keyboard_KEY_CAPITAL_D         = 'D',
    Keyboard_KEY_CAPITAL_E         = 'E',
    Keyboard_KEY_CAPITAL_F         = 'F',
    Keyboard_KEY_CAPITAL_G         = 'G',
    Keyboard_KEY_CAPITAL_H         = 'H',
    Keyboard_KEY_CAPITAL_I         = 'I',
    Keyboard_KEY_CAPITAL_J         = 'J',
    Keyboard_KEY_CAPITAL_K         = 'K',
    Keyboard_KEY_CAPITAL_L         = 'L',
    Keyboard_KEY_CAPITAL_M         = 'M',
    Keyboard_KEY_CAPITAL_N         = 'N',
    Keyboard_KEY_CAPITAL_O         = 'O',
    Keyboard_KEY_CAPITAL_P         = 'P',
    Keyboard_KEY_CAPITAL_Q         = 'Q',
    Keyboard_KEY_CAPITAL_R         = 'R',
    Keyboard_KEY_CAPITAL_S         = 'S',
    Keyboard_KEY_CAPITAL_T         = 'T',
    Keyboard_KEY_CAPITAL_U         = 'U',
    Keyboard_KEY_CAPITAL_V         = 'V',
    Keyboard_KEY_CAPITAL_W         = 'W',
    Keyboard_KEY_CAPITAL_X         = 'X',
    Keyboard_KEY_CAPITAL_Y         = 'Y',
    Keyboard_KEY_CAPITAL_Z         = 'Z',
    Keyboard_KEY_LEFT_BRACKET      = '[',
    Keyboard_KEY_BACK_SLASH        = '\\',
    Keyboard_KEY_RIGHT_BRACKET     = ']',
    Keyboard_KEY_UNDERSCORE        = '_',
    Keyboard_KEY_GRAVE             = '`',
    Keyboard_KEY_A                 = 'a',
    Keyboard_KEY_B                 = 'b',
    Keyboard_KEY_C                 = 'c',
    Keyboard_KEY_D                 = 'd',
    Keyboard_KEY_E                 = 'e',
    Keyboard_KEY_F                 = 'f',
    Keyboard_KEY_G                 = 'g',
    Keyboard_KEY_H                 = 'h',
    Keyboard_KEY_I                 = 'i',
    Keyboard_KEY_J                 = 'j',
    Keyboard_KEY_K                 = 'k',
    Keyboard_KEY_L                 = 'l',
    Keyboard_KEY_M                 = 'm',
    Keyboard_KEY_N                 = 'n',
    Keyboard_KEY_O                 = 'o',
    Keyboard_KEY_P                 = 'p',
    Keyboard_KEY_Q                 = 'q',
    Keyboard_KEY_R                 = 'r',
    Keyboard_KEY_S                 = 's',
    Keyboard_KEY_T                 = 't',
    Keyboard_KEY_U                 = 'u',
    Keyboard_KEY_V                 = 'v',
    Keyboard_KEY_W                 = 'w',
    Keyboard_KEY_X                 = 'x',
    Keyboard_KEY_Y                 = 'y',
    Keyboard_KEY_Z                 = 'z',
    Keyboard_KEY_LEFT_BRACE        = '{',
    Keyboard_KEY_BAR               = '|',
    Keyboard_KEY_RIGHT_BRACE       = '}',
    Keyboard_KEY_TILDE             = '~',
    Keyboard_KEY_EURO              = 0x20AC,
    Keyboard_KEY_POUND             = 0x00A3,
    Keyboard_KEY_YEN               = 0x00A5,
    Keyboard_KEY_MIDDLE_DOT        = 0x0095,
    Keyboard_KEY_SEARCH            = 0xFFAA
};

}

#endif
