//
// Created by NiTe Luo on 11/13/13.
//


#include "GroupCommand.h"
#include "Renderer.h"
#include "CCDirector.h"

NS_CC_BEGIN
RenderCommandPool<GroupCommand> GroupCommand::_commandPool;

static GroupCommandManager* s_instance;
GroupCommandManager *GroupCommandManager::getInstance()
{
    if(!s_instance)
    {
        s_instance = new GroupCommandManager();
        if(!s_instance->init())
        {
            CC_SAFE_DELETE(s_instance);
        }
    }
    return s_instance;
}

GroupCommandManager::GroupCommandManager()
{

}

GroupCommandManager::~GroupCommandManager()
{
    CC_SAFE_RELEASE_NULL(s_instance);
}

bool GroupCommandManager::init()
{
    //0 is the default render group
    _groupMapping[0] = true;
    return true;
}

int GroupCommandManager::getGroupID()
{
    //Reuse old id
    for(auto it = _groupMapping.begin(); it != _groupMapping.end(); ++it)
    {
        if(!it->second)
        {
            return it->first;
        }
    }

    //Create new ID
//    int newID = _groupMapping.size();
    int newID = Director::getInstance()->getRenderer()->createRenderQueue();
    _groupMapping[newID] = true;

    return newID;
}

void GroupCommandManager::releaseGroupID(int groupID)
{
    _groupMapping[groupID] = false;
}

GroupCommand::GroupCommand()
:RenderCommand()
, _viewport(0)
, _depth(0)
{
    _type = RenderCommand::Type::GROUP_COMMAND;
    _renderQueueID = GroupCommandManager::getInstance()->getGroupID();
}

void GroupCommand::init(int viewport, int32_t depth)
{
    _viewport = viewport;
    _depth = depth;
    GroupCommandManager::getInstance()->releaseGroupID(_renderQueueID);
    _renderQueueID = GroupCommandManager::getInstance()->getGroupID();
}

GroupCommand::~GroupCommand()
{
    GroupCommandManager::getInstance()->releaseGroupID(_renderQueueID);
}

int64_t GroupCommand::generateID()
{
    _id = 0;

    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 // translucent
            | (int64_t)_depth << 36;

    return _id;
}

void GroupCommand::releaseToCommandPool()
{
    getCommandPool().pushBackCommand(this);
}


NS_CC_END
