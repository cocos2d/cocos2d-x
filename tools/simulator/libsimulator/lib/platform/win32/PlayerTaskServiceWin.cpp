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


#include <sstream>

#include "stdafx.h"
#include "shellapi.h"
#include "PlayerTaskServiceWin.h"

static const int MAX_LOG_LENGTH = 16 * 1024;// from 2dx

PLAYER_NS_BEGIN

PlayerTaskWin *PlayerTaskWin::create(const std::string &name, const std::string &executePath, const std::string &commandLineArguments)
{
    PlayerTaskWin *task = new PlayerTaskWin(name, executePath, commandLineArguments);
    task->autorelease();
    return task;
}

PlayerTaskWin::PlayerTaskWin(const std::string &name,
                             const std::string &executePath,
                             const std::string &commandLineArguments)
                             : PlayerTask(name, executePath, commandLineArguments)
                             , _childStdInRead(NULL)
                             , _childStdInWrite(NULL)
                             , _childStdOutRead(NULL)
                             , _childStdOutWrite(NULL)
                             , _outputBuff(NULL)
                             , _outputBuffWide(NULL)
{
    ZeroMemory(&_pi, sizeof(_pi));
}

PlayerTaskWin::~PlayerTaskWin()
{
    cleanup();
}

bool PlayerTaskWin::run()
{
    if (!isIdle())
    {
        CCLOG("PlayerTaskWin::run() - task is not idle");
        return false;
    }

    //BOOL WINAPI CreateProcess(
    //    _In_opt_     LPCTSTR lpApplicationName,
    //    _Inout_opt_  LPTSTR lpCommandLine,
    //    _In_opt_     LPSECURITY_ATTRIBUTES lpProcessAttributes,
    //    _In_opt_     LPSECURITY_ATTRIBUTES lpThreadAttributes,
    //    _In_         BOOL bInheritHandles,
    //    _In_         DWORD dwCreationFlags,
    //    _In_opt_     LPVOID lpEnvironment,
    //    _In_opt_     LPCTSTR lpCurrentDirectory,
    //    _In_         LPSTARTUPINFO lpStartupInfo,
    //    _Out_        LPPROCESS_INFORMATION lpProcessInformation
    //);

    // http://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    // Create a pipe for the child process's STDOUT. 
    if (!CreatePipe(&_childStdOutRead, &_childStdOutWrite, &sa, 0) || !SetHandleInformation(_childStdOutRead, HANDLE_FLAG_INHERIT, 0))
    {
        CCLOG("PlayerTaskWin::run() - create stdout handle failed, for execute %s", _executePath.c_str());
        cleanup();
        return false;
    }

    // Create a pipe for the child process's STDIN. 
    if (!CreatePipe(&_childStdInRead, &_childStdInWrite, &sa, 0) || !SetHandleInformation(_childStdInWrite, HANDLE_FLAG_INHERIT, 0))
    {
        CCLOG("PlayerTaskWin::run() - create stdout handle failed, for execute %s", _executePath.c_str());
        cleanup();
        return false;
    }

    ZeroMemory(&_pi, sizeof(_pi));
    STARTUPINFO si = {0};

    si.cb = sizeof(STARTUPINFO);
    si.hStdError = _childStdOutWrite;
    si.hStdOutput = _childStdOutWrite;
    si.hStdInput = _childStdInRead;
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;

#define MAX_COMMAND 4096 //MAX_PATH
    const std::u16string u16command = makeCommandLine();
    WCHAR command[MAX_COMMAND];
    wcscpy_s(command, MAX_COMMAND, (WCHAR*)u16command.c_str());

    BOOL success = CreateProcess(NULL,
                                 command,   // command line 
                                 NULL,      // process security attributes 
                                 NULL,      // primary thread security attributes 
                                 TRUE,      // handles are inherited 
                                 0,         // creation flags 
                                 NULL,      // use parent's environment 
                                 NULL,      // use parent's current directory 
                                 &si,       // STARTUPINFO pointer 
                                 &_pi);     // receives PROCESS_INFORMATION 

    if (!success)
    {
        CCLOG("PlayerTaskWin::run() - create process failed, for execute %s", _executePath.c_str());
        cleanup();
        return false;
    }

    _outputBuff = new CHAR[BUFF_SIZE + 1];
    _outputBuffWide = new WCHAR[BUFF_SIZE];
    _state = STATE_RUNNING;

    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
    return true;
}

