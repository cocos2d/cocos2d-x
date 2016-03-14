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

#include "CCCommandPlayer.h"
#include <sstream>

USING_NS_CC_EXT;
using namespace TapRecorder;

const std::string Command::Player::commandName()
{
    return "play";
}

std::string Command::Player::createResponse(int signal, const std::string& message)
{
    std::stringstream ss;
    ss << responsePrompt() << "SIG_PLAYER:" << signal << " " << message << "\n";
    return ss.str();
}

void Command::Player::parseArguments(int fd, std::vector<std::string>& args)
{
    if (args.size() == 0) {
        help(fd, args);
        return;
    }
    
    std::string option = *args.begin();
    args.erase(args.begin());
    
    if (option == "start")
        start(fd, args);
    else if (option == "stop")
        stop(fd, args);
    else if (option == "calibrate")
        enableCalibration(fd, args);
    else if (option == "not-calibrate")
        disabledCalibration(fd, args);
    else
        help(fd, args);
}

void Command::Player::enableCalibration(int, const std::vector<std::string>&)
{
    ::Player::getInstance()->calibrationEnabled = true;
}
void Command::Player::disabledCalibration(int, const std::vector<std::string>&)
{
    ::Player::getInstance()->calibrationEnabled = false;
}

void Command::Player::start(int fd, const std::vector<std::string>& args)
{
    ::Player* player = ::Player::getInstance();
    if (args.size() == 0) {
        (void)(message(fd, "record id is required to play\n"));
        return;
    }
    
    std::string fileName = *args.begin();
    
    bool sync = false;
    bool willReportGestureEvent = false;
    
    if (args.size() >= 2) {
        bool abstime     = false;
        bool calibration = true;
        
        for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
            if (*it == "abstime")
                abstime = true;
            else if (*it == "sync")
                sync = true;
            else if (*it == "async")
                sync = false;
            else if (*it == "not-calibrate")
                calibration = false;
            else if (*it == "calibrate")
                calibration = true;
            else if (*it == "report-gesture-event")
                willReportGestureEvent = true;
            else
                fileName = *it;
        }
        
        if (!abstime)
            player->resetDurations();
        
        ::Player::getInstance()->calibrationEnabled = calibration;
    }
    
    std::mutex mutex;
    std::condition_variable conditionWait;
    std::unique_lock<std::mutex> lock(mutex);
    
    player->getEventListener()->bindEventCallback("taprecorder_player", [fd, sync, &conditionWait, willReportGestureEvent](::Player* player, int type) {
        eventCallback(fd, conditionWait, sync, willReportGestureEvent, player, type);
    });
    
    bool res = player->play(fileName);
    if (!res) {
        (void)(message(fd, "failed to play, it may already be playing, or record id does not exist.\n"));
        return;
    }
    
    if (sync)
        conditionWait.wait(lock);
}


void Command::Player::stop(int fd, const std::vector<std::string>& args)
{
    ::Player::getInstance()->stop();
}
void Command::Player::help(int fd, const std::vector<std::string>& args)
{
    (void)(message(fd,
        "available commands:\n"
        "\tplay start [name]  start playback tap records assosiated with given name\n"
        "\t\toptoins :\n"
        "\t\t\tsync          play taps as sync process\n"
        "\t\t\tcalibrate     enables calibration between different design resolution screens\n"
        "\t\t\tnot-calibrate disables calibration between different design resolution screens\n"
        "\tplay stop          stop playback\n"
        "\tcalibrate          enables calibration between different design resolution screens\n"
        "\tnot-calibrate      disables calibration between different design resolution screens\n"));
}

void Command::Player::eventCallback(int fd, std::condition_variable& conditionWait, bool sync, bool reportTouch, ::Player* player, int type)
{
    switch (type) {
        case ::Player::EventType::PLAY_BEGAN : {
            (void)(message(fd, createResponse(type, "start playback")));
            break;
        }
        case ::Player::EventType::PLAY_STOPPED : {
            (void)(message(fd, createResponse(type, "finish playback")));
            
            if (sync)
                conditionWait.notify_one();
            break;
        }
        case ::Player::EventType::PLAY_CANCELLED : {
            (void)(message(fd, createResponse(type, "cancel playback")));
            
            if (sync)
                conditionWait.notify_one();
            break;
        }
        case ::Player::EventType::TOUCH_PLAYING :
        case ::Player::EventType::TOUCH_PLAYED  : {
            if (reportTouch)
                reportGestureEvent(fd, type, player->getCurrentRecord());
            break;
        }
    }
}

void Command::Player::reportGestureEvent(int fd, int eventType, const Record& record)
{
    std::string response = "";
    
    if (eventType == ::Player::EventType::TOUCH_PLAYING) {
        switch (record.eventType) {
            case EventTouch::EventCode::BEGAN :
                response = createResponse(static_cast<int>(record.eventType), "touch beginning"); break;
            case EventTouch::EventCode::MOVED :
                response = createResponse(static_cast<int>(record.eventType), "touch moving"); break;
            case EventTouch::EventCode::ENDED :
                response = createResponse(static_cast<int>(record.eventType), "touch ending"); break;
            case EventTouch::EventCode::CANCELLED :
                response = createResponse(static_cast<int>(record.eventType), "touch cancelling"); break;
            default:
                return;
        }
    }
    else if (eventType == ::Player::EventType::TOUCH_PLAYED) {
        switch (record.eventType) {
            case EventTouch::EventCode::BEGAN :
                response = createResponse(static_cast<int>(record.eventType), "touch began"); break;
            case EventTouch::EventCode::MOVED :
                response = createResponse(static_cast<int>(record.eventType), "touch moved"); break;
            case EventTouch::EventCode::ENDED :
                response = createResponse(static_cast<int>(record.eventType), "touch ended"); break;
            case EventTouch::EventCode::CANCELLED :
                response = createResponse(static_cast<int>(record.eventType), "touch cancelled"); break;
            default:
                return;
        }
    }
    else {
        return;
    }
    
    (void)(message(fd, response));
}