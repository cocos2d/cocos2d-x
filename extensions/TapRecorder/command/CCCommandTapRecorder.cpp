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

#include "CCCommandTapRecorder.h"
#include "extensions/TapRecorder/CCRecord.h"
#include "extensions/TapRecorder/CCUtilTapRecorder.h"
#include "CCCommandRecorder.h"
#include "CCCommandPlayer.h"

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <Winsock2.h>
#else
#include <sys/socket.h>
#endif

USING_NS_CC_EXT;

const std::string TapRecorder::Command::TapRecorder::commandName()
{
    return "taprecorder";
}
bool TapRecorder::Command::TapRecorder::message(int fd, const std::string& text)
{
    ssize_t ret = send(fd, text.c_str(), text.size(), 0);
    if (ret == -1) {
        cocos2d::log("failed to send message");
        return false;
    }
    
    return true;
}

std::string TapRecorder::Command::TapRecorder::responsePrompt()
{
    return ">> ";
}

const cocos2d::Console::Command TapRecorder::Command::TapRecorder::getCommand()
{
    return cocos2d::Console::Command({
        commandName(),
        "handles tap recording and playback",
        commandEntryPoint
    });
}

void TapRecorder::Command::TapRecorder::commandEntryPoint(int fd, const std::string& arg)
{
    std::vector<std::string> args = Util::split(arg, ' ');
    if (args.size() == 0) {
        help(fd, args);
        return;
    }
    
    std::string option = *args.begin();
    args.erase(args.begin());
    
    if (option == "record")
        Recorder::parseArguments(fd, args);
    else if (option == "play")
        Player::parseArguments(fd, args);
    else
        help(fd, args);
}

void TapRecorder::Command::TapRecorder::help(int fd, const std::vector<std::string>&)
{
    (void)(message(fd,
        "available commands:\n"
        "\trecord start          start recording\n"
        "\trecord finish [name]  finish recording and store tap data with given name\n"
        "\tplay start [name]     start playback tap records assosiated with given name\n"
        "\tplay stop             stop playback\n"));
}
