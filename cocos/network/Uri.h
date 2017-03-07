#pragma once

#include "platform/CCPlatformMacros.h"

#include <string>

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

class Uri
{
public:
    static Uri parse(const std::string& uri)
    {
        Uri ret;
        ret.secure = false;
        ret.port = 80;

        size_t hostBegin = 0;
        size_t hostEnd = std::string::npos;
        size_t pathBegin = std::string::npos;
        size_t firstSlashPos = std::string::npos;
        size_t firstColonPos = std::string::npos;
        size_t firstQustionPos = std::string::npos;
        size_t tmp = std::string::npos;

        // Start with ws://
        if (0 == uri.find("ws://"))
        {
            hostBegin += 5;
            ret.scheme = "ws";
        }
        else if (0 == uri.find("wss://"))
        {
            hostBegin += 6;
            ret.port = 443;
            ret.scheme = "wss";
            ret.secure = true;
        }
        else if (0 == uri.find("http://"))
        {
            hostBegin += 7;
            ret.scheme = "http";
        }
        else if (0 == uri.find("https://"))
        {
            hostBegin += 8;
            ret.port = 443;
            ret.scheme = "https";
            ret.secure = true;
        }
        else if ((tmp = uri.find("://")) != std::string::npos)
        {
            hostBegin = tmp + 3;
            ret.scheme.insert(0, uri.c_str(), tmp);
        }

        firstSlashPos = uri.find("/", hostBegin);
        firstQustionPos = uri.find("?", hostBegin);
        firstColonPos = uri.find(":", hostBegin);

        if (firstColonPos != std::string::npos
            && (firstSlashPos == std::string::npos || firstColonPos < firstSlashPos)
            && (firstQustionPos == std::string::npos || firstColonPos < firstQustionPos)
            )
        {
            ret.port = atoi(uri.c_str() + firstColonPos + 1);
            hostEnd = firstColonPos;
        }

        if (firstSlashPos != std::string::npos)
        {
            pathBegin = firstSlashPos;
            if (hostEnd == std::string::npos)
            {
                hostEnd = firstSlashPos;
            }
        }
        else if (firstQustionPos != std::string::npos)
        {
            pathBegin = firstQustionPos;
            if (hostEnd == std::string::npos)
            {
                hostEnd = firstQustionPos;
            }
        }
        else
        {
            if (hostEnd == std::string::npos)
            {
                hostEnd = uri.length();
            }
        }

        ret.host.insert(ret.host.begin(), uri.begin() + hostBegin, uri.begin() + hostEnd);

        if (pathBegin != std::string::npos)
        {
            if (uri[pathBegin] != '/')
            {
                ret.path = "/";
            }
            ret.path.insert(ret.path.end(), uri.begin() + pathBegin, uri.end());
        }
        else
        {
            ret.path = "/";
        }

#if 0
        printf("-----------------------------\n");
        printf("scheme: %s\n", ret.scheme.c_str());
        printf("host: %s\n", ret.host.c_str());
        printf("port: %d\n", ret.port);
        printf("path: %s\n", ret.path.c_str());
#endif
        return ret;
    }

    bool secure;
    std::string scheme;
    std::string host;
    unsigned short port;
    std::string path;
};

} // namespace network {

NS_CC_END

// end group
/// @}
