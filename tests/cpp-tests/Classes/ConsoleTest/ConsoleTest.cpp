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

#include "ConsoleTest.h"
#include "../testResource.h"
#include <stdio.h>
#include <stdlib.h>
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netdb.h>
#else
#include <io.h>
#include <WS2tcpip.h>
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
#include "CCWinRTUtils.h"
#include <sstream>
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
#define SO_NOSIGPIPE MSG_NOSIGNAL
#endif
//------------------------------------------------------------------
//
// ConsoleTest
//
//------------------------------------------------------------------

static int sceneIdx = -1;

static std::function<Layer*()> createFunctions[] =
{
#if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8))
    CL(ConsoleRemoteControl),
#endif
    CL(ConsoleCustomCommand),
    CL(ConsoleUploadFile),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextConsoleTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backConsoleTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartConsoleTest()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
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

void BaseTestConsole::onEnter()
{
    BaseTest::onEnter();
}

void BaseTestConsole::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) ConsoleTestScene();
    s->addChild(restartConsoleTest());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseTestConsole::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) ConsoleTestScene();
    s->addChild( nextConsoleTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseTestConsole::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) ConsoleTestScene();
    s->addChild( backConsoleTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void ConsoleTestScene::runThisTest()
{
    auto layer = nextConsoleTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

#if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8))
//------------------------------------------------------------------
//
// ConsoleRemoteControl
//
//------------------------------------------------------------------
ConsoleRemoteControl::ConsoleRemoteControl()
{
    _endListen = false;
    _connected = false;
    _listenThread = std::thread( std::bind( &ConsoleRemoteControl::startListenRemoteConsole, this) );
}

//------------------------------------------------------------------
//
// startListenRemoteConsole
//
//------------------------------------------------------------------
int ConsoleRemoteControl::startListenRemoteConsole()
{
    struct sockaddr_in myaddr;      /* our address */
    struct sockaddr_in remaddr;     /* remote address */
    socklen_t addrlen = sizeof(remaddr);            /* length of addresses */
    int recvlen;                    /* # bytes received */
    int fd;                         /* our socket */
    const int PORT = 4444;
    const int BUFLEN = 2048;
    unsigned char buf[BUFLEN];     /* receive buffer */

// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//     WSADATA wsaData;
//     WSAStartup(MAKEWORD(2, 2),&wsaData);
// #endif
    /* create a UDP socket */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("cannot create socket\n");
            return -1;
    }

    /* bind the socket to any valid IP address and a specific port */

    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(PORT);

    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
            perror("bind failed");
            return 0;
    }
    CCLOG("ConsoleRemoteControl:Create listen socket on %d successfully!", PORT);
    /* now loop, receiving data and printing what we received */
    while (!_endListen) {
            //CCLOG("Listen on port %d\n", PORT);
            recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &addrlen);
            //printf("received %d bytes\n", recvlen);
            if (recvlen > 0) {
                    buf[recvlen] = 0;
                    CCLOG("received message: \"%s\"\n", buf);
                char *msg = (char *)&buf[0];
                std::string addr = std::string(msg);
                auto _console = Director::getInstance()->getConsole();
                auto _ipList = _console->getLocalIPList();
                bool isLocalIp = false;
                for(auto &ip : _ipList)
                {
                    if(ip == addr)
                    {
                        isLocalIp = true;
                        break;
                    }
                }
                if (isLocalIp == true)
                {
                    continue;
                }
                int n = addr.find_last_of('.');
                std::string subnet = addr.substr(0, n);
                //CCLOG("subnet:%s\n", subnet.c_str());
                for(auto &ip : _ipList)
                {
                    //CCLOG("ip:%s\n", ip.c_str());
                    if(subnet == ip.substr(0, n))
                    {
                        connectRemoteConsole(addr);
                        _endListen = true;
                        break;
                    }
                }
            }
    }
    CCLOG("ConsoleRemoteControl:close listen socket.");
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//         closesocket(fd);
// #else
        close(fd);
//#endif
    return 0;
}


