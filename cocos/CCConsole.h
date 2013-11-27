//
//  CCConsole.h
//  cocos2d_libs
//
//  Created by Ricardo Quesada on 11/26/13.
//
//

#ifndef __cocos2d_libs__CCConsole__
#define __cocos2d_libs__CCConsole__

#include <thread>

#include "ccMacros.h"
#include "base/CCObject.h"


NS_CC_BEGIN

class Scheduler;

class CC_DLL Console : public Object
{

public:
    static Console* createWithFileDescriptor(int fd);

    void run();
    void cancel();

    int getFileDescriptor() const { return _fd; }
    void setFileDescriptor(int fd) { _fd = fd; }


protected:
    Console();
    virtual ~Console();


    void loop();

    // weak ref
    Scheduler *_scheduler;

    // file descriptor: socket, console, etc.
    int _fd;
    std::thread _thread;
    bool _running;
    bool _endThread;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Console);
};


NS_CC_END

#endif /* defined(__cocos2d_libs__CCConsole__) */
