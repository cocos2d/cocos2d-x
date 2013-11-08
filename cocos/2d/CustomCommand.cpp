//
// Created by NiTe Luo on 11/8/13.
//


#include "CustomCommand.h"

NS_CC_BEGIN

CustomCommand::CustomCommand(int viewport, int32_t depth)
:RenderCommand()
, _viewport(viewport)
, _depth(depth)
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
            | (int64_t)0 << 59 // is command
            | (int64_t)_depth << 35;

    return _id;
}

void CustomCommand::execute()
{
    if(func)
    {
        func();
    }
}

NS_CC_END