//------------------------------------------------------------------
//
// connectRemoteConsole
//
//------------------------------------------------------------------

void ConsoleRemoteControl::connectRemoteConsole(std::string& ip)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* stream socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */


    s = getaddrinfo(ip.c_str(), "5678", &hints, &result);
    if (s != 0) 
    {
       CCLOG("ConsoleRemoteControl: getaddrinfo error");
        return;
    }

    /* getaddrinfo() returns a list of address structures.
      Try each address until we successfully connect(2).
      If socket(2) (or connect(2)) fails, we (close the socket
      and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        _sfd = socket(rp->ai_family, rp->ai_socktype,
                    rp->ai_protocol);
        if (_sfd == -1)
            continue;

        if (connect(_sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//         closesocket(_sfd);
// #else
        close(_sfd);
//#endif
    }

    if (rp == NULL) {               /* No address succeeded */
        CCLOG("ConsoleRemoteControl: could not connect!");
        return;
    }
    freeaddrinfo(result);           /* No longer needed */
    int one = 1;
    setsockopt(_sfd, IPPROTO_TCP,TCP_NODELAY, &one, sizeof(one));
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
    int set = 1;
    setsockopt(_sfd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
#endif
    std::string tmp = "resolution\n";
     
    char cmd[512];
    strcpy(cmd, tmp.c_str());
    int ret = send(_sfd,cmd,strlen(cmd),0);
    if (ret > 0)
    {
        _connected = true;
    }
    _listener = EventListenerTouchAllAtOnce::create();
    _listener->onTouchesBegan = CC_CALLBACK_2(ConsoleRemoteControl::onTouchesBegan, this);
    _listener->onTouchesMoved = CC_CALLBACK_2(ConsoleRemoteControl::onTouchesMoved, this);
    _listener->onTouchesEnded = CC_CALLBACK_2(ConsoleRemoteControl::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
    CCLOG("ConsoleRemoteControl: connect to remote console successfully!");
    _labelSubTitle->setString("connected to " + ip + "successfully!");
}

ConsoleRemoteControl::~ConsoleRemoteControl()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        closesocket(_sfd);
        WSACleanup();
#else
        close(_sfd);
#endif
    _endListen = true;
    _listenThread.join();
    return;
}

void ConsoleRemoteControl::onEnter()
{
    BaseTestConsole::onEnter();
    
    std::string strSubtitle = "Initializing...";
    if( ! strSubtitle.empty() )
    {
        TTFConfig ttfConfig("fonts/arial.ttf", 32);
        ttfConfig.fontFilePath = "fonts/Thonburi.ttf";
        ttfConfig.fontSize = 16;
        _labelSubTitle = Label::createWithTTF(ttfConfig,strSubtitle.c_str());
        addChild(_labelSubTitle, 9999);
        _labelSubTitle->setPosition( Vec2(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }
}

std::string ConsoleRemoteControl::title() const
{
    return "Console remote control";
}

std::string ConsoleRemoteControl::subtitle() const
{
    return "";
}

void ConsoleRemoteControl::sendTouchCommand(const std::vector<Touch*>& touches, std::string& _cmd)
{
    auto director = Director::getInstance();
    Size points = director->getWinSize();
    if (!_connected)
    {
        return;
    }
    for (auto touch: touches)
    {
        auto location = touch->getLocation();
        //CCLOG("onTouchesMoved:%f, %f",location.x, location.y);
        //addNewSpriteWithCoords( location );
        std::string tmp = _cmd;
        char buf[30];
        tmp += " ";
        snprintf(buf, sizeof(buf)-1, "%f", location.x/points.width);
        tmp += buf;
        tmp += " ";
        snprintf(buf, sizeof(buf)-1, "%f", location.y/points.height);
        tmp += buf;
        tmp += "\n";
        char cmd[512];
        
        strcpy(cmd, tmp.c_str());
        //CCLOG("%s", cmd);
        int ret = send(_sfd,cmd,strlen(cmd),0);
        if (ret < 0)
        {
            CCLOG("connection lost!");
            _connected = false;
            _labelSubTitle->setString("Connection lost!");
        }
        
    }
}

void ConsoleRemoteControl::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    std::string cmd = "touch begin";
    sendTouchCommand(touches,cmd);
}

void ConsoleRemoteControl::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    std::string cmd = "touch move";
    sendTouchCommand(touches,cmd);
 }

