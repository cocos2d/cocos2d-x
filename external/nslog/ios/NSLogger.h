/*
 * NSLogger.h
 *
 * version 1.5-RC2 22-NOV-2013
 *
 * Part of NSLogger (client side)
 * https://github.com/fpillet/NSLogger
 *
 * BSD license follows (http://www.opensource.org/licenses/bsd-license.php)
 *
 * Copyright (c) 2010-2013 Florent Pillet All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of  source code  must retain  the above  copyright notice,
 * this list of  conditions and the following  disclaimer. Redistributions in
 * binary  form must  reproduce  the  above copyright  notice,  this list  of
 * conditions and the following disclaimer  in the documentation and/or other
 * materials  provided with  the distribution.  Neither the  name of  Florent
 * Pillet nor the names of its contributors may be used to endorse or promote
 * products  derived  from  this  software  without  specific  prior  written
 * permission.  THIS  SOFTWARE  IS  PROVIDED BY  THE  COPYRIGHT  HOLDERS  AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A  PARTICULAR PURPOSE  ARE DISCLAIMED.  IN  NO EVENT  SHALL THE  COPYRIGHT
 * HOLDER OR  CONTRIBUTORS BE  LIABLE FOR  ANY DIRECT,  INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY,  OR CONSEQUENTIAL DAMAGES (INCLUDING,  BUT NOT LIMITED
 * TO, PROCUREMENT  OF SUBSTITUTE GOODS  OR SERVICES;  LOSS OF USE,  DATA, OR
 * PROFITS; OR  BUSINESS INTERRUPTION)  HOWEVER CAUSED AND  ON ANY  THEORY OF
 * LIABILITY,  WHETHER  IN CONTRACT,  STRICT  LIABILITY,  OR TORT  (INCLUDING
 * NEGLIGENCE  OR OTHERWISE)  ARISING  IN ANY  WAY  OUT OF  THE  USE OF  THIS
 * SOFTWARE,   EVEN  IF   ADVISED  OF   THE  POSSIBILITY   OF  SUCH   DAMAGE.
 *
 */
#import "LoggerClient.h"



// Log level usual usage:
// Level 0: errors only!
// Level 1: important informations, app states…
// Level 2: less important logs, network requests…
// Level 3: network responses, datas and images…
// Level 4: really not important stuff.



#if 0
    #define NSLog(...)                      LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"NSLog", 0, __VA_ARGS__)
    #define LoggerError(level, ...)         LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Error", level, __VA_ARGS__)
    #define LoggerApp(level, ...)           LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"App", level, __VA_ARGS__)
    #define LoggerView(level, ...)          LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"View", level, __VA_ARGS__)
    #define LoggerService(level, ...)       LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Service", level, __VA_ARGS__)
    #define LoggerModel(level, ...)         LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Model", level, __VA_ARGS__)
    #define LoggerData(level, ...)          LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Data", level, __VA_ARGS__)
    #define LoggerNetwork(level, ...)       LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Network", level, __VA_ARGS__)
    #define LoggerLocation(level, ...)      LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Location", level, __VA_ARGS__)
    #define LoggerPush(level, ...)          LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Push", level, __VA_ARGS__)
    #define LoggerFile(level, ...)          LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"File", level, __VA_ARGS__)
    #define LoggerSharing(level, ...)       LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Sharing", level, __VA_ARGS__)
    #define LoggerAd(level, ...)            LogMessageF(__FILE__, __LINE__, __FUNCTION__, @"Ad and Stat", level, __VA_ARGS__)

#else
    #define NSLog(...)                      LogMessageCompat(__VA_ARGS__)
    #define LoggerError(...)                while(0} {}
    #define LoggerApp(level, ...)           while(0) {}
    #define LoggerView(...)                 while(0) {}
    #define LoggerService(...)              while(0) {}
    #define LoggerModel(...)                while(0) {}
    #define LoggerData(...)                 while(0) {}
    #define LoggerNetwork(...)              while(0) {}
    #define LoggerLocation(...)             while(0) {}
    #define LoggerPush(...)                 while(0) {}
    #define LoggerFile(...)                 while(0) {}
    #define LoggerSharing(...)              while(0) {}
    #define LoggerAd(...)                   while(0) {}

#endif



// Starts the logger with the username defined in the build settings.
// The build setting NSLOGGER_BUILD_USERNAME is automatically configured when NSLogger is
// added to a project using CocoaPods. To use it, just add this macro call to your main() function.
#define LoggerStartForBuildUser() LoggerSetupBonjour(LoggerGetDefaultLogger(), NULL, CFSTR(xstr(NSLOGGER_BUILD_USERNAME)))






