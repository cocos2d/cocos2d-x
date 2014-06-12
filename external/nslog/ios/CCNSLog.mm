//
//  MyLog.cpp
//  cocos2d_libs
//
//  Created by James Chen on 4/23/14.
//
//

#include "CCNSLog.h"

#import "NSLogger.h"


void CCNSLog(const char* file, int line, const char* function, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    
    char buf[1024 * 16] = {0};
    vsprintf(buf, format, args);
    
    va_end(args);
    
    LogMessageF(file, line, function, @"cocos2d-x", 0, [NSString stringWithUTF8String:buf], nullptr);
    
    //    LoggerFlush(LoggerGetDefaultLogger(), YES);
}
