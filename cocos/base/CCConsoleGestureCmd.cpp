/****************************************************************************
 Copyright (c) 2016      Naruto TAKAHASHI <tnaruto@gmail.com>
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

#include "CCConsoleGestureCmd.h"
#include <sstream>

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <WS2tcpip.h>
#include <Winsock2.h>
#if defined(__MINGW32__)
#include "platform/win32/inet_pton_mingw.h"
#endif
#define bzero(a, b) memset(a, 0, b);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "platform/winrt/inet_ntop_winrt.h"
#include "platform/winrt/inet_pton_winrt.h"
#include "platform/winrt/CCWinRTUtils.h"
#endif
#else
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#endif

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCConfiguration.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureCache.h"
#include "base/base64.h"
#include "base/ccUtils.h"
#include "base/allocator/CCAllocatorDiagnostics.h"
#include "2d/CCTouchAction.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"

USING_NS_CC;

ConsoleGestureCmd::ConsoleGestureCmd()
        : touchPriority(DEFAULT_TOUCH_PRIORITY)
{
    command.name = "gesture";
    command.help = "simulate gesture event via console, type [gesture help] to list supported directives";
    command.callback = CC_CALLBACK_2(ConsoleGestureCmd::commandGesture, this);

    addSubCommand("help", "", CC_CALLBACK_2(ConsoleGestureCmd::commandHelp, this));
    // sync gesture commands
    addSubCommand("tap", "x y [duration] [force tap]: simulate tap at (x,y)", CC_CALLBACK_2(ConsoleGestureCmd::commandTap, this));
    addSubCommand("swipe", "srcX srcY dstX dstY [duration]: simulate swipe from (srcX,srcY) to (dstX,dstY)", CC_CALLBACK_2(ConsoleGestureCmd::commandSwipe, this));
    addSubCommand("pinchIn", "centerX centerY initDistance pinchDistance [degree] [duration]: simulate pinchIn", CC_CALLBACK_2(ConsoleGestureCmd::commandPinchIn, this));
    addSubCommand("pinchOut", "centerX centerY initDistance pinchDistance [degree] [duration]: simulate pinchOut", CC_CALLBACK_2(ConsoleGestureCmd::commandPinchOut, this));

    // async gesture commands
    addSubCommand("tapAsync", "x y [duration] [force tap] [asyncID]: simulate async tap at (x,y)", CC_CALLBACK_2(ConsoleGestureCmd::commandTapAsync, this));
    addSubCommand("swipeAsync", "srcX srcY dstX dstY [duration] [asyncID]: simulate async swipe from (srcX,srcY) to (dstX,dstY)", CC_CALLBACK_2(ConsoleGestureCmd::commandSwipeAsync, this));
    addSubCommand("pinchInAsync", "centerX centerY initDistance pinchDistance [degree] [duration] [asyncID]: simulate async pinchIn", CC_CALLBACK_2(ConsoleGestureCmd::commandPinchInAsync, this));
    addSubCommand("pinchOutAsync", "centerX centerY initDistance pinchDistance [degree] [duration] [asyncID]: simulate async pinchOut", CC_CALLBACK_2(ConsoleGestureCmd::commandPinchOutAsync, this));

    // sync primitive touch commands
    addSubCommand("touchBegin", "x y touchID: simulate touchBegan (x,y) with touchID", CC_CALLBACK_2(ConsoleGestureCmd::commandTouchBegin, this));
    addSubCommand("touchMove", "x y touchID: simulate touchMoved (x,y) with touchID", CC_CALLBACK_2(ConsoleGestureCmd::commandTouchMove, this));
    addSubCommand("touchEnd", "x y touchID: simulate touchEnded (x,y) with touchID", CC_CALLBACK_2(ConsoleGestureCmd::commandTouchEnd, this));
    addSubCommand("touchCancel", "x y touchID: simulate touchCanceled (x,y) with touchID", CC_CALLBACK_2(ConsoleGestureCmd::commandTouchCancel, this));
    addSubCommand("touchStatus", ": display simulate touchIDs List", CC_CALLBACK_2(ConsoleGestureCmd::commandTouchStatus, this));
}

ConsoleGestureCmd::~ConsoleGestureCmd()
{
    for (auto &itr : touchesMap) {
        Touch *touch = itr.second;
        touch->release();
    }
    touchesMap.clear();
}

void ConsoleGestureCmd::addSubCommand(const std::string &name, const std::string &help, std::function<void(int, const std::string &)> callback)
{
    subCommands.emplace_back(Console::Command{name, help, callback});
}

void ConsoleGestureCmd::commandGesture(int fd, const std::string &args)
{
    int ret;
    auto argv = split(args,' ');
    auto helpCommand = std::find_if(subCommands.begin(), subCommands.end(), [argv](const struct Console::Command &command) {
        return (command.name == "help")? true : false;
    });

    if(argv.empty()) {
        helpCommand->callback(fd, args);
    } else {
        auto command = std::find_if(subCommands.begin(), subCommands.end(), [argv](const struct Console::Command &command) {
            return (argv[0] == command.name)? true : false;
        });
        if(command == subCommands.end()) {
            helpCommand->callback(fd, args);
            return;
        }
        command->callback(fd, args);
    }
}

// import from CCConsole
std::vector<std::string> &ConsoleGestureCmd::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// import from CCConsole
std::vector<std::string> ConsoleGestureCmd::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void ConsoleGestureCmd::commandHelp(int fd, const std::string &args)
{
    int ret;
    std::string logStr;
    logStr.append(command.name);
    logStr.append(" commands:\n");
    for(auto &cmd : this->subCommands) {
        if(cmd.name == "help") continue;
        std::stringstream ss;
        ss << "\t" << cmd.name << " " << cmd.help << std::endl;
        logStr.append(ss.str());
    }
    ret = send(fd, logStr.c_str(), logStr.size(), 0);
    if(ret < 0) {
        CCLOG("send() error");
    }
}

void ConsoleGestureCmd::commandTapInternal(int fd, const std::string &args, bool async)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    if(argv.size() < 3) return;

    int touchPriority = this->touchPriority;
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, async, &waitCocosThread, touchPriority]() {
        std::string xStr = argv[1];
        std::string yStr = argv[2];
        std::string durationStr = (argv.size() >= 4)? argv[3] : "";
        std::string forceStr = (argv.size() >= 5)? argv[4] : ""; // TODO: implement
        std::string asyncIDStr = (argv.size() >= 6)? argv[5] : "";

        Vec2 pos(std::stof(xStr), std::stof(yStr));
        float duration = (durationStr != "")? std::stof(durationStr) : 1.0f;
        auto tap = Tap::create(duration, pos, true);
        
        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch *touch, Event *event) { return true; };
        listener->onTouchEnded = [fd, async, &waitCocosThread, asyncIDStr, listener](Touch *touch, Event *event) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            if(async) {
                if(!asyncIDStr.empty()) {
                    std::string logStr;
                    logStr.append(">> ");
                    logStr.append(asyncIDStr);
                    logStr.append("\n");
                    int ret = send(fd, logStr.c_str(), logStr.size(), 0);
                    if(ret < 0) {
                        CCLOG("send() error");
                    }
                }
            } else {
                waitCocosThread.notify_one();
            }};
        director->getEventDispatcher()->addEventListenerWithFixedPriority(listener, touchPriority);
        runningScene->runAction(tap);
    });
    if(!async) {
        waitCocosThread.wait(lock);
    }
}

void ConsoleGestureCmd::commandSwipeInternal(int fd, const std::string &args, bool async)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    if(argv.size() < 5) return;

    int touchPriority = this->touchPriority;
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, async, &waitCocosThread, touchPriority]() {
        std::string srcXStr = argv[1];
        std::string srcYStr = argv[2];
        std::string dstXStr = argv[3];
        std::string dstYStr = argv[4];
        std::string durationStr = (argv.size() >= 6)? argv[5] : "";
        std::string asyncIDStr = (argv.size() >= 7)? argv[6] : "";

        Vec2 srcPos(std::stof(srcXStr), std::stof(srcYStr));
        Vec2 dstPos(std::stof(dstXStr), std::stof(dstYStr));
        float duration = (durationStr != "")? std::stof(durationStr) : 1.0f ;
        auto swipe = SwipeBetween::create(duration, srcPos, dstPos);

        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch *touch, Event *event) { return true; };
        listener->onTouchEnded = [fd, async, &waitCocosThread, asyncIDStr, listener](Touch *touch, Event *event) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            if(async) {
                if(!asyncIDStr.empty()) {
                    std::string logStr;
                    logStr.append(">> ");
                    logStr.append(asyncIDStr);
                    logStr.append("\n");
                    int ret = send(fd, logStr.c_str(), logStr.size(), 0);
                    if(ret < 0) {
                        CCLOG("send() error");
                    }
                }
            } else {
                waitCocosThread.notify_one();
            }};
        director->getEventDispatcher()->addEventListenerWithFixedPriority(listener, touchPriority);
        runningScene->runAction(swipe);
    });
    if(!async) {
        waitCocosThread.wait(lock);
    }
}

void ConsoleGestureCmd::commandPinchInInternal(int fd, const std::string &args, bool async)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    if(argv.size() < 5) return;

    int touchPriority = this->touchPriority;
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, async, &waitCocosThread, touchPriority]() {
        std::string centerXStr = argv[1];
        std::string centerYStr = argv[2];
        std::string initDistanceStr = argv[3];
        std::string pinchDistanceStr = argv[4];
        std::string degreeStr = (argv.size() >= 6)? argv[5] : "";
        std::string durationStr = (argv.size() >= 7)? argv[6] : "";
        std::string asyncIDStr = (argv.size() >= 8)? argv[7] : "";

        Vec2 centerPos(std::stof(centerXStr), std::stof(centerYStr));
        float initDistance = std::stof(initDistanceStr);
        float pinchDistance = std::stof(pinchDistanceStr);
        float degree = std::stof(degreeStr);
        float duration = (durationStr != "")? std::stof(durationStr) : 1.0f ;
        auto pinchIn = PinchIn::create(duration, centerPos, initDistance, pinchDistance, true, degree);

        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch *touch, Event *event) { return true; };
        listener->onTouchEnded = [fd, async, &waitCocosThread, asyncIDStr, listener](Touch *touch, Event *event) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            if(async) {
                if(!asyncIDStr.empty()) {
                    std::string logStr;
                    logStr.append(">> ");
                    logStr.append(asyncIDStr);
                    logStr.append("\n");
                    int ret = send(fd, logStr.c_str(), logStr.size(), 0);
                    if(ret < 0) {
                        CCLOG("send() error");
                    }
                }
            } else {
                waitCocosThread.notify_one();
            }};
        director->getEventDispatcher()->addEventListenerWithFixedPriority(listener, touchPriority);
        runningScene->runAction(pinchIn);
    });
    if(!async) {
        waitCocosThread.wait(lock);
    }
}

void ConsoleGestureCmd::commandPinchOutInternal(int fd, const std::string &args, bool async)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    if(argv.size() < 5) return;

    int touchPriority = this->touchPriority;
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, async, &waitCocosThread, touchPriority]() {
        std::string centerXStr = argv[1];
        std::string centerYStr = argv[2];
        std::string initDistanceStr = argv[3];
        std::string pinchDistanceStr = argv[4];
        std::string degreeStr = (argv.size() >= 6)? argv[5] : "";
        std::string durationStr = (argv.size() >= 7)? argv[6] : "";
        std::string asyncIDStr = (argv.size() >= 8)? argv[7] : "";

        Vec2 centerPos(std::stof(centerXStr), std::stof(centerYStr));
        float initDistance = std::stof(initDistanceStr);
        float pinchDistance = std::stof(pinchDistanceStr);
        float degree = std::stof(degreeStr);
        float duration = (durationStr != "")? std::stof(durationStr) : 1.0f ;
        auto pinchOut = PinchOut::create(duration, centerPos, initDistance, pinchDistance, true, degree);

        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [](Touch *touch, Event *event) { return true; };
        listener->onTouchEnded = [fd, async, &waitCocosThread, asyncIDStr, listener](Touch *touch, Event *event) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
            if(async) {
                if(!asyncIDStr.empty()) {
                    std::string logStr;
                    logStr.append(">> ");
                    logStr.append(asyncIDStr);
                    logStr.append("\n");
                    int ret = send(fd, logStr.c_str(), logStr.size(), 0);
                    if(ret < 0) {
                        CCLOG("send() error");
                    }
                }
            } else {
                waitCocosThread.notify_one();
            }};
        director->getEventDispatcher()->addEventListenerWithFixedPriority(listener, touchPriority);
        runningScene->runAction(pinchOut);
    });
    if(!async) {
        waitCocosThread.wait(lock);
    }
}

void ConsoleGestureCmd::commandTouchBegin(int fd, const std::string &args)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    // args: touchBegin x y touchID
    if(argv.size() < 4) return;

    std::string xStr = argv[1];
    std::string yStr = argv[2];
    std::string touchIDStr = argv[3];
    float x = std::stof(xStr);
    float y = std::stof(yStr);
    int touchID = std::stoi(touchIDStr);

    if(findTouch(touchID) != nullptr) {
        int ret;
        std::string logStr;
        logStr.append("already registered touchID: ");
        logStr.append(touchIDStr);
        logStr.append("\n");
        ret = send(fd, logStr.c_str(), logStr.size(), 0);
        if(ret < 0) {
            CCLOG("send() error");
        }
        return;
    }
    addTouch(x, y, touchID);
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, &waitCocosThread, touchID, this]() {
        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        Touch *touch = this->findTouch(touchID);
        Vec2 pos = touch->getLocationInView();
        auto touchBegan = TouchBegan::create(touch, pos, true);
        runningScene->runAction(touchBegan);
        waitCocosThread.notify_one();
    });
    waitCocosThread.wait(lock);
}

void ConsoleGestureCmd::commandTouchMove(int fd, const std::string &args)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    // args: touchMove x y touchID
    if(argv.size() < 4) return;

    std::string xStr = argv[1];
    std::string yStr = argv[2];
    std::string touchIDStr = argv[3];
    float x = std::stof(xStr);
    float y = std::stof(yStr);
    int touchID = std::stoi(touchIDStr);

    Touch *touch = findTouch(touchID);
    if(!touch) return;
    touch->setTouchInfo(touchID, x, y);

    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, &waitCocosThread, touch, this]() {
        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        Vec2 pos = touch->getLocationInView();
        auto touchMoved = TouchMoved::create(touch, pos);

        runningScene->runAction(touchMoved);
        waitCocosThread.notify_one();
    });
    waitCocosThread.wait(lock);
}

void ConsoleGestureCmd::commandTouchEnd(int fd, const std::string &args)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    // args: touchEnd x y touchID
    if(argv.size() < 4) return;

    std::string xStr = argv[1];
    std::string yStr = argv[2];
    std::string touchIDStr = argv[3];
    float x = std::stof(xStr);
    float y = std::stof(yStr);
    int touchID = std::stoi(touchIDStr);

    Touch *touch = findTouch(touchID);
    if(!touch) return;
    touch->setTouchInfo(touchID, x, y);
    removeTouch(touchID);

    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, &waitCocosThread, touch]() {
        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        Vec2 pos = touch->getLocationInView();
        auto touchEnded = TouchEnded::create(touch, pos);
        runningScene->runAction(touchEnded);
        waitCocosThread.notify_one();
    });
    waitCocosThread.wait(lock);
}

void ConsoleGestureCmd::commandTouchCancel(int fd, const std::string &args)
{
    std::mutex m;
    std::condition_variable waitCocosThread;
    std::unique_lock<std::mutex> lock(m);

    auto argv = split(args, ' ');
    // args: touchEnded x y touchID
    if(argv.size() < 3) return;

    std::string xStr = argv[1];
    std::string yStr = argv[2];
    std::string touchIDStr = argv[3];
    float x = std::stof(xStr);
    float y = std::stof(yStr);
    int touchID = std::stoi(touchIDStr);

    Touch *touch = findTouch(touchID);
    if(!touch) return;
    touch->setTouchInfo(touchID, x, y);
    removeTouch(touchID);

    Director::getInstance()->getScheduler()->performFunctionInCocosThread([fd, argv, &waitCocosThread, touch]() {
        auto director = Director::getInstance();
        auto runningScene = director->getRunningScene();
        Vec2 pos = touch->getLocationInView();
        auto touchEnded = TouchCancelled::create(touch, pos);
        runningScene->runAction(touchEnded);
        waitCocosThread.notify_one();
    });
    waitCocosThread.wait(lock);
}

void ConsoleGestureCmd::commandTouchStatus(int fd, const std::string &args)
{
    std::string logStr;
    logStr = getTouchesIDInfo();
    if(!logStr.empty()) {
        send(fd, logStr.c_str(), logStr.size(), 0);
    }
}

void ConsoleGestureCmd::addTouch(float x, float y, int touchID)
{
    Touch *touch = new Touch();
    touch->setTouchInfo(touchID, x, y);
    touchesMap.emplace(touchID, touch);
}

cocos2d::Touch *ConsoleGestureCmd::findTouch(int touchID)
{
    auto itr = touchesMap.find(touchID);
    if(itr == touchesMap.end()) return nullptr;
    return itr->second;
}

void ConsoleGestureCmd::removeTouch(int touchID)
{
    auto itr = touchesMap.find(touchID);
    if(itr == touchesMap.end()) return;

    touchesMap.erase(itr);
    Touch *touch = (Touch*)itr->second;
    touch->release();
}

std::string ConsoleGestureCmd::getTouchesIDInfo() {
    std::string logStr;
    if(touchesMap.empty()) {
        logStr.append("");
    } else {
        logStr.append("\ttouchID\t\tCoordinate\n");
        for (auto &itr : touchesMap) {
            std::stringstream ss;
            int touchID = itr.first;
            Touch *touch = itr.second;
            Vec2 pos = Director::getInstance()->convertToGL(touch->getLocationInView());
            ss << "\t" << touchID << "\t\t" << "(" << pos.x << "," << pos.y << ")" << std::endl;
            logStr.append(ss.str());
        }
    }
    return logStr;
}

void ConsoleGestureCmd::commandTap(int fd, const std::string &args)
{
    commandTapInternal(fd, args, false);
}

void ConsoleGestureCmd::commandSwipe(int fd, const std::string &args)
{
    commandSwipeInternal(fd, args, false);
}

void ConsoleGestureCmd::commandPinchIn(int fd, const std::string &args)
{
    commandPinchInInternal(fd, args, false);
}

void ConsoleGestureCmd::commandPinchOut(int fd, const std::string &args)
{
    commandPinchOutInternal(fd, args, false);
}

void ConsoleGestureCmd::commandTapAsync(int fd, const std::string &args)
{
    commandTapInternal(fd, args, true);
}

void ConsoleGestureCmd::commandSwipeAsync(int fd, const std::string &args)
{
    commandSwipeInternal(fd, args, true);
}

void ConsoleGestureCmd::commandPinchInAsync(int fd, const std::string &args)
{
    commandPinchInInternal(fd, args, true);
}

void ConsoleGestureCmd::commandPinchOutAsync(int fd, const std::string &args)
{
    commandPinchOutInternal(fd, args, true);
}
