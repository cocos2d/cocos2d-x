/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

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

#include "network/Uri.h"
#include <stdlib.h>

NS_CC_BEGIN

namespace network {

Uri Uri::parse(const std::string& uri)
{
    Uri ret;
    ret._isSecure = false;
    ret._port = 80;

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
        ret._scheme = "ws";
    }
    else if (0 == uri.find("wss://"))
    {
        hostBegin += 6;
        ret._port = 443;
        ret._scheme = "wss";
        ret._isSecure = true;
    }
    else if (0 == uri.find("http://"))
    {
        hostBegin += 7;
        ret._scheme = "http";
    }
    else if (0 == uri.find("https://"))
    {
        hostBegin += 8;
        ret._port = 443;
        ret._scheme = "https";
        ret._isSecure = true;
    }
    else if ((tmp = uri.find("://")) != std::string::npos)
    {
        hostBegin = tmp + 3;
        ret._scheme.insert(0, uri.c_str(), tmp);
    }

    firstSlashPos = uri.find("/", hostBegin);
    firstQustionPos = uri.find("?", hostBegin);
    firstColonPos = uri.find(":", hostBegin);

    if (firstColonPos != std::string::npos
        && (firstSlashPos == std::string::npos || firstColonPos < firstSlashPos)
        && (firstQustionPos == std::string::npos || firstColonPos < firstQustionPos)
        )
    {
        ret._port = atoi(uri.c_str() + firstColonPos + 1);
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

    ret._host.insert(ret._host.begin(), uri.begin() + hostBegin, uri.begin() + hostEnd);

    if (pathBegin != std::string::npos)
    {
        if (uri[pathBegin] != '/')
        {
            ret._path = "/";
        }
        ret._path.insert(ret._path.end(), uri.begin() + pathBegin, uri.end());
    }
    else
    {
        ret._path = "/";
    }

    return ret;
}

bool Uri::isSecure() const
{
    return _isSecure;
}

const std::string& Uri::getScheme() const
{
    return _scheme;
}

const std::string& Uri::getHost() const
{
    return _host;
}

unsigned short Uri::getPort() const
{
    return _port;
}

const std::string& Uri::getPath() const
{
    return _path;
}

} // namespace network {

NS_CC_END
