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


#include "PlayerTaskServiceProtocol.h"

PLAYER_NS_BEGIN

std::string PlayerTask::getName() const
{
    return _name;
}

std::string PlayerTask::getExecutePath() const
{
    return _executePath;
}

std::string PlayerTask::getCommandLineArguments() const
{
    return _commandLineArguments;
}

std::string PlayerTask::getOutput() const
{
    return _output;
}

int PlayerTask::getState() const
{
    return _state;
}

bool PlayerTask::isIdle() const
{
    return _state == STATE_IDLE;
}

bool PlayerTask::isRunning() const
{
    return _state == STATE_RUNNING;
}

bool PlayerTask::isCompleted() const
{
    return _state == STATE_COMPLETED;
}

float PlayerTask::getLifetime() const
{
    return _lifetime;
}

int PlayerTask::getResultCode() const
{
    return _resultCode;
}

PlayerTask::PlayerTask(const std::string &name,
                       const std::string &executePath,
                       const std::string &commandLineArguments)
                       : _name(name)
                       , _executePath(executePath)
                       , _commandLineArguments(commandLineArguments)
                       , _lifetime(0)
                       , _state(STATE_IDLE)
                       , _resultCode(0)
{
}

PLAYER_NS_END
