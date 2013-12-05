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

#include "CCConsole.h"

#include <thread>

#include <stdio.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "CCDirector.h"
#include "CCScheduler.h"

#include "CCScene.h"
#include "CCSprite.h"
#include "CCLabelBMFont.h"
#include "CCMenu.h"
#include "CCMenuItem.h"
#include "CCLayer.h"

using namespace cocos2d;

Console* Console::create()
{
    auto ret = new Console;

    ret->autorelease();
    return ret;
}


Console::Console()
: _listenfd(-1)
, _running(false)
, _endThread(false)
, _tokens{
    { "fps on", [](int anFd) {
        Director *dir = Director::getInstance();
        Scheduler *sched = dir->getScheduler();
        sched->performFunctionInCocosThread( std::bind(&Director::setDisplayStats, dir, true));
    } },
    { "fps off", [](int anFd) {
        Director *dir = Director::getInstance();
        Scheduler *sched = dir->getScheduler();
        sched->performFunctionInCocosThread( std::bind(&Director::setDisplayStats, dir, false));
    } },
    { "scene graph", std::bind(&Console::commandSceneGraph, this, std::placeholders::_1) },
    { "exit", std::bind(&Console::commandExit, this, std::placeholders::_1) },
    { "help", std::bind(&Console::commandHelp, this, std::placeholders::_1) },
}
{
    _maxTokens = 5;
 }

Console::~Console()
{
    cancel();
}

bool Console::listenOnTCP(int port)
{
    int listenfd, n;
    const int on = 1;
    struct addrinfo	hints, *res, *ressave;
    char serv[30];

    snprintf(serv,sizeof(serv)-1,"%d",(unsigned int) port );
    serv[sizeof(serv)-1]=0;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(NULL, serv, &hints, &res)) != 0) {
        fprintf(stderr,"net_listen error for %s: %s", serv, gai_strerror(n));
        return false;
    }

    ressave = res;

    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;		/* error, try next one */

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;			/* success */

        close(listenfd);	/* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);
    
    if (res == NULL) {
        perror("net_listen:");
        freeaddrinfo(ressave);
        return false;
    }

    listen(listenfd, 50);

    if (res->ai_family == AF_INET) {
        char buf2[256] = "";
        gethostname(buf2, sizeof(buf2)-1);
        char buf[INET_ADDRSTRLEN] = "";
        struct sockaddr_in *sin = (struct sockaddr_in*) res->ai_addr;
        if( inet_ntop(res->ai_family, sin , buf, sizeof(buf)) != NULL )
            CCLOG("Console: listening on  %s : %d", buf2, ntohs(sin->sin_port));
        else
            perror("inet_ntop");
    }

    freeaddrinfo(ressave);

    return listenOnFileDescriptor(listenfd);
}

bool Console::listenOnFileDescriptor(int fd)
{
    CCASSERT(!_running, "already running");
    _listenfd = fd;
    _thread = std::thread( std::bind( &Console::loop, this) );

    return true;
}

void Console::cancel()
{
    if( _running ) {
        _endThread = true;
        _thread.join();
    }
}


//
// commands
//

void Console::commandHelp(int fd)
{
    const char help[] = "\nAvailable commands:\n";
    write(fd, help, sizeof(help));
    for(int i=0; i<_maxTokens; ++i) {
        write(fd,"\t",1);
        write(fd, _tokens[i].func_name, strlen(_tokens[i].func_name));
        write(fd,"\n",1);
    }
}

void Console::commandExit(int fd)
{
    FD_CLR(fd, &_read_set);
    _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
    close(fd);
}

void printSceneGraph(int fd, Node* node, int level)
{
    for(int i=0; i<level; ++i)
        write(fd, "-", 1);
    std::string type = "Node";
    if( dynamic_cast<Scene*>(node) )
        type = "Scene";
    else if( dynamic_cast<Sprite*>(node) )
        type = "Sprite";
    else if( dynamic_cast<Layer*>(node) )
        type = "Label";
    else if( dynamic_cast<Menu*>(node) )
        type = "Menu";
    else if( dynamic_cast<MenuItem*>(node) )
        type = "MenuItem";

    dprintf(fd, " %s: z=%d, tag=%d\n", type.c_str(), node->getZOrder(), node->getTag() );

    auto children = node->getChildren();
    if( children ) {
        for(const auto& child: *children )
            printSceneGraph(fd, (Node*)child, level+1);
    }
}

void printSceneGraphBoot(int fd)
{
    write(fd,"\n",1);
    auto scene = Director::getInstance()->getRunningScene();
    printSceneGraph(fd, scene, 0);
    write(fd,"\n",1);
}

void Console::commandSceneGraph(int fd)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( std::bind(&printSceneGraphBoot, fd) );
}

bool Console::parseToken(int fd)
{
    auto r = readline(fd);
    if(r < 1)
        return false;

    int i=0;
    for( ; i < _maxTokens; ++i) {
        if( strncmp(_buffer, _tokens[i].func_name,strlen(_tokens[i].func_name)) == 0 ) {
            // XXX TODO FIXME
            // Ideally this loop should execute the function in the cocos2d according to a variable
            // But clang crashes in runtime when doing that (bug in clang, not in the code).
            // So, unfortunately, the only way to fix it was to move that logic to the callback itself
            _tokens[i].callback(fd);
            break;
        }
    }
    if(i == _maxTokens) {
        const char err[] = "Unknown command. Type 'help' for options\n";
        write(fd, err, sizeof(err));
    }

    sendPrompt(fd);

    return true;
}

//
// Helpers
//
void Console::sendPrompt(int fd)
{
    const char prompt[] = "\n> ";
    write(fd, prompt, sizeof(prompt));
}

ssize_t Console::readline(int fd)
{
    int maxlen = sizeof(_buffer)-1;
	ssize_t n, rc;
	char c, *ptr;

    ptr = _buffer;

	for( n=1; n<maxlen; n++ ) {
		if( (rc = read(fd, &c, 1 )) ==1 ) {
			*ptr++ = c;
			if( c=='\n' )
				break;
		} else if( rc == 0 ) {
			return 0;
		} else if( errno == EINTR ) {
            continue;
        } else {
            return -1;
        }
	}

	*ptr = 0;
	return n;
}

void Console::addClient()
{
    struct sockaddr client;
	socklen_t client_len;

    /* new client */
    client_len = sizeof( client );
    int fd = accept(_listenfd, (struct sockaddr *)&client, &client_len );

    // add fd to list of FD
    if( fd != -1 ) {
        FD_SET(fd, &_read_set);
        _fds.push_back(fd);
        _maxfd = std::max(_maxfd,fd);

        sendPrompt(fd);
    }
}

