
#ifndef __PLAYER_EDITBOX_SERVICE_WIN_H_
#define __PLAYER_EDITBOX_SERVICE_WIN_H_

#include "stdafx.h"
#include "PlayerEditBoxServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerEditBoxServiceWin : public PlayerEditBoxServiceProtocol
{
public:
    PlayerEditBoxServiceWin(HWND hwnd);
    virtual ~PlayerEditBoxServiceWin();

    virtual void showSingleLineEditBox(const cocos2d::Rect &rect);
    virtual void showMultiLineEditBox(const cocos2d::Rect &rect);
    virtual void hide();

    virtual void setText(const std::string &text);
    virtual void setFont(const std::string &name, int size);
    virtual void setFontColor(const cocos2d::Color3B &color);

    virtual void setFormator(int formator);
protected:
    HWND _hwnd;
    HWND _hwndSingle;
    HWND _hwndMulti;
    HFONT _hfont;

    void removeFont();
};

PLAYER_NS_END

#endif // __PLAYER_EDITBOX_SERVICE_WIN_H_
