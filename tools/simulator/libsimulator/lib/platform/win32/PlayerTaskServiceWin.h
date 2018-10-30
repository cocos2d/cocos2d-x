/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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


#ifndef __PLAYER_TASK_SERVICE_WIN_H_
#define __PLAYER_TASK_SERVICE_WIN_H_

#include <sstream>

#include "PlayerTaskServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerTaskWin : public PlayerTask
{
public:
    static PlayerTaskWin *create(const std::string &name,
                                 const std::string &executePath,
                                 const std::string &commandLineArguments);

    virtual ~PlayerTaskWin();

    virtual bool run();
    virtual void stop();
    virtual void runInTerminal();

    // check task status
    virtual void update(float dt);

protected:
    PlayerTaskWin(const std::string &name,
                  const std::string &executePath,
                  const std::string &commandLineArguments);

    void cleanup();
    std::u16string makeCommandLine() const;

    HANDLE _childStdInRead;
    HANDLE _childStdInWrite;
    HANDLE _childStdOutRead;
    HANDLE _childStdOutWrite;
    PROCESS_INFORMATION _pi;

    static const size_t BUFF_SIZE = 4096;
    CHAR *_outputBuff;
    WCHAR *_outputBuffWide;
};

class PlayerTaskServiceWin : public PlayerTaskServiceProtocol
{
public:
    PlayerTaskServiceWin(HWND hwnd);
    virtual ~PlayerTaskServiceWin();

    virtual PlayerTask *createTask(const std::string &name,
                                   const std::string &executePath,
                                   const std::string &commandLineArguments);
    virtual PlayerTask *getTask(const std::string &name);
    virtual void removeTask(const std::string &name);

protected:
    HWND _hwnd;
    cocos2d::Map<std::string, PlayerTaskWin*> _tasks;
};

PLAYER_NS_END

#endif // __PLAYER_TASK_SERVICE_WIN_H_