//
// Main Loop
//

void Console::loop()
{
    fd_set copy_set;
	struct timeval timeout, timeout_copy;

    _running = true;

    FD_ZERO(&_read_set);
    FD_SET(_listenfd, &_read_set);
    _maxfd = _listenfd;

	timeout.tv_sec = 0;

    /* 0.016 seconds. Wake up once per frame at 60PFS */
	timeout.tv_usec = 016000;

	while(!_endThread) {

        FD_COPY(&_read_set, &copy_set);
        timeout_copy = timeout;
		int nready = select(_maxfd+1, &copy_set, NULL, NULL, &timeout_copy);

		if( nready == -1 ) {
            /* error ?*/
			if(errno != EINTR) {
				log("Abnormal error in select()\n");
			}
			continue;

		} else if( nready == 0 ) {
            /* timeout ? */
			continue;
        }

        // new client
        if(FD_ISSET(_listenfd, &copy_set)) {
            addClient();
			if(--nready <= 0)
				continue;
        }

        // data from client
        std::vector<int> to_remove;
        for(const auto &fd: _fds) {
            if(FD_ISSET(fd,&copy_set)) {
                if( ! parseToken(fd) ) {
                    to_remove.push_back(fd);
                }
                if(--nready <= 0)
                    break;
            }
        }

        // remove closed conections
        for(const auto &fd: to_remove) {
            FD_CLR(fd, &_read_set);
            _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
        }
    }

    // clean up: ignore stdin, stdout and stderr
    for(const auto &fd: _fds )
        close(fd);
    close(_listenfd);

    _running = false;
}
