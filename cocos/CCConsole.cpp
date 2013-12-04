//
//  CCConsole.cpp
//  cocos2d_libs
//
//  Created by Ricardo Quesada on 11/26/13.
//
//

#include "CCConsole.h"

#include <thread>

#include <stdio.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "CCDirector.h"
#include "CCScheduler.h"

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
{
    _scheduler = Director::getInstance()->getScheduler();
}

Console::~Console()
{
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
    
    freeaddrinfo(ressave);

    CCLOG("Console: listening on port %d", port);
    return listenOnFileDescriptor(listenfd);
}

bool Console::listenOnStdin()
{
    return listenOnFileDescriptor(STDIN_FILENO);
}

bool Console::listenOnFileDescriptor(int fd)
{
    CCASSERT(!_running, "already running");
    _running = true;
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

void Console::parseToken()
{
    struct _tokens {
        const char * func_name;
        std::function<void()> callback;
    } tokens[] {
        { "fps on", []() { Director::getInstance()->setDisplayStats(true); } },
        { "fps off", []() { Director::getInstance()->setDisplayStats(false); } },
    };

    const int max = sizeof(tokens) / sizeof(tokens[0]);

    Scheduler *sched = Director::getInstance()->getScheduler();
    for( int i=0; i < max; ++i) {
        if( strncmp(_buffer, tokens[i].func_name,strlen(tokens[i].func_name)) == 0 )
            sched->performFunctionInCocosThread( tokens[i].callback );
    }

}

ssize_t Console::readline(int fd)
{
    int maxlen = 512;
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

void Console::loop()
{
    fd_set read_set, copy_set;
	struct sockaddr client;
	socklen_t client_len;
	struct timeval timeout, timeout_copy;

    FD_ZERO(&read_set);
    FD_SET(_listenfd, &read_set);
    _maxfd = _listenfd;

	timeout.tv_sec = 0;

    /* 0.016 seconds. Wake up once per frame at 60PFS */
	timeout.tv_usec = 016000;

	while(!_endThread) {

        FD_COPY(&read_set, &copy_set);
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

        if(FD_ISSET(_listenfd, &copy_set)) {
            /* new client */
			client_len = sizeof( client );
			int fd = accept(_listenfd, (struct sockaddr *)&client, &client_len );

            // add fd to list of FD
			if( fd != -1 ) {
                FD_SET(fd, &read_set);
                _fds.push_back(fd);
                _maxfd = std::max(_maxfd,fd);
            }

			if(--nready <= 0)
				continue;
        }

        /* input from client */
        for(const auto &fd: _fds) {
            if(FD_ISSET(fd,&copy_set)) {
                readline(fd);
                parseToken();
                log("read: %s", _buffer);
                if(--nready <= 0)
                    break;
            }
        }
    }

    // clean up: ignore stdin, stdout and stderr
    for(const auto &fd: _fds )
        close(fd);
    close(_listenfd);
}