void ConsoleRemoteControl::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    std::string cmd = "touch end";
    sendTouchCommand(touches,cmd);
 }

 #endif
//------------------------------------------------------------------
//
// ConsoleCustomCommand
//
//------------------------------------------------------------------

ConsoleCustomCommand::ConsoleCustomCommand()
{
    _console = Director::getInstance()->getConsole();
    static struct Console::Command commands[] = {
        {"hello", "This is just a user generated command", [](int fd, const std::string& args) {
            const char msg[] = "how are you?\nArguments passed: ";
            send(fd, msg, sizeof(msg),0);
            send(fd, args.c_str(), args.length(),0);
            send(fd, "\n",1,0);
        }},
    };
    _console->addCommand(commands[0]);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

    std::stringstream ss;
    ss << "WP8 Device IP Addresses:" << std::endl;
    ss << getDeviceIPAddresses();

    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto label = LabelTTF::create(ss.str(), "Arial", 12);

    // position the label on the center of the screen
    label->setPosition(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + (label->getContentSize().height/2));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
#endif
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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
    return "telnet [ip address] 5678";
#else
    return "telnet localhost 5678";
#endif
}


//------------------------------------------------------------------
//
// ConsoleUploadFile
//
//------------------------------------------------------------------

ConsoleUploadFile::ConsoleUploadFile()
{
    srand ((unsigned)time(nullptr));
    int _id = rand()%100000;
    char buf[32];
    sprintf(buf, "%d", _id);
    _target_file_name = std::string("grossini") + buf;

    _src_file_path = FileUtils::getInstance()->fullPathForFilename(s_pathGrossini);
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
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* stream socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif

    s = getaddrinfo("localhost", "5678", &hints, &result);
    if (s != 0) 
    {
       CCLOG("ConsoleUploadFile: getaddrinfo error");
        return;
    }

    /* getaddrinfo() returns a list of address structures.
      Try each address until we successfully connect(2).
      If socket(2) (or connect(2)) fails, we (close the socket
      and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                    rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        closesocket(sfd);
#else
        close(sfd);
#endif
    }

    if (rp == NULL) {               /* No address succeeded */
        CCLOG("ConsoleUploadFile: could not connect!");
        return;
    }

    freeaddrinfo(result);           /* No longer needed */

    
    FILE* fp = fopen(_src_file_path.c_str(), "rb");
    if(!fp)
    {
        CCLOG("ConsoleUploadFile: could not open file %s", _src_file_path.c_str());
        return;
    }
    
    std::string tmp = "upload";

    tmp += " ";
    tmp += _target_file_name;
    tmp += " ";
    char cmd[512];

    strcpy(cmd, tmp.c_str());
    send(sfd,cmd,strlen(cmd),0);
    while(true)
    {
        char buffer[3], *out;
        unsigned char *in;
        in = (unsigned char *)buffer;
        // copy the file into the buffer:
        size_t ret = fread(buffer, 1, 3, fp);
        if (ret > 0)
        {
            base64Encode(in, (unsigned int)ret, &out);
            send(sfd, out, 4, 0);
            free(out);
            if(ret < 3)
            {
                //eof
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
    // terminate
    fclose (fp);
   
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        closesocket(sfd);
        WSACleanup();
#else
        close(sfd);
#endif
    return;
}

std::string ConsoleUploadFile::title() const
{
    return "Console UploadFile";
}

std::string ConsoleUploadFile::subtitle() const
{
    auto sharedFileUtils = FileUtils::getInstance();
    
    std::string writablePath = sharedFileUtils->getWritablePath();

    return "file uploaded to:" + writablePath + _target_file_name;
}

