
#include "PlayerMessageBoxServiceWin.h"

PLAYER_NS_BEGIN

PlayerMessageBoxServiceWin::PlayerMessageBoxServiceWin(HWND hwnd)
: _hwnd(hwnd)
{
}

int PlayerMessageBoxServiceWin::showMessageBox(const std::string &title,
                                               const std::string &message,
                                               int buttonsType /* = BUTTONS_OK */)
{
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(title, u16title);
    std::u16string u16message;
    cocos2d::StringUtils::UTF8ToUTF16(message, u16message);

    CCLOG("PlayerMessageBoxServiceWin::showMessageBox() - title = %s, message = %s", title.c_str(), message.c_str());

    UINT mbtype = MB_APPLMODAL;
    switch (buttonsType)
    {
    case BUTTONS_OK_CANCEL:
        mbtype |= MB_OKCANCEL | MB_ICONQUESTION;
        break;

    case BUTTONS_YES_NO:
        mbtype |= MB_YESNO | MB_ICONQUESTION;
        break;

    case BUTTONS_YES_NO_CANCEL:
        mbtype |= MB_YESNOCANCEL | MB_ICONQUESTION;
        break;

    default:
        mbtype |= MB_OK | MB_ICONINFORMATION;
    }

    // MessageBox() used by cocos2d
    int result = ::MessageBoxW(_hwnd, (LPCTSTR)u16message.c_str(), (LPCTSTR)u16title.c_str(), mbtype);

    switch (result)
    {
    case IDCANCEL:
        result = BUTTON_CANCEL;
        break;

    case IDYES:
        result = BUTTON_YES;
        break;

    case IDNO:
        result = BUTTON_NO;
        break;

    default:
        result = BUTTON_OK;
    }

    CCLOG("PlayerMessageBoxServiceWin::showMessageBox() - result = %d", result);

    return result;
}

PLAYER_NS_END