void PlayerTaskWin::runInTerminal()
{
	std::stringstream buf;
	buf << "/K ";
	buf << _executePath;
	buf << " ";
	buf << _commandLineArguments;

	std::u16string u16command;
	cocos2d::StringUtils::UTF8ToUTF16(buf.str(), u16command);

	ShellExecute(NULL, NULL, L"CMD.EXE", (WCHAR*)u16command.c_str(), NULL, SW_SHOWNORMAL);
}

void PlayerTaskWin::stop()
{
    if (_pi.hProcess)
    {
        TerminateProcess(_pi.hProcess, 0);
        _resultCode = -1;
    }
    cleanup();
}

void PlayerTaskWin::update(float dt)
{
    _lifetime += dt;

    // read output
    for (;;)
    {
        DWORD readCount = 0;
        PeekNamedPipe(_childStdOutRead, NULL, NULL, NULL, &readCount, NULL);
        if (readCount == 0) break;
        if (_output.length() > MAX_LOG_LENGTH) break;

        readCount = 0;
        ZeroMemory(_outputBuff, BUFF_SIZE + 1);
        BOOL success = ReadFile(_childStdOutRead, _outputBuff, BUFF_SIZE - 1, &readCount, NULL);
        if (!success || readCount == 0) break;

        int chars = MultiByteToWideChar(CP_OEMCP, 0, _outputBuff, readCount, _outputBuffWide, BUFF_SIZE);
        if (chars)
        {
            ZeroMemory(_outputBuff, BUFF_SIZE + 1);
            WideCharToMultiByte(CP_UTF8, 0, _outputBuffWide, chars, _outputBuff, BUFF_SIZE + 1, 0, NULL);
            _output.append(_outputBuff);
            if (_output.length() > MAX_LOG_LENGTH) break;
        }
    }

    // get child process exit code
    DWORD resultCode = 0;
    if (GetExitCodeProcess(_pi.hProcess, &resultCode))
    {
        if (resultCode == STILL_ACTIVE) return;
        _resultCode = (int)resultCode;
    }
    else
    {
        // unexpected error
        _resultCode = (int)GetLastError();
    }

    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    cleanup();
}

void PlayerTaskWin::cleanup()
{
    if (_pi.hProcess) CloseHandle(_pi.hProcess);
    if (_pi.hThread) CloseHandle(_pi.hThread);
    ZeroMemory(&_pi, sizeof(_pi));

    if (_outputBuff) delete[] _outputBuff;
    _outputBuff = NULL;
    if (_outputBuffWide) delete[] _outputBuffWide;
    _outputBuffWide = NULL;

    if (_childStdOutRead) CloseHandle(_childStdOutRead);
    if (_childStdOutWrite) CloseHandle(_childStdOutWrite);
    if (_childStdInRead) CloseHandle(_childStdInRead);
    if (_childStdInWrite) CloseHandle(_childStdInWrite);

    _childStdOutRead = NULL;
    _childStdOutWrite = NULL;
    _childStdInRead = NULL;
    _childStdInWrite = NULL;

    _state = STATE_COMPLETED;

    CCLOG("CMD: %s", _output.c_str());

    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(_name);
}

std::u16string PlayerTaskWin::makeCommandLine() const
{
    std::stringstream buf;
    buf << "\"";
    buf << _executePath;
    buf << "\" ";
    buf << _commandLineArguments;

    std::u16string u16command;
    cocos2d::StringUtils::UTF8ToUTF16(buf.str(), u16command);
    return u16command;
}

PlayerTaskServiceWin::PlayerTaskServiceWin(HWND hwnd)
    : _hwnd(hwnd)
{
}

PlayerTaskServiceWin::~PlayerTaskServiceWin()
{
    for (auto it = _tasks.begin(); it != _tasks.end(); ++it)
    {
        it->second->stop();
    }
}

PlayerTask *PlayerTaskServiceWin::createTask(const std::string &name,
                                             const std::string &executePath,
                                             const std::string &commandLineArguments)
{
    CCASSERT(_tasks.find(name) == _tasks.end(), "Task already exists.");
    PlayerTaskWin *task = PlayerTaskWin::create(name, executePath, commandLineArguments);
    _tasks.insert(name, task);
    return task;
}

PlayerTask *PlayerTaskServiceWin::getTask(const std::string &name)
{
    auto it = _tasks.find(name);
    return it != _tasks.end() ? it->second : nullptr;
}

void PlayerTaskServiceWin::removeTask(const std::string &name)
{
    auto it = _tasks.find(name);
    if (it != _tasks.end())
    {
        if (!it->second->isCompleted())
        {
            it->second->stop();
        }
        _tasks.erase(it);
    }
}

PLAYER_NS_END
