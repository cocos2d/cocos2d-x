
#ifndef __PLAYER_FILE_DIALOG_SERVICE_WIN_H_
#define __PLAYER_FILE_DIALOG_SERVICE_WIN_H_

#include "stdafx.h"
#include "PlayerFileDialogServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerFileDialogServiceWin : public PlayerFileDialogServiceProtocol
{
public:
    PlayerFileDialogServiceWin(HWND hwnd);

    virtual std::string openFile(const std::string &title,
                                 const std::string &directory,
                                 const std::string &extensions) const;
    virtual std::vector<std::string> openMultiple(const std::string &title,
                                                  const std::string &directory,
                                                  const std::string &extensions) const;
    virtual std::string saveFile(const std::string &title,
                                 const std::string &path) const;
    virtual std::string openDirectory(const std::string &title,
                                      const std::string &directory) const;

protected:
    HWND _hwnd;

    LPTSTR parseExtensions(const std::string &extensions) const;
    vector<std::string> openMultipleInternal(const std::string &title,
                                             const std::string &directory,
                                             const std::string &extensions,
                                             bool isMulti) const;
};

PLAYER_NS_END

#endif // __PLAYER_FILE_DIALOG_SERVICE_WIN_H_
