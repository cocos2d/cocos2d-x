#ifndef __PLAY_FILE_DIALOG_SERVICE_MAC_H
#define __PLAY_FILE_DIALOG_SERVICE_MAC_H

#include "PlayerMacros.h"
#include "PlayerFileDialogServiceProtocol.h"

PLAYER_NS_BEGIN

class FileDialogServiceMac : public PlayerFileDialogServiceProtocol
{
public:
    // 选择一个已有的文件，并返回文件的完整路径
    // 如果用户取消对话框，返回空字符串
    //
    // @param title 对话框标题
    // @param directory 默认打开的目录
    //
    // 如果 directory 不为空，则对话框打开时，直接进入 directory 参数指定的目录；
    // 否则进入进程当前目录（Current Directory）。
    //
    // @param extensions 用于限制可以打开的文件类型
    //
    // extensions 示例：
    // "Markdown File|md,mdown\nHTML File|htm,html"
    //
    // 每一种类型分为“描述”和“扩展名”两部分，用“|”分隔
    // 扩展名如果有多个，则用“,”分隔
    // 不同类型用“\n”分隔
    //
    // 如果 extensions 参数为空，则表示可以选择任何扩展名的文件。
    //
    virtual string openFile(const char *title,
                            const char *directory = NULL,
                            const char *extensions = NULL);

    virtual string openDirectory(const char *title,
                                const char *directory = NULL);

    virtual vector<string> openMultiple(const char *title,
                                        const char *directory = NULL);

    virtual string saveFile(const char *title,
                            const char *filename,
                            const char *directory);

};

PLAYER_NS_END

#endif // __PLAY_FILE_DIALOG_SERVICE_MAC_H