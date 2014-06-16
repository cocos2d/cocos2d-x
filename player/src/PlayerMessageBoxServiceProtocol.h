//
//  PlaerMessageBoxServiceProtocol.h
//  quick-x-player
//

#ifndef __PLAYER_MESSAGEBOX_SERVICE_PROTOCOL_H
#define __PLAYER_MESSAGEBOX_SERVICE_PROTOCOL_H

#include <string>
#include <vector>

using namespace std;

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

typedef enum {
    MessageBoxOK,
    MessageBoxOKCancel,
    MessageBoxYesNo,
    MessageBoxYesNoCancel,
} MessageBoxButtonsType;

class PlayerMessageBoxServiceProtocol : public PlayerServiceProtocol
{
public:
    // 显示消息框，并返回用户选择按钮的索引
    //
    // @param title 消息框标题
    // @param message 消息框内容
    // @param buttons 消息框中要包含的按钮
    //
    // @return 点击第一个按钮返回 0，以此类推
    virtual int showMessageBox(const char *title,
                               const char *message,
                               MessageBoxButtonsType buttons = MessageBoxOK) = 0;
};

PLAYER_NS_END

#endif
