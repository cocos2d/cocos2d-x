/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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
#ifndef __CCX_PROTOCOL_USER_H__
#define __CCX_PROTOCOL_USER_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TUserDeveloperInfo;

typedef enum
{
    kLoginSucceed = 0,
    kLoginFailed,

    kLogoutSucceed,
} UserActionResultCode;

class ProtocolUser;
class UserActionListener
{
public:
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg) = 0;
};

class ProtocolUser : public PluginProtocol
{
public:
    ProtocolUser();
    virtual ~ProtocolUser();

    /**
    @brief config the application info
    @param devInfo This parameter is the info of aplication,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TUserDeveloperInfo devInfo);

    /**
     @brief User login
     */
    void login();

    /**
     @brief User logout
     */
    void logout();

    /**
     @brief Check whether the user logined or not
     */
    bool isLogined();

    /**
     @brief Get session ID
     @return If user logined, return value is session ID;
             else return value is empty string.
     */
    std::string getSessionID();

    inline void setActionListener(UserActionListener* listener)
    {
        _listener = listener;
    }

    inline UserActionListener* getActionListener()
    {
        return _listener;
    }

protected:
    UserActionListener* _listener;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_USER_H__ */
