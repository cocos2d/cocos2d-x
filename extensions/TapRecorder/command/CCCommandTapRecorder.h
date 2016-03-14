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

#ifndef TapRecorder_Command_h
#define TapRecorder_Command_h

#include "extensions/ExtensionMacros.h"
#include "base/CCDirector.h"
#include "CCCommandCapture.h"
#include "CCCommandUrl.h"

NS_CC_EXT_BEGIN

namespace TapRecorder { namespace Command {
    
    class TapRecorder
    {
    public:
        static const std::string commandName();
        static const cocos2d::Console::Command getCommand();
        
        static std::string responsePrompt();
        
    protected:
        static bool message(int, const std::string&);
        static void commandEntryPoint(int, const std::string&);
        
        static void help(int, const std::vector<std::string>&);
    };
    
    static void initialize()
    {
        cocos2d::Console* console = cocos2d::Director::getInstance()->getConsole();
        console->addCommand(TapRecorder::getCommand());
        console->addCommand(Url::getCommand());
        console->addCommand(Capture::getCommand());
    }
    
}}

NS_CC_EXT_END

#endif /* Command_h */
