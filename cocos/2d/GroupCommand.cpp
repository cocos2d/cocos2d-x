//
// Created by NiTe Luo on 11/13/13.
//


#include "GroupCommand.h"

NS_CC_BEGIN

GroupCommand::GroupCommand(int viewport, int32_t depth, int renderQueueID)
:RenderCommand()
, _viewport(viewport)
, _depth(depth)
, _renderQueueID(renderQueueID)
{
    _type = GROUP_COMMAND;
}

GroupCommand::~GroupCommand()
{

}

int64_t GroupCommand::generateID()
{
    _id = 0;

    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 // translucent
            | (int64_t)_depth << 36;

    return _id;
}


NS_CC_END
