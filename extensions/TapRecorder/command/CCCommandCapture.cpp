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

#include "CCCommandCapture.h"
#include <sstream>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "extensions/TapRecorder/CCCapture.h"
#include "extensions/TapRecorder/CCUtilTapRecorder.h"

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <Winsock2.h>
#else
#include <sys/socket.h>
#endif

# pragma mark Recorder::Command

USING_NS_CC_EXT;
using namespace TapRecorder;

inline std::string responsePrompt()
{
    return ">> ";
}
inline std::string createResponse(int signal, const std::string& message)
{
    std::stringstream ss;
    ss << responsePrompt() << "SIG_CAPTURE:" << signal << " " << message << "\n";
    return ss.str();
}

inline bool message(int fd, const std::string& text)
{
    ssize_t ret = send(fd, text.c_str(), text.size(), 0);
    if (ret == -1) {
        cocos2d::log("failed to send message");
        return false;
    }
    
    return true;
}

const std::string Command::Capture::commandName()
{
    return "capture";
}

const cocos2d::Console::Command TapRecorder::Command::Capture::getCommand()
{
    return cocos2d::Console::Command({
        commandName(),
        "take screen capture and returns save path",
        parseArguments
    });
}

void Command::Capture::parseArguments(int fd, const std::string& argv)
{
    std::vector<std::string> args = Util::split(argv, ' ');
    
    for (std::vector<std::string>::iterator it = args.begin(); it != args.end();) {
        if (*it == "")
            args.erase(it);
        else
            ++it;
    }
    
    std::string savename = "";
    bool sync = true;
    
    if (args.size() >= 1) {
        for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
            if (*it == "sync")
                sync = true;
            else if (*it == "async")
                sync = false;
            else
                savename = *it;
        }
    }

    capture(fd, savename, sync);
}


void Command::Capture::capture(int fd, const std::string& saveName, bool sync)
{
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    std::condition_variable conditionBlock;
    
    ::Capture* capture = ::Capture::getInstance();
    
    capture->getEventListener()->bindEventCallback("taprecorder_capture", [fd, sync, &conditionBlock](::Capture* cap, int eventType) {
        if (!sync)
            return;
        
        switch (eventType) {
            case ::Capture::EventType::BEGAN  : (void)(message(fd, createResponse(eventType, "capturring"))); break;
            case ::Capture::EventType::ENDED  : (void)(message(fd, createResponse(eventType, "capture succeed: " + cap->outputPath))); break;
            case ::Capture::EventType::FAILED : (void)(message(fd, createResponse(eventType, "an error occured"))); break;
        }
        
        conditionBlock.notify_one();
    });
    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([saveName](){ ::Capture::getInstance()->capture(saveName); });
    
    if (sync)
        conditionBlock.wait(lock);
}