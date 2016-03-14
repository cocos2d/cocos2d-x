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

#include "CCCommandRecorder.h"
#include <sstream>
#include "extensions/TapRecorder/CCRecorder.h"

USING_NS_CC_EXT;
using namespace TapRecorder;

std::string Command::Recorder::saveName = "";

const std::string Command::Recorder::commandName()
{
    return "record";
}

std::string Command::Recorder::createResponse(int signal, const std::string& message)
{
    std::stringstream ss;
    ss << responsePrompt() << "SIG_RECORDER:" << signal << " " << message << "\n";
    return ss.str();
}

void Command::Recorder::parseArguments(int fd, std::vector<std::string>& args)
{
    if (args.size() == 0) {
        help(fd, args);
        return;
    }
    
    std::string option = *args.begin();
    args.erase(args.begin());
    
    if (option == "start")
        start(fd, args);
    else if (option == "finish")
        finish(fd, args);
    else
        help(fd, args);
}


void Command::Recorder::start(int fd, const std::vector<std::string>& args)
{
    ::Recorder* recorder = ::Recorder::getInstance();
    if (args.size() > 0) {
        std::string option = args.at(0);
        if (option == "help") {
            help(fd, args);
            return;
        }
        
        bool abstime  = false;
        for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
            if (*it == "abstime")
                abstime = true;
            else
                saveName = *it;
        }
        
        if (!abstime)
            recorder->resetDurations();
    }
    
    
    recorder->getEventListener()->bindEventCallback("taprecorder_recorder", [fd](extension::TapRecorder::Recorder* recorder, int eventType){
        switch (eventType) {
            case ::Recorder::EventType::BEGAN :
                (void)(message(fd, createResponse(eventType, "start recording"))); break;
            case ::Recorder::EventType::CANCELLED :
                (void)(message(fd, createResponse(eventType, "cancel recording"))); break;
            case ::Recorder::EventType::FINISHED : {
                recorder->save(saveName);
                recorder->clear();
                recorder->resetDurations();
                break;
            }
            case ::Recorder::EventType::SAVED : {
                std::string savePath = recorder->lastSavePath();
                
                if (!savePath.empty())
                    (void)(message(fd, createResponse(eventType, "finish recording " + savePath)));
                
                saveName = "";
                
                break;
            }
        }
    });
                                                    
    recorder->init();
    recorder->record(DurationUnit::Frame);
}
void Command::Recorder::finish(int fd, const std::vector<std::string>& args)
{
    ::Recorder::getInstance()->stop();
}
void Command::Recorder::help(int fd, const std::vector<std::string>& args)
{
    (void)(message(fd,
        "available commands:\n"
        "\trecord start          start recording\n"
        "\trecord finish [name]  finish recording and store tap data with given name\n"));
}
