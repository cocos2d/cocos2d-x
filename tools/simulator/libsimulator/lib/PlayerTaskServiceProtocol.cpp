
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
