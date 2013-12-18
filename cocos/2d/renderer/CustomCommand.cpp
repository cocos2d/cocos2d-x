//
// Created by NiTe Luo on 11/8/13.
//


#include "CustomCommand.h"

NS_CC_BEGIN
RenderCommandPool<CustomCommand> CustomCommand::_commandPool;

CustomCommand::CustomCommand()
:RenderCommand()
, func(nullptr)
{
    _type = CUSTOM_COMMAND;
}

CustomCommand::~CustomCommand()
{

}

int64_t CustomCommand::generateID()
{
    _id = 0;

    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 // translucent
            | (int64_t)_depth << 36;

    return _id;
}

void CustomCommand::execute()
{
    if(func)
    {
        func();
    }
}

void CustomCommand::releaseToCommandPool()
{
    getCommandPool().pushBackCommand(this);
}

NS_CC_END