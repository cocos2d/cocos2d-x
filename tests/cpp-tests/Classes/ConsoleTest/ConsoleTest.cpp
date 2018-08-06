/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "ConsoleTest.h"
#include "../testResource.h"
#include <stdio.h>
#include <stdlib.h>
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#else
#include <io.h>
#include <WS2tcpip.h>
#endif

USING_NS_CC;

//------------------------------------------------------------------
//
// ConsoleTest
//
//------------------------------------------------------------------

ConsoleTests::ConsoleTests()
{
    ADD_TEST_CASE(ConsoleCustomCommand);
    ADD_TEST_CASE(ConsoleUploadFile);
}

BaseTestConsole::BaseTestConsole()
{
}

BaseTestConsole::~BaseTestConsole(void)
{
}

std::string BaseTestConsole::title() const
{
    return "No title";
}

//------------------------------------------------------------------
//
// ConsoleCustomCommand
//
//------------------------------------------------------------------

ConsoleCustomCommand::ConsoleCustomCommand()
{
    _console = Director::getInstance()->getConsole();
    static Console::Command commands[] = {
        {"hello", "This is just a user generated command", [](int fd, const std::string& args) {
            const char msg[] = "how are you?\nArguments passed: ";
            send(fd, msg, sizeof(msg),0);
            send(fd, args.c_str(), args.length(),0);
            send(fd, "\n",1,0);
        }},
    };
    _console->addCommand(commands[0]);
}

ConsoleCustomCommand::~ConsoleCustomCommand()
{
}

void ConsoleCustomCommand::onEnter()
{
    BaseTestConsole::onEnter();
}

std::string ConsoleCustomCommand::title() const
{
    return "Console Custom Commands";
}

std::string ConsoleCustomCommand::subtitle() const
{
    return "telnet localhost 5678";
}


//------------------------------------------------------------------
//
// ConsoleUploadFile
//
//------------------------------------------------------------------

ConsoleUploadFile::ConsoleUploadFile()
{
    std::srand ((unsigned)time(nullptr));
    int id = rand()%100000;
    char buf[32];
    sprintf(buf, "%d", id);
    _targetFileName = std::string("grossini") + buf + ".png";

    std::thread t = std::thread( &ConsoleUploadFile::uploadFile, this);
    t.detach();
}

void ConsoleUploadFile::onEnter()
{
    BaseTestConsole::onEnter();
    
}

ConsoleUploadFile::~ConsoleUploadFile()
{
    
}

void ConsoleUploadFile::uploadFile()
{
    Data srcFileData = FileUtils::getInstance()->getDataFromFile(s_pathGrossini);
    if (srcFileData.isNull())
    {
        CCLOGERROR("ConsoleUploadFile: could not open file %s", s_pathGrossini);
    }

    std::string targetFileName = _targetFileName;

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* stream socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif

    std::string nodeName;
    if (Director::getInstance()->getConsole()->isIpv6Server())
        nodeName = "::1";
    else
        nodeName = "localhost";

    s = getaddrinfo(nodeName.c_str(), "5678", &hints, &result);
    if (s != 0) 
    {
        CCLOG("ConsoleUploadFile: getaddrinfo error");
        return;
    }

    /* getaddrinfo() returns a list of address structures.
      Try each address until we successfully connect(2).
      If socket(2) (or connect(2)) fails, we (close the socket
      and) try the next address. */

    for (rp = result; rp != nullptr; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                    rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        closesocket(sfd);
#else
        close(sfd);
#endif
    }

    if (rp == nullptr) {               /* No address succeeded */
        CCLOG("ConsoleUploadFile: could not connect!");
        return;
    }

    freeaddrinfo(result);           /* No longer needed */

    std::string tmp = "upload";

    tmp += " ";
    tmp += targetFileName;
    tmp += " ";
    char cmd[512] = {0};

    strcpy(cmd, tmp.c_str());
    send(sfd,cmd,strlen(cmd),0);

    size_t offset = 0;
    auto readBuffer = [&offset](char* buf, size_t bytes, const Data& data) -> ssize_t {
        if (offset >= data.getSize())
            return 0;
        ssize_t actualReadBytes = (offset + bytes) > data.getSize() ? (data.getSize() - offset) : bytes;
        if (actualReadBytes > 0)
        {
            memcpy(buf, data.getBytes() + offset, actualReadBytes);
            offset += actualReadBytes;
        }
        return actualReadBytes;
    };

    while(true)
    {
        char buffer[3], *out;
        unsigned char *in;
        in = (unsigned char *)buffer;
        // copy the file into the buffer:
        ssize_t ret = readBuffer(buffer, 3, srcFileData);
        if (ret > 0)
        {
            int len = base64Encode(in, (unsigned int)ret, &out);
            send(sfd, out, len, 0);
            free(out);
            if(ret < 3)
            {
                //eof
                log("Reach the end, total send: %d bytes", (int)offset);
                break;
            }
        }
        else
        {
            //read error
            break;
        }
    }
    char l = '\n';
    send(sfd, &l, 1, 0);

    // Sleep 1s to wait server to receive all data.
    std::this_thread::sleep_for(std::chrono::seconds(1));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    closesocket(sfd);
    WSACleanup();
#else
    close(sfd);
#endif
}

std::string ConsoleUploadFile::title() const
{
    return "Console UploadFile";
}

std::string ConsoleUploadFile::subtitle() const
{
    auto sharedFileUtils = FileUtils::getInstance();
    
    std::string writablePath = sharedFileUtils->getWritablePath();

    return "file uploaded to:" + writablePath + _targetFileName;
}

