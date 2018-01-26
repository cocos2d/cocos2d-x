
#ifndef __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_
#define __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_

#include <string>
#include <vector>

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerFileDialogServiceProtocol : public PlayerServiceProtocol
{
public:
    /**
     * extensions = "Lua Script File|*.lua;JSON File|*.json";
     */
    virtual std::string openFile(const std::string &title,
                                 const std::string &directory,
                                 const std::string &extensions) const = 0;
    virtual std::vector<std::string> openMultiple(const std::string &title,
                                                  const std::string &directory,
                                                  const std::string &extensions) const = 0;
    virtual std::string saveFile(const std::string &title,
                                 const std::string &path) const = 0;
    virtual std::string openDirectory(const std::string &title,
                                      const std::string &directory) const = 0;
};

PLAYER_NS_END

#endif // __PLAYER_FILE_DIALOG_SERVICE_PROTOCOL_H_
