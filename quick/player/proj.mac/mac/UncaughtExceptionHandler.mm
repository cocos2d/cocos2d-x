//
//  UncaughtExceptionHandler.mm
//  player3
//
//  Created by ZhuJunfeng on 15-1-8.
//
//

#include <execinfo.h>
#include "base/CCDirector.h"


#import "UncaughtExceptionHandler.h"

volatile int32_t UncaughtExceptionCount = 0;
const int32_t UncaughtExceptionMaximum = 10;

void MySignalHandler(int signal)
{
    int32_t exceptionCount = OSAtomicIncrement32(&UncaughtExceptionCount);
    if (exceptionCount > UncaughtExceptionMaximum)
    {
        return;
    }
    cocos2d::ScriptEngineProtocol* engine = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine();
    if (engine)
    {
        engine->handleAssert("UncaughtException", 0, 0, 0);
    }
    return;
}

void InstallUncaughtExceptionHandler()
{
    signal(SIGABRT, MySignalHandler);
    signal(SIGILL, MySignalHandler);
    signal(SIGSEGV, MySignalHandler);
    signal(SIGFPE, MySignalHandler);
    signal(SIGBUS, MySignalHandler);
    signal(SIGPIPE, MySignalHandler);
}