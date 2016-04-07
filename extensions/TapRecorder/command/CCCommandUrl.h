/****************************************************************************
 Copyright (c) 2016 Yuki Kuwabara <do_low@hotmail.com>
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

#ifndef TapRecorder_CommandUrl_h
#define TapRecorder_CommandUrl_h

#include <string>
#include <vector>
#include "extensions/ExtensionMacros.h"
#include "base/CCConsole.h"

NS_CC_EXT_BEGIN

namespace TapRecorder { namespace Command {
    
    class Url
    {
    public:
        static const std::string commandName();
        static const cocos2d::Console::Command getCommand();
        static void parseArguments(int, const std::string&);
    };
    
    class Upload
    {
    public:
        static const std::string getIdentifier();
        
        static const std::string commandName();
        static void parseArguments(int, std::vector<std::string>&);
        
        static void upload(int, const std::string& url, const std::string& targetFile, bool sync);
        static void help(int);
    };
    
    class Download
    {
    public:
        static const std::string getIdentifier();
        
        static const std::string commandName();
        static void parseArguments(int, std::vector<std::string>&);
        
        static void download(int, const std::string& url, const std::string& saveName, bool sync);
        static void help(int);
        
    private:
        static bool isSuccessHttpStatus(long statusCode);
    };
    
}}

NS_CC_EXT_END

#endif /* TapRecorder_CommandUrl_h */
