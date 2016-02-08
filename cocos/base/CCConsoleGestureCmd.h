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

#ifndef CCConsoleGestureCmd_hpp
#define CCConsoleGestureCmd_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include "base/CCConsole.h"
#include "base/CCTouch.h"

class ConsoleGestureCmd {
public:
    static ConsoleGestureCmd *getInstance() {
        static ConsoleGestureCmd instance;
        return &instance;
    }
    struct cocos2d::Console::Command& getCommand() { return command; }
    int getTouchPriority() const { return touchPriority; }
    void setTouchPriority(int priority) { touchPriority = priority; }

protected:
    static const int DEFAULT_TOUCH_PRIORITY = -9999;

    ConsoleGestureCmd();
    ~ConsoleGestureCmd();
    void addSubCommand(const std::string &name, const std::string &help, std::function<void(int, const std::string&)> callback);
    void commandGesture(int fd, const std::string &args);
    void commandHelp(int fd, const std::string &args);
    void commandTapInternal(int fd, const std::string &args, bool async);
    void commandSwipeInternal(int fd, const std::string &args, bool async);
    void commandPinchInInternal(int fd, const std::string &args, bool async);
    void commandPinchOutInternal(int fd, const std::string &args, bool async);
    void commandTap(int fd, const std::string &args);
    void commandSwipe(int fd, const std::string &args);
    void commandPinchIn(int fd, const std::string &args);
    void commandPinchOut(int fd, const std::string &args);
    void commandTapAsync(int fd, const std::string &args);
    void commandSwipeAsync(int fd, const std::string &args);
    void commandPinchInAsync(int fd, const std::string &args);
    void commandPinchOutAsync(int fd, const std::string &args);
    void commandTouchBegin(int fd, const std::string &args);
    void commandTouchMove(int fd, const std::string &args);
    void commandTouchEnd(int fd, const std::string &args);
    void commandTouchCancel(int fd, const std::string &args);
    void commandTouchStatus(int fd, const std::string &args);

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);

    void addTouch(float x, float y, int touchID);
    cocos2d::Touch *findTouch(int touchID);
    void removeTouch(int touchID);
    std::string getTouchesIDInfo();

private:
    struct cocos2d::Console::Command command;
    std::vector<struct cocos2d::Console::Command> subCommands;
    int touchPriority;
    std::unordered_map<int, cocos2d::Touch*> touchesMap;

    CC_DISALLOW_COPY_AND_ASSIGN(ConsoleGestureCmd);
};


#endif /* CCConsoleGestureCmd_hpp */
