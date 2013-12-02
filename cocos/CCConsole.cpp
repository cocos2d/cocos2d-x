//
//  CCConsole.cpp
//  cocos2d_libs
//
//  Created by Ricardo Quesada on 11/26/13.
//
//

#include "CCConsole.h"

#include <stdio.h>
#include <unistd.h>
#include <thread>

#include "CCDirector.h"

using namespace cocos2d;

Console* Console::createWithFileDescriptor(int fd)
{
    auto ret = new Console;

    ret->setFileDescriptor(fd);
    ret->autorelease();
    return ret;
}


Console::Console()
: _fd(-1)
, _running(false)
, _endThread(false)
{
    _scheduler = Director::getInstance()->getScheduler();
}

Console::~Console()
{
}

void Console::run()
{
    CCASSERT(!_running, "already running");
    _thread = std::thread( std::bind( &Console::loop, this) );
}

void Console::cancel()
{
    CCASSERT(_running, "must be running");
    _endThread = true;
    _thread.join();
}


ssize_t net_readline( int fd, void *vptr, size_t maxlen )
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = (char*)vptr ;

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
    fd_set read_set;

    FD_ZERO(&read_set);
    FD_SET(_fd, &read_set);

	while(!_endThread) {

		int nready = select( _fd+1, &read_set, NULL, NULL, NULL );

		if( nready == -1 ) {
            /* error ?*/
			if(errno != EINTR) {
				log("Abnormal error in select()\n");
			}
			continue;

		} else if( nready == 0 ) {
            /* timeout ? */
			continue;
		} else {
            /* info */
            
		}
	}
}
